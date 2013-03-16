//---------------------------------------------------------------------------

#include <vcl.h>
#include <stdio.h>
#include <assert.h>
#pragma hdrstop

#include "DataModule.h"
#include "BaseCode.h"
#include "APAffirmAndNotBook.h"
#include "TConst.h"
#include "LdyInterface.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TAPAffirmAndNotBookForm *APAffirmAndNotBookForm;

//==========================================================================
//已接案逾期未订明细接口，文件：APAffirmAndNotBook.*
void APAffirmAndNotBook(int nAuth)
{
	CALL_FORM(TAPAffirmAndNotBookForm);
}
//==========================================================================

//---------------------------------------------------------------------------
__fastcall TAPAffirmAndNotBookForm::TAPAffirmAndNotBookForm(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TAPAffirmAndNotBookForm::btnExitClick(TObject *Sender)
{
	Close();	
}
//---------------------------------------------------------------------------
void __fastcall TAPAffirmAndNotBookForm::FormShow(TObject *Sender)
{
	int nYear,nMonth,nDay;
	char strDate0[80],strDate1[80];
	CString szSQL;

	edtID				->Text="";
	edtMncode		->Text="";
//------------------------------------------------------------------------------
 if(g_theOperator.op_cpcode[0]=='A')
      { //若用户为行政中心，自动寻找行政中心的采购部门与采购经办
                     szSQL="select * from StockDepart where sd_code='X' or sd_code='11' order by sd_code DESC";
                     RunSQL(dm1->Query1,szSQL,true);
                     while(!dm1->Query1->Eof)
                       {
                         m_lstStockDepID.Add(dm1->Query1->FieldByName("sd_code")->AsString.c_str());
                         lstStockDep->Items->Add(dm1->Query1->FieldByName("sd_name")->AsString);
                         dm1->Query1->Next();
                        }
                    lstStockDep->ItemIndex=0;
        //采购经办
                    m_lstStockmanID.Add("");
                    lstStockman->Items->Add("全部采购经办");
                    szSQL="select * from StockHandleman where sh_sdcode='X' or sh_sdcode='11'order by sh_code";
                    RunSQL(dm1->Query1,szSQL,true);
                    while(!dm1->Query1->Eof)
                       {
                         m_lstStockmanID.Add(dm1->Query1->FieldByName("sh_code")->AsString.c_str());
                         lstStockman->Items->Add(dm1->Query1->FieldByName("sh_name")->AsString);
                         dm1->Query1->Next();
                        }
                     lstStockman->ItemIndex=0;

      }

 if(g_theOperator.op_cpcode[0]=='D')
      { //若用户为宏铭公司，自动寻找宏铭的采购部门与采购经办
              szSQL="select * from StockDepart where sd_code='Y' or sd_code='1' order by sd_code";
                     RunSQL(dm1->Query1,szSQL,true);
                     while(!dm1->Query1->Eof)
                       {
                         m_lstStockDepID.Add(dm1->Query1->FieldByName("sd_code")->AsString.c_str());
                         lstStockDep->Items->Add(dm1->Query1->FieldByName("sd_name")->AsString);
                         dm1->Query1->Next();
                        }
                    lstStockDep->ItemIndex=0;

        //采购经办
                    m_lstStockmanID.Add("");
                    lstStockman->Items->Add("全部采购经办");
                    szSQL="select * from StockHandleman where sh_sdcode='Y' or sh_sdcode='1' order by sh_code";
                    RunSQL(dm1->Query1,szSQL,true);
                    while(!dm1->Query1->Eof)
                       {
                         m_lstStockmanID.Add(dm1->Query1->FieldByName("sh_code")->AsString.c_str());
                         lstStockman->Items->Add(dm1->Query1->FieldByName("sh_name")->AsString);
                         dm1->Query1->Next();
                        }
                     lstStockman->ItemIndex=0;
      }
 if(g_theOperator.op_cpcode[0]=='B')
      { //若用户为宏仁公司，自动寻找宏仁的采购部门
              szSQL="select * from StockDepart where sd_code='9' order by sd_code";
                     RunSQL(dm1->Query1,szSQL,true);
                     while(!dm1->Query1->Eof)
                       {
                         m_lstStockDepID.Add(dm1->Query1->FieldByName("sd_code")->AsString.c_str());
                         lstStockDep->Items->Add(dm1->Query1->FieldByName("sd_name")->AsString);
                         dm1->Query1->Next();
                        }
                    lstStockDep->ItemIndex=0;

        //采购经办
                    m_lstStockmanID.Add("");
                    lstStockman->Items->Add("全部采购经办");
                    szSQL="select * from StockHandleman where sh_sdcode='9' order by sh_code";
                    RunSQL(dm1->Query1,szSQL,true);
                    while(!dm1->Query1->Eof)
                       {
                         m_lstStockmanID.Add(dm1->Query1->FieldByName("sh_code")->AsString.c_str());
                         lstStockman->Items->Add(dm1->Query1->FieldByName("sh_name")->AsString);
                         dm1->Query1->Next();
                        }
                     lstStockman->ItemIndex=0;
      }
 if(g_theOperator.op_cpcode[0]=='C')
      { //若用户为宏育公司，自动寻找宏育的采购部门
              szSQL="select * from StockDepart where sd_code='4' or sd_code='5' order by sd_code";
                     RunSQL(dm1->Query1,szSQL,true);
                     while(!dm1->Query1->Eof)
                       {
                         m_lstStockDepID.Add(dm1->Query1->FieldByName("sd_code")->AsString.c_str());
                         lstStockDep->Items->Add(dm1->Query1->FieldByName("sd_name")->AsString);
                         dm1->Query1->Next();
                        }
                    lstStockDep->ItemIndex=0;

        //采购经办
                    m_lstStockmanID.Add("");
                    lstStockman->Items->Add("全部采购经办");
                    szSQL="select * from StockHandleman where sh_sdcode='4' or sh_sdcode='5' order by sh_code";
                    RunSQL(dm1->Query1,szSQL,true);
                    while(!dm1->Query1->Eof)
                       {
                         m_lstStockmanID.Add(dm1->Query1->FieldByName("sh_code")->AsString.c_str());
                         lstStockman->Items->Add(dm1->Query1->FieldByName("sh_name")->AsString);
                         dm1->Query1->Next();
                        }
                     lstStockman->ItemIndex=0;
      }
 if(g_theOperator.op_cpcode[0]=='E')
      { //若用户为宏信公司，自动寻找宏信的采购部门
              szSQL="select * from StockDepart where sd_code='2' or sd_code='3' order by sd_code";
                     RunSQL(dm1->Query1,szSQL,true);
                     while(!dm1->Query1->Eof)
                       {
                         m_lstStockDepID.Add(dm1->Query1->FieldByName("sd_code")->AsString.c_str());
                         lstStockDep->Items->Add(dm1->Query1->FieldByName("sd_name")->AsString);
                         dm1->Query1->Next();
                        }
                    lstStockDep->ItemIndex=0;

        //采购经办
                    m_lstStockmanID.Add("");
                    lstStockman->Items->Add("全部采购经办");
                    szSQL="select * from StockHandleman where sh_sdcode='2' or sh_sdcode='3' order by sh_code";
                    RunSQL(dm1->Query1,szSQL,true);
                    while(!dm1->Query1->Eof)
                       {
                         m_lstStockmanID.Add(dm1->Query1->FieldByName("sh_code")->AsString.c_str());
                         lstStockman->Items->Add(dm1->Query1->FieldByName("sh_name")->AsString);
                         dm1->Query1->Next();
                        }
                     lstStockman->ItemIndex=0;
      }
if(g_theOperator.op_cpcode[0]=='F')
      { //若用户为宏焕公司，自动寻找宏焕的采购部门
              szSQL="select * from StockDepart where sd_code='6' or sd_code='7' or sd_code='8' order by sd_code";
                     RunSQL(dm1->Query1,szSQL,true);
                     while(!dm1->Query1->Eof)
                       {
                         m_lstStockDepID.Add(dm1->Query1->FieldByName("sd_code")->AsString.c_str());
                         lstStockDep->Items->Add(dm1->Query1->FieldByName("sd_name")->AsString);
                         dm1->Query1->Next();
                        }
                    lstStockDep->ItemIndex=0;

        //采购经办
                    m_lstStockmanID.Add("");
                    lstStockman->Items->Add("全部采购经办");
                    szSQL="select * from StockHandleman where sh_sdcode='6' or sh_sdcode='7' order by sh_code";
                    RunSQL(dm1->Query1,szSQL,true);
                    while(!dm1->Query1->Eof)
                       {
                         m_lstStockmanID.Add(dm1->Query1->FieldByName("sh_code")->AsString.c_str());
                         lstStockman->Items->Add(dm1->Query1->FieldByName("sh_name")->AsString);
                         dm1->Query1->Next();
                        }
                     lstStockman->ItemIndex=0;
      }
if(g_theOperator.op_cpcode[0]=='G')
      { //若用户为宏昌公司，自动寻找宏昌的采购部门
              szSQL="select * from StockDepart where sd_code='10' order by sd_code";
                     RunSQL(dm1->Query1,szSQL,true);
                     while(!dm1->Query1->Eof)
                       {
                         m_lstStockDepID.Add(dm1->Query1->FieldByName("sd_code")->AsString.c_str());
                         lstStockDep->Items->Add(dm1->Query1->FieldByName("sd_name")->AsString);
                         dm1->Query1->Next();
                        }
                    lstStockDep->ItemIndex=0;

        //采购经办
                    m_lstStockmanID.Add("");
                    lstStockman->Items->Add("全部采购经办");
                    szSQL="select * from StockHandleman where sh_sdcode='10' order by sh_code";
                    RunSQL(dm1->Query1,szSQL,true);
                    while(!dm1->Query1->Eof)
                       {
                         m_lstStockmanID.Add(dm1->Query1->FieldByName("sh_code")->AsString.c_str());
                         lstStockman->Items->Add(dm1->Query1->FieldByName("sh_name")->AsString);
                         dm1->Query1->Next();
                        }
                     lstStockman->ItemIndex=0;
        }
/*	m_lstStockDepID.Add("");
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
	lstStockDep	->ItemIndex=0;
*/
//------------------------------------------------------------------------------
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
	lstType			->ItemIndex=0;        
//------------------------------------------------------------------------------
/*
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
*/
//------------------------------------------------------------------------------
	edtAfmDay->Text="7";

	FormResize(Sender);
  ResetCtrl();
}
//---------------------------------------------------------------------------

void TAPAffirmAndNotBookForm::ResetReqDepart()
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

void TAPAffirmAndNotBookForm::ResetCtrl()
{
	btnDetail->Enabled = lstView->Selected!=NULL;
}
void __fastcall TAPAffirmAndNotBookForm::FormResize(TObject *Sender)
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

void __fastcall TAPAffirmAndNotBookForm::btnQueryClick(TObject *Sender)
{
	TListItem *pItem;
	CString szSQL,szFilter,szTable,szTable2;
	char strTemp[256],strDate0[80],strDate1[80],strBuff[256];
	CStringArray lstDepID,lstDepName,lstFactID,lstFactName;
	int i,nSel,nDays;
	TDateTime tDate;

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

//	szSQL.Format("select * from %s,%s where m_apcode*=bf_apcode"
//		" order by m_apcode",szTable,szTable2);

	nDays=atoi(edtAfmDay->Text.c_str());
	tDate=GetSysTime(false);
	tDate-=nDays;

	sprintf(strTemp," and ap_affirmdate<'%s'",Time2DBDateString(tDate));

	szSQL="select * from AskPurchase,PurchaseDetail,materialno"
  	" where ap_code=substring(pd_code,1,7)"
    " and pd_endflag is null"
		" and mn_code=pd_mncode";
	szSQL+=strTemp;
	szSQL+=" and pd_code not in"
		"("
		" select distinct(bf_apcode) from BookFactory"
		")";
	szSQL+=szFilter;
  szSQL+=" and substring(pd_mncode,2,1)<>'M'";
	szSQL+=" order by ap_affirmdate,pd_code";

	RunSQL(dm1->Query1,szSQL,true);
	while(!dm1->Query1->Eof)
	{
		pItem=lstView->Items->Add();
		assert(pItem!=NULL);

		pItem->Caption=dm1->Query1->FieldByName("pd_code")->AsString;
		strcpy(strTemp,dm1->Query1->FieldByName("ap_buytype")->AsString.c_str());
		pItem->SubItems->Add(strTemp[0]=='M' ? "内购" : "外购");

		strcpy(strTemp,dm1->Query1->FieldByName("ap_sdcode")->AsString.c_str());
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
		
		strcpy(strTemp,dm1->Query1->FieldByName("ap_reqdepart")->AsString.c_str());
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

		strcpy(strTemp,dm1->Query1->FieldByName("ap_reqdepart")->AsString.c_str());
		for(i=0;i<lstDepID.GetSize();i++)
		{
			if(lstDepID[i]==strTemp)
			{
				pItem->SubItems->Add((LPCSTR)lstDepName[i]);
				break;
			}
		}
		if(i==lstDepID.GetSize())	pItem->SubItems->Add("");

		strcpy(strTemp,dm1->Query1->FieldByName("ap_type")->AsString.c_str());
		pItem->SubItems->Add(strTemp[0]=='I' ? "紧急" : "普通");

		pItem->SubItems->Add(DateField2Text(dm1->Query1->FieldByName("ap_reqdate")));
		pItem->SubItems->Add(DateField2Text(dm1->Query1->FieldByName("ap_needdate")));
//		pItem->SubItems->Add(dm1->Query1->FieldByName("m_mncode")->AsString);
		pItem->SubItems->Add(dm1->Query1->FieldByName("mn_name")->AsString);
		pItem->SubItems->Add(DateField2Text(dm1->Query1->FieldByName("ap_affirmdate")));

		strcpy(strTemp,dm1->Query1->FieldByName("ap_shcode")->AsString.c_str());
		for(i=1;i<m_lstStockmanID.GetSize();i++)
		{
			if(m_lstStockmanID[i]==strTemp)
			{
				pItem->SubItems->Add(lstStockman->Items->Strings[i]);
				break;
			}
		}
		if(i==m_lstStockmanID.GetSize())	pItem->SubItems->Add("");

		dm1->Query1->Next();
	}
}
//---------------------------------------------------------------------------

bool TAPAffirmAndNotBookForm::GetFilter(CString &szFilter)
{
	char strTemp[256],strDate0[80];
	int nSel;
  
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
	if((nSel=lstStockDep->ItemIndex)>=0 && nSel<m_lstStockDepID.GetSize())
//	if((nSel=lstStockDep->ItemIndex)>0 && nSel<m_lstStockDepID.GetSize())
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
	if(!edtAfmDay->Text.IsEmpty())
	{
		TDateTime tNow=GetSysTime(false);
		unsigned short year,month,day;

		tNow-=atoi(edtAfmDay->Text.c_str());
		tNow.DecodeDate(&year,&month,&day);
		sprintf(strTemp," and ap_affirmdate<'%04d-%02d-%02d'",year,month,day);
		szFilter+=strTemp;
	}

	return true;
}
void __fastcall TAPAffirmAndNotBookForm::lstViewClick(TObject *Sender)
{
	if(lstView->Selected==NULL)	ResetCtrl();
}
//---------------------------------------------------------------------------

void __fastcall TAPAffirmAndNotBookForm::lstViewDblClick(TObject *Sender)
{
	if(btnDetail->Enabled)
		btnDetailClick(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TAPAffirmAndNotBookForm::lstViewSelectItem(TObject *Sender,
      TListItem *Item, bool Selected)
{
	if(!Selected)	return;
	ResetCtrl();
}
//---------------------------------------------------------------------------

void __fastcall TAPAffirmAndNotBookForm::btnDetailClick(TObject *Sender)
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

void __fastcall TAPAffirmAndNotBookForm::btnToExcelClick(TObject *Sender)
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
				NULL);
		}
	}
	catch(...)
	{
	}
}
//---------------------------------------------------------------------------

