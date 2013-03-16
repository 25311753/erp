//---------------------------------------------------------------------------

#ifndef BookFactoryH
#define BookFactoryH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>

//---------------------------------------------------------------------------
class TBookFactoryForm : public TForm
{
__published:	// IDE-managed Components
	TLabel *Label1;
	TButton *btnQuery;
	TButton *btnNew;
	TButton *btnEdit;
	TButton *btnMove;
	TButton *btnPrint;
	TButton *btnOK;
	TButton *btnExit;
	TPanel *Panel1;
	TLabel *Label2;
	TEdit *edtBookID;
	TLabel *Label4;
	TEdit *edtAPCode;
	TLabel *Label3;
	TEdit *edtBookDate;
	TLabel *Label6;
	TLabel *Label7;
	TEdit *edtCard;
	TLabel *Label8;
	TEdit *edtUnit;
	TLabel *Label9;
	TEdit *edtCount;
	TLabel *Label10;
	TEdit *edtPrice;
	TLabel *Label11;
	TEdit *edtDays;
	TLabel *Label12;
	TLabel *Label13;
	TEdit *edtRem;
	TLabel *Label14;
	TComboBox *lstHandle;
	TLabel *Label15;
	TComboBox *lstInvoice;
	TLabel *Label5;
	TComboBox *lstInvoiceType;
	TComboBox *lstFactory;
	TLabel *Label16;
	TComboBox *lstRMB;
	TLabel *Label17;
	TLabel *Label18;
	TComboBox *lstBuyKind;
	TLabel *Label19;
	TComboBox *lstShowDate;
        TLabel *Label20;
        TComboBox *wfactory;
	void __fastcall FormShow(TObject *Sender);
	void __fastcall btnExitClick(TObject *Sender);
	void __fastcall btnQueryClick(TObject *Sender);
	void __fastcall btnNewClick(TObject *Sender);
	void __fastcall btnEditClick(TObject *Sender);
	void __fastcall btnMoveClick(TObject *Sender);
	void __fastcall btnPrintClick(TObject *Sender);
	void __fastcall btnOKClick(TObject *Sender);
	void __fastcall edtAPCodeExit(TObject *Sender);
	void __fastcall lstHandleExit(TObject *Sender);
	void __fastcall lstFactoryExit(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
	void __fastcall lstShowDateChange(TObject *Sender);
private:	// User declarations
	enum { EN_STATE_IDLE,EN_STATE_NEW,EN_STATE_EDIT } m_enState;
	CStringArray m_lstHandleID;
	CStringArray m_lstInvoiceID;
	CStringArray m_lstFactID;
	CStringArray m_lstRMBID;
        CStringArray m_lstFactID1;

	CArray<BASE2COLDATA,BASE2COLDATA>m_lstFactAll; //厂商列表
	CArray<BASE4COLDATA,BASE4COLDATA>m_lstRcptAll; //收货经办列表
	CArray<BASE2COLDATA,BASE2COLDATA>m_lstInvoAll; //发票列表

	CString m_szActiveID;
	AnsiString m_szFactID;
	AnsiString m_szUnitID;
	AnsiString m_szSHCode; //采购经办

	void ResetCtrl();
	CString GenerateID();
	bool CheckEditor();
	bool CanModify();
	void ResetPurchaseData(); //根据请购单号重设厂商、收货经办、发票的
	void ResetRcptHandle();
	void ResetRMBCode();
	void ResetBookData();
	void ResetFactory();

	void ResetAPData(LPCSTR lpszAP);
	void ResetRcptHandle(LPCSTR lpszAP);
	void ResetShowDate();



public:		// User declarations
	int m_nAuthor;
	AnsiString m_szIDFirst;

	__fastcall TBookFactoryForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TBookFactoryForm *BookFactoryForm;
//---------------------------------------------------------------------------
#endif
