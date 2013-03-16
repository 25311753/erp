//---------------------------------------------------------------------------

#ifndef ApFPListH
#define ApFPListH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TApFPListForm : public TForm
{
__published:	// IDE-managed Components
        TListView *lstView;
        TLabel *Label1;
        TPanel *Panel1;
        TButton *btnPrint;
        TButton *btnQuery;
        TButton *btnToExcel;
        TButton *btnExit;
        TLabel *Label2;
        TEdit *edtFile0;
        TLabel *Label3;
        TEdit *edtFile1;        
        void __fastcall btnExitClick(TObject *Sender);
        void __fastcall btnQueryClick(TObject *Sender);
        void __fastcall btnToExcelClick(TObject *Sender);
        void __fastcall btnPrintClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TApFPListForm(TComponent* Owner);


       	int m_nAuthor;
};
//---------------------------------------------------------------------------
extern PACKAGE TApFPListForm *ApFPListForm;
//---------------------------------------------------------------------------
#endif
