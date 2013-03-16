//---------------------------------------------------------------------------

#ifndef DBSetupH
#define DBSetupH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>

void InitialODBC();

//---------------------------------------------------------------------------
class TDBSetupForm : public TForm
{
__published:	// IDE-managed Components
	TLabel *Label1;
	TLabel *Label2;
	TEdit *edtODBC;
	TLabel *Label3;
	TEdit *edtUID;
	TLabel *Label4;
	TEdit *edtPwd;
	TLabel *Label5;
	TEdit *edtPwd2;
	TButton *btnTest;
	TButton *btnOK;
	TButton *btnCancel;
	void __fastcall FormShow(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
	void __fastcall btnTestClick(TObject *Sender);
	void __fastcall btnOKClick(TObject *Sender);
	void __fastcall btnCancelClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TDBSetupForm(TComponent* Owner);

	bool TestSetup();

};
//---------------------------------------------------------------------------
extern PACKAGE TDBSetupForm *DBSetupForm;
//---------------------------------------------------------------------------
#endif
