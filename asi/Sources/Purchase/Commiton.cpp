//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Commiton.h"
#include "LdyInterface.h"
#include "common.hpp"
#include "DataModule.h"
#include "BaseCode.h"
#include "const.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TCommitonForm *CommitonForm;
void Commiton(int nAuth)
{
  CALL_FORM(TCommitonForm)
}

//---------------------------------------------------------------------------
__fastcall TCommitonForm::TCommitonForm(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void TCommitonForm::clearInput(){
}

bool TCommitonForm::checkInput(){

}

void TCommitonForm::onAdd(){
}

void TCommitonForm::onMod(){

}







