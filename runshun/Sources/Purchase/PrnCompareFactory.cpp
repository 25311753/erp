//---------------------------------------------------------------------------

#include <vcl.h>
#include <stdio.h>
#pragma hdrstop

#include "DataModule.h"
#include "BaseCode.h"
#include "PrnCompareFactory.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TPrnCompareFactoryForm *PrnCompareFactoryForm;
//---------------------------------------------------------------------------
__fastcall TPrnCompareFactoryForm::TPrnCompareFactoryForm(TComponent* Owner)
	: TForm(Owner)
{
	m_pFact[0]=FactName0;
	m_pFact[1]=FactName1;
	m_pFact[2]=FactName2;
	m_pFact[3]=FactName3;
	m_pFact[4]=FactName4;

	m_pCard[0]=FactCard0;
	m_pCard[1]=FactCard1;
	m_pCard[2]=FactCard2;
	m_pCard[3]=FactCard3;
	m_pCard[4]=FactCard4;

	m_pDays[0]=Delivery0;
	m_pDays[1]=Delivery1;
	m_pDays[2]=Delivery2;
	m_pDays[3]=Delivery3;
	m_pDays[4]=Delivery4;

	m_pQuote[0]=Quote0;
	m_pQuote[1]=Quote1;
	m_pQuote[2]=Quote2;
	m_pQuote[3]=Quote3;
	m_pQuote[4]=Quote4;

	m_pTail[0]=Tail0;
	m_pTail[1]=Tail1;
	m_pTail[2]=Tail2;
	m_pTail[3]=Tail3;
	m_pTail[4]=Tail4;

	m_pHiggle[0]=Higgle0;
	m_pHiggle[1]=Higgle1;
	m_pHiggle[2]=Higgle2;
	m_pHiggle[3]=Higgle3;
	m_pHiggle[4]=Higgle4;

	m_pPM[0]=txtPM0;
	m_pPM[1]=txtPM1;
	m_pPM[2]=txtPM2;
	m_pPM[3]=txtPM3;
	m_pPM[4]=txtPM4;

	m_pDD[0]=txtDD0;
	m_pDD[1]=txtDD1;
	m_pDD[2]=txtDD2;
	m_pDD[3]=txtDD3;
	m_pDD[4]=txtDD4;

	m_pTax[0]=txtTax0;
	m_pTax[1]=txtTax1;
	m_pTax[2]=txtTax2;
	m_pTax[3]=txtTax3;
	m_pTax[4]=txtTax4;
}

//---------------------------------------------------------------------------
void __fastcall TPrnCompareFactoryForm::pd_codePrint(TObject *sender,
      AnsiString &Value)
{
	char strItem[80];
  strcpy(strItem,Value.c_str());
  if(strItem[0]!='\0')
	{
  	Value = strItem+strlen(strItem)-1;
  }
}

