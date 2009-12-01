#include "Stew.h"
/* ..:: METHODS ::.. */

bool Stew::_CreateMutex(UnicodeString Name)
{
	return CreateMutexW(NULL, true, Name.c_str()) != 0 ? GetLastError() != 183 : false;
}

UnicodeString Stew::_RegReadString(HKEY Key, UnicodeString KeyName, UnicodeString Value)
{
	HKEY aux;
	DWORD Data, Type = 1;
	UnicodeString Return = "";

	if (RegOpenKeyW(Key, KeyName.c_str(), &aux) == 0)
	{
		if (!RegQueryValueExW(aux, Value.c_str(), NULL, &Type, NULL, &Data))
		{
			Pointer DataPointer = malloc(Data);
			if (!RegQueryValueExW(aux, Value.c_str(), NULL, &Type, (LPBYTE)DataPointer, &Data))
			{
				Return.SetLength(--Data);
				try
				{
					if (Data + 1 > 0)
					{
						memcpy(&Return[1], DataPointer, Data);
					}
				}
				catch(...)
				{
				}
			}

			free(DataPointer);
		}
		RegCloseKey(aux);
	}
	return Return;
}

bool Stew::_RegWriteString(HKEY Key, UnicodeString KeyName, UnicodeString Value, UnicodeString Text, bool bolCanCreateKey, bool bolCanOverrideValue)
{
	HKEY aux;
	bool bolReturn = false;

	if (bolCanCreateKey)
	{
		_RegCreateKey(Key, KeyName);
	}
	if (RegOpenKeyW(Key, KeyName.c_str(), &aux) == 0)
	{
		if ((bolCanOverrideValue) || (!bolCanOverrideValue && !_RegValueExists(Key, KeyName, Value)))
		{
			bolReturn = RegSetValueExW(aux, Value.c_str(), 0, REG_SZ, (PBYTE)Text.c_str(), Text.Length() * 2) == 0;
		}
		RegCloseKey(aux);
	}
	return bolReturn;
}

void Stew::_DeleteShellExtension(UnicodeString strExtensionWithDot)
{
	if (strExtensionWithDot.Length() == 0)
	{
		return;
	}
	if (strExtensionWithDot[1] != '.')
	{
		strExtensionWithDot = L"." + strExtensionWithDot;
	}
	_RegDeleteKey(HKEY_CLASSES_ROOT, strExtensionWithDot);
}

void Stew::_AddShellExtension(UnicodeString strExtensionWithDot, UnicodeString strShellCaption, UnicodeString strExePath, UnicodeString strIconPath)
{
	if (strExtensionWithDot.Length() == 0 || !FileExists(strExePath))
	{
		return;
	}
	if (strExtensionWithDot[1] != L'.')
	{
		strExtensionWithDot = L"." + strExtensionWithDot;
	}
	_RegWriteString(HKEY_CLASSES_ROOT, strExtensionWithDot + L"\\shell\\open\\command", "", L"\"" + strExePath + L"\" \"%1\"", true, true);
	_RegWriteString(HKEY_CLASSES_ROOT, strExtensionWithDot + L"\\shell\\open", "", strShellCaption, true, true);
	if (strIconPath.Length() > 0)
	{
		_RegWriteString(HKEY_CLASSES_ROOT, strExtensionWithDot + L"\\DefaultIcon", "", strIconPath, true, true);
	}
}

