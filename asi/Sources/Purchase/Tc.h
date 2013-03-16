//---------------------------------------------------------------------------

#ifndef TcH
#define TcH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
class TTcForm : public TForm
{
__published:	// IDE-managed Components
        TPanel *plQuery;
        TButton *btnQry;
        TPanel *Panel5;
        TComboBox *cbbQryOpCodeSl;
        TPanel *Panel1;
        TComboBox *cbYear;
        TPanel *Panel3;
        TComboBox *cbQ;
        TPanel *Panel2;
        TComboBox *cbMonth;
        TListView *lvQry;
        void __fastcall FormShow(TObject *Sender);
        void __fastcall btnQryClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TTcForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TTcForm *TcForm;
//---------------------------------------------------------------------------
#endif
