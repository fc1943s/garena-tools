#include <vcl.h>
#include <stdio.h>
#pragma hdrstop
#include "UFormMain.h"
#include "UPointers.cpp"
#include "Stew.cpp"
#pragma package(smart_init)
#pragma resource "*.dfm"

TFormMain* FormMain;

UnicodeString CustomGarenaPath = "", CurrentGarenaText;

int HackCount, read, CurrentGarenaID, rsrs;

bool CanClickHacks, CheckID;

HANDLE CurrentGarenaHandle;

TStringList* GarenaPIDList = new TStringList;
TStringList* GarenaIDList = new TStringList;
TStringList* GarenaPIDList2 = new TStringList;
TStringList* GarenaPIDList3 = new TStringList;

HackStructure* HackGroup[20];

bool Deploy = false;

const UnicodeString Title = "Hot Garena Tools", Version = "1.0",

ForumLink = "http://hotcheats.org/", DownloadLink = "http://downloads.hotcheats.org/", RegKey = "software\\Hot Cheats\\" + Title + "\\" + Version, Translate[][2] =
{
	"Atualizações em ", "Updates in ", // 0
	"Selecione o Garena", "Select Garena", // 1
	"Executar Garena", "Execute Garena", // 2
	"Configurações", "Settings", // 3
	"Caminho do Garena.exe:", "Path of Garena.exe:", // 4

	"Legenda", "Legend", // 5
	"Indisponível", "Unavailable", // 6
	"Inativo", "Disabled", // 7
	"Ativo", "Enabled", // 8

	"Ativar ajuda", "Enable help", // 9
	"Feito para Garena 3.0.0.1593", "Works only in Garena 3.0.0.1593", // 10
	"Erro", "Error", // 11
	"Versão do Garena inválida.", "Invalid Garena version.", // 12
	"ID da conta: ", "Account ID: ", // 13

	"Experiencia", "Experience", // 14
	"Ping em Números", "Ping in Numbers", // 15
	"Flood no Chat", "Flood in Chat", // 16
	"Funções de Admin", "Admin Functions", // 17
	"Alerta de Clan", "Clan Alert", // 18
	"Mensagens/Alertas", "Messages/Alerts", // 19
	"Permitir Hacks", "Bypass Hacks" // 20
}, TranslateHint[][2] =
{ // 0
	"Marque esta opção se você deseja ajuda\r\nquando parar o mouse em cima de algo.", "Check this box if you want help\r\nwhen stop the mouse above something.",
	// 1
	"Clique aqui para visitar o fórum oficial.", "Click here to visit the official forum.",
	// 2
	"Clique aqui para visitar a página de downloads.", "Click here to visit the downloads page.",
	// 3
	"ID da sua conta no Garena.\r\n\r\nSe a ID é zero, você não está logado.", "Your account ID in Garena.\r\n\r\nIf the ID is zero, you aren't logged.",
	// 4
	"Selecione aqui o Garena desejado.\r\n\r\nO Garena só será exibido aqui se ele\r\n foi executado pelo botão \"Executar Garena\".",
	"Select here the desired Garena.\r\n\r\nThe Garena will appear here only if he was\r\nexecuted by button \"Execute Garena\".",
	// 5
	"Clique aqui para executar uma instância do Garena.\r\n\r\nExecutando o Garena por este botão, você poderá\r\nabrir mais de um Garena ao mesmo tempo.\r\n\r\nPara este botão funcionar corretamente, corrija\r\no \"Caminho do Garena.exe\" em Configurações.\r\n\r\nO Garena só será executado se ele estiver na\r\nversão citada na parte de baixo do programa.", "Click here to execute one instance of Garena.\r\n\r\nExecuting the Garena by this button, you could\r\nopen more than one Garena at the same time.\r\n\r\nFor this button works correctly, correct\r\nthe \"Path of Garena.exe\" in Settings.\r\n\r\nThe Garena will only be executed if he is in\r\nthe version said in the bottom of the program.",
	// 6
	"Configure aqui o caminho do Garena.exe na\r\nversão citada na parte de baixo do programa.\r\n\r\nExemplo:\r\n\"C:\\Arquivos de Programas\\Garena\\Garena.exe\""
		, "Correct here the path of Garena.exe in\r\nversion said in the bottom of the program.\r\n\r\nExample:\r\n\"C:\\Program Files\\Garena\\Garena.exe\"",
	// 7
	"Este programa só irá funcionar no Garena com a versão citada aqui.\r\n\r\nSe sua versão for menor que esta, visite www.garena.com para atualizar seu Garena.\r\n\r\nSe sua versão for maior que esta, aguarde alguns\r\ndias até que a proxima versão do hack esteja terminada.\r\n\r\nPara saber a versão do seu Garena,\r\nvisite \"http://img399.imageshack.us/img399/4233/92330279pf4.png\""
		, "This program will works only in Garena with version said here.\r\n\r\nIf your version is lower than this, visit www.garena.com to update your Garena.\r\n\r\nIf your version is greater than this, wait a few days until the next version of hack is done.\r\n\r\nTo know the version of your Garena,\r\nvisit \"http://img399.imageshack.us/img399/4233/92330279pf4.png\"",
	// 8
	"Com este hack você evoluirá sua conta mais rapido.\r\n\r\nVocê não precisa estar em algum jogo, só\r\nprecisa estar online no Garena, e DENTRO DE UMA SALA.\r\n\r\nVocê ganhará em média 50 de experiência a cada 15 minutos."
		, "With this hack you will up your account more fast.\r\n\r\nYou don't need be in any game, need\r\nonly be online in Garena, and WITHIN A ROOM.\r\n\r\nYou will gain on average 50 experience every 15 minutes.",
	// 9
	"Exibe os pings por números invés de barras.", "Show the pings by numbers instead of bars.",
	// 10
	"Permite você floodar no chat.", "Allow you flood in chat.",
	// 11
	"Libera algumas funções de administrador (nem todas funcionam).", "Unlock some admin functions (not all works).",
	// 12
	"Permite membros normais usarem o alerta de clan.", "Allow normal members use clan alert.",
	// 13
	"Não exibe algumas mensagens e alertas, como 5 segundos de\r\nespera, sala cheia, level insuficiente, etc.",
	"Don't show some messages and alerts, like 5 seconds of wait, full room, insufficient level, and more.",
	// 14
	"Com este hack, o Garena não detecta\r\nALGUNS hacks, como map hack, etc.\r\n\r\nÉ recomendado testar com uma conta fake\r\nantes, para não correr risco de ban.\r\n\r\nNÃO me responsabilizo por contas banidas.", "With this hack, the Garena not detects SOME hacks, like map hack, and more.\r\n\r\nIs recommended test with an account fake before, for no risk of ban.\r\n\r\nIf you take ban, it is their guilt."
};

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
	}
	catch(...)
	{
		ChangeLanguage(0);
	}

	imlMain->GetBitmap(0, gbxLegend_imgUnavailable->Picture->Bitmap);
	imlMain->GetBitmap(1, gbxLegend_imgDisabled->Picture->Bitmap);
	imlMain->GetBitmap(2, gbxLegend_imgEnabled->Picture->Bitmap);

	Height = lblUpdates->Top + 55;
	Application->HintPause = 0;
	Application->HintHidePause = 30000;
	ShowHint = gbxSettings_chbEnableHelp->Checked;

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
	gbxLegend->Caption = Translate[5][Language];
	gbxLegend_lblUnavailable->Caption = Translate[6][Language];
	gbxLegend_lblDisabled->Caption = Translate[7][Language];
	gbxLegend_lblEnabled->Caption = Translate[8][Language];
	gbxSettings_chbEnableHelp->Caption = Translate[9][Language];
	lblGarenaVersion->Caption = Translate[10][Language];
	gbxSelectGarena_lblAccountID->Caption = Translate[13][Language] + CurrentGarenaID;

	gbxSettings_chbEnableHelp->Hint = TranslateHint[0][Language];
	lblStew->Hint = TranslateHint[1][Language];
	lblForumLink->Hint = TranslateHint[1][Language];
	lblUpdates->Hint = TranslateHint[2][Language];
	gbxSelectGarena_lblAccountID->Hint = TranslateHint[3][Language];
	gbxSelectGarena_cbbCurrentGarena->Hint = TranslateHint[4][Language];
	btnRunGarena->Hint = TranslateHint[5][Language];
	gbxSettings_edtCustomGarenaPath->Hint = TranslateHint[6][Language];
	lblGarenaVersion->Hint = TranslateHint[7][Language];

	for (int i = 0; i <= HackCount - 1; i++)
	{
		HackGroup[i]->lblHack->Caption = Translate[HackGroup[i]->HackCaption][Language];
		HackGroup[i]->imgHack->Hint = TranslateHint[HackGroup[i]->HintNumber][Language];
	}

	SaveRegConfig();
}

