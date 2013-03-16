//---------------------------------------------------------------------------

#include <vcl.h>
#include <stdio.h>
#pragma hdrstop

#include "DataModule.h"
#include "BaseCode.h"
#include "PrnApafmNotBook.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TPrnApafmNotBookForm *PrnApafmNotBookForm;
//---------------------------------------------------------------------------
__fastcall TPrnApafmNotBookForm::TPrnApafmNotBookForm(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
