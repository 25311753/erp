//---------------------------------------------------------------------------

#include <vcl.h>
#include <stdio.h>
#include <math.h>
#include <assert.h>
#pragma hdrstop

#include "DataModule.h"
#include "BaseCode.h"
#include "PurchaseRow.h"
#include "AskPurchase.h"
#include "TConst.h"
#include "LdyInterface.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TAskPurchaseForm *AskPurchaseForm;

//=================================================================
//请购单输入接口，文件：AskPurchase.*
void AskPurchase(int nAuth)
{
	if(nAuth==AUTH_NONE)	return;         //没有权限

	TAskPurchaseForm *pForm;
  pForm=new TAskPurchaseForm(Application);
  assert(pForm!=NULL);
  pForm->m_nAuthor=nAuth;
  pForm->ShowModal();
  delete pForm;
}

void AskPurchase(LPCSTR lpszID,int nAuth)
{
	if(nAuth==AUTH_NONE)	return;

	TAskPurchaseForm *pForm;
  pForm=new TAskPurchaseForm(Application);
  assert(pForm!=NULL);
	if(lpszID!=NULL)	pForm->m_szIDFirst=lpszID;
  pForm->m_nAuthor=nAuth;
  pForm->ShowModal();
  delete pForm;
}

void UnionPurchase(LPCSTR lpszID,int nAuth)                                     //统购
{
	if(nAuth==AUTH_NONE)	return;

	TAskPurchaseForm *pForm;
  pForm=new TAskPurchaseForm(Application);
  assert(pForm!=NULL);
	pForm->m_bUnion=true;
	if(lpszID!=NULL)	pForm->m_szIDFirst=lpszID;
  pForm->m_nAuthor=nAuth;
  pForm->ShowModal();
  delete pForm;
}
//---------------------------------------------------------------------------

//统购时
//    采购部门不锁住，自动寻找本公司管理课

//---------------------------------------------------------------------------
__fastcall TAskPurchaseForm::TAskPurchaseForm(TComponent* Owner)
	: TForm(Owner)
{
	m_bIsTreat=false;
	m_bUnion=false;
}
//---------------------------------------------------------------------------
void __fastcall TAskPurchaseForm::btnExitClick(TObject *Sender)
{
	if(m_enState==EN_STATE_IDLE)
	{
		m_bExiting=true;
		Close();
	}
	else
	{
		m_enState=EN_STATE_IDLE;
		ResetCtrl();
	}
}
//---------------------------------------------------------------------------
void __fastcall TAskPurchaseForm::FormShow(TObject *Sender)
{
	CString szSQL;
	AnsiString szDep;
	TListItem *pItem;
	char strTemp[256],strCorp[80];

	if(m_bUnion)
	{
		Title->Caption="统购单输入";
		m_bIsTreat=true;
	}
	m_bExiting=false;

	edtMainID		->Text="";
	edtNeedDate	->Text="";
	edtAskDate	->Text="";
	edtProject	->Text="";
	edtUsage		->Text="";
	edtChkSpec	->Text="";
	edtItem			->Text="";
	edtMater		->Text="";
	edtCount		->Text="";
	edtCooper		->Text="";
	edtEndFlag	->Text="";
	edtMnname		->Text="";
	edtAfmDate		->Text="";
	edtModifyDate	->Text="";
	edtInpDate		->Text="";
  edtPrnDate		->Text="";

	lstType->Items->Add("一般");
	lstType->Items->Add("紧急");

	lstBuyType->Items->Add("内购");
	lstBuyType->Items->Add("外购");
	lstBuyType->Items->Add("核销");

	lstChkFlag->Items->Add("Y");
	lstChkFlag->Items->Add("N");

	ResetAskDepart(false);
/*
	szSQL.Format("select * from operator,DepartCorp where op_cpcode=substring(dc_code,1,1)"
		" and op_code='%s'",operatorcode.c_str());
  RunSQL(dm1->Query1,szSQL,true);
	strcpy(strCorp,dm1->Query1->FieldByName("op_cpcode")->AsString.c_str());
	if(strCorp[0]=='\0' || operatorcode=="admin")
  {
		szSQL="select * from DicDepart,DepartCorp where substring(dd_code,1,2)*=dc_code order by dd_code";
		RunSQL(dm1->Query1,szSQL,true);
		while(!dm1->Query1->Eof)
		{
			m_lstDepartID.Add(dm1->Query1->FieldByName("dd_code")->AsString.c_str());
			szDep=dm1->Query1->FieldByName("dc_name")->AsString+dm1->Query1->FieldByName("dd_name")->AsString;
			lstDepAsk		->Items->Add(szDep);
			lstDepCharge->Items->Add(szDep);
			dm1->Query1->Next();
		}
  }
  else
  {
		szSQL.Format("select * from DicDepart,DepartCorp where substring(dd_code,1,2)*=dc_code"
      " and substring(dc_code,1,1)='%s'"
	    " order by dd_code",strCorp);
		RunSQL(dm1->Query1,szSQL,true);
		while(!dm1->Query1->Eof)
		{
			m_lstDepartID.Add(dm1->Query1->FieldByName("dd_code")->AsString.c_str());
			szDep=dm1->Query1->FieldByName("dc_name")->AsString+dm1->Query1->FieldByName("dd_name")->AsString;
			lstDepAsk		->Items->Add(szDep);
			lstDepCharge->Items->Add(szDep);
			dm1->Query1->Next();
		}
  }
*/

	szSQL="select * from StockDepart order by sd_code";
	RunSQL(dm1->Query1,szSQL,true);
	while(!dm1->Query1->Eof)
	{
		m_lstStockDepID.Add(dm1->Query1->FieldByName("sd_code")->AsString.c_str());
		lstDepBuy->Items->Add(dm1->Query1->FieldByName("sd_name")->AsString);
		dm1->Query1->Next();
	}
	szSQL="select * from HandleMan order by hm_code";
	RunSQL(dm1->Query1,szSQL,true);
	while(!dm1->Query1->Eof)
	{
		m_lstHandleID.Add(dm1->Query1->FieldByName("hm_code")->AsString.c_str());
		lstHandle->Items->Add(dm1->Query1->FieldByName("hm_name")->AsString);
		dm1->Query1->Next();
	}
	szSQL="select * from GoodsAddr order by ga_code";
	RunSQL(dm1->Query1,szSQL,true);
	while(!dm1->Query1->Eof)
	{
		m_lstGACode.Add(dm1->Query1->FieldByName("ga_code")->AsString.c_str());
		m_lstGACorp.Add(dm1->Query1->FieldByName("ga_area")->AsString.c_str());
		lstGoodsAddr->Items->Add(dm1->Query1->FieldByName("ga_area")->AsString
			+dm1->Query1->FieldByName("ga_name")->AsString);
		dm1->Query1->Next();
	}

	szSQL="select * from DicUnits order by du_code";
	RunSQL(dm1->Query1,szSQL,true);
	while(!dm1->Query1->Eof)
	{
		m_lstUnitID.Add(dm1->Query1->FieldByName("du_code")->AsString.c_str());
		lstUnits->Items->Add(dm1->Query1->FieldByName("du_name")->AsString);
		dm1->Query1->Next();
	}


//------------------------------------------------------------------------------//0528
	szSQL="select distinct mn_code,mn_name from TreatStock,materialno"
		" where ts_mncode=mn_code order by mn_code";
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------//0528
/*
	szSQL="select distinct mn_code,mn_name from TreatStock,materialno"
		" where ts_mncode=mn_code order by mn_code";
*/
//------------------------------------------------------------------------------
	RunSQL(dm1->Query1,szSQL,true);
	while(!dm1->Query1->Eof)
	{
		sprintf(strTemp,"%-21s%s",
			dm1->Query1->FieldByName("mn_code")->AsString.c_str(),
			dm1->Query1->FieldByName("mn_name")->AsString.c_str());
		lstTreatView->Items->Add(strTemp);

		dm1->Query1->Next();
	}
	lstTreatView->Visible=false;


	m_enRegion=EN_REGION0;
	m_enState=EN_STATE_IDLE;
	ResetCtrl();

	if(!m_szIDFirst.IsEmpty())
	{
		edtMainID->Text=m_szIDFirst;
		btnQueryClick(Sender);
	}
}
//---------------------------------------------------------------------------


void TAskPurchaseForm::ResetAskDepart(bool bIdle)
{
	CString szSQL;
  AnsiString szSel0,szSel1;
	char strCorp[80];
	AnsiString szDep;
	int i;

  szSel0=lstDepAsk->Text;
  szSel1=lstDepCharge->Text;

	m_lstDepartID.RemoveAll();
	lstDepAsk		->Items->Clear();
	lstDepCharge->Items->Clear();

	szSQL.Format("select * from operator,DepartCorp where op_cpcode=substring(dc_code,1,1)"
		" and op_code='%s'",operatorcode.c_str());
  RunSQL(dm1->Query1,szSQL,true);
	strcpy(strCorp,dm1->Query1->FieldByName("op_cpcode")->AsString.c_str());
	if(strCorp[0]=='\0' || operatorcode=="admin" || bIdle)
  {
		szSQL="select * from DicDepart,DepartCorp where substring(dd_code,1,2)*=dc_code order by dd_code";
		RunSQL(dm1->Query1,szSQL,true);
		while(!dm1->Query1->Eof)
		{
			m_lstDepartID.Add(dm1->Query1->FieldByName("dd_code")->AsString.c_str());
			szDep=dm1->Query1->FieldByName("dc_name")->AsString+dm1->Query1->FieldByName("dd_name")->AsString;
			lstDepAsk		->Items->Add(szDep);
			lstDepCharge->Items->Add(szDep);
			dm1->Query1->Next();
		}
  }
  else
  {
		szSQL.Format("select * from DicDepart,DepartCorp where substring(dd_code,1,2)=dc_code"
      " and substring(dc_code,1,1)='%s'"
	    " order by dd_code",strCorp);
		RunSQL(dm1->Query1,szSQL,true);
		while(!dm1->Query1->Eof)
		{
			m_lstDepartID.Add(dm1->Query1->FieldByName("dd_code")->AsString.c_str());
			szDep=dm1->Query1->FieldByName("dc_name")->AsString+dm1->Query1->FieldByName("dd_name")->AsString;
			lstDepAsk		->Items->Add(szDep);
			lstDepCharge->Items->Add(szDep);
			dm1->Query1->Next();
		}
  }
	for(i=0;i<lstDepAsk->Items->Count;i++)
	{
		if(lstDepAsk->Items->Strings[i]==szSel0)
		{
			lstDepAsk->ItemIndex=i;
			break;
		}
	}
	if(i==lstDepAsk->Items->Count)	lstDepAsk->ItemIndex=-1;

	for(i=0;i<lstDepCharge->Items->Count;i++)
	{
		if(lstDepCharge->Items->Strings[i]==szSel1)
		{
			lstDepCharge->ItemIndex=i;
			break;
		}
	}
	if(i==lstDepCharge->Items->Count)	lstDepCharge->ItemIndex=-1;
}

