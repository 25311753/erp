//---------------------------------------------------------------------------

#include <vcl.h>
#include <stdio.h>
#include <assert.h>
#pragma hdrstop

#include "DataModule.h"
#include "BaseCode.h"
#include "AskPurchaseSetSH.h"
#include "TConst.h"
#include "LdyInterface.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TAskPurchaseSetSHForm *AskPurchaseSetSHForm;

//==========================================================================
//请购单指派采购经办接口，文件AskPurchaseSetSH.*
void AskPurchaseSetSH(int nAuth)
{
	TAskPurchaseSetSHForm *pForm;
	pForm=new TAskPurchaseSetSHForm(Application);
  assert(pForm!=NULL);
  pForm->m_nAuthor=nAuth;
  pForm->ShowModal();
  delete pForm;
}
//==========================================================================


//---------------------------------------------------------------------------
__fastcall TAskPurchaseSetSHForm::TAskPurchaseSetSHForm(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TAskPurchaseSetSHForm::btnExitClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------
void __fastcall TAskPurchaseSetSHForm::FormShow(TObject *Sender)
{
	CString szSQL;
//	bool bMatch;
	char strDepart[80],strTemp[80];

	szSQL.Format("select * from StockHandleman where sh_code='%s'",operatorcode.c_str());
	RunSQL(dm1->Query1,szSQL,true);
	if(dm1->Query1->Eof)	strDepart[0]='\0';
	else	strcpy(strDepart,dm1->Query1->FieldByName("sh_sdcode")->AsString.c_str());

	szSQL="select * from StockHandleman order by sh_code";
	RunSQL(dm1->Query1,szSQL,true);
	while(!dm1->Query1->Eof)
	{
		if(strDepart[0]!='\0')
		{
			if(dm1->Query1->FieldByName("sh_sdcode")->AsString!=strDepart)
			{
				dm1->Query1->Next();
				continue;
			}
		}
		m_lstID.Add(dm1->Query1->FieldByName("sh_code")->AsString.c_str());
		lstStockHandle->Items->Add(dm1->Query1->FieldByName("sh_name")->AsString);
		dm1->Query1->Next();
	}
	RefreshData();
}

void TAskPurchaseSetSHForm::RefreshData()
{
	TListItem *pItem;
	CString szSQL;
	char strSH[80],strDepart[80];
	int i;

	szSQL.Format("select * from StockHandleman where sh_code='%s'",operatorcode.c_str());
	RunSQL(dm1->Query1,szSQL,true);
	if(dm1->Query1->Eof)	strDepart[0]='\0';
	else	strcpy(strDepart,dm1->Query1->FieldByName("sh_sdcode")->AsString.c_str());
	
	lstView->Items->Clear();
	szSQL="select * from AskPurchase where ap_shcode is null"
   " and ap_affirmdate is not null"
   " order by ap_inputdate,ap_code";
	RunSQL(dm1->Query1,szSQL,true);
	while(!dm1->Query1->Eof)
	{
		if(strDepart[0]!='\0')
		{
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
		strcpy(strSH,dm1->Query1->FieldByName("ap_shcode")->AsString.c_str());
		for(i=0;i<m_lstID.GetSize();i++)
		{
			if(m_lstID[i]==strSH)
			{
				pItem->SubItems->Add(lstStockHandle->Items->Strings[i]);
				break;
			}
		}
		if(i==m_lstID.GetSize())
			pItem->SubItems->Add("");

		dm1->Query1->Next();
	}
	edtID->Text="";
	ResetCtrl();
}
//---------------------------------------------------------------------------

void TAskPurchaseSetSHForm::ResetCtrl()
{
	TListItem *pItem;
	bool bAuth = m_nAuthor==AUTH_FULL;

	pItem=lstView->Selected;
	btnDetail->Enabled=pItem!=NULL;
	btnAfm->Enabled=pItem!=NULL && bAuth;
	btnDeafm->Enabled=pItem!=NULL && bAuth && !pItem->SubItems->Strings[4].IsEmpty();
}

void __fastcall TAskPurchaseSetSHForm::FormKeyDown(TObject *Sender,WORD &Key, TShiftState Shift)
{
//
}
//---------------------------------------------------------------------------

void __fastcall TAskPurchaseSetSHForm::lstViewSelectItem(TObject *Sender,TListItem *Item, bool Selected)
{
	TListItem *pItem;

	if(!Selected)	return;
	if((pItem=lstView->Selected)==NULL)	return;
	edtID->Text=pItem->Caption;
	if(pItem->SubItems->Strings[4].IsEmpty())
		lstStockHandle->ItemIndex=-1;
	else
		lstStockHandle->ItemIndex=lstStockHandle->Items->IndexOf(pItem->SubItems->Strings[4]);

  ResetCtrl();
}
//---------------------------------------------------------------------------

void __fastcall TAskPurchaseSetSHForm::lstViewClick(TObject *Sender)
{
	if(lstView->Selected==NULL)	ResetCtrl();
}
//---------------------------------------------------------------------------

void __fastcall TAskPurchaseSetSHForm::btnAfmClick(TObject *Sender)
{
	TListItem *pItem;
	CString szSQL;
	TDateTime tNow;
	int nSel;

	if((pItem=lstView->Selected)==NULL)	return;
	if((nSel=lstStockHandle->ItemIndex)<0 || nSel>=m_lstID.GetSize())
	{
		ShowMessage("请选择一个有效的采购经办");
		return;
	}
	szSQL.Format("update AskPurchase set ap_shcode='%s' where ap_code='%s'",
		m_lstID[nSel],pItem->Caption.c_str());
	if(!RunSQL(dm1->Query1,szSQL))	return;
	pItem->SubItems->Strings[4]=lstStockHandle->Text;
	ResetCtrl();
}
//---------------------------------------------------------------------------

void __fastcall TAskPurchaseSetSHForm::btnDeafmClick(TObject *Sender)
{
	TListItem *pItem;
  TDateTime tNow;
	CString szSQL;

	if((pItem=lstView->Selected)==NULL)	return;
	if(pItem->SubItems->Strings[4].IsEmpty())	return;
	szSQL.Format("update AskPurchase set ap_shcode=NULL"
  " where ap_code='%s'",pItem->Caption.c_str());
	if(!RunSQL(dm1->Query1,szSQL))	return;
	pItem->SubItems->Strings[4]="";

	ResetCtrl();
}
//---------------------------------------------------------------------------

void __fastcall TAskPurchaseSetSHForm::btnDetailClick(TObject *Sender)
{
	TListItem *pItem;

  if((pItem=lstView->Selected)==NULL)	return;
	int nRight=GetOperatorRight(operatorcode.c_str(),"IDM_ASKPURCHASE");
	//请购单输入接口，文件：AskPurchase.*
	AskPurchase(pItem->Caption.c_str(),nRight);
}
//---------------------------------------------------------------------------

void __fastcall TAskPurchaseSetSHForm::edtIDKeyDown(TObject *Sender,
      WORD &Key, TShiftState Shift)
{
	if(Key==VK_RETURN)
  {
		TListItem *pItem;
		int i;
		CString szSQL;
		char strSH[80],strDepart[80];

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

		szSQL.Format("select * from AskPurchase where ap_code='%s'",edtID->Text.c_str());
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
    if(dm1->Query1->FieldByName("ap_affirmdate")->IsNull)
    {
    	ShowMessage("该请购单还没有接案");
      return;
    }
		pItem=lstView->Items->Insert(0);
		assert(pItem!=NULL);
		pItem->Caption=dm1->Query1->FieldByName("ap_code")->AsString;
		pItem->SubItems->Add(DateField2Text(dm1->Query1->FieldByName("ap_inputdate")));
		pItem->SubItems->Add(DateField2Text(dm1->Query1->FieldByName("ap_affirmdate")));
		pItem->SubItems->Add(DateField2Text(dm1->Query1->FieldByName("ap_printdate")));
		pItem->SubItems->Add(DateField2Text(dm1->Query1->FieldByName("ap_modifydate")));
		strcpy(strSH,dm1->Query1->FieldByName("ap_shcode")->AsString.c_str());
		for(i=0;i<m_lstID.GetSize();i++)
		{
			if(m_lstID[i]==strSH)
			{
				pItem->SubItems->Add(lstStockHandle->Items->Strings[i]);
				break;
			}
		}
		if(i==m_lstID.GetSize())	pItem->SubItems->Add("");

		lstView->Selected=pItem;
		ResetCtrl();
  }	
}
//---------------------------------------------------------------------------

void __fastcall TAskPurchaseSetSHForm::btnRefreshClick(TObject *Sender)
{
	RefreshData();
}
//---------------------------------------------------------------------------

