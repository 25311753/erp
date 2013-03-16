//---------------------------------------------------------------------------

#include <vcl.h>
#include <stdio.h>
#include <assert.h>
#pragma hdrstop

#include "DataModule.h"
#include "BaseCode.h"
#include "AskPurchaseAfm.h"
#include "TConst.h"
#include "LdyInterface.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TAskPurchaseAfmForm *AskPurchaseAfmForm;

//==========================================================================
//请购单确认接口，文件AskPurchaseAfm.*
void AskPurchaseAfm(int nAuth)
{
	TAskPurchaseAfmForm *pForm;
	pForm=new TAskPurchaseAfmForm(Application);
  assert(pForm!=NULL);
  pForm->m_nAuthor=nAuth;
  pForm->ShowModal();
  delete pForm;
}
//==========================================================================


//---------------------------------------------------------------------------
__fastcall TAskPurchaseAfmForm::TAskPurchaseAfmForm(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TAskPurchaseAfmForm::btnExitClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------
void __fastcall TAskPurchaseAfmForm::FormShow(TObject *Sender)
{
	RefreshData();
}

void TAskPurchaseAfmForm::RefreshData()
{
	TListItem *pItem;
	CString szSQL;
	char strDepart[80],strTemp[80];

	szSQL.Format("select * from StockHandleman where sh_code='%s'",operatorcode.c_str());
	RunSQL(dm1->Query1,szSQL,true);
	if(dm1->Query1->Eof)	strDepart[0]='\0';
	else	strcpy(strDepart,dm1->Query1->FieldByName("sh_sdcode")->AsString.c_str());

	lstView->Items->Clear();
	szSQL="select * from AskPurchase,HandleMan where"
  	" ap_hmcode*=hm_code and ap_affirmdate is null order by ap_inputdate,ap_code";
	RunSQL(dm1->Query1,szSQL,true);
	while(!dm1->Query1->Eof)
	{
		if(strDepart[0]!='\0')
		{
    	strcpy(strTemp,dm1->Query1->FieldByName("ap_code")->AsString.c_str());
			if(dm1->Query1->FieldByName("ap_sdcode")->AsString!=strDepart)
			{
				dm1->Query1->Next();
				continue;
			}
		}

		pItem=lstView->Items->Add();
		assert(pItem!=NULL);
		pItem->Caption=dm1->Query1->FieldByName("ap_code")->AsString;
		pItem->SubItems->Add(DateField2Text(dm1->Query1->FieldByName("ap_inputdate")));
		pItem->SubItems->Add(DateField2Text(dm1->Query1->FieldByName("ap_affirmdate")));
		pItem->SubItems->Add(DateField2Text(dm1->Query1->FieldByName("ap_printdate")));
		pItem->SubItems->Add(DateField2Text(dm1->Query1->FieldByName("ap_modifydate")));
		pItem->SubItems->Add(dm1->Query1->FieldByName("hm_name")->AsString);

		dm1->Query1->Next();
	}
	edtID->Text="";
	ResetCtrl();
}
//---------------------------------------------------------------------------

void TAskPurchaseAfmForm::ResetCtrl()
{
	TListItem *pItem;
	bool bAuth = m_nAuthor==AUTH_FULL;

	pItem=lstView->Selected;
	btnDetail->Enabled=pItem!=NULL;
	btnAfm->Enabled=pItem!=NULL && bAuth && pItem->SubItems->Strings[1].IsEmpty();
	btnDeafm->Enabled=pItem!=NULL && bAuth && !pItem->SubItems->Strings[1].IsEmpty();
}

void __fastcall TAskPurchaseAfmForm::FormKeyDown(TObject *Sender,WORD &Key, TShiftState Shift)
{
//
}
//---------------------------------------------------------------------------

void __fastcall TAskPurchaseAfmForm::lstViewSelectItem(TObject *Sender,TListItem *Item, bool Selected)
{
	TListItem *pItem;

	if(!Selected)	return;
	if((pItem=lstView->Selected)==NULL)	return;
	edtID->Text=pItem->Caption;
  ResetCtrl();
}
//---------------------------------------------------------------------------

void __fastcall TAskPurchaseAfmForm::lstViewClick(TObject *Sender)
{
	if(lstView->Selected==NULL)	ResetCtrl();
}
//---------------------------------------------------------------------------

void __fastcall TAskPurchaseAfmForm::btnAfmClick(TObject *Sender)
{
	TListItem *pItem;
	CString szSQL;
	TDateTime tNow;

	if((pItem=lstView->Selected)==NULL)	return;
	if(!pItem->SubItems->Strings[1].IsEmpty())	return;
	tNow=GetSysTime(false);
	szSQL.Format("update AskPurchase set ap_affirmdate='%s' where ap_code='%s'",
		Time2DBTimeString(tNow),pItem->Caption.c_str());
	if(!RunSQL(dm1->Query1,szSQL))	return;
	pItem->SubItems->Strings[1]=(LPCSTR)Date2YYMMDD(tNow);
	ResetCtrl();
}
//---------------------------------------------------------------------------

void __fastcall TAskPurchaseAfmForm::btnDeafmClick(TObject *Sender)
{
	TListItem *pItem;
  TDateTime tNow;
	CString szSQL;

	if((pItem=lstView->Selected)==NULL)	return;
	if(pItem->SubItems->Strings[1].IsEmpty())	return;
	tNow=GetSysTime(false);
	szSQL.Format("update AskPurchase set ap_affirmdate=NULL,ap_modifydate='%s'"
  " where ap_code='%s'",Time2DBDateString(tNow),pItem->Caption.c_str());
	if(!RunSQL(dm1->Query1,szSQL))	return;
	pItem->SubItems->Strings[1]="";
  pItem->SubItems->Strings[3]=(LPCSTR)Date2YYMMDD(tNow);

	ResetCtrl();
}
//---------------------------------------------------------------------------

void __fastcall TAskPurchaseAfmForm::btnDetailClick(TObject *Sender)
{
	TListItem *pItem;

  if((pItem=lstView->Selected)==NULL)	return;
	int nRight=GetOperatorRight(operatorcode.c_str(),"IDM_ASKPURCHASE");
	//请购单输入接口，文件：AskPurchase.*
	AskPurchase(pItem->Caption.c_str(),nRight);
}
//---------------------------------------------------------------------------

void __fastcall TAskPurchaseAfmForm::edtIDKeyDown(TObject *Sender,
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
		szSQL.Format("select * from StockHandleman where sh_code='%s'",operatorcode.c_str());
		RunSQL(dm1->Query1,szSQL,true);
		if(dm1->Query1->Eof)	strDepart[0]='\0';
		else	strcpy(strDepart,dm1->Query1->FieldByName("sh_sdcode")->AsString.c_str());

		szSQL.Format("select * from AskPurchase,HandleMan where ap_hmcode*=hm_code and ap_code='%s'",edtID->Text.c_str());
		RunSQL(dm1->Query1,szSQL,true);
		if(dm1->Query1->Eof)	return;
		if(strDepart[0]!='\0')
		{
			if(dm1->Query1->FieldByName("ap_sdcode")->AsString!=strDepart)
			{
				ShowMessage("该请购单指定的采购部门与你所属的采购部门不同");
				return;
			}
		}
		pItem=lstView->Items->Insert(0);
		assert(pItem!=NULL);
		pItem->Caption=dm1->Query1->FieldByName("ap_code")->AsString;
		pItem->SubItems->Add(DateField2Text(dm1->Query1->FieldByName("ap_inputdate")));
		pItem->SubItems->Add(DateField2Text(dm1->Query1->FieldByName("ap_affirmdate")));
		pItem->SubItems->Add(DateField2Text(dm1->Query1->FieldByName("ap_printdate")));
		pItem->SubItems->Add(DateField2Text(dm1->Query1->FieldByName("ap_modifydate")));
		pItem->SubItems->Add(dm1->Query1->FieldByName("hm_name")->AsString);
		lstView->Selected=pItem;
		ResetCtrl();
  }
}
//---------------------------------------------------------------------------

void __fastcall TAskPurchaseAfmForm::btnRefreshClick(TObject *Sender)
{
	RefreshData();
}
//---------------------------------------------------------------------------

#include "PrnBaseData.h"
void __fastcall TAskPurchaseAfmForm::btnPrintClick(TObject *Sender)
{
  TPrnBaseDataForm *pForm;
 	pForm=new TPrnBaseDataForm(this);
  assert(pForm!=NULL);

  pForm->txtTitle->Caption="未接案请购单列表";
  pForm->txtText0->Caption="请购单号";
  pForm->txtText1->Caption="数据日期";
  pForm->txtText2->Caption="列印日期";
  pForm->txtText3->Caption="请购人员";

  CString szSQL;
	szSQL="select ap_code as prnID,ap_inputdate as prnName,ap_printdate as prnText2,"
  	"hm_name as prnText3 from AskPurchase,HandleMan where"
  	" ap_hmcode*=hm_code and ap_affirmdate is null"
    " order by hm_code,ap_inputdate,ap_code";
  if(!OpenQuery(dm1->sqlPrint,szSQL))
  	return;
  pForm->PrnView->PreviewModal() ;
  delete pForm;
}
//---------------------------------------------------------------------------


