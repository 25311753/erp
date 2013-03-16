//---------------------------------------------------------------------------

#ifndef SumHiggleNotEndH
#define SumHiggleNotEndH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TSumHiggleNotEndForm : public TForm
{
__published:	// IDE-managed Components
	TLabel *Label1;
	TListView *lstView;
	TPanel *Panel1;
	TLabel *Label2;
	TComboBox *lstHandle;
	TLabel *Label3;
	TComboBox *lstCorp;
	TLabel *Label4;
	TComboBox *lstFactory;
	TButton *btnQuery;
	TButton *btnPrint;
	TButton *btnToExcel;
	TButton *btnExit;
	TLabel *Label5;
	TEdit *edtDays;
	TLabel *Label6;
	TComboBox *lstStockDepart;
	void __fastcall btnExitClick(TObject *Sender);
	void __fastcall btnToExcelClick(TObject *Sender);
	void __fastcall btnPrintClick(TObject *Sender);
	void __fastcall btnQueryClick(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall lstFactoryExit(TObject *Sender);
private:	// User declarations
	CStringArray m_lstFactID;
	CStringArray m_lstCorpID;
	CStringArray m_lstHandleID;
	CStringArray m_lstStockDepartID;

public:		// User declarations
	__fastcall TSumHiggleNotEndForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TSumHiggleNotEndForm *SumHiggleNotEndForm;
//---------------------------------------------------------------------------
#endif
