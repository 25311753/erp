//---------------------------------------------------------------------------

#include <vcl.h>
#include <stdio.h>
#include <assert.h>
#pragma hdrstop

#include "DataModule.h"
#include "BaseCode.h"
#include "BookNotAcceptList.h"
#include "LdyInterface.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TBookNotAcceptListForm *BookNotAcceptListForm;

//-----------------------------------------------------------------------------
//已订购未受料明细接口，文件：BookNotAcceptList.*
void BookNotAcceptList(int nAuth)
{
	CALL_FORM(TBookNotAcceptListForm);
}
//------------------------------------------------------------------------------

//---------------------------------------------------------------------------
__fastcall TBookNotAcceptListForm::TBookNotAcceptListForm(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TBookNotAcceptListForm::FormShow(TObject *Sender)
{
	CString szSQL;
        unsigned short year,month,day;
	edtDays->Text="2";

	m_lstCorpID.Add("");
	lstCorp->Items->Add("全部");

	szSQL="select * from DepartCorp order by dc_code";
	RunSQL(dm1->Query1,szSQL,true);
	while(!dm1->Query1->Eof)
	{
		m_lstCorpID.Add(dm1->Query1->FieldByName("dc_code")->AsString.c_str());
		lstCorp->Items->Add(dm1->Query1->FieldByName("dc_name")->AsString);

		dm1->Query1->Next();
	}
	lstCorp->ItemIndex=0;

	m_lstDepartID.Add("");
	lstDepart->Items->Add("全部");
	szSQL="select * from StockDepart order by sd_code";
	RunSQL(dm1->Query1,szSQL,true);
	while(!dm1->Query1->Eof)
	{
		m_lstDepartID.Add(dm1->Query1->FieldByName("sd_code")->AsString.c_str());
		lstDepart->Items->Add(dm1->Query1->FieldByName("sd_name")->AsString);
		dm1->Query1->Next();
	}
	lstDepart->ItemIndex=0;

	m_lstAskDepID.Add("");
  lstAskDep->Items->Add("全部");
	szSQL="select * from DicDepart,DepartCorp where dc_code=substring(dd_code,1,2) order by dd_code";
	RunSQL(dm1->Query1,szSQL,true);
	while(!dm1->Query1->Eof)
	{
		m_lstAskDepID.Add(dm1->Query1->FieldByName("dd_code")->AsString.c_str());
		lstAskDep->Items->Add(dm1->Query1->FieldByName("dc_name")->AsString
    	+dm1->Query1->FieldByName("dd_name")->AsString);
		dm1->Query1->Next();
	}
	lstAskDep->ItemIndex=0;

	m_lstFactID.Add("");
	lstFact->Items->Add("全部");
	szSQL="select * from Manufactur order by mf_code";
	RunSQL(dm1->Query1,szSQL,true);
	while(!dm1->Query1->Eof)
	{
		m_lstFactID.Add(dm1->Query1->FieldByName("mf_code")->AsString.c_str());
		lstFact->Items->Add(dm1->Query1->FieldByName("mf_shortname")->AsString);
		dm1->Query1->Next();
	}
	lstFact->ItemIndex=0;

        TDateTime tNow;
        tNow=GetSysTime(false);
        tNow.DecodeDate(&year,&month,&day);
        DateTimePicker1->Date=tNow;
        DateTimePicker2->Date=tNow;
}
//---------------------------------------------------------------------------

void __fastcall TBookNotAcceptListForm::btnQueryClick(TObject *Sender)
{
	int nDays,nYear,nMonth,nDay;
	CString szSQL;
	TListItem *pItem;
	char strTemp[256];
	int nSel,i;
        char strDate0[80],strDate1[80];
        unsigned short year0,month0,day0,year1,month1,day1;

	GetSysDate(nYear,nMonth,nDay,false);
	lstView->Items->Clear();

	edtDays->Text=edtDays->Text.Trim();
	if(edtDays->Text.IsEmpty())
	{
		ShowMessage("请输入宽放天数");
		if(edtDays->CanFocus())	edtDays->SetFocus();
		return;
	}
	if(!StringIsInt(edtDays->Text.c_str()) || (nDays=atoi(edtDays->Text.c_str()))<0)
	{
		ShowMessage("请输入整数");
		if(edtDays->CanFocus())	edtDays->SetFocus();
		return;
	}

	szSQL.Format("select * from BookFactory,PurchaseDetail,materialno,AskPurchase,Manufactur,StockHandleman"
		" where pd_code=bf_apcode"
		" and substring(pd_mncode,2,1)<>'M'"
		" and mn_code=pd_mncode"
    " and pd_endflag is null"
    " and ap_shcode=sh_code"
		" and ap_code=substring(pd_code,1,7)"
    " and bf_mfcode*=mf_code"
		" and bf_bookdate+bf_deliverdays+%d<'%04d-%02d-%02d'",nDays,nYear,nMonth,nDay);
        DateTimePicker1->DateTime.DecodeDate(&year0,&month0,&day0);
        sprintf(strDate0,"%04d-%02d-%02d",year0,month0,day0);
        DateTimePicker2->DateTime.DecodeDate(&year1,&month1,&day1);
        sprintf(strDate1,"%04d-%02d-%02d",year1,month1,day1);
        sprintf(strTemp," and bf_bookdate between '%s' and '%s'",strDate0,strDate1);
        szSQL+=strTemp;
	if((nSel=lstCorp->ItemIndex)>0 && nSel<m_lstCorpID.GetSize())
	{
		sprintf(strTemp," and substring(ap_reqdepart,1,2)='%s'",m_lstCorpID[nSel]);
		szSQL+=strTemp;
	}
	if((nSel=lstAskDep->ItemIndex)>0 && nSel<m_lstAskDepID.GetSize())
	{
		sprintf(strTemp," and ap_reqdepart='%s'",m_lstAskDepID[nSel]);
		szSQL+=strTemp;
	}
	if((nSel=lstDepart->ItemIndex)>0 && nSel<m_lstDepartID.GetSize())
	{
		sprintf(strTemp," and ap_sdcode='%s'",m_lstDepartID[nSel]);
		szSQL+=strTemp;
	}

	if((nSel=lstFact->ItemIndex)>0 && nSel<m_lstFactID.GetSize())
	{
		sprintf(strTemp," and bf_mfcode='%s'",m_lstFactID[nSel]);
		szSQL+=strTemp;
	}

	szSQL+=" and  bf_code not in"
		"("
		"select distinct(am_bfcode) from acceptmate"
		")"
		" order by bf_bookdate";
    RunSQL(dm1->Query1,szSQL,true);
	while(!dm1->Query1->Eof)
	{
		pItem=lstView->Items->Add();
		assert(pItem!=NULL);
		pItem->Caption=dm1->Query1->FieldByName("bf_code")->AsString;
		pItem->SubItems->Add(DateField2Text(dm1->Query1->FieldByName("bf_bookdate")));
		pItem->SubItems->Add(IntField2Text(dm1->Query1->FieldByName("bf_deliverdays")));
		pItem->SubItems->Add(dm1->Query1->FieldByName("mn_code")->AsString);
		pItem->SubItems->Add(dm1->Query1->FieldByName("mn_name")->AsString);
		strcpy(strTemp,dm1->Query1->FieldByName("ap_reqdepart")->AsString.c_str());
		strTemp[2]='\0';
		for(i=1;i<m_lstCorpID.GetSize();i++)
		{
			if(m_lstCorpID[i]==strTemp)
			{
				pItem->SubItems->Add(lstCorp->Items->Strings[i]);
				break;
			}
		}
		if(i==m_lstCorpID.GetSize())	pItem->SubItems->Add("");

		for(i=1;i<m_lstAskDepID.GetSize();i++)
		{
			if(m_lstAskDepID[i]==dm1->Query1->FieldByName("ap_reqdepart")->AsString.c_str())
			{
				pItem->SubItems->Add(lstAskDep->Items->Strings[i]);
				break;
			}
		}
		if(i==m_lstAskDepID.GetSize())	pItem->SubItems->Add("");

		for(i=1;i<m_lstDepartID.GetSize();i++)
		{
			if(m_lstDepartID[i]==dm1->Query1->FieldByName("ap_sdcode")->AsString.c_str())
			{
				pItem->SubItems->Add(lstDepart->Items->Strings[i]);
				break;
			}
		}
		if(i==m_lstDepartID.GetSize())	pItem->SubItems->Add("");

    pItem->SubItems->Add(FloatField2String(dm1->Query1->FieldByName("bf_count"),2));
    pItem->SubItems->Add(dm1->Query1->FieldByName("mf_shortname")->AsString);
    pItem->SubItems->Add(dm1->Query1->FieldByName("pd_code")->AsString);
    pItem->SubItems->Add(dm1->Query1->FieldByName("sh_name")->AsString);

		dm1->Query1->Next();
	}
// ShowMessage(szSQL.s)
}
//---------------------------------------------------------------------------

void __fastcall TBookNotAcceptListForm::btnToExcelClick(TObject *Sender)
{
	Variant vExcel,vSheet;
  int nRow,i;
  TListItem *pItem;

  try
  {
	  nRow=1;
		if(!OpenExcel("已订购未受料明细.xls",vExcel,vSheet))	return;
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
				NULL);
		}
	}
	catch(...)
	{
	}
}

