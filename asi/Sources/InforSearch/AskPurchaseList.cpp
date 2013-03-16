//---------------------------------------------------------------------------

#include <vcl.h>
#include <stdio.h>
#include <assert.h>
#pragma hdrstop

#include "DataModule.h"
#include "BaseCode.h"
#include "PurchaseRow.h"
#include "TConst.h"
#include "AskPurchaseList.h"
#include "LdyInterface.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TAskPurchaseListForm *AskPurchaseListForm;

//===========================================================================
//请购单列表查询接口，文件：AskPurchaseList.*
void AskPurchaseList(int nAuth)
{
	TAskPurchaseListForm *pForm;
	pForm=new TAskPurchaseListForm(Application);
	assert(pForm!=NULL);
	pForm->ShowModal();
	delete pForm;
}

//---------------------------------------------------------------------------
__fastcall TAskPurchaseListForm::TAskPurchaseListForm(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TAskPurchaseListForm::btnExitClick(TObject *Sender)
{
	Close();	
}

bool TAskPurchaseListForm::GetFilter(CString &szFilter)
{
	char strTemp[256],strDate0[80];
	int nSel;
 
	szFilter += " and substring(pd_mncode,2,1)<>'M'";

	edtID->Text=edtID->Text.Trim();
	if(!edtID->Text.IsEmpty())
	{
		sprintf(strTemp," and pd_code like '%s%%'",edtID->Text.c_str());
		szFilter+=strTemp;
	}
	if(lstType->ItemIndex>0)
	{
		sprintf(strTemp," and ap_type='%s'",lstType->Text=="普通" ? "N" : "I");
		szFilter+=strTemp;
	}
	edtReqDate0->Text=edtReqDate0->Text.Trim();
	if(!edtReqDate0->Text.IsEmpty())
	{
  	TDateTime tDate;
    int nYear,nMonth,nDay;

    if(edtReqDate0->Text.Length()!=8)
    {
    	ShowMessage("不合法的日期格式，日期格式为：yyyymmdd");
      if(edtReqDate0->CanFocus())	edtReqDate0->SetFocus();
      return false;
    }
    Date2YYMMDD(edtReqDate0->Text.c_str(),nYear,nMonth,nDay);
    try
    {
    	tDate=TDateTime(nYear,nMonth,nDay);
    }
    catch(...)
    {
    	ShowMessage("不合法的日期格式，日期格式为：yyyymmdd");
      if(edtReqDate0->CanFocus())	edtReqDate0->SetFocus();
      return false;
    }
		sprintf(strDate0,"%04d-%02d-%02d",nYear,nMonth,nDay);

		sprintf(strTemp," and ap_reqdate%s'%s'",lstReqType->Text.c_str(),strDate0);
		szFilter+=strTemp;
  }
	edtNeedDate->Text=edtNeedDate->Text.Trim();
	if(!edtNeedDate->Text.IsEmpty())
	{
  	TDateTime tDate;
    int nYear,nMonth,nDay;

    if(edtNeedDate->Text.Length()!=8)
    {
    	ShowMessage("不合法的日期格式，日期格式为：yyyymmdd");
      if(edtNeedDate->CanFocus())	edtNeedDate->SetFocus();
      return false;
    }
    Date2YYMMDD(edtNeedDate->Text.c_str(),nYear,nMonth,nDay);
    try
    {
    	tDate=TDateTime(nYear,nMonth,nDay);
    }
    catch(...)
    {
    	ShowMessage("不合法的日期格式，日期格式为：yyyymmdd");
      if(edtNeedDate->CanFocus())	edtNeedDate->SetFocus();
      return false;
    }
		sprintf(strDate0,"%04d-%02d-%02d",nYear,nMonth,nDay);
		sprintf(strTemp," and ap_needdate%s'%s'",lstNeedType->Text.c_str(),strDate0);
		szFilter+=strTemp;
	}
//	if(lstBuyType->ItemIndex>0)
//	{
//		sprintf(strTemp," and ap_buytype='%s'",lstBuyType->Text=="内购" ? "M" : "N");
//		szFilter+=strTemp;
//	}
	if((nSel=lstStockDep->ItemIndex)>0 && nSel<m_lstStockDepID.GetSize())
	{
		sprintf(strTemp," and ap_sdcode='%s'",m_lstStockDepID[nSel]);
		szFilter+=strTemp;
	}
	if((nSel=lstAskDep->ItemIndex)>0 && nSel<m_lstReqDepID.GetSize())
	{
		sprintf(strTemp," and ap_reqdepart='%s'",m_lstReqDepID[nSel]);
		szFilter+=strTemp;
	}
	edtMncode->Text=edtMncode->Text.Trim();
	if(!edtMncode->Text.IsEmpty())
	{
		sprintf(strTemp," and pd_mncode like '%s%%'",edtMncode->Text.c_str());
		szFilter+=strTemp;
	}
	if((nSel=lstStockman->ItemIndex)>0 && nSel<m_lstStockmanID.GetSize())
	{
		sprintf(strTemp," and ap_shcode='%s'",m_lstStockmanID[nSel]);
		szFilter+=strTemp;
	}
	if((nSel=lstReqCorp->ItemIndex)>0 && nSel<m_lstCorpID.GetSize())
	{
		sprintf(strTemp," and substring(ap_reqdepart,1,2)='%s'",m_lstCorpID[nSel]);
		szFilter+=strTemp;
	}
	
	if(lstAfm->Text=="未接案")	szFilter+=" and ap_affirmdate is null";
	else if(lstAfm->Text=="已接案")	szFilter+=" and ap_affirmdate is not null";

	if(lstEndFlag->Text=="未结案")	szFilter+=" and pd_endflag is null";
	else if(lstEndFlag->Text=="已结案")	szFilter+=" and pd_endflag is not null";

	return true;
}

//---------------------------------------------------------------------------
void __fastcall TAskPurchaseListForm::btnQueryClick(TObject *Sender)
{
	TListItem *pItem;
	CString szSQL,szFilter,szTable,szTable2;
	char strTemp[256],strDate0[80],strDate1[80],strBuff[256];
	CAskPurchaseRow rwMain;
	CStringArray lstDepID,lstDepName,lstFactID,lstFactName;
	int i,nSel;

	szSQL="select * from DicDepart order by dd_code";
	RunSQL(dm1->Query1,szSQL,true);
	while(!dm1->Query1->Eof)
	{
		lstDepID.Add(dm1->Query1->FieldByName("dd_code")->AsString.c_str());
		lstDepName.Add(dm1->Query1->FieldByName("dd_name")->AsString.c_str());
		dm1->Query1->Next();
	}

	szSQL="select * from Manufactur";
	RunSQL(dm1->Query1,szSQL,true);
	while(!dm1->Query1->Eof)
	{
		lstFactID.Add(dm1->Query1->FieldByName("mf_code")->AsString.c_str());
		lstFactName.Add(dm1->Query1->FieldByName("mf_shortname")->AsString.c_str());
		dm1->Query1->Next();
	}

	lstView->Items->Clear();
	if(!GetFilter(szFilter))	return;

	szTable=GetTmpTableName();
	szSQL.Format("create table dbo.%s("

#ifdef _DEBUG
		"m_apcode varchar(20) COLLATE Chinese_Taiwan_Stroke_CS_AS,"
		"m_buytype varchar(20) COLLATE Chinese_Taiwan_Stroke_CS_AS,"
		"m_buydep  varchar(20) COLLATE Chinese_Taiwan_Stroke_CS_AS,"
		"m_reqdep varchar(30) COLLATE Chinese_Taiwan_Stroke_CS_AS,"
		"m_type    varchar(20) COLLATE Chinese_Taiwan_Stroke_CS_AS,"
		"m_reqdate datetime,"
		"m_needdate datetime,"
		"m_mncode varchar(30) COLLATE Chinese_Taiwan_Stroke_CS_AS,"
		"m_mnspec varchar(80) COLLATE Chinese_Taiwan_Stroke_CS_AS,"
		"m_afmdate datetime,"
		"m_stockman varchar(20) COLLATE Chinese_Taiwan_Stroke_CS_AS,"
		"m_endflag varchar(10) COLLATE Chinese_Taiwan_Stroke_CS_AS,"
#else
		"m_apcode varchar(20),"
		"m_buytype varchar(20),"
		"m_buydep  varchar(20),"
		"m_reqdep varchar(30),"
		"m_type    varchar(20),"
		"m_reqdate datetime,"
		"m_needdate datetime,"
		"m_mncode varchar(30),"
		"m_mnspec varchar(80),"
		"m_afmdate datetime,"
		"m_stockman varchar(20),"
		"m_endflag varchar(10),"
#endif
		"m_quoteenddate datetime,"
		"m_speerprndate datetime,"
		"m_quoteinpdate datetime,"
		"m_higgleinpdate datetime,"
		"m_showdate datetime,"
		"m_decidedate datetime,"
    "m_pdcount float"
		")",szTable);
	if(!RunSQL(dm1->Query1,szSQL))	return;

  if(lstStockType->ItemIndex==1)	szFilter+=" and substring(ap_code,1,1)='Q'";
  else	szFilter+=" and substring(ap_code,1,1)='P'";

	szSQL.Format("insert into %s"
		" select pd_code,ap_buytype,ap_sdcode,ap_reqdepart,ap_type,ap_reqdate,"
		"ap_needdate,pd_mncode,mn_name,ap_affirmdate,ap_shcode,pd_endflag,null,null,null,null,null,null,pd_count"
		" from AskPurchase,PurchaseDetail,materialno"
		" where ap_code=substring(pd_code,1,7) and mn_code=pd_mncode",szTable);
	szSQL+=szFilter;
	if(!RunSQL(dm1->Query1,szSQL))	goto DROP_TABLE;

	szSQL.Format("update %s set m_quoteenddate="
		"("
		" select max(qf_enddate) from QuoteFactory "
		" where qf_apcode=substring(m_apcode,1,7)"
		" group by qf_apcode  "
		")",szTable);
	if(!RunSQL(dm1->Query1,szSQL))	goto DROP_TABLE;

	szSQL.Format("update %s set m_speerprndate="
		"("
		" select max(qf_printdate) from QuoteFactory"
		" where qf_apcode=substring(m_apcode,1,7)"
		" group by qf_apcode  "
		")",szTable);
	if(!RunSQL(dm1->Query1,szSQL))	goto DROP_TABLE;

	szSQL.Format("update %s set m_quoteinpdate="
		"("
		" select max(cf_quotedate) from CompareFactory"
		" where cf_apcode=m_apcode"
		" group by cf_apcode  "
		")",szTable);
	if(!RunSQL(dm1->Query1,szSQL))	goto DROP_TABLE;

	szSQL.Format("update %s set m_higgleinpdate="
		"("
		" select max(cf_higgledate) from CompareFactory"
		" where cf_apcode=m_apcode"
		" group by cf_apcode"
		")",szTable);
	if(!RunSQL(dm1->Query1,szSQL))	goto DROP_TABLE;

	szSQL.Format("update %s set m_showdate="
		"("
		" select max(df_plandate) from DecideFactory"
		" where df_apcode=m_apcode"
		" group by df_apcode"
		")",szTable);
	if(!RunSQL(dm1->Query1,szSQL))	goto DROP_TABLE;

	szSQL.Format("update %s set m_decidedate="
		"("
		" select max(df_decidedate) from DecideFactory"
		" where df_apcode=m_apcode"
		" group by df_apcode"
		")",szTable);
	if(!RunSQL(dm1->Query1,szSQL))	goto DROP_TABLE;

	szSQL="select * from DicDepart order by dd_code";
	RunSQL(dm1->Query1,szSQL,true);
	while(!dm1->Query1->Eof)
	{
		m_lstDepID.Add(dm1->Query1->FieldByName("dd_code")->AsString.c_str());
		m_lstDepName.Add(dm1->Query1->FieldByName("dd_name")->AsString.c_str());
		dm1->Query1->Next();
	}

	szTable2=GetTmpTableName();
	szSQL.Format("create table dbo.%s ("
#ifdef _DEBUG
		"bf_code varchar(20) COLLATE Chinese_Taiwan_Stroke_CS_AS,"
		"bf_apcode varchar(20) COLLATE Chinese_Taiwan_Stroke_CS_AS,"
		"bf_date datetime,"
    "bf_days int,"
		"bf_mfname varchar(80) COLLATE Chinese_Taiwan_Stroke_CS_AS,"
		"bf_count float,"
		"am_num float,"
		"am_chknum float,"
		"b_count float,"
		"b_money float"
#else
		"bf_code varchar(20),"
		"bf_apcode varchar(20),"
		"bf_date datetime,"
    "bf_days int,"
		"bf_mfname varchar(80),"
		"bf_count float,"
		"am_num float,"
		"am_chknum float,"
		"b_count float,"
		"b_money float"
#endif
		")",szTable2);
	if(!RunSQL(dm1->Query1,szSQL))
	{
		szTable2="";
		goto DROP_TABLE;
	}

	szSQL.Format("insert into %s"
		" select bf_code,bf_apcode,bf_bookdate,bf_deliverdays,mf_shortname,bf_count,sum(am_quantity),sum(am_checkquan),NULL,NULL"
		" from AskPurchase,PurchaseDetail,BookFactory,acceptmate,Manufactur"
		" where ap_code=substring(pd_code,1,7) and bf_apcode=pd_code"
		" and bf_mfcode=mf_code and bf_code*=am_bfcode %s"
		" group by bf_code,bf_apcode,bf_bookdate,bf_deliverdays,mf_shortname,bf_count",szTable2,szFilter);
	if(!RunSQL(dm1->Query1,szSQL))	goto DROP_TABLE;

	szSQL.Format("update %s set b_count="
		"("
		"select sum(pmd_chkquan) from paymentdetail where pmd_bfcode=bf_code"
		")",szTable2);
	if(!RunSQL(dm1->Query1,szSQL))	goto DROP_TABLE;

	szSQL.Format("update %s set b_money="
		"("
		"select sum(pmd_money) from paymentdetail where pmd_bfcode=bf_code"
		")",szTable2);
	if(!RunSQL(dm1->Query1,szSQL))	goto DROP_TABLE;

	szSQL.Format("select * from %s,%s where m_apcode*=bf_apcode"
		" order by m_apcode",szTable,szTable2);

	RunSQL(dm1->Query1,szSQL,true);
	while(!dm1->Query1->Eof)
	{
		pItem=lstView->Items->Add();
		assert(pItem!=NULL);

		pItem->Caption=dm1->Query1->FieldByName("m_apcode")->AsString;
		strcpy(strTemp,dm1->Query1->FieldByName("m_buytype")->AsString.c_str());
		pItem->SubItems->Add(strTemp[0]=='M' ? "内购" : "外购");

		strcpy(strTemp,dm1->Query1->FieldByName("m_buydep")->AsString.c_str());
		for(i=1;i<m_lstStockDepID.GetSize();i++)
		{
			if(m_lstStockDepID[i]==strTemp)
			{
				pItem->SubItems->Add(lstStockDep->Items->Strings[i]);
				strcpy(strBuff,lstStockDep->Items->Strings[i].c_str());
				break;
			}
		}
		if(i==m_lstStockDepID.GetSize())	pItem->SubItems->Add("");

		strcpy(strTemp,dm1->Query1->FieldByName("m_reqdep")->AsString.c_str());
		strTemp[2]='\0';
		for(i=1;i<m_lstCorpID.GetSize();i++)
		{
			if(m_lstCorpID[i]==strTemp)
			{
				pItem->SubItems->Add(lstReqCorp->Items->Strings[i]);
				break;
			}
		}
		if(i==m_lstCorpID.GetSize())	pItem->SubItems->Add("");

		strcpy(strTemp,dm1->Query1->FieldByName("m_reqdep")->AsString.c_str());
		for(i=0;i<m_lstDepID.GetSize();i++)
		{
			if(m_lstDepID[i]==strTemp)
			{
				pItem->SubItems->Add((LPCSTR)m_lstDepName[i]);
				break;
			}
		}
		if(i==lstDepID.GetSize())	pItem->SubItems->Add("");

		strcpy(strTemp,dm1->Query1->FieldByName("m_type")->AsString.c_str());
		pItem->SubItems->Add(strTemp[0]=='I' ? "紧急" : "普通");

		pItem->SubItems->Add(DateField2Text(dm1->Query1->FieldByName("m_reqdate")));
		pItem->SubItems->Add(DateField2Text(dm1->Query1->FieldByName("m_needdate")));
		pItem->SubItems->Add(dm1->Query1->FieldByName("m_mncode")->AsString);
		pItem->SubItems->Add(dm1->Query1->FieldByName("m_mnspec")->AsString);
		pItem->SubItems->Add(dm1->Query1->FieldByName("m_afmdate")->AsString);

		strcpy(strTemp,dm1->Query1->FieldByName("m_stockman")->AsString.c_str());
		for(i=1;i<m_lstStockmanID.GetSize();i++)
		{
			if(m_lstStockmanID[i]==strTemp)
			{
				pItem->SubItems->Add(lstStockman->Items->Strings[i]);
				break;
			}
		}
		if(i==m_lstStockmanID.GetSize())	pItem->SubItems->Add("");

		pItem->SubItems->Add(dm1->Query1->FieldByName("m_endflag")->AsString);
    pItem->SubItems->Add(FloatField2String(dm1->Query1->FieldByName("m_pdcount"),2));
		pItem->SubItems->Add(DateField2Text(dm1->Query1->FieldByName("m_quoteenddate")));
		pItem->SubItems->Add(DateField2Text(dm1->Query1->FieldByName("m_speerprndate")));
		pItem->SubItems->Add(DateField2Text(dm1->Query1->FieldByName("m_quoteinpdate")));
		pItem->SubItems->Add(DateField2Text(dm1->Query1->FieldByName("m_higgleinpdate")));
		pItem->SubItems->Add(DateField2Text(dm1->Query1->FieldByName("m_showdate")));
		pItem->SubItems->Add(DateField2Text(dm1->Query1->FieldByName("m_decidedate")));

		pItem->SubItems->Add(dm1->Query1->FieldByName("bf_code")->AsString);
		pItem->SubItems->Add(DateField2Text(dm1->Query1->FieldByName("bf_date")));
		pItem->SubItems->Add(IntField2Text(dm1->Query1->FieldByName("bf_days")));
		pItem->SubItems->Add(dm1->Query1->FieldByName("bf_mfname")->AsString);
		pItem->SubItems->Add(FloatField2String(dm1->Query1->FieldByName("bf_count"),2));
		pItem->SubItems->Add(FloatField2String(dm1->Query1->FieldByName("am_num"),2));
		pItem->SubItems->Add(FloatField2String(dm1->Query1->FieldByName("am_chknum"),2));

		pItem->SubItems->Add(FloatField2String(dm1->Query1->FieldByName("b_count"),2));
//		pItem->SubItems->Add(FloatField2String(dm1->Query1->FieldByName("b_money"),2));

//		strcpy(strTemp,dm1->Query1->FieldByName("bf_mfcode")->AsString.c_str());
//		for(i=0;i<lstFactID.GetSize();i++)
//		{
//			if(lstFactID[i]==strTemp)
//			{
//				pItem->SubItems->Add((LPCSTR)lstFactName[i]);
//				break;
//			}
//		}
//		if(i==lstFactID.GetSize())	pItem->SubItems->Add("");

		dm1->Query1->Next();
	}

DROP_TABLE:
	szSQL.Format("drop table dbo.%s",szTable);
	RunSQL(dm1->Query1,szSQL);
	if(!szTable2.IsEmpty())
	{
		szSQL.Format("drop table dbo.%s",szTable2);
		RunSQL(dm1->Query1,szSQL);
	}
}
//---------------------------------------------------------------------------
void __fastcall TAskPurchaseListForm::FormShow(TObject *Sender)
{
	int nYear,nMonth,nDay;
	char strDate0[80],strDate1[80];
	CString szSQL;

	edtID				->Text="";
	edtReqDate0	->Text="";
	edtNeedDate	->Text="";
	edtMncode		->Text="";

	m_lstStockDepID.Add("");
	lstStockDep->Items->Add("全部");
	szSQL="select * from StockDepart order by sd_code";
	RunSQL(dm1->Query1,szSQL,true);
	while(!dm1->Query1->Eof)
	{
		m_lstStockDepID.Add(dm1->Query1->FieldByName("sd_code")->AsString.c_str());
		lstStockDep->Items->Add(dm1->Query1->FieldByName("sd_name")->AsString);
		dm1->Query1->Next();
	}

	lstType			->ItemIndex=0;
	lstReqType	->ItemIndex=0;
//	lstBuyType	->ItemIndex=0;
	lstNeedType	->ItemIndex=0;
	lstStockDep	->ItemIndex=0;
  lstStockType->ItemIndex=0;

  lstReqCorp->Items->Add("全部");
	m_lstCorpID.Add("");
  szSQL="select * from DepartCorp order by dc_code";
  RunSQL(dm1->Query1,szSQL,true);
	while(!dm1->Query1->Eof)
	{
		m_lstCorpID.Add(dm1->Query1->FieldByName("dc_code")->AsString.c_str());
		lstReqCorp->Items->Add(dm1->Query1->FieldByName("dc_name")->AsString);
		dm1->Query1->Next();
	}
	lstReqCorp->ItemIndex=0;
	ResetReqDepart();

	lstAfm->ItemIndex=0;
	lstEndFlag->ItemIndex=0;

	lstStockman->Items->Add("全部");
	m_lstStockmanID.Add("");
	szSQL="select * from StockHandleman order by sh_code";
	RunSQL(dm1->Query1,szSQL,true);
	while(!dm1->Query1->Eof)
	{
		m_lstStockmanID.Add(dm1->Query1->FieldByName("sh_code")->AsString.c_str());
		lstStockman->Items->Add(dm1->Query1->FieldByName("sh_name")->AsString);
		dm1->Query1->Next();
	}
	lstStockman->ItemIndex=0;

	FormResize(Sender);
  ResetCtrl();
}
//---------------------------------------------------------------------------

void TAskPurchaseListForm::ResetReqDepart()
{
	CString szSQL;
	int nSel;
	bool bAll;

	lstAskDep->Items->Clear();
	m_lstReqDepID.RemoveAll();

	lstAskDep->Items->Add("全部");
	m_lstReqDepID.Add("");

	if((nSel=lstReqCorp->ItemIndex)>0 && nSel<m_lstCorpID.GetSize())
	{
		bAll=false;
		szSQL.Format("select * from DicDepart where substring(dd_code,1,2)='%s'",m_lstCorpID[nSel]);
	}
	else
	{
		bAll=true;
		szSQL="select * from DicDepart,DepartCorp where substring(dd_code,1,2)*=dc_code";
	}
	szSQL+=" order by dd_code";
	RunSQL(dm1->Query1,szSQL,true);
	while(!dm1->Query1->Eof)
	{
		m_lstReqDepID.Add(dm1->Query1->FieldByName("dd_code")->AsString.c_str());
		if(bAll)
			lstAskDep->Items->Add(dm1->Query1->FieldByName("dc_name")->AsString
				+dm1->Query1->FieldByName("dd_name")->AsString);
		else
			lstAskDep->Items->Add(dm1->Query1->FieldByName("dd_name")->AsString);
		dm1->Query1->Next();
	}
	lstAskDep->ItemIndex=0;
}

void TAskPurchaseListForm::ResetCtrl()
{
	btnDetail->Enabled = lstView->Selected!=NULL;
  btnToEnd->Enabled = lstView->Selected!=NULL;
}

void __fastcall TAskPurchaseListForm::lstViewSelectItem(TObject *Sender,TListItem *Item, bool Selected)
{
	if(!Selected)	return;
	ResetCtrl();
}
//---------------------------------------------------------------------------

void __fastcall TAskPurchaseListForm::btnDetailClick(TObject *Sender)
{
	TListItem *pItem;
	char strID[80];
	if((pItem=lstView->Selected)==NULL)	return;
	if(pItem->Caption.IsEmpty())	return;
	strcpy(strID,pItem->Caption.c_str());
	strID[strlen(strID)-1]='\0';

	int nRight=GetOperatorRight(operatorcode.c_str(),"IDM_ASKPURCHASE");
	//请购单输入接口，文件：AskPurchase.*
	AskPurchase(strID,nRight);
}
//---------------------------------------------------------------------------

void __fastcall TAskPurchaseListForm::btnToExcelClick(TObject *Sender)
{
	Variant vExcel,vSheet;
  int nRow,i;
  TListItem *pItem;

  try
  {
	  nRow=1;
		if(!OpenExcel("请购单列表.xls",vExcel,vSheet))	return;
		ListHead2Excel(lstView,vSheet,nRow++);
		for(i=0;i<lstView->Items->Count;i++)
    {
    	pItem=lstView->Items->Item[i];
      InsertExcelItem(vSheet,nRow++,
      	pItem->Caption.c_str(),
        pItem->SubItems->Strings[0].c_str(),
        pItem->SubItems->Strings[1].c_str(),
        pItem->SubItems->Strings[2].c_str(),
        pItem->SubItems->Strings[3].c_str(),
        pItem->SubItems->Strings[4].c_str(),
        pItem->SubItems->Strings[5].c_str(),
        pItem->SubItems->Strings[6].c_str(),
        pItem->SubItems->Strings[7].c_str(),
        pItem->SubItems->Strings[8].c_str(),
        pItem->SubItems->Strings[9].c_str(),
        pItem->SubItems->Strings[10].c_str(),
        pItem->SubItems->Strings[11].c_str(),
        pItem->SubItems->Strings[12].c_str(),
        pItem->SubItems->Strings[13].c_str(),
        pItem->SubItems->Strings[14].c_str(),
        pItem->SubItems->Strings[15].c_str(),
        pItem->SubItems->Strings[16].c_str(),
        pItem->SubItems->Strings[17].c_str(),
        pItem->SubItems->Strings[18].c_str(),
        pItem->SubItems->Strings[19].c_str(),
        pItem->SubItems->Strings[20].c_str(),
        pItem->SubItems->Strings[21].c_str(),
        pItem->SubItems->Strings[22].c_str(),
        pItem->SubItems->Strings[23].c_str(),
        pItem->SubItems->Strings[24].c_str(),
        pItem->SubItems->Strings[25].c_str(),
        pItem->SubItems->Strings[26].c_str(),
				NULL);
		}
	}
	catch(...)
	{
	}
}
//---------------------------------------------------------------------------


void __fastcall TAskPurchaseListForm::lstViewDblClick(TObject *Sender)
{
	if(btnDetail->Enabled)
		btnDetailClick(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TAskPurchaseListForm::lstReqCorpClick(TObject *Sender)
{
	ResetReqDepart();	
}
//---------------------------------------------------------------------------

void __fastcall TAskPurchaseListForm::FormKeyDown(TObject *Sender,
      WORD &Key, TShiftState Shift)
{
	if(Key==VK_RETURN)
		KeyReturnHandle(ActiveControl);
}
//---------------------------------------------------------------------------

void __fastcall TAskPurchaseListForm::FormResize(TObject *Sender)
{
	int nHeight,nWidth,nCtlTop;

  nHeight=ClientHeight;
  nWidth=ClientWidth;
  nCtlTop=nHeight-100;

  lstView->Height = nHeight - 150;
  lstView->Width	= nWidth  - 20;

  ctlPane		->Top= nCtlTop;
}
//---------------------------------------------------------------------------

void __fastcall TAskPurchaseListForm::btnToEndClick(TObject *Sender)
{
	TListItem *pItem;
	if((pItem=lstView->Selected)==NULL)	return;
	if(pItem->Caption.IsEmpty())	return;

	int nRight=GetOperatorRight(operatorcode.c_str(),"IDM_ASKPURCHASEEND");
	//请购单输入接口，文件：AskPurchase.*
	AskPurchaseEnd(pItem->Caption.c_str(),nRight);
}
//---------------------------------------------------------------------------

#include "AskPurchaseMT.h"
void __fastcall TAskPurchaseListForm::btnMaterPickupClick(TObject *Sender)
{
	TAskPurchaseMTForm *pMT;
	pMT=new TAskPurchaseMTForm(this);
	assert(pMT!=NULL);
	pMT->m_szMaterCode=edtMncode->Text;
	if(pMT->ShowModal()==mrOk)
	{
		edtMncode->Text=pMT->m_szMaterCode;
	}
	delete pMT;
}
//---------------------------------------------------------------------------