void TFormMain::SaveRegConfig()
{
	Stew::_RegWriteString(HKEY_LOCAL_MACHINE, RegKey, "Config", IntToStr(rgpLanguage->ItemIndex) + IntToStr((int)gbxSettings_chbEnableHelp->Checked), true, true);
	if (FileExists(CustomGarenaPath) && ExtractFileName(CustomGarenaPath) == "Garena.exe")
	{
		Stew::_RegWriteString(HKEY_LOCAL_MACHINE, RegKey, "CustomGarenaPath", CustomGarenaPath, true, true);
	}
}

void TFormMain::AddHack(UnicodeString HackName, int HackCaption, int HintNumber, int const* FirstPointer, int PointerCount)
{
	HackGroup[HackCount] = new HackStructure;
	HackCount++;
	HackGroup[HackCount - 1]->HackName = HackName;
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
	HackGroup[HackCount - 1]->imgHack->OnClick = imgHackClick;

	gbxHacks->Height = gbxHacks->Height + (Stew::_Odd(HackCount) ? 23 : 0);
	FormMain->Height = FormMain->Height + (Stew::_Odd(HackCount) ? 23 : 0);
	lblUpdates->Top = lblUpdates->Top + (Stew::_Odd(HackCount) ? 23 : 0);
	lblGarenaVersion->Top = lblGarenaVersion->Top + (Stew::_Odd(HackCount) ? 23 : 0);
}

