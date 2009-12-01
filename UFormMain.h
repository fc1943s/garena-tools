#ifndef UFormMainH
#define UFormMainH

#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <ScktComp.hpp>

class TFormMain : public TForm
{
__published:
	TButton* Button1;
	TEdit* Edit1;
	TEdit* Edit2;
	TMemo* Memo1;
	TTimer* Timer1;
	TMemo* Memo2;
	TButton* Button2;
	TButton* Button3;
	TButton* Button4;
	TButton* Button5;
	TMemo* Memo3;
	TMemo* Memo4;
	TClientSocket* ClientSocket1;
	TButton* Button6;
	TCheckBox* CheckBox1;
	TButton* Button7;
	TButton* Button8;

	void __fastcall Button1Click(TObject* Sender);
	void __fastcall Timer1Timer(TObject* Sender);
	void __fastcall Button2Click(TObject* Sender);
	void __fastcall Button3Click(TObject* Sender);
	void __fastcall Button4Click(TObject* Sender);
	void __fastcall Button5Click(TObject* Sender);
	void __fastcall ClientSocket1Connect(TObject* Sender, TCustomWinSocket* Socket);
	void __fastcall ClientSocket1Connecting(TObject* Sender, TCustomWinSocket* Socket);
	void __fastcall ClientSocket1Disconnect(TObject* Sender, TCustomWinSocket* Socket);
	void __fastcall ClientSocket1Error(TObject* Sender, TCustomWinSocket* Socket, TErrorEvent ErrorEvent, int& ErrorCode);
	void __fastcall ClientSocket1Read(TObject* Sender, TCustomWinSocket* Socket);
	void __fastcall Button6Click(TObject* Sender);
	void __fastcall CheckBox1Click(TObject* Sender);
	void __fastcall Button7Click(TObject* Sender);
	void __fastcall Button8Click(TObject* Sender);

private:
public:
	__fastcall TFormMain(TComponent* Owner);
};

extern PACKAGE TFormMain* FormMain;
#endif
