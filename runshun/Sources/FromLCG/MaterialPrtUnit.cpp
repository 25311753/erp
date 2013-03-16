//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "MaterialPrtUnit.h"
#include "DataModule.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TMaterialPrtForm *MaterialPrtForm;
//---------------------------------------------------------------------------
__fastcall TMaterialPrtForm::TMaterialPrtForm(TComponent* Owner)
   : TForm(Owner)
{
}
//---------------------------------------------------------------------------
