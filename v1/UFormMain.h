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

struct HackStructure
{
	TLabel* lblHack;
	TImage* imgHack;
	UnicodeString HackName;
	int HackCaption;
	int HintNumber;
	int const* FirstPointer;
	int PointerCount;
	int State;
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
	TGroupBox* gbxLegend;
	TImage* gbxLegend_imgUnavailable;
	TLabel* gbxLegend_lblUnavailable;
	TLabel* gbxLegend_lblDisabled;
	TImage* gbxLegend_imgDisabled;
	TImage* gbxLegend_imgEnabled;
	TLabel* gbxLegend_lblEnabled;
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
	TLabel* gbxSelectGarena_lblAccountID;

	void __fastcall FormCreate(TObject* Sender);
	void __fastcall OpenForum(TObject* Sender);
	void __fastcall imgHackClick(TObject* Sender);
	void __fastcall tmrMainTimer(TObject* Sender);
	void __fastcall rgpLanguageClick(TObject* Sender);
	void __fastcall btnRunGarenaClick(TObject* Sender);
	void __fastcall gbxSelectGarena_cbbCurrentGarenaChange(TObject* Sender);
	void __fastcall FormClose(TObject* Sender, TCloseAction& Action);
	void __fastcall gbxSettings_chbEnableHelpClick(TObject* Sender);

private:

public:
	void ChangeLanguage(int Language);
	void SaveRegConfig();
	void RefreshGarenaProcesses();
	void AddHack(UnicodeString HackName, int HackCaption, int HintNumber, int const* FirstPointer, int PointerCount);
	void ChangeHackState(int HackNumber, int State);
	void CreateHacks();
	__fastcall TFormMain(TComponent* Owner);

};

extern PACKAGE TFormMain* FormMain;

#endif
