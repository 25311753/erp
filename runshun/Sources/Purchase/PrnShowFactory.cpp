//---------------------------------------------------------------------------

#include <vcl.h>
#include <stdio.h>
#pragma hdrstop

#include "DataModule.h"
#include "BaseCode.h"
#include "PrnShowFactory.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TPrnShowFactoryForm *PrnShowFactoryForm;
//---------------------------------------------------------------------------
__fastcall TPrnShowFactoryForm::TPrnShowFactoryForm(TComponent* Owner)
	: TForm(Owner)
{
	m_pTailDate [0] =TailDate0;
	m_pTailDate [1] =TailDate1;
	m_pTailDate [2] =TailDate2;
	m_pTailDate [3] =TailDate3;

	m_pTailFact [0] =TailFact0;
	m_pTailFact [1] =TailFact1;
	m_pTailFact [2] =TailFact2;
	m_pTailFact [3] =TailFact3;

	m_pTailPrice[0] =TailPrice0;
	m_pTailPrice[1] =TailPrice1;
	m_pTailPrice[2] =TailPrice2;
	m_pTailPrice[3] =TailPrice3;

	m_pTailRmb[0] =txtRMB0;
	m_pTailRmb[1] =txtRMB1;
	m_pTailRmb[2] =txtRMB2;
	m_pTailRmb[3] =txtRMB3;

	m_pTailPDCode[0]=txtPDCode0;
	m_pTailPDCode[1]=txtPDCode1;
	m_pTailPDCode[2]=txtPDCode2;
	m_pTailPDCode[3]=txtPDCode3;

  m_pTailNum[0]=txtTailNum0;
  m_pTailNum[1]=txtTailNum1;
  m_pTailNum[2]=txtTailNum2;
  m_pTailNum[3]=txtTailNum3;

//------new 0712----------------------------------------------------------------
        m_pTailPDMf[0]=txtPDMf0;
        m_pTailPDMf[1]=txtPDMf1;
        m_pTailPDMf[2]=txtPDMf2;
        m_pTailPDMf[3]=txtPDMf3;
//------------------------------------------------------------------------------
}
//---------------------------------------------------------------------------

void __fastcall TPrnShowFactoryForm::QRSubDetail1BeforePrint(
      TQRCustomBand *Sender, bool &PrintBand)
{
	PM_NAME1->Caption="";
	dd_name1->Caption="";
  txtOrder->Caption=IntToStr(m_nOrder);
  CStringArray lstRem;
  double fMoney;
  char strTemp[80];

  if(pd_code->DataSet->FieldByName("m_mfplan")->AsString==pd_code->DataSet->FieldByName("m_cfmfcode")->AsString)
  {
		PlanMF->Caption=txtOrder->Caption;
    fMoney=pd_code->DataSet->FieldByName("m_dfcount")->AsFloat
    	*pd_code->DataSet->FieldByName("m_hgprice")->AsFloat;
    sprintf(strTemp,"%.2f",fMoney);
		PlanMoney->Caption=(LPCSTR)AddComma(strTemp);
    sprintf(strTemp,"%.1f",pd_code->DataSet->FieldByName("m_dfcount")->AsFloat);
    txtShowNum->Caption=strTemp;
		EndDate->Caption=DateField2Text(pd_code->DataSet->FieldByName("m_dfvalidate"));    

		SplitStrToLines(pd_code->DataSet->FieldByName("m_planrem")->AsString.c_str(),60,lstRem);
		switch(lstRem.GetSize())
		{
			case 0:	PlanRem0->Caption="";	PlanRem1->Caption="";	break;
			case 1:	PlanRem0->Caption=(LPCSTR)lstRem[0];	PlanRem1->Caption="";	break;
			default:PlanRem0->Caption=(LPCSTR)lstRem[0];	PlanRem1->Caption=(LPCSTR)lstRem[1];	break;
		}
  }

  m_nOrder++;

	CStringArray lstLine;
  AnsiString szDDName;
	BASE2COLDATA rwData;
  CString szSQL;
  int i;

  szDDName=pd_code->DataSet->FieldByName("m_dltype")->AsString;
	SplitStrToLines(szDDName.c_str(),24,lstLine);
  switch(lstLine.GetSize())
  {
  	case 0:	dd_name->Caption="";				dd_name1->Caption="";	break;
    case 1:	dd_name->Caption=szDDName;	dd_name1->Caption="";	break;
    default:
    	dd_name	->Caption=(LPCSTR)lstLine[0];
      dd_name1->Caption=(LPCSTR)lstLine[1];
      break;
  }

  AnsiString szTax,szTax2;
	if(!pd_code->DataSet->FieldByName("m_invoice")->IsNull)
  {
  	szTax=pd_code->DataSet->FieldByName("m_invoice")->AsString;
    lstLine.RemoveAll();
		SplitStrToLines(szTax.c_str(),7,lstLine);
    if(lstLine.GetSize()>=2)
    {
    	szTax=(LPCSTR)lstLine[0];
      szTax2=(LPCSTR)lstLine[1];
    }
  }
  else
  {
    if(!pd_code->DataSet->FieldByName("m_taxtype")->IsNull)
    {
	    szTax=FloatToStr(pd_code->DataSet->FieldByName("m_taxtype")->AsFloat);
    }
  }
  txtTax->Caption=szTax;
  txtTax2->Caption=szTax2;

  AnsiString szFact,szFact2;
 	szFact=pd_code->DataSet->FieldByName("m_mfname")->AsString;
  lstLine.RemoveAll();
	SplitStrToLines(szFact.c_str(),18,lstLine);
  switch(lstLine.GetSize())
 	{
 		case 0:	txtFact1->Caption="";				txtFact2->Caption="";	break;
   	case 1:	txtFact1->Caption=(LPCSTR)lstLine[0];	txtFact2->Caption="";	break;
   	default:
   		txtFact1->Caption=(LPCSTR)lstLine[0];
     	txtFact2->Caption=(LPCSTR)lstLine[1];
     	break;
  }
}
//---------------------------------------------------------------------------

void __fastcall TPrnShowFactoryForm::PageHeaderBand1BeforePrint(
      TQRCustomBand *Sender, bool &PrintBand)
{
	m_nOrder=1;
}
//---------------------------------------------------------------------------

void __fastcall TPrnShowFactoryForm::QRDBText11Print(TObject *sender,
      AnsiString &Value)
{
	CStringArray lstLine;

  CString szSQL,szSQL1;
  char strTemp[256];

  strTemp[0]='\0';
//        szSQL1.Format("select * from DecideFactory where df_apcode='%s' and df_mfplan='%s'",pd_code->DataSet->FieldByName("m_pdcode")->AsString.c_str(),pd_code->DataSet->FieldByName("m_")->AsString.c_str());

        if(pd_code->DataSet->FieldByName("m_mfplan")->AsString==pd_code->DataSet->FieldByName("m_cfmfcode")->AsString)
        strcpy(strTemp,pd_code->DataSet->FieldByName("m_dfpricert")->AsString.c_str());
  Value+=strTemp;

	SplitStrToLines(Value.c_str(),30,lstLine);
  switch(lstLine.GetSize())
  {
  	case 0:	Value="";	PM_NAME1->Caption="";	break;
    case 1:PM_NAME1->Caption="";	break;
    default:
    	Value=(LPCSTR)lstLine[0];
      PM_NAME1->Caption=(LPCSTR)lstLine[1];
      break;

  }
}
//---------------------------------------------------------------------------

static CStringArray s_lstMNCode;

void __fastcall TPrnShowFactoryForm::QRGroup1BeforePrint(
      TQRCustomBand *Sender, bool &PrintBand)
{
	CString szSQL;

  szSQL.Format("select *"
  	" from PurchaseDetail,materialno,DicUnits"
    " where pd_mncode=mn_code"
    " and pd_ducode=du_code"
    " and pd_code='%s'",pd_code->DataSet->FieldByName("m_pdcode")->AsString.c_str());
  RunSQL(dm1->Query1,szSQL,true);
  if(dm1->Query1->Eof)	return;

  txtMNCode->Caption=dm1->Query1->FieldByName("mn_code")->AsString;
  txtMNName->Caption=dm1->Query1->FieldByName("mn_name")->AsString;
  txtMNUsage->Caption=dm1->Query1->FieldByName("mn_usage")->AsString;
  txtUnit->Caption=dm1->Query1->FieldByName("du_name")->AsString;
  txtPDNumber->Caption=dm1->Query1->FieldByName("pd_count")->AsString;

  s_lstMNCode.Add(txtMNCode->Caption.c_str());
}
//---------------------------------------------------------------------------

