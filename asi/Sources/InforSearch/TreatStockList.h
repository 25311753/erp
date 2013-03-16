//---------------------------------------------------------------------------

#ifndef TreatStockListH
#define TreatStockListH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TTreatStockListForm : public TForm
{
__published:	// IDE-managed Components
	TLabel *Label1;
	TPageControl *ctlPage;
	TTabSheet *ctlCurrent;
	TListView *lstView;
	TTabSheet *ctlModify;
	TPanel *ctlPane;
	TLabel *Label2;
	TLabel *Label3;
	TLabel *Label4;
	TLabel *Label5;
	TEdit *edtID;
	TEdit *edtMater;
	TButton *btnPickup;
	TComboBox *lstFact;
	TComboBox *lstHandle;
	TButton *btnToExcel;
	TButton *btnDetail;
	TButton *btnQuery;
	TButton *btnExit;
	TListView *lstModify;
	TTabSheet *ctlHistory;
	TListView *lstHistory;
	TLabel *Label6;
	TComboBox *lstDepart;
	TButton *btnFactPickup;
	TLabel *Label7;
	TComboBox *lstDateType;
	TEdit *edtDate;
        TButton *Button1;
	void __fastcall btnPickupClick(TObject *Sender);
	void __fastcall btnDetailClick(TObject *Sender);
	void __fastcall btnToExcelClick(TObject *Sender);
	void __fastcall btnExitClick(TObject *Sender);
	void __fastcall lstViewClick(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall btnQueryClick(TObject *Sender);
	void __fastcall lstViewSelectItem(TObject *Sender, TListItem *Item,
          bool Selected);
	void __fastcall lstViewDblClick(TObject *Sender);
	void __fastcall lstFactExit(TObject *Sender);
	void __fastcall lstHandleExit(TObject *Sender);
	void __fastcall btnFactPickupClick(TObject *Sender);
	void __fastcall ctlCurrentShow(TObject *Sender);
	void __fastcall ctlModifyShow(TObject *Sender);
	void __fastcall ctlHistoryShow(TObject *Sender);
        void __fastcall Button1Click(TObject *Sender);
private:	// User declarations
	CStringArray m_lstFactID;
	CStringArray m_lstHandleID;
	CStringArray m_lstDepartID;

	void ResetCtrl();

public:		// User declarations
	__fastcall TTreatStockListForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TTreatStockListForm *TreatStockListForm;
//---------------------------------------------------------------------------
#endif
