#include "kStew.h"
//+ + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + +
void WriteProtection(int Protect)
{
	if(!Protect)
	{
		__asm
		{
			PUSH EAX
			CLI
			MOV EAX,CR0
			AND EAX,NOT 0x10000
			MOV CR0,EAX
			POP EAX
		}
	}
	else
	{
		__asm
		{
			PUSH EAX
			MOV EAX,CR0
			OR  EAX,0x10000
			MOV CR0,EAX
			STI
			POP EAX
		}
	}
}
//+ + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + +
void SaveSDT(PVOID FakeSDT)
{
	ULONG ulSize;
	ulSize = KeServiceDescriptorTable->TableSize * 4;
	if(ulSize > 0)
	{
		FakeSDT = ExAllocatePool(NonPagedPool, ulSize);
		if(FakeSDT != NULL)
		{
			__try
			{
				WriteProtection(0);
				RtlCopyMemory(FakeSDT, &KeServiceDescriptorTable->ServiceTable[0], ulSize);
				WriteProtection(1);
			}
			__except(1)
			{
			}
		}
	}
}
//+ + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + +
void RestoreSDT(PVOID FakeSDT)
{
	ULONG ulSize;
	ulSize = KeServiceDescriptorTable->TableSize * 4;
	__try
	{
		WriteProtection(0);
		RtlCopyMemory(&KeServiceDescriptorTable->ServiceTable[0], FakeSDT, ulSize);
		WriteProtection(1);
	}
	__except(1)
	{
	}
}
//+ + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + +
PMODULE_LIST GetModuleList()
{
	NTSTATUS NtStatus;
	ULONG ulNeededSize;
	PULONG pulModuleList;

	ZwQuerySystemInformation(SystemModuleInformation, &ulNeededSize, 0, &ulNeededSize);
	pulModuleList = (PULONG)ExAllocatePoolWithTag(PagedPool, ulNeededSize, 'mlst');
	NtStatus = ZwQuerySystemInformation(SystemModuleInformation, pulModuleList, ulNeededSize, 0);

	return (PMODULE_LIST)pulModuleList;
}
//+ + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + +
PVOID GetModuleHandle(PCHAR ModuleName)
{
	PMODULE_LIST pModules = GetModuleList();
	PMODULE_INFO pKernelInfo;

	char Temp[255], Temp2[255];

	for(int i = 0; i < (int)pModules->dwModules; i++)
	{
		pKernelInfo = &pModules->Modules[i];
		RtlZeroMemory(&Temp2, 255);
		RtlZeroMemory(&Temp, 255);
		strcpy(Temp, pKernelInfo->cPath);
		_strrev(Temp);
		for(int j = 0; j < (int)strlen(pKernelInfo->cPath); j++)
		{
			if(Temp[j] != '\\')
			{
				Temp2[j] = Temp[j];
			}
			else
			{
				break;
			}
		}
		RtlZeroMemory(&Temp, 255);
		strcpy(Temp, Temp2);
		_strrev(Temp);
		if(strcmp(Temp, ModuleName) == 0)
		{
			return (PVOID)pKernelInfo->dwBase;
		}
	}
	return NULL;
}
//+ + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + +
PVOID GetProcAddress(PVOID ModuleBase, PCHAR pFunctionName)
{
typedef struct _IMAGE_EXPORT_DIRECTORY {
	ULONG   Characteristics;
	ULONG   TimeDateStamp;
	USHORT  MajorVersion;
    USHORT  MinorVersion;
	ULONG   Name;
	ULONG   Base;
	ULONG   NumberOfFunctions;
	ULONG   NumberOfNames;
	ULONG   AddressOfFunctions;
	ULONG   AddressOfNames;
	ULONG   AddressOfNameOrdinals;
} IMAGE_EXPORT_DIRECTORY, *PIMAGE_EXPORT_DIRECTORY;

    PVOID pFunctionAddress = NULL;

    __try
    {
		ULONG size = 0;
		PIMAGE_EXPORT_DIRECTORY exports = (PIMAGE_EXPORT_DIRECTORY)RtlImageDirectoryEntryToData(ModuleBase, TRUE, 0, &size);
		ULONG addr = (ULONG)exports - (ULONG)ModuleBase;
		PULONG functions = PULONG((ULONG)ModuleBase + exports->AddressOfFunctions);
		PSHORT ordinals = PSHORT((ULONG)ModuleBase + exports->AddressOfNameOrdinals);
		PULONG names = PULONG((ULONG)ModuleBase + exports->AddressOfNames);
		ULONG max_name = exports->NumberOfNames;
		ULONG max_func = exports->NumberOfFunctions;

        ULONG i;
		for(i = 0; i < max_name; i++)
        {
            ULONG ord = ordinals[i];
			if(i >= max_name || ord >= max_func)
			{
                return NULL;
            }
            if (functions[ord] < addr || functions[ord] >= addr + size)
			{
				if(strcmp((PCHAR) ModuleBase + names[i], pFunctionName) == 0)
                {
					pFunctionAddress = PVOID((PCHAR) ModuleBase + functions[ord]);
					break;
                }
            }
		}
	}
    __except(EXCEPTION_EXECUTE_HANDLER)
    {
        pFunctionAddress = NULL;
	}

    return pFunctionAddress;
}
//+ + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + +
