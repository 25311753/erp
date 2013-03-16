//---------------------------------------------------------------------------

#ifndef PurchaseRoadH
#define PurchaseRoadH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TPurchaseRoadForm : public TForm
{
__published:	// IDE-managed Components
	TLabel *Label1;
	TPageControl *ctlPage;
	TTabSheet *ctlSpeer;
	TLabel *Label3;
	TEdit *edtSpeerEndDate;
	TLabel *Label4;
	TEdit *edtSpeerPrnDate;
	TLabel *Label5;
	TComboBox *lstSpeerFact;
	TListBox *lstSpeerView;
	TTabSheet *ctlQuote;
	TListView *lstQuoteView;
	TPanel *Panel1;
	TLabel *Label6;
	TEdit *edtQuoteItem;
	TLabel *Label7;
	TComboBox *lstQuoteFact;
	TLabel *Label8;
	TEdit *edtQuoteFactCard;
	TLabel *Label9;
	TEdit *edtQuoteReqUnit;
	TLabel *Label10;
	TEdit *edtQuoteReqNum;
	TLabel *Label11;
	TComboBox *lstQuoteUnit;
	TLabel *Label12;
	TEdit *edtQuoteNum;
	TLabel *Label13;
	TEdit *edtQuotePrice;
	TLabel *Label14;
	TEdit *edtQuoteDelDays;
	TLabel *Label15;
	TLabel *Label16;
	TComboBox *lstQuotePay;
	TLabel *Label17;
	TLabel *Label18;
	TEdit *edtQuoteInpDate;
	TTabSheet *ctlHiggle;
	TListView *lstHiggleView;
	TLabel *Label19;
	TEdit *edtHigglePrice;
	TLabel *Label20;
	TEdit *edtHiggleDate;
	TTabSheet *ctlShow;
	TListView *lstShowView;
	TLabel *Label21;
	TComboBox *lstShowFact;
	TLabel *Label22;
	TEdit *edtShowDate;
	TTabSheet *ctlDecide;
	TListView *lstDecideView;
	TLabel *Label23;
	TComboBox *lstDecideFact;
	TLabel *Label24;
	TEdit *edtDecideDate;
	TPanel *Panel2;
	TLabel *Label2;
	TEdit *edtMainID;
	TLabel *Label25;
	TEdit *edtNeedDate;
	TLabel *Label26;
	TLabel *Label27;
	TEdit *edtAskDate;
	TLabel *Label28;
	TLabel *Label29;
	TLabel *Label30;
	TEdit *edtBuyType;
	TEdit *edtType;
	TEdit *edtAskDepart;
	TEdit *edtStockDep;
	TPanel *Panel3;
	TButton *btnQuery;
	TButton *btnNew;
	TButton *btnEdit;
	TButton *btnMove;
	TButton *btnDetail;
	TButton *btnOK;
	TButton *btnExit;
	TButton *btnSpeerFactInf;
	TButton *btnSpeerPrn;
	TLabel *Label32;
	TEdit *edtShowItem;
	TLabel *Label33;
	TEdit *edtDecideItem;
	TLabel *Label34;
	TEdit *edtDecideNum;
	TLabel *Label35;
	TComboBox *lstDecideUnit;
	TLabel *Label36;
	TEdit *edtDecidePrice;
	TLabel *Label37;
	TEdit *edtDecideFact0;
	TButton *btnQuotePrint;
	TLabel *Label38;
	TEdit *edtStockMan;
	TLabel *Label39;
	TEdit *edtProject;
	TLabel *Label40;
	TEdit *edtTel;
	TButton *btnHigglePrint;
	TButton *btnShowPrint;
	TLabel *Label31;
	TEdit *edtAfmDate;
	TButton *btnSpeerFactSearch;
	TLabel *Label41;
	TEdit *edtShowRem;
	TTabSheet *ctlBook;
	TListView *lstBookView;
	TButton *btnToBook;
	TLabel *Label42;
	TEdit *edtValidDate;
	TButton *btnStockRecord;
	TLabel *Label43;
	TComboBox *lstQuoteRMB;
	TLabel *Label44;
	TEdit *edtHiggleRMB;
	TLabel *Label45;
	TComboBox *lstQuoteDelivery;
	TComboBox *lstQuoteTax;
	TLabel *Label46;
	TComboBox *lstPriceRT;
	TTabSheet *ctlStockList;
	TListView *lstStockList;
	TButton *btnListStock;
	TLabel *Label47;
	TEdit *edtDfShowDate;
	TLabel *Label48;
	TEdit *edtShowNum;
        TButton *btnToMutBook;
	void __fastcall btnExitClick(TObject *Sender);
	void __fastcall ctlSpeerShow(TObject *Sender);
	void __fastcall btnQueryClick(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall lstSpeerFactExit(TObject *Sender);
	void __fastcall btnNewClick(TObject *Sender);
	void __fastcall btnOKClick(TObject *Sender);
	void __fastcall lstSpeerViewClick(TObject *Sender);
	void __fastcall btnEditClick(TObject *Sender);
	void __fastcall btnDetailClick(TObject *Sender);
	void __fastcall edtMainIDChange(TObject *Sender);
	void __fastcall ctlPageChanging(TObject *Sender, bool &AllowChange);
	void __fastcall btnMoveClick(TObject *Sender);
	void __fastcall ctlQuoteShow(TObject *Sender);
	void __fastcall lstQuoteFactExit(TObject *Sender);
	void __fastcall lstQuoteViewSelectItem(TObject *Sender, TListItem *Item,
          bool Selected);
	void __fastcall lstQuoteViewClick(TObject *Sender);
	void __fastcall edtQuoteItemExit(TObject *Sender);
	void __fastcall ctlHiggleShow(TObject *Sender);
	void __fastcall lstHiggleViewClick(TObject *Sender);
	void __fastcall lstHiggleViewSelectItem(TObject *Sender, TListItem *Item,
          bool Selected);
	void __fastcall btnSpeerPrnClick(TObject *Sender);
	void __fastcall btnSpeerFactInfClick(TObject *Sender);
	void __fastcall ctlShowShow(TObject *Sender);
	void __fastcall lstShowFactExit(TObject *Sender);
	void __fastcall lstShowViewClick(TObject *Sender);
	void __fastcall lstShowViewSelectItem(TObject *Sender, TListItem *Item,
          bool Selected);
	void __fastcall ctlDecideShow(TObject *Sender);
	void __fastcall lstDecideViewClick(TObject *Sender);
	void __fastcall lstDecideViewSelectItem(TObject *Sender, TListItem *Item,
          bool Selected);
	void __fastcall lstDecideFactExit(TObject *Sender);
	void __fastcall btnQuotePrintClick(TObject *Sender);
	void __fastcall btnHigglePrintClick(TObject *Sender);
	void __fastcall btnShowPrintClick(TObject *Sender);
	void __fastcall btnSpeerFactSearchClick(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
	void __fastcall lstDecideUnitExit(TObject *Sender);
	void __fastcall lstQuoteUnitExit(TObject *Sender);
	void __fastcall btnToBookClick(TObject *Sender);
	void __fastcall ctlBookShow(TObject *Sender);
	void __fastcall lstBookViewDblClick(TObject *Sender);
	void __fastcall lstQuoteUnitEnter(TObject *Sender);
	void __fastcall edtQuoteNumEnter(TObject *Sender);
	void __fastcall btnStockRecordClick(TObject *Sender);
	void __fastcall lstQuoteDeliveryExit(TObject *Sender);
	void __fastcall lstQuoteTaxExit(TObject *Sender);
	void __fastcall btnListStockClick(TObject *Sender);
	void __fastcall ctlStockListShow(TObject *Sender);
        void __fastcall lstQuoteFactChange(TObject *Sender);
        void __fastcall btnToMutBookClick(TObject *Sender);
private:	// User declarations
	bool m_bSpeerInitialed;
	bool m_bQuoteInitialed;
	bool m_bHiggleInitialed;
	bool m_bShowInitialed;
	bool m_bDecideInitialed;

	enum { EN_STATE_IDLE, EN_STATE_NEW , EN_STATE_EDIT } m_enState;
	enum { EN_REG_SPEER,EN_REG_QUOTE,EN_REG_HIGGLE,EN_REG_SHOW,EN_REG_DECIDE,EN_REG_BOOK,EN_REG_LIST } m_enRegion;

	CStringArray m_lstQuoteViewID;
	CStringArray m_lstQuoteFactID;
	CStringArray m_lstQuoteUnitID;
	CStringArray m_lstQuotePayID;

	CStringArray m_lstQuoteRMBID;
  CStringArray m_lstQuoteDeliveryID;
  CStringArray m_lstQuoteTaxID;

  CStringArray m_lstQuoteTaxIDnew;

	CArray<BASE2COLDATA,BASE2COLDATA>m_lstHiggleRMB;

	CStringArray m_lstHiggleViewID;
	CStringArray m_lstShowViewID;
	CStringArray m_lstShowFactID;
	CStringArray m_lstDecideFactID;
	CStringArray m_lstDecideViewID;
	CStringArray m_lstDecideUnitID;

	CString m_szActiveID;
	CString m_szSpeerID;
	CString m_szQuoteID;
	CString m_szHiggleID;

	CStringArray m_lstSpeerFactID;
	CStringArray m_lstSpeerViewID;

	void OnQuerySpeer(LPCSTR lpszID);
	void OnQueryQuote(LPCSTR lpszID);
	void OnQueryHiggle(LPCSTR lpszID);
  void OnQueryShow(LPCSTR lpszID);
	void OnSpeerNew();
	void ResetCtrl();
	void OnFactListExit(TComboBox *pList,CStringArray &lstID);
	void FetchQuotePurchase(LPCSTR lpszItem);
	void OnQueryDecide(LPCSTR lpszID);
	void OnQueryBook(LPCSTR lpszID);
	void OnDecideShow();
	void OnDecideOK();
	void OnDecideMove();

	void OnSpeerOK();
	void OnSpeerMove();
	void OnQuoteMove();
	void OnShowMove();
	void OnQuoteOK();
	void OnHiggleOK();
	void OnShowOK();

	void EmptySpeer();
	void EmptyQuote();
	void EmptyShow();

	void InitQuoteFactory();
	void InitShowFactory();
	void InitDecideFactory(LPCSTR lpszID);
	void InitStockList();

public:		// User declarations
	int m_nAuthor;
        AnsiString edtform();

	__fastcall TPurchaseRoadForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TPurchaseRoadForm *PurchaseRoadForm;
//---------------------------------------------------------------------------
#endif
