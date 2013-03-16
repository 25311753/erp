//---------------------------------------------------------------------------

#ifndef CalcH
#define CalcH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
class TCalcForm : public TForm
{
__published:	// IDE-managed Components
        TLabel *Label1;
        TEdit *edtCid;
        TLabel *Label2;
        TEdit *edtBaseFree;
        TButton *btnMod;
        TButton *btnQuery;
        TListView *lstView;
private:	// User declarations
public:		// User declarations
        __fastcall TCalcForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TCalcForm *CalcForm;
//---------------------------------------------------------------------------
#endif
