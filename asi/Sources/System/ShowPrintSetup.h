//---------------------------------------------------------------------------

#ifndef ShowPrintSetupH
#define ShowPrintSetupH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
class TShowPrnSetupForm : public TForm
{
__published:	// IDE-managed Components
	TLabel *Label1;
	TLabel *Label2;
	TEdit *edtTop;
	TLabel *Label3;
	TEdit *edtLeft;
	TLabel *Label4;
	TLabel *Label5;
	TButton *btnOK;
	TButton *btnCancel;
	TLabel *Label6;
	TEdit *edtBottom;
	TLabel *Label7;
	void __fastcall FormShow(TObject *Sender);
	void __fastcall btnOKClick(TObject *Sender);
	void __fastcall btnCancelClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TShowPrnSetupForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TShowPrnSetupForm *ShowPrnSetupForm;
//---------------------------------------------------------------------------
#endif
