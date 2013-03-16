//---------------------------------------------------------------------------

#ifndef AskPurchaseH
#define AskPurchaseH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
#include <AppEvnts.hpp>

#include "PurchaseRow.h"

//---------------------------------------------------------------------------
class TAskPurchaseForm : public TForm
{
__published:	// IDE-managed Components
	TLabel *Title;
	TGroupBox *grpReg0;
	TLabel *Label2;
	TEdit *edtMainID;
	TLabel *Label3;
	TEdit *edtNeedDate;
	TLabel *Label4;
	TComboBox *lstType;
	TLabel *Label5;
	TEdit *edtAskDate;
	TLabel *Label6;
	TComboBox *lstBuyType;
	TLabel *Label7;
	TComboBox *lstDepAsk;
	TLabel *Label8;
	TComboBox *lstDepBuy;
	TLabel *Label9;
	TComboBox *lstDepCharge;
	TLabel *Label10;
	TEdit *edtProject;
	TLabel *Label11;
	TEdit *edtUsage;
	TLabel *Label12;
	TComboBox *lstGoodsAddr;
	TLabel *Label13;
	TComboBox *lstChkFlag;
	TLabel *Label14;
	TEdit *edtChkSpec;
	TLabel *Label15;
	TComboBox *lstHandle;
	TLabel *Label16;
	TEdit *edtAfmDate;
	TLabel *Label17;
	TEdit *edtModifyDate;
	TLabel *Label18;
	TEdit *edtInpDate;
	TListView *lstView;
	TGroupBox *grpReg1;
	TLabel *Label19;
	TEdit *edtItem;
	TLabel *Label20;
	TEdit *edtMater;
	TLabel *Label21;
	TComboBox *lstUnits;
	TLabel *Label22;
	TEdit *edtCount;
	TLabel *txtCooper;
	TEdit *edtCooper;
	TLabel *Label24;
	TEdit *edtEndFlag;
	TPanel *Panel1;
	TBitBtn *btnReg0;
	TBitBtn *btnReg1;
	TBitBtn *btnQuery;
	TBitBtn *btnNew;
	TBitBtn *btnEdit;
	TButton *btnMove;
	TButton *btnPrint;
	TButton *btnOK;
	TButton *btnExit;
	TImage *Image1;
	TApplicationEvents *ApplicationEvents1;
	TLabel *txtTips;
	TButton *btnQueryMT;
	TLabel *Label25;
	TEdit *edtPrnDate;
	TLabel *Label26;
	TEdit *edtMnname;
	TComboBox *lstTreat;
	TLabel *txtTreat;
	TButton *btnToTreat;
	TLabel *Label23;
	TComboBox *lstTreatFlag;
	TListBox *lstTreatView;
	TButton *btnPrintRem;
	void __fastcall btnExitClick(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key,TShiftState Shift);
	void __fastcall grpReg1Click(TObject *Sender);
	void __fastcall grpReg0Click(TObject *Sender);
	void __fastcall btnReg0Click(TObject *Sender);
	void __fastcall btnReg1Click(TObject *Sender);
	void __fastcall btnQueryClick(TObject *Sender);
	void __fastcall btnNewClick(TObject *Sender);
	void __fastcall btnEditClick(TObject *Sender);
	void __fastcall btnMoveClick(TObject *Sender);
	void __fastcall btnPrintClick(TObject *Sender);
	void __fastcall btnOKClick(TObject *Sender);
	void __fastcall lstViewClick(TObject *Sender);
	void __fastcall lstViewSelectItem(TObject *Sender, TListItem *Item,bool Selected);
	void __fastcall btnQueryMTClick(TObject *Sender);
	void __fastcall ApplicationEvents1Idle(TObject *Sender, bool &Done);
	void __fastcall edtMaterExit(TObject *Sender);
	void __fastcall lstTreatClick(TObject *Sender);
	void __fastcall btnToTreatClick(TObject *Sender);
	void __fastcall lstTreatViewExit(TObject *Sender);
	void __fastcall lstTreatViewDblClick(TObject *Sender);
	void __fastcall lstTreatViewKeyDown(TObject *Sender, WORD &Key,TShiftState Shift);
	void __fastcall lstUnitsExit(TObject *Sender);
	void __fastcall btnPrintRemClick(TObject *Sender);
private:	// User declarations
	void ResetCtrl();
	enum { EN_STATE_IDLE,EN_STATE_NEW,EN_STATE_EDIT } m_enState;
	enum { EN_REGION0,EN_REGION1 } m_enRegion;
	bool m_bExiting;
	CString m_szActiveID;
	CStringArray m_lstDepartID;
	CStringArray m_lstStockDepID;
	CStringArray m_lstHandleID;
	CStringArray m_lstGACode;
	CStringArray m_lstGACorp;
	CStringArray m_lstUnitID;
	CStringArray m_lstTreatID;
	CStringArray m_lstTreatUnit;
	CAskPurchaseRow m_rwMain;
	CArray<CPurchaseDetailRow,CPurchaseDetailRow>m_lstDetail;
//	TDateTime m_tMainOperTime;
	bool m_bIsTreat;
	AnsiString m_szPrvMaterialID;

	void Editor2Row(CAskPurchaseRow &row,bool bNew);
	void Editor2Row(CPurchaseDetailRow &row,bool bNew);
	void OnRegion0New(CAskPurchaseRow &row);
	void OnRegion0Edit(CAskPurchaseRow &row);
	void Row2Editor(CAskPurchaseRow &row);
	void Row2Editor(CPurchaseDetailRow &row);
	bool CheckRegion0();
	bool CheckRegion1();
	void OnRegion1New(CPurchaseDetailRow &row);
	void OnRegion1Edit(CPurchaseDetailRow &row);
	void Row2List(CPurchaseDetailRow &row);
	void List2Editor(TListItem *pItem);
	CString GenerateID();
	void ResetTreatList(LPCSTR lpszID,LPCSTR lpszSel);
	void ResetTreatUnit();
	void ResetAskDepart(bool bIdle);

public:		// User declarations
	int m_nAuthor;
	AnsiString m_szIDFirst;
	bool m_bUnion;

	__fastcall TAskPurchaseForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TAskPurchaseForm *AskPurchaseForm;
//---------------------------------------------------------------------------
#endif
