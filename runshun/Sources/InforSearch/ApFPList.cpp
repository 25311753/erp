//---------------------------------------------------------------------------

#include <vcl.h>
#include <stdio.h>
#include <assert.h>
#pragma hdrstop


#include "DataModule.h"
#include "BaseCode.h"
#include "TConst.h"
#include "ApFPList.h"
#include "PrnApPFList.h"
#include "LdyInterface.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TApFPListForm *ApFPListForm;
//---------------------------------------------------------------------------

void ApFPList(int nAuth)
{
	if(nAuth==AUTH_NONE)	return;         //没有权限

	TApFPListForm *pForm;
  pForm=new TApFPListForm(Application);
  assert(pForm!=NULL);
  pForm->m_nAuthor=nAuth;
  pForm->ShowModal();
  delete pForm;
}


__fastcall TApFPListForm::TApFPListForm(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------


void __fastcall TApFPListForm::btnExitClick(TObject *Sender)
{
        Close();
}
//---------------------------------------------------------------------------
void __fastcall TApFPListForm::btnQueryClick(TObject *Sender)
{
	CString szSQL;
	TListItem *pItem;
	int i,nSel;
	char strFile0[80],strFile1[80],strTemp[256],strCorp[80],strTemp1[256],strTemp2[256],strTemp3[256];

	szSQL="select * from AskPurchase,PurchaseDetail,BookFactory,DecideFactory,materialno,DepartCorp,FilePage,Manufactur,StockHandleman"
		" where   ap_code=substring(pd_code,1,7)"
                " and     pd_code=bf_apcode"
                " and     pd_code=df_apcode"
                " and     dc_code=substring(ap_reqdepart,1,2)"
                " and     pd_mncode=mn_code"
                " and     fp_apcode=ap_code"
                " and     mf_code=df_mfdecide"
                " and     substring(pd_code,8,1)='1'"
                " and     ap_shcode=sh_code";


	sprintf(strFile0,"%s",edtFile0->Text);
	sprintf(strFile1,"%s",edtFile1->Text);
	sprintf(strTemp," and fp_fno between '%s' and '%s'",strFile0,strFile1);
	szSQL+=strTemp;

	szSQL+=" order by fp_fno";

	lstView->Items->Clear();

	RunSQL(dm1->Query1,szSQL,true);
	while(!dm1->Query1->Eof)
	{
		pItem=lstView->Items->Add();
		assert(pItem!=NULL);
/*		strcpy(strCorp,dm1->Query1->FieldByName("ap_reqdepart")->AsString.c_str());

		for(i=0;i<lstCorp.GetSize();i++)
		{
			if(strcmp(lstCorp[i].strCode,strCorp)==0)
			{
				pItem->Caption=lstCorp[i].strName;
				break;
			}
		}
		if(i==lstCorp.GetSize())	pItem->Caption="";
*/
                strncpy(strTemp1,dm1->Query1->FieldByName("ap_affirmdate")->AsString.c_str(),10);
                strncpy(strTemp2,dm1->Query1->FieldByName("df_plandate")->AsString.c_str(),10);
                strncpy(strTemp3,dm1->Query1->FieldByName("df_decidedate")->AsString.c_str(),10);

		pItem->Caption=dm1->Query1->FieldByName("dc_name")->AsString;
		pItem->SubItems->Add(dm1->Query1->FieldByName("fp_fno")->AsString);
		pItem->SubItems->Add(dm1->Query1->FieldByName("fp_apcode")->AsString);
//		pItem->SubItems->Add(Field2TimeString(dm1->Query1->FieldByName("ap_affirmdate")));
		pItem->SubItems->Add(strTemp1);
		pItem->SubItems->Add(dm1->Query1->FieldByName("mn_name")->AsString);
		pItem->SubItems->Add(dm1->Query1->FieldByName("sh_name")->AsString);
		pItem->SubItems->Add(dm1->Query1->FieldByName("mf_shortname")->AsString);
		pItem->SubItems->Add(dm1->Query1->FieldByName("bf_price")->AsString);
//		pItem->SubItems->Add(Field2TimeString(dm1->Query1->FieldByName("df_plandate")));
		pItem->SubItems->Add(strTemp2);
//		pItem->SubItems->Add(Field2TimeString(dm1->Query1->FieldByName("df_decidedate")));
		pItem->SubItems->Add(strTemp2);
		pItem->SubItems->Add(dm1->Query1->FieldByName("fp_rem")->AsString);
		pItem->SubItems->Add(dm1->Query1->FieldByName("fp_pno")->AsString);
		dm1->Query1->Next();
	}
}
//---------------------------------------------------------------------------

void __fastcall TApFPListForm::btnToExcelClick(TObject *Sender)
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
                                        NULL);
		}
	}
	catch(...)
	{
	}
}
//---------------------------------------------------------------------------

void __fastcall TApFPListForm::btnPrintClick(TObject *Sender)
{
	CString szSQL,szTable;
	TListItem *pItem;
	int i;
        char strTemp[80];
	TPrnApFPListForm *pPrn;

	szTable=GetTmpTableName();
	szSQL.Format("create table dbo.%s("
		"m_id int,"
		"m_corp varchar(80),"
		"m_fpfno varchar(80),"
		"m_apcode varchar(20),"
		"m_afmdate varchar(20),"
		"m_mnname varchar(80),"
		"m_sh varchar(20),"
		"m_bfcorp varchar(80),"
		"m_dfprice varchar(80),"
		"m_showdate varchar(20),"
		"m_bfdate varchar(20),"
		"m_dfplanrem varchar(80),"
		"m_fppno varchar(20),"
		")",szTable);
	
	try
	{
		BeginTransact();
		RunTransactSQL(szSQL);

		for(i=0;i<lstView->Items->Count;i++)
		{
			pItem=lstView->Items->Item[i];
			szSQL.Format("insert into %s values(",szTable);
			szSQL+=Int2DBString(i+1);
			szSQL+=",";	szSQL+=Str2DBString(pItem->Caption.c_str());
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
			szSQL+=",";	szSQL+=Str2DBString(pItem->SubItems->Strings[10].c_str());
//			szSQL+=",";	szSQL+=Str2DBString(pItem->SubItems->Strings[11].c_str());
			szSQL+=")";
			if(!RunTransactSQL(szSQL))	goto DROP_TABLE;
		}
		CommitTransact();
	}
	catch(...)
	{
		goto DROP_TABLE;
	}

	pPrn=new TPrnApFPListForm(this);
	assert(pPrn!=NULL);

	szSQL.Format("select * from %s order by m_id",szTable);
	if(!OpenQuery(dm1->sqlPrint,szSQL))	goto DROP_TABLE;
	pPrn->PrnView->PreviewModal();
	delete pPrn;

DROP_TABLE:
	szSQL.Format("drop table dbo.%s",szTable);
	RunSQL(dm1->Query1,szSQL);
}
//---------------------------------------------------------------------------