void TAskPurchaseForm::ResetCtrl()
{
	bool bIdle,bAuth;

	bIdle = m_enState==EN_STATE_IDLE;
	bAuth = m_nAuthor==AUTH_FULL;

	EnableEdit(edtMnname			,false);
//	EnableCombo(lstUnits            ,false);                                
	EnableEdit(edtAfmDate			,false);
	EnableEdit(edtModifyDate	,false);
	EnableEdit(edtInpDate			,false);
	EnableEdit(edtEndFlag			,false);
  EnableEdit(edtPrnDate			,false);

	if(m_enRegion==EN_REGION0)
	{
		btnEdit->Enabled = bIdle && bAuth && !m_szActiveID.IsEmpty();
		btnMove->Enabled = bIdle && bAuth && !m_szActiveID.IsEmpty();

		EnableEdit(edtMainID		,m_enState!=EN_STATE_EDIT);
		EnableEdit(edtNeedDate	,!bIdle);
		EnableEdit(edtAskDate		,!bIdle);
		EnableEdit(edtProject		,!bIdle);
		EnableEdit(edtUsage			,!bIdle);
		EnableEdit(edtChkSpec		,!bIdle);
		EnableCombo(lstType			,!bIdle);
		EnableCombo(lstBuyType	,!bIdle);
		EnableCombo(lstDepAsk		,!bIdle);
//		if(m_bUnion && lstDepBuy->Text=="广州采购处")
//			EnableCombo(lstDepBuy		,false);
//		else
			EnableCombo(lstDepBuy		,!bIdle);
		EnableCombo(lstDepCharge,!bIdle);
		EnableCombo(lstGoodsAddr,!bIdle);
		EnableCombo(lstChkFlag	,!bIdle);
		EnableCombo(lstHandle		,!bIdle);
		if(m_bUnion)
			EnableCombo(lstTreatFlag,false);
		else
			EnableCombo(lstTreatFlag,m_enState==EN_STATE_NEW);

		EnableEdit(edtItem	,false);
		EnableEdit(edtMater	,false);
		EnableEdit(edtCount	,false);
		EnableEdit(edtCooper,false);
		EnableCombo(lstUnits,false);
		btnQueryMT->Enabled=false;
		EnableCombo(lstTreat,false);
		btnToTreat->Enabled=false;
	}
	else
	{
		btnEdit->Enabled = bIdle && bAuth && lstView->Selected!=NULL;
		btnMove->Enabled = bIdle && bAuth && lstView->Selected!=NULL;

		EnableEdit(edtMainID		,false);
		EnableEdit(edtNeedDate	,false);
		EnableEdit(edtAskDate		,false);
		EnableEdit(edtProject		,false);
		EnableEdit(edtUsage			,false);
		EnableEdit(edtChkSpec		,false);
		EnableCombo(lstType			,false);
		EnableCombo(lstBuyType	,false);
		EnableCombo(lstDepAsk		,false);
		EnableCombo(lstDepBuy		,false);
		EnableCombo(lstDepCharge,false);
		EnableCombo(lstGoodsAddr,false);
		EnableCombo(lstChkFlag	,false);
		EnableCombo(lstHandle		,false);
		EnableCombo(lstTreatFlag,false);

//		EnableEdit(edtItem			,m_enState==EN_STATE_NEW);
		EnableEdit(edtItem			,false);
		EnableEdit(edtMater			,!bIdle);
		EnableEdit(edtCount			,!bIdle);
		EnableEdit(edtCooper		,!bIdle);
		EnableCombo(lstUnits		,!bIdle && !m_bIsTreat);
		btnQueryMT->Enabled=!bIdle;

//		EnableEdit(edtType,false);
		EnableCombo(lstTreat,!bIdle);
		btnToTreat->Enabled=m_bIsTreat && lstTreat->ItemIndex>=0;
	}
	edtCooper	->Visible=!m_bIsTreat;
	txtCooper	->Visible=!m_bIsTreat;
	txtTreat	->Visible=m_bIsTreat;
	lstTreat	->Visible=m_bIsTreat;
	btnToTreat->Visible=m_bIsTreat;

	btnNew  ->Glyph= m_enState==EN_STATE_NEW  ? Image1->Picture->Bitmap:NULL;
	btnEdit ->Glyph= m_enState==EN_STATE_EDIT ? Image1->Picture->Bitmap:NULL;
	btnQuery->Glyph= m_enState==EN_STATE_IDLE ? Image1->Picture->Bitmap:NULL;
	btnReg0 ->Glyph= m_enRegion==EN_REGION0   ? Image1->Picture->Bitmap:NULL;
	btnReg1 ->Glyph= m_enRegion==EN_REGION1   ? Image1->Picture->Bitmap:NULL;

	lstView	->Enabled = bIdle;
	btnReg0	->Enabled = bIdle;
	btnReg1	->Enabled = bIdle && !m_szActiveID.IsEmpty();
	btnNew	->Enabled = bIdle && bAuth;
	btnQuery->Enabled = bIdle && bAuth;
	btnPrint->Enabled = bIdle && !m_szActiveID.IsEmpty();
	btnOK		->Enabled = !bIdle;
	btnExit ->Caption = bIdle ? "退    出" : "放    弃";
}

void __fastcall TAskPurchaseForm::FormKeyDown(TObject *Sender, WORD &Key,TShiftState Shift)
{
	if(Key==VK_RETURN)
	{
		if(m_enState==EN_STATE_IDLE && ActiveControl==edtMainID)
		{
			if(btnQuery->CanFocus())	btnQuery->SetFocus();
		}
		else if(ActiveControl==lstHandle || ActiveControl==edtCooper)
		{
			if(btnOK->CanFocus())	btnOK->SetFocus();
		}
    else if(ActiveControl==lstTreat)
		{
			if(btnOK->CanFocus())	btnOK->SetFocus();
		}
		else	KeyReturnHandle(ActiveControl);
	}
}
//---------------------------------------------------------------------------