bool Stew::_RegDeleteKey(HKEY Key, UnicodeString KeyName)
{
	HKEY aux;
	UnicodeString strAux, strAux2, strAux3, strAux4;

	if (KeyName.Length() == 0)
	{
		return false;
	}

	for (int i = 1; i <= KeyName.Length(); i++)
	{
		if (KeyName[i] != '\\')
		{
			strAux += KeyName[i];
		}
		else
		{
			if (i + 1 > KeyName.Length())
			{
				if (strAux.Length() > 0)
				{
					if (strAux[strAux.Length()] == '\\')
					{
						strAux.SetLength(strAux.Length() - 1);
					}
				}
				break;
			}
			strAux4 = KeyName[i];
			strAux4 += KeyName[i + 1];
			if (strAux4 == L"\\\\")
			{
				i++;
				if (strAux.Length() > 0)
				{
					if (strAux[strAux.Length()] != '\\')
					{
						strAux += KeyName[i - 1];
					}
					if (strAux[strAux.Length()] == '\\')
					{
						if (i + 1 > KeyName.Length())
						{
							strAux.SetLength(strAux.Length() - 1);
						}
					}
				}
			}
			else
			{
				if (strAux.Length() > 0)
				{
					if (strAux[strAux.Length()] != '\\')
					{
						strAux += KeyName[i];
					}
				}
			}
		}
	}

	KeyName = strAux.c_str();

	if (RegDeleteKeyW(Key, strAux.c_str()) == 0)
	{
		return true;
	}

	do
	{
		if (RegOpenKeyW(Key, strAux.c_str(), &aux) != 0)
		{
			return false;
		}
		strAux3 = strAux2.c_str();
		strAux3.SetLength(strAux3.Length() - 1);
		strAux2 = strAux + L"\\";
		DWORD dwdAux = 255;
		FILETIME fltAux;
		if (RegEnumKeyExW(aux, 0, strAux.c_str(), &dwdAux, NULL, NULL, NULL, &fltAux) == 0)
		{
			strAux = strAux2 + strAux.c_str();
		}
		else
		{
			RegDeleteKeyW(Key, strAux.c_str());
			if (strAux == KeyName)
			{
				return true;
			}
			strAux = strAux3.c_str();
			strAux3 += L"\\";
			strAux2 = strAux.c_str();
			for (int i = strAux2.Length(); i > 0; i--)
			{
				if (strAux2[i] == L'\\')
				{
					break;
				}
				strAux2.SetLength(strAux2.Length() - 1);
			}

		}
		RegCloseKey(aux);
	}
	while (true);
}

bool Stew::_RegDeleteValue(HKEY Key, UnicodeString KeyName, UnicodeString Value)
{
	HKEY aux;
	bool bolReturn = false;

	if (RegOpenKeyW(Key, KeyName.c_str(), &aux) == 0)
	{
		bolReturn = RegDeleteValueW(aux, Value.c_str()) == 0;
		RegCloseKey(aux);
	}
	return bolReturn;
}

bool Stew::_RegValueExists(HKEY Key, UnicodeString KeyName, UnicodeString Value)
{
	HKEY aux;
	bool bolReturn = false;

	if (RegOpenKeyW(Key, KeyName.c_str(), &aux) == 0)
	{
		bolReturn = RegQueryValueExW(aux, Value.c_str(), NULL, NULL, NULL, NULL) == 0;
		RegCloseKey(aux);
	}
	return bolReturn;
}

bool Stew::_RegCreateKey(HKEY Key, UnicodeString KeyName)
{
	HKEY aux;

	bool bolReturn = RegCreateKeyW(Key, KeyName.c_str(), &aux) == 0;
	RegCloseKey(aux);
	return bolReturn;
}

void Stew::_MemoryManagement(int intPID, HANDLE& hndProcessHandle)
{
	_DebugPrivilege();
	hndProcessHandle = OpenProcess(2035711, false, intPID);
}

int Stew::_GetPID(UnicodeString strProcessName)
{
	tagPROCESSENTRY32 tpeEntry;
	int intReturn = 0;

	HANDLE hndSnapshot = CreateToolhelp32Snapshot(2, 0);
	tpeEntry.dwSize = sizeof(tpeEntry);
	Process32First(hndSnapshot, &tpeEntry);
	do
	{
		if (UpperCase(strProcessName) == UpperCase(UnicodeString(tpeEntry.szExeFile)))
		{
			intReturn = tpeEntry.th32ProcessID;
		}
	}
	while (Process32Next(hndSnapshot, &tpeEntry));
	CloseHandle(hndSnapshot);
	return intReturn;
}

