//---------------------------------------------------------------------------

#include <vcl.h>
#include <stdio.h>
#include <assert.h>
#pragma hdrstop

#include "MaterBookList2.h"
#include "DataModule.h"
#include "BaseCode.h"
#include "TConst.h"
#include "LdyInterface.h"


//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TMaterBookListForm2 *MaterBookListForm2;

//采购记录模糊搜索接口，文件：MaterBookList2.*
void MaterBookList2(int nAuth)
{
	CALL_FORM(TMaterBookListForm2);
}
//---------------------------------------------------------------------------
__fastcall TMaterBookListForm2::TMaterBookListForm2(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TMaterBookListForm2::btnQueryClick(TObject *Sender)
{
	CString szSQL,szFilter0,szFilter1,szFilter03,szFilter13;                      //szFilter0用於一般采购，szFilter1用於合约采购
	TListItem *pItem;
	char strCode[80],strTemp[256],strTemp2[256],strTemp3[256];

  szFilter0=szFilter1=szFilter03=szFilter13=" and substring(mn_code,2,1)<>'M'";
/*
  if(!edtMNCode->Text.IsEmpty())
	{
  	sprintf(strTemp," and mn_code like '%s%%'",edtMNCode->Text.c_str());
    szFilter0+=strTemp;
    szFilter1+=strTemp;
	}
*/

  if(!edtDPName->Text.IsEmpty())
  {
  	sprintf(strTemp," and mn_name like '%%%s%%'",edtDPName->Text.c_str());
  	sprintf(strTemp2," and mn_name not like '%%%s%%' and mn_code in( select cc_ocode from codecheck where cc_ncode in(select mn_code from materialno where mn_name like '%%%s%%') and cc_ocode not in ( select mn_code from materialno where mn_name like '%%%s%%' ))",edtDPName->Text.c_str(),edtDPName->Text.c_str(),edtDPName->Text.c_str(),edtDPName->Text.c_str());
        szFilter0+=strTemp;
        szFilter1+=strTemp;
        szFilter03+=strTemp2;
        szFilter13+=strTemp2;
  }
/*  if(!edtFactCard->Text.IsEmpty())
  {
  	sprintf(strTemp," and cf_card like '%%%s%%'",edtFactCard->Text.c_str());
    szFilter0+=strTemp;
    sprintf(strTemp," and ts_mfcard like '%%%s%%'",edtFactCard->Text.c_str());
    szFilter1+=strTemp;
  }
*/
/*
	strcpy(strCode,edtMNCode->Text.c_str());
  if(strCode[0]!='\0')
  {
	  if(strCode[1]=='M')
          {
  		ShowMessage("本程序不能查看原料(编号第二位为“M”)的采购记录");
			if(edtMNCode->CanFocus())	edtMNCode->SetFocus();
			return;
          }

		szSQL.Format("select * from materialno where mn_code='%s'",strCode);
		RunSQL(dm1->Query1,szSQL,true);
		if(dm1->Query1->Eof)
		{
			ShowMessage("没有该材料编号");
			if(edtMNCode->CanFocus())	edtMNCode->SetFocus();
			return;
		}
		txtName->Caption=dm1->Query1->FieldByName("mn_name")->AsString;
  }
*/

	lstView->Items->Clear();

//--------------new 0623 用新编号开请购单时带出旧编号的请购信息-----------------
	szSQL="select bf_bookdate,bf_code,bf_apcode,mf_shortname,bf_mfcard,bf_count,bf_price,mn_name,mn_code"
		" from BookFactory,Manufactur,PurchaseDetail,materialno,CompareFactory"
		" where bf_mfcode=mf_code and bf_apcode=pd_code and pd_mncode=mn_code"       //关键点0623 一般采购
    " and cf_apcode=pd_code and cf_mfcode=mf_code";
  szSQL+=szFilter0;

  szSQL+=" union"
	        " select bf_bookdate,bf_code,bf_apcode,mf_shortname,bf_mfcard,bf_count,bf_price,mn_name,mn_code"
		" from BookFactory,Manufactur,PurchaseDetail,materialno,CompareFactory"
		" where bf_mfcode=mf_code and bf_apcode=pd_code and pd_mncode=mn_code"       //关键点0623 一般采购
    " and cf_apcode=pd_code and cf_mfcode=mf_code";
  szSQL+=szFilter03;

  szSQL+=" union"                                                                            //集合查询 见 P95 海大书
		" select bf_bookdate,bf_code,bf_apcode,mf_shortname,bf_mfcard,bf_count,bf_price,mn_name,mn_code"
		" from BookFactory,Manufactur,TreatStock,materialno,PurchaseDetail"
		" where bf_mfcode=mf_code and bf_apcode=pd_code and pd_tscode=ts_code and ts_mncode=mn_code";   // 关键点0623  如合约采购也曾采购过 则也给抓出来
  szSQL+=szFilter1;


  szSQL+=" union"                                                                            //集合查询 见 P95 海大书
		" select bf_bookdate,bf_code,bf_apcode,mf_shortname,bf_mfcard,bf_count,bf_price,mn_name,mn_code"
		" from BookFactory,Manufactur,TreatStock,materialno,PurchaseDetail"
		" where bf_mfcode=mf_code and bf_apcode=pd_code and pd_tscode=ts_code and ts_mncode=mn_code";   // 关键点0623  如合约采购也曾采购过 则也给抓出来
  szSQL+=szFilter13;


  szSQL+=" order by bf_apcode ";

//------------------------------------------------------------------------------

        RunSQL(dm1->Query1,szSQL,true);
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
//		pItem->SubItems->Add(FloatField2String(dm1->Query1->FieldByName("bf_price"),2));
//--------------new 0705--------------------------------------------------------
                strncpy(strTemp3,dm1->Query1->FieldByName("bf_apcode")->AsString.c_str(),7);
                szSQL.Format(" select * from AskPurchase where ap_code ='%s'",strTemp3);
        	RunSQL(dm1->Query2,szSQL,true);
                strcpy(strTemp2,dm1->Query2->FieldByName("ap_sdcode")->AsString.c_str());
                if(g_theOperator.op_cpcode[0]!='E' && (strcmp(strTemp2,"2")==0 || strcmp(strTemp2,"3")==0))
                {
                        pItem->SubItems->Add("");
                }
                else
                {
		pItem->SubItems->Add(FloatField2String(dm1->Query1->FieldByName("bf_price"),2));
                }
//------------------------------------------------------------------------------
		pItem->SubItems->Add(dm1->Query1->FieldByName("mn_name")->AsString);
		pItem->SubItems->Add(dm1->Query1->FieldByName("mn_code")->AsString);                

		dm1->Query1->Next();
	}
}
//---------------------------------------------------------------------------

