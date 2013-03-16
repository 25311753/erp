//---------------------------------------------------------------------------

#include <vcl.h>
#include <stdio.h>
#include <assert.h>
#pragma hdrstop

#include "DataModule.h"
#include "BaseCode.h"
#include "AskPurchaseEnd.h"
#include "TConst.h"
#include "LdyInterface.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TAskPurchaseEndForm *AskPurchaseEndForm;

//==========================================================================
//请购单结案接口，文件AskPurchaseEnd.*
void AskPurchaseEnd(int nAuth)
{
	AskPurchaseEnd(NULL,nAuth);
}


void AskPurchaseEnd(LPCSTR lpszID,int nAuth)
{
	TAskPurchaseEndForm *pForm;
	pForm=new TAskPurchaseEndForm(Application);
  assert(pForm!=NULL);
  pForm->m_nAuthor=nAuth;
	if(lpszID!=NULL)	pForm->m_szIDFirst=lpszID;
  pForm->ShowModal();
  delete pForm;
}
//==========================================================================


//---------------------------------------------------------------------------
__fastcall TAskPurchaseEndForm::TAskPurchaseEndForm(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TAskPurchaseEndForm::btnExitClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------
void __fastcall TAskPurchaseEndForm::FormShow(TObject *Sender)
{
//	RefreshData();
	if(!m_szIDFirst.IsEmpty())
	{
		edtID->Text=m_szIDFirst;
		OnQuery();
	}

}

void TAskPurchaseEndForm::RefreshData()
{

	TListItem *pItem;
	CString szSQL,szSQL1;
	char strDepart[80],strTemp[256],strSH[80],strRcptMan[80],strCpCode[80];


        if(edtH3ApC->Text.IsEmpty())
        {
                ShowMessage("请输入请购单前叁位");
		if(edtH3ApC->CanFocus())	edtH3ApC->SetFocus();
                return;
        }
        if(edtH3ApC->Text.c_str()[0]==' ' || edtH3ApC->Text.c_str()[1]==' ' || edtH3ApC->Text.c_str()[2]==' ')
        {
                ShowMessage("检查是否输入了空格,请输入正确的请购单前叁位");
		if(edtH3ApC->CanFocus())	edtH3ApC->SetFocus();
                return;
        }

        szSQL.Format("select * from operator where op_code='%s'", operatorcode.c_str());
        RunSQL(dm1->Query1, szSQL, true);
	if(!dm1->Query1->Eof)
	{
//                strcpy(strRcptMan,dm1->Query1->FieldByName("op_name")->AsString.c_str());
                szSQL1.Format("select * from RcptHandleman where rh_code='%s' or rh_name='%s'",operatorcode.c_str(),dm1->Query1->FieldByName("op_name")->AsString.c_str());
                RunSQL(dm1->Query2,szSQL1,true);
                if (dm1->Query2->Eof)
                {
                        ShowMessage("抱歉!只有受权的收料经办才可进行结案操作");
                        return;
                }
		strcpy(strCpCode,dm1->Query1->FieldByName("op_cpcode")->AsString.c_str());

        }


	lstView->Items->Clear();
	szSQL="select * from PurchaseDetail,AskPurchase where ap_code=substring(pd_code,1,len(pd_code)-1)"
		" and pd_endflag is null";
        sprintf(strTemp," and substring(pd_code,1,3)='%s'",edtH3ApC->Text.c_str());
        szSQL+=strTemp;

        sprintf(strTemp," and substring(ap_reqdepart,1,1) ='%s'",strCpCode);           //只能查自己公司的请购案件
        szSQL+=strTemp;

        sprintf(strTemp," order by pd_code");
        szSQL+=strTemp;

        RunSQL(dm1->Query1,szSQL,true);
	while(!dm1->Query1->Eof)
	{
		pItem=lstView->Items->Add();
		assert(pItem!=NULL);
		pItem->Caption=dm1->Query1->FieldByName("pd_code")->AsString;
		if(dm1->Query1->FieldByName("pd_endflag")->IsNull)
			pItem->SubItems->Add("");
		else
			pItem->SubItems->Add("V");

		dm1->Query1->Next();
	}
	edtID->Text="";
	ResetCtrl();

/*	szSQL.Format("select * from StockHandleman where sh_code='%s'",operatorcode.c_str());
	RunSQL(dm1->Query1,szSQL,true);
	if(dm1->Query1->Eof)	strDepart[0]='\0';                              //非经办
	else	strcpy(strDepart,dm1->Query1->FieldByName("sh_sdcode")->AsString.c_str());

	lstView->Items->Clear();
	szSQL="select * from PurchaseDetail,AskPurchase where ap_code=substring(pd_code,1,len(pd_code)-1)"
		" and pd_endflag is null";
        sprintf(strTemp," and substring(pd_code,1,3)='%s'",edtH3ApC->Text.c_str());
        szSQL+=strTemp;
        sprintf(strTemp," order by pd_code");
        szSQL+=strTemp;

        RunSQL(dm1->Query1,szSQL,true);
	while(!dm1->Query1->Eof)
	{
		if(strDepart[0]!='\0')
		{//是经办
			if(dm1->Query1->FieldByName("ap_sdcode")->AsString!=strDepart)
			{//只显示本部的案子
				dm1->Query1->Next();
				continue;
			}
		}
		pItem=lstView->Items->Add();
		assert(pItem!=NULL);
		pItem->Caption=dm1->Query1->FieldByName("pd_code")->AsString;
		if(dm1->Query1->FieldByName("pd_endflag")->IsNull)
			pItem->SubItems->Add("");
		else
			pItem->SubItems->Add("V");

		dm1->Query1->Next();
	}       
	edtID->Text="";
	ResetCtrl();
*/
/*	szSQL.Format("select * from StockHandleman where sh_code='%s'",operatorcode.c_str());
	RunSQL(dm1->Query1,szSQL,true);
	if(dm1->Query1->Eof)	strDepart[0]='\0';
	else	strcpy(strDepart,dm1->Query1->FieldByName("sh_sdcode")->AsString.c_str());

	lstView->Items->Clear();
	szSQL="select * from PurchaseDetail,AskPurchase where ap_code=substring(pd_code,1,len(pd_code)-1)"
		" and pd_endflag is null order by pd_code";
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
		pItem->Caption=dm1->Query1->FieldByName("pd_code")->AsString;
		if(dm1->Query1->FieldByName("pd_endflag")->IsNull)
			pItem->SubItems->Add("");
		else
			pItem->SubItems->Add("V");

		dm1->Query1->Next();
	}
	edtID->Text="";
	ResetCtrl();
*/        
}
//---------------------------------------------------------------------------

void TAskPurchaseEndForm::ResetCtrl()
{
	TListItem *pItem;
	bool bAuth = m_nAuthor==AUTH_FULL;

	pItem=lstView->Selected;
	btnDetail->Enabled=pItem!=NULL;
	btnAfm->Enabled=pItem!=NULL && bAuth && pItem->SubItems->Strings[0].IsEmpty();
	btnDeafm->Enabled=pItem!=NULL && bAuth && !pItem->SubItems->Strings[0].IsEmpty();
}

void __fastcall TAskPurchaseEndForm::FormKeyDown(TObject *Sender,WORD &Key, TShiftState Shift)
{
//
}
//---------------------------------------------------------------------------

void __fastcall TAskPurchaseEndForm::lstViewSelectItem(TObject *Sender,TListItem *Item, bool Selected)
{
	TListItem *pItem;

	if(!Selected)	return;
	if((pItem=lstView->Selected)==NULL)	return;
	edtID->Text=pItem->Caption;
  ResetCtrl();
}
//---------------------------------------------------------------------------

void __fastcall TAskPurchaseEndForm::lstViewClick(TObject *Sender)
{
	if(lstView->Selected==NULL)	ResetCtrl();
}
//---------------------------------------------------------------------------

void __fastcall TAskPurchaseEndForm::btnAfmClick(TObject *Sender)
{
	TListItem *pItem;
	CString szSQL;

	if((pItem=lstView->Selected)==NULL)	return;
	if(!pItem->SubItems->Strings[0].IsEmpty())	return;
	szSQL.Format("update PurchaseDetail set pd_endflag='E' where pd_code='%s'",
		pItem->Caption.c_str());
	if(!RunSQL(dm1->Query1,szSQL))	return;
	pItem->SubItems->Strings[0]="V";
	ResetCtrl();
}
//---------------------------------------------------------------------------

void __fastcall TAskPurchaseEndForm::btnDeafmClick(TObject *Sender)
{
	TListItem *pItem;
  TDateTime tNow;
	CString szSQL;

	if((pItem=lstView->Selected)==NULL)	return;
	if(pItem->SubItems->Strings[0].IsEmpty())	return;
	szSQL.Format("update PurchaseDetail set pd_endflag=NULL where pd_code='%s'",pItem->Caption.c_str());
	if(!RunSQL(dm1->Query1,szSQL))	return;
	pItem->SubItems->Strings[0]="";

	ResetCtrl();
}
//---------------------------------------------------------------------------

void __fastcall TAskPurchaseEndForm::btnDetailClick(TObject *Sender)
{
	TListItem *pItem;
	char strID[80];

  if((pItem=lstView->Selected)==NULL)	return;
	int nRight=GetOperatorRight(operatorcode.c_str(),"IDM_ASKPURCHASE");
	//请购单输入接口，文件：AskPurchase.*
	strcpy(strID,pItem->Caption.c_str());
	if(strID[0]!='\0')
	{
		strID[strlen(strID)-1]='\0';
		AskPurchase(strID,nRight);
	}
}
//---------------------------------------------------------------------------

void __fastcall TAskPurchaseEndForm::edtIDKeyDown(TObject *Sender,
      WORD &Key, TShiftState Shift)
{
	if(Key==VK_RETURN)
        {
		OnQuery();
	}
}

void TAskPurchaseEndForm::OnQuery()
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

	szSQL.Format("select * from PurchaseDetail,AskPurchase where ap_code=substring(pd_code,1,len(pd_code)-1)"
		" and pd_code='%s'",edtID->Text.c_str());
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
	pItem->Caption=dm1->Query1->FieldByName("pd_code")->AsString;
	if(dm1->Query1->FieldByName("pd_endflag")->IsNull)
		pItem->SubItems->Add("");
	else
		pItem->SubItems->Add("V");

	lstView->Selected=pItem;
	ResetCtrl();
}	
//---------------------------------------------------------------------------

void __fastcall TAskPurchaseEndForm::btnRefreshClick(TObject *Sender)
{
	RefreshData();
}
//---------------------------------------------------------------------------

void __fastcall TAskPurchaseEndForm::edtH3ApCKeyDown(TObject *Sender,
      WORD &Key, TShiftState Shift)
{
	if(Key==VK_RETURN)
        {
        	RefreshData();
	}        
}
//---------------------------------------------------------------------------



