//---------------------------------------------------------------------------

#include <vcl.h>
#include <stdio.h>
#include <assert.h>
#pragma hdrstop

#include "DataModule.h"
#include "BaseCode.h"
#include "StuffBookList.h"
#include "TConst.h"
#include "LdyInterface.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TStuffBookListForm *StuffBookListForm;

//=====================================================================================
//原料采购记录表接口，文件：StuffBookList.*
void StuffBookList(int nAuth)
{
	CALL_FORM(TStuffBookListForm);
}

void StuffBookList(LPCSTR lpszID,int nAuth)
{
	TStuffBookListForm *pForm;
  pForm=new TStuffBookListForm(Application);
  assert(pForm!=NULL);
  pForm->m_szIDFirst=lpszID;
  pForm->ShowModal();
  delete pForm;
}
//--------------------------------------------------------------------

//---------------------------------------------------------------------------
__fastcall TStuffBookListForm::TStuffBookListForm(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TStuffBookListForm::btnExitClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------
void __fastcall TStuffBookListForm::FormShow(TObject *Sender)
{
	int nYear,nMonth,nDay;
  char strDate0[80],strDate1[80];

  GetSysDate(nYear,nMonth,nDay,false);
  sprintf(strDate0,"%04d%02d%02d",nYear,nMonth,1);
  sprintf(strDate1,"%04d%02d%02d",nYear,nMonth,nDay);
  edtDate0->Text=strDate0;
  edtDate1->Text=strDate1;

	edtMNCode->Text="";
	edtFactCard->Text="";
  edtDPName->Text="";

  ResetCtrl();
//  if(!m_szIDFirst.IsEmpty())
//	{
//		edtMNCode->Text=m_szIDFirst;
//    CString szSQL;
//    szSQL.Format("select * from materialno where mn_code='%s'",m_szIDFirst.c_str());
//		RunSQL(dm1->Query1,szSQL,true);
//    txtName->Caption=dm1->Query1->FieldByName("mn_name")->AsString;
//		btnQueryClick(Sender);
//  }
}
//---------------------------------------------------------------------------
void __fastcall TStuffBookListForm::btnQueryClick(TObject *Sender)
{
	CString szSQL,szFilter;
	TListItem *pItem;
	char strCode[80],strCorp[80],strDate0[80],strDate1[80],strTemp[256];
 	TDateTime tDate;
  int nYear,nMonth,nDay;

	edtDate0->Text=edtDate0->Text.Trim();
	if(edtDate0->Text.IsEmpty())
	{
		ShowMessage("请输入开始日期");
		if(edtDate0->CanFocus())	edtDate0->SetFocus();
		return;
	}
  if(edtDate0->Text.Length()!=8)
  {
    ShowMessage("不合法的日期格式，日期格式为：yyyymmdd");
    if(edtDate0->CanFocus())	edtDate0->SetFocus();
    return;
  }
  Date2YYMMDD(edtDate0->Text.c_str(),nYear,nMonth,nDay);
  try
  {
    tDate=TDateTime(nYear,nMonth,nDay);
  }
  catch(...)
  {
    ShowMessage("不合法的日期格式，日期格式为：yyyymmdd");
    if(edtDate0->CanFocus())	edtDate0->SetFocus();
    return;
  }
	sprintf(strDate0,"%04d-%02d-%02d",nYear,nMonth,nDay);

	edtDate1->Text=edtDate1->Text.Trim();
	if(edtDate1->Text.IsEmpty())
	{
		ShowMessage("请输入截止日期");
		if(edtDate1->CanFocus())	edtDate1->SetFocus();
		return;
	}
  if(edtDate1->Text.Length()!=8)
  {
    ShowMessage("不合法的日期格式，日期格式为：yyyymmdd");
    if(edtDate1->CanFocus())	edtDate1->SetFocus();
    return;
  }
  Date2YYMMDD(edtDate1->Text.c_str(),nYear,nMonth,nDay);
  try
  {
    tDate=TDateTime(nYear,nMonth,nDay);
  }
  catch(...)
  {
    ShowMessage("不合法的日期格式，日期格式为：yyyymmdd");
    if(edtDate1->CanFocus())	edtDate1->SetFocus();
    return;
  }
	sprintf(strDate1,"%04d-%02d-%02d",nYear,nMonth,nDay);

  if(!edtMNCode->Text.IsEmpty())
	{
  	sprintf(strTemp," and mn_code like '%s%%'",edtMNCode->Text.c_str());
    szFilter+=strTemp;
	}
  if(!edtDPName->Text.IsEmpty())
	{
  	sprintf(strTemp," and mn_name like '%%%s%%'",edtDPName->Text.c_str());
    szFilter+=strTemp;
  }
  if(!edtFactCard->Text.IsEmpty())
  {
  	sprintf(strTemp," and bf_mfcard like '%%%s%%'",edtFactCard->Text.c_str());
    szFilter+=strTemp;
  }

	if(operatorcode=="admin")	strcpy(strCorp,"_");
	else	strcpy(strCorp,g_theOperator.op_cpcode);
	sprintf(strCode,"%sM%%",strCorp);                                       //只查自己公司的原料

	lstView->Items->Clear();

	szSQL.Format("select bf_bookdate,bf_code,bf_apcode,mf_shortname,bf_mfcard,bf_count,bf_price,mn_code,mn_name"
		" from BookFactory,Manufactur,PurchaseDetail,materialno"
		" where bf_mfcode=mf_code and bf_apcode=pd_code and pd_mncode like '%s'"
    " and pd_mncode=mn_code"
		" and bf_bookdate between '%s' and '%s'",strCode,strDate0,strDate1);
//		" union"
//		" select bf_bookdate,bf_code,bf_apcode,mf_shortname,bf_mfcard,bf_count,bf_price "
//		" from BookFactory,Manufactur,TreatStock"
//		" where bf_mfcode=mf_code and bf_apcode=ts_code and ts_mncode='%s'",strCode,strCode);
	szSQL+=szFilter;
	szSQL+=" order by bf_bookdate";

	RunSQL(dm1->Query1,szSQL,true);
//------new 0707-------宏信宏纶的除了吴总其它不可查看单价-----------------------
        if(g_theOperator.op_cpcode[0]=='E' && operatorcode!="180079")
        {
        	while(!dm1->Query1->Eof)
	{
		pItem=lstView->Items->Add();
		assert(pItem!=NULL);
		pItem->Caption=DateField2Text(dm1->Query1->FieldByName("bf_bookdate"));
		pItem->SubItems->Add(dm1->Query1->FieldByName("bf_code")->AsString);
		pItem->SubItems->Add(dm1->Query1->FieldByName("bf_apcode")->AsString);
		pItem->SubItems->Add(dm1->Query1->FieldByName("mf_shortname")->AsString);
		pItem->SubItems->Add(dm1->Query1->FieldByName("bf_mfcard")->AsString);
		pItem->SubItems->Add(FloatField2String(dm1->Query1->FieldByName("bf_count"),2));
		pItem->SubItems->Add("");
		pItem->SubItems->Add(dm1->Query1->FieldByName("mn_code")->AsString);
		pItem->SubItems->Add(dm1->Query1->FieldByName("mn_name")->AsString);

		dm1->Query1->Next();
	}
        }
        else
        {
        	while(!dm1->Query1->Eof)
	{
		pItem=lstView->Items->Add();
		assert(pItem!=NULL);
		pItem->Caption=DateField2Text(dm1->Query1->FieldByName("bf_bookdate"));
		pItem->SubItems->Add(dm1->Query1->FieldByName("bf_code")->AsString);
		pItem->SubItems->Add(dm1->Query1->FieldByName("bf_apcode")->AsString);
		pItem->SubItems->Add(dm1->Query1->FieldByName("mf_shortname")->AsString);
		pItem->SubItems->Add(dm1->Query1->FieldByName("bf_mfcard")->AsString);
		pItem->SubItems->Add(FloatField2String(dm1->Query1->FieldByName("bf_count"),2));
		pItem->SubItems->Add(FloatField2String(dm1->Query1->FieldByName("bf_price"),2));
		pItem->SubItems->Add(dm1->Query1->FieldByName("mn_code")->AsString);
		pItem->SubItems->Add(dm1->Query1->FieldByName("mn_name")->AsString);

		dm1->Query1->Next();
	}
        }

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
/*	while(!dm1->Query1->Eof)
	{
		pItem=lstView->Items->Add();
		assert(pItem!=NULL);
		pItem->Caption=DateField2Text(dm1->Query1->FieldByName("bf_bookdate"));
		pItem->SubItems->Add(dm1->Query1->FieldByName("bf_code")->AsString);
		pItem->SubItems->Add(dm1->Query1->FieldByName("bf_apcode")->AsString);
		pItem->SubItems->Add(dm1->Query1->FieldByName("mf_shortname")->AsString);
		pItem->SubItems->Add(dm1->Query1->FieldByName("bf_mfcard")->AsString);
		pItem->SubItems->Add(FloatField2String(dm1->Query1->FieldByName("bf_count"),2));
		pItem->SubItems->Add(FloatField2String(dm1->Query1->FieldByName("bf_price"),2));
		pItem->SubItems->Add(dm1->Query1->FieldByName("mn_code")->AsString);
		pItem->SubItems->Add(dm1->Query1->FieldByName("mn_name")->AsString);

		dm1->Query1->Next();
	}       */
//------------------------------------------------------------------------------
}
//---------------------------------------------------------------------------


void __fastcall TStuffBookListForm::btnToBookClick(TObject *Sender)
{
	TListItem *pItem;

  if((pItem=lstView->Selected)==NULL)	return;

	int nRight=GetOperatorRight(operatorcode.c_str(),"IDM_BOOKFACTORY");
	//订购单输入接口，文件：BookFactory.*
	BookFactory(pItem->SubItems->Strings[0].c_str(),nRight);
}
//---------------------------------------------------------------------------

void __fastcall TStuffBookListForm::btnToPurchaseClick(TObject *Sender)
{
	TListItem *pItem;
  char strID[80];

  if((pItem=lstView->Selected)==NULL)	return;
  strcpy(strID,pItem->SubItems->Strings[1].c_str());
  if(strID[0]=='\0')	return;
  if(strID[0]=='P')
	{
	  strID[strlen(strID)-1]='\0';
		int nRight=GetOperatorRight(operatorcode.c_str(),"IDM_ASKPURCHASE");
		//请购单输入接口，文件：AskPurchase.*
		AskPurchase(strID,nRight);
  }
  else
  {
		int nRight=GetOperatorRight(operatorcode.c_str(),"IDM_TREATSTOCK");
		//合约采购档接口，文件：TreatStock.*
		TreatStock(strID,nRight);
  }
}
//---------------------------------------------------------------------------

void TStuffBookListForm::ResetCtrl()
{
	btnToBook->Enabled = lstView->Selected!=NULL;
	btnToPurchase->Enabled = lstView->Selected!=NULL;
}
void __fastcall TStuffBookListForm::lstViewClick(TObject *Sender)
{
	if(lstView->Selected==NULL)	ResetCtrl();	
}
//---------------------------------------------------------------------------
void __fastcall TStuffBookListForm::lstViewSelectItem(TObject *Sender,
      TListItem *Item, bool Selected)
{
	if(!Selected)	return;
  ResetCtrl();
}
//---------------------------------------------------------------------------
void __fastcall TStuffBookListForm::btnToExcelClick(TObject *Sender)
{
	Variant vExcel,vSheet;
  int nRow,i;
  TListItem *pItem;

  try
  {
	  nRow=1;
		if(!OpenExcel("采购记录表.xls",vExcel,vSheet))	return;
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
				NULL);
		}
	}
	catch(...)
	{
	}
}
//---------------------------------------------------------------------------

