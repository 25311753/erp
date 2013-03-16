//---------------------------------------------------------------------------

#ifndef AskPurchaseListH
#define AskPurchaseListH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TAskPurchaseListForm : public TForm
{
__published:	// IDE-managed Components
	TLabel *Label1;
	TListView *lstView;
	TPanel *ctlPane;
	TLabel *Label2;
	TEdit *edtID;
	TLabel *Label3;
	TComboBox *lstType;
	TEdit *edtReqDate0;
	TLabel *Label6;
	TEdit *edtNeedDate;
	TComboBox *lstNeedType;
	TLabel *Label8;
	TComboBox *lstStockDep;
	TLabel *Label9;
	TComboBox *lstAskDep;
	TLabel *Label10;
	TComboBox *lstAfm;
	TLabel *Label11;
	TEdit *edtMncode;
	TButton *btnQuery;
	TButton *btnToExcel;
	TButton *btnExit;
	TButton *btnDetail;
	TLabel *Label4;
	TComboBox *lstReqType;
	TLabel *Label5;
	TComboBox *lstReqCorp;
	TLabel *Label12;
	TComboBox *lstEndFlag;
	TLabel *Label13;
	TComboBox *lstStockman;
	TButton *btnToEnd;
	TLabel *Label7;
	TComboBox *lstStockType;
	TButton *btnMaterPickup;
	void __fastcall btnExitClick(TObject *Sender);
	void __fastcall btnQueryClick(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall lstViewSelectItem(TObject *Sender, TListItem *Item,
          bool Selected);
	void __fastcall btnDetailClick(TObject *Sender);
	void __fastcall btnToExcelClick(TObject *Sender);
	void __fastcall lstViewDblClick(TObject *Sender);
	void __fastcall lstReqCorpClick(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
	void __fastcall FormResize(TObject *Sender);
	void __fastcall btnToEndClick(TObject *Sender);
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
	__fastcall TAskPurchaseListForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TAskPurchaseListForm *AskPurchaseListForm;
//---------------------------------------------------------------------------
#endif