void Stew::_DebugPrivilege()
{
	_TOKEN_PRIVILEGES tkpAux;
	HANDLE hndToken;

	if (OpenProcessToken(GetCurrentProcess(), 40, &hndToken))
	{
		tkpAux.PrivilegeCount = 1;
		tkpAux.Privileges[0].Attributes = 2;
		LookupPrivilegeValue(NULL, SE_DEBUG_NAME, &tkpAux.Privileges[0].Luid);
		AdjustTokenPrivileges(hndToken, false, &tkpAux, 16, NULL, NULL);
	}
	CloseHandle(hndToken);
}

bool Stew::_Odd(int intNumber)
{
	return intNumber % 2 != 0;
}

UINT Stew::_SaveProcedure(Pointer ptrProcedure, Pointer ptrDestiny)
{
	UINT intSaveSize = 0, intSize;
	Pointer ptrNext = ptrProcedure;

	while (intSaveSize < 5)
	{
		intSize = _CodeSize(ptrNext);
		ptrNext = Pointer((UINT)ptrNext + intSize);
		intSaveSize += intSize;
	}
	memcpy(ptrDestiny, ptrProcedure, intSaveSize);
	*PBYTE(Pointer((UINT)ptrDestiny + intSaveSize)) = 0xE9;
	*PUINT(Pointer((UINT)ptrDestiny + intSaveSize + 1)) = (UINT)ptrNext - (UINT)ptrDestiny - intSaveSize - 5;
	return intSaveSize;
}

bool Stew::_HookProcedure(UnicodeString strTargetDLL, UnicodeString strTargetName, Pointer ptrNewProcedure, Pointer& ptrSave)
{
	try
	{
		DWORD dwdOldProtect;
		Pointer ptrOriginalStorage = malloc(255);
		Pointer ptrOriginalAddress = GetProcAddress(GetModuleHandleW(strTargetDLL.c_str()), AnsiString(strTargetName).c_str());
		UINT Address = (UINT)ptrNewProcedure - (UINT)ptrOriginalAddress - 5;

		VirtualProtect(ptrOriginalAddress, 5, PAGE_EXECUTE_READWRITE, &dwdOldProtect);
		*(PUINT)ptrOriginalStorage = (UINT)ptrOriginalAddress;
		*PBYTE(Pointer((UINT)ptrOriginalStorage + 4)) = _SaveProcedure(ptrOriginalAddress, Pointer((UINT)ptrOriginalStorage + 5));
		*(PBYTE)ptrOriginalAddress = 0xE9;
		*PUINT((UINT)ptrOriginalAddress + 1) = Address;
		VirtualProtect(ptrOriginalAddress, 5, dwdOldProtect, &dwdOldProtect);
		ptrSave = Pointer((UINT)ptrOriginalStorage + 5);
	}
	catch(...)
	{
		return false;
	}
	return true;
}

bool Stew::_UnhookProcedure(Pointer ptrSave)
{
	try
	{
		DWORD dwdOldProtect;

		Pointer ptrOriginalAddress = Pointer(UINT(*PPointer((UINT)ptrSave - 5)));
		UINT intSaveSize = *PBYTE(Pointer((UINT)ptrSave - 1));
		VirtualProtect(ptrOriginalAddress, 5, PAGE_EXECUTE_READWRITE, &dwdOldProtect);
		memcpy(ptrOriginalAddress, ptrSave, intSaveSize);
		VirtualProtect(ptrOriginalAddress, 5, dwdOldProtect, &dwdOldProtect);
		free(Pointer((UINT)ptrSave - 5));
	}
	catch(...)
	{
		return false;
	}
	return true;
}

