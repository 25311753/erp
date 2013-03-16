//---------------------------------------------------------------------------

#ifndef YjQryH
#define YjQryH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
class TYjQryForm : public TForm
{
__published:	// IDE-managed Components
        TPanel *plQuery;
        TButton *btnQry;
        TPanel *Panel5;
        TComboBox *cbbQryOpCodeSl;
        TPanel *Panel1;
        TComboBox *cbYear;
        TPanel *Panel2;
        TComboBox *cbMonth;
        TPanel *Panel3;
        TComboBox *cbQ;
        TListView *lvQry;
        void __fastcall btnQryClick(TObject *Sender);
        void __fastcall FormShow(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TYjQryForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TYjQryForm *YjQryForm;
//---------------------------------------------------------------------------
#endif
