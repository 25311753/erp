//---------------------------------------------------------------------------

#include <vcl.h>
#include <stdio.h>
#include <math.h>
#include <assert.h>
#pragma hdrstop

#include "DataModule.h"
#include "BaseCode.h"
#include "PurchaseRoad.h"
#include "TConst.h"
#include "PrnCompareFactory.h"
#include "LdyInterface.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TPurchaseRoadForm *PurchaseRoadForm;

//=================================================================
//请购过程接口，文件：PurchaseRoad.*
void PurchaseRoad(int nAuth)
{
	TPurchaseRoadForm *pForm;
  pForm=new TPurchaseRoadForm(Application);
  assert(pForm!=NULL);
	pForm->m_nAuthor=nAuth;
  pForm->ShowModal();
  delete pForm;
}

//---------------------------------------------------------------------------
__fastcall TPurchaseRoadForm::TPurchaseRoadForm(TComponent* Owner)
	: TForm(Owner)
{
	m_bSpeerInitialed=false;
	m_bQuoteInitialed=false;
	m_bHiggleInitialed=false;
	m_bShowInitialed=false;
	m_bDecideInitialed=false;
}
//---------------------------------------------------------------------------
void __fastcall TPurchaseRoadForm::btnExitClick(TObject *Sender)
{
	if(m_enState==EN_STATE_IDLE)
		Close();	
	else
	{
		m_enState=EN_STATE_IDLE;
		ResetCtrl();
	}
}

void TPurchaseRoadForm::EmptySpeer()
{
	edtSpeerEndDate->Text="";
	edtSpeerPrnDate->Text="";
	lstSpeerFact->ItemIndex=-1;
	lstSpeerFact->Text="";
}

//---------------------------------------------------------------------------
void __fastcall TPurchaseRoadForm::ctlSpeerShow(TObject *Sender)
{
	CString szSQL;

	if(!m_bSpeerInitialed)
	{
		szSQL="select * from Manufactur order by mf_code";
		RunSQL(dm1->Query1,szSQL,true);
		while(!dm1->Query1->Eof)
		{
			m_lstSpeerFactID.Add(dm1->Query1->FieldByName("mf_code")->AsString.c_str());
			lstSpeerFact->Items->Add(dm1->Query1->FieldByName("mf_shortname")->AsString);

			dm1->Query1->Next();
		}

		EmptySpeer();
	}
	m_bSpeerInitialed=true;

	m_enRegion=EN_REG_SPEER;
	if(m_szActiveID!=m_szSpeerID)	OnQuerySpeer(m_szActiveID);
	m_enState=EN_STATE_IDLE;
	ResetCtrl();
}
//---------------------------------------------------------------------------

void TPurchaseRoadForm::OnQuerySpeer(LPCSTR lpszID)
{
	CString szSQL;

	lstSpeerView->Items->Clear();
	m_lstSpeerViewID.RemoveAll();
	if(lpszID[0]=='\0')	return;

	szSQL.Format("select * from QuoteFactory,Manufactur where qf_apcode='%s'"
		" and qf_mfcode=mf_code order by qf_mfcode",lpszID);
	RunSQL(dm1->Query1,szSQL,true);
	while(!dm1->Query1->Eof)
	{
		m_lstSpeerViewID.Add(dm1->Query1->FieldByName("mf_code")->AsString.c_str());
		lstSpeerView->Items->Add(dm1->Query1->FieldByName("mf_shortname")->AsString);

		dm1->Query1->Next();
	}
	m_szActiveID=lpszID;
  m_szSpeerID=lpszID;
}

void TPurchaseRoadForm::OnQueryQuote(LPCSTR lpszID)
{
	CString szSQL;
	TListItem *pItem;
	char strID[80];

	lstQuoteView->Items->Clear();
	m_lstQuoteViewID.RemoveAll();
	if(lpszID[0]=='\0')	return;

	szSQL.Format("select * from CompareFactory,Manufactur"
		" where cf_mfcode=mf_code"
		" and cf_apcode like '%s_' order by cf_apcode,cf_mfcode",lpszID);
	RunSQL(dm1->Query1,szSQL,true);
	while(!dm1->Query1->Eof)
	{
		strcpy(strID,dm1->Query1->FieldByName("cf_apcode")->AsString.c_str());
		if(strID[0]=='\0')	return;

		pItem=lstQuoteView->Items->Add();
		assert(pItem!=NULL);
		pItem->Caption =  strID+strlen(strID)-1;

		m_lstQuoteViewID.Add(dm1->Query1->FieldByName("mf_code")->AsString.c_str());
		pItem->SubItems->Add(dm1->Query1->FieldByName("mf_shortname")->AsString);

		dm1->Query1->Next();
	}
	m_szActiveID=lpszID;
  m_szQuoteID=lpszID;

	InitQuoteFactory();
}

void TPurchaseRoadForm::OnQueryHiggle(LPCSTR lpszID)
{
	CString szSQL;
	TListItem *pItem;
	char strID[80];

	lstHiggleView->Items->Clear();
	m_lstHiggleViewID.RemoveAll();
	if(lpszID[0]=='\0')	return;

	szSQL.Format("select * from CompareFactory,Manufactur"
		" where cf_mfcode=mf_code"
		" and cf_apcode like '%s_' order by cf_apcode,cf_mfcode",lpszID);
	RunSQL(dm1->Query1,szSQL,true);
	while(!dm1->Query1->Eof)
	{
		strcpy(strID,dm1->Query1->FieldByName("cf_apcode")->AsString.c_str());
		if(strID[0]=='\0')	return;

		pItem=lstHiggleView->Items->Add();
		assert(pItem!=NULL);
		pItem->Caption =  strID+strlen(strID)-1;

		m_lstHiggleViewID.Add(dm1->Query1->FieldByName("mf_code")->AsString.c_str());
		pItem->SubItems->Add(dm1->Query1->FieldByName("mf_shortname")->AsString);

		dm1->Query1->Next();
	}
	m_szActiveID=lpszID;
  m_szHiggleID=lpszID;
}

void __fastcall TPurchaseRoadForm::btnQueryClick(TObject *Sender)
{
	CString szSQL,szSQL1;
	char strDep0[80],strDep1[80],strStockMan[80],strID[256],strSHID[256];
 	int nRightSH;
//---------- new 0711---取得操作者对应的采购部门别(在StockHandleman中的公司别)------srtSHID-------
        szSQL.Format("select * from StockHandleman where sh_code='%s'",operatorcode);
        RunSQL(dm1->Query1,szSQL,true);
        strcpy(strSHID,dm1->Query1->FieldByName("sh_sdcode")->AsString.c_str());
//------------------------------------------------------------------------------

	m_szActiveID="";
	edtMainID->Text=edtMainID->Text.Trim();
	if(edtMainID->Text.IsEmpty())
	{
		ShowMessage("请输入7位请购单本单编号");
		ResetCtrl();
		if(edtMainID->CanFocus())	edtMainID->SetFocus();
		return;
	}
	szSQL.Format("select * from AskPurchase,StockDepart where ap_code='%s'"
		" and ap_sdcode=sd_code",edtMainID->Text.c_str());
	RunSQL(dm1->Query1,szSQL,true);
	if(dm1->Query1->Eof)
	{
		ShowMessage("没有该请购单的资料");
		ResetCtrl();
		if(edtMainID->CanFocus())	edtMainID->SetFocus();
		return;
	}
	if(dm1->Query1->FieldByName("ap_affirmdate")->IsNull)
	{
		ShowMessage("该请购单还没有接案");
		ResetCtrl();
		return;
	}
	if(dm1->Query1->FieldByName("ap_shcode")->IsNull)
	{
		ShowMessage("该请购单还没有指派采购经办");
		ResetCtrl();
		return;
	}
	edtAfmDate->Text=DateField2Text(dm1->Query1->FieldByName("ap_affirmdate"));
	edtNeedDate->Text=DateField2Text(dm1->Query1->FieldByName("ap_needdate"));
	edtType->Text = dm1->Query1->FieldByName("ap_type")->AsString=="I" ? "紧急" : "一般";
	edtAskDate->Text=DateField2Text(dm1->Query1->FieldByName("ap_reqdate"));
	edtBuyType->Text=dm1->Query1->FieldByName("ap_buytype")->AsString=="M" ? "内购" : "外购";
	edtStockDep->Text=dm1->Query1->FieldByName("sd_name")->AsString;
	strcpy(strDep0,dm1->Query1->FieldByName("ap_reqdepart")->AsString.c_str());
	strcpy(strDep1,dm1->Query1->FieldByName("ap_chargedep")->AsString.c_str());
	edtProject->Text=dm1->Query1->FieldByName("ap_prjcode")->AsString;
	strcpy(strStockMan,dm1->Query1->FieldByName("ap_shcode")->AsString.c_str());

	strcpy(strID,dm1->Query1->FieldByName("ap_sdcode")->AsString.c_str());
//------new 0713----------------------------------------------------------------
//        nRightSH=GetOperatorRight(operatorcode.c_str(),"IDM_PR_PRSHLPRICE");            //取得权限
        nRightSH=GetOperatorRight(operatorcode.c_str(),"IDM_PRSHLPRICE");            //取得权限
	szSQL1.Format("select * from AskPurchase,BookFactory,StockDepart where ap_code='%s'"
		" and ap_code=substring(bf_apcode,1,7) and ap_sdcode=sd_code",edtMainID->Text.c_str());
	RunSQL(dm1->Query3,szSQL1,true);                                        //判断该单是否已呈核
//     if((g_theOperator.op_cpcode[0]=='A' && strcmp(strID,strSHID)!=0 && operatorcode!="admin" && operatorcode!="108557") || (g_theOperator.op_cpcode[0]!='A' && operatorcode!=strStockMan  && operatorcode!="admin" && operatorcode!="108557") || nRightSH!=2)
        if (nRightSH==3 && !dm1->Query3->Eof)                                                            //权限为1的人员可以查看本采购部门其它经办的已呈准的采购过程
        {
                if(strcmp(strID,strSHID)!=0 && operatorcode!="admin")
                {
                        ShowMessage("您只能查看自己的采购过程!");
                        return;
                }
        }
        else if (nRightSH==3)
        {//未下订单的
                if(operatorcode!=strStockMan && operatorcode!="108650" && operatorcode!="admin")        //其它的只有经办自己才能查询
                {
                        ShowMessage("您只能查看自己的采购过程!!");
                        return;
                }
        }
        else
        {//未受权"采购经办间可查看"
                if(operatorcode!=strStockMan && operatorcode!="admin")        //其它的只有经办自己才能查询
                {
                        ShowMessage("您只能查看自己的采购过程!!!");
                        return;
                }
        }

/*     if(nRightSH==3 && !dm1->Query3->Eof)                                                            //权限为1的人员可以查看本采购部门其它经办的已呈准的采购过程
     {
        if(strcmp(strID,strSHID)!=0 && operatorcode!="admin")
        {
                ShowMessage("您只能查看自己的采购过程");
                return;
        }
     }
     else
     {
        if(operatorcode!=strStockMan && operatorcode!="admin")        //其它的只有经办自己才能查询
        {
                ShowMessage("您只能查看自己的采购过程__");
                return;
        }
     }
*/

/*  if(strcmp(strID,strSHID)!=0 && operatorcode!="admin" && operatorcode!="108557" && operatorcode!="0")
  {
  	ShowMessage("您只能查看自己的采购过程");
    return;
  }     */
//------------------------------------------------------------------------------
	if(strDep0[0]!='\0')
	{
		szSQL.Format("select * from DicDepart where dd_code='%s'",strDep0);
		RunSQL(dm1->Query1,szSQL,true);
		if(!dm1->Query1->Eof)
		{
			edtAskDepart->Text=dm1->Query1->FieldByName("dd_name")->AsString;
		}
	}
//	if(strDep1[0]!='\0')
//	{
//		szSQL.Format("select * from DicDepart where dd_code='%s'",strDep1);
//		RunSQL(dm1->Query1,szSQL,true);
//		if(!dm1->Query1->Eof)
//		{
//			edtChargeDep->Text=dm1->Query1->FieldByName("dd_name")->AsString;
//		}
//	}
	edtStockMan->Text="";
	edtTel->Text="";
	if(strStockMan[0]!='\0')
	{
            if(operatorcode=="107532")
              {
               szSQL.Format("select * from StockHandleman,operator where sh_code=op_code"
                            " and op_cpcode in (select op_cpcode from operator where op_code='107532')"
                            " and sh_code='%s'",strStockMan);
               RunSQL(dm1->Query1,szSQL,true);
               if(!dm1->Query1->Eof)
		{
			edtStockMan->Text=dm1->Query1->FieldByName("sh_name")->AsString;
			edtTel->Text=dm1->Query1->FieldByName("sh_tel")->AsString;
		}
              }
            else
	      {
                szSQL.Format("select * from StockHandleman where sh_code='%s'",strStockMan);
		RunSQL(dm1->Query1,szSQL,true);
		if(!dm1->Query1->Eof)
		{
			edtStockMan->Text=dm1->Query1->FieldByName("sh_name")->AsString;
			edtTel->Text=dm1->Query1->FieldByName("sh_tel")->AsString;
		}
              }
	}
	switch(m_enRegion)
	{
		case EN_REG_SPEER:	OnQuerySpeer(edtMainID->Text.c_str());	break;
		case EN_REG_QUOTE:	OnQueryQuote(edtMainID->Text.c_str());	break;
		case EN_REG_HIGGLE:	OnQueryHiggle(edtMainID->Text.c_str());	break;
		case EN_REG_SHOW:		OnQueryShow(edtMainID->Text.c_str());		break;
		case EN_REG_DECIDE:	OnQueryDecide(edtMainID->Text.c_str());	break;
		case EN_REG_BOOK:		OnQueryBook(edtMainID->Text.c_str());		break;
		case EN_REG_LIST:		InitStockList();	break;
		default:	break;
	}
/*
  if(ctlPage->ActivePage==ctlSpeer)
		OnQuerySpeer(edtMainID->Text.c_str());
	else if(ctlPage->ActivePage==ctlQuote)
		OnQueryQuote(edtMainID->Text.c_str());
	else if(ctlPage->ActivePage==ctlHiggle)
		OnQueryHiggle(edtMainID->Text.c_str());
  else if(ctlPage->ActivePage==ctlShow)
  	OnQueryShow(edtMainID->Text.c_str());
	else if(ctlPage->ActivePage==ctlDecide)
		OnQueryDecide(edtMainID->Text.c_str());
*/
	ResetCtrl();
}
//---------------------------------------------------------------------------

void __fastcall TPurchaseRoadForm::FormShow(TObject *Sender)
{
	edtMainID		->Text="";
	edtNeedDate	->Text="";
	edtType			->Text="";
	edtAskDate	->Text="";
	edtBuyType	->Text="";
	edtAskDepart->Text="";
	edtStockDep	->Text="";
	edtAfmDate	->Text="";
//	edtChargeDep->Text="";
	edtStockMan	->Text="";
	edtTel			->Text="";
	edtProject	->Text="";
  lstPriceRT	->Text="";

	EnableEdit(edtProject		,false);
	EnableEdit(edtAfmDate		,false);
	EnableEdit(edtNeedDate	,false);
	EnableEdit(edtType			,false);
	EnableEdit(edtAskDate		,false);
	EnableEdit(edtBuyType		,false);
	EnableEdit(edtAskDepart	,false);
	EnableEdit(edtStockDep	,false);
//	EnableEdit(edtChargeDep	,false);
	EnableEdit(edtStockMan	,false);
	EnableEdit(edtTel				,false);
	m_enState=EN_STATE_IDLE;
  ResetCtrl();
}
//---------------------------------------------------------------------------

void __fastcall TPurchaseRoadForm::lstSpeerFactExit(TObject *Sender)
{
	OnFactListExit(lstSpeerFact,m_lstSpeerFactID);
}

