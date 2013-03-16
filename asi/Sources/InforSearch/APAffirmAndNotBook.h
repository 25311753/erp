//---------------------------------------------------------------------------

#ifndef APAffirmAndNotBookH
#define APAffirmAndNotBookH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TAPAffirmAndNotBookForm : public TForm
{
__published:	// IDE-managed Components
	TLabel *Label1;
	TListView *lstView;
	TPanel *ctlPane;
	TLabel *Label2;
	TLabel *Label3;
	TLabel *Label8;
	TLabel *Label9;
	TLabel *Label11;
	TLabel *Label5;
	TLabel *Label13;
	TEdit *edtID;
	TComboBox *lstType;
	TComboBox *lstStockDep;
	TComboBox *lstAskDep;
	TEdit *edtMncode;
	TButton *btnQuery;
	TButton *btnExit;
	TButton *btnDetail;
	TComboBox *lstReqCorp;
	TComboBox *lstStockman;
	TLabel *Label4;
	TEdit *edtAfmDay;
	TLabel *Label6;
	TButton *btnPrint;
	TButton *btnMaterPickup;
	TButton *btnToExcel;
	void __fastcall btnExitClick(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall FormResize(TObject *Sender);
	void __fastcall btnQueryClick(TObject *Sender);
	void __fastcall lstViewClick(TObject *Sender);
	void __fastcall lstViewDblClick(TObject *Sender);
	void __fastcall lstViewSelectItem(TObject *Sender, TListItem *Item,
          bool Selected);
	void __fastcall btnDetailClick(TObject *Sender);
	void __fastcall btnToExcelClick(TObject *Sender);
	void __fastcall btnPrintClick(TObject *Sender);
	void __fastcall btnMaterPickupClick(TObject *Sender);
private:	// User declarations
	CStringArray m_lstStockDepID;
	CStringArray m_lstDepID;
	CStringArray m_lstDepName;
	CStringArray m_lstCorpID;
	CStringArray m_lstReqDepID;
	CStringArray m_lstStockmanID;

	void ResetReqDepart();
	bool GetFilter(CString &szFilter);

	void ResetCtrl();
public:		// User declarations
	__fastcall TAPAffirmAndNotBookForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TAPAffirmAndNotBookForm *APAffirmAndNotBookForm;
//---------------------------------------------------------------------------
#endif
