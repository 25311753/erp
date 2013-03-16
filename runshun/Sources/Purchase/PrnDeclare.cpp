//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "PrnDeclare.h"

#include "DataModule.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TPrnDeclareForm *PrnDeclareForm;
//---------------------------------------------------------------------------
__fastcall TPrnDeclareForm::TPrnDeclareForm(TComponent* Owner)
        : TForm(Owner)
{
//        m_nColOrd = 1;
//        m_nStep = 0;
}
//---------------------------------------------------------------------------
void __fastcall TPrnDeclareForm::DetailBand1BeforePrint(
      TQRCustomBand *Sender, bool &PrintBand)
{
//        ShowMessage("bfp");
//        qrl_col_ord->Caption = AnsiString(m_nStep + m_nColOrd++);
}
//---------------------------------------------------------------------------