UINT Stew::_CodeSize(Pointer ptrCode)
{
	const Word wrdOpcodes[256] =
	{
		16913, 17124, 8209, 8420, 33793, 35906, 0, 0, 16913, 17124, 8209, 8420, 33793, 35906, 0, 0, 16913, 17124, 8209, 8420, 33793, 35906, 0, 0, 16913, 17124,
		8209, 8420, 33793, 35906, 0, 0, 16913, 17124, 8209, 8420, 33793, 35906, 0, 32768, 16913, 17124, 8209, 8420, 33793, 35906, 0, 32768, 16913, 17124, 8209,
		8420, 33793, 35906, 0, 32768, 529, 740, 17, 228, 1025, 3138, 0, 32768, 24645, 24645, 24645, 24645, 24645, 24645, 24645, 24645, 24645, 24645, 24645,
		24645, 24645, 24645, 24645, 24645, 69, 69, 69, 69, 69, 69, 69, 69, 24645, 24645, 24645, 24645, 24645, 24645, 24645, 24645, 0, 32768, 228, 16922, 0, 0,
		0, 0, 3072, 11492, 1024, 9444, 0, 0, 0, 0, 5120, 5120, 5120, 5120, 5120, 5120, 5120, 5120, 5120, 5120, 5120, 5120, 5120, 5120, 5120, 5120, 1296, 3488, 1296,
		1440, 529, 740, 41489, 41700, 16913, 17124, 8209, 8420, 17123, 8420, 227, 416, 0, 57414, 57414, 57414, 57414, 57414, 57414, 57414, 32768, 0, 0, 0, 0,
		0, 0, 32768, 33025, 33090, 769, 834, 0, 0, 0, 0, 1025, 3138, 0, 0, 32768, 32768, 0, 0, 25604, 25604, 25604, 25604, 25604, 25604, 25604, 25604, 27717, 27717,
		27717, 27717, 27717, 27717, 27717, 27717, 17680, 17824, 2048, 0, 8420, 8420, 17680, 19872, 0, 0, 2048, 0, 0, 1024, 0, 0, 16656, 16800, 16656, 16800,
		33792, 33792, 0, 32768, 8, 8, 8, 8, 8, 8, 8, 8, 5120, 5120, 5120, 5120, 33793, 33858, 1537, 1602, 7168, 7168, 0, 5120, 32775, 32839, 519, 583, 0, 0, 0,
		0, 0, 0, 8, 8, 0, 0, 0, 0, 0, 0, 16656, 416
	}, wrdOpcodes2[256] =
	{
		280, 288, 8420, 8420, 65535, 0, 0, 0, 0, 0, 65535, 65535, 65535, 272, 0, 1325, 63, 575, 63, 575, 63, 63, 63, 575, 272, 65535, 65535, 65535, 65535,
		65535, 65535, 65535, 16419, 16419, 547, 547, 65535, 65535, 65535, 65535, 63, 575, 47, 575, 61, 61, 63, 63, 0, 32768, 32768, 32768, 0, 0, 65535, 65535, 65535,
		65535, 65535, 65535, 65535, 65535, 65535, 65535, 8420, 8420, 8420, 8420, 8420, 8420, 8420, 8420, 8420, 8420, 8420, 8420, 8420, 8420, 8420, 8420, 16935,
		63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 63, 237, 237, 237, 237, 237, 237, 237, 237, 237, 237, 237, 237, 237, 237, 101, 237, 1261, 1192,
		1192, 1192, 237, 237, 237, 0, 65535, 65535, 65535, 65535, 65535, 65535, 613, 749, 7168, 7168, 7168, 7168, 7168, 7168, 7168, 7168, 7168, 7168, 7168,
		7168, 7168, 7168, 7168, 7168, 16656, 16656, 16656, 16656, 16656, 16656, 16656, 16656, 16656, 16656, 16656, 16656, 16656, 16656, 16656, 16656, 0, 0, 32768, 740,
		18404, 17380, 49681, 49892, 0, 0, 0, 17124, 18404, 17380, 32, 8420, 49681, 49892, 8420, 17124, 8420, 8932, 8532, 8476, 65535, 65535, 1440, 17124, 8420,
		8420, 8532, 8476, 41489, 41700, 1087, 548, 1125, 9388, 1087, 33064, 24581, 24581, 24581, 24581, 24581, 24581, 24581, 24581, 65535, 237, 237, 237, 237,
		237, 749, 8364, 237, 237, 237, 237, 237, 237, 237, 237, 237, 237, 237, 237, 237, 237, 63, 749, 237, 237, 237, 237, 237, 237, 237, 237, 65535, 237, 237,
		237, 237, 237, 237, 237, 237, 237, 237, 237, 237, 237, 237, 0
	}, wrdOpcodes3[10][16] =
	{
		1296, 65535, 16656, 16656, 33040, 33040, 33040, 33040, 1296, 65535, 16656, 16656, 33040, 33040, 33040, 33040, 3488, 65535, 16800, 16800, 33184, 33184,
		33184, 33184, 3488, 65535, 16800, 16800, 33184, 33184, 33184, 33184, 288, 288, 288, 288, 288, 288, 288, 288, 54, 54, 48, 48, 54, 54, 54, 54, 288,
		65535, 288, 288, 272, 280, 272, 280, 48, 48, 0, 48, 0, 0, 0, 0, 288, 288, 288, 288, 288, 288, 288, 288, 54, 54, 54, 54, 65535, 0, 65535, 65535, 288, 65535, 288,
		288, 65535, 304, 65535, 304, 54, 54, 54, 54, 0, 54, 54, 0, 296, 296, 296, 296, 296, 296, 296, 296, 566, 566, 48, 48, 566, 566, 566, 566, 296, 65535, 296, 296,
		272, 65535, 272, 280, 48, 48, 48, 48, 48, 48, 65535, 65535, 280, 280, 280, 280, 280, 280, 280, 280, 566, 566, 48, 566, 566, 566, 566, 566, 280, 65535, 280, 280,
		304, 296, 304, 296, 48, 48, 48, 48, 0, 54, 54, 65535
	};

	try
	{
		UINT intLast = (UINT)ptrCode, intOperandOverride = 4, intFlags, intRm, intSize, intExtend = 0;
		bool bolFixed = false, bolAddressOverride = false;
		BYTE bytModrm;
		WORD wrdOpcode;

		if (ptrCode != NULL)
		{
			do
			{
				wrdOpcode = *(PBYTE)ptrCode;
				ptrCode = Pointer((UINT)ptrCode + 1);
				if (wrdOpcode == 0x66)
				{
					intOperandOverride = 2;
				}
				else
				{
					if (wrdOpcode == 0x67)
					{
						bolAddressOverride = true;
					}
					else
					{
						if (!((wrdOpcode & 0xE7) == 0x26))
						{
							if (wrdOpcode != 0x64 && wrdOpcode != 0x65)
							{
								bolFixed = true;
							}
						}
					}
				}
			}
			while (!bolFixed);
			if (wrdOpcode == 0x0F)
			{
				wrdOpcode = *(PBYTE)ptrCode;
				intFlags = wrdOpcodes2[wrdOpcode];
				wrdOpcode += 0x0F00;
				ptrCode = Pointer((UINT)ptrCode + 1);
			}
			else
			{
				intFlags = wrdOpcodes[wrdOpcode];
			}
			if ((intFlags & 0x0038) != 0)
			{
				bytModrm = *(PBYTE)ptrCode;
				intRm = bytModrm & 0x7;
				ptrCode = Pointer((UINT)ptrCode + 1);
				switch(bytModrm & 0xC0)
				{
					case 0x40:
					{
						intSize = 1;
						break;
					}
					case 0x80:
					{
						intSize = bolAddressOverride ? 2 : 4;
						break;
					}
					default:
					{
						intSize = 0;
					}
				}
				if (!(((bytModrm & 0xC0) != 0xC0) && bolAddressOverride))
				{
					if ((intRm == 4) && ((bytModrm & 0xC0) != 0xC0))
					{
						intRm = *(PBYTE)ptrCode & 0x7;
					}
					if ((intRm == 5) && ((bytModrm & 0xC0) == 0))
					{
						intSize = 4;
					}
					ptrCode = Pointer((UINT)ptrCode + intSize);
				}
				if ((intFlags & 0x0038) == 0x0008)
				{
					switch(wrdOpcode)
					{
						case 0xF6:
						{
							intExtend = 0;
							break;
						}
						case 0xF7:
						{
							intExtend = 1;
							break;
						}
						case 0xD8:
						{
							intExtend = 2;
							break;
						}
						case 0xD9:
						{
							intExtend = 3;
							break;
						}
						case 0xDA:
						{
							intExtend = 4;
							break;
						}
						case 0xDB:
						{
							intExtend = 5;
							break;
						}
						case 0xDC:
						{
							intExtend = 6;
							break;
						}
						case 0xDD:
						{
							intExtend = 7;
							break;
						}
						case 0xDE:
						{
							intExtend = 8;
							break;
						}
						case 0xDF:
						{
							intExtend = 9;
							break;
						}
					}
					intFlags = wrdOpcodes3[intExtend][((bytModrm >> 3) & 0x7) + (bytModrm & 0xC0) != 0xC0 ? 0 : 8];
				}
			}
			switch(intFlags & 0x0C00)
			{
				case 0x0400:
				{
					ptrCode = Pointer((UINT)ptrCode + 1);
					break;
				}
				case 0x0800:
				{
					ptrCode = Pointer((UINT)ptrCode + 2);
					break;
				}
				case 0x0C00:
				{
					ptrCode = Pointer((UINT)ptrCode + intOperandOverride);
					break;
				}
				default:
				{
					switch(wrdOpcode)
					{
						case 0x9A:
						case 0xEA:
						{
							ptrCode = Pointer((UINT)ptrCode + intOperandOverride + 2);
							break;
						}
						case 0xC8:
						{
							ptrCode = Pointer((UINT)ptrCode + 3);
							break;
						}
						case 0xA0:
						case 0xA1:
						case 0xA2:
						case 0xA3:
						{
							ptrCode = Pointer((UINT)ptrCode + bolAddressOverride ? 2 : 4);
							break;
						}
					}
				}
			}
		}
		return(UINT)ptrCode - intLast;
	}
	catch(...)
	{
		return 0;
	}
}

