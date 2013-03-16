//---------------------------------------------------------------------------

#ifndef AskPurchaseAfmListH
#define AskPurchaseAfmListH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TAskPurchaseAfmListForm : public TForm
{
__published:	// IDE-managed Components
	TLabel *Label1;
	TListView *lstView;
	TPanel *Panel1;
	TDateTimePicker *ctlTime0;
	TButton *btnExit;
	TDateTimePicker *ctlDate0;
	TLabel *Label2;
	TLabel *Label3;
	TDateTimePicker *ctlDate1;
	TDateTimePicker *ctlTime1;
	TLabel *Label4;
	TComboBox *lstDepart;
	TButton *btnToExcel;
	TButton *btnQuery;
	TButton *btnPrint;
        TButton *btnQuery0;
	void __fastcall btnExitClick(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall btnQueryClick(TObject *Sender);
	void __fastcall btnToExcelClick(TObject *Sender);
	void __fastcall btnPrintClick(TObject *Sender);
        void __fastcall btnQuery0Click(TObject *Sender);
private:	// User declarations
	CStringArray m_lstDepartID;
                             //0712

public:		// User declarations
	__fastcall TAskPurchaseAfmListForm(TComponent* Owner);
//        m_pTailHandleman=txtHandleman;                    //0712
};
//---------------------------------------------------------------------------
extern PACKAGE TAskPurchaseAfmListForm *AskPurchaseAfmListForm;
//---------------------------------------------------------------------------
#endif