//---------------------------------------------------------------------------
void __fastcall TPrnCompareFactoryForm::DetailBand1BeforePrint(TQRCustomBand *Sender, bool &PrintBand)
{
	char strID[80],strMN[80];
	AnsiString szRMB,szPM,szDD,szTax;
	CString szSQL;
	int i,j;
	BASE2COLDATA rwData;

	if(m_lstPM.GetSize()==0)
	{
		szSQL="select * from DicPayment order by pm_code";
		RunSQL(dm1->Query1,szSQL,true);
		while(!dm1->Query1->Eof)
		{
			strcpy(rwData.strCode,dm1->Query1->FieldByName("pm_code")->AsString.c_str());
			strcpy(rwData.strName,dm1->Query1->FieldByName("pm_name")->AsString.c_str());
			m_lstPM.Add(rwData);

			dm1->Query1->Next();
		}
	}

	if(m_lstRMB.GetSize()==0)
	{
		szSQL="select * from diccurrency order by dc_code";
		RunSQL(dm1->Query1,szSQL,true);
		while(!dm1->Query1->Eof)
		{
			strcpy(rwData.strCode,dm1->Query1->FieldByName("dc_code")->AsString.c_str());
			strcpy(rwData.strName,dm1->Query1->FieldByName("dc_name")->AsString.c_str());
			m_lstRMB.Add(rwData);
			dm1->Query1->Next();
		}
	}

	if(m_lstDD.GetSize()==0)
	{
		szSQL="select * from DicDelivery order by dd_code";
		RunSQL(dm1->Query1,szSQL,true);
		while(!dm1->Query1->Eof)
		{
			strcpy(rwData.strCode,dm1->Query1->FieldByName("dd_code")->AsString.c_str());
			strcpy(rwData.strName,dm1->Query1->FieldByName("dd_name")->AsString.c_str());
			m_lstDD.Add(rwData);
			dm1->Query1->Next();
		}
	}

	strcpy(strID,pd_code->DataSet->FieldByName("pd_code")->AsString.c_str());
	for(i=0;i<m_lstID.GetSize();i++)
	{
		szSQL.Format("select * from CompareFactory,DicUnits,PurchaseDetail"
			" where cf_apcode=pd_code and cf_quoteunit=du_code"
      " and cf_apcode='%s' and cf_mfcode='%s'",strID,m_lstID[i]);
		RunSQL(dm1->Query1,szSQL,true);
		if(!dm1->Query1->Eof)
		{
    	strcpy(strMN,dm1->Query1->FieldByName("pd_mncode")->AsString.c_str());

			szRMB="";
			for(j=0;j<m_lstRMB.GetSize();j++)
			{
				if(dm1->Query1->FieldByName("cf_quotermb")->AsString==m_lstRMB[j].strCode)
				{
					szRMB=m_lstRMB[j].strName;
					break;
				}
			}
			szPM="";
			for(j=0;j<m_lstPM.GetSize();j++)
			{
				if(dm1->Query1->FieldByName("cf_pmcode")->AsString==m_lstPM[j].strCode)
				{
					szPM=m_lstPM[j].strName;
					break;
				}
			}
			szDD="";
			for(j=0;j<m_lstDD.GetSize();j++)
			{
				if(dm1->Query1->FieldByName("cf_ddcode")->AsString==m_lstDD[j].strCode)
				{
					szDD=m_lstDD[j].strName;
					break;
				}
			}
      szTax="";
      if(!dm1->Query1->FieldByName("cf_invoice")->IsNull)
      {
      	szTax=dm1->Query1->FieldByName("cf_invoice")->AsString;
      }
      else
      {
      	if(!dm1->Query1->FieldByName("cf_tax")->IsNull)
        	szTax=FloatToStr(dm1->Query1->FieldByName("cf_tax")->AsFloat);
      }
      if(strMN[0]=='E' && strMN[1]=='M')
      {
				m_pQuote	[i]->Caption=FloatField2String(dm1->Query1->FieldByName("cf_quoteprice"),6);
				m_pHiggle	[i]->Caption=FloatField2String(dm1->Query1->FieldByName("cf_higgleprice"),6);
      }
      else
      {
				m_pQuote	[i]->Caption=FloatField2String(dm1->Query1->FieldByName("cf_quoteprice"),3);
				m_pHiggle	[i]->Caption=FloatField2String(dm1->Query1->FieldByName("cf_higgleprice"),3);
      }
			m_pTail		[i]->Caption=szRMB + " / " + dm1->Query1->FieldByName("du_name")->AsString;
			m_pPM			[i]->Caption=szPM;
			m_pDD			[i]->Caption=szDD;
			m_pTax		[i]->Caption=szTax;
		}
		else
		{
			m_pQuote	[i]->Caption="";
			m_pTail		[i]->Caption="";
			m_pHiggle	[i]->Caption="";
			m_pPM			[i]->Caption="";
			m_pDD			[i]->Caption="";
			m_pTax		[i]->Caption="";
		}
	}

	for(;i<5;i++)
	{
		m_pQuote	[i]->Caption="";
		m_pTail		[i]->Caption="";
		m_pHiggle	[i]->Caption="";
		m_pPM			[i]->Caption="";
		m_pDD			[i]->Caption="";
		m_pTax		[i]->Caption="";
	}

	char strName[512];
	CStringArray lstName;
	strcpy(strName,pd_code->DataSet->FieldByName("mn_name")->AsString.c_str());
	SplitStrToLines(strName,34,lstName);
	if(lstName.GetSize()==0)
	{
		txtMNName1->Caption="";
		txtMNName2->Caption="";
	}
	else if(lstName.GetSize()==1)
	{
		txtMNName1->Caption=(LPCSTR)lstName[0];
		txtMNName2->Caption="";
	}
	else
	{
		txtMNName1->Caption=(LPCSTR)lstName[0];
		txtMNName2->Caption=(LPCSTR)lstName[1];
	}
}
//---------------------------------------------------------------------------