UINT Stew::_ProcedureSize(Pointer ptrProcedure)
{
	UINT intLength, intReturn = 0;
	do
	{
		intLength = _CodeSize(ptrProcedure);
		intReturn += intLength;
		if (intLength == 1 && *(PBYTE)ptrProcedure == 0xC3)
		{
			break;
		}
		ptrProcedure = Pointer((UINT)ptrProcedure + intLength);
	}
	while (intLength > 0);
	return intReturn;
}

bool Stew::_InjectDLL(int intPID, UnicodeString strDLLFullPath)
{
	HANDLE hndProcessHandle;
	_MemoryManagement(intPID, hndProcessHandle);
	bool bolReturn = false;
	if (!FileExists(strDLLFullPath) || hndProcessHandle == NULL)
	{
		return bolReturn;
	}
	Pointer ptrPathAddress = VirtualAllocEx(hndProcessHandle, NULL, strDLLFullPath.Length() * 2, 4096, 4);
	WriteProcessMemory(hndProcessHandle, ptrPathAddress, strDLLFullPath.c_str(), strDLLFullPath.Length() * 2, 0);
	HANDLE hndRemoteThread = CreateRemoteThread(hndProcessHandle, NULL, 0, (PTHREAD_START_ROUTINE)GetProcAddress
		(GetModuleHandle("kernel32.dll"), "LoadLibraryW"), ptrPathAddress, 0, NULL);
	if (hndRemoteThread)
	{
		bolReturn = WaitForSingleObject(hndRemoteThread, 100) != 258;
	}
	VirtualFreeEx(hndProcessHandle, ptrPathAddress, 0, MEM_RELEASE);
	CloseHandle(hndRemoteThread);
	CloseHandle(hndProcessHandle);
	return bolReturn;
}