void TFormMain::CreateHacks()
{
	AddHack("Experience", 14, 8, PExperience, (sizeof(PExperience) / 4) / 3);
	AddHack("PingNumbers", 15, 9, PPingNumbers, (sizeof(PPingNumbers) / 4) / 3);
	AddHack("FloodChat", 16, 10, PFloodChat, (sizeof(PFloodChat) / 4) / 3);
	AddHack("AdminFunctions", 17, 11, PAdminFunctions, (sizeof(PAdminFunctions) / 4) / 3);
	AddHack("ClanAlert", 18, 12, PClanAlert, (sizeof(PClanAlert) / 4) / 3);
	AddHack("MessagesAlerts", 19, 13, PMessagesAlerts, (sizeof(PMessagesAlerts) / 4) / 3);
	AddHack("BypassHacks", 20, 14, PBypassHacks, (sizeof(PBypassHacks) / 4) / 3);
}

void __fastcall TFormMain::imgHackClick(TObject* Sender)
{
	TImage* aux = (TImage*)Sender;
	int HackNumber = StrToInt(aux->Name[aux->Name.Length()]);
	if (!CanClickHacks || HackGroup[HackNumber]->State == 0)
	{
		return;
	}
	for (int i = 0; i < HackGroup[HackNumber]->PointerCount; i++)
	{
		WriteProcessMemory(CurrentGarenaHandle, Pointer(*((PINT)HackGroup[HackNumber]->FirstPointer + (i * 3))),
			((PINT)HackGroup[HackNumber]->FirstPointer + (HackGroup[HackNumber]->State == 2 ? 1 : 2) + (i * 3)), 1, 0);
	}
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

	if (GarenaPIDList2->Text != GarenaPIDList3->Text || CheckID)
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
			ReadProcessMemory(aux, Pointer(PPolygamy[0]), &read, 1, 0);
			CloseHandle(aux);
			if (!((read == PPolygamy[1]) || (read == PPolygamy[2])))
			{
				GarenaPIDList3->Delete(i--);
			}
			i++;
		}
		if (gbxSelectGarena_cbbCurrentGarena->Items->Text != GarenaPIDList3->Text)
		{
			gbxSelectGarena_cbbCurrentGarena->Items->Text = GarenaPIDList3->Text;
			GarenaPIDList->Text = GarenaPIDList3->Text;
			CheckID = true;
			gbxSelectGarena_cbbCurrentGarena->ItemIndex = gbxSelectGarena_cbbCurrentGarena->Items->IndexOf(CurrentGarenaText);
		}
		if (CheckID)
		{
			CheckID = false;
			GarenaIDList->Text = GarenaPIDList->Text;
			for (int i = 0; i <= GarenaPIDList->Count - 1; i++)
			{
				Stew::_MemoryManagement(StrToInt(GarenaPIDList->Strings[i]), aux);
				read = 0;
				ReadProcessMemory(aux, (Pointer)PAccountID, &read, 8, 0);
				CloseHandle(aux);
				if (read == 0)
				{
					CheckID = true;
				}
				GarenaIDList->Strings[i] = IntToStr(read);
			}
			CurrentGarenaID = gbxSelectGarena_cbbCurrentGarena->ItemIndex == -1 ? 0 : StrToInt(GarenaIDList->Strings[gbxSelectGarena_cbbCurrentGarena->ItemIndex]);
			gbxSelectGarena_lblAccountID->Caption = Translate[13][rgpLanguage->ItemIndex] + CurrentGarenaID;
		}
	}
}

void TFormMain::ChangeHackState(int HackNumber, int State)
{
	if (HackGroup[HackNumber]->State == State)
	{
		return;
	}
	HackGroup[HackNumber]->State = State;
	imlMain->GetBitmap(State, HackGroup[HackNumber]->imgHack->Picture->Bitmap);
	HackGroup[HackNumber]->imgHack->Refresh();
}

