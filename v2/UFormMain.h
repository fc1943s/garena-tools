#ifndef UFormMainH
#define UFormMainH

#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <ComCtrls.hpp>
#include <Buttons.hpp>
#include <Graphics.hpp>
#include <ImgList.hpp>
#include "Stew.cpp"
#include "UPointers.cpp"

struct HackStructure
{
	TLabel* lblHack;
	TImage* imgHack;
	int HackCaption;
	int HintNumber;
	int const* FirstPointer;
	int PointerCount;
};

class TFormMain : public TForm
{
__published:
	TLabel* lblTitle;
	TLabel* lblForumLink;
	TLabel* lblStew;
	TLabel* lblUpdates;
	TTimer* tmrMain;
	TImageList* imlMain;
	TGroupBox* gbxHacks;
	TRadioGroup* rgpLanguage;
	TGroupBox* gbxSelectGarena;
	TComboBox* gbxSelectGarena_cbbCurrentGarena;
	TGroupBox* gbxSettings;
	TLabel* gbxSettings_lblCustomGarenaPath;
	TEdit* gbxSettings_edtCustomGarenaPath;
	TCheckBox* gbxSettings_chbEnableHelp;
	TLabel* lblGarenaVersion;
	TButton* btnRunGarena;
	TLabel* gbxSelectGarena_lblNick;
	TButton* Button1;
	TCheckBox* gbxSettings_chbEnableNameSpoofer;
	TEdit* gbxSettings_edtNameSpoofer;
	TLabel* gbxSettings_lblNameSpoofer;
	TTrayIcon* triMain;
	TLabel* lblCredits;

	void __fastcall FormCreate(TObject* Sender);
	void __fastcall OpenForum(TObject* Sender);
	void __fastcall tmrMainTimer(TObject* Sender);
	void __fastcall rgpLanguageClick(TObject* Sender);
	void __fastcall btnRunGarenaClick(TObject* Sender);
	void __fastcall gbxSelectGarena_cbbCurrentGarenaChange(TObject* Sender);
	void __fastcall FormClose(TObject* Sender, TCloseAction& Action);
	void __fastcall gbxSettings_chbEnableHelpClick(TObject* Sender);
	void __fastcall gbxSettings_chbEnableNameSpooferClick(TObject* Sender);
	void __fastcall gbxSettings_edtNameSpooferChange(TObject* Sender);
	void __fastcall gbxSettings_edtCustomGarenaPathChange(TObject* Sender);
	void __fastcall Button1Click(TObject* Sender);
	void __fastcall triMainClick(TObject* Sender);
	void __fastcall lblCreditsClick(TObject* Sender);

private:
public:
	void ChangeLanguage(int Language);
	void SaveRegConfig();
	void RefreshGarenaProcesses();
	void AddHack(int HackCaption, int HintNumber, int const* FirstPointer, int PointerCount);
	void CreateHacks();
	void CCWriteLine(int Value, int Size);
	void NullGEngine(HANDLE CGH);
	void NameSpoofer(HANDLE CGH);
	void __fastcall HideToTray(TObject* Sender);
	__fastcall TFormMain(TComponent* Owner);
};

extern PACKAGE TFormMain* FormMain;
#endif