#include "PrnApafmNotBook.h"
void __fastcall TAPAffirmAndNotBookForm::btnPrintClick(TObject *Sender)
{
	CString szSQL,szTable;
	int i;
	TListItem *pItem;
	TPrnApafmNotBookForm *pPrn;
	TDateTime tNow;

	szTable=GetTmpTableName();
	szSQL.Format("create table dbo.%s ("
		"m_apcode  varchar(20),"
		"m_aptype  varchar(20),"
		"m_sdname  varchar(80),"
		"m_corp    varchar(80),"
		"m_reqdep  varchar(80),"
		"m_type    varchar(20),"
		"m_apdate  varchar(20),"
		"m_needdate varchar(20),"
		"m_mnname  varchar(80),"
		"m_afmdate varchar(80),"
		"m_shname  varchar(80)"
		")",szTable);
	if(!RunSQL(dm1->Query1,szSQL))	return;

	for(i=0;i<lstView->Items->Count;i++)
	{
		pItem=lstView->Items->Item[i];
		szSQL.Format("insert into %s values(",szTable);
		szSQL+=Str2DBString(pItem->Caption.c_str());
		szSQL+=",";	szSQL+=Str2DBString(pItem->SubItems->Strings[0].c_str());
		szSQL+=",";	szSQL+=Str2DBString(pItem->SubItems->Strings[1].c_str());
		szSQL+=",";	szSQL+=Str2DBString(pItem->SubItems->Strings[2].c_str());
		szSQL+=",";	szSQL+=Str2DBString(pItem->SubItems->Strings[3].c_str());
		szSQL+=",";	szSQL+=Str2DBString(pItem->SubItems->Strings[4].c_str());
		szSQL+=",";	szSQL+=Str2DBString(pItem->SubItems->Strings[5].c_str());
		szSQL+=",";	szSQL+=Str2DBString(pItem->SubItems->Strings[6].c_str());
		szSQL+=",";	szSQL+=Str2DBString(pItem->SubItems->Strings[7].c_str());
		szSQL+=",";	szSQL+=Str2DBString(pItem->SubItems->Strings[8].c_str());
		szSQL+=",";	szSQL+=Str2DBString(pItem->SubItems->Strings[9].c_str());
		szSQL+=")";
		if(!RunSQL(dm1->Query1,szSQL))	goto DROP_TABLE;
	}

	pPrn=new TPrnApafmNotBookForm(this);
	assert(pPrn!=NULL);

	tNow=GetSysTime(false);
	pPrn->txtPrnTime->Caption=(LPCSTR)Time2DBTimeString(tNow);

	szSQL.Format("select * from %s",szTable);

	if(OpenQuery(dm1->sqlPrint,szSQL))
	{
		pPrn->PrnView->PreviewModal();
	}
	delete pPrn;

DROP_TABLE:
	szSQL.Format("drop table dbo.%s",szTable);
	RunSQL(dm1->Query1,szSQL);
}
//---------------------------------------------------------------------------

#include "AskPurchaseMT.h"
void __fastcall TAPAffirmAndNotBookForm::btnMaterPickupClick(TObject *Sender)
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


