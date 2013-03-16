//---------------------------------------------------------------------------

#ifndef FactoryH
#define FactoryH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>

#include "RamRow.h"

class CFactoryRow : public CRamRow
{
public:
	CFactoryRow();
	bool ReadFromDB(TQuery *pQuery);

	char	mf_code[80];
  char	mf_name[80];
  char	mf_shortname[80];
  char	mf_linkman[80];
  char	mf_tel[80];
  char	mf_fax[80];
  char	mf_addr[80];
  char	mf_type[80];
  char	mf_artific[80];
  char	mf_regmoney[80];
  char	mf_prodaddr   [128];
  int mf_areascale;
  int mf_manscale;
  int mf_monthcap;
  char	mf_workitem[80];
  char	mf_idaffix[80];
  char	mf_status[80];
  char	mf_postcode[80];
  char	mf_taxcode[80];
  char	mf_bankid[80];
  char	mf_bankname[80];
  char	mf_bandaddr[128];
  char	mf_judge[80];
  char	mf_advice[80];
  char	mf_mail[80];

  TDateTime mf_statdate0;
  TDateTime mf_statdate1;
  TDateTime mf_inputdate;

};

//---------------------------------------------------------------------------
class TFactoryForm : public TForm
{
__published:	// IDE-managed Components
	TLabel *Label1;
	TListBox *lstCode;
	TLabel *Label2;
	TPanel *Panel1;
	TLabel *Label3;
	TEdit *edtID;
	TLabel *Label4;
	TEdit *edtName;
	TLabel *Label5;
	TEdit *edtShortName;
	TLabel *Label6;
	TEdit *edtLinkMan;
	TLabel *Label7;
	TEdit *edtTel;
	TLabel *Label8;
	TEdit *edtFax;
	TLabel *Label9;
	TEdit *edtAddr;
	TLabel *Label10;
	TEdit *edtType;
	TLabel *Label11;
	TEdit *edtArtific;
	TLabel *Label12;
	TEdit *edtRegmoney;
	TLabel *Label13;
	TEdit *edtProdAddr;
	TLabel *Label14;
	TEdit *edtAreaScale;
	TLabel *Label15;
	TLabel *Label16;
	TEdit *edtManScale;
	TLabel *Label17;
	TEdit *edtMonthCap;
	TLabel *Label18;
	TEdit *edtWorkItem;
	TLabel *Label19;
	TEdit *edtIDAffix;
	TLabel *Label20;
	TLabel *Label21;
	TEdit *edtDate0;
	TComboBox *lstStatus;
	TLabel *Label22;
	TEdit *edtDate1;
	TLabel *Label23;
	TEdit *edtPostCode;
	TLabel *Label24;
	TEdit *edtTax;
	TLabel *Label25;
	TEdit *edtBankID;
	TLabel *Label26;
	TEdit *edtBankName;
	TLabel *Label27;
	TEdit *edtBankAddr;
	TLabel *Label28;
	TEdit *edtJudge;
	TLabel *Label29;
	TEdit *edtAdvice;
	TLabel *Label30;
	TEdit *edtMail;
	TLabel *Label31;
	TMemo *memProxy;
	TButton *btnQuery;
	TButton *btnNew;
	TButton *btnEdit;
	TButton *btnMove;
	TButton *btnPrintThis;
	TButton *btnOK;
	TButton *btnExit;
	TLabel *Label32;
	TButton *btnPrintAll;
	TLabel *Label33;
	TComboBox *lstCorp;
	TLabel *Label34;
	TComboBox *lstTaxType;
	TLabel *Label35;
	TEdit *edtEndDate;
	TLabel *Label36;
	TComboBox *lstSearchCorp;
	TButton *btnCorpFresh;
	TButton *btnPickClient;
        TLabel *Label37;
        TComboBox *lstTaxType2;
	void __fastcall FormShow(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
	void __fastcall btnQueryClick(TObject *Sender);
	void __fastcall btnNewClick(TObject *Sender);
	void __fastcall btnEditClick(TObject *Sender);
	void __fastcall btnMoveClick(TObject *Sender);
	void __fastcall btnPrintThisClick(TObject *Sender);
	void __fastcall btnOKClick(TObject *Sender);
	void __fastcall btnExitClick(TObject *Sender);
	void __fastcall lstCodeClick(TObject *Sender);
	void __fastcall btnPrintAllClick(TObject *Sender);
	void __fastcall lstCorpExit(TObject *Sender);
	void __fastcall lstTaxTypeExit(TObject *Sender);
	void __fastcall lstSearchCorpExit(TObject *Sender);
	void __fastcall btnCorpFreshClick(TObject *Sender);
	void __fastcall btnPickClientClick(TObject *Sender);
        void __fastcall lstTaxType2Exit(TObject *Sender);
private:	// User declarations
	void ResetCtrl();
	void OnQuery();
	void EmptyEditor();
	bool DetectInput(CStringArray &lstProxy);
	void OnAddnew(CStringArray &lstProxy);
	void OnEdit(CStringArray &lstProxy);
	void DoPrint(LPCSTR lpszID);

	enum { EN_STATE_IDLE,EN_STATE_NEW,EN_STATE_EDIT } m_enState;
	CString m_szActiveID;
	CStringArray m_lstStatusID;

public:		// User declarations
	int m_nAuthor;
	AnsiString m_szIDFirst;
  CStringArray m_lstCorpID,m_lstSearchCorpID;
  CStringArray m_lstTaxID;
  CStringArray m_lstTaxID2;
	bool IsSameCorp();
	void RefreshIDList();

	__fastcall TFactoryForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFactoryForm *FactoryForm;
//---------------------------------------------------------------------------
#endif
