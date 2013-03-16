//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Calc.h"
#include "DataModule.h"
#include "BaseCode.h"
#include "LdyInterface.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TCalcForm *CalcForm;
//---------------------------------------------------------------------------
void Calc(int nAuth)
{
        CALL_FORM(TCalcForm);
}
__fastcall TCalcForm::TCalcForm(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