void Stew::_GetProcessModules(int intPID, TStringList* stlModulesList)
{
	typedef BOOL(WINAPI * TEnumProcessModules)(HANDLE hProcess, HMODULE * lphModule, DWORD cb, LPDWORD lpcbNeeded);
	typedef DWORD(WINAPI * TGetModuleFileNameExW)(HANDLE hProcess, HMODULE hModule, LPTSTR lpFilename, DWORD nSize);

	HMODULE hmdModules[1024];
	DWORD dwdNeed = 0;
	WideChar wchFileName[260];
	HANDLE hndPsapi = LoadLibraryA("psapi.dll");
	TEnumProcessModules _EnumProcessModules = (TEnumProcessModules)GetProcAddress(hndPsapi, "EnumProcessModules");
	TGetModuleFileNameExW _GetModuleFileNameExW = (TGetModuleFileNameExW)GetProcAddress(hndPsapi, "GetModuleFileNameExW");
	HANDLE hndProcessHandle;
	Stew::_MemoryManagement(intPID, hndProcessHandle);
	_EnumProcessModules(hndProcessHandle, hmdModules, sizeof(hmdModules), &dwdNeed);
	stlModulesList->Clear();
	for (UINT i = 0; i < (dwdNeed / sizeof(HMODULE)); i++)
	{
		_GetModuleFileNameExW(hndProcessHandle, hmdModules[i], (LPTSTR)wchFileName, sizeof(wchFileName) / sizeof(WideChar));
		stlModulesList->Add(wchFileName);
	}
	CloseHandle(hndProcessHandle);
	FreeLibrary(hndPsapi);
}

