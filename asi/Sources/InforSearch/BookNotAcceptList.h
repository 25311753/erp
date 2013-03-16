//---------------------------------------------------------------------------

#ifndef BookNotAcceptListH
#define BookNotAcceptListH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
class TBookNotAcceptListForm : public TForm
{
__published:	// IDE-managed Components
	TLabel *Label1;
	TListView *lstView;
	TLabel *Label2;
	TEdit *edtDays;
	TButton *btnQuery;
	TButton *btnToExcel;
	TButton *btnExit;
	TLabel *Label3;
	TComboBox *lstCorp;
	TLabel *Label4;
	TComboBox *lstDepart;
	TLabel *Label5;
	TComboBox *lstFact;
	TButton *btnFactPickup;
	TLabel *Label6;
	TComboBox *lstAskDep;
        TLabel *Label7;
        TLabel *Label8;
        TDateTimePicker *DateTimePicker1;
        TDateTimePicker *DateTimePicker2;
        TButton *btnprint;
	void __fastcall FormShow(TObject *Sender);
	void __fastcall btnQueryClick(TObject *Sender);
	void __fastcall btnToExcelClick(TObject *Sender);
	void __fastcall btnExitClick(TObject *Sender);
	void __fastcall btnFactPickupClick(TObject *Sender);
        void __fastcall btnprintClick(TObject *Sender);
private:	// User declarations
	CStringArray m_lstCorpID;
	CStringArray m_lstDepartID;
	CStringArray m_lstFactID;
  CStringArray m_lstAskDepID;

public:		// User declarations
	__fastcall TBookNotAcceptListForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TBookNotAcceptListForm *BookNotAcceptListForm;
//---------------------------------------------------------------------------
#endif