void __fastcall TMaterBookListForm2::btnExitClick(TObject *Sender)
{
	Close();        
}
//---------------------------------------------------------------------------

void __fastcall TMaterBookListForm2::btnToPurchaseClick(TObject *Sender)
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

void __fastcall TMaterBookListForm2::lstViewClick(TObject *Sender)
{
	if(lstView->Selected==NULL)	ResetCtrl();        
}
//---------------------------------------------------------------------------

void __fastcall TMaterBookListForm2::lstViewSelectItem(TObject *Sender,
      TListItem *Item, bool Selected)
{
	if(!Selected)	return;

	TListItem *pItem;
	if(!Selected)	return;
                
	if((pItem=lstView->Selected)==NULL)	return;
        edtMNCode->Text=pItem->SubItems->Strings[7];
        txtName->Caption=pItem->SubItems->Strings[6];



  ResetCtrl();

}
//---------------------------------------------------------------------------




void TMaterBookListForm2::ResetCtrl()
{
	btnToBook->Enabled = lstView->Selected!=NULL;
	btnToPurchase->Enabled = lstView->Selected!=NULL;
}

void __fastcall TMaterBookListForm2::btnToBookClick(TObject *Sender)
{
	TListItem *pItem;

  if((pItem=lstView->Selected)==NULL)	return;

	int nRight=GetOperatorRight(operatorcode.c_str(),"IDM_BOOKFACTORY");
	//订购单输入接口，文件：BookFactory.*
	BookFactory(pItem->SubItems->Strings[0].c_str(),nRight);        
}
//---------------------------------------------------------------------------
#include "PrnMaterBookList.h"
void __fastcall TMaterBookListForm2::btnPrintClick(TObject *Sender)
{
	TPrnMaterBookListForm *pPrn;
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
		"m_price  varchar(20)"
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
		szSQL+=")";
		if(!RunSQL(dm1->Query1,szSQL))	goto DROP_TABLE;
	}

  pPrn=new TPrnMaterBookListForm(this);
  assert(pPrn!=NULL);

  pPrn->txtMNCode->Caption=edtMNCode->Text;                       //列印编号正确性关键点
  pPrn->txtName->Caption=txtName->Caption;

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

void __fastcall TMaterBookListForm2::btnToExcelClick(TObject *Sender)
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

