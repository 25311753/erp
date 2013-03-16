//---------------------------------------------------------------------------

#include <vcl.h>
#include <stdio.h>
#include <assert.h>
#pragma hdrstop

#include "DataModule.h"
#include "BaseCode.h"
#include "TreatStockAfm.h"
#include "TConst.h"
#include "LdyInterface.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TTreatStockAfmForm *TreatStockAfmForm;

//==========================================================================
//合约采购确认接口，文件TreatStockAfm.*
//参数：nType=0 确认，nType=1 会计确认
void TreatStockAfm(int nType,int nAuth)
{
	TTreatStockAfmForm *pForm;
	pForm=new TTreatStockAfmForm(Application);
  assert(pForm!=NULL);
	pForm->m_nType=nType;
  pForm->m_nAuthor=nAuth;
  pForm->ShowModal();
  delete pForm;
}
//==========================================================================


//---------------------------------------------------------------------------
__fastcall TTreatStockAfmForm::TTreatStockAfmForm(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TTreatStockAfmForm::btnExitClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------
void __fastcall TTreatStockAfmForm::FormShow(TObject *Sender)
{
	RefreshData();
}

void TTreatStockAfmForm::RefreshData()
{
	TListItem *pItem;
	CString szSQL;
	char strDepart[80],strTemp[80],strCorp[80];

//	szSQL.Format("select * from StockHandleman where sh_code='%s'",operatorcode.c_str());
//	RunSQL(dm1->Query1,szSQL,true);
//	if(dm1->Query1->Eof)	strDepart[0]='\0';
//	else	strcpy(strDepart,dm1->Query1->FieldByName("sh_sdcode")->AsString.c_str());

	lstView->Items->Clear();
	if(operatorcode!="admin")
  {
  	szSQL.Format("select * from operator where op_code='%s'",operatorcode.c_str());
		RunSQL(dm1->Query1,szSQL,true);
    if(dm1->Query1->Eof)	return;
		strcpy(strCorp,dm1->Query1->FieldByName("op_cpcode")->AsString.c_str());
		szSQL.Format("select * from TreatStock,operator,materialno where (ts_afmdate is null or ts_afmdate2 is null)"
			" and op_code=ts_shcode and op_cpcode='%s' and ts_mncode*=mn_code",strCorp);
  }
  else
		szSQL="select * from TreatStock,materialno"
    	" where ts_mncode*=mn_code and (ts_afmdate is null or ts_afmdate2 is null)";

	szSQL+=" order by ts_inputdate,ts_code";
	RunSQL(dm1->Query1,szSQL,true);
	while(!dm1->Query1->Eof)
	{
//		if(strDepart[0]!='\0')
//		{
//    	strcpy(strTemp,dm1->Query1->FieldByName("ap_code")->AsString.c_str());
//			if(dm1->Query1->FieldByName("ap_sdcode")->AsString!=strDepart)
//			{
//				dm1->Query1->Next();
//				continue;
//			}
//		}

		pItem=lstView->Items->Add();
		assert(pItem!=NULL);
		pItem->Caption=dm1->Query1->FieldByName("ts_code")->AsString;
		pItem->SubItems->Add(DateField2Text(dm1->Query1->FieldByName("ts_inputdate")));
		pItem->SubItems->Add(DateField2Text(dm1->Query1->FieldByName("ts_modifydate")));
		pItem->SubItems->Add(DateField2Text(dm1->Query1->FieldByName("ts_afmdate")));
		pItem->SubItems->Add(DateField2Text(dm1->Query1->FieldByName("ts_afmdate2")));
		pItem->SubItems->Add(FloatField2String(dm1->Query1->FieldByName("ts_price"),2));
		pItem->SubItems->Add(dm1->Query1->FieldByName("mn_name")->AsString);

		dm1->Query1->Next();
	}
	edtID->Text="";
	ResetCtrl();
}
//---------------------------------------------------------------------------

void TTreatStockAfmForm::ResetCtrl()
{
	TListItem *pItem;
	bool bAuth = m_nAuthor==AUTH_FULL;

	pItem=lstView->Selected;
	btnDetail->Enabled=pItem!=NULL;
	if(operatorcode=="admin")
	{
		btnAfm		->Enabled=pItem!=NULL && bAuth &&  pItem->SubItems->Strings[2].IsEmpty();
		btnDeafm	->Enabled=pItem!=NULL && bAuth && !pItem->SubItems->Strings[2].IsEmpty();
		btnAfm2		->Enabled=pItem!=NULL && bAuth &&  pItem->SubItems->Strings[3].IsEmpty();
		btnDeafm2	->Enabled=pItem!=NULL && bAuth && !pItem->SubItems->Strings[3].IsEmpty();
	}
	else if(m_nType==0)
	{
		btnAfm		->Enabled=pItem!=NULL && bAuth &&  pItem->SubItems->Strings[2].IsEmpty();
		btnDeafm	->Enabled=pItem!=NULL && bAuth && !pItem->SubItems->Strings[2].IsEmpty();
		btnAfm2		->Enabled=false;
		btnDeafm2	->Enabled=false;
	}
	else if(m_nType==1)
	{
		btnAfm		->Enabled=false;
		btnDeafm	->Enabled=false;
		btnAfm2		->Enabled=pItem!=NULL && bAuth &&  pItem->SubItems->Strings[3].IsEmpty();
		btnDeafm2	->Enabled=pItem!=NULL && bAuth && !pItem->SubItems->Strings[3].IsEmpty();
	}
	else
	{
		btnAfm		->Enabled=false;
		btnDeafm	->Enabled=false;
		btnAfm2		->Enabled=false;
		btnDeafm2	->Enabled=false;
	}
}

void __fastcall TTreatStockAfmForm::FormKeyDown(TObject *Sender,WORD &Key, TShiftState Shift)
{
//
}
//---------------------------------------------------------------------------

void __fastcall TTreatStockAfmForm::lstViewSelectItem(TObject *Sender,TListItem *Item, bool Selected)
{
	TListItem *pItem;

	if(!Selected)	return;
	if((pItem=lstView->Selected)==NULL)	return;
	edtID->Text=pItem->Caption;
  ResetCtrl();
}
//---------------------------------------------------------------------------

void __fastcall TTreatStockAfmForm::lstViewClick(TObject *Sender)
{
	if(lstView->Selected==NULL)	ResetCtrl();
}
//---------------------------------------------------------------------------

void __fastcall TTreatStockAfmForm::btnAfmClick(TObject *Sender)
{
	TListItem *pItem;
	CString szSQL;
	TDateTime tNow;

	if((pItem=lstView->Selected)==NULL)	return;
	szSQL.Format("select * from TreatStock where ts_code='%s'",pItem->Caption.c_str());
  RunSQL(dm1->Query1,szSQL,true);
	if(dm1->Query1->Eof)
	{
		ShowMessage("该编号数据不存在，也许是删除了，请刷新数据");
		return;
	}
	if(!pItem->SubItems->Strings[2].IsEmpty())	return;
	tNow=GetSysTime(false);
	szSQL.Format("update TreatStock set ts_afmdate='%s' where ts_code='%s'",
		Time2DBTimeString(tNow),pItem->Caption.c_str());
	if(!RunSQL(dm1->Query1,szSQL))	return;
	pItem->SubItems->Strings[2]=(LPCSTR)Date2YYMMDD(tNow);
	ResetCtrl();
}
//---------------------------------------------------------------------------

void __fastcall TTreatStockAfmForm::btnDeafmClick(TObject *Sender)
{
	TListItem *pItem;
  TDateTime tNow;
	CString szSQL;

	if((pItem=lstView->Selected)==NULL)	return;
	szSQL.Format("select * from TreatStock where ts_code='%s'",pItem->Caption.c_str());
  RunSQL(dm1->Query1,szSQL,true);
	if(dm1->Query1->Eof)
	{
		ShowMessage("该编号数据不存在，也许是删除了，请刷新数据");
		return;
	}
	if(pItem->SubItems->Strings[2].IsEmpty())	return;
	tNow=GetSysTime(false);
	szSQL.Format("update TreatStock set ts_afmdate=NULL"
  " where ts_code='%s'",pItem->Caption.c_str());
	if(!RunSQL(dm1->Query1,szSQL))	return;
	pItem->SubItems->Strings[2]="";

	ResetCtrl();
}
//---------------------------------------------------------------------------

void __fastcall TTreatStockAfmForm::btnDetailClick(TObject *Sender)
{
	TListItem *pItem;

  if((pItem=lstView->Selected)==NULL)	return;
	int nRight=GetOperatorRight(operatorcode.c_str(),"IDM_TREATSTOCK");
	//合约采购档接口，文件：TreatStock.*
	TreatStock(pItem->Caption.c_str(),nRight);
}
//---------------------------------------------------------------------------

void __fastcall TTreatStockAfmForm::edtIDKeyDown(TObject *Sender,
      WORD &Key, TShiftState Shift)
{
	if(Key==VK_RETURN)
  {
		TListItem *pItem;
		int i;
		CString szSQL;
		char strDepart[80];

		if(edtID->Text.IsEmpty())	return;
		for(i=0;i<lstView->Items->Count;i++)
		{
			pItem=lstView->Items->Item[i];
			if(pItem->Caption==edtID->Text)
			{
				lstView->Selected=pItem;
				ResetCtrl();
				return;
			}
		}
		szSQL.Format("select * from TreatStock where ts_code='%s'",edtID->Text.c_str());
		RunSQL(dm1->Query1,szSQL,true);
		if(dm1->Query1->Eof)	return;
		pItem=lstView->Items->Insert(0);
		assert(pItem!=NULL);
		pItem->Caption=dm1->Query1->FieldByName("ts_code")->AsString;
		pItem->SubItems->Add(DateField2Text(dm1->Query1->FieldByName("ts_inputdate")));
		pItem->SubItems->Add(DateField2Text(dm1->Query1->FieldByName("ts_modifydate")));
		pItem->SubItems->Add(DateField2Text(dm1->Query1->FieldByName("ts_afmdate")));
		pItem->SubItems->Add(DateField2Text(dm1->Query1->FieldByName("ts_afmdate2")));
		lstView->Selected=pItem;
		ResetCtrl();
  }	
}
//---------------------------------------------------------------------------

void __fastcall TTreatStockAfmForm::btnRefreshClick(TObject *Sender)
{
	RefreshData();
}
//---------------------------------------------------------------------------

void __fastcall TTreatStockAfmForm::btnAfm2Click(TObject *Sender)
{
	TListItem *pItem;
	CString szSQL;
	TDateTime tNow;

	if((pItem=lstView->Selected)==NULL)	return;
	szSQL.Format("select * from TreatStock where ts_code='%s'",pItem->Caption.c_str());
  RunSQL(dm1->Query1,szSQL,true);
	if(dm1->Query1->Eof)
	{
		ShowMessage("该编号数据不存在，也许是删除了，请刷新数据");
		return;
	}
	if(!pItem->SubItems->Strings[3].IsEmpty())	return;
	tNow=GetSysTime(false);
	szSQL.Format("update TreatStock set ts_afmdate2='%s' where ts_code='%s'",
		Time2DBTimeString(tNow),pItem->Caption.c_str());
	if(!RunSQL(dm1->Query1,szSQL))	return;
	pItem->SubItems->Strings[3]=(LPCSTR)Date2YYMMDD(tNow);
	ResetCtrl();
}
//---------------------------------------------------------------------------

void __fastcall TTreatStockAfmForm::btnDeafm2Click(TObject *Sender)
{
	TListItem *pItem;
  TDateTime tNow;
	CString szSQL;

	if((pItem=lstView->Selected)==NULL)	return;
	szSQL.Format("select * from TreatStock where ts_code='%s'",pItem->Caption.c_str());
  RunSQL(dm1->Query1,szSQL,true);
	if(dm1->Query1->Eof)
	{
		ShowMessage("该编号数据不存在，也许是删除了，请刷新数据");
		return;
	}
	if(pItem->SubItems->Strings[3].IsEmpty())	return;
	tNow=GetSysTime(false);
	szSQL.Format("update TreatStock set ts_afmdate2=NULL"
  " where ts_code='%s'",pItem->Caption.c_str());
	if(!RunSQL(dm1->Query1,szSQL))	return;
	pItem->SubItems->Strings[3]="";

	ResetCtrl();
}
//---------------------------------------------------------------------------

