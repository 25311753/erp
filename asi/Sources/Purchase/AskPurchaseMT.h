//---------------------------------------------------------------------------

#ifndef AskPurchaseMTH
#define AskPurchaseMTH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <ADODB.hpp>
#include <DB.hpp>
#include <DBCtrls.hpp>
#include <DBGrids.hpp>
#include <Grids.hpp>
//---------------------------------------------------------------------------
class TAskPurchaseMTForm : public TForm
{
__published:	// IDE-managed Components
	TLabel *Label5;
	TPageControl *ctlPage;
	TTabSheet *ctlType;
	TEdit *edtCorp;
	TEdit *edtID0;
	TPanel *Panel1;
	TEdit *edtID1;
	TLabel *Label6;
	TEdit *edtSpec;
	TLabel *Label1;
	TComboBox *lstCorp;
	TLabel *Label2;
	TComboBox *lstLarge;
	TLabel *Label3;
	TComboBox *lstMid;
	TLabel *Label4;
	TComboBox *lstMin;
	TListView *lstView;
	TTabSheet *ctlTree;
	TTreeView *lstTree;
	TListView *lstTreeView;
	TLabel *Label7;
	TComboBox *lstTreeCorp;
	TButton *btnToExcel;
	TButton *btnOK;
	TButton *btnCancel;
	TLabel *Label8;
	TEdit *edtID;
	TLabel *Label9;
	TEdit *edtName;
	TTabSheet *ctlSearch;
	TLabel *Label10;
	TEdit *edtSearchText;
	TLabel *Label11;
	TListView *lstSearchView;
	TButton *btnSearch;
	TTabSheet *ctlPrefix;
	TLabel *Label12;
	TLabel *Label13;
	TEdit *edtPrefixID;
	TButton *btnPrefixQuery;
	TListView *lstPrefixView;
	TLabel *Label14;
	TComboBox *lstTreatType;
	TMemo *Memo1;
	TButton *btnPrintRem;
	TButton *btnRem2Excel;
        TLabel *Label15;
        TEdit *edtUnits;
        TGroupBox *GroupBox1;
        TDBImage *DBImage1;
        TDataSource *DSMnPic;
        TADOConnection *ADOC1;
        TADOTable *ADOT1;
        TLabel *labCorp;
        TLabel *labID0;
        TLabel *labID1;
        TButton *btnDetail;
	void __fastcall FormShow(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
	void __fastcall lstCorpClick(TObject *Sender);
	void __fastcall lstLargeClick(TObject *Sender);
	void __fastcall edtID0Change(TObject *Sender);
	void __fastcall edtCorpChange(TObject *Sender);
	void __fastcall lstMidClick(TObject *Sender);
	void __fastcall lstMinClick(TObject *Sender);
	void __fastcall edtID1Change(TObject *Sender);
	void __fastcall lstViewSelectItem(TObject *Sender, TListItem *Item,
          bool Selected);
	void __fastcall btnOKClick(TObject *Sender);
	void __fastcall btnToExcelClick(TObject *Sender);
	void __fastcall ctlTreeShow(TObject *Sender);
	void __fastcall lstTreeClick(TObject *Sender);
	void __fastcall lstTreeChange(TObject *Sender, TTreeNode *Node);
	void __fastcall lstTreeViewSelectItem(TObject *Sender, TListItem *Item,
          bool Selected);
	void __fastcall lstTreeCorpClick(TObject *Sender);
	void __fastcall lstSearchViewSelectItem(TObject *Sender, TListItem *Item,
          bool Selected);
	void __fastcall btnSearchClick(TObject *Sender);
	void __fastcall btnPrefixQueryClick(TObject *Sender);
	void __fastcall lstPrefixViewSelectItem(TObject *Sender, TListItem *Item,
          bool Selected);
	void __fastcall lstTreatTypeClick(TObject *Sender);
	void __fastcall lstViewDblClick(TObject *Sender);
	void __fastcall lstPrefixViewDblClick(TObject *Sender);
	void __fastcall lstTreeViewDblClick(TObject *Sender);
	void __fastcall lstSearchViewDblClick(TObject *Sender);
	void __fastcall btnRem2ExcelClick(TObject *Sender);
	void __fastcall btnPrintRemClick(TObject *Sender);
        void __fastcall btnDetailClick(TObject *Sender);
private:	// User declarations
	CStringArray m_lstCorpID;
	CStringArray m_lstLargID;
	CStringArray m_lstMidID;
	CStringArray m_lstMinID;
	CStringArray m_lstTreeCorpID;

	char	m_cCurCorp;
	char	m_cCurLarge;
	CString m_szCurMid;
	CString m_szCurMin;
	TTreeNode *m_pNode;

	CStringArray m_lstTreeID;

  bool m_bTreeInitialed;

	enum { EN_CLICK_NONE,EN_CLICK_CORP,EN_CLICK_LARGE,EN_CLICK_MID,EN_CLICK_MIN,EN_CLICK_VIEW,EN_CLICK_INIT } m_enClick;

	void ResetAllUI();
	void ResetCorp();
	void ResetMiddle();
	void ResetMin();
	void ResetView();

public:		// User declarations
	AnsiString m_szMaterCode;
	int m_nTreatType;
        int m_nAuthor;        

	__fastcall TAskPurchaseMTForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TAskPurchaseMTForm *AskPurchaseMTForm;
//---------------------------------------------------------------------------
#endif
