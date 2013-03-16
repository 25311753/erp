//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "DataModule.h"
#include "BaseCode.h"
#include "PrnAskPurchase.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TPrnAskPurchaseForm *PrnAskPurchaseForm;
//---------------------------------------------------------------------------
__fastcall TPrnAskPurchaseForm::TPrnAskPurchaseForm(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TPrnAskPurchaseForm::pd_codePrint(TObject *sender,
      AnsiString &Value)
{
	char strItem[80];
  strcpy(strItem,Value.c_str());
  if(strItem[0]!='\0')
		Value=strItem+strlen(strItem)-1;
}
//---------------------------------------------------------------------------

void __fastcall TPrnAskPurchaseForm::QRDBText6Print(TObject *sender,
      AnsiString &Value)
{
	CStringArray lstLine;
  Value+= "  " + pd_code->DataSet->FieldByName("mn_usage")->AsString;
	SplitStrToLines(Value.c_str(),52,lstLine);
	if(lstLine.GetSize()>=2)
	{
		Value=(LPCSTR)lstLine[0];
		txtSpec1->Caption=(LPCSTR)lstLine[1];
	}
}
//---------------------------------------------------------------------------

void __fastcall TPrnAskPurchaseForm::DetailBand1BeforePrint(
      TQRCustomBand *Sender, bool &PrintBand)
{
	CStringArray lstLine;
  char strTemp[512],strTS[80],strPrice[80],strSQL[1024];

	txtSpec1->Caption="";
//  txtCooper1->Caption="";
	if(!txtTreat0->Caption.IsEmpty())
	{
  	strcpy(strTemp,pd_code->DataSet->FieldByName("pd_cooper")->AsString.c_str());
		SplitStrToLines(strTemp,30,lstLine);
    if(lstLine.GetSize()==0)
    {
    	txtCooper0->Caption="";
      txtCooper1->Caption="";
    }
    else if(lstLine.GetSize()==1)
    {
			txtCooper0->Caption=(LPCSTR)lstLine[0];
      txtCooper1->Caption="";
    }
    else
    {
    	txtCooper0->Caption=(LPCSTR)lstLine[0];
      txtCooper1->Caption=(LPCSTR)lstLine[1];
    }
	}
  else
  {
		strcpy(strTS,pd_code->DataSet->FieldByName("pd_tscode")->AsString.c_str());
    if(strTS[0]=='\0')
    {
    	txtCooper0->Caption=strTS;
      txtCooper1->Caption="";
    }                        
    else
    {
    	sprintf(strSQL,"select * from TreatStock,Manufactur where mf_code=ts_mfcode and ts_code='%s'",strTS);
      RunSQL(dm1->Query1,strSQL,true);
//			strcpy(strPrice,FloatField2String(dm1->Query1->FieldByName("ts_price"),2).c_str());
			strcpy(strPrice,FloatField2String(dm1->Query1->FieldByName("ts_price"),8).c_str());
      sprintf(strTemp,"%-20s%s",strTS,strPrice);
      txtCooper0->Caption=strTemp;
      txtCooper1->Caption=dm1->Query1->FieldByName("mf_shortname")->AsString;
    }
  }
  if(!pd_code->DataSet->FieldByName("mn_rem")->IsNull)
  {
    strcpy(strTemp,pd_code->DataSet->FieldByName("pd_code")->AsString.c_str());
    m_lstRemID.Add(strTemp[strlen(strTemp)-1]);
  }
}
//---------------------------------------------------------------------------

void __fastcall TPrnAskPurchaseForm::QRDBText5Print(TObject *sender,
      AnsiString &Value)
{
	CStringArray lstLine;
	SplitStrToLines(Value.c_str(),30,lstLine);
	if(lstLine.GetSize()>=2)
	{
		Value=(LPCSTR)lstLine[0];
		txtCooper1->Caption=(LPCSTR)lstLine[1];
	}
}
//---------------------------------------------------------------------------

void __fastcall TPrnAskPurchaseForm::PrnViewBeforePrint(
      TCustomQuickRep *Sender, bool &PrintReport)
{
TPrinter *pnt = Printer();
int xInch=GetDeviceCaps(pnt->Handle,LOGPIXELSX);//1Inch=25.4mm
int yInch=GetDeviceCaps(pnt->Handle,LOGPIXELSY);
float xMM,yMM;//x,y方向1厘米的??
xMM=(float)xInch/25.4;
yMM=(float)yInch/25.4;

//?置??大小

char Device[CCHDEVICENAME];
char Driver[MAX_PATH];
char Port[32];
THandle  hDMode;
PDevMode  pDMode;
pnt->GetPrinter(Device,Driver,Port,hDMode);
pDMode=(PDevMode)GlobalLock((HGLOBAL &)hDMode);

pDMode->dmPaperSize= 0;    //自定?
pDMode->dmFields=pDMode->dmFields|DM_PAPERSIZE;

pDMode->dmPaperLength =2035;  //高：4英寸=101.6mm
pDMode->dmFields =pDMode->dmFields|DM_PAPERLENGTH;

pDMode->dmPaperWidth = 2970;  //?：10英寸=25.40mm
pDMode->dmFields =pDMode->dmFields|DM_PAPERWIDTH;

ResetDC(pnt->Handle,pDMode);
GlobalUnlock((HGLOBAL &)hDMode);
pnt->Refresh();

pnt->GetPrinter(Device,Driver,Port,hDMode);
pDMode=(PDevMode)GlobalLock((HGLOBAL &)hDMode);

pDMode->dmPaperSize= 0;    //自定?
pDMode->dmFields=pDMode->dmFields|DM_PAPERSIZE;

pDMode->dmPaperLength =2035;  //高：4英寸=101.6mm
pDMode->dmFields =pDMode->dmFields|DM_PAPERLENGTH;

pDMode->dmPaperWidth = 2970;  //?：10英寸=25.40mm
pDMode->dmFields =pDMode->dmFields|DM_PAPERWIDTH;

ResetDC(pnt->Handle,pDMode);
GlobalUnlock((HGLOBAL &)hDMode);
pnt->Refresh();
}
//---------------------------------------------------------------------------

void __fastcall TPrnAskPurchaseForm::PageFooterBand1BeforePrint(
      TQRCustomBand *Sender, bool &PrintBand)
{
	char strRem[256],strTemp[80];
  int i;

  if(m_lstRemID.GetSize()==0)	strRem[0]='\0';
  else
  {
  	sprintf(strRem,"请列印材料产品规范：%s",m_lstRemID[0]);
    if(i>0)
      {
        i=m_lstRemID.GetSize()-1;
        sprintf(strTemp,"~%s",m_lstRemID[i]);
        strcat(strRem,strTemp);
      }
    /*for(i=1;i<m_lstRemID.GetSize();i++)
    {
    	sprintf(strTemp,",%s",m_lstRemID[i]);
      strcat(strRem,strTemp);
    }
  }    */
  }
  txtPrnRem->Caption=strRem;
}
//---------------------------------------------------------------------------


