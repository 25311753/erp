//---------------------------------------------------------------------------

#ifndef AcceptNotPayListH
#define AcceptNotPayListH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
class TAcceptNotPayListForm : public TForm
{
__published:	// IDE-managed Components
	TLabel *Label1;
	TListView *lstView;
	TButton *btnExit;
	TButton *btnToExcel;
	TLabel *Label2;
	TComboBox *lstCorp;
	TLabel *Label3;
	TComboBox *lstStore;
	TButton *btnQuery;
	TLabel *Label4;
	TComboBox *lstFact;
	TButton *btnFactPickup;
	void __fastcall FormShow(TObject *Sender);
	void __fastcall btnToExcelClick(TObject *Sender);
	void __fastcall btnExitClick(TObject *Sender);
	void __fastcall btnQueryClick(TObject *Sender);
	void __fastcall btnFactPickupClick(TObject *Sender);
	void __fastcall lstFactExit(TObject *Sender);
private:	// User declarations
	CStringArray m_lstCorpID;
	CStringArray m_lstStoreID;
	CStringArray m_lstFactID;

public:		// User declarations
	__fastcall TAcceptNotPayListForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TAcceptNotPayListForm *AcceptNotPayListForm;
//---------------------------------------------------------------------------
#endif