#include "PrnStuffBookList.h"

void __fastcall TStuffBookListForm::btnPrintClick(TObject *Sender)
{
	TPrnStuffBookListForm *pPrn;
  CString szSQL,szTable;
	int i;
	TListItem *pItem;

  szTable=GetTmpTableName();
  szSQL.Format("create table dbo.%s ("
		"m_date   varchar(80),"
		"m_bookid varchar(80),"
		"m_mfname varchar(80),"
		"m_mfcard varchar(80),"
		"m_count  varchar(20),"
		"m_price  varchar(20),"
    "m_mncode varchar(80),"
    "m_mnname varchar(80)"
		")",szTable);
	if(!RunSQL(dm1->Query1,szSQL))	return;

	for(i=0;i<lstView->Items->Count;i++)
	{
		pItem=lstView->Items->Item[i];
		szSQL.Format("insert into %s values(",szTable);
		szSQL+=Str2DBString(pItem->Caption.c_str());
		szSQL+=",";	szSQL+=Str2DBString(pItem->SubItems->Strings[0].c_str());
		szSQL+=",";	szSQL+=Str2DBString(pItem->SubItems->Strings[2].c_str());
		szSQL+=",";	szSQL+=Str2DBString(pItem->SubItems->Strings[3].c_str());
		szSQL+=",";	szSQL+=Str2DBString(pItem->SubItems->Strings[4].c_str());
		szSQL+=",";	szSQL+=Str2DBString(pItem->SubItems->Strings[5].c_str());
		szSQL+=",";	szSQL+=Str2DBString(pItem->SubItems->Strings[6].c_str());
		szSQL+=",";	szSQL+=Str2DBString(pItem->SubItems->Strings[7].c_str());
		szSQL+=")";
		if(!RunSQL(dm1->Query1,szSQL))	goto DROP_TABLE;
	}

  pPrn=new TPrnStuffBookListForm(this);
  assert(pPrn!=NULL);

//  pPrn->txtMNCode->Caption=edtMNCode->Text;
//  pPrn->txtName->Caption=txtName->Caption;
  
	szSQL.Format("select * from %s order by m_date",szTable);
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

void __fastcall TStuffBookListForm::btnPickupClick(TObject *Sender)
{
	TAskPurchaseMTForm *pMT;
	pMT=new TAskPurchaseMTForm(this);
	assert(pMT!=NULL);
	pMT->m_szMaterCode=edtMNCode->Text;
	if(pMT->ShowModal()==mrOk)
	{
		edtMNCode->Text=pMT->m_szMaterCode;
	}
	delete pMT;
}
//---------------------------------------------------------------------------

