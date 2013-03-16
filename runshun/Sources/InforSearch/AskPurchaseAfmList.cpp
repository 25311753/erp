//---------------------------------------------------------------------------

#include <vcl.h>
#include <stdio.h>
#include <assert.h>
#pragma hdrstop

#include "DataModule.h"
#include "BaseCode.h"
#include "AskPurchaseAfmList.h"
#include "PrnPurchaseAfmList.h"

#include "TConst.h"

#include "LdyInterface.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TAskPurchaseAfmListForm *AskPurchaseAfmListForm;

//============================================================================
//新接案件统计报表接口，文件：AskPurchaseAfmList.*
void AskPurchaseAfmList(int nAuth)
{
	CALL_FORM(TAskPurchaseAfmListForm);
}

//---------------------------------------------------------------------------
__fastcall TAskPurchaseAfmListForm::TAskPurchaseAfmListForm(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TAskPurchaseAfmListForm::btnExitClick(TObject *Sender)
{
	Close();	
}
//---------------------------------------------------------------------------
void __fastcall TAskPurchaseAfmListForm::FormShow(TObject *Sender)
{
	CString szSQL;
	unsigned short year,month,day,hour,minute,sec,msec;

	lstDepart->Items->Add("全部");
	m_lstDepartID.Add("");

	szSQL="select * from StockDepart order by sd_code";
	RunSQL(dm1->Query1,szSQL,true);
	while(!dm1->Query1->Eof)
	{
		m_lstDepartID.Add(dm1->Query1->FieldByName("sd_code")->AsString.c_str());
		lstDepart->Items->Add(dm1->Query1->FieldByName("sd_name")->AsString);
		dm1->Query1->Next();
	}
	lstDepart->ItemIndex=0;

	TDateTime tNow;
	tNow=GetSysTime(false);
	tNow.DecodeDate(&year,&month,&day);
	tNow.DecodeTime(&hour,&minute,&sec,&msec);
	ctlDate0->DateTime=tNow;
	ctlDate1->DateTime=tNow;
	if(hour<=12)
	{
		ctlTime0->DateTime=TDateTime(0,0,0,0);
		ctlTime1->DateTime=TDateTime(11,59,59,0);
	}
	else
	{
		ctlTime0->DateTime=TDateTime(12,0,0,0);
		ctlTime1->DateTime=TDateTime(23,59,59,0);
	}
}
//---------------------------------------------------------------------------

void __fastcall TAskPurchaseAfmListForm::btnQueryClick(TObject *Sender)
{
	CString szSQL;
	TListItem *pItem;
	int i,nSel;
	CArray<BASE2COLDATA,BASE2COLDATA>lstSH,lstCorp,lstType;
	BASE2COLDATA rwSH;
	char strDate0[80],strDate1[80],strTemp[256],strCorp[80];
	unsigned short year0,month0,day0,year1,month1,day1,hour0,minute0,sec0,msec0,hour1,minute1,sec1,msec1;

	szSQL="select * from diclargetype order by lt_code";
	RunSQL(dm1->Query1,szSQL,true);
	while(!dm1->Query1->Eof)
	{
		strcpy(rwSH.strCode,dm1->Query1->FieldByName("lt_code")->AsString.c_str());
		strcpy(rwSH.strName,dm1->Query1->FieldByName("lt_name")->AsString.c_str());
		lstType.Add(rwSH);
		dm1->Query1->Next();
	}

	szSQL="select * from StockHandleman order by sh_code";
	RunSQL(dm1->Query1,szSQL,true);
	while(!dm1->Query1->Eof)
	{
		strcpy(rwSH.strCode,dm1->Query1->FieldByName("sh_code")->AsString.c_str());
		strcpy(rwSH.strName,dm1->Query1->FieldByName("sh_name")->AsString.c_str());
		lstSH.Add(rwSH);
		dm1->Query1->Next();
	}

	szSQL="select * from DepartCorp order by dc_code";
	RunSQL(dm1->Query1,szSQL,true);
	while(!dm1->Query1->Eof)
	{
		strcpy(rwSH.strCode,dm1->Query1->FieldByName("dc_code")->AsString.c_str());
		strcpy(rwSH.strName,dm1->Query1->FieldByName("dc_name")->AsString.c_str());
		lstCorp.Add(rwSH);
		dm1->Query1->Next();
	}

	szSQL="select * from AskPurchase,PurchaseDetail,materialno,DecideFactory"
		" where ap_code=substring(pd_code,1,7)"
		" and substring(pd_mncode,2,1)<>'M'"
		" and pd_mncode=mn_code"
		" and pd_code*=df_apcode";
	ctlDate0->DateTime.DecodeDate(&year0,&month0,&day0);
	ctlTime0->DateTime.DecodeTime(&hour0,&minute0,&sec0,&msec0);
	ctlDate1->DateTime.DecodeDate(&year1,&month1,&day1);
	ctlTime1->DateTime.DecodeTime(&hour1,&minute1,&sec1,&msec1);
	sprintf(strDate0,"%04d-%02d-%02d %02d:%02d:%02d",year0,month0,day0,hour0,minute0,sec0,msec0);
	sprintf(strDate1,"%04d-%02d-%02d %02d:%02d:%02d",year1,month1,day1,hour1,minute1,sec1,msec1);
	sprintf(strTemp," and ap_affirmdate between '%s' and '%s'",strDate0,strDate1);
	szSQL+=strTemp;
	if((nSel=lstDepart->ItemIndex)>0 && nSel<m_lstDepartID.GetSize())
	{
		sprintf(strTemp," and ap_sdcode='%s'",m_lstDepartID[nSel]);
		szSQL+=strTemp;
	}
	szSQL+=" order by pd_code";

	lstView->Items->Clear();

	RunSQL(dm1->Query1,szSQL,true);
	while(!dm1->Query1->Eof)
	{
		pItem=lstView->Items->Add();
		assert(pItem!=NULL);
		strcpy(strCorp,dm1->Query1->FieldByName("ap_reqdepart")->AsString.c_str());
//		strcpy(strCorp,dm1->Query1->FieldByName("ap_sdcode")->AsString.c_str());
		strCorp[2]='\0';
		for(i=0;i<lstCorp.GetSize();i++)
		{
			if(strcmp(lstCorp[i].strCode,strCorp)==0)
			{
				pItem->Caption=lstCorp[i].strName;
				break;
			}
		}
		if(i==lstCorp.GetSize())	pItem->Caption="";

		pItem->SubItems->Add(dm1->Query1->FieldByName("pd_code")->AsString);
		strcpy(strTemp,dm1->Query1->FieldByName("ap_type")->AsString.c_str());
		if(strTemp[0]=='I')	pItem->SubItems->Add("紧急");
		else pItem->SubItems->Add("普通");

		pItem->SubItems->Add(dm1->Query1->FieldByName("mn_name")->AsString);
		pItem->SubItems->Add(Field2TimeString(dm1->Query1->FieldByName("ap_affirmdate")));
		pItem->SubItems->Add(Field2DateString(dm1->Query1->FieldByName("ap_needdate")));

		strcpy(strTemp,dm1->Query1->FieldByName("mn_code")->AsString.c_str());
		strTemp[2]='\0';
		for(i=0;i<lstType.GetSize();i++)
		{
			if(strcmp(lstType[i].strCode,strTemp+1)==0)
			{
				pItem->SubItems->Add(lstType[i].strName);
				break;
			}
		}
		if(i==lstType.GetSize())	pItem->SubItems->Add("");

		strcpy(strTemp,dm1->Query1->FieldByName("ap_shcode")->AsString.c_str());
		if(strTemp[0]=='\0')	pItem->SubItems->Add("");
    else
    {
			for(i=0;i<lstSH.GetSize();i++)
			{
				if(strcmp(lstSH[i].strCode,strTemp)==0)
				{
					pItem->SubItems->Add(lstSH[i].strName);
					break;
				}
			}
			if(i==lstSH.GetSize())	pItem->SubItems->Add("");
		}

		pItem->SubItems->Add(Field2DateString(dm1->Query1->FieldByName("df_plandate")));
		pItem->SubItems->Add(Field2DateString(dm1->Query1->FieldByName("df_decidedate")));

		dm1->Query1->Next();
	}
}
//---------------------------------------------------------------------------

void __fastcall TAskPurchaseAfmListForm::btnToExcelClick(TObject *Sender)
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
				NULL);
		}
	}
	catch(...)
	{
	}
}
//---------------------------------------------------------------------------

