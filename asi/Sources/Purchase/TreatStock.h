//---------------------------------------------------------------------------

#ifndef TreadStockH
#define TreadStockH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
class TTreatStockForm : public TForm
{
__published:	// IDE-managed Components
	TLabel *Label1;
	TLabel *Label2;
	TEdit *edtMater;
	TButton *btnPickup;
	TLabel *Label3;
	TComboBox *lstFact;
	TLabel *Label4;
	TEdit *edtSpec;
	TLabel *Label5;
	TEdit *edtCard;
	TLabel *Label6;
	TComboBox *lstUnit;
	TLabel *Label7;
	TEdit *edtPrice;
	TLabel *Label8;
	TEdit *edtDays;
	TLabel *Label9;
	TComboBox *lstHandle;
	TLabel *Label10;
	TEdit *edtInpdate;
	TLabel *Label11;
	TEdit *edtEditdate;
	TButton *btnQuery;
	TButton *btnNew;
	TButton *btnEdit;
	TButton *btnMove;
	TButton *btnOK;
	TButton *btnExit;
	TLabel *Label12;
	TEdit *edtInuredate;
	TLabel *Label13;
	TEdit *edtID;
	TLabel *Label14;
	TComboBox *lstDepart;
	TLabel *Label15;
	TEdit *edtAfmDate;
	TLabel *Label16;
	TEdit *edtAfmDate2;
	TButton *btnPickFact;
        TLabel *Label17;
	void __fastcall btnExitClick(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall btnQueryClick(TObject *Sender);
	void __fastcall btnNewClick(TObject *Sender);
	void __fastcall btnEditClick(TObject *Sender);
	void __fastcall btnMoveClick(TObject *Sender);
	void __fastcall btnOKClick(TObject *Sender);
	void __fastcall btnPickupClick(TObject *Sender);
	void __fastcall lstFactExit(TObject *Sender);
	void __fastcall lstUnitExit(TObject *Sender);
	void __fastcall lstHandleExit(TObject *Sender);
	void __fastcall edtMaterExit(TObject *Sender);
	void __fastcall btnPrintClick(TObject *Sender);
	void __fastcall btnPickFactClick(TObject *Sender);
private:	// User declarations
	enum { EN_STATE_NEW,EN_STATE_EDIT,EN_STATE_IDLE } m_enState;

	void ResetCtrl();
	bool CheckInput();
	AnsiString GenerateID();
	AnsiString GenModifyFlowID();

public:		// User declarations
	int m_nAuthor;
	AnsiString m_szIDFirst;

	CStringArray m_lstFactID;
	CStringArray m_lstUnitID;
	CStringArray m_lstHandleID;
	CStringArray m_lstDepartID;
	CString m_szActiveID;

	TDateTime m_tOperTime;

	__fastcall TTreatStockForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TTreatStockForm *TreatStockForm;
//---------------------------------------------------------------------------
#endif
