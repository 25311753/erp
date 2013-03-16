//---------------------------------------------------------------------------

#include <vcl.h>
#include <stdio.h>
#include <assert.h>
#pragma hdrstop

#include "DataModule.h"
#include "BaseCode.h"
#include "PrnSpeerFactory.h"
#include "SpeerMultiPrn.h"
#include "TConst.h"
#include "LdyInterface.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TSpeerMultiPrnForm *SpeerMultiPrnForm;

//===========================================================================
//询价单列印接口，文件：SpeerMultiPrn.*
void SpeerMultiPrn(int nAuth)
{
	CALL_FORM(TSpeerMultiPrnForm);
}
//===========================================================================

//---------------------------------------------------------------------------
__fastcall TSpeerMultiPrnForm::TSpeerMultiPrnForm(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TSpeerMultiPrnForm::FormShow(TObject *Sender)
{
	CString szSQL;
	int i,nYear,nMonth,nDay;
	char strDate[80];
	BASE2COLDATA rwBase;

//  m_lstCorpID.Add("");
//  lstCorp->Items->Add("全部");
	szSQL="select * from DepartCorp order by dc_code";
	RunSQL(dm1->Query1,szSQL,true);
	while(!dm1->Query1->Eof)
	{
		strcpy(rwBase.strCode,dm1->Query1->FieldByName("dc_code")->AsString.c_str());
		strcpy(rwBase.strName,dm1->Query1->FieldByName("dc_name")->AsString.c_str());
		m_lstCorp.Add(rwBase);

//		m_lstCorpID.Add(dm1->Query1->FieldByName("dc_code")->AsString.c_str());
//		lstCorp->Items->Add(dm1->Query1->FieldByName("dc_name")->AsString);
		dm1->Query1->Next();
	}
//	lstCorp->ItemIndex=0;

	szSQL="select * from StockHandleman order by sh_code";
	RunSQL(dm1->Query1,szSQL,true);
  while(!dm1->Query1->Eof)
	{
		m_lstHandleID.Add(dm1->Query1->FieldByName("sh_code")->AsString.c_str());
		lstHandle->Items->Add(dm1->Query1->FieldByName("sh_name")->AsString);
		dm1->Query1->Next();
	}
	for(i=0;i<m_lstHandleID.GetSize();i++)
	{
		if(m_lstHandleID[i]==operatorcode.c_str())
		{
			lstHandle->ItemIndex=i;
			lstHandle->Enabled=false;
			break;
		}
	}
	if(i==m_lstHandleID.GetSize())	lstHandle->ItemIndex=0;

	GetSysDate(nYear,nMonth,nDay,false);
	sprintf(strDate,"%04d%02d%02d",nYear,nMonth,nDay);
//	edtDate0->Text=strDate;
//	edtDate1->Text=strDate;

	unsigned short year,month,day;
	TDateTime tDate=GetSysTime(false);
  ctlDate0->DateTime=tDate;
  ctlDate1->DateTime=tDate;
	tDate+=3;
	tDate.DecodeDate(&year,&month,&day);
	sprintf(strDate,"%04d%02d%02d",year,month,day);
	edtEndDate->Text=strDate;
}
//---------------------------------------------------------------------------

void __fastcall TSpeerMultiPrnForm::btnQueryClick(TObject *Sender)
{
	CString szSQL;
	int nSel,i;
	char strTemp[256],strDate0[80],strDate1[80];
	TListItem *pItem;
	CArray<BASE2COLDATA,BASE2COLDATA>lstAddr;
	BASE2COLDATA rwAddr;

	szSQL="select * from GoodsAddr order by ga_code";
	RunSQL(dm1->Query1,szSQL,true);
	while(!dm1->Query1->Eof)
	{
		strcpy(rwAddr.strCode,dm1->Query1->FieldByName("ga_code")->AsString.c_str());
		sprintf(rwAddr.strName,"%s%s",dm1->Query1->FieldByName("ga_area")->AsString.c_str(),dm1->Query1->FieldByName("ga_name")->AsString.c_str());
		lstAddr.Add(rwAddr);
		dm1->Query1->Next();
	}

	szSQL="select * from AskPurchase,PurchaseDetail,materialno,DicUnits"
		" where ap_code=substring(pd_code,1,7) and pd_mncode=mn_code and pd_ducode=du_code"
    " and pd_endflag is null"
    " and substring(ap_code,1,1)='P'"; //合约采购的不用询价
  if(chkShowQuoted->Checked)
  {
  	szSQL+=" and pd_code not in (select distinct cf_apcode from CompareFactory)";
	}
	if((nSel=lstHandle->ItemIndex)<0 || nSel>=m_lstHandleID.GetSize())
	{
		ShowMessage("请选择一个有效的采购经办");
		return;
	}
	m_szHandleID=m_lstHandleID[nSel];
	sprintf(strTemp," and ap_shcode='%s'",m_szHandleID);
	szSQL+=strTemp;

	sprintf(strTemp," and ap_affirmdate between '%s 00:00:00' and '%s 23:59:59'",
		Time2DBDateString(ctlDate0->DateTime),Time2DBDateString(ctlDate1->DateTime));
	szSQL+=strTemp;
  szSQL+=" order by ap_affirmdate,pd_code";
	RunSQL(dm1->Query1,szSQL,true);
	lstView->Items->Clear();
	while(!dm1->Query1->Eof)
	{
		strcpy(strTemp,dm1->Query1->FieldByName("ap_code")->AsString.c_str());
/*
    if(strTemp[0]=='\0')
    {
    	dm1->Query1->Next();
      continue;
    }
    szSQL.Format("select * from QuoteFactory where qf_apcode='%s'",strTemp);
    RunSQL(dm1->Query2,szSQL,true);
    if(dm1->Query2->Eof)
    {
    	dm1->Query1->Next();
      continue;
    }
*/
		pItem=lstView->Items->Add();
		assert(pItem!=NULL);
		pItem->Caption=dm1->Query1->FieldByName("pd_code")->AsString;
		pItem->SubItems->Add(dm1->Query1->FieldByName("mn_name")->AsString);
		pItem->SubItems->Add(dm1->Query1->FieldByName("du_name")->AsString);
		pItem->SubItems->Add(FloatField2String(dm1->Query1->FieldByName("pd_count")));
		for(i=0;i<lstAddr.GetSize();i++)
		{
			if(dm1->Query1->FieldByName("ap_gacode")->AsString==lstAddr[i].strCode)
			{
				pItem->SubItems->Add(lstAddr[i].strName);
				break;
			}
		}
		if(i==lstAddr.GetSize())	pItem->SubItems->Add("");


    strcpy(strTemp,dm1->Query1->FieldByName("ap_reqdepart")->AsString.c_str());
		strTemp[2]='\0';
    for(i=0;i<m_lstCorp.GetSize();i++)
    {
    	if(strcmp(m_lstCorp[i].strCode,strTemp)==0)
      {
      	pItem->SubItems->Add(m_lstCorp[i].strName);
        break;
      }
    }
    if(i==m_lstCorp.GetSize())	pItem->SubItems->Add("");

    pItem->SubItems->Add(dm1->Query1->FieldByName("pd_quotedate")->IsNull ? "" : "*");

		dm1->Query1->Next();
	}
}
//---------------------------------------------------------------------------

void __fastcall TSpeerMultiPrnForm::btnExitClick(TObject *Sender)
{
	Close();	
}
//---------------------------------------------------------------------------

void __fastcall TSpeerMultiPrnForm::btnPrintClick(TObject *Sender)
{
	TListItem *pItem;
	AnsiString szAddr;
	int i;
	bool bSelected;
	CStringArray lstID;

	bSelected=false;
	for(i=0;i<lstView->Items->Count;i++)
	{
  	        pItem=lstView->Items->Item[i];
		if(!pItem->Selected)	continue;
		bSelected=true;
                                                  //		if(szAddr.IsEmpty())	szAddr=pItem->SubItems->Strings[3];
                                                  //		else if(szAddr!=pItem->SubItems->Strings[3])
                                                  //		{
                                                  //			ShowMessage("你选择的请购单交货地点不相同");
                                                  //			return;
                                                  //		}
                                                  
		lstID.Add(pItem->Caption.c_str());
	}

	if(!bSelected)
	{
		ShowMessage("请选择一个或多个项次");
		return;
	}

	CString szSQL;
  char strDate[80],strTemp[256],strSD[80];
  int nYear,nMonth,nDay;

  GetSysDate(nYear,nMonth,nDay,false);
//  sprintf(strDate,"%04d%02d%02d",nYear,nMonth,nDay);
//  edtSpeerPrnDate->Text=strDate;

	TPrnSpeerFactoryForm *pPrn;
  pPrn=new TPrnSpeerFactoryForm(this);
  assert(pPrn!=NULL);

//	pPrn->txtGAName->Caption=szAddr;

	szSQL.Format("select * from StockHandleman where sh_code='%s'",m_szHandleID);
	RunSQL(dm1->Query1,szSQL,true);
	if(!dm1->Query1->Eof)
	{
		pPrn->txtSHName->Caption=dm1->Query1->FieldByName("sh_name")->AsString;
		pPrn->txtSHTel->Caption=dm1->Query1->FieldByName("sh_tel")->AsString;
		strcpy(strSD,dm1->Query1->FieldByName("sh_sdcode")->AsString.c_str());
		if(strSD[0]!='\0')
  	        {
			szSQL.Format("select * from StockDepart where sd_code='%s'",strSD);
                        RunSQL(dm1->Query1,szSQL,true);
                        if(!dm1->Query1->Eof)
                        {
                                pPrn->txtSDAddr->Caption=dm1->Query1->FieldByName("sd_address")->AsString;
                                pPrn->txtSDTel->Caption=dm1->Query1->FieldByName("sd_tel")->AsString;
                        }
                }
	}
	else
	{
		pPrn->txtSHName->Caption="";
		pPrn->txtSHTel->Caption="";
	}
	pPrn->EndDate->Caption=edtEndDate->Text;

                                                //	szSQL="select * from"
                                                //		" PurchaseDetail,DicUnits,materialno,AskPurchase,QuoteFactory,Manufactur"
                                                //		 " where ap_code=substring(pd_code,1,7)"
                                                //		" and qf_apcode=ap_code"
                                                //		" and qf_mfcode=mf_code"
                                                //		" and pd_ducode=du_code and pd_mncode*=mn_code";

		szSQL="select * from"
		" PurchaseDetail,DicUnits,materialno,AskPurchase"
		 " where ap_code=substring(pd_code,1,7)"
		" and pd_ducode=du_code and pd_mncode*=mn_code";

	sprintf(strTemp," and pd_code in('%s'",lstID[0]);
	szSQL+=strTemp;
	for(i=1;i<lstID.GetSize();i++)
	{
		sprintf(strTemp,",'%s'",lstID[i]);
		szSQL+=strTemp;
	}
	szSQL+=")";
	szSQL+=" order by pd_code";



	if(!OpenQuery(dm1->sqlPrint,szSQL))	return;

  sprintf(strDate,"%04d-%02d-%02d",nYear,nMonth,nDay);
  pPrn->PrnDate->Caption=strDate;
  
  pPrn->PrnView->PreviewModal();
  delete pPrn;

	for(i=0;i<lstView->Items->Count;i++)
	{
  	        pItem=lstView->Items->Item[i];
		if(!pItem->Selected)	continue;
                strcpy(strTemp,pItem->Caption.c_str());
                szSQL.Format("update PurchaseDetail set pd_quotedate=getdate()"
    	                        " where pd_code='%s'",strTemp);
                RunSQL(dm1->Query1,szSQL);
                pItem->SubItems->Strings[5]="*";
	}
}
//---------------------------------------------------------------------------