//---------------------------------------------------------------------------

void __fastcall TBookNotAcceptListForm::btnExitClick(TObject *Sender)
{
	Close();	
}
//---------------------------------------------------------------------------

#include "FactorySearch.h"
void __fastcall TBookNotAcceptListForm::btnFactPickupClick(TObject *Sender)
{
	TFactorySearchForm *pForm;
  int i;

  pForm=new TFactorySearchForm(this);
  assert(pForm!=NULL);
  if(pForm->ShowModal()==mrOk && !pForm->m_szID.IsEmpty())
  {
  	for(i=0;i<m_lstFactID.GetSize();i++)
    {
    	if(m_lstFactID[i]==pForm->m_szID)
      {
      	lstFact->ItemIndex=i;
        break;
      }
    }
  }
  delete pForm;
}
//---------------------------------------------------------------------------
 #include "PrnBookNotAccept.h"
void __fastcall TBookNotAcceptListForm::btnprintClick(TObject *Sender)
{
  CString szSQL,szTable;
  int i;
  TListItem *pItem;
  TPrnBookNotAcceptForm *pPrn;
  TDateTime tNow;

  szTable=GetTmpTableName();
  szSQL.Format("create table dbo.%s ("
               "m_bookid varchar(20),"
               "m_date varchar(20),"
               "m_days varchar(4),"
               "m_mncode varchar(25),"
               "m_mnname varchar(80),"
               "m_corp varchar(20),"
               "m_sdname varchar(20)"
               ")",szTable);

  if(!RunSQL(dm1->Query1,szSQL))  return;
  //if(lstView->Items->Count>0)
    //lstView->SelectAll();

  for(i=0;i<lstView->Items->Count;i++)
   {
    pItem=lstView->Items->Item[i];
    szSQL.Format("insert into %s values(",szTable);
    szSQL+=Str2DBString(pItem->Caption.c_str());
    szSQL+=",";    szSQL+=Str2DBString(pItem->SubItems->Strings[0].c_str());
    szSQL+=",";    szSQL+=Str2DBString(pItem->SubItems->Strings[1].c_str());
    szSQL+=",";    szSQL+=Str2DBString(pItem->SubItems->Strings[2].c_str());
    szSQL+=",";    szSQL+=Str2DBString(pItem->SubItems->Strings[3].c_str());
    szSQL+=",";    szSQL+=Str2DBString(pItem->SubItems->Strings[4].c_str());
    szSQL+=",";    szSQL+=Str2DBString(pItem->SubItems->Strings[6].c_str());
    szSQL+=")";
    if(!RunSQL(dm1->Query1,szSQL))  goto DROP_TABLE;
   }

  pPrn=new TPrnBookNotAcceptForm(this);
  assert(pPrn!=NULL);
  tNow=GetSysTime(false);
  pPrn->txtPrnTime->Caption=(LPCSTR)Time2DBTimeString(tNow);
  szSQL.Format("select * from %s order by m_bookid",szTable);

  if(RunSQL(dm1->sqlPrint,szSQL,true))
   {pPrn->PrnView->PreviewModal();}
  delete pPrn;

  DROP_TABLE:
    szSQL.Format("drop table dbo.%s",szTable);
    RunSQL(dm1->Query1,szSQL);
}
//---------------------------------------------------------------------------

