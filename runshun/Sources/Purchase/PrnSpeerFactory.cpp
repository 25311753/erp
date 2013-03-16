//---------------------------------------------------------------------------

#include <vcl.h>
#include <stdio.h>
#pragma hdrstop

#include "BaseCode.h"
#include "PrnSpeerFactory.h"
#include "DataModule.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TPrnSpeerFactoryForm *PrnSpeerFactoryForm;
//---------------------------------------------------------------------------
__fastcall TPrnSpeerFactoryForm::TPrnSpeerFactoryForm(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TPrnSpeerFactoryForm::pd_codePrint(TObject *sender,
      AnsiString &Value)
{
/*
	char strID[80];
  strcpy(strID,Value.c_str());
  if(strID[0]!='\0')
  {
  	Value=strID+strlen(strID)-1;
  }
*/
}
//---------------------------------------------------------------------------

void __fastcall TPrnSpeerFactoryForm::QRSubDetail1BeforePrint(
      TQRCustomBand *Sender, bool &PrintBand)
{
	CStringArray lstLine;

  AnsiString szName=pd_code->DataSet->FieldByName("mn_name")->AsString
  	+pd_code->DataSet->FieldByName("mn_usage")->AsString;
	SplitStrToLines(szName.c_str(),50,lstLine);
	if(lstLine.GetSize()>=2)
	{
		txtName0->Caption=(LPCSTR)lstLine[0];
		txtName1->Caption=(LPCSTR)lstLine[1];
	}
        else
        {
              txtName0->Caption=(LPCSTR)lstLine[0];
              txtName1->Caption="";
        }
  if(pd_code->DataSet->FieldByName("ap_buytype")->AsString!="M")
  	txtSpeerTax->Caption="___________";
}
//---------------------------------------------------------------------------







