//---------------------------------------------------------------------------

#ifndef Book4TimesH
#define Book4TimesH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
class TBook4TimesForm : public TForm
{
__published:	// IDE-managed Components
	TLabel *Label1;
	TListView *lstView;
	TLabel *Label2;
	TEdit *edtDate0;
	TLabel *Label3;
	TEdit *edtDate1;
	TButton *btnQuery;
	TButton *btnToExcel;
	TButton *btnExit;
	TLabel *Label4;
	TComboBox *lstCorp;
	TLabel *Label5;
	TComboBox *lstDepart;
	TLabel *Label6;
	TEdit *edtTimes;
	void __fastcall btnExitClick(TObject *Sender);
	void __fastcall btnToExcelClick(TObject *Sender);
	void __fastcall btnQueryClick(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
private:	// User declarations
	CStringArray m_lstCorpID;
	CStringArray m_lstDepartID;

public:		// User declarations
	__fastcall TBook4TimesForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TBook4TimesForm *Book4TimesForm;
//---------------------------------------------------------------------------
#endif