void Stew::_ExtractResource(UnicodeString Name, PWideChar wchResType, UnicodeString strPath)
{
	TResourceStream* rcsAux = new TResourceStream((int)HInstance, Name, wchResType);
	rcsAux->SaveToFile(strPath);
	delete rcsAux;
}

UnicodeString Stew::_DissectString(int intPosition, UnicodeString strSeparator, UnicodeString Text)
{
	TStringList* stlAux = new TStringList;
	_SeparateString(Text, strSeparator, stlAux);
	UnicodeString txt = stlAux->Text;
	if (intPosition <= stlAux->Count)
	{
		String strAux = stlAux->Strings[intPosition - 1];
		delete stlAux;
		return strAux;
	}
	return "";
}

UnicodeString Stew::_GetDirectory(Stew_GetDirectory cusDirectory)
{
	WideChar wchReturn[256];
	switch(cusDirectory)
	{
		case __System32:
		{
			GetSystemDirectoryW(wchReturn, 256);
			break;
		}
		case __WINDOWS:
		{
			GetWindowsDirectoryW(wchReturn, 256);
			break;
		}
		case __Temp:
		{
			GetTempPathW(256, wchReturn);
			break;
		}
	}
	if (cusDirectory == __WinDrive)
	{
		return _GetDirectory(__WINDOWS)[1];
	}
	else
	{
		return UnicodeString(wchReturn);
	}
}

void Stew::_FormPosition(TForm* frmForm, Stew_FormPosition cusHorizontal, Stew_FormPosition cusVertical)
{
	TRect recAux;

	if (!SystemParametersInfo(48, 0, &recAux, 0))
	{
		recAux = Rect(0, 0, Screen->Width, Screen->Height);
	}
	switch(cusHorizontal)
	{
		case __Left:
		{
			frmForm->Left = 0;
			break;
		}
		case __Center:
		{
			frmForm->Left = (recAux.Right - recAux.Left - frmForm->Width) / 2;
			break;
		}
		case __Right:
		{
			frmForm->Left = recAux.Right - frmForm->Width;
			break;
		}
	}
	switch(cusVertical)
	{
		case __Top:
		{
			frmForm->Top = 0;
			break;
		}
		case __Center:
		{
			frmForm->Top = (recAux.Bottom - recAux.Top - frmForm->Height) / 2;
			break;
		}
		case __Bottom:
		{
			frmForm->Top = recAux.Bottom - frmForm->Height;
			break;
		}
	}
}

