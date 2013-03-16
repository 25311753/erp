//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "YjCSSZ.h"


#include "LdyInterface.h"
#include "common.hpp"
#include "DataModule.h"
#include "BaseCode.h"
#include "const.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TYjCSSZForm *YjCSSZForm;

void YjCSSZ(int nAuth)
{
  CALL_FORM(TYjCSSZForm);
}
//---------------------------------------------------------------------------
__fastcall TYjCSSZForm::TYjCSSZForm(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