void TPurchaseRoadForm::OnFactListExit(TComboBox *pList,CStringArray &lstID)
{
	int i;

	if(pList->Items->IndexOf(pList->Text)<0)
	{
		pList->Text=pList->Text.UpperCase();
		for(i=0;i<lstID.GetSize();i++)
		{
			if(lstID[i]==pList->Text.c_str())
			{
				pList->ItemIndex=i;
				break;
			}
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TPurchaseRoadForm::btnNewClick(TObject *Sender)
{
	TDateTime tNow=GetSysTime(false);
	CString szSQL;
  char strUnit[80];
  int i;
  TListItem *pItem;

	if(m_szActiveID.IsEmpty())
  {
  	ShowMessage("请先输入7位请购单编号并查询");
    if(edtMainID->CanFocus())	edtMainID->SetFocus();
    return;
  }
  edtMainID->Text=edtMainID->Text.Trim();
  if(m_szActiveID!=edtMainID->Text.c_str())
  {
  	ShowMessage("您输入的请购单编号与你正在查询的不同，请重新查询");
    return;
  }

	szSQL.Format("select * from AskPurchase where ap_code='%s'",m_szActiveID);
	RunSQL(dm1->Query1,szSQL,true);
	if(dm1->Query1->Eof)
	{
		ShowMessage("该请购单不存在，可能是被其他人删除了");
		return;
	}
	if(operatorcode!=dm1->Query1->FieldByName("ap_shcode")->AsString && operatorcode!="admin" && operatorcode!="108557")
	{
		ShowMessage("只有admin和采购经办自己才能新增、删除或修改请购过程内容");
		return;
	}

	if(ctlPage->ActivePage==ctlSpeer)
  {
		EmptySpeer();
    szSQL.Format("select * from QuoteFactory where qf_apcode='%s'",m_szActiveID);
		RunSQL(dm1->Query1,szSQL,true);
    if(!dm1->Query1->Eof)
    {
			edtSpeerEndDate->Text=DateField2Text(dm1->Query1->FieldByName("qf_enddate"));
    }
		m_enState=EN_STATE_NEW;
		ResetCtrl();

		if(edtSpeerEndDate->CanFocus())	edtSpeerEndDate->SetFocus();
  }
  else if(ctlPage->ActivePage==ctlQuote)
  {
		EmptyQuote();
  	edtQuoteInpDate->Text=(LPCSTR)Date2YYMMDD(tNow);
    lstQuotePay->ItemIndex=lstQuotePay->Items->IndexOf("月结30天");
    lstQuoteDelivery->ItemIndex=lstQuoteDelivery->Items->IndexOf("送货进厂");
/*
		if(!m_szActiveID.IsEmpty() && lstQuoteView->Selected!=NULL)
    {
    	pItem=lstQuoteView->Selected;
      szSQL.Format("select * from PurchaseDetail where pd_code='%s%s'",
				m_szActiveID,pItem->Caption.c_str());
      RunSQL(dm1->Query1,szSQL,true);
      if(!dm1->Query1->Eof)
      {
      	strcpy(strUnit,dm1->Query1->FieldByName("pd_ducode")->AsString.c_str());
        for(i=0;i<m_lstQuoteUnitID.GetSize();i++)
        {
        	if(m_lstQuoteUnitID[i]==strUnit)
          {
          	lstQuoteUnit->ItemIndex=i;
            break;
          }
        }
      }
    }
*/
		for(i=0;i<m_lstQuoteRMBID.GetSize();i++)
		{
			if(m_lstQuoteRMBID[i]=="RMB")
			{
				lstQuoteRMB->ItemIndex=i;
				break;
			}
		}
		if(i==m_lstQuoteRMBID.GetSize())	lstQuoteRMB->ItemIndex=0;

		m_enState=EN_STATE_NEW;
		ResetCtrl();
  	if(edtQuoteItem->CanFocus())	edtQuoteItem->SetFocus();
  }
  else if(ctlPage->ActivePage==ctlHiggle)
  {
//		EmptyHiggle();
  	edtHiggleDate->Text=(LPCSTR)Date2YYMMDD(tNow);
		m_enState=EN_STATE_NEW;
		ResetCtrl();
    if(edtHigglePrice->CanFocus())	edtHigglePrice->SetFocus();
  }
  else if(ctlPage->ActivePage==ctlShow)
  {
		EmptyShow();
  	edtShowDate->Text=(LPCSTR)Date2YYMMDD(tNow);

		m_enState=EN_STATE_NEW;
		ResetCtrl();
    if(edtShowItem->CanFocus())	edtShowItem->SetFocus();
  }
}
//---------------------------------------------------------------------------

void TPurchaseRoadForm::OnSpeerNew()
{
	m_enState=EN_STATE_NEW;
	ResetCtrl();
}

void TPurchaseRoadForm::ResetCtrl()
{
	bool bIdle,bAuth;
	bIdle=m_enState==EN_STATE_IDLE;
	bAuth=m_nAuthor==AUTH_FULL;

	edtMainID->Enabled=bIdle;

	btnQuery	->Enabled = bIdle;
	btnDetail	->Enabled= bIdle && !edtMainID->Text.IsEmpty();
	btnOK			->Enabled = !bIdle;
	btnExit->Caption = bIdle ? "退    出" : "放    弃";

	if(m_enRegion==EN_REG_SPEER)
	{
		EnableCombo(lstSpeerFact,m_enState==EN_STATE_NEW);

		btnNew		->Enabled = bIdle && bAuth;
		EnableEdit(edtSpeerEndDate,!bIdle);
		EnableEdit(edtSpeerPrnDate,false);

		btnSpeerPrn->Enabled = bIdle && !m_szActiveID.IsEmpty();
		btnSpeerFactInf->Enabled = bIdle && lstSpeerView->ItemIndex>=0;
    btnSpeerFactSearch->Enabled=lstSpeerFact->Enabled;

		btnEdit	->Enabled = bIdle && bAuth && lstSpeerView->ItemIndex>=0;
		btnMove	->Enabled = bIdle && bAuth && lstSpeerView->ItemIndex>=0;
	}
	else if(m_enRegion==EN_REG_QUOTE)
	{
		EnableEdit(edtQuoteItem			,m_enState==EN_STATE_NEW);
		EnableCombo(lstQuoteFact		,m_enState==EN_STATE_NEW);

		EnableEdit(edtQuoteFactCard	,!bIdle);
		EnableEdit(edtQuoteNum			,!bIdle);
		EnableEdit(edtQuotePrice		,!bIdle);
		EnableCombo(lstQuoteRMB			,!bIdle);
		EnableEdit(edtQuoteDelDays	,!bIdle);
//		EnableEdit(edtQuoteTax			,!bIdle);
		EnableEdit(edtQuoteInpDate	,!bIdle);

		EnableCombo(lstQuoteUnit	,!bIdle);
		EnableCombo(lstQuotePay		,!bIdle);
		EnableCombo(lstQuoteDelivery,!bIdle);
                EnableCombo(lstQuoteTax		,!bIdle);

		btnNew		->Enabled = bIdle && bAuth;
		btnEdit	->Enabled = bIdle && bAuth && lstQuoteView->Selected!=NULL;
		btnMove	->Enabled = bIdle && bAuth && lstQuoteView->Selected!=NULL;
		btnQuotePrint->Enabled=bIdle && !m_szActiveID.IsEmpty();
	}
	else if(m_enRegion==EN_REG_HIGGLE)
	{
		EnableEdit(edtHigglePrice	,!bIdle);
		EnableEdit(edtHiggleDate	,!bIdle);
		EnableEdit(edtHiggleRMB		,false);

		lstHiggleView->Enabled = bIdle;
		btnNew	->Enabled = false;
		btnMove	->Enabled = false;
		btnEdit	->Enabled = bIdle && bAuth && lstHiggleView->Selected!=NULL;
		btnHigglePrint->Enabled=bIdle && !m_szActiveID.IsEmpty();
	}
	else if(m_enRegion==EN_REG_SHOW)
	{
		EnableEdit(edtShowItem,m_enState==EN_STATE_NEW);
		EnableCombo(lstShowFact,m_enState==EN_STATE_NEW);
		EnableEdit(edtShowDate	,m_enState==EN_STATE_NEW);
		EnableEdit(edtShowRem		,!bIdle);
    EnableCombo(lstPriceRT	,!bIdle);
    EnableEdit(edtValidDate	,!bIdle);
		EnableEdit(edtShowNum		,!bIdle);

		btnShowPrint->Enabled = bIdle && !m_szActiveID.IsEmpty();
		lstShowView->Enabled = bIdle;
		btnNew		->Enabled = bIdle && bAuth;
		btnEdit	->Enabled = bIdle && bAuth && lstShowView->Selected!=NULL;
		btnMove	->Enabled = bIdle && bAuth && lstShowView->Selected!=NULL;
	}
	else if(m_enRegion==EN_REG_DECIDE)
	{
		EnableEdit(edtDecideItem,false);
		EnableEdit(edtDecideFact0,false);
    EnableEdit(edtDfShowDate,false);

		EnableCombo(lstDecideFact	,!bIdle);
		EnableEdit(edtDecideDate	,!bIdle);
		EnableEdit(edtDecideNum		,false);
		EnableCombo(lstDecideUnit	,!bIdle);
		EnableEdit(edtDecidePrice	,!bIdle);

		btnNew->Enabled=false;
		btnMove->Enabled=false;
		lstDecideView->Enabled=bIdle;
		btnEdit	->Enabled = bIdle && bAuth && lstDecideView->Selected!=NULL;
	}
	else if(m_enRegion==EN_REG_BOOK)
	{
		btnNew->Enabled=false;
		btnMove->Enabled=false;
		btnEdit	->Enabled = false;
//		btnToBook->Enabled=lstBookView->Selected!=NULL;
	}
}


void __fastcall TPurchaseRoadForm::btnOKClick(TObject *Sender)
{
	int nState=m_enState;

	switch(m_enRegion)
	{
		case EN_REG_SPEER:	OnSpeerOK();		break;
		case EN_REG_QUOTE:	OnQuoteOK();		break;
		case EN_REG_HIGGLE:	OnHiggleOK();		break;
		case EN_REG_SHOW:	OnShowOK();			break;
		case EN_REG_DECIDE:	OnDecideOK();		break;
		default:	break;
	}
  if(m_enState!=EN_STATE_IDLE)	return;
  if(nState==EN_STATE_NEW)
  {
  	if(btnNew->CanFocus())	btnNew->SetFocus();
  }
  else if(nState==EN_STATE_EDIT)
  {
  	if(btnEdit->CanFocus())	btnEdit->SetFocus();
  }
}
//---------------------------------------------------------------------------

void TPurchaseRoadForm::OnSpeerOK()
{
	int nSel;
	CString szSQL;
	char strEndDate[80],strPrnDate[80],strID[80];

	edtSpeerEndDate->Text=edtSpeerEndDate->Text.Trim();
	edtSpeerPrnDate->Text=edtSpeerPrnDate->Text.Trim();

	if(!CheckDateEditor(edtSpeerEndDate))	return;
  edtSpeerPrnDate->Text=edtSpeerPrnDate->Text.Trim();
  if(!edtSpeerPrnDate->Text.IsEmpty())
	{
		if(!CheckDateEditor(edtSpeerPrnDate))	return;
		Date2Dbdate(edtSpeerPrnDate->Text.c_str(),strPrnDate);
  }
  else
	{
  	strPrnDate[0]='\0';
  }
	if((nSel=lstSpeerFact->ItemIndex)<0 || nSel>=m_lstSpeerFactID.GetSize())
	{
		ShowMessage("请选择一个有效的厂商");
		return;
	}
	Date2Dbdate(edtSpeerEndDate->Text.c_str(),strEndDate);

	if(m_enState==EN_STATE_NEW)
	{
		szSQL.Format("select * from QuoteFactory where qf_apcode=%s and qf_mfcode=%s"
			,Str2DBString(m_szActiveID),Str2DBString(m_lstSpeerFactID[nSel]));
		RunSQL(dm1->Query1,szSQL,true);
		if(!dm1->Query1->Eof)
		{
			ShowMessage("数据库中已有该项数据");
			return;
		}

		szSQL="insert into QuoteFactory (qf_apcode,qf_mfcode,qf_enddate,qf_printdate) values(";
		szSQL+=Str2DBString(m_szActiveID);
		szSQL+=",";	szSQL+=Str2DBString(m_lstSpeerFactID[nSel]);
		szSQL+=",";	szSQL+=Str2DBString(strEndDate);
		szSQL+=",";	szSQL+=Str2DBString(strPrnDate);
		szSQL+=")";
		if(!RunSQL(dm1->Query1,szSQL))	return;

		lstSpeerView->Items->Add(lstSpeerFact->Text);
		m_lstSpeerViewID.Add(m_lstSpeerFactID[nSel]);

		m_enState=EN_STATE_IDLE;
		ResetCtrl();
	}
	else if(m_enState==EN_STATE_EDIT)
	{
		if(lstSpeerView->ItemIndex<0 || lstSpeerView->ItemIndex>=m_lstSpeerViewID.GetSize())	return;
		strcpy(strID,m_lstSpeerViewID[lstSpeerView->ItemIndex]);

		szSQL.Format("select * from QuoteFactory where qf_apcode=%s and qf_mfcode=%s"
			,Str2DBString(m_szActiveID),Str2DBString(strID));
		RunSQL(dm1->Query1,szSQL,true);
		if(dm1->Query1->Eof)
		{
			ShowMessage("数据库中没有该项数据");
			return;
		}

		szSQL="update QuoteFactory set";
		szSQL+=" qf_mfcode=";				szSQL+=Str2DBString(m_lstSpeerFactID[nSel]);
		szSQL+=",qf_enddate=";			szSQL+=Str2DBString(strEndDate);
		szSQL+=",qf_printdate=";		szSQL+=Str2DBString(strPrnDate);
		szSQL+=" where qf_apcode=";	szSQL+=Str2DBString(m_szActiveID);
		szSQL+=" and qf_mfcode=";		szSQL+=Str2DBString(strID);
		if(!RunSQL(dm1->Query1,szSQL))	return;

		lstSpeerView->Items->Strings[lstSpeerView->ItemIndex]=lstSpeerFact->Text;
		m_lstSpeerViewID[lstSpeerView->ItemIndex]=m_lstSpeerFactID[nSel];
		m_enState=EN_STATE_IDLE;
		ResetCtrl();
	}
}

void __fastcall TPurchaseRoadForm::lstSpeerViewClick(TObject *Sender)
{
	int nSel;
  CString szSQL;

	if(m_szSpeerID.IsEmpty())	return;
	if((nSel=lstSpeerView->ItemIndex)<0 || nSel>=m_lstSpeerViewID.GetSize())
	{
		edtSpeerEndDate->Text="";
		edtSpeerPrnDate->Text="";
		lstSpeerFact->ItemIndex=-1;
		return;
	}
	szSQL.Format("select * from QuoteFactory where qf_apcode='%s' and qf_mfcode='%s'",
		m_szSpeerID,m_lstSpeerViewID[nSel]);
	RunSQL(dm1->Query1,szSQL,true);
	if(!dm1->Query1->Eof)
	{
		edtSpeerEndDate->Text=DateField2Text(dm1->Query1->FieldByName("qf_enddate"));
		edtSpeerPrnDate->Text=DateField2Text(dm1->Query1->FieldByName("qf_printdate"));
		lstSpeerFact->Text=lstSpeerView->Items->Strings[nSel];
	}
	ResetCtrl();
}
//---------------------------------------------------------------------------

void __fastcall TPurchaseRoadForm::btnEditClick(TObject *Sender)
{
	int nSel,i;
  TDateTime tNow;
	CString szSQL;
	TListItem *pItem;
	char strID[80],strMN[80];

  tNow=GetSysTime(false);

	if(m_szActiveID.IsEmpty())	return;
	if(m_szActiveID!=edtMainID->Text.c_str())
	{
		ShowMessage("您输入的请购单号与您正在查询的编号不同，请重新查询");
		return;
	}

	szSQL.Format("select * from AskPurchase where ap_code='%s'",m_szActiveID);
	RunSQL(dm1->Query1,szSQL,true);
	if(dm1->Query1->Eof)
	{
		ShowMessage("该请购单不存在，可能是被其他人删除了");
		return;
	}
	if(operatorcode!=dm1->Query1->FieldByName("ap_shcode")->AsString && operatorcode!="admin" && operatorcode!="108650")
	{
		ShowMessage("只有admin和采购经办自己才能新增、删除或修改请购过程内容__");
		return;
	}
/*	if(operatorcode!=dm1->Query1->FieldByName("ap_shcode")->AsString && operatorcode!="admin")
	{
		ShowMessage("只有admin和采购经办自己才能新增、删除或修改请购过程内容");
		return;
	}
*/
	if(ctlPage->ActivePage==ctlSpeer)
	{
		if(m_szActiveID!=m_szSpeerID)	return;
		if((nSel=lstSpeerView->ItemIndex)<0 || nSel>=m_lstSpeerViewID.GetSize())	return;
	}
        else if(ctlPage->ActivePage==ctlQuote)
        {
  	        if(m_szActiveID!=m_szQuoteID)           return;
                if(lstQuoteView->Selected==NULL)	return;
        }
	else if(ctlPage->ActivePage==ctlHiggle)
	{
		if(m_szActiveID!=m_szHiggleID)          return;
		if(lstHiggleView->Selected==NULL)	return;
                        if(edtHiggleDate->Text.IsEmpty())
        	  	edtHiggleDate->Text=(LPCSTR)Date2YYMMDD(tNow);

                if(edtHigglePrice->Text.IsEmpty())
                {
                    	pItem=lstHiggleView->Selected;
			if((nSel=lstHiggleView->Items->IndexOf(pItem))<0 || nSel>=m_lstHiggleViewID.GetSize())	return;

                        szSQL.Format("select * from CompareFactory where cf_apcode='%s%s' and cf_mfcode='%s'",
			m_szActiveID,pItem->Caption.c_str(),m_lstHiggleViewID[nSel]);
                        RunSQL(dm1->Query1,szSQL,true);
                        if(!dm1->Query1->Eof)
                    	{
                              	edtHigglePrice->Text=FloatField2String(dm1->Query1->FieldByName("cf_quoteprice"),3);
                        }
                 }
		m_enState=EN_STATE_EDIT;
		ResetCtrl();
                if(edtHigglePrice->CanFocus())	edtHigglePrice->SetFocus();
                return;
       	}
        else if(ctlPage->ActivePage==ctlDecide)
	{
                if(edtDecideDate->Text.IsEmpty())
                {
                        edtDecideDate->Text=(LPCSTR)Date2YYMMDD(tNow);
			if((pItem=lstDecideView->Selected)!=NULL)
			{
				lstDecideFact->ItemIndex=lstDecideFact->Items->IndexOf(pItem->SubItems->Strings[0]);
				if((nSel=lstDecideFact->ItemIndex)>=0 && nSel<m_lstDecideFactID.GetSize())
				{
					szSQL.Format("select * from CompareFactory,PurchaseDetail"
						" where cf_apcode=pd_code and cf_apcode='%s%s' and cf_mfcode='%s'",
						m_szActiveID,pItem->Caption.c_str(),m_lstDecideFactID[nSel]);
					RunSQL(dm1->Query1,szSQL,true);
					if(!dm1->Query1->Eof)
					{
//						edtDecideNum->Text=IntField2Text(dm1->Query1->FieldByName("cf_quotenum"));
						strcpy(strMN,dm1->Query1->FieldByName("pd_mncode")->AsString.c_str());
						if(strMN[0]=='E' && strMN[1]=='M') //宏信原料单价 .6
							edtDecidePrice->Text=FloatField2String(dm1->Query1->FieldByName("cf_higgleprice"),6);
						else
							edtDecidePrice->Text=FloatField2String(dm1->Query1->FieldByName("cf_higgleprice"),3);
						strcpy(strID,dm1->Query1->FieldByName("cf_quoteunit")->AsString.c_str());
						for(i=0;i<m_lstDecideUnitID.GetSize();i++)
						{
							if(m_lstDecideUnitID[i]==strID)
							{
								lstDecideUnit->ItemIndex=i;
								break;
							}
                                                }
                                        }
                                }
                        }
                }
		m_enState=EN_STATE_EDIT;
		ResetCtrl();
  	        if(lstDecideFact->CanFocus())	lstDecideFact->SetFocus();
                return;
        }
	m_enState=EN_STATE_EDIT;
	ResetCtrl();
}
//---------------------------------------------------------------------------

void __fastcall TPurchaseRoadForm::btnDetailClick(TObject *Sender)
{
	edtMainID->Text=edtMainID->Text.Trim();
  if(edtMainID->Text.IsEmpty())	return;

	int nRight=GetOperatorRight(operatorcode.c_str(),"IDM_ASKPURCHASE");
	//请购单输入接口，文件：AskPurchase.*
	AskPurchase(edtMainID->Text.c_str(),nRight);
}
//---------------------------------------------------------------------------

void __fastcall TPurchaseRoadForm::edtMainIDChange(TObject *Sender)
{
	if(m_enState==EN_STATE_IDLE)
	{
  	btnDetail->Enabled = !edtMainID->Text.IsEmpty();
  }
}
//---------------------------------------------------------------------------

void __fastcall TPurchaseRoadForm::ctlPageChanging(TObject *Sender,bool &AllowChange)
{
	AllowChange = m_enState==EN_STATE_IDLE;
}
//---------------------------------------------------------------------------

void __fastcall TPurchaseRoadForm::btnMoveClick(TObject *Sender)
{
	CString szSQL;

	if(m_szActiveID.IsEmpty())	return;
	if(m_szActiveID!=edtMainID->Text.c_str())
	{
		ShowMessage("您输入的请购单号与您正在查询的编号不同，请重新查询");
		return;
	}

	szSQL.Format("select * from AskPurchase where ap_code='%s'",m_szActiveID);
	RunSQL(dm1->Query1,szSQL,true);
	if(dm1->Query1->Eof)
	{
		ShowMessage("该请购单不存在，可能是被其他人删除了");
		return;
	}
	if(operatorcode!=dm1->Query1->FieldByName("ap_shcode")->AsString && operatorcode!="admin" && operatorcode!="108650")
	{
		ShowMessage("只有admin和采购经办自己才能新增、删除或修改请购过程内容");
		return;
	}

/*	if(operatorcode!=dm1->Query1->FieldByName("ap_shcode")->AsString && operatorcode!="admin" && operatorcode!="108557")
	{
		ShowMessage("只有admin和采购经办自己才能新增、删除或修改请购过程内容");
		return;
	}
*/
	if(ctlPage->ActivePage==ctlSpeer)
		OnSpeerMove();
	else if(ctlPage->ActivePage==ctlQuote)
		OnQuoteMove();
	else if(ctlPage->ActivePage==ctlShow)
		OnShowMove();
}

void TPurchaseRoadForm::OnQuoteMove()
{
	int nSel;
	CString szSQL;
	TListItem *pItem;
  char strID[80];

	if(m_szActiveID!=m_szQuoteID)	return;
	if((pItem=lstQuoteView->Selected)==NULL)	return;
	if((nSel=lstQuoteView->Items->IndexOf(pItem))<0 || nSel>=m_lstQuoteViewID.GetSize())	return;

	if(Application->MessageBox("真要删除选定的数据吗","警告",MB_YESNOCANCEL | MB_ICONQUESTION | MB_DEFBUTTON2)!=IDYES)	return;

  sprintf(strID,"%s%s",m_szActiveID,pItem->Caption.c_str());
	szSQL="delete CompareFactory";
	szSQL+=" where cf_apcode=";	szSQL+=Str2DBString(strID);
	szSQL+=" and cf_mfcode=";		szSQL+=Str2DBString(m_lstQuoteViewID[nSel]);
	if(!RunSQL(dm1->Query1,szSQL))	return;

	lstQuoteView->Items->Delete(nSel);
	m_lstQuoteViewID.RemoveAt(nSel);

	m_enState=EN_STATE_IDLE;
	ResetCtrl();
}
//---------------------------------------------------------------------------

void TPurchaseRoadForm::OnSpeerMove()
{
	int nSel;
	CString szSQL;

	if(m_szActiveID!=m_szSpeerID)	return;
	if((nSel=lstSpeerView->ItemIndex)<0 || nSel>=m_lstSpeerViewID.GetSize())	return;

	if(Application->MessageBox("真要删除选定的数据吗","警告",MB_YESNOCANCEL | MB_ICONQUESTION | MB_DEFBUTTON2)!=IDYES)	return;

	szSQL="delete QuoteFactory";
	szSQL+=" where qf_apcode=";	szSQL+=Str2DBString(m_szActiveID);
	szSQL+=" and qf_mfcode=";		szSQL+=Str2DBString(m_lstSpeerViewID[nSel]);
	if(!RunSQL(dm1->Query1,szSQL))	return;

	lstSpeerView->Items->Delete(nSel);
	m_lstSpeerViewID.RemoveAt(nSel);

	m_enState=EN_STATE_IDLE;
	ResetCtrl();
}
//---------------------------------------------------------------------------

void TPurchaseRoadForm::EmptyQuote()
{
	edtQuoteItem		->Text="";
	edtQuoteFactCard->Text="";
	edtQuoteReqUnit	->Text="";
	edtQuoteReqNum	->Text="";
	edtQuoteNum			->Text="";
	edtQuotePrice		->Text="";
	edtQuoteDelDays	->Text="";
	edtQuoteInpDate	->Text="";

	lstQuoteFact->ItemIndex=-1;
	lstQuoteFact->Text="";
	lstQuoteUnit->ItemIndex=-1;
	lstQuoteUnit->Text="";
	lstQuotePay->Text="";
  lstQuoteDelivery->Text="";
	lstQuoteDelivery->ItemIndex=-1;
  lstQuoteTax->ItemIndex=-1;
}

void TPurchaseRoadForm::InitQuoteFactory()
{
	CString szSQL;

	if(!m_szActiveID.IsEmpty())
	{
		szSQL.Format("select * from QuoteFactory,Manufactur"
			" where qf_mfcode=mf_code and qf_apcode='%s'"
			" order by mf_code",m_szActiveID);

		m_lstQuoteFactID.RemoveAll();
		lstQuoteFact->Items->Clear();
		RunSQL(dm1->Query1,szSQL,true);
		while(!dm1->Query1->Eof)
		{
			m_lstQuoteFactID.Add(dm1->Query1->FieldByName("mf_code")->AsString.c_str());
			lstQuoteFact->Items->Add(dm1->Query1->FieldByName("mf_shortname")->AsString);

			dm1->Query1->Next();
		}
	}
}


void __fastcall TPurchaseRoadForm::ctlQuoteShow(TObject *Sender)
{
	CString szSQL;

	InitQuoteFactory();

	if(!m_bQuoteInitialed)
	{
		szSQL="select * from DicUnits order by du_code";
		RunSQL(dm1->Query1,szSQL,true);
		while(!dm1->Query1->Eof)
		{
			m_lstQuoteUnitID.Add(dm1->Query1->FieldByName("du_code")->AsString.c_str());
			lstQuoteUnit->Items->Add(dm1->Query1->FieldByName("du_name")->AsString);
			dm1->Query1->Next();
		}
		szSQL="select * from DicPayment order by pm_code";
		RunSQL(dm1->Query1,szSQL,true);
		while(!dm1->Query1->Eof)
		{
			m_lstQuotePayID.Add(dm1->Query1->FieldByName("pm_code")->AsString.c_str());
			lstQuotePay->Items->Add(dm1->Query1->FieldByName("pm_name")->AsString);
			dm1->Query1->Next();
		}

		szSQL="select * from diccurrency order by dc_code";
		RunSQL(dm1->Query1,szSQL,true);
		while(!dm1->Query1->Eof)
		{
			m_lstQuoteRMBID.Add(dm1->Query1->FieldByName("dc_code")->AsString.c_str());
			lstQuoteRMB->Items->Add(dm1->Query1->FieldByName("dc_name")->AsString);
			dm1->Query1->Next();
		}

   	m_lstQuoteDeliveryID.Add("");
    lstQuoteDelivery->Items->Add("");
    szSQL="select * from DicDelivery order by dd_code";
    RunSQL(dm1->Query1,szSQL,true);
    while(!dm1->Query1->Eof)
  	{
    	m_lstQuoteDeliveryID.Add(dm1->Query1->FieldByName("dd_code")->AsString.c_str());
      lstQuoteDelivery->Items->Add(dm1->Query1->FieldByName("dd_name")->AsString);

    	dm1->Query1->Next();
    }
//---------添加所有税别---------------------------------------------------------
/*
    szSQL="select * from DicInvoice order by di_code";
    RunSQL(dm1->Query1,szSQL,true);
    while(!dm1->Query1->Eof)
    {
    	m_lstQuoteTaxID.Add(dm1->Query1->FieldByName("di_code")->AsString.c_str());
      lstQuoteTax->Items->Add(dm1->Query1->FieldByName("di_name")->AsString);

    	dm1->Query1->Next();
    }
*/
		EmptyQuote();

		EnableEdit(edtQuoteReqUnit	,false);
		EnableEdit(edtQuoteReqNum		,false);
	}
	m_bQuoteInitialed=true;

	m_enRegion=EN_REG_QUOTE;
	if(!m_szActiveID.IsEmpty())	OnQueryQuote(m_szActiveID);
	m_enState=EN_STATE_IDLE;
	ResetCtrl();
}
//---------------------------------------------------------------------------

void __fastcall TPurchaseRoadForm::lstQuoteFactExit(TObject *Sender)
{ 
//	int nPreSel=lstQuoteFact->ItemIndex;
	OnFactListExit(lstQuoteFact,m_lstQuoteFactID);
//	if(lstQuoteFact->ItemIndex==nPreSel)	return;

        int nSel,i;
	char strTax[80];

        lstQuoteTax->Clear();
	m_lstQuoteTaxID.RemoveAll();
	if((nSel=lstQuoteFact->ItemIndex)>=0 && nSel<m_lstQuoteFactID.GetSize())        //添加厂商档里的税别
        {
                CString szSQL;
		szSQL.Format("select * from Manufactur,DicInvoice where mf_taxtype=di_code and mf_code='%s'",m_lstQuoteFactID[nSel]);
                RunSQL(dm1->Query1,szSQL,true);
                if(!dm1->Query1->Eof)
                {
                        m_lstQuoteTaxID.Add(dm1->Query1->FieldByName("di_code")->AsString.c_str());             //将厂商目前的有效税率(主税率)添加进下拉列表
                        lstQuoteTax->Items->Add(dm1->Query1->FieldByName("di_name")->AsString);
                        dm1->Query1->Next();
                }
                else
                {//主说率找不到
                        szSQL="select * from DicInvoice order by di_code";
                        RunSQL(dm1->Query1,szSQL,true);
                        while(!dm1->Query1->Eof)
                        {
                                m_lstQuoteTaxID.Add(dm1->Query1->FieldByName("di_code")->AsString.c_str());
                                lstQuoteTax->Items->Add(dm1->Query1->FieldByName("di_name")->AsString);

                                dm1->Query1->Next();
                        }
                }
                CString szSQLn;
                szSQLn.Format("select * from Manufactur,DicInvoice where mf_taxtype2=di_code and mf_code='%s'",m_lstQuoteFactID[nSel]);
                RunSQL(dm1->Query4,szSQLn,true);
                if(!dm1->Query4->Eof)
                {//若主说率找不到，必然也不会执行该步
                        m_lstQuoteTaxID.Add(dm1->Query4->FieldByName("di_code")->AsString.c_str());             //将厂商目前的有效税率(副税率)添加进下拉列表
                        lstQuoteTax->Items->Add(dm1->Query4->FieldByName("di_name")->AsString);
                        dm1->Query4->Next();
                }

        }

/*	if((nSel=lstQuoteFact->ItemIndex)>=0 && nSel<m_lstQuoteFactID.GetSize())        //添加厂商档里的税别
        {
                CString szSQL;
		szSQL.Format("select * from Manufactur,DicInvoice where mf_taxtype=di_code and mf_code='%s'",m_lstQuoteFactID[nSel]);
                RunSQL(dm1->Query1,szSQL,true);
                if(!dm1->Query1->Eof)
                {
                        m_lstQuoteTaxID.Add(dm1->Query1->FieldByName("di_code")->AsString.c_str());             //将厂商目前的有效税率(主税率)添加进下拉列表
                        lstQuoteTax->Items->Add(dm1->Query1->FieldByName("di_name")->AsString);
                        dm1->Query1->Next();
                }
                CString szSQLn;
		szSQLn.Format("select * from Manufactur,DicInvoice where mf_taxtype2=di_code and mf_code='%s'",m_lstQuoteFactID[nSel]);
                RunSQL(dm1->Query4,szSQLn,true);
                if(!dm1->Query4->Eof)
                {
                        m_lstQuoteTaxID.Add(dm1->Query4->FieldByName("di_code")->AsString.c_str());             //将厂商目前的有效税率(副税率)添加进下拉列表
                        lstQuoteTax->Items->Add(dm1->Query4->FieldByName("di_name")->AsString);
                        dm1->Query4->Next();
                }
        }
*/
//------------------------------------------------------------------------------
	if((nSel=lstQuoteFact->ItemIndex)>=0 && nSel<m_lstQuoteFactID.GetSize())
	{
		CString szSQL;
		szSQL.Format("select * from Manufactur where mf_code='%s'",m_lstQuoteFactID[nSel]);
		RunSQL(dm1->Query1,szSQL,true);
		if(!dm1->Query1->Eof)
		{
			strcpy(strTax,dm1->Query1->FieldByName("mf_taxtype")->AsString.c_str());
			if(strTax[0]=='\0')	return;
			for(i=0;i<m_lstQuoteTaxID.GetSize();i++)
			{
				if(m_lstQuoteTaxID[i]==strTax)
				{
					lstQuoteTax->ItemIndex=i;
                                        break;
				}
                        }
		}
	}

//------------------------------------------------------------------------------
/*
    szSQL="select * from DicInvoice order by di_code";
    RunSQL(dm1->Query1,szSQL,true);
    while(!dm1->Query1->Eof)
    {
    	m_lstQuoteTaxID.Add(dm1->Query1->FieldByName("di_code")->AsString.c_str());
      lstQuoteTax->Items->Add(dm1->Query1->FieldByName("di_name")->AsString);

    	dm1->Query1->Next();
    }
	if((nSel=lstQuoteFact->ItemIndex)>=0 && nSel<m_lstQuoteFactID.GetSize())        //搜索所选厂商对应的税别，并显示之。
	{
//		if(lstQuoteTax->ItemIndex < 0)
//		{
			CString szSQL;
			szSQL.Format("select * from Manufactur where mf_code='%s'",m_lstQuoteFactID[nSel]);
			RunSQL(dm1->Query1,szSQL,true);
			if(!dm1->Query1->Eof)
			{
				strcpy(strTax,dm1->Query1->FieldByName("mf_taxtype")->AsString.c_str());
				if(strTax[0]=='\0')	return;
				for(i=0;i<m_lstQuoteTaxID.GetSize();i++)
				{
					if(m_lstQuoteTaxID[i]==strTax)
					{
						lstQuoteTax->ItemIndex=i;
            break;
					}
				}
//			}
		}
	}
*/
}
//---------------------------------------------------------------------------
void TPurchaseRoadForm::OnQuoteOK()
{
	int nSel,nRow;
	CString szSQL;
	char strInpDate[80],strID[80],strPD[80],strMN[80];
	TListItem *pItem;

	if(m_szActiveID.IsEmpty())	return;

	edtQuoteItem->Text=edtQuoteItem->Text.Trim();
	if(edtQuoteItem->Text.IsEmpty())
	{
		ShowMessage("请输入项次");
		if(edtQuoteItem->CanFocus())	edtQuoteItem->SetFocus();
		return;
	}
	sprintf(strPD,"%s%s",m_szActiveID,edtQuoteItem->Text.c_str());
	szSQL.Format("select * from PurchaseDetail where pd_code='%s'",strPD);
	RunSQL(dm1->Query1,szSQL,true);
	if(dm1->Query1->Eof)
	{
		ShowMessage("请购单中没有该项次");
		if(edtQuoteItem->CanFocus())	edtQuoteItem->SetFocus();
		return;
	}
	strcpy(strMN,dm1->Query1->FieldByName("pd_mncode")->AsString.c_str());
	if((nSel=lstQuoteFact->ItemIndex)<0 || nSel>=m_lstQuoteFactID.GetSize())
	{
		ShowMessage("请选择一个有效的厂商");
		return;
	}
	edtQuoteFactCard->Text=edtQuoteFactCard->Text.Trim();
	if((nSel=lstQuoteUnit->ItemIndex)<0 || nSel>=m_lstQuoteUnitID.GetSize())
	{
		ShowMessage("请选择一个有效的单位");
		return;
	}
	edtQuoteNum->Text=edtQuoteNum->Text.Trim();
	if(edtQuoteNum->Text.IsEmpty())
	{
		ShowMessage("请输入报价数量");
		if(edtQuoteNum->CanFocus())	edtQuoteNum->SetFocus();
		return;
	}
//	if(!StringIsInt(edtQuoteNum->Text.c_str()))
//	{
//		ShowMessage("请输入整数");
//		if(edtQuoteNum->CanFocus())	edtQuoteNum->SetFocus();
//		return;
//	}
	edtQuotePrice->Text=edtQuotePrice->Text.Trim();
	if(edtQuotePrice->Text.IsEmpty())
	{
		ShowMessage("请输入报价单价");
		if(edtQuotePrice->CanFocus())	edtQuotePrice->SetFocus();
		return;
	}
	if((nSel=lstQuoteRMB->ItemIndex)<0 || nSel>=m_lstQuoteRMBID.GetSize())
	{
		ShowMessage("请选择一个有效的币别");
		return;
	}
//------new 0802 保证税率合法---------------------------------------------------
        if((nSel=lstQuoteTax->ItemIndex)<0 || nSel>=m_lstQuotePayID.GetSize())                                         //new 0802
        {//税率非空
                ShowMessage("请选择税率");
                ShowMessage("若无可选项,说明该厂商尚未有相应税率资料，请与有关人员联系");
                return;
        }
//------------------------------------------------------------------------------
	edtQuoteDelDays->Text=edtQuoteDelDays->Text.Trim();
	if((nSel=lstQuotePay->ItemIndex)<0 || nSel>=m_lstQuotePayID.GetSize())
	{
		ShowMessage("请选择一个有效的付款方式");
		return;
	}
	edtQuoteInpDate->Text=edtQuoteInpDate->Text.Trim();
	if(!CheckDateEditor(edtQuoteInpDate))	return;
	Date2Dbdate(edtQuoteInpDate->Text.c_str(),strInpDate);

  if((nSel=lstQuoteDelivery->ItemIndex)<0 || nSel>=m_lstQuoteDeliveryID.GetSize())
  {
  	ShowMessage("请选择一个有效的交货方式");
    return;
  }

	if(m_enState==EN_STATE_NEW)
	{
		nSel=lstQuoteFact->ItemIndex;

		szSQL.Format("select * from CompareFactory where cf_apcode=%s and cf_mfcode=%s"
			,Str2DBString(strPD),Str2DBString(m_lstQuoteFactID[nSel]));
		RunSQL(dm1->Query1,szSQL,true);
		if(!dm1->Query1->Eof)
		{
			ShowMessage("数据库中已有该项数据");
			return;
		}

		szSQL="insert into CompareFactory (cf_apcode,cf_mfcode,cf_card,cf_quoteunit,"
//			"cf_quotenum,cf_quoteprice,cf_quotermb,cf_deliverday,cf_higgleprice,cf_pmcode,cf_ddcode,cf_tax,cf_quotedate,cf_higgledate"
			"cf_quotenum,cf_quoteprice,cf_quotermb,cf_deliverday,cf_higgleprice,cf_pmcode,cf_ddcode,cf_tax,cf_quotedate,cf_higgledate,cf_invoice"
			") values(";
		szSQL+=Str2DBString(strPD);
		szSQL+=",";	szSQL+=Str2DBString(m_lstQuoteFactID[nSel]);
		szSQL+=",";	szSQL+=Str2DBString(edtQuoteFactCard->Text.c_str());
		szSQL+=",";	szSQL+=Str2DBString(m_lstQuoteUnitID[lstQuoteUnit->ItemIndex]);
		szSQL+=",";	szSQL+=Text2DBFloat(edtQuoteNum->Text,2).c_str();
		if(strMN[0]=='E' && strMN[1]=='M')
    {
			szSQL+=",";	szSQL+=Text2DBFloat(edtQuotePrice->Text,6).c_str();
    }
		else
    {
			szSQL+=",";	szSQL+=Text2DBFloat(edtQuotePrice->Text,3).c_str();
    }
		szSQL+=",";	szSQL+=Str2DBString(m_lstQuoteRMBID[lstQuoteRMB->ItemIndex]);
		szSQL+=",";	szSQL+=Text2DBInt(edtQuoteDelDays->Text).c_str();
		szSQL+=",NULL";
		szSQL+=",";	szSQL+=Str2DBString(m_lstQuotePayID[lstQuotePay->ItemIndex]);
    szSQL+=",";	szSQL+=Str2DBString(m_lstQuoteDeliveryID[lstQuoteDelivery->ItemIndex]);
//		szSQL+=",";	szSQL+=Text2DBFloat(edtQuoteTax->Text,2).c_str();
		szSQL+=",NULL";	//新版本不要税率
		szSQL+=",";	szSQL+=Str2DBString(strInpDate);
		szSQL+=",NULL";
		szSQL+=",";	szSQL+=Str2DBString(lstQuoteTax->Text.c_str());
		szSQL+=")";
		if(!RunSQL(dm1->Query1,szSQL))	return;

		pItem=lstQuoteView->Items->Add();
		assert(pItem!=NULL);
		pItem->Caption=edtQuoteItem->Text;
		pItem->SubItems->Add(lstQuoteFact->Text);
		m_lstQuoteViewID.Add(m_lstQuoteFactID[nSel]);

		m_enState=EN_STATE_IDLE;
		ResetCtrl();
	}
	else if(m_enState==EN_STATE_EDIT)
	{
		if((pItem=lstQuoteView->Selected)==NULL)	return;
		if((nRow=lstQuoteView->Items->IndexOf(pItem))<0 || nRow>=m_lstQuoteViewID.GetSize())	return;
		strcpy(strID,m_lstQuoteViewID[nRow]);

		szSQL.Format("select * from CompareFactory where cf_apcode='%s' and cf_mfcode='%s'",strPD,strID);
		RunSQL(dm1->Query1,szSQL,true);
		if(dm1->Query1->Eof)
		{
			ShowMessage("数据库中没有该项数据");
			return;
		}

        	if((nSel=lstQuoteFact->ItemIndex)>=0 && nSel<m_lstQuoteFactID.GetSize())
                {
                        CString szSQL;
                	char strTax[80];
                        int i;
                        szSQL.Format("select * from Manufactur,DicInvoice where mf_taxtype=di_code and mf_code='%s'",m_lstQuoteFactID[nSel]);
                        RunSQL(dm1->Query4,szSQL,true);
                        if(dm1->Query4->Eof)                                   //厂商无税率(无主税率,则也必无副税率)
        		{
                                ShowMessage("相应厂商目前尚未有税率信息，不能修改税率，请与有关人员联系");
                                return;
                        }
                        else                                                    //厂商有税率
                        {
                                CString szSQLn;
                                szSQLn.Format("select * from Manufactur,DicInvoice where mf_taxtype2=di_code and mf_code='%s'",m_lstQuoteFactID[nSel]);
                                RunSQL(dm1->Query3,szSQLn,true);
                                if(lstQuoteTax->Text!=dm1->Query4->FieldByName("di_name")->AsString && lstQuoteTax->Text!=dm1->Query3->FieldByName("di_name")->AsString)
                                {
                                        ShowMessage("所选税率与厂商质料不匹配，请重选");        //主次税率均已考虑        
                                        return;
                                }
                        }

/*	        		strcpy(strTax,dm1->Query4->FieldByName("mf_taxtype")->AsString.c_str());
		        	if(strTax[0]=='\0')
                                {
                                        ShowMessage("相应厂商目前尚未有税率信息，不能修改税率，请与有关人员联系");
                                        return;
                                }
                                else
                                {//厂商必有税率

                                        ShowMessage(strTax);
                                        if(lstQuoteTax->Text!=strTax)
                                        {
                                                ShowMessage("所选税率与厂商质料不匹配，请重选");
                                                return;
                                        }
                                }
*/

                }

		szSQL="update CompareFactory set";
		szSQL+=" cf_card=";					szSQL+=Str2DBString(edtQuoteFactCard->Text.c_str());
		szSQL+=",cf_quoteunit=";		szSQL+=Str2DBString(m_lstQuoteUnitID[lstQuoteUnit->ItemIndex]);
		szSQL+=",cf_quotenum=";			szSQL+=Text2DBFloat(edtQuoteNum->Text,2).c_str();
		if(strMN[0]=='E' && strMN[1]=='M')
    {
			szSQL+=",cf_quoteprice=";		szSQL+=Text2DBFloat(edtQuotePrice->Text,6).c_str();
    }
		else
    {
			szSQL+=",cf_quoteprice=";		szSQL+=Text2DBFloat(edtQuotePrice->Text,3).c_str();
    }
		szSQL+=",cf_quotermb=";			szSQL+=Str2DBString(m_lstQuoteRMBID[lstQuoteRMB->ItemIndex]);
		szSQL+=",cf_deliverday=";		szSQL+=Text2DBInt(edtQuoteDelDays->Text).c_str();
		szSQL+=",cf_pmcode=";				szSQL+=Str2DBString(m_lstQuotePayID[lstQuotePay->ItemIndex]);
    szSQL+=",cf_ddcode=";				szSQL+=Str2DBString(m_lstQuoteDeliveryID[lstQuoteDelivery->ItemIndex]);
//		szSQL+=",cf_tax=";					szSQL+=Text2DBFloat(edtQuoteTax->Text,2).c_str();
		szSQL+=",cf_quotedate=";		szSQL+=Str2DBString(strInpDate);
		szSQL+=",cf_invoice=";			szSQL+=Str2DBString(lstQuoteTax->Text.c_str());
		szSQL+=" where cf_apcode=";	szSQL+=Str2DBString(strPD);
		szSQL+=" and cf_mfcode=";		szSQL+=Str2DBString(strID);
		if(!RunSQL(dm1->Query1,szSQL))	return;

		m_enState=EN_STATE_IDLE;
		ResetCtrl();
	}
}

void __fastcall TPurchaseRoadForm::lstQuoteViewSelectItem(TObject *Sender,TListItem *Item, bool Selected)
{
	TListItem *pItem;
	int i,nSel;
	CString szSQL;
	char strUnit[80],strPM[80],strFact[80],strDD[80],strMN[80],strTax[80];

	if(!Selected)	return;
	if((pItem=lstQuoteView->Selected)==NULL)	return;
	if((nSel=lstQuoteView->Items->IndexOf(pItem))<0 || nSel>=m_lstQuoteViewID.GetSize())	return;

	szSQL.Format("select * from CompareFactory,PurchaseDetail"
		" where cf_apcode=pd_code and cf_apcode='%s%s' and cf_mfcode='%s'",
		m_szActiveID,pItem->Caption.c_str(),m_lstQuoteViewID[nSel]);
	RunSQL(dm1->Query1,szSQL,true);
	if(dm1->Query1->Eof)
	{
		ShowMessage("没有该项数据");
		return;
	}
	strcpy(strMN,dm1->Query1->FieldByName("pd_mncode")->AsString.c_str());
	edtQuoteItem->Text=pItem->Caption;
	lstQuoteFact->Text=pItem->SubItems->Strings[0];
	strcpy(strFact,dm1->Query1->FieldByName("cf_mfcode")->AsString.c_str());
        for(i=0;i<m_lstQuoteFactID.GetSize();i++)
	{
		if(m_lstQuoteFactID[i]==strFact)
		{
			lstQuoteFact->ItemIndex=i;
			break;
		}
	}
	if(i==m_lstQuoteFactID.GetSize())	lstQuoteFact->ItemIndex=-1;


	edtQuoteFactCard->Text=dm1->Query1->FieldByName("cf_card")->AsString;
	strcpy(strUnit,dm1->Query1->FieldByName("cf_quoteunit")->AsString.c_str());
	for(i=0;i<m_lstQuoteUnitID.GetSize();i++)
	{
		if(m_lstQuoteUnitID[i]==strUnit)
		{
			lstQuoteUnit->ItemIndex=i;
			break;
		}
	}
	if(i==m_lstQuoteUnitID.GetSize())	lstQuoteUnit->ItemIndex=-1;
	edtQuoteNum->Text=FloatField2String(dm1->Query1->FieldByName("cf_quotenum"),2);

	if(strMN[0]=='E' && strMN[1]=='M')
		edtQuotePrice->Text=FloatField2String(dm1->Query1->FieldByName("cf_quoteprice"),6);
	else
		edtQuotePrice->Text=FloatField2String(dm1->Query1->FieldByName("cf_quoteprice"),3);
	for(i=0;i<m_lstQuoteRMBID.GetSize();i++)
	{
  	if(m_lstQuoteRMBID[i]==dm1->Query1->FieldByName("cf_quotermb")->AsString.c_str())
		{
    	lstQuoteRMB->ItemIndex=i;
      break;
    }
  }
  if(i==m_lstQuoteRMBID.GetSize())	lstQuoteRMB->ItemIndex=-1;

	edtQuoteDelDays->Text=IntField2Text(dm1->Query1->FieldByName("cf_deliverday"));
	strcpy(strPM,dm1->Query1->FieldByName("cf_pmcode")->AsString.c_str());
	for(i=0;i<m_lstQuotePayID.GetSize();i++)
	{
		if(m_lstQuotePayID[i]==strPM)
		{
			lstQuotePay->ItemIndex=i;
			break;
		}
	}
	if(i==m_lstQuotePayID.GetSize())	lstQuotePay->ItemIndex=-1;
	edtQuoteInpDate->Text=DateField2Text(dm1->Query1->FieldByName("cf_quotedate"));
//------税率--------------------------------------------------------------------

//判断cf_invoice是否为DicInvoice中的税率(是否为合法税率)。
	CString szSQLTemp;
        szSQLTemp.Format("select * from DicInvoice where di_name='%s'",dm1->Query1->FieldByName("cf_invoice")->AsString.c_str());
        RunSQL(dm1->Query3,szSQLTemp,true);

  if(!dm1->Query1->FieldByName("cf_invoice")->IsNull && !dm1->Query3->Eof)
  {//发票税率是後来加的，为了与之前的税率兼容，而两者共存，如果有发票，取发票数据
  	OnFactListExit(lstQuoteFact,m_lstQuoteFactID);
//        int nSel,i;
	char strTax[80],strTax2[80],strTemp[256];
		lstQuoteTax->Items->Clear();
		m_lstQuoteTaxIDnew.RemoveAll();

	if((nSel=lstQuoteFact->ItemIndex)>=0 && nSel<m_lstQuoteFactID.GetSize())        //添加厂商档里的税别
        {
                CString szSQL;
		szSQL.Format("select * from Manufactur,DicInvoice where mf_taxtype=di_code and mf_code='%s'",m_lstQuoteFactID[nSel]);
                RunSQL(dm1->Query4,szSQL,true);
                if(!dm1->Query4->Eof)                                           //厂商有税率(主税率)
                {
                        m_lstQuoteTaxIDnew.Add(dm1->Query4->FieldByName("di_code")->AsString.c_str());
                        lstQuoteTax->Items->Add(dm1->Query4->FieldByName("di_name")->AsString);
                        dm1->Query4->Next();
                }

                CString szSQLn;
		szSQLn.Format("select * from Manufactur,DicInvoice where mf_taxtype2=di_code and mf_code='%s'",m_lstQuoteFactID[nSel]);
                RunSQL(dm1->Query4,szSQLn,true);
                if(!dm1->Query4->Eof)
                {
                        m_lstQuoteTaxIDnew.Add(dm1->Query4->FieldByName("di_code")->AsString.c_str());             //将厂商目前的有效税率(副税率)添加进下拉列表
                        lstQuoteTax->Items->Add(dm1->Query4->FieldByName("di_name")->AsString);
                        dm1->Query4->Next();
                }

                else if(dm1->Query4->FieldByName("mf_taxtype")->IsNull)         //厂商无税率                                   //有合法税率纪录，但厂商本身无税率。
                {
                        m_lstQuoteTaxIDnew.Add(dm1->Query1->FieldByName("cf_invoice")->AsString.c_str());
                        lstQuoteTax->Items->Add(dm1->Query1->FieldByName("cf_invoice")->AsString);
                }
        }
	if((nSel=lstQuoteFact->ItemIndex)>=0 && nSel<m_lstQuoteFactID.GetSize())
	{
			CString szSQL;
			szSQL.Format("select * from Manufactur where mf_code='%s'",m_lstQuoteFactID[nSel]);
			RunSQL(dm1->Query4,szSQL,true);
			if(!dm1->Query4->Eof)
			{
                                if(!dm1->Query4->FieldByName("mf_taxtype")->IsNull)             //厂商有税率,则下拉列表必有主税率，副税率若有也应该在 
                                {       //strTax为税率编号
				        strcpy(strTax,dm1->Query4->FieldByName("mf_taxtype")->AsString.c_str());
				        strcpy(strTax2,dm1->Query4->FieldByName("mf_taxtype2")->AsString.c_str());                                               //厂商有税率，则下面的自动选择只比较其代号
        				if(strTax[0]=='\0')	return;
	        			for(i=0;i<m_lstQuoteTaxIDnew.GetSize();i++)
		        		{
			        		if(m_lstQuoteTaxIDnew[i]==strTax)
				        	{
					        	lstQuoteTax->ItemIndex=i;
                                                        break;
        					}
	        			}
                                        if(i==m_lstQuoteTaxIDnew.GetSize())     //主税率对不上，转而搜索副税率
                                        {
        	        			if(strTax2[0]=='\0')	return;
	                			for(i=0;i<m_lstQuoteTaxIDnew.GetSize();i++)
        		        		{
			        	        	if(m_lstQuoteTaxIDnew[i]==strTax2)
				                	{
			        		        	lstQuoteTax->ItemIndex=i;
                                                                break;
                					}
        	        			}
                                        }
//                                        if(i==m_lstQuoteTaxIDnew.GetSize())

                                }
                                else                                                            //厂商无税率,说明CompareFactory中的合法的cf_invoice亏空了。
                                {//strTax为具体的税率
				        strcpy(strTax,dm1->Query1->FieldByName("cf_invoice")->AsString.c_str());        //厂商无税率，则只比较名字,因为上面添加时添加名字
               				if(strTax[0]=='\0')	return;
	        			for(i=0;i<m_lstQuoteTaxIDnew.GetSize();i++)
		        		{
			        		if(m_lstQuoteTaxIDnew[i]==strTax)
				        	{
					        	lstQuoteTax->ItemIndex=i;
                                                        break;
        					}
	        			}
                                }
               	        }
	}
  }
  else if(!dm1->Query1->FieldByName("cf_invoice")->IsNull && dm1->Query3->Eof)  //有cf_invoice，但cf_invoice 为非法税率
  {
  	OnFactListExit(lstQuoteFact,m_lstQuoteFactID);
//        int nSel,i;
	char strTax[80],strTemp[256];
		lstQuoteTax->Items->Clear();
		m_lstQuoteTaxIDnew.RemoveAll();
	if((nSel=lstQuoteFact->ItemIndex)>=0 && nSel<m_lstQuoteFactID.GetSize())        //添加厂商档里的税别
        {
                CString szSQL;
		szSQL.Format("select * from Manufactur,DicInvoice where mf_taxtype=di_code and mf_code='%s'",m_lstQuoteFactID[nSel]);
                RunSQL(dm1->Query4,szSQL,true);
                if(!dm1->Query4->Eof)                                           //若厂商本身有税率，则添加进下拉列表里,此举针对现状!
                {
                        m_lstQuoteTaxIDnew.Add(dm1->Query4->FieldByName("di_code")->AsString.c_str());
                        lstQuoteTax->Items->Add(dm1->Query4->FieldByName("di_name")->AsString);
                        dm1->Query4->Next();
                }

                CString szSQLn;
		szSQLn.Format("select * from Manufactur,DicInvoice where mf_taxtype2=di_code and mf_code='%s'",m_lstQuoteFactID[nSel]);
                RunSQL(dm1->Query4,szSQLn,true);
                if(!dm1->Query4->Eof)
                {
                        m_lstQuoteTaxIDnew.Add(dm1->Query4->FieldByName("di_code")->AsString.c_str());             //只将厂商目前的有效税率(副税率)添加进下拉列表
                        lstQuoteTax->Items->Add(dm1->Query4->FieldByName("di_name")->AsString);
                        dm1->Query4->Next();
                }                
                                                                                //将较早的税率也添加在下拉列表里
                        m_lstQuoteTaxIDnew.Add(dm1->Query1->FieldByName("cf_invoice")->AsString.c_str());
                        lstQuoteTax->Items->Add(dm1->Query1->FieldByName("cf_invoice")->AsString.c_str());       //增加最早的
        }

				strcpy(strTax,dm1->Query1->FieldByName("cf_invoice")->AsString.c_str());
				if(strTax[0]=='\0')	return;
				for(i=0;i<m_lstQuoteTaxIDnew.GetSize();i++)
				{
					if(m_lstQuoteTaxIDnew[i]==strTax)
					{
						lstQuoteTax->ItemIndex=i;       //若选中，必为非法法的cf_invoice
                                                break;                          //用於显示原有税率
					}
				}
  }
  else if(dm1->Query1->FieldByName("cf_invoice")->IsNull)
  {
  	OnFactListExit(lstQuoteFact,m_lstQuoteFactID);
//        int nSel,i;
	char strTax[80],strTemp[256];
		lstQuoteTax->Items->Clear();
		m_lstQuoteTaxIDnew.RemoveAll();
	if((nSel=lstQuoteFact->ItemIndex)>=0 && nSel<m_lstQuoteFactID.GetSize())        //添加厂商档里的税别
        {
                CString szSQL;
		szSQL.Format("select * from Manufactur,DicInvoice where mf_taxtype=di_code and mf_code='%s'",m_lstQuoteFactID[nSel]);
                RunSQL(dm1->Query4,szSQL,true);
                if(!dm1->Query4->Eof)
                {
                        m_lstQuoteTaxIDnew.Add(dm1->Query4->FieldByName("di_code")->AsString.c_str());
                        lstQuoteTax->Items->Add(dm1->Query4->FieldByName("di_name")->AsString);
                        dm1->Query4->Next();
                }

                CString szSQLn;
		szSQLn.Format("select * from Manufactur,DicInvoice where mf_taxtype2=di_code and mf_code='%s'",m_lstQuoteFactID[nSel]);
                RunSQL(dm1->Query4,szSQLn,true);
                if(!dm1->Query4->Eof)
                {
                        m_lstQuoteTaxIDnew.Add(dm1->Query4->FieldByName("di_code")->AsString.c_str());             //只将厂商目前的有效税率(副税率)添加进下拉列表
                        lstQuoteTax->Items->Add(dm1->Query4->FieldByName("di_name")->AsString);
                        dm1->Query4->Next();
                }
                                                                                        //将最早的税率也添加在下拉列表里
                        m_lstQuoteTaxIDnew.Add(dm1->Query1->FieldByName("cf_tax")->AsString.c_str());
                        lstQuoteTax->Items->Add(dm1->Query1->FieldByName("cf_tax")->AsString.c_str());       //增加最早的
        }

				strcpy(strTax,dm1->Query1->FieldByName("cf_tax")->AsString.c_str());
				if(strTax[0]=='\0')	return;
				for(i=0;i<m_lstQuoteTaxIDnew.GetSize();i++)
				{
					if(m_lstQuoteTaxIDnew[i]==strTax)
					{
						lstQuoteTax->ItemIndex=i;               //选中的必为最早的税率
                                                break;
					}
				}
  }

//------------------------------------------------------------------------------        
/*  if(!dm1->Query1->FieldByName("cf_invoice")->IsNull)
  { //发票税率是後来加的，为了与之前的税率兼容，而两者共存，如果有发票，取发票数据
		lstQuoteTax->Text=dm1->Query1->FieldByName("cf_invoice")->AsString;
  }
  else
  {
//		edtQuoteTax->Text=FloatField2String(dm1->Query1->FieldByName("cf_tax"),2);
		lstQuoteTax->Text=FloatField2String(dm1->Query1->FieldByName("cf_tax"),2);
  }
*/
  strcpy(strDD,dm1->Query1->FieldByName("cf_ddcode")->AsString.c_str());
  for(i=0;i<m_lstQuoteDeliveryID.GetSize();i++)
  {
  	if(m_lstQuoteDeliveryID[i]==strDD)
    {
    	lstQuoteDelivery->ItemIndex=i;
      break;
    }
  }
  if(i==m_lstQuoteDeliveryID.GetSize())	lstQuoteDelivery->ItemIndex=-1;

	FetchQuotePurchase(pItem->Caption.c_str());
	ResetCtrl();
}
//---------------------------------------------------------------------------

void __fastcall TPurchaseRoadForm::lstQuoteViewClick(TObject *Sender)
{
	if(lstQuoteView->Selected==NULL)	ResetCtrl();
}
//---------------------------------------------------------------------------

void TPurchaseRoadForm::FetchQuotePurchase(LPCSTR lpszItem)
{
	CString szSQL;
	if(m_szActiveID.IsEmpty())	return;

	szSQL.Format("select * from PurchaseDetail,DicUnits where"
		" pd_ducode=du_code and pd_code='%s%s'",m_szActiveID,lpszItem);
	RunSQL(dm1->Query1,szSQL,true);
	if(!dm1->Query1->Eof)
	{
		edtQuoteReqUnit->Text=dm1->Query1->FieldByName("du_name")->AsString;
//		edtQuoteReqNum->Text=FloatField2String(dm1->Query1->FieldByName("pd_count"),1);
		if(dm1->Query1->FieldByName("pd_count")->IsNull)
			edtQuoteReqNum->Text="";
    else
    	edtQuoteReqNum->Text=FloatToStr(dm1->Query1->FieldByName("pd_count")->AsFloat);
	}
	else
	{
		edtQuoteReqUnit->Text="";
		edtQuoteReqNum->Text="";
	}
}

void __fastcall TPurchaseRoadForm::edtQuoteItemExit(TObject *Sender)
{
	FetchQuotePurchase(edtQuoteItem->Text.c_str());
}
//---------------------------------------------------------------------------

void __fastcall TPurchaseRoadForm::ctlHiggleShow(TObject *Sender)
{
	CString szSQL;
	BASE2COLDATA rwData;

	if(!m_bHiggleInitialed)
	{
		m_bHiggleInitialed=true;
		edtHigglePrice->Text="";
		edtHiggleDate	->Text="";

		szSQL="select * from diccurrency order by dc_code";
		RunSQL(dm1->Query1,szSQL,true);
		while(!dm1->Query1->Eof)
		{
			strcpy(rwData.strCode,dm1->Query1->FieldByName("dc_code")->AsString.c_str());
			strcpy(rwData.strName,dm1->Query1->FieldByName("dc_name")->AsString.c_str());
			m_lstHiggleRMB.Add(rwData);
			dm1->Query1->Next();
		}
	}
	m_enRegion=EN_REG_HIGGLE;
	if(!m_szActiveID.IsEmpty())	OnQueryHiggle(m_szActiveID);
	m_enState=EN_STATE_IDLE;
	ResetCtrl();
}
//---------------------------------------------------------------------------

void __fastcall TPurchaseRoadForm::lstHiggleViewClick(TObject *Sender)
{
	if(lstHiggleView->Selected==NULL)	ResetCtrl();
}
//---------------------------------------------------------------------------

void __fastcall TPurchaseRoadForm::lstHiggleViewSelectItem(TObject *Sender,TListItem *Item, bool Selected)
{
	TListItem *pItem;
	int i,nSel;
	CString szSQL;
	char strUnit[80],strPM[80],strFact[80],strMN[80];

	if(!Selected)	return;
	if((pItem=lstHiggleView->Selected)==NULL)	return;
	if((nSel=lstHiggleView->Items->IndexOf(pItem))<0 || nSel>=m_lstHiggleViewID.GetSize())	return;

	szSQL.Format("select * from CompareFactory,PurchaseDetail"
		" where cf_apcode=pd_code and cf_apcode='%s%s' and cf_mfcode='%s'",
		m_szActiveID,pItem->Caption.c_str(),m_lstHiggleViewID[nSel]);
	RunSQL(dm1->Query1,szSQL,true);
	if(dm1->Query1->Eof)
	{
		ShowMessage("没有该项数据");
		return;
	}
	strcpy(strMN,dm1->Query1->FieldByName("pd_mncode")->AsString.c_str());
	if(strMN[0]=='E' && strMN[1]=='M')
		edtHigglePrice->Text=FloatField2String(dm1->Query1->FieldByName("cf_higgleprice"),6);
	else
		edtHigglePrice->Text=FloatField2String(dm1->Query1->FieldByName("cf_higgleprice"),3);
	edtHiggleDate->Text=DateField2Text(dm1->Query1->FieldByName("cf_higgledate"));
	for(i=0;i<m_lstHiggleRMB.GetSize();i++)
	{
		if(dm1->Query1->FieldByName("cf_quotermb")->AsString==m_lstHiggleRMB[i].strCode)
		{
			edtHiggleRMB->Text=m_lstHiggleRMB[i].strName;
			break;
		}
	}
	if(i==m_lstHiggleRMB.GetSize())	edtHiggleRMB->Text="";

	ResetCtrl();
}
//---------------------------------------------------------------------------

void TPurchaseRoadForm::OnHiggleOK()
{
	int nSel,nRow;
	CString szSQL;
	char strDate[80],strID[80],strPD[80],strMN[80];
	TListItem *pItem;

	if(m_szActiveID.IsEmpty())	return;
	if((pItem=lstHiggleView->Selected)==NULL)	return;
	if((nSel=lstHiggleView->Items->IndexOf(pItem))<0 || nSel>=m_lstHiggleViewID.GetSize())	return;

	sprintf(strPD,"%s%s",m_szActiveID,pItem->Caption.c_str());
	szSQL.Format("select * from PurchaseDetail where pd_code='%s'",strPD);
	RunSQL(dm1->Query1,szSQL,true);
	if(dm1->Query1->Eof)
	{
		ShowMessage("请购单中没有该项次");
		return;
	}
	strcpy(strMN,dm1->Query1->FieldByName("pd_mncode")->AsString.c_str());

	edtHigglePrice->Text=edtHigglePrice->Text.Trim();
	if(edtHigglePrice->Text.IsEmpty())
	{
		ShowMessage("请输入议价单价");
		if(edtHigglePrice->CanFocus())	edtHigglePrice->SetFocus();
		return;
	}
	edtHiggleDate->Text=edtHiggleDate->Text.Trim();
	if(!CheckDateEditor(edtHiggleDate))	return;
	Date2Dbdate(edtHiggleDate->Text.c_str(),strDate);

	if(m_enState==EN_STATE_EDIT)
	{
		if((pItem=lstHiggleView->Selected)==NULL)	return;
		if((nRow=lstHiggleView->Items->IndexOf(pItem))<0 || nRow>=m_lstHiggleViewID.GetSize())	return;
		strcpy(strID,m_lstHiggleViewID[nRow]);

		szSQL.Format("select * from CompareFactory where cf_apcode='%s' and cf_mfcode='%s'",strPD,strID);
		RunSQL(dm1->Query1,szSQL,true);
		if(dm1->Query1->Eof)
		{
			ShowMessage("数据库中没有该项数据");
			return;
		}

		szSQL="update CompareFactory set";
		if(strMN[0]=='E' && strMN[1]=='M')
    {
			szSQL+=" cf_higgleprice=";	szSQL+=Text2DBFloat(edtHigglePrice->Text,6).c_str();
    }
		else
    {
			szSQL+=" cf_higgleprice=";	szSQL+=Text2DBFloat(edtHigglePrice->Text,3).c_str();
    }
		szSQL+=",cf_higgledate=";		szSQL+=Str2DBString(strDate);
		szSQL+=" where cf_apcode=";	szSQL+=Str2DBString(strPD);
		szSQL+=" and cf_mfcode=";		szSQL+=Str2DBString(strID);
		if(!RunSQL(dm1->Query1,szSQL))	return;

		m_enState=EN_STATE_IDLE;
		ResetCtrl();
	}
}

#include "PrnSpeerFactory.h"
void __fastcall TPurchaseRoadForm::btnSpeerPrnClick(TObject *Sender)
{
	CString szSQL;
  char strDate[80],strSD[80];
  int nYear,nMonth,nDay;
	if(m_szActiveID.IsEmpty())	return;

  GetSysDate(nYear,nMonth,nDay,false);
  sprintf(strDate,"%04d%02d%02d",nYear,nMonth,nDay);
  edtSpeerPrnDate->Text=strDate;

	TPrnSpeerFactoryForm *pPrn;
  pPrn=new TPrnSpeerFactoryForm(this);
  assert(pPrn!=NULL);

	szSQL.Format("select * from AskPurchase,GoodsAddr where ga_code=ap_gacode"
		" and ap_code='%s'",m_szActiveID);
	RunSQL(dm1->Query1,szSQL,true);
//	if(!dm1->Query1->Eof)
//		pPrn->txtGAName->Caption = dm1->Query1->FieldByName("ga_area")->AsString
//			+ dm1->Query1->FieldByName("ga_name")->AsString;
//	else
//		pPrn->txtGAName->Caption="";

	szSQL.Format("select * from AskPurchase,StockHandleman"
		" where sh_code=ap_shcode and ap_code='%s'",m_szActiveID);
	RunSQL(dm1->Query1,szSQL,true);
	if(!dm1->Query1->Eof)
	{
		pPrn->txtSHName->Caption=dm1->Query1->FieldByName("sh_name")->AsString;
		pPrn->txtSHTel->Caption=dm1->Query1->FieldByName("sh_tel")->AsString;
		strcpy(strSD,dm1->Query1->FieldByName("sh_sdcode")->AsString.c_str());
		if(strSD[0]!='\0')
  	{
			szSQL.Format("select * from StockDepart where sd_code='%s'",strSD);
      RunSQL(dm1->Query1,szSQL,true);
      if(!dm1->Query1->Eof)
    	{
      	pPrn->txtSDAddr->Caption=dm1->Query1->FieldByName("sd_address")->AsString;
        pPrn->txtSDTel->Caption=dm1->Query1->FieldByName("sd_tel")->AsString;
      }
    }
	}
	else
	{
		pPrn->txtSHName->Caption="";
		pPrn->txtSHTel->Caption="";
	}

  szSQL.Format("select * from QuoteFactory where qf_apcode='%s'",m_szActiveID);
  RunSQL(dm1->Query1,szSQL,true);
  pPrn->EndDate->Caption=DateField2Text(dm1->Query1->FieldByName("qf_enddate"));

//	szSQL.Format("select * from"
//		" PurchaseDetail,DicUnits,materialno,AskPurchase,QuoteFactory,Manufactur"
//		 " where ap_code=substring(pd_code,1,7)"
//		" and qf_apcode=ap_code"
//		" and qf_mfcode=mf_code"
//		" and pd_ducode=du_code and pd_mncode*=mn_code"
//		" and ap_code='%s'",m_szActiveID);
//	szSQL+=" order by mf_code,pd_code";
	szSQL.Format("select * from"
		" PurchaseDetail,DicUnits,materialno,AskPurchase"
		 " where ap_code=substring(pd_code,1,7)"
		" and pd_ducode=du_code and pd_mncode*=mn_code"
		" and ap_code='%s'",m_szActiveID);
	szSQL+=" order by pd_code";
	if(!OpenQuery(dm1->sqlPrint,szSQL))	return;

  sprintf(strDate,"%04d-%02d-%02d",nYear,nMonth,nDay);
  pPrn->PrnDate->Caption=strDate;

  pPrn->PrnView->PreviewModal();
  delete pPrn;

  szSQL.Format("update QuoteFactory set qf_printdate=getdate()"
  	" where qf_apcode='%s'",m_szActiveID);
  RunSQL(dm1->Query1,szSQL);
}
//---------------------------------------------------------------------------

void __fastcall TPurchaseRoadForm::btnSpeerFactInfClick(TObject *Sender)
{
	int nSel;

  if((nSel=lstSpeerView->ItemIndex)<0 ||nSel>=m_lstSpeerViewID.GetSize())	return;

	int nRight=GetOperatorRight(operatorcode.c_str(),"IDM_FACTORY");
	FactoryInput(m_lstSpeerViewID[nSel],nRight);
}
//---------------------------------------------------------------------------

void TPurchaseRoadForm::EmptyShow()
{
	edtShowRem	->Text="";
	edtShowItem	->Text="";
	lstShowFact	->Text="";
	edtShowDate	->Text="";
  edtValidDate->Text="";
	edtShowNum	->Text="";
}

void TPurchaseRoadForm::InitShowFactory()
{
	CString szSQL;

	if(!m_szActiveID.IsEmpty())
	{
		m_lstShowFactID.RemoveAll();
		lstShowFact->Items->Clear();

		szSQL.Format("select distinct mf_code,mf_shortname from CompareFactory,Manufactur"
			" where cf_mfcode=mf_code"
			" and cf_apcode like '%s_'"
			" order by mf_code",m_szActiveID);
		RunSQL(dm1->Query1,szSQL,true);
		while(!dm1->Query1->Eof)
		{
			m_lstShowFactID.Add(dm1->Query1->FieldByName("mf_code")->AsString.c_str());
			lstShowFact->Items->Add(dm1->Query1->FieldByName("mf_shortname")->AsString);

			dm1->Query1->Next();
		}
	}
}

void __fastcall TPurchaseRoadForm::ctlShowShow(TObject *Sender)
{
	CString szSQL;

	InitShowFactory();

	if(!m_bShowInitialed)
	{
		EmptyShow();
	}
	m_bShowInitialed=true;

	m_enRegion=EN_REG_SHOW;
	if(!m_szActiveID.IsEmpty())	OnQueryShow(m_szActiveID);
	m_enState=EN_STATE_IDLE;
	ResetCtrl();
}
//---------------------------------------------------------------------------

void TPurchaseRoadForm::OnQueryShow(LPCSTR lpszID)
{
	CString szSQL;
	TListItem *pItem;
	char strID[80];

	lstShowView->Items->Clear();
	m_lstShowViewID.RemoveAll();
	if(lpszID[0]=='\0')	return;

	szSQL.Format("select * from DecideFactory,Manufactur"
		" where df_mfplan*=mf_code"
		" and df_apcode like '%s_' order by df_apcode,df_mfplan",lpszID);
	RunSQL(dm1->Query1,szSQL,true);
	while(!dm1->Query1->Eof)
	{
		strcpy(strID,dm1->Query1->FieldByName("df_apcode")->AsString.c_str());
		if(strID[0]=='\0')	return;

		pItem=lstShowView->Items->Add();
		assert(pItem!=NULL);
		pItem->Caption =  strID+strlen(strID)-1;

		m_lstShowViewID.Add(dm1->Query1->FieldByName("mf_code")->AsString.c_str());
		pItem->SubItems->Add(dm1->Query1->FieldByName("mf_shortname")->AsString);
		pItem->SubItems->Add(DateField2Text(dm1->Query1->FieldByName("df_plandate")));

		dm1->Query1->Next();
	}
	m_szActiveID=lpszID;

	InitShowFactory();
}


void __fastcall TPurchaseRoadForm::lstShowFactExit(TObject *Sender)
{
	OnFactListExit(lstShowFact,m_lstShowFactID);
  if(!edtShowNum->Text.IsEmpty())	return;
	if(m_szActiveID.IsEmpty())	return;
  if(edtShowItem->Text.IsEmpty())	return;
  int nSel;
  CString szSQL;

  if((nSel=lstShowFact->ItemIndex)<0 || nSel>=m_lstShowFactID.GetSize())	return;
  szSQL.Format("select * from CompareFactory where cf_apcode='%s%s' and cf_mfcode='%s'",
    m_szActiveID,edtShowItem->Text.c_str(),m_lstShowFactID[nSel]);
  RunSQL(dm1->Query1,szSQL,true);
  if(!dm1->Query1->Eof)
	{
  	edtShowNum->Text=dm1->Query1->FieldByName("cf_quotenum")->AsString;
  }
}
//---------------------------------------------------------------------------

void TPurchaseRoadForm::OnShowOK()
{
	int nSel,nRow;
	CString szSQL;
	char strDate[80],strID[80],strPD[80],strValidDate[80];
	TListItem *pItem;

	if(m_szActiveID.IsEmpty())	return;

	edtShowItem->Text=edtShowItem->Text.Trim();
	if(edtShowItem->Text.IsEmpty())
	{
		ShowMessage("请输入项次");
		if(edtShowItem->CanFocus())	edtShowItem->SetFocus();
		return;
	}
	sprintf(strPD,"%s%s",m_szActiveID,edtShowItem->Text.c_str());
	szSQL.Format("select * from PurchaseDetail where pd_code='%s'",strPD);
	RunSQL(dm1->Query1,szSQL,true);
	if(dm1->Query1->Eof)
	{
		ShowMessage("请购单中没有该项次");
		if(edtShowItem->CanFocus())	edtShowItem->SetFocus();
		return;
	}
	if((nSel=lstShowFact->ItemIndex)<0 || nSel>=m_lstShowFactID.GetSize())
	{
		ShowMessage("请选择一个有效的厂商");
		return;
	}
	edtShowDate->Text=edtShowDate->Text.Trim();
	if(!CheckDateEditor(edtShowDate))	return;
	Date2Dbdate(edtShowDate->Text.c_str(),strDate);
  if(!CheckDateEditor(edtValidDate))	return;
	Date2Dbdate(edtValidDate->Text.c_str(),strValidDate);

	if(m_enState==EN_STATE_NEW)
	{
		nSel=lstShowFact->ItemIndex;

		szSQL.Format("select * from DecideFactory where df_apcode=%s and df_mfplan=%s and df_plandate=%s"
			,Str2DBString(strPD),Str2DBString(m_lstShowFactID[nSel]),Str2DBString(strDate));
		RunSQL(dm1->Query1,szSQL,true);
		if(!dm1->Query1->Eof)
		{
			ShowMessage("数据库中已有该项次的数据");
			return;
		}

		szSQL="insert into DecideFactory (df_apcode,df_mfplan,df_planrem,df_plandate,df_mfdecide,df_decidedate,"
			"df_count,df_unit,df_price,df_validdate,df_pricert"
			") values(";
		szSQL+=Str2DBString(strPD);
		szSQL+=",";	szSQL+=Str2DBString(m_lstShowFactID[nSel]);
		szSQL+=",";	szSQL+=Str2DBString(edtShowRem->Text.c_str());
		szSQL+=",";	szSQL+=Str2DBString(strDate);
		szSQL+=",NULL";	
		szSQL+=",NULL";                                                 //df_decidedate是缺省的
		szSQL+=",";	szSQL+=Float2DBString(atof(edtShowNum->Text.c_str()),2);
		szSQL+=",NULL";
		szSQL+=",NULL";
    szSQL+=",";	szSQL+=Str2DBString(strValidDate);
    szSQL+=",";	szSQL+=Str2DBString(lstPriceRT->Text.c_str());
		szSQL+=")";
		if(!RunSQL(dm1->Query1,szSQL))	return;

		pItem=lstShowView->Items->Add();
		assert(pItem!=NULL);
		pItem->Caption=edtShowItem->Text;
		pItem->SubItems->Add(lstShowFact->Text);
		pItem->SubItems->Add(strDate);
		m_lstShowViewID.Add(m_lstShowFactID[nSel]);

		m_enState=EN_STATE_IDLE;
		ResetCtrl();
	}
	else if(m_enState==EN_STATE_EDIT)
	{
		if((pItem=lstShowView->Selected)==NULL)	return;
		if((nRow=lstShowView->Items->IndexOf(pItem))<0 || nRow>=m_lstShowViewID.GetSize())	return;
		strcpy(strID,m_lstShowViewID[nRow]);

		szSQL.Format("select * from DecideFactory where df_apcode='%s' and df_mfplan='%s' and df_plandate=%s"
			,strPD,strID,Str2DBString(strDate));
		RunSQL(dm1->Query1,szSQL,true);
		if(dm1->Query1->Eof)
		{
			ShowMessage("数据库中没有该项数据");
			return;
		}

		szSQL="update DecideFactory set";
		szSQL+=" df_mfplan=";				szSQL+=Str2DBString(m_lstShowFactID[nSel]);
		szSQL+=",df_planrem=";			szSQL+=Str2DBString(edtShowRem->Text.c_str());
		szSQL+=",df_plandate=";			szSQL+=Str2DBString(strDate);
		szSQL+=",df_count=";				szSQL+=Float2DBString(atof(edtShowNum->Text.c_str()),2);
    szSQL+=",df_validdate=";		szSQL+=Str2DBString(strValidDate);
    szSQL+=",df_pricert=";			szSQL+=Str2DBString(lstPriceRT->Text.c_str());
		szSQL+=" where df_apcode=";	szSQL+=Str2DBString(strPD);
		szSQL+=" and df_mfplan=";		szSQL+=Str2DBString(strID);
		szSQL+=" and df_plandate=";	szSQL+=Str2DBString(strDate);
		if(!RunSQL(dm1->Query1,szSQL))	return;

		pItem->SubItems->Strings[0]=lstShowFact->Text;
		m_lstShowViewID[nRow]=(LPCSTR)m_lstShowFactID[nSel];

		m_enState=EN_STATE_IDLE;
		ResetCtrl();
	}
}


void __fastcall TPurchaseRoadForm::lstShowViewClick(TObject *Sender)
{
	if(lstShowView->Selected==NULL)	ResetCtrl();
}
//---------------------------------------------------------------------------

void __fastcall TPurchaseRoadForm::lstShowViewSelectItem(TObject *Sender,
      TListItem *Item, bool Selected)
{
	TListItem *pItem;
	int i,nSel;
	CString szSQL;
	char strUnit[80],strPM[80],strFact[80],strDate[80],strTemp[256];

	if(!Selected)	return;
	if((pItem=lstShowView->Selected)==NULL)	return;
	if((nSel=lstShowView->Items->IndexOf(pItem))<0 || nSel>=m_lstShowViewID.GetSize())	return;
  strcpy(strTemp,pItem->SubItems->Strings[1].c_str());
	if(strlen(strTemp)!=8)	return;
	Date2Dbdate(strTemp,strDate);

	szSQL.Format("select * from DecideFactory where df_apcode='%s%s' and df_mfplan='%s' and df_plandate=%s",
		m_szActiveID,pItem->Caption.c_str(),m_lstShowViewID[nSel],Str2DBString(strDate));
	RunSQL(dm1->Query1,szSQL,true);
	if(dm1->Query1->Eof)
	{
		ShowMessage("该项数据有误");
//		return;
	}
	edtShowItem->Text=pItem->Caption;
	lstShowFact->ItemIndex=lstShowFact->Items->IndexOf(pItem->SubItems->Strings[0]);
	edtShowDate->Text=DateField2Text(dm1->Query1->FieldByName("df_plandate"));
  edtShowRem->Text=dm1->Query1->FieldByName("df_planrem")->AsString;
  edtValidDate->Text=DateField2Text(dm1->Query1->FieldByName("df_validdate"));
	edtShowNum->Text=FloatField2String(dm1->Query1->FieldByName("df_count"),2);
  lstPriceRT->Text=dm1->Query1->FieldByName("df_pricert")->AsString;
	ResetCtrl();
}
//---------------------------------------------------------------------------

void TPurchaseRoadForm::OnShowMove()
{
	int nSel;
	CString szSQL;
	TListItem *pItem;
  char strID[80],strDate[80];

	if(m_szActiveID.IsEmpty())	return;
	if((pItem=lstShowView->Selected)==NULL)	return;
	if((nSel=lstShowView->Items->IndexOf(pItem))<0 || nSel>=m_lstShowViewID.GetSize())	return;
	if(edtShowDate->Text.Length()!=8)	return;
	Date2Dbdate(edtShowDate->Text.c_str(),strDate);

	if(Application->MessageBox("真要删除选定的数据吗","警告",MB_YESNOCANCEL | MB_ICONQUESTION | MB_DEFBUTTON2)!=IDYES)	return;

  sprintf(strID,"%s%s",m_szActiveID,pItem->Caption.c_str());
	szSQL="delete DecideFactory";
	szSQL+=" where df_apcode=";	szSQL+=Str2DBString(strID);
	szSQL+=" and df_mfplan=";		szSQL+=Str2DBString(m_lstShowViewID[nSel]);
	szSQL+=" and df_plandate=";	szSQL+=Str2DBString(strDate);
	if(!RunSQL(dm1->Query1,szSQL))	return;

	lstShowView->Items->Delete(nSel);
	m_lstShowViewID.RemoveAt(nSel);

	m_enState=EN_STATE_IDLE;
	ResetCtrl();
}

void TPurchaseRoadForm::InitDecideFactory(LPCSTR lpszID)
{
	CString szSQL;

	if(lpszID[0]!='\0')
	{
		m_lstDecideFactID.RemoveAll();
		lstDecideFact->Items->Clear();

		szSQL.Format("select distinct mf_code,mf_shortname from CompareFactory,Manufactur"
			" where cf_mfcode=mf_code"
			" and cf_apcode like '%s_'"
			" order by mf_code",lpszID);
		RunSQL(dm1->Query1,szSQL,true);
		while(!dm1->Query1->Eof)
		{
			m_lstDecideFactID.Add(dm1->Query1->FieldByName("mf_code")->AsString.c_str());
			lstDecideFact->Items->Add(dm1->Query1->FieldByName("mf_shortname")->AsString);

			dm1->Query1->Next();
		}
	}
}

//---------------------------------------------------------------------------
void __fastcall TPurchaseRoadForm::ctlDecideShow(TObject *Sender)
{
	CString szSQL;

//	InitDecideFactory("");

	if(!m_bDecideInitialed)
	{
		szSQL="select * from DicUnits order by du_code";
		RunSQL(dm1->Query1,szSQL,true);
		while(!dm1->Query1->Eof)
		{
			m_lstDecideUnitID.Add(dm1->Query1->FieldByName("du_code")->AsString.c_str());
			lstDecideUnit->Items->Add(dm1->Query1->FieldByName("du_name")->AsString);
			dm1->Query1->Next();
		}
		edtDecideFact0->Text="";
		
		edtDecideItem->Text	="";
		lstDecideFact->Text	="";
		edtDecideDate->Text	="";
		lstDecideUnit->ItemIndex	=-1;
		edtDecideNum	->Text="";
		edtDecidePrice->Text="";
	}
	m_bDecideInitialed=true;

	m_enRegion=EN_REG_DECIDE;
	if(!m_szActiveID.IsEmpty())	OnQueryDecide(m_szActiveID);
	m_enState=EN_STATE_IDLE;
	ResetCtrl();
}
//---------------------------------------------------------------------------

void __fastcall TPurchaseRoadForm::lstDecideViewClick(TObject *Sender)
{
	if(lstDecideView->Selected==NULL)	ResetCtrl();
}
//---------------------------------------------------------------------------

void __fastcall TPurchaseRoadForm::lstDecideViewSelectItem(TObject *Sender,TListItem *Item, bool Selected)
{
	TListItem *pItem;
	int i,nSel;
	CString szSQL;
	char strUnit[80],strPM[80],strFact[80],strMN[80],strMFPlan[80],strShowDate[80],strTemp[80];

	if(!Selected)	return;
	if((pItem=lstDecideView->Selected)==NULL)	return;
	if((nSel=lstDecideView->Items->IndexOf(pItem))<0 || nSel>=m_lstDecideViewID.GetSize())	return;

	if((nSel=lstDecideFact->Items->IndexOf(pItem->SubItems->Strings[0]))<0 || nSel>=m_lstDecideFactID.GetSize())
		return;
	strcpy(strMFPlan,m_lstDecideFactID[nSel]);

  strcpy(strTemp,pItem->SubItems->Strings[1].c_str());
	if(strlen(strTemp)!=8)	return;
	Date2Dbdate(strTemp,strShowDate);
  
	szSQL.Format("select * from DecideFactory,PurchaseDetail"
		" where df_apcode=pd_code and df_apcode='%s%s' and df_mfplan=%s and df_plandate=%s",
    m_szActiveID,pItem->Caption.c_str(),Str2DBString(strMFPlan),Str2DBString(strShowDate));
	RunSQL(dm1->Query1,szSQL,true);
	if(dm1->Query1->Eof)
	{
		ShowMessage("没有该项数据");
		return;
	}
	strcpy(strMN,dm1->Query1->FieldByName("pd_mncode")->AsString.c_str());

	edtDecideItem->Text=pItem->Caption;
	edtDecideFact0->Text=pItem->SubItems->Strings[0];
  edtDfShowDate->Text=pItem->SubItems->Strings[1];
	lstDecideFact->ItemIndex=lstDecideFact->Items->IndexOf(pItem->SubItems->Strings[2]);
	edtDecideDate->Text=DateField2Text(dm1->Query1->FieldByName("df_decidedate"));
	edtDecideNum->Text=FloatField2String(dm1->Query1->FieldByName("df_count"),2);
	if(strMN[0]=='E' && strMN[1]=='M')
		edtDecidePrice->Text=FloatField2String(dm1->Query1->FieldByName("df_price"),6);
	else
		edtDecidePrice->Text=FloatField2String(dm1->Query1->FieldByName("df_price"),3);
	strcpy(strUnit,dm1->Query1->FieldByName("df_unit")->AsString.c_str());
	for(i=0;i<m_lstDecideUnitID.GetSize();i++)
	{
		if(m_lstDecideUnitID[i]==strUnit)
		{
			lstDecideUnit->ItemIndex=i;
			break;
		}
	}
	if(i==m_lstDecideUnitID.GetSize())	lstDecideUnit->ItemIndex=-1;

	ResetCtrl();
}
//---------------------------------------------------------------------------

void __fastcall TPurchaseRoadForm::lstDecideFactExit(TObject *Sender)
{
	OnFactListExit(lstDecideFact,m_lstDecideFactID);

  int nSel;
  CString szSQL;
	char strMN[80];

  if((nSel=lstDecideFact->ItemIndex)<0 || nSel>=m_lstDecideFactID.GetSize())	return;
  edtDecideItem->Text=edtDecideItem->Text.Trim();
  if(edtDecideItem->Text.IsEmpty())	return;
	szSQL.Format("select * from CompareFactory,PurchaseDetail"
		" where cf_apcode=pd_code and cf_apcode='%s%s' and cf_mfcode='%s'",
		m_szActiveID,edtDecideItem->Text.c_str(),m_lstDecideFactID[nSel]);
  RunSQL(dm1->Query1,szSQL,true);
  if(!dm1->Query1->Eof)
  {
		strcpy(strMN,dm1->Query1->FieldByName("pd_mncode")->AsString.c_str());
		if(strMN[0]=='E' && strMN[1]=='M')
	  	edtDecidePrice->Text=FloatField2String(dm1->Query1->FieldByName("cf_higgleprice"),6);
		else
			edtDecidePrice->Text=FloatField2String(dm1->Query1->FieldByName("cf_higgleprice"),3);
  }
}
//---------------------------------------------------------------------------

void TPurchaseRoadForm::OnQueryDecide(LPCSTR lpszID)
{
	CString szSQL;
	TListItem *pItem;
	char strID[80],strMF[80];
	int i;

	InitDecideFactory(lpszID);

	lstDecideView->Items->Clear();
	m_lstDecideViewID.RemoveAll();
	if(lpszID[0]=='\0')	return;

	szSQL.Format("select * from DecideFactory where df_apcode like '%s_' order by df_apcode",lpszID);
	RunSQL(dm1->Query1,szSQL,true);
	while(!dm1->Query1->Eof)
	{
		strcpy(strID,dm1->Query1->FieldByName("df_apcode")->AsString.c_str());
		if(strID[0]=='\0')	return;

		pItem=lstDecideView->Items->Add();
		assert(pItem!=NULL);
		pItem->Caption =  strID+strlen(strID)-1;

		strcpy(strMF,dm1->Query1->FieldByName("df_mfplan")->AsString.c_str());
		for(i=0;i<m_lstDecideFactID.GetSize();i++)
		{
			if(m_lstDecideFactID[i]==strMF)
			{
				pItem->SubItems->Add(lstDecideFact->Items->Strings[i]);
				break;
			}
		}
		if(i==m_lstDecideFactID.GetSize())	pItem->SubItems->Add("");

    pItem->SubItems->Add(DateField2Text(dm1->Query1->FieldByName("df_plandate")));

		strcpy(strMF,dm1->Query1->FieldByName("df_mfdecide")->AsString.c_str());
		for(i=0;i<m_lstDecideFactID.GetSize();i++)
		{
			if(m_lstDecideFactID[i]==strMF)
			{
				m_lstDecideViewID.Add(strMF);
				pItem->SubItems->Add(lstDecideFact->Items->Strings[i]);
				break;
			}
		}
		if(i==m_lstDecideFactID.GetSize())
		{
			m_lstDecideViewID.Add("");
			pItem->SubItems->Add("");
		}

		dm1->Query1->Next();
	}
	m_szActiveID=lpszID;

}


void TPurchaseRoadForm::OnDecideOK()
{
	int nSel,nRow,nUnit;
	CString szSQL,szMsg;
	char strDate[80],strPD[80],strMN[80],strMFPlan[80],strShowDate[80];
	TListItem *pItem;

	if(m_szActiveID.IsEmpty())	return;

	if((pItem=lstDecideView->Selected)==NULL)	return;
	if((nRow=lstDecideView->Items->IndexOf(pItem))<0 || nRow>=m_lstDecideViewID.GetSize())	return;
  if(edtDfShowDate->Text.Length()!=8)	return;
	Date2Dbdate(edtDfShowDate->Text.c_str(),strShowDate);

	sprintf(strPD,"%s%s",m_szActiveID,pItem->Caption.c_str());
	szSQL.Format("select * from PurchaseDetail where pd_code='%s'",strPD);
	RunSQL(dm1->Query1,szSQL,true);
	if(dm1->Query1->Eof)
	{
		ShowMessage("请购单中没有该项次");
		return;
	}
	if((nSel=lstDecideFact->Items->IndexOf(edtDecideFact0->Text))<0 || nSel>=m_lstDecideFactID.GetSize())
		return;
	strcpy(strMFPlan,m_lstDecideFactID[nSel]);
	strcpy(strMN,dm1->Query1->FieldByName("pd_mncode")->AsString.c_str());
	if((nSel=lstDecideFact->ItemIndex)<0 || nSel>=m_lstDecideFactID.GetSize())
	{
		ShowMessage("请选择一个有效的厂商");
		return;
	}
	edtDecideDate->Text=edtDecideDate->Text.Trim();
	if(!CheckDateEditor(edtDecideDate))	return;
	Date2Dbdate(edtDecideDate->Text.c_str(),strDate);
	if(!CheckFloatEditor(edtDecideNum))	return;
	if(!CheckFloatEditor(edtDecidePrice))	return;
//  if(!CheckDateEditor(edtValidDate))	return;
//	Date2Dbdate(edtValidDate->Text.c_str(),strValidDate);
	if((nUnit=lstDecideUnit->ItemIndex)<0 || nUnit>=m_lstDecideUnitID.GetSize())
	{
		ShowMessage("请选择一个有效的单位");
		return;
	}

	if(m_enState==EN_STATE_EDIT)
	{
		szSQL.Format("select * from DecideFactory where df_apcode='%s' and df_mfplan=%s and df_plandate=%s",
    	strPD,Str2DBString(strMFPlan),Str2DBString(strShowDate));
		RunSQL(dm1->Query1,szSQL,true);
		if(dm1->Query1->Eof)
		{
			ShowMessage("数据库中没有该项数据");
			return;
		}

//		bool bUpdateBook;
//		char strCard[80];
//		szSQL.Format("select * from BookFactory where bf_apcode='%s' and bf_mfcode=%s",strPD,Str2DBString(strMFPlan));
//		RunSQL(dm1->Query1,szSQL,true);
//		bUpdateBook = dm1->Query1->RecordCount==1;
//		if(bUpdateBook)
//		{
//			szSQL.Format("select * from CompareFactory where cf_apcode='%s' and cf_mfcode='%s'",
//				strPD,m_lstDecideFactID[nSel]);
//			RunSQL(dm1->Query1,szSQL,true);
//			strcpy(strCard,dm1->Query1->FieldByName("cf_card")->AsString.c_str());
//		}

    try
		{
			BeginTransact();

			szSQL="update DecideFactory set";
			szSQL+=" df_mfdecide=";		szSQL+=Str2DBString(m_lstDecideFactID[nSel]);
			szSQL+=",df_decidedate=";	szSQL+=Str2DBString(strDate);                //在呈核时未输入这项数据，这里才输入
			szSQL+=",df_count=";			szSQL+=Text2DBFloat(edtDecideNum->Text,2).c_str();
			szSQL+=",df_unit=";				szSQL+=Str2DBString(m_lstDecideUnitID[nUnit]);
			if(strMN[0]=='E' && strMN[1]=='M')
      {
				szSQL+=",df_price=";			szSQL+=Text2DBFloat(edtDecidePrice->Text,6).c_str();
      }
			else
      {
				szSQL+=",df_price=";			szSQL+=Text2DBFloat(edtDecidePrice->Text,3).c_str();
      }
//			szSQL+=",df_validdate=";	szSQL+=Str2DBString(strValidDate);
			szSQL+=" where df_apcode=";	szSQL+=Str2DBString(strPD);
			szSQL+=" and df_mfplan=";		szSQL+=Str2DBString(strMFPlan);
      szSQL+=" and df_plandate=";	szSQL+=Str2DBString(strShowDate);
			if(!RunTransactSQL(szSQL))	goto EXCEPT_TRANSACT;

//			if(bUpdateBook)
//			{
//				szSQL.Format("update BookFactory set bf_mfcode='%s',bf_mfcard='%s'"
//					" where bf_apcode='%s'",m_lstDecideFactID[nSel],strCard,strPD);
//				if(!RunTransactSQL(szSQL))	goto EXCEPT_TRANSACT;
//			}
			CommitTransact();
		}
		catch(...)
		{
			goto EXCEPT_TRANSACT;
		}

		pItem->SubItems->Strings[2]=lstDecideFact->Text;
		m_lstDecideViewID[nRow]=(LPCSTR)m_lstDecideFactID[nSel];

		m_enState=EN_STATE_IDLE;
		ResetCtrl();
	}
  return;

EXCEPT_TRANSACT:
	RollBackTransact();
	szMsg.Format("数据库操作失败，SQL=\n%s",szSQL);
	ShowMessage((LPCSTR)szMsg);
}

void __fastcall TPurchaseRoadForm::btnQuotePrintClick(TObject *Sender)
{
	TPrnCompareFactoryForm *pPrn;
	CString szSQL;
	int i,j;
	char strMF[80];

  pPrn=new TPrnCompareFactoryForm(this);
  assert(pPrn!=NULL);

	if(m_szActiveID.IsEmpty())	return;
	pPrn->ReqDep		->Caption=edtAskDepart->Text;
	pPrn->MainID		->Caption=edtMainID		->Text;
  pPrn->Project		->Caption=edtProject	->Text;
  pPrn->ReqDate		->Caption=edtAskDate	->Text;
  pPrn->NeedDate	->Caption=edtNeedDate	->Text;

	szSQL.Format("select * from HandleMan,AskPurchase where ap_hmcode=hm_code and ap_code='%s'",m_szActiveID);
	RunSQL(dm1->Query1,szSQL,true);
	if(!dm1->Query1->Eof)
	{
	  pPrn->HandleMan	->Caption=dm1->Query1->FieldByName("hm_name")->AsString;
		pPrn->Tel				->Caption=dm1->Query1->FieldByName("hm_tel")->AsString;
	}
	else
	{
	  pPrn->HandleMan	->Caption="";
		pPrn->Tel				->Caption="";
	}

	szSQL.Format("select * from QuoteFactory where qf_apcode='%s'",m_szActiveID);
	RunSQL(dm1->Query1,szSQL,true);
	if(!dm1->Query1->Eof)	pPrn->EndDate->Caption=(LPCSTR)Date2YYMMDD(dm1->Query1->FieldByName("qf_enddate")->AsDateTime);
	else pPrn->EndDate->Caption="";

	szSQL.Format("select distinct mf_code,mf_shortname,cf_card,cf_deliverday"
		" from CompareFactory,Manufactur where mf_code=cf_mfcode"
		" and cf_apcode like '%s_'",m_szActiveID);
	RunSQL(dm1->Query1,szSQL,true);
	i=0;
	while(!dm1->Query1->Eof)
	{
		pPrn->m_lstID.Add(dm1->Query1->FieldByName("mf_code")->AsString.c_str());
		pPrn->m_pFact[i]->Caption=dm1->Query1->FieldByName("mf_shortname")->AsString;
		pPrn->m_pCard[i]->Caption=dm1->Query1->FieldByName("cf_card")->AsString;
		pPrn->m_pDays[i]->Caption=IntField2Text(dm1->Query1->FieldByName("cf_deliverday"));
		i++;
		if(i>=5)	break;
    dm1->Query1->Next();
	}

	szSQL.Format("select * from QuoteFactory,Manufactur where mf_code=qf_mfcode"
		" and qf_apcode='%s'",m_szActiveID);
	RunSQL(dm1->Query1,szSQL,true);
	while(!dm1->Query1->Eof)
	{
		if(i>=5)	break;
		strcpy(strMF,dm1->Query1->FieldByName("qf_mfcode")->AsString.c_str());
		for(j=0;j<pPrn->m_lstID.GetSize();j++)
		{
			if(pPrn->m_lstID[j]==strMF)	break;
		}
		if(j==pPrn->m_lstID.GetSize())
		{
			pPrn->m_pFact[i]->Caption=dm1->Query1->FieldByName("mf_shortname")->AsString;
			pPrn->m_pCard[i]->Caption="未报价";
			pPrn->m_pDays[i]->Caption="";
			i++;
		}
		dm1->Query1->Next();
	}

	for(;i<5;i++)
	{
		pPrn->m_pFact[i]->Caption="";
		pPrn->m_pCard[i]->Caption="";
		pPrn->m_pDays[i]->Caption="";
	}

	szSQL.Format("select distinct pd_code,mn_name,pd_count,du_name from CompareFactory,PurchaseDetail,materialno,DicUnits"
		" where pd_code=cf_apcode and pd_mncode=mn_code and pd_ducode=du_code"
		" and pd_code like '%s_' order by pd_code",m_szActiveID);
	if(!OpenQuery(dm1->sqlPrint,szSQL))	return;

  pPrn->PrnView->PreviewModal();
  delete pPrn;
}
//---------------------------------------------------------------------------

void __fastcall TPurchaseRoadForm::btnHigglePrintClick(TObject *Sender)
{
	btnQuotePrintClick(Sender);
}
//---------------------------------------------------------------------------

#include "PrnShowFactory.h"
typedef struct _base3coldata
{
	char strCode[80];
	char strName[256];
	char strCol2[80];
} BASE3COLDATA;

void __fastcall TPurchaseRoadForm::btnShowPrintClick(TObject *Sender)
{
  char strMFPlan[80],strAP[80];
  int nSel,i;
	TPrnShowFactoryForm *pPrn;
  CString szSQL,szTable;
	char strDep[80],strGACode[80],strTop[256],strBottom[256],strLeft[256],strTemp[256],strCode[256];
  AnsiString szBuyType;
  bool bEmpty;

	if(m_szActiveID.IsEmpty())	return;
        edtMainID->Text=edtMainID->Text.Trim();
        edtShowItem->Text=edtShowItem->Text.Trim();

	szTable=GetTmpTableName();
	szSQL.Format("create table dbo.%s ("
		"m_key    varchar(80),"
		"m_pdcode varchar(10),"
		"m_mfplan varchar(10)," //拟购厂商
		"m_plandate datetime,"  //呈核日
		"m_cfmfcode varchar(10),"//报价厂商
		"m_mfname varchar(80),"
		"m_qtcount float," //报价数量
		"m_mfcard varchar(80),"
		"m_qtprice float," //报价单价
		"m_rmbcode varchar(10)," //报价币别
		"m_hgprice float,"//议价单价
		"m_pmtype  varchar(80)," //报价付款方式
		"m_dltype  varchar(80)," //报价交货方式
		"m_money   float," //议价总金额
		"m_taxtype varchar(20),"
		"m_days    int,"
		"m_planrem varchar(256)," //呈核备注
		"m_invoice varchar(80),"
		"m_dfpricert varchar(80),"
		"m_dfcount float,"
    "m_dfvalidate datetime"
		")",szTable);
	RunSQL(dm1->Query1,szSQL);


	szSQL.Format("insert into %s"                                           //全部一次过列印
		" select pd_code+df_mfplan+convert(varchar(40),getdate(),20),pd_code,df_mfplan,df_plandate,cf_mfcode,mf_shortname,cf_quotenum,cf_card,cf_quoteprice,"
		"cf_quotermb,cf_higgleprice,pm_name,dd_name,cf_quotenum*cf_higgleprice,cf_invoice,cf_deliverday,"
		"df_planrem,cf_invoice,df_pricert,df_count,df_validdate"
		" from PurchaseDetail,DecideFactory,CompareFactory,Manufactur,DicPayment,DicDelivery"
		" where pd_code=df_apcode"
		" and pd_code=cf_apcode"
		" and cf_mfcode=mf_code"
		" and cf_pmcode=pm_code"
		" and cf_ddcode=dd_code"
		" and pd_code like '%s_'",szTable,m_szActiveID);
	RunSQL(dm1->Query1,szSQL);
//------------------------------------------------------------------------------//点击一条，列印一条
/*       szSQL.Format("insert into %s"
		" select pd_code+df_mfplan+convert(varchar(40),getdate(),20),pd_code,df_mfplan,df_plandate,cf_mfcode,mf_shortname,cf_quotenum,cf_card,cf_quoteprice,"
		"cf_quotermb,cf_higgleprice,pm_name,dd_name,cf_quotenum*cf_higgleprice,cf_invoice,cf_deliverday,"
		"df_planrem,cf_invoice,df_pricert,df_count,df_validdate"
		" from PurchaseDetail,DecideFactory,CompareFactory,Manufactur,DicPayment,DicDelivery"
		" where pd_code=df_apcode"
		" and pd_code=cf_apcode"
		" and cf_mfcode=mf_code"
		" and cf_pmcode=pm_code"
		" and cf_ddcode=dd_code"
		" and pd_code like '%s%s'",szTable,edtMainID->Text.c_str(),edtShowItem->Text.c_str());
	RunSQL(dm1->Query1,szSQL);         */
//------------------------------------------------------------------------------

	CArray<BASE3COLDATA,BASE3COLDATA>lstDF;
	BASE3COLDATA rwDF;
	szSQL.Format("select df_apcode,df_mfplan,convert(varchar(40),getdate(),20) as m_date from DecideFactory where df_apcode like '%s_' order by df_apcode",m_szActiveID);
	RunSQL(dm1->Query1,szSQL,true);
	while(!dm1->Query1->Eof)
	{
		strcpy(rwDF.strCode,dm1->Query1->FieldByName("df_apcode")->AsString.c_str());
		strcpy(rwDF.strName,dm1->Query1->FieldByName("df_mfplan")->AsString.c_str());
		strcpy(rwDF.strCol2,dm1->Query1->FieldByName("m_date")->AsString.c_str());
		lstDF.Add(rwDF);
		dm1->Query1->Next();
	}

	for(i=0;i<lstDF.GetSize();i++)
	{
  	rwDF=lstDF[i];
//        ShowMessage(rwDF.strCode);
		strcpy(strAP,rwDF.strCode);
		strAP[7]='\0';
//		strAP[8]='\0';
		szSQL.Format("insert into %s"
			" select '%s%s%s','%s',qf_mfcode,'%s',null,mf_shortname,null,'无报价',null,null,null,null,null,null,null,null,null,null,null,null,null"
			" from QuoteFactory,Manufactur"
			" where qf_apcode='%s'"
			" and qf_mfcode=mf_code",szTable,rwDF.strCode,rwDF.strName,rwDF.strCol2,rwDF.strCode,rwDF.strCol2,strAP);
		sprintf(strTemp," and qf_apcode+qf_mfcode not in"
			" (select distinct substring(cf_apcode,1,7)+cf_mfcode from CompareFactory where cf_apcode='%s')",
			rwDF.strCode);
		szSQL+=strTemp;
//                ShowMessage(strTemp);
		RunSQL(dm1->Query1,szSQL);
	}


  pPrn=new TPrnShowFactoryForm(this);
  assert(pPrn!=NULL);

	GetPrivateProfileString("SHOWPRINTSETUP","TOPMARGIN" ,"",strTop ,250,INI_FILE_NAME);
  GetPrivateProfileString("SHOWPRINTSETUP","BOTTOMMARGIN" ,"",strBottom ,250,INI_FILE_NAME);
  GetPrivateProfileString("SHOWPRINTSETUP","LEFTMARGIN","",strLeft,250,INI_FILE_NAME);
	if(strTop[0]!='\0' && strLeft[0]!='\0')
  {
  	pPrn->PrnView->Page->TopMargin=atof(strTop);
  	pPrn->PrnView->Page->BottomMargin=atof(strBottom);
    pPrn->PrnView->Page->LeftMargin=atof(strLeft);
  }
  pPrn->txtHandle->Caption=edtStockMan->Text;

  szSQL.Format("select * from AskPurchase where ap_code='%s'",m_szActiveID);
	RunSQL(dm1->Query1,szSQL,true);

 //       ShowMessage(dm1->Query1->RowsAffected);

	if(dm1->Query1->Eof)	return;

  pPrn->ReqDate		->Caption=Field2DateString(dm1->Query1->FieldByName("ap_reqdate"));
  pPrn->NeedDate	->Caption=Field2DateString(dm1->Query1->FieldByName("ap_needdate"));
	strcpy(strDep,dm1->Query1->FieldByName("ap_reqdepart")->AsString.c_str());
	strcpy(strGACode,dm1->Query1->FieldByName("ap_gacode")->AsString.c_str());

  szBuyType=dm1->Query1->FieldByName("ap_buytype")->AsString;
  if(szBuyType=="M")        pPrn->BuyType->Caption="内购";
  else if(szBuyType=="N")   pPrn->BuyType->Caption="外购";
  else if(szBuyType=="H")   pPrn->BuyType->Caption="核销";

	szSQL.Format("select * from DicDepart,DepartCorp where substring(dd_code,1,2)*=dc_code"
		" and dd_code='%s'",strDep);
	RunSQL(dm1->Query1,szSQL,true);
	if(dm1->Query1->Eof)
	{
		pPrn->ReqCorp->Caption	="";
		pPrn->ReqDepart->Caption="";
	}
	else
	{
		pPrn->ReqCorp->Caption	=dm1->Query1->FieldByName("dc_name")->AsString;
		pPrn->ReqDepart->Caption=dm1->Query1->FieldByName("dd_name")->AsString;
	}

	bEmpty=true;
	if(strGACode[0]!='\0')
	{
		szSQL.Format("select * from GoodsAddr where ga_code='%s'",strGACode);
		RunSQL(dm1->Query1,szSQL,true);
		if(!dm1->Query1->Eof)
		{
			bEmpty=false;
			pPrn->GAName0->Caption=dm1->Query1->FieldByName("ga_area")->AsString;
			pPrn->GAName1->Caption=dm1->Query1->FieldByName("ga_name")->AsString;
		}
	}
	if(bEmpty)
	{
		pPrn->GAName0->Caption="";
		pPrn->GAName1->Caption="";
	}

	szSQL.Format("select * from %s order by m_key,m_hgprice",szTable);
	if(OpenQuery(dm1->sqlPrint,szSQL))
		pPrn->PrnView->PreviewModal();
	delete pPrn;

	szSQL.Format("drop table dbo.%s",szTable);
	RunSQL(dm1->Query1,szSQL);
}
//---------------------------------------------------------------------------

#include "FactorySearch.h"
void __fastcall TPurchaseRoadForm::btnSpeerFactSearchClick(TObject *Sender)
{
	TFactorySearchForm *pForm;
  int i;

  pForm=new TFactorySearchForm(this);
  assert(pForm!=NULL);
  if(pForm->ShowModal()==mrOk && !pForm->m_szID.IsEmpty())
  {
  	for(i=0;i<m_lstSpeerFactID.GetSize();i++)
    {
    	if(m_lstSpeerFactID[i]==pForm->m_szID)
      {
      	lstSpeerFact->ItemIndex=i;
        break;
      }
    }
  }
  delete pForm;
}
//---------------------------------------------------------------------------

void __fastcall TPurchaseRoadForm::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
	if(Key==VK_RETURN)
  {
  	if(ActiveControl==edtMainID && m_enState==EN_STATE_IDLE)
    {
    	if(btnQuery->CanFocus())	btnQuery->SetFocus();
    }
    else if(ActiveControl==lstSpeerFact)
    {
    	if(btnOK->CanFocus())	btnOK->SetFocus();
    }
    else if(ActiveControl==lstQuoteDelivery)
    {
    	if(btnOK->CanFocus())	btnOK->SetFocus();
    }
    else if(ActiveControl==edtHiggleDate)
    {
    	if(btnOK->CanFocus())	btnOK->SetFocus();
    }
    else if(ActiveControl==lstPriceRT)
    {
    	if(btnOK->CanFocus())	btnOK->SetFocus();
    }
    else if(ActiveControl==edtDecidePrice)
    {
    	if(btnOK->CanFocus())	btnOK->SetFocus();
    }
    else	KeyReturnHandle(ActiveControl);
  }
}
//---------------------------------------------------------------------------

void __fastcall TPurchaseRoadForm::lstDecideUnitExit(TObject *Sender)
{
	HandleListboxExit(lstDecideUnit,&m_lstDecideUnitID);
/*
	int nSel;
	if((nSel=lstDecideUnit->Items->IndexOf(lstDecideUnit->Text))<0 || nSel>=m_lstDecideUnitID.GetSize())
	{
		lstDecideUnit->Text=lstDecideUnit->Text.UpperCase();
		for(nSel=0;nSel<m_lstDecideUnitID.GetSize();nSel++)
		{
			if(m_lstDecideUnitID[nSel]==lstDecideUnit->Text.c_str())
			{
				lstDecideUnit->ItemIndex=nSel;
				break;
			}
		}
	}
*/
}
//---------------------------------------------------------------------------

void __fastcall TPurchaseRoadForm::lstQuoteUnitExit(TObject *Sender)
{
	HandleListboxExit(lstQuoteUnit,&m_lstQuoteUnitID);
/*
	int nSel;
	if((nSel=lstQuoteUnit->Items->IndexOf(lstQuoteUnit->Text))<0 || nSel>=m_lstQuoteUnitID.GetSize())
	{
		lstQuoteUnit->Text=lstQuoteUnit->Text.UpperCase();
		for(nSel=0;nSel<m_lstQuoteUnitID.GetSize();nSel++)
		{
			if(m_lstQuoteUnitID[nSel]==lstQuoteUnit->Text.c_str())
			{
				lstQuoteUnit->ItemIndex=nSel;
				break;
			}
		}
	}
*/
}
//---------------------------------------------------------------------------

void __fastcall TPurchaseRoadForm::btnToBookClick(TObject *Sender)
{
	int nSel;
	TListItem *pItem;
	char strID[80];

	if(m_szActiveID.IsEmpty())	return;
	//订购单输入接口，文件：BookFactory.*
	int nRight=GetOperatorRight(operatorcode.c_str(),"IDM_BOOKFACTORY");

	if((pItem=lstBookView->Selected)==NULL)
		BookFactory(nRight);
	else
		BookFactory(pItem->SubItems->Strings[0].c_str(),nRight);

	OnQueryBook(m_szActiveID);
}
//---------------------------------------------------------------------------

void __fastcall TPurchaseRoadForm::ctlBookShow(TObject *Sender)
{
	m_enRegion=EN_REG_BOOK;
	if(!m_szActiveID.IsEmpty())	OnQueryBook(m_szActiveID);
	m_enState=EN_STATE_IDLE;
	ResetCtrl();
}
//---------------------------------------------------------------------------

void TPurchaseRoadForm::OnQueryBook(LPCSTR lpszID)
{
	CString szSQL;
	TListItem *pItem;
	char strID[80];

	lstBookView->Items->Clear();
	if(lpszID==NULL || lpszID[0]=='\0')	return;
	szSQL.Format("select * from BookFactory where bf_apcode like '%s_' order by bf_apcode",lpszID);
	RunSQL(dm1->Query1,szSQL,true);
	while(!dm1->Query1->Eof)
	{
		strcpy(strID,dm1->Query1->FieldByName("bf_apcode")->AsString.c_str());

		pItem=lstBookView->Items->Add();
		assert(pItem!=NULL);
		pItem->Caption=strID+strlen(strID)-1;
		pItem->SubItems->Add(dm1->Query1->FieldByName("bf_code")->AsString);

		dm1->Query1->Next();
	}
	m_szActiveID=lpszID;
}
void __fastcall TPurchaseRoadForm::lstBookViewDblClick(TObject *Sender)
{
	if(btnToBook->Enabled)
		btnToBookClick(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TPurchaseRoadForm::lstQuoteUnitEnter(TObject *Sender)
{
	if(lstQuoteUnit->ItemIndex==-1)
  {
  	lstQuoteUnit->ItemIndex=lstQuoteUnit->Items->IndexOf(edtQuoteReqUnit->Text);
  }
}
//---------------------------------------------------------------------------

void __fastcall TPurchaseRoadForm::edtQuoteNumEnter(TObject *Sender)
{
	if(edtQuoteNum->Text.IsEmpty())
  {
  	edtQuoteNum->Text=edtQuoteReqNum->Text;
  }
}
//---------------------------------------------------------------------------

void MaterBookList(LPCSTR lpszID,int nAuth);

void __fastcall TPurchaseRoadForm::btnStockRecordClick(TObject *Sender)
{
	TListItem *pItem;
  char strID[80];
  CString szSQL;

  if(m_szActiveID.IsEmpty())	return;
  if((pItem=lstShowView->Selected)==NULL)	return;

  szSQL.Format("select * from PurchaseDetail where pd_code='%s%s'",m_szActiveID,pItem->Caption.c_str());
  RunSQL(dm1->Query1,szSQL,true);
  if(dm1->Query1->Eof)	return;

  strcpy(strID,dm1->Query1->FieldByName("pd_mncode")->AsString.c_str());
	MaterBookList(strID,AUTH_FULL);
}
//---------------------------------------------------------------------------

void __fastcall TPurchaseRoadForm::lstQuoteDeliveryExit(TObject *Sender)
{
	HandleListboxExit(lstQuoteDelivery,&m_lstQuoteDeliveryID);
}
//---------------------------------------------------------------------------

void __fastcall TPurchaseRoadForm::lstQuoteTaxExit(TObject *Sender)
{
	HandleListboxExit(lstQuoteTax,&m_lstQuoteTaxID);
}
//---------------------------------------------------------------------------

void __fastcall TPurchaseRoadForm::btnListStockClick(TObject *Sender)
{
	TListItem *pItem;
  char strID[80];
  CString szSQL;

  if(edtMainID->Text.IsEmpty())	return;
  if((pItem=lstStockList->Selected)==NULL)	return;

  szSQL.Format("select * from PurchaseDetail where pd_code='%s%s'",edtMainID->Text.c_str(),pItem->Caption.c_str());
  RunSQL(dm1->Query1,szSQL,true);
  if(dm1->Query1->Eof)	return;

  strcpy(strID,dm1->Query1->FieldByName("pd_mncode")->AsString.c_str());
	MaterBookList(strID,AUTH_FULL);
}
//---------------------------------------------------------------------------

void __fastcall TPurchaseRoadForm::ctlStockListShow(TObject *Sender)
{
	m_enRegion=EN_REG_LIST;
	ResetCtrl();
	InitStockList();
}

void TPurchaseRoadForm::InitStockList()
{
	CString szSQL;
  TListItem *pItem;
  char strID[80];

	m_szActiveID="";
	if(!edtMainID->Text.IsEmpty())
	{
		szSQL.Format("select pd_code from PurchaseDetail"
			" where pd_code like '%s_'"
			" order by pd_code",edtMainID->Text.c_str());

		lstStockList->Items->Clear();
		RunSQL(dm1->Query1,szSQL,true);
		if(!dm1->Query1->Eof)
			m_szActiveID=edtMainID->Text.c_str();

		while(!dm1->Query1->Eof)
		{
			pItem=lstStockList->Items->Add();
			assert(pItem!=NULL);
			strcpy(strID,dm1->Query1->FieldByName("pd_code")->AsString.c_str());
			pItem->Caption = strID+strlen(strID)-1;

			dm1->Query1->Next();
		}
	}
}
//---------------------------------------------------------------------------






void __fastcall TPurchaseRoadForm::lstQuoteFactChange(TObject *Sender)
{
/*
//	int nPreSel=lstQuoteFact->ItemIndex;
	OnFactListExit(lstQuoteFact,m_lstQuoteFactID);
//	if(lstQuoteFact->ItemIndex==nPreSel)	return;
/*
        if(true)              //测试代码
        {
                strcpy(strTemp,m_lstQuoteTaxID[0]);
                ShowMessage(strTemp);
        }


        int nSel,i;
	char strTax[80],strTemp[256];
		lstQuoteTax->Items->Clear();
		m_lstQuoteTaxIDnew.RemoveAll();

	if((nSel=lstQuoteFact->ItemIndex)>=0 && nSel<m_lstQuoteFactID.GetSize())        //添加厂商档里的税别
        {
                CString szSQL;
		szSQL.Format("select * from Manufactur,DicInvoice where mf_taxtype=di_code and mf_code='%s'",m_lstQuoteFactID[nSel]);
                RunSQL(dm1->Query1,szSQL,true);
                if(!dm1->Query1->Eof)
                {
                        m_lstQuoteTaxIDnew.Add(dm1->Query1->FieldByName("di_code")->AsString.c_str());
                        lstQuoteTax->Items->Add(dm1->Query1->FieldByName("di_name")->AsString);
                        dm1->Query1->Next();
                }
        }

	if((nSel=lstQuoteFact->ItemIndex)>=0 && nSel<m_lstQuoteFactID.GetSize())
	{
//		if(lstQuoteTax->ItemIndex < 0)
//		{
			CString szSQL;
			szSQL.Format("select * from Manufactur where mf_code='%s'",m_lstQuoteFactID[nSel]);
			RunSQL(dm1->Query1,szSQL,true);
			if(!dm1->Query1->Eof)
			{
				strcpy(strTax,dm1->Query1->FieldByName("mf_taxtype")->AsString.c_str());
				if(strTax[0]=='\0')	return;
				for(i=0;i<m_lstQuoteTaxIDnew.GetSize();i++)
				{
					if(m_lstQuoteTaxIDnew[i]==strTax)
					{
						lstQuoteTax->ItemIndex=i;
            break;
					}
				}
//			}
		}
	}
*/        
}
//---------------------------------------------------------------------------

void __fastcall TPurchaseRoadForm::btnToMutBookClick(TObject *Sender)
{
	int nRight=GetOperatorRight(operatorcode.c_str(),"IDM_BOOKMULTIPRN");
	//订购单列印接口，文件：BookMultiPrn.*
	BookMultiPrn(nRight);
}
//---------------------------------------------------------------------------

