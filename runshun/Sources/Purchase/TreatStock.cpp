//---------------------------------------------------------------------------

#include <vcl.h>
#include <stdio.h>
#include <assert.h>
#pragma hdrstop

#include "DataModule.h"
#include "BaseCode.h"
#include "TreatStock.h"
#include "TConst.h"
#include "LdyInterface.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TTreatStockForm *TreatStockForm;

//=========================================================================================
//合约采购档接口，文件：TreatStock.*
void TreatStock(int nAuth)
{
	TreatStock(NULL,nAuth);
}

void TreatStock(LPCSTR lpszID,int nAuth)
{
	if(nAuth==AUTH_NONE)
	{
		ShowMessage("抱歉，您没有该权限");
		return;
	}

	TTreatStockForm *pForm;
	pForm=new TTreatStockForm(Application);
	assert(pForm!=NULL);
	pForm->m_nAuthor=nAuth;
	if(lpszID!=NULL)	pForm->m_szIDFirst=lpszID;
	pForm->ShowModal();
	delete pForm;
}

//---------------------------------------------------------------------------
__fastcall TTreatStockForm::TTreatStockForm(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TTreatStockForm::btnExitClick(TObject *Sender)
{
	int nState=m_enState;
	if(m_enState==EN_STATE_IDLE)
		Close();
	else
	{
		m_enState=EN_STATE_IDLE;
		ResetCtrl();
                    if(nState!=EN_STATE_NEW)
			btnQueryClick(Sender);
	}
}
//---------------------------------------------------------------------------
void __fastcall TTreatStockForm::FormKeyDown(TObject *Sender, WORD &Key,TShiftState Shift)
{
	if(Key==VK_RETURN)
		KeyReturnHandle(ActiveControl);
}
//---------------------------------------------------------------------------

void __fastcall TTreatStockForm::FormShow(TObject *Sender)
{
	CString szSQL;

	edtID					->Text="";
	edtMater			->Text="";
	edtSpec				->Text="";
	edtCard				->Text="";
	edtInuredate	->Text="";
	edtPrice			->Text="";
	edtDays				->Text="";
	edtInpdate		->Text="";
	edtEditdate		->Text="";
	edtAfmDate		->Text="";
	edtAfmDate2		->Text="";

	EnableEdit(edtSpec		,false);
	EnableEdit(edtInpdate	,false);
	EnableEdit(edtEditdate,false);

	szSQL="select * from Manufactur order by mf_code";
	RunSQL(dm1->Query1,szSQL,true);
	while(!dm1->Query1->Eof)
	{
		m_lstFactID.Add(dm1->Query1->FieldByName("mf_code")->AsString.c_str());
		lstFact->Items->Add(dm1->Query1->FieldByName("mf_name")->AsString);
		dm1->Query1->Next();
	}
	lstFact->Text="";
	lstFact->ItemIndex=-1;

	szSQL="select * from DicUnits order by du_code";
	RunSQL(dm1->Query1,szSQL,true);
	while(!dm1->Query1->Eof)
	{
		m_lstUnitID.Add(dm1->Query1->FieldByName("du_code")->AsString.c_str());
		lstUnit->Items->Add(dm1->Query1->FieldByName("du_name")->AsString);
		dm1->Query1->Next();
	}
	lstUnit->Text="";
	lstUnit->ItemIndex=-1;

	szSQL="select * from StockHandleman order by sh_code";
	RunSQL(dm1->Query1,szSQL,true);
	while(!dm1->Query1->Eof)
	{
		m_lstHandleID.Add(dm1->Query1->FieldByName("sh_code")->AsString.c_str());
		lstHandle->Items->Add(dm1->Query1->FieldByName("sh_name")->AsString);
		dm1->Query1->Next();
	}
	lstHandle->Text="";
	lstHandle->ItemIndex=-1;

	szSQL="select * from StockDepart order by sd_code";
	RunSQL(dm1->Query1,szSQL,true);
	while(!dm1->Query1->Eof)
	{
		m_lstDepartID.Add(dm1->Query1->FieldByName("sd_code")->AsString.c_str());
		lstDepart->Items->Add(dm1->Query1->FieldByName("sd_name")->AsString);
		dm1->Query1->Next();
	}
	lstDepart->ItemIndex=0;

	m_enState=EN_STATE_IDLE;
	ResetCtrl();

	if(!m_szIDFirst.IsEmpty())
	{
		edtID->Text=m_szIDFirst;
		btnQueryClick(Sender);
	}
}
//---------------------------------------------------------------------------

void TTreatStockForm::ResetCtrl()
{
	bool bIdle,bAuth;

	bIdle = m_enState==EN_STATE_IDLE;
	bAuth = m_nAuthor==AUTH_FULL;

	EnableEdit(edtID				,m_enState!=EN_STATE_EDIT);
	EnableEdit(edtMater			,m_enState==EN_STATE_NEW);
	EnableCombo(lstFact			,!bIdle);
  btnPickFact->Enabled = lstFact->Enabled;
	btnPickup->Enabled = edtMater->Enabled;
	EnableEdit(edtCard			,!bIdle);
	EnableEdit(edtInuredate	,!bIdle);
	EnableCombo(lstUnit			,!bIdle);
	EnableEdit(edtPrice			,!bIdle);
	EnableEdit(edtDays			,!bIdle);
	EnableCombo(lstHandle		,!bIdle);
	EnableCombo(lstDepart		,!bIdle);

	EnableEdit(edtAfmDate		,false);
	EnableEdit(edtAfmDate2	,false);

	btnQuery->Enabled = bIdle;
	btnNew	->Enabled = bIdle && bAuth;
	btnEdit	->Enabled = bIdle && bAuth && !m_szActiveID.IsEmpty();
	btnMove	->Enabled = bIdle && bAuth && !m_szActiveID.IsEmpty();
	btnOK	->Enabled = !bIdle;
	btnExit->Caption = bIdle ? "退    出" : "放    弃";
}

void __fastcall TTreatStockForm::btnQueryClick(TObject *Sender)
{
	CString szSQL;
	int i,nSel;
	char strID[80],strSHID[4],strTemp3[256];

//---------- new 0629---取得操作者对应的采购部门别(在StockHandleman中的公司别)------srtSHID-------
/*        szSQL.Format("select * from StockHandleman where sh_code='%s'",operatorcode);
        RunSQL(dm1->Query1,szSQL,true);
        strcpy(strSHID,dm1->Query1->FieldByName("sh_sdcode")->AsString.c_str());
//        sprintf(strSHID,"%s",dm1->Query1->FieldByName("sh_sdcode")->AsString.c_str());        */
//------------------------------------------------------------------------------

	m_szActiveID="";

	edtID->Text=edtID->Text.Trim();
	if(edtID->Text.IsEmpty())
	{
		ShowMessage("请输入合约编号");
		if(edtID->CanFocus())	edtID->SetFocus();
		ResetCtrl();
		return;
	}
	szSQL.Format("select * from TreatStock,materialno where ts_mncode*=mn_code and ts_code='%s'",edtID->Text.c_str());
	RunSQL(dm1->Query1,szSQL,true);
	if(dm1->Query1->Eof)
	{
		ShowMessage("没有该项数据");
		ResetCtrl();
		return;
	}
	edtMater->Text=dm1->Query1->FieldByName("ts_mncode")->AsString;
	edtSpec	->Text=dm1->Query1->FieldByName("mn_name")->AsString;

	strcpy(strID,dm1->Query1->FieldByName("ts_mfcode")->AsString.c_str());
	for(i=0;i<m_lstFactID.GetSize();i++)
	{
		if(m_lstFactID[i]==strID)
		{
			lstFact->ItemIndex=i;
			break;
		}
	}
	if(i==m_lstFactID.GetSize())	lstFact->ItemIndex=-1;

	edtCard			->Text=dm1->Query1->FieldByName("ts_mfcard")->AsString;
	edtInuredate->Text=DateField2Text(dm1->Query1->FieldByName("ts_inuredate"));
	
	strcpy(strID,dm1->Query1->FieldByName("ts_ducode")->AsString.c_str());
	for(i=0;i<m_lstUnitID.GetSize();i++)
	{
		if(m_lstUnitID[i]==strID)
		{
			lstUnit->ItemIndex=i;
			break;
		}
	}
	if(i==m_lstUnitID.GetSize())	lstUnit->ItemIndex=-1;

//	edtPrice->Text=FloatField2String(dm1->Query1->FieldByName("ts_price"),2);
	strcpy(strID,dm1->Query1->FieldByName("ts_sdcode")->AsString.c_str());
        edtDays	->Text=IntField2Text(dm1->Query1->FieldByName("ts_days"));
//----new 0629----经办自己可以查看自己开的单的单价，可能是其它公司的.只有同一公司的经办才可以查看单价
/*        if(strcmp(strID,strSHID)!=0 && operatorcode!=dm1->Query1->FieldByName("ts_shcode")->AsString.c_str() && operatorcode!="admin" && operatorcode!="108557")
        {
                edtPrice->Text="";
        }
        else
        edtPrice->Text=FloatField2String(dm1->Query1->FieldByName("ts_price"),2);       */

//------------------------------------------------------------------------------
//-----NEW 0704-----------------------------------------------------------------
                if(operatorcode!=dm1->Query1->FieldByName("ts_shcode")->AsString && operatorcode!=dm1->Query1->FieldByName("ts_operator")->AsString)
                {
                        edtPrice->Text="";
                }
                else
                {
//                        edtPrice->Text=FloatField2String(dm1->Query1->FieldByName("ts_price"),2);
                        edtPrice->Text=FloatField2String(dm1->Query1->FieldByName("ts_price"),8);      //高精度
                }
//------------------------------------------------------------------------------


	strcpy(strID,dm1->Query1->FieldByName("ts_shcode")->AsString.c_str());
	for(i=0;i<m_lstHandleID.GetSize();i++)
	{
		if(m_lstHandleID[i]==strID)
		{
			lstHandle->ItemIndex=i;
			break;
		}
	}
	if(i==m_lstHandleID.GetSize())	lstHandle->ItemIndex=-1;

  for(i=0;i<m_lstDepartID.GetSize();i++)
	{
  	if(m_lstDepartID[i]==dm1->Query1->FieldByName("ts_sdcode")->AsString.c_str())
  	{
    	lstDepart->ItemIndex=i;
      break;
    }
  }
	if(i==m_lstDepartID.GetSize())	lstDepart->ItemIndex=0;

	edtInpdate	->Text=DateField2Text(dm1->Query1->FieldByName("ts_inputdate"));
	edtEditdate	->Text=DateField2Text(dm1->Query1->FieldByName("ts_modifydate"));
	edtAfmDate	->Text=DateField2Text(dm1->Query1->FieldByName("ts_afmdate"));
	edtAfmDate2	->Text=DateField2Text(dm1->Query1->FieldByName("ts_afmdate2"));

	m_szActiveID=edtID->Text.c_str();
	m_tOperTime=dm1->Query1->FieldByName("ts_opertime")->AsDateTime;

	ResetCtrl();
}
//---------------------------------------------------------------------------

void __fastcall TTreatStockForm::btnNewClick(TObject *Sender)
{
	m_enState=EN_STATE_NEW;
	ResetCtrl();
	edtID->Text=GenerateID();
  edtInpdate	->Text="";
  edtEditdate	->Text="";
  edtAfmDate	->Text="";
  edtAfmDate2	->Text="";
  edtMater->Text="";
  lstUnit->Text="";
//  lstUnit->Enabled=true;
	if(edtMater->CanFocus())	edtMater->SetFocus();
}
//---------------------------------------------------------------------------

void __fastcall TTreatStockForm::btnEditClick(TObject *Sender)
{
	int nSel;
	if(m_szActiveID.IsEmpty())	return;

	if(m_szActiveID!=edtID->Text.c_str())
	{
		ShowMessage("您输入的合约编号与正在查询的不同");
		if(edtID->CanFocus())	edtID->SetFocus();
		return;
	}
	if(!edtAfmDate->Text.IsEmpty() || !edtAfmDate2->Text.IsEmpty())
	{
		ShowMessage("该合约已被确认，必须确认日期和会计确认日期都解除才可修改和删除");
		return;
	}
//----------new 0629------------------------------------------------------------
	if(operatorcode!=dm1->Query1->FieldByName("ts_shcode")->AsString && operatorcode!="admin" && operatorcode!="108557")
	{
		ShowMessage("只有admin和采购经办自己才能删除或修改合约内容");
		return;
	}
//------------------------------------------------------------------------------
	m_enState=EN_STATE_EDIT;
  ResetCtrl();
  if(edtCard->CanFocus())	edtCard->SetFocus();
}
//---------------------------------------------------------------------------

void __fastcall TTreatStockForm::btnMoveClick(TObject *Sender)
{
	int nSel;
	CString szSQL,szMsg;
	AnsiString szFlow;
	TDateTime tNow;

	if(m_szActiveID.IsEmpty())	return;
//----------new 0629------------------------------------------------------------
	if(operatorcode!=dm1->Query1->FieldByName("ts_shcode")->AsString && operatorcode!="admin" && operatorcode!="108557")
	{
		ShowMessage("只有admin和采购经办自己才能删除或修改合约内容");
		return;
	}
//------------------------------------------------------------------------------
	if(m_szActiveID!=edtID->Text.c_str())
	{
		ShowMessage("您输入的合约编号与正在查询的不同");
		if(edtID->CanFocus())	edtID->SetFocus();
		return;
	}
	if(Application->MessageBox("真要删除该项数据吗","警告",MB_YESNOCANCEL | MB_ICONQUESTION | MB_DEFBUTTON2)!=IDYES)	return;
	szSQL.Format("select * from TreatStock where ts_code='%s'",m_szActiveID);
	RunSQL(dm1->Query1,szSQL,true);
	if(dm1->Query1->Eof)
	{
		ShowMessage("该项数据不存在，可能已被其它人删除了");
		return;
	}
	if(dm1->Query1->FieldByName("ts_opertime")->AsDateTime!=m_tOperTime)
	{
		ShowMessage("该项数据已被其它人修改过了，请重新查询");
		return;
	}
	if(!edtAfmDate->Text.IsEmpty() || !edtAfmDate2->Text.IsEmpty())
	{
		ShowMessage("该合约已被确认，必须确认日期和会计确认日期都解除才可修改和删除");
		return;
	}

	try
	{
		szFlow=GenModifyFlowID();
		tNow=GetSysTime(false);

		if(!BeginTransact())	return;

		szSQL.Format("insert into TreatStockModify"
			" select '%s',ts_code,ts_mncode,ts_mfcode,ts_inuredate,ts_price,ts_ducode,ts_mfcard,ts_days,"
			"ts_shcode,ts_sdcode,ts_inputdate,ts_modifydate,ts_afmdate,ts_afmdate2,'%s','%s','D' from TreatStock where ts_code='%s'",
			szFlow.c_str(),operatorcode.c_str(),Time2DBTimeString(tNow),m_szActiveID);
		if(!RunTransactSQL(szSQL))	goto EXCEPT_TRANSACT;

		szSQL.Format("delete TreatStock where ts_code='%s'",m_szActiveID);
		if(!RunTransactSQL(szSQL))	goto EXCEPT_TRANSACT;

		CommitTransact();
	}
	catch(...)
	{
		goto EXCEPT_TRANSACT;
	}

	m_szActiveID="";
	ResetCtrl();
	return;

EXCEPT_TRANSACT:
	RollBackTransact();
	szMsg.Format("数据操作失败，SQL=\n%s",szSQL);
	ShowMessage((LPCSTR)szMsg);
}
//---------------------------------------------------------------------------


void __fastcall TTreatStockForm::btnOKClick(TObject *Sender)
{
	CString szSQL, szMsg;
	TDateTime tNow;
	AnsiString szFlow;
	bool bHistory;
        int nState;

	if (!CheckInput())
        {
        	return;
        }
	tNow = GetSysTime(false);

//--------NEW 0527  新旧编号合法性验证------------------------------------------
//        CString szSQL;
        char strID[80];
        sprintf(strID, "%s", edtMater->Text.c_str());


        szSQL.Format("select * from codecheck where cc_ocode=%s", Str2DBString(strID));
        RunSQL(dm1->Query1, szSQL, true);
	if (!dm1->Query1->Eof)
	{
                ShowMessage("抱歉！该编号已被停用，请查找同一品名规格的并且以A开头的编号");
		return;
	}
//------------------------------------------------------------------------------

        nState = m_enState;
	if (m_enState==EN_STATE_NEW)
	{
		szSQL.Format("select * from TreatStock where ts_mncode='%s' and ts_mfcode='%s'",
			        edtMater->Text.c_str(), m_lstFactID[lstFact->ItemIndex]);
		RunSQL(dm1->Query1, szSQL, true);
		if (!dm1->Query1->Eof)
                {
                	bHistory = true;
                }
		else
                {
                	bHistory = false;
                }

		try
		{
			if (!BeginTransact())
                        {
                        	return;
                        }

			if(bHistory)
			{
				szSQL.Format("insert into TreatStockHistory select * from TreatStock where ts_mncode='%s' and ts_mfcode='%s'",
					edtMater->Text.c_str(),m_lstFactID[lstFact->ItemIndex]);
				if(!RunTransactSQL(szSQL))	goto EXCEPT_TRANSACT;

				szSQL.Format("delete TreatStock where ts_mncode='%s' and ts_mfcode='%s'",
					edtMater->Text.c_str(),m_lstFactID[lstFact->ItemIndex]);
				if(!RunTransactSQL(szSQL))	goto EXCEPT_TRANSACT;
			}

			szSQL="insert into TreatStock (ts_code,ts_mncode,ts_mfcode,ts_inuredate,ts_price,ts_ducode,"
				"ts_mfcard,ts_days,ts_shcode,ts_sdcode,ts_inputdate,ts_modifydate,ts_afmdate,ts_afmdate2,"
				"ts_operator,ts_opertime"
				") values(";
			szSQL+=Str2DBString(edtID->Text.c_str());
			szSQL+=",";	szSQL+=Str2DBString(edtMater->Text.c_str());
			szSQL+=",";	szSQL+=Str2DBString(m_lstFactID[lstFact->ItemIndex]);
			szSQL+=",";	szSQL+=Text2DBDate(edtInuredate->Text).c_str();
//			szSQL+=",";	szSQL+=Text2DBFloat(edtPrice->Text,2).c_str();
			szSQL+=",";	szSQL+=Text2DBFloat(edtPrice->Text,8).c_str(); //高精度
	       		szSQL+=",";	szSQL+=Str2DBString(m_lstUnitID[lstUnit->ItemIndex]);
			szSQL+=",";	szSQL+=Str2DBString(edtCard->Text.c_str());
			szSQL+=",";	szSQL+=Text2DBInt(edtDays->Text).c_str();
			szSQL+=",";	szSQL+=Str2DBString(m_lstHandleID[lstHandle->ItemIndex]);
			szSQL+=",";	szSQL+=Str2DBString(m_lstDepartID[lstDepart->ItemIndex]);
			szSQL+=",";	szSQL+=Str2DBString(Time2DBDateString(tNow));
			szSQL+=",NULL";
			szSQL+=",NULL";
			szSQL+=",NULL";
			szSQL+=",";	szSQL+=Str2DBString(operatorcode.c_str());
			szSQL+=",";	szSQL+=Str2DBString(Time2DBTimeString(tNow));
			szSQL+=")";
			if(!RunTransactSQL(szSQL))	goto EXCEPT_TRANSACT;

			CommitTransact();
		}
		catch(...)
		{
			goto EXCEPT_TRANSACT;
		}

		edtInpdate->Text=(LPCSTR)Date2YYMMDD(tNow);
		m_szActiveID=edtID->Text.c_str();

                szSQL.Format("select * from TreatStock where ts_code='%s'",m_szActiveID);
                RunSQL(dm1->Query1,szSQL,true);
                if (dm1->Query1->FieldByName("ts_opertime")->IsNull)
                {
                        m_tOperTime = tNow;
                }
                else
                {
                    	m_tOperTime = dm1->Query1->FieldByName("ts_opertime")->AsDateTime;
                }

		m_enState = EN_STATE_IDLE;
		ResetCtrl();
	}
	else
	{//修改合约档：先将要修改之合约档插入TreatStockModify　若插入成功　则更新TreatStock 中的纪录
		szFlow = GenModifyFlowID();

		try
		{
			if (!BeginTransact())
                        {
                        	return;
                        }

			szSQL.Format("insert into TreatStockModify"
				" select '%s',ts_code,ts_mncode,ts_mfcode,ts_inuredate,ts_price,ts_ducode,ts_mfcard,ts_days,"
				"ts_shcode,ts_sdcode,ts_inputdate,ts_modifydate,ts_afmdate,ts_afmdate2,'%s','%s','E' from TreatStock where ts_code='%s'",
				szFlow.c_str(),operatorcode.c_str(),Time2DBTimeString(tNow),m_szActiveID);
			if(!RunTransactSQL(szSQL))	goto EXCEPT_TRANSACT;

			szSQL="update TreatStock set";
			szSQL+=" ts_mncode=";				szSQL+=Str2DBString(edtMater->Text.c_str());
			szSQL+=",ts_mfcode=";				szSQL+=Str2DBString(m_lstFactID[lstFact->ItemIndex]);
			szSQL+=",ts_inuredate=";		szSQL+=Text2DBDate(edtInuredate->Text).c_str();
//			szSQL+=",ts_price=";				szSQL+=Text2DBFloat(edtPrice->Text,2).c_str();
			szSQL+=",ts_price=";				szSQL+=Text2DBFloat(edtPrice->Text,8).c_str(); //高精度
			szSQL+=",ts_ducode=";				szSQL+=Str2DBString(m_lstUnitID[lstUnit->ItemIndex]);
			szSQL+=",ts_mfcard=";				szSQL+=Str2DBString(edtCard->Text.c_str());
			szSQL+=",ts_days=";					szSQL+=Text2DBInt(edtDays->Text).c_str();
			szSQL+=",ts_shcode=";				szSQL+=Str2DBString(m_lstHandleID[lstHandle->ItemIndex]);
			szSQL+=",ts_sdcode=";				szSQL+=Str2DBString(m_lstDepartID[lstDepart->ItemIndex]);
			szSQL+=",ts_modifydate=";		szSQL+=Str2DBString(Time2DBDateString(tNow));
			szSQL+=",ts_operator=";			szSQL+=Str2DBString(operatorcode.c_str());
			szSQL+=",ts_opertime=";			szSQL+=Str2DBString(Time2DBTimeString(tNow));
			szSQL+=" where ts_code=";		szSQL+=Str2DBString(m_szActiveID);
			if(!RunTransactSQL(szSQL))	goto EXCEPT_TRANSACT;

			CommitTransact();
		}
		catch(...)
		{
			goto EXCEPT_TRANSACT;
		}

		edtEditdate->Text=(LPCSTR)Date2YYMMDD(tNow);

                szSQL.Format("select * from TreatStock where ts_code='%s'",m_szActiveID);
                RunSQL(dm1->Query1,szSQL,true);
                if (dm1->Query1->FieldByName("ts_opertime")->IsNull)
                {
                        m_tOperTime=tNow;
                }
                else
                {
                        m_tOperTime=dm1->Query1->FieldByName("ts_opertime")->AsDateTime;
                }
                m_enState=EN_STATE_IDLE;
                ResetCtrl();
        }


        if (nState==EN_STATE_NEW)
        {
              if (btnNew->CanFocus())
              {
                btnNew->SetFocus();
              }
        }
        else if(nState==EN_STATE_EDIT)
	{
  	        if (btnEdit->CanFocus())
                {
                	btnEdit->SetFocus();
                }
        }
	return;

EXCEPT_TRANSACT:
	RollBackTransact();
	szMsg.Format("数据操作失败，SQL=\n%s",szSQL);
	ShowMessage((LPCSTR)szMsg);
}
//---------------------------------------------------------------------------

bool TTreatStockForm::CheckInput()
{
	CString szSQL;
	int nSel;
        char strCorp[80], strMater[80];

	if(m_enState==EN_STATE_NEW)
	{
		edtID->Text=edtID->Text.Trim();
		if(edtID->Text.IsEmpty())
		{
			ShowMessage("请输入合约编号");
			if(edtID->CanFocus())	edtID->SetFocus();
			return false;
		}
		szSQL.Format("select * from TreatStock where ts_code='%s'",edtID->Text.c_str());
		RunSQL(dm1->Query1,szSQL,true);
		if(!dm1->Query1->Eof)
		{
			ShowMessage("数据库中已有该编号的数据");
			if(edtID->CanFocus())	edtID->SetFocus();
			return false;
		}
	}
	else
	{
		if(m_szActiveID.IsEmpty())	return false;
		if(m_szActiveID!=edtID->Text.c_str())	return false;
		szSQL.Format("select * from TreatStock where ts_code='%s'",m_szActiveID);
		RunSQL(dm1->Query1,szSQL,true);
		if(dm1->Query1->Eof)
		{
			ShowMessage("数据库中没有该编号的记录\n可能是被其它人删除了，请重新查询");
			return false;
		}
		if(dm1->Query1->FieldByName("ts_opertime")->IsNull 
			|| dm1->Query1->FieldByName("ts_opertime")->AsDateTime!=m_tOperTime)
		{
			ShowMessage("数据库中该项数据已被其它人修改过，请重新查询");
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
		if(edtMater->CanFocus())	edtMater->SetFocus();
		return false;
	}
  if(operatorcode!="admin")
  {
	  szSQL.Format("select * from operator where op_code='%s'",operatorcode.c_str());
		RunSQL(dm1->Query1,szSQL,true);
	  if(dm1->Query1->Eof)	return false;
  	strcpy(strCorp,dm1->Query1->FieldByName("op_cpcode")->AsString.c_str());
		strcpy(strMater,edtMater->Text.c_str());

//------------  0527  开放编号使用权限　把原有程序括起来　----------------------
/*
  	if(strMater[0]!=strCorp[0])
	  {
			ShowMessage("材料编号的第一个字母必须与您的公司相同");
			return false;
	  }
*/
//------------------------------------------------------------------------------
  }

	if(lstFact->Text.IsEmpty() || ((nSel=lstFact->ItemIndex)<0 || nSel>=m_lstFactID.GetSize()))
	{
		ShowMessage("请选择一个有效的厂商");
		return false;
	}

	edtCard->Text=edtCard->Text.Trim();
	if(edtCard->Text.IsEmpty())
	{
		ShowMessage("请输入厂牌");
		if(edtCard->CanFocus())	edtCard->SetFocus();
		return false;
	}
	if(!CheckDateEditor(edtInuredate))	return false;
	if(lstUnit->Text.IsEmpty() || ((nSel=lstUnit->ItemIndex)<0 || nSel>=m_lstUnitID.GetSize()))
	{
		ShowMessage("请选择一个有效的单位");
		return false;
	}
	if(!CheckFloatEditor(edtPrice))	return false;
	if(!CheckIntEditor(edtDays))	return false;
	if(lstHandle->Text.IsEmpty() || ((nSel=lstHandle->ItemIndex)<0 || nSel>=m_lstHandleID.GetSize()))
	{
		ShowMessage("请选择一个有效的经办人");
		return false;
	}
	if((nSel=lstDepart->ItemIndex)<0 || nSel>=m_lstDepartID.GetSize())
	{
		ShowMessage("请选择一个有效的采购部门");
		return false;
	}

	szSQL.Format("select * from TreatStock where ts_mncode='%s' and ts_mfcode='%s'",
		edtMater->Text.c_str(),m_lstFactID[lstFact->ItemIndex]);
	RunSQL(dm1->Query1,szSQL,true);
	if(!dm1->Query1->Eof)
	{
		if(m_enState==EN_STATE_NEW)
		{
			ShowMessage("数据库中已有同一材料、同一厂商的合约");
			return false;
		}
		else if(m_enState==EN_STATE_EDIT)
		{
			if(edtID->Text!=dm1->Query1->FieldByName("ts_code")->AsString)
			{
				ShowMessage("数据库中已有同一材料、同一厂商的合约");
				return false;
			}
		}
	}

	return true;
}


#include "AskPurchaseMT.h"
void __fastcall TTreatStockForm::btnPickupClick(TObject *Sender)
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
//---------------------------------------------------------------------------

void __fastcall TTreatStockForm::lstFactExit(TObject *Sender)
{
	int nSel,i;

	lstFact->Text=lstFact->Text.Trim();
	if(lstFact->Text.IsEmpty())	return;

	if((nSel=lstFact->Items->IndexOf(lstFact->Text))<0 || nSel>=m_lstFactID.GetSize())
	{
		lstFact->Text=lstFact->Text.UpperCase();
		for(i=0;i<m_lstFactID.GetSize();i++)
		{
			if(m_lstFactID[i]==lstFact->Text.c_str())
			{
				lstFact->ItemIndex=i;
				break;
			}
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TTreatStockForm::lstUnitExit(TObject *Sender)
{
	int nSel,i;

	lstUnit->Text=lstUnit->Text.Trim();
	if(lstUnit->Text.IsEmpty())	return;

	if((nSel=lstUnit->Items->IndexOf(lstUnit->Text))<0 || nSel>=m_lstUnitID.GetSize())
	{
		lstUnit->Text=lstUnit->Text.UpperCase();
		for(i=0;i<m_lstUnitID.GetSize();i++)
		{
			if(m_lstUnitID[i]==lstUnit->Text.c_str())
			{
				lstUnit->ItemIndex=i;
				break;
			}
		}
	}
}
//---------------------------------------------------------------------------


void __fastcall TTreatStockForm::lstHandleExit(TObject *Sender)
{
	int nSel,i;

	lstHandle->Text=lstHandle->Text.Trim();
	if(lstHandle->Text.IsEmpty())	return;

	if((nSel=lstHandle->Items->IndexOf(lstHandle->Text))<0 || nSel>=m_lstHandleID.GetSize())
	{
		lstHandle->Text=lstHandle->Text.UpperCase();
		for(i=0;i<m_lstFactID.GetSize();i++)
		{
			if(m_lstHandleID[i]==lstHandle->Text.c_str())
			{
				lstHandle->ItemIndex=i;
				break;
			}
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TTreatStockForm::edtMaterExit(TObject *Sender)
{
	CString szSQL;
        int i;
	edtMater->Text=edtMater->Text.Trim();
	if(edtMater->Text.IsEmpty())
	{
		edtSpec->Text="";
		return;
	}
	
	szSQL.Format("select * from materialno where mn_code='%s'",edtMater->Text.c_str());
	RunSQL(dm1->Query1,szSQL,true);
	if(dm1->Query1->Eof)	edtSpec->Text="";
	else
        {
                edtSpec->Text=dm1->Query1->FieldByName("mn_name")->AsString;
        	for(i=0;i<m_lstUnitID.GetSize();i++)
	        {
		        if(m_lstUnitID[i]==dm1->Query1->FieldByName("mn_ducode")->AsString.c_str())
        		{
	        		lstUnit->ItemIndex=i;
                                lstUnit->Enabled=false; //材料有单位。则自动锁定之
		        	break;
        		}
	        }
        	if(i==m_lstUnitID.GetSize())	lstUnit->ItemIndex=-1;
        }
}
//---------------------------------------------------------------------------

//根据输入的数据、系统时间以及流水号生成编号
AnsiString TTreatStockForm::GenerateID()
{ //编号格式：PymXXXX
	int nYear,nMonth,nDay,nFlow;
  char strID[80],chMon,strSQL[1024],strKey[80];

  if(!dm1->OpenDatabase())	return "";
	GetSysDate(nYear,nMonth,nDay,false);

	if(nMonth<10)	chMon=(char)('0'+nMonth);
  else chMon=(char)('A'-10+nMonth);

  //查看该月是否已经有流水号
  sprintf(strKey,"TreatStock_%04d%02d",nYear,nMonth);
  sprintf(strSQL,"select * from RuntimeData where rd_key='%s'",strKey);
	RunSQL(strSQL,true);
  if(dm1->Query1->Eof)
  { //该月还没有流水号，初始化该月流水号
  	sprintf(strSQL,"insert into RuntimeData values('%s',1,NULL,'合约采购%d年%d月流水号')",
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
    sprintf(strID,"T%02d%c%04d",nYear%10,chMon,nFlow);
    sprintf(strSQL,"select * from TreatStock where ts_code='%s'",strID);
    RunSQL(strSQL,true);
    if(dm1->Query1->Eof)	break;
		nFlow++;
  }
  sprintf(strSQL,"update RuntimeData set rd_int=%d where rd_key='%s'",nFlow,strKey);
  RunSQL(strSQL);

  return AnsiString(strID);
}

//根据输入的数据、系统时间以及流水号生成编号
AnsiString TTreatStockForm::GenModifyFlowID()
{ //编号格式：PymXXXX
  char strID[80],chMon,strSQL[1024],strKey[80];
  int nFlow;

  if(!dm1->OpenDatabase())	return "";

  sprintf(strKey,"TreatStockModify");
  sprintf(strSQL,"select * from RuntimeData where rd_key='%s'",strKey);
	RunSQL(strSQL,true);
  if(dm1->Query1->Eof)
  { 
  	sprintf(strSQL,"insert into RuntimeData values('%s',1,NULL,'合约采购更改档流水号')",strKey);
    RunSQL(strSQL);
    nFlow=1;
  }
  else
  {
  	nFlow=dm1->Query1->FieldByName("rd_int")->AsInteger;
  }

  while(1)
  {
    sprintf(strID,"F%07d",nFlow);
    sprintf(strSQL,"select * from TreatStockModify where ts_flow='%s'",strID);
    RunSQL(strSQL,true);
    if(dm1->Query1->Eof)	break;
		nFlow++;
  }
  sprintf(strSQL,"update RuntimeData set rd_int=%d where rd_key='%s'",nFlow,strKey);
  RunSQL(strSQL);

  return AnsiString(strID);
}


void __fastcall TTreatStockForm::btnPrintClick(TObject *Sender)
{
//
}
//---------------------------------------------------------------------------

#include "FactorySearch.h"
void __fastcall TTreatStockForm::btnPickFactClick(TObject *Sender)
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






