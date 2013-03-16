//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "DataModule.h"
#include "BaseCode.h"
#include "PrnMaterial.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TPrnMaterialForm *PrnMaterialForm;
//---------------------------------------------------------------------------
__fastcall TPrnMaterialForm::TPrnMaterialForm(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TPrnMaterialForm::QRSubDetail1BeforePrint(
      TQRCustomBand *Sender, bool &PrintBand)
{
     	QRMemo1->Caption=cp_name->DataSet->FieldByName("mn_rem")->AsString;
}
//---------------------------------------------------------------------------

void __fastcall TPrnMaterialForm::DetailBand1BeforePrint(
      TQRCustomBand *Sender, bool &PrintBand)
{
  	AnsiString szRem=cp_name->DataSet->FieldByName("mn_rem")->AsString;
  CStringArray lstLine;
  int i;
  QRMemo1->Lines->Clear();

  SplitLine(szRem.c_str(),lstLine);
  for(i=0;i<lstLine.GetSize();i++)
  {
  	QRMemo1->Lines->Add((LPCSTR)lstLine[i]);
  }
   //	QRMemo1->Text=cp_name->DataSet->FieldByName("mn_rem")->AsString;
}
//---------------------------------------------------------------------------