void __fastcall TPrnShowFactoryForm::PageFooterBand1BeforePrint(
      TQRCustomBand *Sender, bool &PrintBand)
{
	char strCode[80];
	int i;
  CString szSQL;
  static int s_nPage=0;                                                         //静态局部变量

  if(s_nPage>=s_lstMNCode.GetSize())	return;
  strcpy(strCode,s_lstMNCode[s_nPage]);
  s_nPage++;
//  strcpy(strCode,txtMNCode->Caption.c_str());
	if(strCode[0]=='\0')	return;

//------------------------------------------------------------------------------
	szSQL.Format("select bf_bookdate,bf_code,bf_apcode,mf_shortname,bf_mfcard,bf_count,bf_price,bf_dccode"
		" from BookFactory,Manufactur,PurchaseDetail,codecheck"
		" where bf_mfcode=mf_code and bf_apcode=pd_code and pd_mncode='%s'"
		" union"
		" select bf_bookdate,bf_code,bf_apcode,mf_shortname,bf_mfcard,bf_count,bf_price,bf_dccode"
		" from BookFactory,Manufactur,TreatStock,codecheck"
		" where bf_mfcode=mf_code and bf_apcode=ts_code and ts_mncode='%s'"
                " union"
                " select bf_bookdate,bf_code,bf_apcode,mf_shortname,bf_mfcard,bf_count,bf_price,bf_dccode"
		" from BookFactory,Manufactur,PurchaseDetail,codecheck"
		" where bf_mfcode=mf_code and bf_apcode=pd_code and pd_mncode=cc_ocode and cc_ncode='%s'"
                " union"
		" select bf_bookdate,bf_code,bf_apcode,mf_shortname,bf_mfcard,bf_count,bf_price,bf_dccode"
		" from BookFactory,Manufactur,TreatStock,codecheck"
		" where bf_mfcode=mf_code and bf_apcode=ts_code and ts_mncode=cc_ocode and cc_ncode='%s'"
	        " order by bf_bookdate desc",strCode,strCode,strCode,strCode);
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
/*	szSQL.Format("select bf_bookdate,bf_code,bf_apcode,mf_shortname,bf_mfcard,bf_count,bf_price,bf_dccode"
		" from BookFactory,Manufactur,PurchaseDetail"
		" where bf_mfcode=mf_code and bf_apcode=pd_code and pd_mncode='%s'"
		" union"
		" select bf_bookdate,bf_code,bf_apcode,mf_shortname,bf_mfcard,bf_count,bf_price,bf_dccode"
		" from BookFactory,Manufactur,TreatStock"
		" where bf_mfcode=mf_code and bf_apcode=ts_code and ts_mncode='%s'"
		" order by bf_bookdate desc",strCode,strCode);  */
//------------------------------------------------------------------------------
	RunSQL(dm1->Query1,szSQL,true);
	i=0;
	while(!dm1->Query1->Eof && i<4)
	{
		m_pTailDate		[i]->Caption=DateField2Text(dm1->Query1->FieldByName("bf_bookdate"));
		m_pTailPDCode	[i]->Caption=dm1->Query1->FieldByName("bf_apcode")->AsString;
                m_pTailPDMf[i]->Caption=dm1->Query1->FieldByName("bf_mfcard")->AsString;         // 0712
		m_pTailFact		[i]->Caption=dm1->Query1->FieldByName("mf_shortname")->AsString;
    if(strCode[0]=='E' && strCode[1]=='M')
			m_pTailPrice[i]->Caption=FloatField2String(dm1->Query1->FieldByName("bf_price"),6);
    else
			m_pTailPrice[i]->Caption=FloatField2String(dm1->Query1->FieldByName("bf_price"),3);
    m_pTailRmb[i]->Caption=dm1->Query1->FieldByName("bf_dccode")->AsString;
    m_pTailNum[i]->Caption=dm1->Query1->FieldByName("bf_count")->AsString;

		i++;
		dm1->Query1->Next();
	}
	for(;i<4;i++)
	{
		m_pTailDate		[i]->Caption="";
		m_pTailPDCode	[i]->Caption="";
                m_pTailPDMf[i]->Caption="";
		m_pTailFact		[i]->Caption="";
		m_pTailPrice	[i]->Caption="";
    m_pTailRmb		[i]->Caption="";
    m_pTailNum		[i]->Caption="";
	}
}
//---------------------------------------------------------------------------











