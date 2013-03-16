//---------------------------------------------------------------------------

#include <vcl.h>
#include <stdio.h>
#pragma hdrstop

#include "DataModule.h"
#include "BaseCode.h"
#include "PrnBookNotAccept.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TPrnBookNotAcceptForm *PrnBookNotAcceptForm;
//---------------------------------------------------------------------------
__fastcall TPrnBookNotAcceptForm::TPrnBookNotAcceptForm(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
