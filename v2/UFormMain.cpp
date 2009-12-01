#include <vcl.h>
#include <stdio.h>
#pragma hdrstop
#include "UTranslate.cpp"
#include "UFormMain.h"
#pragma package(smart_init)
#pragma resource "*.dfm"

TFormMain* FormMain;

UnicodeString CustomGarenaPath = "", CurrentGarenaText, CurrentGarenaNick = "?";

int HackCount, read, CodeCavePosition, CodeCaveControl;

HANDLE CurrentGarenaHandle, CurrentCodeCaveHandle;

bool CheckNick;

TStringList* GarenaPIDList = new TStringList;
TStringList* GarenaPIDList2 = new TStringList;
TStringList* GarenaPIDList3 = new TStringList;

HackStructure* HackGroup[20];

bool Deploy = false;

const UnicodeString Title = "Hot Garena Tools", Version = "2.0",

ForumLink = "http://hotcheats.org/", DownloadLink = "http://downloads.hotcheats.org/", RegKey = "software\\Hot Cheats\\" + Title + "\\" + Version;

__fastcall TFormMain::TFormMain(TComponent* Owner) : TForm(Owner)
{
}

void __fastcall TFormMain::FormCreate(TObject* Sender)
{
	if (!Stew::_CreateMutex(Title + Version))
	{
		Application->Terminate();
	}
	Application->Title = Title + " " + Version;
	Caption = Title + " " + Version;
	lblTitle->Caption = Title + " " + Version;
	lblForumLink->Caption = ForumLink;
	CreateHacks();

	try
	{
		UnicodeString Configs = Stew::_RegReadString(HKEY_LOCAL_MACHINE, RegKey, "Config");
		CustomGarenaPath = Stew::_RegReadString(HKEY_LOCAL_MACHINE, RegKey, "CustomGarenaPath");
		UnicodeString NS = Stew::_RegReadString(HKEY_LOCAL_MACHINE, RegKey, "NameSpoofer");
		if (NS != "")
		{
			NS.SetLength(15);
			gbxSettings_edtNameSpoofer->Text = NS;
		}

		if (!FileExists(CustomGarenaPath))
		{
			char aux[MAX_PATH];
			GetWindowsDirectory(aux, MAX_PATH);
			CustomGarenaPath = "";
			if (FileExists((UnicodeString)aux[0] + ":\\Arquivos de Programas\\Garena\\Garena.exe"))
			{
				CustomGarenaPath = (UnicodeString)aux[0] + ":\\Arquivos de Programas\\Garena\\Garena.exe";
			}
			if (FileExists((UnicodeString)aux[0] + ":\\Program Files\\Garena\\Garena.exe"))
			{
				CustomGarenaPath = (UnicodeString)aux[0] + ":\\Program Files\\Garena\\Garena.exe";
			}
			Stew::_RegWriteString(HKEY_LOCAL_MACHINE, RegKey, "CustomGarenaPath", CustomGarenaPath, true, true);
		}
		gbxSettings_edtCustomGarenaPath->Text = CustomGarenaPath;
		ChangeLanguage(StrToInt(Configs[1]));
		gbxSettings_chbEnableHelp->Checked = StrToBool(Configs[2]);
		gbxSettings_chbEnableNameSpoofer->Checked = StrToBool(Configs[3]);
	}
	catch(...)
	{
		ChangeLanguage(0);
	}

	if (Deploy)
	{
		Height = lblUpdates->Top + 55;
		Button1->Visible = false;
	}
	Application->HintPause = 0;
	Application->HintHidePause = 30000;
	ShowHint = gbxSettings_chbEnableHelp->Checked;

	triMain->Icon = Application->Icon;
	triMain->Hint = Caption;
	Application->OnMinimize = HideToTray;

	Stew::_FormPosition(this, __Center, __Center);
}

void TFormMain::ChangeLanguage(int Language)
{
	rgpLanguage->ItemIndex = Language;

	lblUpdates->Caption = Translate[0][Language] + DownloadLink;
	gbxSelectGarena->Caption = Translate[1][Language];
	btnRunGarena->Caption = Translate[2][Language];
	gbxSettings->Caption = Translate[3][Language];
	gbxSettings_lblCustomGarenaPath->Caption = Translate[4][Language];
	gbxSettings_chbEnableNameSpoofer->Caption = Translate[5][Language];
	gbxHacks->Caption = Translate[6][Language];
	lblCredits->Caption = Translate[8][Language];
	gbxSettings_chbEnableHelp->Caption = Translate[9][Language];
	lblGarenaVersion->Caption = Translate[10][Language];

	gbxSettings_chbEnableHelp->Hint = TranslateHint[0][Language];
	lblStew->Hint = TranslateHint[1][Language];
	lblForumLink->Hint = TranslateHint[1][Language];
	lblUpdates->Hint = TranslateHint[2][Language];
	gbxSelectGarena_lblNick->Hint = TranslateHint[3][Language];
	gbxSelectGarena_cbbCurrentGarena->Hint = TranslateHint[4][Language];
	btnRunGarena->Hint = TranslateHint[5][Language];
	gbxSettings_edtCustomGarenaPath->Hint = TranslateHint[6][Language];
	lblGarenaVersion->Hint = TranslateHint[7][Language];
	gbxSettings_chbEnableNameSpoofer->Hint = TranslateHint[15][Language];
	gbxSettings_edtNameSpoofer->Hint = TranslateHint[16][Language];

	for (int i = 0; i <= HackCount - 1; i++)
	{
		HackGroup[i]->lblHack->Caption = Translate[HackGroup[i]->HackCaption][Language];
		HackGroup[i]->imgHack->Hint = TranslateHint[HackGroup[i]->HintNumber][Language];
	}

	SaveRegConfig();
}

void TFormMain::SaveRegConfig()
{
	Stew::_RegWriteString(HKEY_LOCAL_MACHINE, RegKey, "Config", IntToStr(rgpLanguage->ItemIndex) + IntToStr((int)gbxSettings_chbEnableHelp->Checked) + IntToStr
		((int)gbxSettings_chbEnableNameSpoofer->Checked), true, true);
	Stew::_RegWriteString(HKEY_LOCAL_MACHINE, RegKey, "NameSpoofer", gbxSettings_edtNameSpoofer->Text, true, true);
	if (FileExists(CustomGarenaPath) && ExtractFileName(CustomGarenaPath) == "Garena.exe")
	{
		Stew::_RegWriteString(HKEY_LOCAL_MACHINE, RegKey, "CustomGarenaPath", CustomGarenaPath, true, true);
	}
}

void TFormMain::AddHack(int HackCaption, int HintNumber, int const* FirstPointer, int PointerCount)
{
	HackGroup[HackCount] = new HackStructure;
	HackCount++;
	HackGroup[HackCount - 1]->FirstPointer = FirstPointer;
	HackGroup[HackCount - 1]->PointerCount = PointerCount;
	HackGroup[HackCount - 1]->HackCaption = HackCaption;
	HackGroup[HackCount - 1]->HintNumber = HintNumber;

	HackGroup[HackCount - 1]->lblHack = new TLabel(gbxHacks);
	HackGroup[HackCount - 1]->imgHack = new TImage(gbxHacks);

	HackGroup[HackCount - 1]->lblHack->Parent = gbxHacks;
	HackGroup[HackCount - 1]->imgHack->Parent = gbxHacks;

	HackGroup[HackCount - 1]->lblHack->Left = Stew::_Odd(HackCount) ? 41 : 154;
	HackGroup[HackCount - 1]->imgHack->Left = Stew::_Odd(HackCount) ? 18 : 131;

	HackGroup[HackCount - 1]->lblHack->Top = 21 + (23 * ((HackCount - 1) / 2));
	HackGroup[HackCount - 1]->imgHack->Top = 21 + (23 * ((HackCount - 1) / 2));

	HackGroup[HackCount - 1]->lblHack->Name = "gbxHacks_lbl" + IntToStr(HackCount - 1);
	HackGroup[HackCount - 1]->imgHack->Name = "gbxHacks_img" + IntToStr(HackCount - 1);

	HackGroup[HackCount - 1]->lblHack->Caption = Translate[HackCaption][rgpLanguage->ItemIndex];

	imlMain->GetBitmap(0, HackGroup[HackCount - 1]->imgHack->Picture->Bitmap);

	HackGroup[HackCount - 1]->imgHack->Width = 17;
	HackGroup[HackCount - 1]->imgHack->Height = 17;

	gbxHacks->Height = gbxHacks->Height + (Stew::_Odd(HackCount) ? 23 : 0);
	FormMain->Height = FormMain->Height + (Stew::_Odd(HackCount) ? 23 : 0);
	lblUpdates->Top = lblUpdates->Top + (Stew::_Odd(HackCount) ? 23 : 0);
	lblCredits->Top = lblCredits->Top + (Stew::_Odd(HackCount) ? 23 : 0);
	lblGarenaVersion->Top = lblGarenaVersion->Top + (Stew::_Odd(HackCount) ? 23 : 0);
}

void TFormMain::CreateHacks()
{
	AddHack(14, 8, PExperience, (sizeof(PExperience) / 4) / 3);
	AddHack(15, 9, PPingNumbers, (sizeof(PPingNumbers) / 4) / 3);
	AddHack(16, 10, PFloodChat, (sizeof(PFloodChat) / 4) / 3);
	AddHack(17, 11, PTraceLocation, (sizeof(PTraceLocation) / 4) / 3);
	AddHack(18, 12, PClanAlert, (sizeof(PClanAlert) / 4) / 3);
	AddHack(20, 14, PBypassHacks, (sizeof(PBypassHacks) / 4) / 3);
	AddHack(21, 17, PAlwaysPlaying, (sizeof(PAlwaysPlaying) / 4) / 3);
	AddHack(19, 13, POtherChanges, (sizeof(POtherChanges) / 4) / 3);
}

void __fastcall TFormMain::OpenForum(TObject* Sender)
{
	TLabel* aux = (TLabel*)Sender;
	ShellExecuteW(Handle, L"open", aux->Name == "lblUpdates" ? DownloadLink.c_str() : ForumLink.c_str(), NULL, NULL, 6);
}

void TFormMain::RefreshGarenaProcesses()
{
	HANDLE Snapshot;
	tagPROCESSENTRY32 Entry;
	GarenaPIDList3->Clear();

	Snapshot = CreateToolhelp32Snapshot(2, 0);
	Entry.dwSize = sizeof(Entry);
	Process32First(Snapshot, &Entry);
	do
	{
		if (UpperCase("Garena.exe") == UpperCase(Entry.szExeFile))
		{
			GarenaPIDList3->Add(Entry.th32ProcessID);
		}
	}
	while (Process32Next(Snapshot, &Entry));

	if (GarenaPIDList2->Text != GarenaPIDList3->Text)
	{
		GarenaPIDList2->Text = GarenaPIDList3->Text;
		HANDLE aux;
		int i = 0;
		while (true)
		{
			if (i == GarenaPIDList3->Count)
			{
				break;
			}
			Stew::_MemoryManagement(StrToInt(GarenaPIDList3->Strings[i]), aux);
			read = 0;
			ReadProcessMemory(aux, Pointer(PCodeCavePosition + 5), &read, 1, 0);
			CloseHandle(aux);
			if (read != 1)
			{
				GarenaPIDList3->Delete(i--);
			}
			i++;
		}
		if (gbxSelectGarena_cbbCurrentGarena->Items->Text != GarenaPIDList3->Text)
		{
			gbxSelectGarena_cbbCurrentGarena->Items->Text = GarenaPIDList3->Text;
			GarenaPIDList->Text = GarenaPIDList3->Text;
			gbxSelectGarena_cbbCurrentGarena->ItemIndex = gbxSelectGarena_cbbCurrentGarena->Items->IndexOf(CurrentGarenaText);
			CheckNick = true;
		}
	}
}

void __fastcall TFormMain::tmrMainTimer(TObject* Sender)
{
	try
	{
		if (Stew::_ActiveCaption() != Caption)
		{
			return;
		}
		RefreshGarenaProcesses();
		if (CheckNick)
		{
			read = 0;
			ReadProcessMemory(CurrentGarenaHandle, Pointer(PCodeCavePosition), &read, 4, 0);
			if (read == 0 || CurrentGarenaHandle == NULL)
			{
				CurrentGarenaNick = "?";
				CheckNick = false;
			}
			else
			{
				int aux1 = read + 0x400 - 0x1E;
				int aux2 = 0;
				ReadProcessMemory(CurrentGarenaHandle, Pointer(aux1), &aux2, 4, 0);
				if (aux2 == 0)
				{
					CurrentGarenaNick = "?";
				}
				else
				{
					char aux3[15] = "";
					ReadProcessMemory(CurrentGarenaHandle, Pointer(aux2), aux3, 15, 0);
					if (aux3 == "")
					{
						CurrentGarenaNick = "?";
					}
					else
					{
						CurrentGarenaNick = aux3;
						CheckNick = false;
					}
				}
			}
			gbxSelectGarena_lblNick->Caption = "Nick: " + CurrentGarenaNick;
		}
	}
	catch(...)
	{
	}
}

void __fastcall TFormMain::rgpLanguageClick(TObject* Sender)
{
	ChangeLanguage(rgpLanguage->ItemIndex);
}

void __fastcall TFormMain::gbxSelectGarena_cbbCurrentGarenaChange(TObject* Sender)
{
	CloseHandle(CurrentGarenaHandle);
	CurrentGarenaHandle = NULL;
	CurrentGarenaText = gbxSelectGarena_cbbCurrentGarena->Items->Strings[gbxSelectGarena_cbbCurrentGarena->ItemIndex];
	CheckNick = true;
	if (CurrentGarenaText == "")
	{
		return;
	}
	Stew::_MemoryManagement(StrToInt(GarenaPIDList->Strings[gbxSelectGarena_cbbCurrentGarena->ItemIndex]), CurrentGarenaHandle);
}

void __fastcall TFormMain::FormClose(TObject* Sender, TCloseAction& Action)
{
	if (Deploy)
	{
		OpenForum(lblForumLink);
	}
}

void __fastcall TFormMain::gbxSettings_chbEnableHelpClick(TObject* Sender)
{
	ShowHint = gbxSettings_chbEnableHelp->Checked;
	SaveRegConfig();
}

void __fastcall TFormMain::btnRunGarenaClick(TObject* Sender)
{
	if (gbxSettings_chbEnableNameSpoofer->Checked && gbxSettings_edtNameSpoofer->Text == "")
	{
		MessageBoxW(Handle, Translate[7][rgpLanguage->ItemIndex].c_str(), Translate[11][rgpLanguage->ItemIndex].c_str(), 16);
		return;
	}

	STARTUPINFOW SI;
	PROCESS_INFORMATION PI;

	ZeroMemory(&SI, sizeof(SI));

	CreateProcessW(NULL, CustomGarenaPath.c_str(), NULL, NULL, false, CREATE_SUSPENDED, NULL, NULL, &SI, &PI);
	HANDLE aux;
	Stew::_MemoryManagement(PI.dwProcessId, aux);
	read = 0;
	ReadProcessMemory(aux, Pointer(PPolygamy[0]), &read, 1, 0);
	if (read != PPolygamy[1])
	{
		TerminateProcess(OpenProcess(1, false, PI.dwProcessId), 0);
		MessageBoxW(Handle, Translate[12][rgpLanguage->ItemIndex].c_str(), Translate[11][rgpLanguage->ItemIndex].c_str(), 16);
		return;
	}
	for (UINT i = 0; i < (sizeof(PPolygamy) / 4) / 3; i++)
	{
		WriteProcessMemory(aux, Pointer(PPolygamy[i * 3]), &PPolygamy[2 + i * 3], 1, 0);
	}
	for (int j = 0; j <= HackCount - 1; j++)
	{
		for (int i = 0; i < HackGroup[j]->PointerCount; i++)
		{
			WriteProcessMemory(aux, Pointer(*((PINT)HackGroup[j]->FirstPointer + (i * 3))), ((PINT)HackGroup[j]->FirstPointer + 2 + (i * 3)), 1, 0);
		}
	}

	CodeCavePosition = (int)VirtualAllocEx(aux, NULL, 0x1000, 4096, 4);
	WriteProcessMemory(aux, Pointer(PCodeCavePosition), &CodeCavePosition, 4, 0);
	int xxx = 1;
	WriteProcessMemory(aux, Pointer(PCodeCavePosition + 5), &xxx, 1, 0);

	NullGEngine(aux);
	NameSpoofer(aux);

	ResumeThread(PI.hThread);

	/*
	WideString downpage = DownloadLink;
	//StringToWideChar(DownloadLink, downpage.c_bstr(), 100);
	read = 0;
	ReadProcessMemory(aux, Pointer(PHomePage), &read, 4, 0);
	DWORD OldProtect;
	//VirtualProtectEx(aux, Pointer(read + PHomePageOffset), 200, PAGE_EXECUTE_READWRITE, &OldProtect);
	//WriteProcessMemory(aux, Pointer(read + PHomePageOffset), downpage, downpage.Length() * 2, 0);
	WriteProcessMemory(aux, Pointer(0x70D758), downpage, downpage.Length() * 2, 0);
	 */

	CloseHandle(aux);
}

void __fastcall TFormMain::gbxSettings_chbEnableNameSpooferClick(TObject* Sender)
{
	gbxSettings_edtNameSpoofer->Enabled = gbxSettings_chbEnableNameSpoofer->Checked;
	gbxSettings_lblNameSpoofer->Font->Style = TFontStyles(gbxSettings_chbEnableNameSpoofer->Checked ? 1 : 0);
	SaveRegConfig();
}

void __fastcall TFormMain::gbxSettings_edtNameSpooferChange(TObject* Sender)
{
	SaveRegConfig();
}

void __fastcall TFormMain::gbxSettings_edtCustomGarenaPathChange(TObject* Sender)
{
	if (gbxSelectGarena_cbbCurrentGarena->Text == "")
	{
		CurrentGarenaHandle = NULL;
	}
	if (CustomGarenaPath != gbxSettings_edtCustomGarenaPath->Text)
	{
		CustomGarenaPath = gbxSettings_edtCustomGarenaPath->Text;
	}
	btnRunGarena->Enabled = ExtractFileName(CustomGarenaPath) == "Garena.exe" && FileExists(CustomGarenaPath);
	gbxSettings_edtCustomGarenaPath->Font->Color = btnRunGarena->Enabled ? clGreen : clRed;
	if (btnRunGarena->Enabled)
	{
		SaveRegConfig();
	}
}

void __fastcall TFormMain::Button1Click(TObject* Sender)
{
	HANDLE hnd;
	Stew::_MemoryManagement(Stew::_GetPID("Garena.exe"), hnd);
	read = 0;
	ReadProcessMemory(hnd, Pointer(PCodeCavePosition), &read, 4, 0);
	if (read == 0)
	{
		CodeCavePosition = (int)VirtualAllocEx(hnd, NULL, 0x1000, 4096, 4);
		WriteProcessMemory(hnd, Pointer(PCodeCavePosition), &CodeCavePosition, 4, 0);
	}
	else
	{
		CodeCavePosition = read;
	}

	TStringList* test = new TStringList;

	for (int j = 0; j <= HackCount - 1; j++)
	{
		for (int i = 0; i < HackGroup[j]->PointerCount; i++)
		{
			PULONG old;
			VirtualProtectEx(hnd, Pointer(*((PINT)HackGroup[j]->FirstPointer + (i * 3))), 1, PAGE_EXECUTE_READWRITE, old);
			if (!WriteProcessMemory(hnd, Pointer(*((PINT)HackGroup[j]->FirstPointer + (i * 3))), ((PINT)HackGroup[j]->FirstPointer + 2 + (i * 3)), 1, 0))
			{
				test->Add(IntToHex(*((PINT)HackGroup[j]->FirstPointer + (i * 3)), 8) + " - " + IntToStr((int)GetLastError()));
			}
		}
	}

	ShowMessage(test->Text);

	NullGEngine(hnd);
	NameSpoofer(hnd);
	CloseHandle(hnd);
}

void TFormMain::CCWriteLine(int Value, int Size)
{
	WriteProcessMemory(CurrentCodeCaveHandle, Pointer(CodeCavePosition + CodeCaveControl), &Value, Size, 0);
	CodeCaveControl = CodeCaveControl + Size;
}

void TFormMain::NullGEngine(HANDLE CGH)
{
	CurrentCodeCaveHandle = CGH;
	CodeCaveControl = 0;
	int aux, PlstrcatW = CodeCavePosition + 0x57, PDllCmp = CodeCavePosition + 0x6f;

	UnicodeString DllCmpName = "\\plugins\\ui\\GEngine.dll";
	AnsiString SlstrcatW = "lstrcatW";

	// PJmpGateGEngine
	aux = 0xE9;
	WriteProcessMemory(CurrentCodeCaveHandle, Pointer(PJmpGateGEngine), &aux, 1, 0);
	aux = CodeCavePosition - PJmpGateGEngine - 5 + CodeCaveControl;
	WriteProcessMemory(CurrentCodeCaveHandle, Pointer(PJmpGateGEngine + 1), &aux, 4, 0);

	// PUSHAD
	CCWriteLine(0x60, 1);

	// PUSH [PGarenaFolder]
	CCWriteLine(0x35FF, 2);
	CCWriteLine(PGarenaFolder, 4);

	// MOV EBX, CodeCavePosition + B0
	CCWriteLine(0xBB, 1);
	CCWriteLine(CodeCavePosition + 0xB0, 4);

	// PUSH EBX
	CCWriteLine(0x53, 1);

	// CALL lstrcpyW
	CCWriteLine(0x15FF, 2);
	CCWriteLine(PlstrcpyW, 4);

	// PUSH "kernel32.dll"
	CCWriteLine(0x68, 1);
	CCWriteLine(PKernel32str, 4);

	// CALL GetModuleHandleA
	CCWriteLine(0x15FF, 2);
	CCWriteLine(PGetModuleHandleA, 4);

	// PUSH PlstrcatW2
	CCWriteLine(0x68, 1);
	CCWriteLine(PlstrcatW, 4);

	// PUSH EAX
	CCWriteLine(0x50, 1);

	// CALL GetProcAddress
	CCWriteLine(0x15FF, 2);
	CCWriteLine(PGetProcAddress, 4);

	// PUSH PDllCmp
	CCWriteLine(0x68, 1);
	CCWriteLine(PDllCmp, 4);

	// PUSH EBX
	CCWriteLine(0x53, 1);

	// CALL EAX
	CCWriteLine(0xD0FF, 2);

	// PUSH EBX
	CCWriteLine(0x53, 1);

	// PUSH EBP
	CCWriteLine(0x55, 1);

	// CALL lstrcmpW
	CCWriteLine(0x15FF, 2);
	CCWriteLine(PlstrcmpW, 4);

	// JNZ 0B
	CCWriteLine(0x0B75, 2);

	// POPAD / MOV ESI, EAX / ADD ESP, 4
	CCWriteLine(0x83F08B61, 4);
	CCWriteLine(0x04C4, 2);

	// JMP PRetGateGEngine2
	CCWriteLine(0xE9, 1);
	CCWriteLine(PRetGateGEngine2 - CodeCavePosition - CodeCaveControl - 4, 4);

	// POPAD / MOV ESI, EAX / ADD ESP, 4
	CCWriteLine(0x83F08B61, 4);
	CCWriteLine(0x04C4, 2);

	// JMP PRetGateGEngine
	CCWriteLine(0xE9, 1);
	CCWriteLine(PRetGateGEngine - CodeCavePosition - CodeCaveControl - 4, 4);

	// String lstrcatW
	WriteProcessMemory(CurrentCodeCaveHandle, Pointer(PlstrcatW), SlstrcatW.c_str(), SlstrcatW.Length(), 0);

	// String dllcmpname
	WriteProcessMemory(CurrentCodeCaveHandle, Pointer(PDllCmp), DllCmpName.c_str(), DllCmpName.Length() * 2, 0);
}

void TFormMain::NameSpoofer(HANDLE CGH)
{
	CurrentCodeCaveHandle = CGH;
	CodeCaveControl = 0x400;
	int aux;

	// PJmpGateNS
	aux = 0xE9;
	WriteProcessMemory(CurrentCodeCaveHandle, Pointer(PJmpGateNS), &aux, 1, 0);
	aux = CodeCavePosition - PJmpGateNS - 5 + CodeCaveControl;
	WriteProcessMemory(CurrentCodeCaveHandle, Pointer(PJmpGateNS + 1), &aux, 4, 0);
	aux = 0x90;
	WriteProcessMemory(CurrentCodeCaveHandle, Pointer(PJmpGateNS + 5), &aux, 1, 0);

	if (gbxSettings_chbEnableNameSpoofer->Checked)
	{
		// String gbxSettings_edtNameSpoofer->Text
		WriteProcessMemory(CurrentCodeCaveHandle, Pointer(CodeCavePosition + CodeCaveControl - 16), gbxSettings_edtNameSpoofer->Text.c_str(),
			gbxSettings_edtNameSpoofer->Text.Length(), 0);

		// MOV EDX, CodeCavePosition + CodeCaveControl - 16 - 1
		CCWriteLine(0xBA, 1);
		CCWriteLine(CodeCavePosition + CodeCaveControl - 16 - 1, 4);
	}
	else
	{
		// LEA EDX,[EDI+4]
		CCWriteLine(0x04578D, 3);
	}

	// ADD EAX, 4
	CCWriteLine(0x04C083, 3);

	// MOV [CodeCavePosition + CodeCaveControl - 37 - (gbxSettings_chbEnableNameSpoofer->Checked ? 2 : 0)],EAX
	CCWriteLine(0xA3, 1);
	CCWriteLine(CodeCavePosition + CodeCaveControl - 37 - (gbxSettings_chbEnableNameSpoofer->Checked ? 2 : 0), 4);

	// JMP PRetGateNS
	CCWriteLine(0xE9, 1);
	CCWriteLine(PRetGateNS - CodeCavePosition - CodeCaveControl - 5 + 1, 4);
}

void __fastcall TFormMain::triMainClick(TObject* Sender)
{
	Show();
	Stew::_WindowManagement(Handle, __Restore);
}

void __fastcall TFormMain::HideToTray(TObject* Sender)
{
	Hide();
}

void __fastcall TFormMain::lblCreditsClick(TObject* Sender)
{
	ShowMessage(Translate[22][rgpLanguage->ItemIndex]);
}