void __fastcall TFormMain::tmrMainTimer(TObject* Sender)
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
	CanClickHacks = CurrentGarenaHandle != NULL;
	for (int i = 0; i <= HackCount - 1; i++)
	{
		HackGroup[i]->imgHack->Cursor = CanClickHacks && HackGroup[i]->State != 0 ? crHandPoint : crDefault;
	}
	RefreshGarenaProcesses();

	for (int i = 0; i <= HackCount - 1; i++)
	{
		read = 0;
		CurrentGarenaHandle == NULL ? read = -1 : ReadProcessMemory(CurrentGarenaHandle, Pointer(*HackGroup[i]->FirstPointer), &read, 1, 0);
		ChangeHackState(i, (read == *((PINT)HackGroup[i]->FirstPointer + 1)) || (read == *((PINT)HackGroup[i]->FirstPointer + 2)) ? read == *
			((PINT)HackGroup[i]->FirstPointer + 1) ? 1 : 2 : 0);
	}
}

void __fastcall TFormMain::rgpLanguageClick(TObject* Sender)
{
	ChangeLanguage(rgpLanguage->ItemIndex);
}

void __fastcall TFormMain::btnRunGarenaClick(TObject* Sender)
{
	STARTUPINFOW SI;
	PROCESS_INFORMATION PI;

	ZeroMemory(&SI, sizeof(SI));

	CreateProcessW(NULL, CustomGarenaPath.c_str(), NULL, NULL, false, CREATE_SUSPENDED, NULL, NULL, &SI, &PI);
	HANDLE aux;
	Stew::_MemoryManagement(Stew::_GetPID("Garena.exe"), aux);
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
	for (UINT i = 0; i < (sizeof(PBypassOpenProcess) / 4) / 3; i++)
	{
		WriteProcessMemory(aux, Pointer(PBypassOpenProcess[i * 3]), &PBypassOpenProcess[2 + i * 3], 1, 0);
	}
	for (int j = 0; j <= HackCount - 1; j++)
	{
		for (int i = 0; i < HackGroup[j]->PointerCount; i++)
		{
			WriteProcessMemory(aux, Pointer(*((PINT)HackGroup[j]->FirstPointer + (i * 3))), ((PINT)HackGroup[j]->FirstPointer + 2 + (i * 3)), 1, 0);
		}
	}

	/*
	for(UINT i = 0; i < (sizeof(UnknowN1) / 4) / 3; i++)
	WriteProcessMemory(aux, Pointer(UnknowN1[i * 3]), &UnknowN1[2 + i * 3], 1, 0);
	for(UINT i = 0; i < (sizeof(UnknowN2) / 4) / 3; i++)
	WriteProcessMemory(aux, Pointer(UnknowN2[i * 3]), &UnknowN2[2 + i * 3], 1, 0);
	for(UINT i = 0; i < (sizeof(UnknowN3) / 4) / 3; i++)
	WriteProcessMemory(aux, Pointer(UnknowN3[i * 3]), &UnknowN3[2 + i * 3], 1, 0);
	/*
	for(UINT i = 0; i < (sizeof(UnknowN4) / 4) / 3; i++)
	WriteProcessMemory(aux, Pointer(UnknowN4[i * 3]), &UnknowN4[2 + i * 3], 1, 0);
	for(UINT i = 0; i < (sizeof(UnknowN5) / 4) / 3; i++)
	WriteProcessMemory(aux, Pointer(UnknowN5[i * 3]), &UnknowN5[2 + i * 3], 1, 0);
	for(UINT i = 0; i < (sizeof(UnknowN6) / 4) / 3; i++)
	WriteProcessMemory(aux, Pointer(UnknowN6[i * 3]), &UnknowN6[2 + i * 3], 1, 0);
	 */

	ResumeThread(PI.hThread);
}

void __fastcall TFormMain::gbxSelectGarena_cbbCurrentGarenaChange(TObject* Sender)
{
	CloseHandle(CurrentGarenaHandle);
	CurrentGarenaHandle = NULL;
	CurrentGarenaText = gbxSelectGarena_cbbCurrentGarena->Items->Strings[gbxSelectGarena_cbbCurrentGarena->ItemIndex];
	CurrentGarenaID = gbxSelectGarena_cbbCurrentGarena->ItemIndex == -1 ? 0 : StrToInt(GarenaIDList->Strings[gbxSelectGarena_cbbCurrentGarena->ItemIndex]);
	gbxSelectGarena_lblAccountID->Caption = Translate[13][rgpLanguage->ItemIndex] + CurrentGarenaID;
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
}
