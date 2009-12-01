#ifndef StewH
#define StewH

#ifdef Deploy
#pragma resource "admin.res"
#endif

#include <SysUtils.hpp>
//#include <Classes.hpp>
#include <Forms.hpp>
#include <TlHelp32.hpp>
//#include <ExtActns.hpp>
//#include <vector>

//using std::vector;

typedef enum
{
	__System32, __WINDOWS, __Temp, __WinDrive
}Stew_GetDirectory;

typedef enum
{
	__Left, __Center, __Right, __Top, __Bottom
}Stew_FormPosition;

typedef enum
{
	__Hide, __Show, __Minimize, __Maximize, __Restore
}Stew_WindowManagement;

class Stew
{
	private:

	public:
	static bool _CreateMutex(UnicodeString Name);
	static UnicodeString _RegReadString(HKEY Key, UnicodeString KeyName, UnicodeString Value);
	static bool _RegWriteString(HKEY Key, UnicodeString KeyName, UnicodeString Value, UnicodeString Text, bool bolCanCreateKey,
		bool bolCanOverrideValue);
	static void _DeleteShellExtension(UnicodeString strExtensionWithDot);
	static void _AddShellExtension(UnicodeString strExtensionWithDot, UnicodeString strShellCaption, UnicodeString strExePath, UnicodeString strIconPath);
	static bool _RegDeleteKey(HKEY Key, UnicodeString KeyName);
	static bool _RegDeleteValue(HKEY Key, UnicodeString KeyName, UnicodeString Value);
	static bool _RegValueExists(HKEY Key, UnicodeString KeyName, UnicodeString Value);
	static bool _RegCreateKey(HKEY Key, UnicodeString KeyName);
	static void _MemoryManagement(int intPID, HANDLE& hndProcessHandle);
	static int _GetPID(UnicodeString strProcessName);
	static void _DebugPrivilege();
	static bool _Odd(int intNumber);
	static UINT _SaveProcedure(Pointer ptrProcedure, Pointer ptrDestiny);
	static bool _HookProcedure(UnicodeString strTargetDLL, UnicodeString strTargetName, Pointer ptrNewProcedure, Pointer& ptrSave);
	static bool _UnhookProcedure(Pointer ptrSave);
	static UINT _CodeSize(Pointer ptrCode);
	static UINT _ProcedureSize(Pointer ptrProcedure);
	static bool _InjectDLL(int intPID, UnicodeString strDLLFullPath);
	static void _GetProcessModules(int intPID, TStringList* stlModulesList);
	static void _ExtractResource(UnicodeString Name, PWideChar wchResType, UnicodeString strPath);
	static UnicodeString _DissectString(int intPosition, UnicodeString strSeparator, UnicodeString Text);
	static UnicodeString _GetDirectory(Stew_GetDirectory cusDirectory);
	static void _FormPosition(TForm* frmForm, Stew_FormPosition cusHorizontal, Stew_FormPosition cusVertical);
	static void _WindowManagement(HANDLE hndWindowHandle, Stew_WindowManagement cusAction);
	static void _SeparateString(UnicodeString Text, UnicodeString strSeparator, TStringList* stlDestiny);
	static void _ListFolders(UnicodeString strFolder, TStrings* stsList);
	static void _ListFiles(UnicodeString strStartFolder, UnicodeString strMask, TStrings* stsList, bool bolFullPath, bool bolSubFolders, bool bolClearList);
	static bool _CheckInternet();
	static bool _DownloadURL(UnicodeString URL, UnicodeString Target);
};

#endif
