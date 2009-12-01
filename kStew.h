//NTSYSAPI NTSTATUS NTAPI NtWriteVirtualMemory(IN HANDLE ProcessHandle,IN PVOID BaseAddress, IN PVOID Buffer,IN ULONG NumberOfBytesToWrite, OUT PULONG NumberOfBytesWritten OPTIONAL);
PVOID RtlImageDirectoryEntryToData(IN PVOID Base,IN BOOLEAN MappedAsImage,IN USHORT DirectoryEntry,OUT PULONG Size);
//+ + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + +
#define SYSTEMSERVICE(CallNumber) KeServiceDescriptorTable->ServiceTable[CallNumber]
//+ + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + +
typedef struct _MODULE_INFO
{
	ULONG dwReserved[2];
	ULONG dwBase;
	ULONG dwSize;
	ULONG dwFlags;
	USHORT wIndex;
	USHORT wRank;
	USHORT wLoadCount;
	USHORT NameOffset;
	char cPath[256];
} MODULE_INFO, *PMODULE_INFO, **PPMODULE_INFO;

typedef struct _MODULE_LIST
{
	ULONG dwModules;
	MODULE_INFO Modules[1];
} MODULE_LIST, *PMODULE_LIST, **PPMODULE_LIST;

typedef struct _DEVICE_EXTENSION
{
	PDEVICE_OBJECT DeviceObject;
} DEVICE_EXTENSION, *PDEVICE_EXTENSION;
//+ + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + +
