//---------------------------------------------------------------------------

#include <vcl.h>
#include <stdio.h>
#include <assert.h>
#pragma hdrstop

#include "DataModule.h"
#include "BaseCode.h"
#include "PrnBookFactory.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TPrnBookFactoryForm *PrnBookFactoryForm;
//---------------------------------------------------------------------------
__fastcall TPrnBookFactoryForm::TPrnBookFactoryForm(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TPrnBookFactoryForm::bf_codePrint(TObject *sender,
      AnsiString &Value)
{
//	char strID[80];
//  strcpy(strID,Value.c_str());
//  if(strID[0]!='\0')
//	{
//  	Value=strID+strlen(strID)-1;
//  }
}
//---------------------------------------------------------------------------
void __fastcall TPrnBookFactoryForm::DetailBand1BeforePrint(
      TQRCustomBand *Sender, bool &PrintBand)
{
	char strMN[80],strKind[80],strApcode[80];
  strcpy(strMN,bf_code->DataSet->FieldByName("mn_code")->AsString.c_str());
  strcpy(strApcode,bf_code->DataSet->FieldByName("pd_code")->AsString.c_str());

  if(strMN[0]=='E' && strMN[1]=='M')
  {
  	bf_price->Mask="#,##0.000000;; ";
  }
  else
//  	bf_price->Mask="#,##0.0000;; ";
  {
        if (strApcode[0]=='P')
        {//一般请购
          	bf_price->Mask="#,##0.0000;; ";
        }
        else if (strApcode[0]=='Q')
        {//统购
  	        bf_price->Mask="#,##0.00000000;; ";
        }
  }
	if(!bf_code->DataSet->FieldByName("bf_price")->IsNull
  	&& !bf_code->DataSet->FieldByName("bf_count")->IsNull)
  {
  	double fPrice,fCount;
    char strMoney[80];

    fPrice=bf_code->DataSet->FieldByName("bf_price")->AsFloat;
    fCount=bf_code->DataSet->FieldByName("bf_count")->AsFloat;
//    sprintf(strMoney,"%.2f",fPrice*fCount);
  if(strMN[0]=='E' && strMN[1]=='M')
  {
    sprintf(strMoney,"%.2f",fPrice*fCount);
  }
  else
  {
        if (strApcode[0]=='P')
        {
                sprintf(strMoney,"%.2f",fPrice*fCount);     //提高精度
        }
        else if (strApcode[0]=='Q')
        {
                sprintf(strMoney,"%.8f",fPrice*fCount);     //提高精度
        }
  }
    BookMoney->Caption=(LPCSTR)AddComma(strMoney);
//    BookMoney->Caption=FloatToStr(fPrice*fCount);
  }
  else	BookMoney->Caption="";

  char strTemp[256];
  CString szSQL;
  strcpy(strTemp,bf_code->DataSet->FieldByName("bf_dccode")->AsString.c_str());
	if(strTemp[0]=='\0')	txtRMB->Caption="";
  else
  {
  	szSQL.Format("select * from diccurrency where dc_code='%s'",strTemp);
    RunSQL(dm1->Query1,szSQL,true);
		txtRMB->Caption=dm1->Query1->FieldByName("dc_name")->AsString;
  }

  strcpy(strKind,bf_code->DataSet->FieldByName("bf_buykind")->AsString.c_str());
  switch(strKind[0])
  {
  	case 'A':
    	txtKind0->Caption="一般";
      txtKind1->Caption="贸易";
      break;
    case 'B':
    	txtKind0->Top=10;
      txtKind0->Caption="保税";
      txtKind1->Caption="";;
      txtKind1->Top=100;
      break;
    case 'C':
    	txtKind0->Top=10;
      txtKind0->Caption="核销";
      txtKind1->Caption="";;
      txtKind1->Top=100;
      break;
    default:
    	txtKind0->Caption="";
      txtKind1->Caption="";
      break;
  }
}
//---------------------------------------------------------------------------

void __fastcall TPrnBookFactoryForm::QRDBText2Print(TObject *sender,AnsiString &Value)
{
	CStringArray lstLine;
	//把一字符串分解成多行,width 为每行字数
	SplitStrToLines(Value.c_str(),36,lstLine);
  if(lstLine.GetSize()>=2)
  {
  	Value=(LPCSTR)lstLine[0];
    txtName2->Caption=(LPCSTR)lstLine[1];
  }
  else
  {
  	txtName2->Caption="";
  }
}
//---------------------------------------------------------------------------







