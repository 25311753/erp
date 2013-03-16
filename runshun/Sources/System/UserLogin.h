//---------------------------------------------------------------------------

#ifndef loginunitH
#define loginunitH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
#include <jpeg.hpp>
//---------------------------------------------------------------------------
class TUserLoginForm : public TForm
{
__published:	// IDE-managed Components
   TPanel *Panel1;
   TImage *Image1;
   TBitBtn *OKBtn;
   TBitBtn *CancelBtn;
   TBevel *Bevel1;
   TLabel *Label3;
   TEdit *Edit_Code;
   TLabel *Label4;
   TEdit *Edit_Password;
	TButton *btnDBSetup;
        TLabel *Label1;
        TLabel *Label2;
        TBevel *Bevel2;
        TLabel *Label5;
   void __fastcall OKBtnClick(TObject *Sender);
   void __fastcall CancelBtnClick(TObject *Sender);
   void __fastcall Edit_PasswordKeyPress(TObject *Sender, char &Key);
   void __fastcall FormShow(TObject *Sender);
   void __fastcall Edit_CodeKeyPress(TObject *Sender, char &Key);
	void __fastcall btnDBSetupClick(TObject *Sender);
private:	// User declarations
   int num;
public:		// User declarations
   __fastcall TUserLoginForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TUserLoginForm *UserLoginForm;
//---------------------------------------------------------------------------
#endif
