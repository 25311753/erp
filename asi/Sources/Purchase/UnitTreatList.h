//---------------------------------------------------------------------------

#ifndef UnitTreatListH
#define UnitTreatListH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
class TUnitTreatListForm : public TForm
{
__published:	// IDE-managed Components
	TLabel *Label1;
	TListView *lstView;
	TLabel *Label2;
	TComboBox *lstCorp;
	TLabel *Label3;
	TComboBox *lstLarge;
	TButton *btnExit;
	TButton *btnToExcel;
	TButton *btnPrint;
	TButton *btnQuery;
	TLabel *Label4;
	void __fastcall FormShow(TObject *Sender);
	void __fastcall btnQueryClick(TObject *Sender);
	void __fastcall btnPrintClick(TObject *Sender);
	void __fastcall btnToExcelClick(TObject *Sender);
	void __fastcall btnExitClick(TObject *Sender);
private:	// User declarations
	CStringArray m_lstCorpID;
	CStringArray m_lstLargeID;

public:		// User declarations
	__fastcall TUnitTreatListForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TUnitTreatListForm *UnitTreatListForm;
//---------------------------------------------------------------------------
#endif