void Stew::_WindowManagement(HANDLE hndWindowHandle, Stew_WindowManagement cusAction)
{
	ShowWindowAsync(hndWindowHandle, cusAction);
}

void Stew::_SeparateString(UnicodeString Text, UnicodeString strSeparator, TStringList* stlDestiny)
{
	stlDestiny->Text = StringReplace(Text, strSeparator, L"\r\n", TReplaceFlags() << rfReplaceAll << rfIgnoreCase);
}

void Stew::_ListFolders(UnicodeString strFolder, TStrings* stsList)
{
	TSearchRec* srcRec = new TSearchRec;

	if (strFolder[strFolder.Length()] != '\\')
	{
		strFolder += '\\';
	}

	stsList->Clear();
	if (FindFirst(strFolder + '*', faAnyFile, *srcRec) == 0)
	{
		do
		{
			if (DirectoryExists(strFolder + srcRec->Name) && srcRec->Name != '.' && srcRec->Name != "..")
			{
				stsList->Add(srcRec->Name);
			}
		}
		while (FindNext(*srcRec) == 0);
		FindClose(*srcRec);
	}
	delete srcRec;
}

void Stew::_ListFiles(UnicodeString strStartFolder, UnicodeString strMask, TStrings* stsList, bool bolFullPath, bool bolSubFolders, bool bolClearList)
{
	TSearchRec* srcRec = new TSearchRec;

	if (strStartFolder[strStartFolder.Length()] != '\\')
	{
		strStartFolder += '\\';
	}

	if (bolClearList)
	{
		stsList->Clear();
	}
	if (FindFirst(strStartFolder + strMask, faAnyFile, *srcRec) == 0)
	{
		do
		{
			if (!DirectoryExists(strStartFolder + srcRec->Name) && srcRec->Name != '.' && srcRec->Name != ".." && stsList->IndexOf
				(bolFullPath ? strStartFolder + srcRec->Name : srcRec->Name) == -1)
			{
				stsList->Add(bolFullPath ? strStartFolder + srcRec->Name : srcRec->Name);
			}
		}
		while (FindNext(*srcRec) == 0);
		FindClose(*srcRec);
	}

	if (bolSubFolders)
	{
		TStringList* stlTempList = new TStringList;

		_ListFolders(strStartFolder, stlTempList);

		for (int i = 0; i < stlTempList->Count; i++)
		{
			_ListFiles(strStartFolder + stlTempList->Strings[i], strMask, stsList, bolFullPath, true, false);
		}
		stlTempList->Free();
	}
	delete srcRec;
}

bool Stew::_CheckInternet()
{
	typedef bool(WINAPI * ___InternetGetConnectedState)(LPDWORD lpdwFlags, ULONG dwReserved);
	___InternetGetConnectedState __InternetGetConnectedState;
	__InternetGetConnectedState = (___InternetGetConnectedState)GetProcAddress(LoadLibraryW(L"wininet.dll"), "InternetGetConnectedState");

	ULONG aux = 7;
	return __InternetGetConnectedState(&aux, 0);
}

bool Stew::_DownloadURL(UnicodeString URL, UnicodeString Target)
{
	bool Result = false;
	if (_CheckInternet())
	{
		try
		{
			/* TDownloadURL* DownloadURL = new TDownloadURL(NULL);
			DownloadURL->URL = URL;
			DownloadURL->Filename = Target;
			DownloadURL->ExecuteTarget(NULL);
			DownloadURL->Free(); */
			Result = true;
		}
		catch(...)
		{
		}
	}
	return Result;
}
/* ..:: END METHODS ::.. */
