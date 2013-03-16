//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "PrnFactory.h"
#include "DataModule.h"
#include "BaseCode.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TPrnFactoryForm *PrnFactoryForm;
//---------------------------------------------------------------------------
__fastcall TPrnFactoryForm::TPrnFactoryForm(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TPrnFactoryForm::PageHeaderBand1BeforePrint(
      TQRCustomBand *Sender, bool &PrintBand)
{
	char strID[80];
	TQRLabel *pProxy[8];
  CString szSQL;
  int i;

	pProxy[0]=txtProxy1;
	pProxy[1]=txtProxy2;
	pProxy[2]=txtProxy3;
	pProxy[3]=txtProxy4;
	pProxy[4]=txtProxy5;
	pProxy[5]=txtProxy6;
	pProxy[6]=txtProxy7;
	pProxy[7]=txtProxy8;

	strcpy(strID,mf_code->DataSet->FieldByName("mf_code")->AsString.c_str());
	szSQL.Format("select * from FactoryProxy where fp_mfcode='%s'",strID);
	RunSQL(dm1->Query1,szSQL,true);
  i=0;
  while(!dm1->Query1->Eof && i<8)
  {
  	pProxy[i]->Caption=dm1->Query1->FieldByName("fp_proxy")->AsString;
  	i++;
  	dm1->Query1->Next();
  }
  for(;i<8;i++)
  {
  	pProxy[i]->Caption="";
  }
}
//---------------------------------------------------------------------------

