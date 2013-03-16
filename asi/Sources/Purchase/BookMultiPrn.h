//---------------------------------------------------------------------------

#ifndef BookMultiPrnH
#define BookMultiPrnH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
class TBookMultiPrnForm : public TForm
{
__published:	// IDE-managed Components
	TListView *lstView;
	TLabel *Label1;
	TComboBox *lstFactory;
	TLabel *Label2;
	TEdit *edtDate0;
	TLabel *Label4;
	TButton *btnQuery;
	TButton *btnPrint;
	TButton *btnExit;
	TButton *btnDetail;
	TLabel *Label3;
	TComboBox *lstStockHandle;
	TLabel *Label5;
	TComboBox *lstCorp;
	TButton *btnPickup;
	TLabel *Label6;
	TEdit *edtDate1;
        TLabel *Label7;
        TComboBox *ComboBox1;
	void __fastcall FormShow(TObject *Sender);
	void __fastcall btnExitClick(TObject *Sender);
	void __fastcall btnQueryClick(TObject *Sender);
	void __fastcall btnPrintClick(TObject *Sender);
	void __fastcall btnDetailClick(TObject *Sender);
	void __fastcall lstFactoryExit(TObject *Sender);
	void __fastcall lstViewDblClick(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
	void __fastcall btnPickupClick(TObject *Sender);
	void __fastcall lstStockHandleExit(TObject *Sender);
	void __fastcall lstCorpExit(TObject *Sender);
private:	// User declarations
	CStringArray m_lstFactID;
	CStringArray m_lstCorpID;
	CStringArray m_lstHandleID;
	CString m_szFactID;
	AnsiString m_szDate;
        CStringArray  m_lstFactID1;
	void ResetFactList();

public:		// User declarations
	__fastcall TBookMultiPrnForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TBookMultiPrnForm *BookMultiPrnForm;
//---------------------------------------------------------------------------
#endif