void __fastcall TAskPurchaseForm::grpReg1Click(TObject *Sender)
{
	if(btnReg1->Enabled)
		btnReg1Click(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TAskPurchaseForm::lstViewClick(TObject *Sender)
{
	if(btnReg1->Enabled)
		btnReg1Click(Sender);
	else if(lstView->Selected==NULL)	ResetCtrl();
}
//---------------------------------------------------------------------------

void __fastcall TAskPurchaseForm::grpReg0Click(TObject *Sender)
{
	if(btnReg0->Enabled)
		btnReg0Click(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TAskPurchaseForm::btnReg0Click(TObject *Sender)
{
	m_enRegion=EN_REGION0;
	ResetCtrl();
}
//---------------------------------------------------------------------------

void __fastcall TAskPurchaseForm::btnReg1Click(TObject *Sender)
{
	m_enRegion=EN_REGION1;
	ResetCtrl();
}
//---------------------------------------------------------------------------

void __fastcall TAskPurchaseForm::btnQueryClick(TObject *Sender)
{
	CString szSQL;
	CAskPurchaseRow rwMain;
	CPurchaseDetailRow rwDetail;
	char strID[80];

	ResetAskDepart(true);

	m_lstDetail.RemoveAll();
	lstView->Items->Clear();

	edtMainID->Text=edtMainID->Text.Trim();
	if(edtMainID->Text.IsEmpty())
	{
		ShowMessage("请输入本单编号");
		if(edtMainID->CanFocus())	edtMainID->SetFocus();
		return;
	}
	strcpy(strID,edtMainID->Text.c_str());
	szSQL.Format("select * from AskPurchase where ap_code='%s'",strID);
	RunSQL(dm1->Query1,szSQL,true);
	if(dm1->Query1->Eof)
	{
		ShowMessage("没有该编号的请购单");
		if(edtMainID->CanFocus())	edtMainID->SetFocus();
		return;
	}
	rwMain.ReadFromDB(dm1->Query1);
	Row2Editor(rwMain);
	m_bIsTreat = rwMain.ap_treatflag[0]!='\0';

	szSQL.Format("select * from PurchaseDetail where pd_code like '%s_' order by pd_code",strID);
	RunSQL(dm1->Query2,szSQL,true);
	while(!dm1->Query2->Eof)
	{
		rwDetail.ReadFromDB(dm1->Query2);
		Row2List(rwDetail);
		dm1->Query2->Next();
	}
  
  m_szActiveID=rwMain.ap_code;
	m_rwMain=rwMain;
  ResetCtrl();
}
//---------------------------------------------------------------------------

void __fastcall TAskPurchaseForm::btnNewClick(TObject *Sender)
{
	char strItem[80],strTemp[256],cc;
	int i;
	TListItem *pItem;
  TDateTime tNow;
	CString szSQL;

  tNow=GetSysTime(false);

	if(m_enRegion==EN_REGION0)                                              // 上区
	{
		ResetAskDepart(false);
    
		m_lstDetail.RemoveAll();
		lstView->Items->Clear();

		edtMainID			->Text=(LPCSTR)GenerateID();

		edtAfmDate		->Text="";
		edtModifyDate	->Text="";
		edtInpDate		->Text="";
    edtPrnDate		->Text="";
//		edtNeedDate		->Text="";
		edtAskDate		->Text=(LPCSTR)Date2YYMMDD(tNow);
		edtProject		->Text="";
		edtUsage			->Text="";
		edtChkSpec		->Text="";

		lstType			->ItemIndex=0;
		lstBuyType	->ItemIndex=0;
//		lstDepAsk		->ItemIndex=0;
//		lstDepBuy		->ItemIndex=0;
//		lstDepCharge->ItemIndex=0;
//		lstGoodsAddr->ItemIndex=0;


		if(lstDepAsk->ItemIndex==-1)
		{
		  GetPrivateProfileString("ASKPURCHASE","DEPART_REQUEST","",strTemp,250,INI_FILE_NAME);
			if(strTemp[0]!='\0')
			{
				for(i=0;i<lstDepAsk->Items->Count;i++)
				{
					if(lstDepAsk->Items->Strings[i]==strTemp)
					{
						lstDepAsk->ItemIndex=i;
						break;
					}
				}
			}
		}
		if(lstDepCharge->ItemIndex==-1)
		{
		  GetPrivateProfileString("ASKPURCHASE","DEPART_CHARGE","",strTemp,250,INI_FILE_NAME);
			if(strTemp[0]!='\0')
			{
				for(i=0;i<lstDepCharge->Items->Count;i++)
				{
					if(lstDepCharge->Items->Strings[i]==strTemp)
					{
						lstDepCharge->ItemIndex=i;
						break;
					}
				}
			}
		}

		if(!operatorcode.IsEmpty())
		{
			szSQL.Format("select * from diccorp,operator where op_cpcode=cp_code"
				" and op_code='%s'",operatorcode.c_str());
			RunSQL(dm1->Query1,szSQL,true);
			strcpy(strTemp,dm1->Query1->FieldByName("cp_name")->AsString.c_str());
			for(i=0;i<m_lstGACorp.GetSize();i++)
			{
				if(strstr(strTemp,m_lstGACorp[i])!=NULL)
				{
					lstGoodsAddr->ItemIndex=i;
					break;
				}
			}
		}

		lstChkFlag	->ItemIndex=0;
		for(i=0;i<m_lstHandleID.GetSize();i++)
		{
			if(operatorcode==(LPCSTR)m_lstHandleID[i])
			{
				lstHandle->ItemIndex=i;
				break;
			}
		}
		if(i==m_lstHandleID.GetSize())	lstHandle->ItemIndex=0;
		lstTreatFlag->ItemIndex=0;
//---------------统购单---------------------------------------------------------
		if(m_bUnion)
		{ //统购单
			lstTreatFlag->ItemIndex=1;
			strcpy(strTemp,	edtMainID	->Text.c_str());
			strTemp[0]='Q';
			edtMainID->Text=strTemp;

			if(g_theOperator.op_cpcode[0]=='D')
			{ //若用户为宏铭，自动寻找宏铭管理课的采购部门
				for(i=0;i<m_lstStockDepID.GetSize();i++)
				{
					if(m_lstStockDepID[i]=="1" && i<lstDepBuy->Items->Count)
					{
						lstDepBuy->ItemIndex=i;
						break;
					}
				}
			}
			if(g_theOperator.op_cpcode[0]=='E')
			{ //若用户为宏信，自动寻找宏信管理课的采购部门
				for(i=0;i<m_lstStockDepID.GetSize();i++)
				{
					if(m_lstStockDepID[i]=="2" && i<lstDepBuy->Items->Count)
					{
						lstDepBuy->ItemIndex=i;
						break;
					}
				}
			}
			
//			for(i=0;i<m_lstStockDepID.GetSize();i++)
//			{
//				if(m_lstStockDepID[i]=="X" && i<lstDepBuy->Items->Count)
//				{
//					lstDepBuy->ItemIndex=i;
//					break;
//				}
//			}
		}
		if(edtMainID->CanFocus())	edtMainID->SetFocus();
	}
	else                                                                    //下区
	{
                edtMater->Text="";
                edtMnname->Text="";                
                lstUnits->Text="";
                
                int j=0;
		cc='1';
		while(true && j<5)
		{
			for(i=0;i<lstView->Items->Count;i++)
			{
				pItem=lstView->Items->Item[i];
				strcpy(strItem,pItem->Caption.c_str());
				if(cc==strItem[0])
				{
//                                	if(cc=='9')	cc='A';
                                        cc++;
					break;
				}
			}
			if(i==lstView->Items->Count)	break;                  //找不到
                        if(lstView->Items->Count>=5)
                        {
                                ShowMessage("请购单相次已满，如有需要，请另开请购单");
                                return;
                        }
                        j++;                        
		}
/*		while(true)
		{
			for(i=0;i<lstView->Items->Count;i++)
			{
				pItem=lstView->Items->Item[i];
				strcpy(strItem,pItem->Caption.c_str());
				if(cc==strItem[0])
				{
                                	if(cc=='9')	cc='A';
                                        else	cc++;
					break;
				}
			}
			if(i==lstView->Items->Count)	break;
		}       */
		strItem[0]=cc;
		strItem[1]='\0';

		edtItem		->Text=strItem;
		edtEndFlag->Text="";
		if(edtItem->CanFocus())	edtItem->SetFocus();
	}
	m_enState=EN_STATE_NEW;
	ResetCtrl();
}
//---------------------------------------------------------------------------

void __fastcall TAskPurchaseForm::btnEditClick(TObject *Sender)
{
	if(m_szActiveID.IsEmpty())	return;
	if(m_enRegion==EN_REGION0)
	{
		if(edtMainID->Text!=(LPCSTR)m_szActiveID)
		{
			ShowMessage("您输入的本单编号与当前查询的不同");
			return;
		}
		ResetAskDepart(false);
	}
	if(!edtAfmDate->Text.IsEmpty())
	{
		ShowMessage("该请购单已被接案，不能修改");
		return;
	}
//-------------------   0527 先开放一下权限　测试中-----------------------------
//------------------- 测试成功　------------------------------------------------

	if(operatorcode!=m_rwMain.ap_hmcode && operatorcode!="admin" && operatorcode!="108557")    //0527　　加强我自己的权限
	{
		ShowMessage("只有admin或请购经办人员自己才能修改请购单");
		return;
	}

//------------------------------------------------------------------------------
  if(m_enRegion==EN_REGION1)
	{
  	int nSel;
    TListItem *pItem;
    if((pItem=lstView->Selected)==NULL)	return;
    if((nSel=lstView->Items->IndexOf(pItem))<0 || nSel>=m_lstDetail.GetSize())	return;
		if(!edtEndFlag->Text.IsEmpty())
  	{
    	ShowMessage("该项次已经结案，不能修改");
      return;
    }
	}
	m_enState=EN_STATE_EDIT;
  ResetCtrl();
  if(edtNeedDate->CanFocus())	edtNeedDate->SetFocus();
}
//---------------------------------------------------------------------------

void __fastcall TAskPurchaseForm::btnMoveClick(TObject *Sender)
{
	TDateTime tTime;
	CString szSQL;
	TListItem *pItem;
	int nSel;

	if(m_szActiveID.IsEmpty())	return;
	if(m_enRegion==EN_REGION0)
	{
		if(edtMainID->Text!=(LPCSTR)m_szActiveID)
		{
			ShowMessage("您输入的本单编号与当前查询的不同");
			return;
		}
	}
	if(!edtAfmDate->Text.IsEmpty())
	{
		ShowMessage("该请购单已被接案，不能删除");
		return;
	}
//--------------0527　测试中　开放权限------------------------------------------
//--------------测试成功！------------------------------------------------------

	if(operatorcode!=m_rwMain.ap_hmcode && operatorcode!="admin")
	{
		ShowMessage("只有admin或请购经办人员自己才能修改请购单");
		return;
	}

//------------------------------------------------------------------------------
	if(m_enRegion==EN_REGION0)
	{
		if(lstView->Items->Count>0)
		{
			ShowMessage("下区还有数据，请把下区全部删除之後再删除上区");
			return;
		}
		if(Application->MessageBox("真要删除该请购单吗","警告",
			MB_YESNOCANCEL | MB_ICONQUESTION | MB_DEFBUTTON2)!=IDYES)	return;
		szSQL.Format("select * from AskPurchase where ap_code='%s'",m_szActiveID);
		RunSQL(dm1->Query1,szSQL,true);
		if(dm1->Query1->Eof)
		{
			ShowMessage("该请购单不存在，可能被其他人删除了");
			return;
		}
		if(m_rwMain.ap_opertime!=dm1->Query1->FieldByName("ap_opertime")->AsDateTime)
		{
			ShowMessage("该请购单数据已被其他人修改过，请重新查询");
			return;
		}
		szSQL.Format("delete AskPurchase where ap_code='%s'",m_szActiveID);
		if(!RunSQL(dm1->Query1,szSQL))	return;
		ShowMessage("已成功删除了该请购单");
		m_szActiveID="";
		ResetCtrl();
	}
	else
	{
		if((pItem=lstView->Selected)==NULL)	return;
		if((nSel=lstView->Items->IndexOf(pItem))<0 || nSel>=m_lstDetail.GetSize())	return;
		if(Application->MessageBox("真要删除选定的项次吗","警告",
			MB_YESNOCANCEL | MB_ICONQUESTION | MB_DEFBUTTON2)!=IDYES)	return;
		szSQL.Format("select * from PurchaseDetail where pd_code='%s'",m_lstDetail[nSel].pd_code);
		RunSQL(dm1->Query1,szSQL,true);
		if(dm1->Query1->Eof)
		{
			ShowMessage("没有该项次数据，可能是被其他人删除了");
			return;
		}
		if(m_lstDetail[nSel].pd_opertime!=dm1->Query1->FieldByName("pd_opertime")->AsDateTime)
		{
			ShowMessage("该项次数据已被其他人修改过，请重新查询");
			return;
		}
		szSQL.Format("delete PurchaseDetail where pd_code='%s'",m_lstDetail[nSel].pd_code);
		if(!RunSQL(dm1->Query1,szSQL))	return;
		lstView->Items->Delete(nSel);
		m_lstDetail.RemoveAt(nSel);
		ResetCtrl();
	}
}
//---------------------------------------------------------------------------

#include "PrnAskPurchase.h"
void __fastcall TAskPurchaseForm::btnPrintClick(TObject *Sender)
{
	char strDate[80],strTop[256],strLeft[256],strBottom[256];
  CString szSQL;
  CStringArray lstUsage,lstSpec;
	int nSel;

	if(m_szActiveID.IsEmpty())	return;

  szSQL.Format("select * from PurchaseDetail,DicUnits,materialno"
  	" where pd_ducode=du_code and pd_mncode*=mn_code"
    " and pd_code like '%s_'"
    " order by pd_code",m_szActiveID);
	if(!OpenQuery(dm1->sqlPrint,szSQL))	return;

  TPrnAskPurchaseForm *pPrn;
  pPrn=new TPrnAskPurchaseForm(this);
  assert(pPrn!=NULL);

  GetPrivateProfileString("APPRINTSETUP","TOPMARGIN" ,"",strTop ,250,INI_FILE_NAME);
  GetPrivateProfileString("APPRINTSETUP","BOTTOMMARGIN" ,"",strBottom ,250,INI_FILE_NAME);
  GetPrivateProfileString("APPRINTSETUP","LEFTMARGIN","",strLeft,250,INI_FILE_NAME);
	if(strTop[0]!='\0' && strLeft[0]!='\0')
  {
  	pPrn->PrnView->Page->TopMargin=atof(strTop);
  	pPrn->PrnView->Page->BottomMargin=atof(strBottom);
    pPrn->PrnView->Page->LeftMargin=atof(strLeft);
  }

  if(lstTreatFlag->ItemIndex==1)
  {
  	pPrn->txtTreat0->Caption="";
  	pPrn->txtTreat1->Caption="V";
    pPrn->txtCoopTitle->Caption="合约编号    单价";
  }
  else
	{
  	pPrn->txtTreat0->Caption="V";
    pPrn->txtTreat1->Caption="";
    pPrn->txtCoopTitle->Caption="厂商配合事项";
  }

  pPrn->Type->Caption=lstType->Text;
  strcpy(strDate,edtNeedDate->Text.c_str());
  pPrn->NeedDay->Caption	=strDate+6;  strDate[6]='\0';
  pPrn->NeedMonth->Caption=strDate+4;  strDate[4]='\0';
  pPrn->NeedYear->Caption	=strDate+2;

  strcpy(strDate,edtAskDate->Text.c_str());
  pPrn->ReqDay->Caption=strDate+6;			strDate[6]='\0';
  pPrn->ReqMonth->Caption=strDate+4;		strDate[4]='\0';
  pPrn->ReqYear->Caption=strDate+2;

	SplitStrToLines(edtUsage->Text.c_str(),36,lstUsage);
	SplitStrToLines(edtChkSpec->Text.c_str(),30,lstSpec);

  pPrn->BuyType->Caption		=lstBuyType->Text;
  pPrn->StockDep->Caption		=lstDepBuy->Text;
  pPrn->ChargeDep->Caption	=lstDepCharge->Text;
  pPrn->Project->Caption		=edtProject->Text;
  pPrn->MainID->Caption			=(LPCSTR)m_szActiveID;
  if(lstUsage.GetSize()>0)	pPrn->txtUsage0->Caption=(LPCSTR)lstUsage[0];
  else pPrn->txtUsage0->Caption="";
  if(lstUsage.GetSize()>1)	pPrn->txtUsage1->Caption=(LPCSTR)lstUsage[1];
  else pPrn->txtUsage1->Caption="";
	if(lstChkFlag->Text=="Y")
	{
		pPrn->ChkFlag->Caption="需要检验";
	  if(lstSpec.GetSize()>0)	pPrn->ChkSpec0->Caption=(LPCSTR)lstSpec[0];
		else pPrn->ChkSpec0->Caption="";
		if(lstSpec.GetSize()>1)	pPrn->ChkSpec1->Caption=(LPCSTR)lstSpec[1];
		else pPrn->ChkSpec1->Caption="";
	}
	else
	{
		pPrn->ChkFlag->Caption="不需要检验";
		pPrn->ChkSpec0->Caption="";
		pPrn->ChkSpec1->Caption="";
	}
  pPrn->GoodsAddr->Caption	=lstGoodsAddr->Text;
  pPrn->HandleMan->Caption	=lstHandle->Text;

	if((nSel=lstDepAsk->ItemIndex)>=0 && nSel<m_lstDepartID.GetSize())
	{
		szSQL.Format("select * from DicDepart,DepartCorp"
			" where substring(dd_code,1,2)*=dc_code and dd_code='%s'",m_lstDepartID[lstDepAsk->ItemIndex]);
		RunSQL(dm1->Query1,szSQL,true);
		if(!dm1->Query1->Eof)
		{
			pPrn->ReqCorp->Caption=dm1->Query1->FieldByName("dc_name")->AsString;
			pPrn->ReqDepart->Caption=dm1->Query1->FieldByName("dd_name")->AsString;
		}
	}
  pPrn->txtTel->Caption="";
  if(m_rwMain.ap_hmcode[0]!='\0')
  {
	  szSQL.Format("select * from HandleMan where hm_code='%s'",m_rwMain.ap_hmcode);
		RunSQL(dm1->Query1,szSQL,true);
    if(!dm1->Query1->Eof)
    {
    	pPrn->txtTel->Caption=dm1->Query1->FieldByName("hm_tel")->AsString;
    }
  }

/*
TPrinter *pnt = Printer();
int xInch=GetDeviceCaps(pnt->Handle,LOGPIXELSX);//1Inch=25.4mm
int yInch=GetDeviceCaps(pnt->Handle,LOGPIXELSY);
float xMM,yMM;//x,y方向1厘米的??
xMM=(float)xInch/25.4;
yMM=(float)yInch/25.4;

//?置??大小

char Device[CCHDEVICENAME];
char Driver[MAX_PATH];
char Port[32];
THandle  hDMode;
PDevMode  pDMode;
pnt->GetPrinter(Device,Driver,Port,hDMode);
pDMode=(PDevMode)GlobalLock((HGLOBAL &)hDMode);

pDMode->dmPaperSize= 256;    //自定?
pDMode->dmFields=pDMode->dmFields|DM_PAPERSIZE;

pDMode->dmPaperLength =2035;  //高：4英寸=101.6mm
pDMode->dmFields =pDMode->dmFields|DM_PAPERLENGTH;

pDMode->dmPaperWidth = 2970;  //?：10英寸=25.40mm
pDMode->dmFields =pDMode->dmFields|DM_PAPERWIDTH;

ResetDC(pnt->Handle,pDMode);
GlobalUnlock((HGLOBAL &)hDMode);
pnt->Refresh();
*/
	pPrn->PrnView->PreviewModal();
  delete pPrn;

  TDateTime tNow=GetSysTime(false);
	m_rwMain.SetMemberNotNULL(&m_rwMain.ap_printdate);
	m_rwMain.ap_printdate=tNow;
	szSQL.Format("update AskPurchase set ap_printdate=%s where ap_code='%s'",
		m_rwMain.Member2DBString(m_rwMain.ap_printdate,false),m_rwMain.ap_code);
	RunSQL(dm1->Query1,szSQL);
	edtPrnDate->Text=(LPCSTR)Date2YYMMDD(tNow);
}

//---------------new 0526-------------------------------------------------------

void __fastcall TAskPurchaseForm::btnOKClick(TObject *Sender)
{
	CAskPurchaseRow rwMain;
	CPurchaseDetailRow rwDetail;
	int nSel;
	TListItem *pItem;
//--------------新旧编号合法性验证----------------------------------------------
        CString szSQL;
        char strID[80];
        sprintf(strID,"%s",edtMater->Text.c_str());


        szSQL.Format("select * from codecheck where cc_ocode=%s",Str2DBString(strID));
        RunSQL(dm1->Query1,szSQL,true);
	if(!dm1->Query1->Eof)
	{
                ShowMessage("抱歉！该编号已被停用，请查找同一品名规格的并且以A开头的编号");
		return;
	}
//------------------------------------------------------------------------------

	if(m_enRegion==EN_REGION0)
	{
		rwMain=m_rwMain;
		if(!CheckRegion0())	return;

		if(m_enState==EN_STATE_NEW)
		{
			Editor2Row(rwMain,true);
			OnRegion0New(rwMain);
		}
		else if(m_enState==EN_STATE_EDIT)
		{
			Editor2Row(rwMain,false);
			OnRegion0Edit(rwMain);
		}
	} //if(m_enRegion==EN_REGION0)
	else if(m_enRegion==EN_REGION1)
	{
		if(!CheckRegion1())	return;
		if(m_enState==EN_STATE_NEW)
		{
			Editor2Row(rwDetail,true);
			OnRegion1New(rwDetail);
		}
		else
		{
			if((pItem=lstView->Selected)==NULL)	return;
			if((nSel=lstView->Items->IndexOf(pItem))<0 || nSel>=m_lstDetail.GetSize())	return;
			rwDetail=m_lstDetail[nSel];
			Editor2Row(rwDetail,false);
			OnRegion1Edit(rwDetail);
		}
	}
}

//---------------------------------------------------------------------------


//------------------------------------------------------------------------------
/*
void __fastcall TAskPurchaseForm::btnOKClick(TObject *Sender)
{
	CAskPurchaseRow rwMain;
	CPurchaseDetailRow rwDetail;
	int nSel;
	TListItem *pItem;

	if(m_enRegion==EN_REGION0)
	{
		rwMain=m_rwMain;
		if(!CheckRegion0())	return;

		if(m_enState==EN_STATE_NEW)
		{
			Editor2Row(rwMain,true);
			OnRegion0New(rwMain);
		}
		else if(m_enState==EN_STATE_EDIT)
		{
			Editor2Row(rwMain,false);
			OnRegion0Edit(rwMain);
		}
	} //if(m_enRegion==EN_REGION0)
	else if(m_enRegion==EN_REGION1)
	{
		if(!CheckRegion1())	return;
		if(m_enState==EN_STATE_NEW)
		{
			Editor2Row(rwDetail,true);
			OnRegion1New(rwDetail);
		}
		else
		{
			if((pItem=lstView->Selected)==NULL)	return;
			if((nSel=lstView->Items->IndexOf(pItem))<0 || nSel>=m_lstDetail.GetSize())	return;
			rwDetail=m_lstDetail[nSel];
			Editor2Row(rwDetail,false);
			OnRegion1Edit(rwDetail);
		}
	}
}
*/
//---------------------------------------------------------------------------

bool TAskPurchaseForm::CheckRegion1()
{
	CString szSQL;
	int nSel;
	TDateTime tTime;
	TListItem *pItem;
  char strCorp[80],strTemp[256];

	if(m_szActiveID.IsEmpty())	return false;

	edtItem->Text=edtItem->Text.Trim();
	if(edtItem->Text.IsEmpty())
	{
		ShowMessage("项次不能为空");
		if(edtItem->CanFocus())	edtItem->SetFocus();
		return false;
	}
	szSQL.Format("select * from PurchaseDetail where pd_code='%s%s'",m_szActiveID,edtItem->Text.c_str());
	RunSQL(dm1->Query1,szSQL,true);
	if(m_enState==EN_STATE_NEW)
	{
		if(!dm1->Query1->Eof)
		{
			ShowMessage("数据库中已有该项次");
			if(edtItem->CanFocus())	edtItem->SetFocus();
			return false;
		}
	}
	else
	{
		if((pItem=lstView->Selected)==NULL)	return false;
		if((nSel=lstView->Items->IndexOf(pItem))<0 || nSel>=m_lstDetail.GetSize())	return false;

		if(dm1->Query1->Eof)
		{
			ShowMessage("数据库中没有该项次，也许是被其他人删除了");
			return false;
		}
		if(m_lstDetail[nSel].pd_opertime!=dm1->Query1->FieldByName("pd_opertime")->AsDateTime)
		{
			ShowMessage("该项次已被其他人修改过，请重新查询");
			return false;
		}
	}

	edtMater->Text=edtMater->Text.Trim();
	if(edtMater->Text.IsEmpty())
	{
		ShowMessage("请输入材料编号");
		if(edtMater->CanFocus())	edtMater->SetFocus();
		return false;
	}
	szSQL.Format("select * from materialno where mn_code='%s'",edtMater->Text.c_str());
	RunSQL(dm1->Query1,szSQL,true);
	if(dm1->Query1->Eof)
	{
		ShowMessage("没有该材料编号");
		return false;
	}
	szSQL.Format("select * from TreatStock where ts_mncode='%s'",edtMater->Text.c_str());
	RunSQL(dm1->Query1,szSQL,true);
	if(lstTreatFlag->ItemIndex==1)
	{
		if(dm1->Query1->Eof)
		{
			ShowMessage("合约采购档中没有该材料编号");
			return false;
		}
	}
	else
	{
		if(!dm1->Query1->Eof)
		{
			ShowMessage("合约采购档中有该材料编号，请另开一个合约采购的请购单");
			return false;
		}
	}
	if(m_bUnion)
	{
		strcpy(strCorp,edtMater->Text.c_str());
		if(strCorp[0]!='A')
		{
    	ShowMessage("统购单材料编号第一个字母必须为“A”");
			if(edtMater->CanFocus())	edtMater->SetFocus();
			return false;
		}
	}
	else
	{
		if((nSel=lstDepAsk->ItemIndex)>=0 && nSel<m_lstDepartID.GetSize())
		{
  		strcpy(strCorp,edtMater->Text.c_str());
			strcpy(strTemp,m_lstDepartID[nSel]);

                    if(strTemp[0]=='B')
                      {
                        if(strCorp[0]!='A'&& strCorp[0]!='B')
                          {
                            ShowMessage("只能选字母“A”开头或“B”开头的材料编号");
                            if(edtMater->CanFocus())   edtMater->SetFocus();
                            return false;
                          }
                      }
//---------------new　0527　开放其他公司使用A开头编号的权限---------------------
//------------------------------------------------------------------------------
       


                    else
                      {
                        char strCorp[80];
                        strcpy(strCorp,edtMater->Text.c_str());

			if(strCorp[0]!=strTemp[0] && strCorp[0]!='A')           // strCorp[0]!='A'  A开头的编号一定可用
  		          {
    		               ShowMessage("请购部门与材料编号必须为同一公司");
				if(edtMater->CanFocus())	edtMater->SetFocus();
				return false;
			}
                      }

//------------------------------------------------------------------------------


//------------------原有程序是没有括的------------------------------------------
/*                    else
                      {
			if(strCorp[0]!=strTemp[0])
  		          {
    		               ShowMessage("请购部门与材料编号必须为同一公司");
				if(edtMater->CanFocus())	edtMater->SetFocus();
				return false;
			}
                      }
*/
//------------------------------------------------------------------------------
                }
	}

	if(lstUnits->ItemIndex<0)
	{
		ShowMessage("请选择一个有效的单位");
		if(lstUnits->CanFocus())	lstUnits->SetFocus();
		return false;
	}

	edtCount->Text=edtCount->Text.Trim();
	if(edtCount->Text.IsEmpty())
	{
		ShowMessage("请输入数量");
		if(edtCount->CanFocus())	edtCount->SetFocus();
		return false;
	}
	if(!StringIsFloat(edtCount->Text.c_str()))
	{
		ShowMessage("请输入数字");
		if(edtCount->CanFocus())	edtCount->SetFocus();
		return false;
	}

	edtCooper->Text=edtCooper->Text.Trim();

	if(m_bIsTreat && (nSel=lstTreat->ItemIndex)>=0 && nSel<m_lstTreatID.GetSize())
	{
		szSQL.Format("select * from TreatStock where ts_code='%s'",m_lstTreatID[nSel]);
		RunSQL(dm1->Query1,szSQL,true);
		if(dm1->Query1->FieldByName("ts_afmdate")->IsNull || dm1->Query1->FieldByName("ts_afmdate2")->IsNull)
		{
			ShowMessage("您选定的合约采购还没有采购确认或会计确认");
			return false;
		}		
	}

	return true;
}

void TAskPurchaseForm::OnRegion1New(CPurchaseDetailRow &row)
{
	CString szSQL;

	szSQL="insert into PurchaseDetail (pd_code,pd_mncode,pd_ducode,pd_count,pd_cooper,pd_tscode,pd_endflag,pd_opertime"
		") values(";
	szSQL+=row.Member2DBString(row.pd_code);
	szSQL+=",";	szSQL+=row.Member2DBString(row.pd_mncode);
	szSQL+=",";	szSQL+=row.Member2DBString(row.pd_ducode);
	szSQL+=",";	szSQL+=row.Member2DBString(row.pd_count,2);
	szSQL+=",";	szSQL+=row.Member2DBString(row.pd_cooper);
	szSQL+=",";	szSQL+=row.Member2DBString(row.pd_tscode);
	szSQL+=",";	szSQL+=row.Member2DBString(row.pd_endflag);
	szSQL+=",";	szSQL+=row.Member2DBString(row.pd_opertime,false);
	szSQL+=")";
	if(!RunSQL(dm1->Query1,szSQL))	return;

	Row2List(row);
	if(lstView->Items->Count>0)
		lstView->Selected=lstView->Items->Item[lstView->Items->Count-1];

	m_enState=EN_STATE_IDLE;
	ResetCtrl();
	if(btnNew->CanFocus())	btnNew->SetFocus();
}

void TAskPurchaseForm::OnRegion1Edit(CPurchaseDetailRow &row)
{
	CString szSQL;

	szSQL="update PurchaseDetail set";
	szSQL+=" pd_mncode=";			szSQL+=row.Member2DBString(row.pd_mncode);
	szSQL+=",pd_ducode=";			szSQL+=row.Member2DBString(row.pd_ducode);
	szSQL+=",pd_count=";			szSQL+=row.Member2DBString(row.pd_count,2);
	szSQL+=",pd_cooper=";			szSQL+=row.Member2DBString(row.pd_cooper);
	szSQL+=",pd_tscode=";			szSQL+=row.Member2DBString(row.pd_tscode);
	szSQL+=",pd_endflag=";		szSQL+=row.Member2DBString(row.pd_endflag);
	szSQL+=",pd_opertime=";		szSQL+=row.Member2DBString(row.pd_opertime,false);
	szSQL+=" where pd_code=";	szSQL+=row.Member2DBString(row.pd_code);
	if(!RunSQL(dm1->Query1,szSQL))	return;

	Row2List(row);

	m_enState=EN_STATE_IDLE;
	ResetCtrl();
	if(btnEdit->CanFocus())	btnEdit->SetFocus();
}

void TAskPurchaseForm::Row2List(CPurchaseDetailRow &row)
{
	TListItem *pItem;
	int i;
	AnsiString szUnit;
	char strName[256],strCooper[80];
	CString szSQL;

	strName[0]='\0';
	if(row.pd_mncode[0]!='\0')
	{
		szSQL.Format("select * from materialno where mn_code='%s'",row.pd_mncode);
		RunSQL(dm1->Query1,szSQL,true);
		if(!dm1->Query1->Eof)
		{
			strcpy(strName,dm1->Query1->FieldByName("mn_name")->AsString.c_str());
		}
	}
	for(i=0;i<m_lstUnitID.GetSize();i++)
	{
		if(m_lstUnitID[i]==row.pd_ducode)
		{
			szUnit=lstUnits->Items->Strings[i];
			break;
		}
	}

	for(i=0;i<lstView->Items->Count;i++)
	{
		pItem=lstView->Items->Item[i];
		if(pItem->Caption==(LPCSTR)row.GetItem())
			break;
	}
	strCooper[0]='\0';
	if(m_bIsTreat && row.pd_tscode[0]!='\0')
	{
		szSQL.Format("select * from TreatStock,Manufactur where mf_code=ts_mfcode and ts_code='%s'",row.pd_tscode);
		RunSQL(dm1->Query1,szSQL,true);
		if(!dm1->Query1->Eof)
			strcpy(strCooper,dm1->Query1->FieldByName("mf_shortname")->AsString.c_str());
	}
	else
		strcpy(strCooper,row.pd_cooper);
		
	if(i==lstView->Items->Count)
	{ //add new item
		m_lstDetail.Add(row);
		pItem=lstView->Items->Add();
		assert(pItem!=NULL);
		pItem->Caption=(LPCSTR)row.GetItem();
		pItem->SubItems->Add(row.pd_mncode);
		pItem->SubItems->Add(strName);
		pItem->SubItems->Add(szUnit);
		pItem->SubItems->Add((LPCSTR)row.Member2String(row.pd_count,2));
		pItem->SubItems->Add(strCooper);
		pItem->SubItems->Add(row.pd_endflag);
	}
	else
	{
		m_lstDetail[i]=row;
		pItem->SubItems->Strings[0]=row.pd_mncode;
		pItem->SubItems->Strings[1]=strName;
		pItem->SubItems->Strings[2]=szUnit;
		pItem->SubItems->Strings[3]=(LPCSTR)row.Member2String(row.pd_count,2);
		pItem->SubItems->Strings[4]=strCooper;
		pItem->SubItems->Strings[5]=row.pd_endflag;
	}
}

bool TAskPurchaseForm::CheckRegion0()
{
	CString szSQL;
	char strDate[80],strTemp[80],strDep0[80],strDep1[80];
	TDateTime tTime,tTmp;
	int nSel;

	if(m_enState==EN_STATE_NEW)
	{
		edtMainID->Text=edtMainID->Text.Trim();
		if(edtMainID->Text.Length()!=7)
		{
			ShowMessage("请输入7位本单编号");
			if(edtMainID->CanFocus())	edtMainID->SetFocus();
			return false;
		}
	}
	if(m_enState==EN_STATE_NEW)
	{
		strcpy(strTemp,edtMainID->Text.c_str());
		if(lstTreatFlag->ItemIndex==1)
			strTemp[0]='Q';
		else
			strTemp[0]='P';
		edtMainID->Text=strTemp;

		szSQL.Format("select * from AskPurchase where ap_code='%s'",edtMainID->Text.c_str());
		RunSQL(dm1->Query1,szSQL,true);
		if(!dm1->Query1->Eof)
		{
			ShowMessage("数据库中已有该编号的请购单");
			if(edtMainID->CanFocus())	edtMainID->SetFocus();
			return false;
		}
	}
	else if(m_enState==EN_STATE_EDIT)
	{
		if(m_szActiveID.IsEmpty())	return false;
		if(edtMainID->Text!=(LPCSTR)m_szActiveID)
		{
			ShowMessage("您输入的本单编号与当前查询的不同");
			return false;
		}
		szSQL.Format("select * from AskPurchase where ap_code='%s'",edtMainID->Text.c_str());
		RunSQL(dm1->Query1,szSQL,true);
		if(dm1->Query1->Eof)
		{
			ShowMessage("数据库中没有该编号的请购单，可能是其他人删除了，请重新查询");
			return false;
		}
		tTime=dm1->Query1->FieldByName("ap_opertime")->AsDateTime;
		if(tTime!=m_rwMain.ap_opertime)
		{
			ShowMessage("该请购单的内容已被其他人修改过了，请重新查询");
			return false;
		}
		if( (lstTreatFlag->ItemIndex==0 && m_rwMain.ap_treatflag[0]!='\0')
			|| (lstTreatFlag->ItemIndex==1 && m_rwMain.ap_treatflag[0]=='\0'))
		{
			if(lstView->Items->Count>0)
			{
				ShowMessage("下区还有内容时不能更改采购类别");
				return false;
			}
		}
	}

	edtNeedDate->Text=edtNeedDate->Text.Trim();
	if(edtNeedDate->Text.Length()!=8)
	{
		ShowMessage("请输入8位日期数据，格式：yyyymmdd");
		if(edtNeedDate->CanFocus())	edtNeedDate->SetFocus();
		return false;
	}
	strcpy(strDate,edtNeedDate->Text.c_str());
	try
	{
		tTmp=YYMMDD2Date(strDate);
	}
	catch(...)
	{
		ShowMessage("请输入有效的日期数据，格式：yyyymmdd");
		if(edtNeedDate->CanFocus())	edtNeedDate->SetFocus();
		return false;
	}

	edtAskDate->Text=edtAskDate->Text.Trim();
	if(edtAskDate->Text.Length()!=8)
	{
		ShowMessage("请输入8位日期数据，格式：yyyymmdd");
		if(edtAskDate->CanFocus())	edtAskDate->SetFocus();
		return false;
	}
	strcpy(strDate,edtAskDate->Text.c_str());
	try
	{
		tTmp=YYMMDD2Date(strDate);
	}
	catch(...)
	{
		ShowMessage("请输入有效的日期数据，格式：yyyymmdd");
		if(edtAskDate->CanFocus())	edtAskDate->SetFocus();
		return false;
	}

	if(lstType->ItemIndex<0)
	{
		ShowMessage("请选择有效的案件类别");
		return false;
	}
	if(lstBuyType->ItemIndex<0)
	{
		ShowMessage("请选择有效的采购别");
		return false;
	}
	if((nSel=lstDepAsk->ItemIndex)<0 || nSel>=m_lstDepartID.GetSize())
	{
		ShowMessage("请选择有效的请购部门");
		return false;
	}
	if((nSel=lstDepBuy->ItemIndex)<0 || nSel>=m_lstStockDepID.GetSize())
	{
		ShowMessage("请选择有效的采购部门");
		return false;
	}
	if((nSel=lstDepCharge->ItemIndex)<0 || nSel>=m_lstDepartID.GetSize())
	{
		ShowMessage("请选择有效的成本负担部门");
		return false;
	}
  strcpy(strDep0,m_lstDepartID[lstDepAsk->ItemIndex]);
  strcpy(strDep1,m_lstDepartID[lstDepCharge->ItemIndex]);
  if(strDep0[0]!=strDep1[0] || strDep0[1]!=strDep1[1])
  {
  	ShowMessage("请购部门与成品负担部门的公司必须一致");
    return false;
  }
	strcpy(strTemp,m_lstStockDepID[lstDepBuy->ItemIndex]);
/*	if( (strDep0[0]=='D' && strTemp[0]=='2') || (strDep0[0]=='E' && strTemp[0]=='1'))
	{
		ShowMessage("请购部门与采购部门不匹配，请检查");
		return false;
	}       */
	if(lstGoodsAddr->ItemIndex<0)
	{
		ShowMessage("请选择有效的交货地址");
		return false;
	}
	if(lstChkFlag->ItemIndex<0)
	{
		ShowMessage("请选择有效的检验注记");
		return false;
	}
	if((nSel=lstHandle->ItemIndex)<0 || nSel>=m_lstHandleID.GetSize())
	{
		ShowMessage("请选择有效的经办人员");
		return false;
	}

	szSQL.Format("select * from operator where op_code='%s'",m_lstHandleID[nSel]);
	RunSQL(dm1->Query1,szSQL,true);
	if(!dm1->Query1->Eof)
	{
		strcpy(strTemp,dm1->Query1->FieldByName("op_cpcode")->AsString.c_str());
		if(strTemp[0]!=m_lstDepartID[lstDepAsk->ItemIndex][0])
		{
			ShowMessage("请购经办与请购部门的公司别不相同");
			return false;
		}
	}

	edtProject->Text=edtProject	->Text.Trim();
	edtUsage	->Text=edtUsage		->Text.Trim();
  if(edtUsage->Text.IsEmpty())
  {
  	ShowMessage("请输入用途");
    if(edtUsage->CanFocus())	edtUsage->SetFocus();
    return false;
  }
	edtChkSpec->Text=edtChkSpec	->Text.Trim();

	return true;
}


void TAskPurchaseForm::OnRegion0Edit(CAskPurchaseRow &row)
{
	CString szSQL;

	szSQL="update AskPurchase set";
	szSQL+=" ap_needdate=";		szSQL+=row.Member2DBString(row.ap_needdate);
	szSQL+=",ap_type=";				szSQL+=row.Member2DBString(row.ap_type);
	szSQL+=",ap_reqdate=";		szSQL+=row.Member2DBString(row.ap_reqdate);
	szSQL+=",ap_buytype=";		szSQL+=row.Member2DBString(row.ap_buytype);
	szSQL+=",ap_reqdepart=";	szSQL+=row.Member2DBString(row.ap_reqdepart);
	szSQL+=",ap_sdcode=";			szSQL+=row.Member2DBString(row.ap_sdcode);
	szSQL+=",ap_chargedep=";	szSQL+=row.Member2DBString(row.ap_chargedep);
	szSQL+=",ap_prjcode=";		szSQL+=row.Member2DBString(row.ap_prjcode);
	szSQL+=",ap_usage=";			szSQL+=row.Member2DBString(row.ap_usage);
	szSQL+=",ap_gacode=";			szSQL+=row.Member2DBString(row.ap_gacode);
	szSQL+=",ap_chkflag=";		szSQL+=row.Member2DBString(row.ap_chkflag);
	szSQL+=",ap_chkspec=";		szSQL+=row.Member2DBString(row.ap_chkspec);
	szSQL+=",ap_hmcode=";			szSQL+=row.Member2DBString(row.ap_hmcode);
	szSQL+=",ap_treatflag=";	szSQL+=row.Member2DBString(row.ap_treatflag);
	szSQL+=",ap_opertime=";		szSQL+=row.Member2DBString(row.ap_opertime,false);
	szSQL+=" where ap_code=";	szSQL+=row.Member2DBString(row.ap_code);
	if(!RunSQL(dm1->Query1,szSQL))	return;

	m_rwMain=row;
	m_bIsTreat = row.ap_treatflag[0]!='\0';
//	m_tMainOperTime=row.ap_opertime;
	m_enState=EN_STATE_IDLE;
	ResetCtrl();
}

void TAskPurchaseForm::OnRegion0New(CAskPurchaseRow &row)
{
	CString szSQL;

	szSQL="insert into AskPurchase(ap_code,ap_needdate,ap_type,ap_reqdate,ap_buytype,"
		"ap_reqdepart,ap_sdcode,ap_chargedep,ap_prjcode,ap_usage,ap_gacode,ap_chkflag,"
		"ap_chkspec,ap_hmcode,ap_shcode,ap_treatflag,ap_affirmdate,ap_modifydate,ap_inputdate,"
		"ap_printdate,ap_opertime"
		") values(";
	szSQL+=row.Member2DBString(row.ap_code);
	szSQL+=",";	szSQL+=row.Member2DBString(row.ap_needdate);
	szSQL+=",";	szSQL+=row.Member2DBString(row.ap_type);
	szSQL+=",";	szSQL+=row.Member2DBString(row.ap_reqdate);
	szSQL+=",";	szSQL+=row.Member2DBString(row.ap_buytype);
	szSQL+=",";	szSQL+=row.Member2DBString(row.ap_reqdepart);
	szSQL+=",";	szSQL+=row.Member2DBString(row.ap_sdcode);
	szSQL+=",";	szSQL+=row.Member2DBString(row.ap_chargedep);
	szSQL+=",";	szSQL+=row.Member2DBString(row.ap_prjcode);
	szSQL+=",";	szSQL+=row.Member2DBString(row.ap_usage);
	szSQL+=",";	szSQL+=row.Member2DBString(row.ap_gacode);
	szSQL+=",";	szSQL+=row.Member2DBString(row.ap_chkflag);
	szSQL+=",";	szSQL+=row.Member2DBString(row.ap_chkspec);
	szSQL+=",";	szSQL+=row.Member2DBString(row.ap_hmcode);
	szSQL+=",NULL";
	szSQL+=",";	szSQL+=row.Member2DBString(row.ap_treatflag);
	szSQL+=",NULL";	//ap_affirmdate);
	szSQL+=",NULL";//ap_modifydate);
	szSQL+=",";	szSQL+=row.Member2DBString(row.ap_inputdate);
	szSQL+=",NULL"; //ap_printdate
	szSQL+=",";	szSQL+=row.Member2DBString(row.ap_opertime,false);
	szSQL+=")";
	if(!RunSQL(dm1->Query1,szSQL))	return;

	edtInpDate->Text=MEMBER2STRING(row,ap_inputdate);
	row.SetMemberNULL(row.ap_printdate);
	m_rwMain=row;
	m_bIsTreat = row.ap_treatflag[0]!='\0';

	m_szActiveID=row.ap_code;
	m_enState=EN_STATE_IDLE;	
	ResetCtrl();

	WritePrivateProfileString("ASKPURCHASE","DEPART_REQUEST",lstDepAsk		->Text.c_str(),INI_FILE_NAME);
	WritePrivateProfileString("ASKPURCHASE","DEPART_CHARGE" ,lstDepCharge	->Text.c_str(),INI_FILE_NAME);
}

void TAskPurchaseForm::Editor2Row(CAskPurchaseRow &row,bool bNew)
{
	TDateTime tNow;
	int i,nSel;

	tNow=GetSysTime(false);
  if(bNew)	row.SetAllMemberNULL(false);

	strcpy(row.ap_code		,edtMainID		->Text.c_str());
	strcpy(row.ap_prjcode	,edtProject		->Text.c_str());
	strcpy(row.ap_usage		,edtUsage			->Text.c_str());
	strcpy(row.ap_chkspec	,edtChkSpec		->Text.c_str());
	row.ap_needdate	=YYMMDD2Date(edtNeedDate->Text.c_str());
	row.ap_reqdate	=YYMMDD2Date(edtAskDate	->Text.c_str());
	row.ap_opertime=tNow;
	if(bNew)	row.ap_inputdate=tNow;

	strcpy(row.ap_type		,lstType->Text=="一般" ? "N" : "I");
//	strcpy(row.ap_buytype	,lstBuyType->Text=="内购" ? "M" : "N");
  if(lstBuyType->Text=="内购")  strcpy(row.ap_buytype,"M");
  if(lstBuyType->Text=="外购")  strcpy(row.ap_buytype,"N");
  if(lstBuyType->Text=="核销")  strcpy(row.ap_buytype,"H");

	strcpy(row.ap_chkflag	,lstChkFlag->Text.c_str());

	strcpy(row.ap_hmcode		,m_lstHandleID[lstHandle		->ItemIndex]);
	strcpy(row.ap_reqdepart	,m_lstDepartID[lstDepAsk		->ItemIndex]);
	strcpy(row.ap_chargedep	,m_lstDepartID[lstDepCharge	->ItemIndex]);
	strcpy(row.ap_sdcode		,m_lstStockDepID[lstDepBuy	->ItemIndex]);
	strcpy(row.ap_gacode		,m_lstGACode[lstGoodsAddr		->ItemIndex]);
	if(lstTreatFlag->ItemIndex==1)	row.SetMemberVal(row.ap_treatflag,"Y");
	else	row.ap_treatflag[0]='\0';
	
	if(!row.MemberIsNull(row.ap_modifydate))	row.ap_modifydate=tNow;
}

void TAskPurchaseForm::Editor2Row(CPurchaseDetailRow &row,bool bNew)
{
	TDateTime tNow;
	int nSel;

	tNow=GetSysTime(false);
  if(bNew)	row.SetAllMemberNULL(false);

	sprintf(row.pd_code,"%s%s",m_szActiveID,edtItem->Text.c_str());
	strcpy(row.pd_mncode	,edtMater		->Text.c_str());
	strcpy(row.pd_cooper	,edtCooper	->Text.c_str());
	strcpy(row.pd_endflag	,edtEndFlag	->Text.c_str());
	strcpy(row.pd_ducode	,m_lstUnitID[lstUnits->ItemIndex]);
	row.String2Member(row.pd_count,edtCount->Text.c_str());
	if(m_bIsTreat && (nSel=lstTreat->ItemIndex)>=0 && nSel<m_lstTreatID.GetSize())
		strcpy(row.pd_tscode,m_lstTreatID[nSel]);
	else	row.pd_tscode[0]='\0';

	row.pd_opertime=tNow;
}

void TAskPurchaseForm::Row2Editor(CAskPurchaseRow &row)
{
	int i;
  
	edtMainID			->Text=MEMBER2STRING(row,ap_code);
	edtNeedDate		->Text=MEMBER2STRING(row,ap_needdate);
	edtAskDate		->Text=MEMBER2STRING(row,ap_reqdate);
	edtProject		->Text=MEMBER2STRING(row,ap_prjcode);	
	edtUsage			->Text=MEMBER2STRING(row,ap_usage);
	edtChkSpec		->Text=MEMBER2STRING(row,ap_chkspec);
	edtAfmDate		->Text=MEMBER2STRING(row,ap_affirmdate);
	edtModifyDate	->Text=MEMBER2STRING(row,ap_modifydate);
	edtInpDate		->Text=MEMBER2STRING(row,ap_inputdate);
  edtPrnDate		->Text=MEMBER2STRING(row,ap_printdate);

	lstType		->ItemIndex=row.ap_type[0]=='N' ? 0 : 1;
//	lstBuyType->ItemIndex=row.ap_buytype[0]=='M' ? 0 : 1;
  if(row.ap_buytype[0]=='M')
    lstBuyType->ItemIndex=0;
  else if(row.ap_buytype[0]=='N')
    lstBuyType->ItemIndex=1;
  else if(row.ap_buytype[0]=='H')
    lstBuyType->ItemIndex=2;

	lstChkFlag->ItemIndex=row.ap_chkflag[0]=='Y' ? 0 : 1;
	lstTreatFlag->ItemIndex=row.ap_treatflag[0]=='\0' ? 0 : 1;
	for(i=0;i<m_lstDepartID.GetSize();i++)
	{
		if(m_lstDepartID[i]==row.ap_reqdepart)
		{
			lstDepAsk->ItemIndex=i;
			break;
		}
	}
	if(i==m_lstDepartID.GetSize())	lstDepAsk->ItemIndex=-1;

	for(i=0;i<m_lstDepartID.GetSize();i++)
	{
		if(m_lstDepartID[i]==row.ap_chargedep)
		{
			lstDepCharge->ItemIndex=i;
			break;
		}
	}
	if(i==m_lstDepartID.GetSize())	lstDepCharge->ItemIndex=-1;

	for(i=0;i<m_lstStockDepID.GetSize();i++)
	{
		if(m_lstStockDepID[i]==row.ap_sdcode)
		{
			lstDepBuy->ItemIndex=i;
			break;
		}
	}
	if(i==m_lstStockDepID.GetSize())	lstDepBuy->ItemIndex=-1;

	for(i=0;i<m_lstGACode.GetSize();i++)
	{
		if(m_lstGACode[i]==row.ap_gacode)
		{
			lstGoodsAddr->ItemIndex=i;
			break;
		}
	}
	if(i==m_lstGACode.GetSize())	lstGoodsAddr->ItemIndex=-1;

	for(i=0;i<m_lstHandleID.GetSize();i++)
	{
		if(m_lstHandleID[i]==row.ap_hmcode)
		{
			lstHandle->ItemIndex=i;
			break;
		}
	}
	if(i==m_lstHandleID.GetSize())	lstHandle->ItemIndex=-1;
}
void __fastcall TAskPurchaseForm::lstViewSelectItem(TObject *Sender,TListItem *Item, bool Selected)
{
	TListItem *pItem;
	if(m_bExiting)	return;
	if(lstView->Selected==NULL)	return;
	if(!Selected)	return;

	pItem=lstView->Selected;
	List2Editor(pItem);
	ResetCtrl();
}
//---------------------------------------------------------------------------

void TAskPurchaseForm::List2Editor(TListItem *pItem)
{
	CPurchaseDetailRow row;
	int nSel;
	
	if((nSel=lstView->Items->IndexOf(pItem))>=0 && nSel<m_lstDetail.GetSize())
		row=m_lstDetail[nSel];
	else
		memset(&row,0,sizeof(row));

	edtItem		->Text=pItem->Caption;
	edtMater	->Text=pItem->SubItems->Strings[0];
	edtMnname	->Text=pItem->SubItems->Strings[1];
	edtCount	->Text=pItem->SubItems->Strings[3];
	edtCooper	->Text=pItem->SubItems->Strings[4];
	edtEndFlag->Text=pItem->SubItems->Strings[5];

	ResetTreatList(edtMater->Text.c_str(),row.pd_tscode);
	lstUnits	->ItemIndex=lstUnits->Items->IndexOf(pItem->SubItems->Strings[2]);
}

#include "AskPurchaseMT.h"
void __fastcall TAskPurchaseForm::btnQueryMTClick(TObject *Sender)
{
	TAskPurchaseMTForm *pMT;
	pMT=new TAskPurchaseMTForm(this);
	assert(pMT!=NULL);
	pMT->m_szMaterCode=edtMater->Text;
	if(m_bIsTreat)
  	pMT->m_nTreatType=2;
  else
  	pMT->m_nTreatType=1;
	if(pMT->ShowModal()==mrOk)
	{
		edtMater->Text=pMT->m_szMaterCode;
	}
	delete pMT;
  if(edtMater->CanFocus())	edtMater->SetFocus();

/*
	if(m_bIsTreat)
  {
  	lstTreatView->Visible=true;
  }
  else
  {
		TAskPurchaseMTForm *pMT;
		pMT=new TAskPurchaseMTForm(this);
		assert(pMT!=NULL);
		pMT->m_szMaterCode=edtMater->Text;
		if(pMT->ShowModal()==mrOk)
		{
			edtMater->Text=pMT->m_szMaterCode;
		}
		delete pMT;
	  if(edtMater->CanFocus())	edtMater->SetFocus();
  }
*/
}
//---------------------------------------------------------------------------

void __fastcall TAskPurchaseForm::ApplicationEvents1Idle(TObject *Sender,bool &Done)
{
	if(ActiveControl==edtNeedDate || ActiveControl==edtAskDate)
		txtTips->Caption="日期格式：yyyymmdd";
	else txtTips->Caption="";
}
//---------------------------------------------------------------------------

//根据输入的数据、系统时间以及流水号生成编号
CString TAskPurchaseForm::GenerateID()
{ //编号格式：PymXXXX
	int nYear,nMonth,nDay,nFlow;
  char strID[80],chMon,strSQL[1024],strKey[80],strID2[80];

  if(!dm1->OpenDatabase())	return "";
	GetSysDate(nYear,nMonth,nDay,false);

	if(nMonth<10)	chMon=(char)('0'+nMonth);
  else chMon=(char)('A'-10+nMonth);

  //查看该月是否已经有流水号
  sprintf(strKey,"AskPurchase_%04d%02d",nYear,nMonth);
  sprintf(strSQL,"select * from RuntimeData where rd_key='%s'",strKey);
	RunSQL(strSQL,true);
  if(dm1->Query1->Eof)
  { //该月还没有流水号，初始化该月流水号
  	sprintf(strSQL,"insert into RuntimeData values('%s',1,NULL,'请购单%d年%d月流水号')",
    	strKey,nYear,nMonth);
    RunSQL(strSQL);
    nFlow=1;
  }
  else
  {
  	nFlow=dm1->Query1->FieldByName("rd_int")->AsInteger;
  }

  while(1)
  {
    sprintf(strID,"P%d%c%04d",nYear%10,chMon,nFlow);
    sprintf(strID2,"Q%d%c%04d",nYear%10,chMon,nFlow);
    sprintf(strSQL,"select * from AskPurchase where ap_code='%s' or ap_code='%s'",strID,strID2);
    RunSQL(strSQL,true);
    if(dm1->Query1->Eof)	break;
		nFlow++;
  }
  sprintf(strSQL,"update RuntimeData set rd_int=%d where rd_key='%s'",nFlow,strKey);
  RunSQL(strSQL);

  return CString(strID);
}
void __fastcall TAskPurchaseForm::edtMaterExit(TObject *Sender)
{
	char strName[256];
	CString szSQL;
        char strID[80];
        int i;

	edtMater->Text=edtMater->Text.Trim();
	strName[0]='\0';
	if(!edtMater->Text.IsEmpty())
	{
		szSQL.Format("select * from materialno where mn_code='%s'",edtMater->Text.c_str());
		RunSQL(dm1->Query1,szSQL,true);
		if(!dm1->Query1->Eof)
		{
			strcpy(strName,dm1->Query1->FieldByName("mn_name")->AsString.c_str());
                        strcpy(strID,dm1->Query1->FieldByName("mn_ducode")->AsString.c_str());
		}

//		if(m_bIsTreat && m_szPrvMaterialID!=edtMater->Text)	ResetTreatList(edtMater->Text.c_str(),NULL);
		if(m_bIsTreat)	ResetTreatList(edtMater->Text.c_str(),NULL);
	}

//	strcpy(strID,dm1->Query1->FieldByName("ts_ducode")->AsString.c_str());
        if(!m_bIsTreat)
        {
        	for(i=0;i<m_lstUnitID.GetSize();i++)
	        {
		        if(m_lstUnitID[i]==strID)
        		{
	        		lstUnits->ItemIndex=i;
//                                lstUnits->Enabled=false;
		        	break;
        		}
	        }
        	if(i==m_lstUnitID.GetSize())	lstUnits->ItemIndex=-1;
        }
	edtMnname->Text=strName;
	ResetCtrl();
//        lstUnits->Enabled=false;        
}
//---------------------------------------------------------------------------

void TAskPurchaseForm::ResetTreatList(LPCSTR lpszID,LPCSTR lpszSel)
{
	CString szSQL;
	int i;

	if(lpszID==NULL || lpszID[0]=='\0')
		return;

	szSQL.Format("select * from TreatStock,Manufactur where mf_code=ts_mfcode and ts_mncode='%s'",lpszID);
	RunSQL(dm1->Query1,szSQL,true);
	if(!dm1->Query1->Eof)
	{
		lstTreat->Items->Clear();
		m_lstTreatID.RemoveAll();
		m_lstTreatUnit.RemoveAll();
		while(!dm1->Query1->Eof)
		{
			lstTreat->Items->Add(dm1->Query1->FieldByName("mf_shortname")->AsString);
			m_lstTreatID.Add(dm1->Query1->FieldByName("ts_code")->AsString.c_str());
			m_lstTreatUnit.Add(dm1->Query1->FieldByName("ts_ducode")->AsString.c_str());

			dm1->Query1->Next();
		}
		if(lpszSel!=NULL && lpszSel[0]!='\0')
		{
			for(i=0;i<m_lstTreatID.GetSize();i++)
			{
				if(m_lstTreatID[i]==lpszSel)
				{
					lstTreat->ItemIndex=i;
					break;
				}
			}
		}
		else
			lstTreat->ItemIndex=0;
		ResetTreatUnit();
	}
	m_szPrvMaterialID=lpszID;
}

void TAskPurchaseForm::ResetTreatUnit()
{
	int nSel,i;
	CString szUnit;

	if(!m_bIsTreat)	return;

	if((nSel=lstTreat->ItemIndex)>=0 && nSel<m_lstTreatUnit.GetSize())
	{
		szUnit=m_lstTreatUnit[nSel];
		for(i=0;i<m_lstUnitID.GetSize();i++)
		{
			if(m_lstUnitID[i]==szUnit)
			{
				lstUnits->ItemIndex=i;
				break;
			}
		}
	}
}

void __fastcall TAskPurchaseForm::lstTreatClick(TObject *Sender)
{
	ResetTreatUnit();	
}
//---------------------------------------------------------------------------

void __fastcall TAskPurchaseForm::btnToTreatClick(TObject *Sender)
{
	int nSel;
	if((nSel=lstTreat->ItemIndex)>=0 && nSel<m_lstTreatID.GetSize())
	{
		TreatStock(m_lstTreatID[nSel]);
	}
}
//---------------------------------------------------------------------------



void __fastcall TAskPurchaseForm::lstTreatViewExit(TObject *Sender)
{
	lstTreatView->Visible=false;
}
//---------------------------------------------------------------------------

void __fastcall TAskPurchaseForm::lstTreatViewDblClick(TObject *Sender)
{
	int nSel;
	char strTemp[256];

	if((nSel=lstTreatView->ItemIndex)>=0)
	{
		strcpy(strTemp,lstTreatView->Items->Strings[nSel].c_str());
		strTemp[21]='\0';
		edtMater->Text=AnsiString(strTemp).Trim();
		lstTreatView->Visible=false;
		if(edtMater->CanFocus())	edtMater->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TAskPurchaseForm::lstTreatViewKeyDown(TObject *Sender,WORD &Key, TShiftState Shift)
{
	if(Key==VK_RETURN)	lstTreatViewDblClick(Sender);
	else if(Key==VK_ESCAPE)
	{
		lstTreatView->Visible=false;
		if(edtMater->CanFocus())	edtMater->SetFocus();
	}
}
//---------------------------------------------------------------------------

void __fastcall TAskPurchaseForm::lstUnitsExit(TObject *Sender)
{
	HandleListboxExit(lstUnits,&m_lstUnitID);
}
//---------------------------------------------------------------------------

#include "PrnMaterial.h"

void __fastcall TAskPurchaseForm::btnPrintRemClick(TObject *Sender)
{
	CString szSQL;
  TListItem *pItem;
  char strTemp[256];

  if((pItem=lstView->Selected)==NULL)
  {
  	ShowMessage("请选择一个材料编号");
    return;
  }

	szSQL="select * from materialno,diccorp,diclargetype,dicmiddletype,dicsmalltype,PurchaseDetail"
		" where substring(mn_code,1,1)=cp_code"
		" and substring(mn_code,2,1)=lt_code"
		" and substring(mn_code,2,2)=mt_code"
		" and substring(mn_code,2,4)=st_code"
    " and mn_code=pd_mncode";
  sprintf(strTemp," and pd_code like '%s_'",m_szActiveID);
  szSQL+=strTemp;
  szSQL+=" and mn_rem is not null"
  	" order by pd_code";

  TPrnMaterialForm *pPrn=new TPrnMaterialForm(this);
  assert(pPrn!=NULL);
	if(OpenQuery(dm1->sqlPrint,szSQL))
  {
	  pPrn->PrnView->PreviewModal();
  }
  delete pPrn;
}
//---------------------------------------------------------------------------