void __fastcall TAskPurchaseAfmListForm::btnPrintClick(TObject *Sender)
{
	CString szSQL,szTable;
	TListItem *pItem;
	int i;
	TPrnPurchaseAfmListForm *pPrn;

	szTable=GetTmpTableName();
	szSQL.Format("create table dbo.%s("
		"m_id int,"
		"m_corp varchar(80),"
		"m_apcode varchar(20),"
		"m_type varchar(20),"
		"m_mnname varchar(80),"
		"m_afmdate varchar(20),"
		"m_needdate varchar(20),"
		"m_lttype varchar(20),"
		"m_sh varchar(20),"
		"m_showdate varchar(20),"
		"m_decicedate varchar(20)"
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
			szSQL+=")";
			if(!RunTransactSQL(szSQL))	goto DROP_TABLE;
		}
		CommitTransact();
	}
	catch(...)
	{
		goto DROP_TABLE;
	}

	pPrn=new TPrnPurchaseAfmListForm(this);
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

void __fastcall TAskPurchaseAfmListForm::btnQuery0Click(TObject *Sender)
{
	CString szSQL;
	TListItem *pItem;
	int i,nSel;
	CArray<BASE2COLDATA,BASE2COLDATA>lstSH,lstCorp,lstType,lstPdCodeMin;    //0714 lstPdCodeMin
	BASE2COLDATA rwSH,rwPDMIN;                                              //0714 rwPDMIN
	char strDate0[80],strDate1[80],strTemp[256],strCorp[80];
	unsigned short year0,month0,day0,year1,month1,day1,hour0,minute0,sec0,msec0,hour1,minute1,sec1,msec1;

	szSQL="select * from diclargetype order by lt_code";
	RunSQL(dm1->Query1,szSQL,true);
	while(!dm1->Query1->Eof)
	{
		strcpy(rwSH.strCode,dm1->Query1->FieldByName("lt_code")->AsString.c_str());
		strcpy(rwSH.strName,dm1->Query1->FieldByName("lt_name")->AsString.c_str());
		lstType.Add(rwSH);
		dm1->Query1->Next();
	}

	szSQL="select * from StockHandleman order by sh_code";
	RunSQL(dm1->Query1,szSQL,true);
	while(!dm1->Query1->Eof)
	{
		strcpy(rwSH.strCode,dm1->Query1->FieldByName("sh_code")->AsString.c_str());
		strcpy(rwSH.strName,dm1->Query1->FieldByName("sh_name")->AsString.c_str());
//		lstSH.Add(rwSH);
		dm1->Query1->Next();
	}

	szSQL="select * from DepartCorp order by dc_code";
	RunSQL(dm1->Query1,szSQL,true);
	while(!dm1->Query1->Eof)
	{
		strcpy(rwSH.strCode,dm1->Query1->FieldByName("dc_code")->AsString.c_str());
		strcpy(rwSH.strName,dm1->Query1->FieldByName("dc_name")->AsString.c_str());
		lstCorp.Add(rwSH);
		dm1->Query1->Next();
	}

//----------new 0714------------------------------------------------------------
/*	szSQL="select * from AskPurchase,PurchaseDetail,materialno"
		" where ap_code=substring(pd_code,1,7)"
		" and substring(pd_mncode,2,1)<>'M'"
		" and pd_mncode=mn_code"
		" and ap_shcode is null"
                " and substring(pd_code,8,1)='1'";
	ctlDate0->DateTime.DecodeDate(&year0,&month0,&day0);
	ctlTime0->DateTime.DecodeTime(&hour0,&minute0,&sec0,&msec0);
	ctlDate1->DateTime.DecodeDate(&year1,&month1,&day1);
	ctlTime1->DateTime.DecodeTime(&hour1,&minute1,&sec1,&msec1);
	sprintf(strDate0,"%04d-%02d-%02d %02d:%02d:%02d",year0,month0,day0,hour0,minute0,sec0,msec0);
	sprintf(strDate1,"%04d-%02d-%02d %02d:%02d:%02d",year1,month1,day1,hour1,minute1,sec1,msec1);
	sprintf(strTemp," and ap_affirmdate between '%s' and '%s'",strDate0,strDate1);
	szSQL+=strTemp;
	if((nSel=lstDepart->ItemIndex)>0 && nSel<m_lstDepartID.GetSize())
	{
		sprintf(strTemp," and ap_sdcode='%s'",m_lstDepartID[nSel]);
		szSQL+=strTemp;
	}
	szSQL+=" order by ap_code";
	RunSQL(dm1->Query1,szSQL,true);
	while(!dm1->Query1->Eof)
	{
		strcpy(rwSH.strCode,dm1->Query1->FieldByName("lt_code")->AsString.c_str());
		strcpy(rwSH.strName,dm1->Query1->FieldByName("lt_name")->AsString.c_str());
		lstType.Add(rwSH);
		dm1->Query1->Next();
	}
*/
//------------------------------------------------------------------------------

	szSQL="select * from AskPurchase,PurchaseDetail,materialno"
		" where ap_code=substring(pd_code,1,7)"
		" and substring(pd_mncode,2,1)<>'M'"
		" and pd_mncode=mn_code"
		" and ap_shcode is null"
                " and substring(pd_code,8,1)='1'";
	ctlDate0->DateTime.DecodeDate(&year0,&month0,&day0);
	ctlTime0->DateTime.DecodeTime(&hour0,&minute0,&sec0,&msec0);
	ctlDate1->DateTime.DecodeDate(&year1,&month1,&day1);
	ctlTime1->DateTime.DecodeTime(&hour1,&minute1,&sec1,&msec1);
	sprintf(strDate0,"%04d-%02d-%02d %02d:%02d:%02d",year0,month0,day0,hour0,minute0,sec0,msec0);
	sprintf(strDate1,"%04d-%02d-%02d %02d:%02d:%02d",year1,month1,day1,hour1,minute1,sec1,msec1);
	sprintf(strTemp," and ap_affirmdate between '%s' and '%s'",strDate0,strDate1);
	szSQL+=strTemp;
	if((nSel=lstDepart->ItemIndex)>0 && nSel<m_lstDepartID.GetSize())
	{
		sprintf(strTemp," and ap_sdcode='%s'",m_lstDepartID[nSel]);
		szSQL+=strTemp;
	}
	szSQL+=" order by ap_code";

	lstView->Items->Clear();

	RunSQL(dm1->Query1,szSQL,true);
	while(!dm1->Query1->Eof)
	{
		pItem=lstView->Items->Add();
		assert(pItem!=NULL);
		strcpy(strCorp,dm1->Query1->FieldByName("ap_reqdepart")->AsString.c_str());
//		strcpy(strCorp,dm1->Query1->FieldByName("ap_sdcode")->AsString.c_str());
		strCorp[2]='\0';
		for(i=0;i<lstCorp.GetSize();i++)
		{
			if(strcmp(lstCorp[i].strCode,strCorp)==0)
			{
				pItem->Caption=lstCorp[i].strName;
				break;
			}
		}
		if(i==lstCorp.GetSize())	pItem->Caption="";

		pItem->SubItems->Add(dm1->Query1->FieldByName("ap_code")->AsString);
		strcpy(strTemp,dm1->Query1->FieldByName("ap_type")->AsString.c_str());
		if(strTemp[0]=='I')	pItem->SubItems->Add("紧急");
		else pItem->SubItems->Add("普通");
    		pItem->SubItems->Add(dm1->Query1->FieldByName("mn_name")->AsString);
		pItem->SubItems->Add(Field2TimeString(dm1->Query1->FieldByName("ap_affirmdate")));
		pItem->SubItems->Add(Field2DateString(dm1->Query1->FieldByName("ap_needdate")));

		strcpy(strTemp,dm1->Query1->FieldByName("mn_code")->AsString.c_str());
		strTemp[2]='\0';
		for(i=0;i<lstType.GetSize();i++)
		{
			if(strcmp(lstType[i].strCode,strTemp+1)==0)
			{
//				pItem->SubItems->Add(lstType[i].strName);
                                pItem->SubItems->Add("");
				break;
			}
		}
		if(i==lstType.GetSize())	pItem->SubItems->Add("");

		strcpy(strTemp,dm1->Query1->FieldByName("ap_shcode")->AsString.c_str());
		if(strTemp[0]=='\0')	pItem->SubItems->Add("");
    else
    {
			for(i=0;i<lstSH.GetSize();i++)
			{
				if(strcmp(lstSH[i].strCode,strTemp)==0)
				{
					pItem->SubItems->Add(lstSH[i].strName);
					break;
				}
			}
			if(i==lstSH.GetSize())	pItem->SubItems->Add("");
		}

//		pItem->SubItems->Add(Field2DateString(dm1->Query1->FieldByName("df_plandate")));
//		pItem->SubItems->Add(Field2DateString(dm1->Query1->FieldByName("df_decidedate")));
                pItem->SubItems->Add("");
                pItem->SubItems->Add("");

		dm1->Query1->Next();
	}
//        szSQL.Format(" select * from operator where op_code = '%s'",operatorcode);
//	RunSQL(dm1->Query1,szSQL,true);

//               txtHandleman->Caption=dm1->Query1->FieldByName("op_name")->AsString;
}
//---------------------------------------------------------------------------


