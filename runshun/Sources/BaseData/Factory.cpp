//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include <assert.h>
#include "DataModule.h"
#include "BaseCode.h"
#include "Factory.h"
#include "FactorySearch.h"
#include "LdyInterface.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFactoryForm *FactoryForm;

//==============================================================
//厂商资料档接口，文件：Factory.*
void FactoryInput(LPCSTR lpszID,int nAuth)
{
	if(nAuth==AUTH_NONE)
  {
  	ShowMessage("抱歉，您没有这个权限");
    return;
  }

  TFactoryForm *pForm;
	try
	{
  	pForm=new TFactoryForm(Application);
  }
	catch (Exception &exception)
	{
		Application->ShowException(&exception);
    return;
	}
	if(lpszID!=NULL)	pForm->m_szIDFirst=lpszID;
  pForm->m_nAuthor=nAuth;
  pForm->ShowModal();
  delete pForm;
}

void FactoryInput(int nAuth)
{
	FactoryInput(NULL,nAuth);
}
// ==================================================================

CFactoryRow::CFactoryRow()
{
	InitMemberField(mf_code);
	InitMemberField(mf_name);
	InitMemberField(mf_shortname);
	InitMemberField(mf_linkman);
	InitMemberField(mf_tel);
	InitMemberField(mf_fax);
	InitMemberField(mf_addr);
	InitMemberField(mf_type);
	InitMemberField(mf_artific);
	InitMemberField(mf_regmoney);
	InitMemberField(mf_prodaddr);
	InitMemberField(mf_areascale);
	InitMemberField(mf_manscale);
	InitMemberField(mf_monthcap);
	InitMemberField(mf_workitem);
	InitMemberField(mf_idaffix);
	InitMemberField(mf_status);
	InitMemberField(mf_postcode);
	InitMemberField(mf_taxcode);
	InitMemberField(mf_bankid);
	InitMemberField(mf_bankname);
	InitMemberField(mf_bandaddr);
	InitMemberField(mf_judge);
	InitMemberField(mf_advice);
	InitMemberField(mf_mail);
	InitMemberField(mf_statdate0);
	InitMemberField(mf_statdate1);
	InitMemberField(mf_inputdate);
}

bool CFactoryRow::ReadFromDB(TQuery *pQuery)
{
	ReadMember(mf_code			,pQuery->FieldByName("mf_code"));
	ReadMember(mf_name			,pQuery->FieldByName("mf_name"));
	ReadMember(mf_shortname	,pQuery->FieldByName("mf_shortname"));
	ReadMember(mf_linkman		,pQuery->FieldByName("mf_linkman"));
	ReadMember(mf_tel				,pQuery->FieldByName("mf_tel"));
	ReadMember(mf_fax				,pQuery->FieldByName("mf_fax"));
	ReadMember(mf_addr			,pQuery->FieldByName("mf_addr"));
	ReadMember(mf_type			,pQuery->FieldByName("mf_type"));
	ReadMember(mf_artific		,pQuery->FieldByName("mf_artific"));
	ReadMember(mf_regmoney	,pQuery->FieldByName("mf_regmoney"));
	ReadMember(mf_prodaddr	,pQuery->FieldByName("mf_prodaddr"));
	ReadMember(mf_areascale	,pQuery->FieldByName("mf_areascale"));
	ReadMember(mf_manscale	,pQuery->FieldByName("mf_manscale"));
	ReadMember(mf_monthcap	,pQuery->FieldByName("mf_monthcap"));
	ReadMember(mf_workitem	,pQuery->FieldByName("mf_workitem"));
	ReadMember(mf_idaffix		,pQuery->FieldByName("mf_idaffix"));
	ReadMember(mf_status		,pQuery->FieldByName("mf_status"));
	ReadMember(mf_postcode	,pQuery->FieldByName("mf_postcode"));
	ReadMember(mf_taxcode		,pQuery->FieldByName("mf_taxcode"));
	ReadMember(mf_bankid		,pQuery->FieldByName("mf_bankid"));
	ReadMember(mf_bankname	,pQuery->FieldByName("mf_bankname"));
	ReadMember(mf_bandaddr	,pQuery->FieldByName("mf_bandaddr"));
	ReadMember(mf_judge			,pQuery->FieldByName("mf_judge"));
	ReadMember(mf_advice		,pQuery->FieldByName("mf_advice"));
	ReadMember(mf_mail			,pQuery->FieldByName("mf_mail"));
	ReadMember(mf_statdate0	,pQuery->FieldByName("mf_statdate0"));
	ReadMember(mf_statdate1	,pQuery->FieldByName("mf_statdate1"));
	ReadMember(mf_inputdate	,pQuery->FieldByName("mf_inputdate"));

	return true;
}

//---------------------------------------------------------------------------
__fastcall TFactoryForm::TFactoryForm(TComponent* Owner)
	: TForm(Owner)
{
}

void TFactoryForm::RefreshIDList()
{
	CString szSQL;
	char strTemp[256];
	int nSel;

	szSQL="select mf_code from Manufactur";
	if((nSel=lstSearchCorp->ItemIndex)>0 && nSel<m_lstSearchCorpID.GetSize())
	{
		sprintf(strTemp," where mf_corp=%s",Str2DBString(m_lstSearchCorpID[nSel]));
		szSQL+=strTemp;
	}
	szSQL+=" order by mf_code";
	lstCode->Items->Clear();
	RunSQL(dm1->Query1,szSQL,true);
	while(!dm1->Query1->Eof)
	{
		lstCode->Items->Add(dm1->Query1->FieldByName("mf_code")->AsString);
		dm1->Query1->Next();
	}
}

//---------------------------------------------------------------------------
void __fastcall TFactoryForm::FormShow(TObject *Sender)
{
	edtID->Text="";
	EmptyEditor();

	CString szSQL;

	m_lstSearchCorpID.Add("");
	lstSearchCorp->Items->Add("全部");
  szSQL="select * from diccorp order by cp_code";
  RunSQL(dm1->Query1,szSQL,true);
  while(!dm1->Query1->Eof)
  {
		m_lstSearchCorpID.Add(dm1->Query1->FieldByName("cp_code")->AsString.c_str());
  	m_lstCorpID.Add(dm1->Query1->FieldByName("cp_code")->AsString.c_str());
   	lstCorp->Items->Add(dm1->Query1->FieldByName("cp_name")->AsString);
		lstSearchCorp->Items->Add(dm1->Query1->FieldByName("cp_name")->AsString);
    dm1->Query1->Next();
  }
  szSQL="select * from DicInvoice order by di_code";                            //添加所有主税别
  RunSQL(dm1->Query1,szSQL,true);
  while(!dm1->Query1->Eof)
  {
  	m_lstTaxID.Add(dm1->Query1->FieldByName("di_code")->AsString.c_str());
    lstTaxType->Items->Add(dm1->Query1->FieldByName("di_name")->AsString.c_str());
    dm1->Query1->Next();
  }
  szSQL="select * from DicInvoice order by di_code";                            //添加所有副税别
  RunSQL(dm1->Query1,szSQL,true);
  while(!dm1->Query1->Eof)
  {
  	m_lstTaxID2.Add(dm1->Query1->FieldByName("di_code")->AsString.c_str());
    lstTaxType2->Items->Add(dm1->Query1->FieldByName("di_name")->AsString.c_str());
    dm1->Query1->Next();
  }

	szSQL="select * from DicStatus order by ds_code";
	RunSQL(dm1->Query1,szSQL,true);
	while(!dm1->Query1->Eof)
	{
		m_lstStatusID.Add(dm1->Query1->FieldByName("ds_code")->AsString.c_str());
		lstStatus->Items->Add(dm1->Query1->FieldByName("ds_name")->AsString);
		dm1->Query1->Next();
	}

	RefreshIDList();

	m_enState=EN_STATE_IDLE;
	ResetCtrl();

	if(!m_szIDFirst.IsEmpty())
	{
		edtID->Text=m_szIDFirst;
		OnQuery();
	}
}

void TFactoryForm::ResetCtrl()
{
	bool bIdle,bAuth;

	bIdle = m_enState==EN_STATE_IDLE;
	bAuth = m_nAuthor==AUTH_FULL;

	EnableEdit(edtID				,bIdle || m_enState==EN_STATE_NEW);
	EnableEdit(edtName			,!bIdle);
	EnableEdit(edtShortName	,!bIdle);
	EnableEdit(edtLinkMan		,!bIdle);
	EnableEdit(edtTel				,!bIdle);
	EnableEdit(edtFax				,!bIdle);
	EnableEdit(edtAddr			,!bIdle);
	EnableEdit(edtType			,!bIdle);
	EnableEdit(edtArtific		,!bIdle);
	EnableEdit(edtRegmoney	,!bIdle);
	EnableEdit(edtProdAddr	,!bIdle);
	EnableEdit(edtAreaScale	,!bIdle);
	EnableEdit(edtManScale	,!bIdle);
	EnableEdit(edtMonthCap	,!bIdle);
	EnableEdit(edtWorkItem	,!bIdle);
	EnableEdit(edtIDAffix		,!bIdle);
	EnableCombo(lstStatus		,!bIdle);
	EnableEdit(edtDate0			,!bIdle);
	EnableEdit(edtDate1			,!bIdle);
	EnableEdit(edtPostCode	,!bIdle);
	EnableEdit(edtTax				,!bIdle);
	EnableEdit(edtBankID		,!bIdle);
	EnableEdit(edtBankName	,!bIdle);
	EnableEdit(edtBankAddr	,!bIdle);
	EnableEdit(edtJudge			,!bIdle);
	EnableEdit(edtAdvice		,!bIdle);
	EnableEdit(edtMail			,!bIdle);
	memProxy->Enabled=!bIdle;
  if(memProxy->Enabled)
    memProxy->Color=clWindow;
  else
    memProxy->Color=TColor(RGB(245,245,245)); //clBtnFace;
	EnableCombo(lstCorp,!bIdle);
	EnableCombo(lstTaxType,!bIdle);
	EnableCombo(lstTaxType2,!bIdle);
	EnableEdit(edtEndDate,!bIdle);

	lstCode	->Enabled=bIdle;
	btnQuery->Enabled=bIdle;
	btnNew	->Enabled=bIdle && bAuth;
	btnEdit	->Enabled=bIdle && bAuth && !m_szActiveID.IsEmpty();
	btnMove	->Enabled=bIdle && bAuth && !m_szActiveID.IsEmpty();
	btnPrintAll->Enabled=bIdle;
	btnPrintThis->Enabled=bIdle && !m_szActiveID.IsEmpty();
	btnOK		->Enabled=!bIdle;
	btnExit	->Caption = bIdle ? "退    出" : "放    弃";
}

void TFactoryForm::EmptyEditor()
{
	edtName			->Text="";
	edtShortName->Text="";
	edtLinkMan	->Text="";
	edtTel			->Text="";
	edtFax			->Text="";
	edtAddr			->Text="";
	edtType			->Text="";
	edtArtific	->Text="";
	edtRegmoney	->Text="";
	edtProdAddr	->Text="";
	edtAreaScale->Text="";
	edtManScale	->Text="";
	edtMonthCap	->Text="";
	edtWorkItem	->Text="";
	edtIDAffix	->Text="";
	lstStatus		->Text="";
	edtDate0		->Text="";
	edtDate1		->Text="";
	edtPostCode	->Text="";
	edtTax			->Text="";
	edtBankID		->Text="";
	edtBankName	->Text="";
	edtBankAddr	->Text="";
	edtJudge		->Text="";
	edtAdvice		->Text="";
	edtMail			->Text="";
	memProxy		->Text="";
}

//---------------------------------------------------------------------------
void __fastcall TFactoryForm::FormKeyDown(TObject *Sender, WORD &Key,TShiftState Shift)
{
	if(Key==VK_RETURN && ActiveControl!=memProxy)
		KeyReturnHandle(ActiveControl);
}
//---------------------------------------------------------------------------
void __fastcall TFactoryForm::btnQueryClick(TObject *Sender)
{
	edtID->Text=edtID->Text.Trim();
	if(edtID->Text.IsEmpty())
	{
		ShowMessage("请输入代号");
		if(edtID->CanFocus())	edtID->SetFocus();
		return;
	}
	OnQuery();
	if(m_szActiveID==edtID->Text.c_str())                                   //查询後lstCode自动跳转到合适位置
	{
		int i;
		for(i=0;i<lstCode->Items->Count;i++)
		{
			if(lstCode->Items->Strings[i]==(LPCSTR)m_szActiveID)
			{
				lstCode->ItemIndex=i;
				break;
			}
		}
	}
}

void TFactoryForm::OnQuery()
{
	CString szSQL;
	CFactoryRow row;
  char strID[80],strTemp[256],strBuff[80];
	int i;

  strcpy(strID,edtID->Text.c_str());

	szSQL.Format("select * from Manufactur where mf_code='%s'",strID);
	RunSQL(dm1->Query1,szSQL,true);
	if(dm1->Query1->Eof)
	{
		ShowMessage("没有该编号的数据");
		m_szActiveID="";
		ResetCtrl();
		return;
	}
	row.ReadFromDB(dm1->Query1);

	edtName			->Text=row.mf_name;
	edtShortName->Text=row.mf_shortname;
	edtLinkMan	->Text=row.mf_linkman;
	edtTel			->Text=row.mf_tel;
	edtFax			->Text=row.mf_fax;
	edtAddr			->Text=row.mf_addr;
	edtType			->Text=row.mf_type;
	edtArtific	->Text=row.mf_artific;
	edtRegmoney	->Text=MEMBER2STRING(row,mf_regmoney);
	edtProdAddr	->Text=row.mf_prodaddr;
	edtAreaScale->Text=MEMBER2STRING(row,mf_areascale);
	edtManScale	->Text=MEMBER2STRING(row,mf_manscale);
	edtMonthCap	->Text=MEMBER2STRING(row,mf_monthcap);
	edtWorkItem	->Text=row.mf_workitem;
	edtIDAffix	->Text=row.mf_idaffix;

	strcpy(strBuff,dm1->Query1->FieldByName("mf_corp")->AsString.c_str());
	for(i=0;i<m_lstCorpID.GetSize();i++)
	{
		if(m_lstCorpID[i]==strBuff)
		{
			lstCorp->ItemIndex=i;
			break;
		}
	}
	if(i==m_lstCorpID.GetSize())	lstCorp->ItemIndex=-1;

	strcpy(strBuff,dm1->Query1->FieldByName("mf_taxtype")->AsString.c_str());       //主税别
	for(i=0;i<m_lstTaxID.GetSize();i++)
	{
		if(m_lstTaxID[i]==strBuff)
		{
			lstTaxType->ItemIndex=i;
			break;
		}
	}
	if(i==m_lstTaxID.GetSize())	lstTaxType->ItemIndex=-1;

	strcpy(strBuff,dm1->Query1->FieldByName("mf_taxtype2")->AsString.c_str());       //副税别
	for(i=0;i<m_lstTaxID2.GetSize();i++)
	{
		if(m_lstTaxID2[i]==strBuff)
		{
			lstTaxType2->ItemIndex=i;
			break;
		}
	}
	if(i==m_lstTaxID2.GetSize())	lstTaxType2->ItemIndex=-1;

	if(dm1->Query1->FieldByName("mf_enddate")->IsNull)
		edtEndDate->Text="";
	else
	{
		edtEndDate->Text=(LPCSTR)Date2YYMMDD(dm1->Query1->FieldByName("mf_enddate")->AsDateTime);
	}
		
	for(i=0;i<m_lstStatusID.GetSize();i++)
	{
		if(m_lstStatusID[i]==row.mf_status)
		{
			lstStatus->ItemIndex=i;
			break;
		}
	}
	if(i==m_lstStatusID.GetSize())	lstStatus->ItemIndex=-1;

	edtDate0		->Text=MEMBER2STRING(row,mf_statdate0);
	edtDate1		->Text=MEMBER2STRING(row,mf_statdate1);
	edtPostCode	->Text=row.mf_postcode;
	edtTax			->Text=row.mf_taxcode;
	edtBankID		->Text=row.mf_bankid;
	edtBankName	->Text=row.mf_bankname;
	edtBankAddr	->Text=row.mf_bandaddr;
	edtJudge		->Text=row.mf_judge;
	edtAdvice		->Text=row.mf_advice;
	edtMail			->Text=row.mf_mail;

	memProxy->Lines->Clear();
	szSQL.Format("select * from FactoryProxy where fp_mfcode='%s'",row.mf_code);
	RunSQL(dm1->Query1,szSQL,true);
	while(!dm1->Query1->Eof)
	{
		memProxy->Lines->Add(dm1->Query1->FieldByName("fp_proxy")->AsString);
		dm1->Query1->Next();
	}

	m_szActiveID=row.mf_code;
	ResetCtrl();
}

//---------------------------------------------------------------------------
void __fastcall TFactoryForm::btnNewClick(TObject *Sender)
{
	m_enState=EN_STATE_NEW;
	ResetCtrl();
	if(edtID->CanFocus())	edtID->SetFocus();
}

bool TFactoryForm::IsSameCorp()
{
	int nSel;
	if(strcmp(g_theOperator.op_code,"admin")!=0)
	{
		if((nSel=lstCorp->ItemIndex)>=0 && nSel<m_lstCorpID.GetSize())
		{
			if(m_lstCorpID[nSel]!=g_theOperator.op_cpcode)
			{
				ShowMessage("公司别不同，不能进行修改或删除操作");
				return false;
			}
		}
	}
	return true;
}

//---------------------------------------------------------------------------
void __fastcall TFactoryForm::btnEditClick(TObject *Sender)
{
	if(m_szActiveID.IsEmpty())	return;
	edtID->Text=edtID->Text.Trim();
	if(m_szActiveID!=edtID->Text.c_str())
	{
		ShowMessage("您输入的厂商代号与您正在查询的代号不同，请重新查询");
		if(edtID->CanFocus())	edtID->SetFocus();
		return;
	}
	if(!IsSameCorp())	return;

	m_enState=EN_STATE_EDIT;
	ResetCtrl();
	if(edtName->CanFocus())	edtName->SetFocus();
}
//---------------------------------------------------------------------------
void __fastcall TFactoryForm::btnMoveClick(TObject *Sender)
{
	CString szSQL,szMsg;
	int nSel;

	if(m_szActiveID.IsEmpty())	return;
	if(m_szActiveID!=edtID->Text.c_str())
	{
		ShowMessage("您输入的厂商代号与您正在查询的代号不同，请重新查询");
		if(edtID->CanFocus())	edtID->SetFocus();
		return;
	}
	if(!IsSameCorp())	return;

	if((nSel=lstCode->ItemIndex)<0)	return;
	if(m_szActiveID!=lstCode->Items->Strings[nSel].c_str())	return;

	if(Application->MessageBox("真要删除选定的编号吗","警告",MB_YESNOCANCEL | MB_ICONQUESTION | MB_DEFBUTTON2)!=IDYES)	return;

	try
	{
		BeginTransact();
		szSQL.Format("delete from Manufactur where mf_code='%s'",m_szActiveID);
		if(!RunTransactSQL(szSQL))	goto CANCEL_TRANSACT;
		szSQL.Format("delete from FactoryProxy where fp_mfcode='%s'",m_szActiveID);
		if(!RunTransactSQL(szSQL))	goto CANCEL_TRANSACT;
		CommitTransact();
	}
	catch(...)
	{
		goto CANCEL_TRANSACT;
	}
	lstCode->Items->Delete(nSel);
	m_szActiveID="";
	ResetCtrl();

	return;
CANCEL_TRANSACT:
	RollBackTransact();
	szMsg.Format("数据库操作失败,\nSQL=%s",szSQL);
	ShowMessage((LPCSTR)szMsg);
}

#include "PrnFactory.h"
//---------------------------------------------------------------------------
void __fastcall TFactoryForm::btnPrintThisClick(TObject *Sender)
{
	if(m_szActiveID.IsEmpty())	return;
	DoPrint(m_szActiveID);
}

void __fastcall TFactoryForm::btnPrintAllClick(TObject *Sender)
{
	DoPrint(NULL);
}
//---------------------------------------------------------------------------

void TFactoryForm::DoPrint(LPCSTR lpszID)
{
	TPrnFactoryForm *pPrn;
  CString szSQL;
	if(lpszID!=NULL)
		szSQL.Format("select * from Manufactur,DicStatus where mf_status*=ds_code and mf_code='%s'",lpszID);
	else
		szSQL="select * from Manufactur,DicStatus where mf_status*=ds_code order by mf_code";
  if(!OpenQuery(dm1->sqlPrint,szSQL))	return;
  try
  {
  	pPrn=new TPrnFactoryForm(this);
    pPrn->PrnView->PreviewModal();
    delete pPrn;
  }
  catch(...)
  {
  }
}

bool TFactoryForm::DetectInput(CStringArray &lstProxy)
{
	int i,nSel;
	char strMsg[256];

	edtID				->Text=edtID				->Text.Trim();
	edtName			->Text=edtName			->Text.Trim();
	edtShortName->Text=edtShortName	->Text.Trim();
	edtLinkMan	->Text=edtLinkMan		->Text.Trim();
	edtTel			->Text=edtTel				->Text.Trim();
	edtFax			->Text=edtFax				->Text.Trim();
	edtAddr			->Text=edtAddr			->Text.Trim();
	edtType			->Text=edtType			->Text.Trim();
	edtArtific	->Text=edtArtific		->Text.Trim();
	edtRegmoney	->Text=edtRegmoney	->Text.Trim();
	edtProdAddr	->Text=edtProdAddr	->Text.Trim();
	edtAreaScale->Text=edtAreaScale	->Text.Trim();
	edtManScale	->Text=edtManScale	->Text.Trim();
	edtMonthCap	->Text=edtMonthCap	->Text.Trim();
	edtWorkItem	->Text=edtWorkItem	->Text.Trim();
	edtIDAffix	->Text=edtIDAffix		->Text.Trim();
	lstStatus		->Text=lstStatus		->Text.Trim();
	edtDate0		->Text=edtDate0			->Text.Trim();
	edtDate1		->Text=edtDate1			->Text.Trim();
	edtPostCode	->Text=edtPostCode	->Text.Trim();
	edtTax			->Text=edtTax				->Text.Trim();
	edtBankID		->Text=edtBankID		->Text.Trim();
	edtBankName	->Text=edtBankName	->Text.Trim();
	edtBankAddr	->Text=edtBankAddr	->Text.Trim();
	edtJudge		->Text=edtJudge			->Text.Trim();
	edtAdvice		->Text=edtAdvice		->Text.Trim();
	edtMail			->Text=edtMail			->Text.Trim();
	for(i=0;i<memProxy->Lines->Count;i++)
	{
		memProxy->Lines->Strings[i]=memProxy->Lines->Strings[i].Trim();
		if(memProxy->Lines->Strings[i].IsEmpty())	continue;
		if(memProxy->Lines->Strings[i].Length()>200)
		{
			sprintf(strMsg,"代理品牌的第 %d 行长度超过了数据库长度200",i);
			ShowMessage(strMsg);
			if(memProxy->CanFocus())	memProxy->SetFocus();
			return false;
		}
		lstProxy.Add(memProxy->Lines->Strings[i].c_str());
	}
	if(lstProxy.GetSize()>8)
	{
		ShowMessage("代理品牌个数请不要超过8个");
		if(memProxy->CanFocus())	memProxy->SetFocus();
		return false;
	}

	if(m_enState==EN_STATE_NEW)
	{
		if(edtID->Text.IsEmpty())
		{
			ShowMessage("请输入厂商代号");
			if(edtID->CanFocus())	edtID->SetFocus();
			return false;
		}
	}
	if(edtName->Text.IsEmpty())
	{
		ShowMessage("请输入厂商名称");
		if(edtName->CanFocus())	edtName->SetFocus();
		return false;
	}
	if(edtShortName->Text.IsEmpty())
	{
		ShowMessage("请输入厂商简称");
		if(edtShortName->CanFocus())	edtShortName->SetFocus();
		return false;
	}
	if(edtAreaScale->Text.IsEmpty())
	{
		ShowMessage("请输入工厂面积");
		if(edtAreaScale->CanFocus())	edtAreaScale->SetFocus();
		return false;
	}
	if(edtManScale->Text.IsEmpty())
	{
		ShowMessage("请输入工厂员工人数");
		if(edtManScale->CanFocus())	edtManScale->SetFocus();
		return false;
	}
	if(edtMonthCap->Text.IsEmpty())
	{
		ShowMessage("请输入月业务能力");
		if(edtMonthCap->CanFocus())	edtMonthCap->SetFocus();
		return false;
	}
	if(!edtAreaScale->Text.IsEmpty() && !StringIsInt(edtAreaScale->Text.c_str()))
	{
		ShowMessage("请输入整数");
		if(edtAreaScale->CanFocus())	edtAreaScale->SetFocus();
		return false;
	}
	if(!edtManScale->Text.IsEmpty() && !StringIsInt(edtManScale->Text.c_str()))
	{
		ShowMessage("请输入整数");
		if(edtManScale->CanFocus())	edtManScale->SetFocus();
		return false;
	}
	if(!edtMonthCap->Text.IsEmpty() && !StringIsInt(edtMonthCap->Text.c_str()))
	{
		ShowMessage("请输入整数");
		if(edtMonthCap->CanFocus())	edtMonthCap->SetFocus();
		return false;
	}

	if((nSel=lstStatus->ItemIndex)<0 || nSel>=m_lstStatusID.GetSize())
	{
		ShowMessage("请选择一个有效的状态别");
		if(lstStatus->CanFocus())	lstStatus->SetFocus();
		return false;
	}
	if(edtDate0->Text.IsEmpty())
	{
		ShowMessage("请输入状态起始日");
		if(edtDate0->CanFocus())	edtDate0->SetFocus();
		return false;
	}
	if(edtDate1->Text.IsEmpty())
	{
		ShowMessage("请输入状态截止日");
		if(edtDate1->CanFocus())	edtDate1->SetFocus();
		return false;
	}
  if(!edtDate0->Text.IsEmpty())
  {
  	TDateTime tDate;
    int nYear,nMonth,nDay;

    if(edtDate0->Text.Length()!=8)
    {
    	ShowMessage("不合法的日期格式，日期格式为：yyyymmdd");
      if(edtDate0->CanFocus())	edtDate0->SetFocus();
      return false;
    }
    Date2YYMMDD(edtDate0->Text.c_str(),nYear,nMonth,nDay);
    try
    {
    	tDate=TDateTime(nYear,nMonth,nDay);
    }
    catch(...)
    {
    	ShowMessage("不合法的日期格式，日期格式为：yyyymmdd");
      if(edtDate0->CanFocus())	edtDate0->SetFocus();
      return false;
    }

    if(edtDate1->Text.IsEmpty())
    {
    	ShowMessage("当开始日期不为空时，必须输入截止日期");
      if(edtDate1->CanFocus())	edtDate1->SetFocus();
      return false;
    }
    if(edtDate1->Text.Length()!=8)
    {
    	ShowMessage("不合法的日期格式，日期格式为：yyyymmdd");
      if(edtDate1->CanFocus())	edtDate1->SetFocus();
      return false;
    }
    Date2YYMMDD(edtDate1->Text.c_str(),nYear,nMonth,nDay);
    try
    {
    	tDate=TDateTime(nYear,nMonth,nDay);
    }
    catch(...)
    {
    	ShowMessage("不合法的日期格式，日期格式为：yyyymmdd");
      if(edtDate1->CanFocus())	edtDate1->SetFocus();
      return false;
    }
  }

	return true;
}

//---------------------------------------------------------------------------
void __fastcall TFactoryForm::btnOKClick(TObject *Sender)
{
	CStringArray lstProxy;

	if(!DetectInput(lstProxy))	return;
	if(m_enState==EN_STATE_NEW)
		OnAddnew(lstProxy);
	else
		OnEdit(lstProxy);
}

void TFactoryForm::OnAddnew(CStringArray &lstProxy)
{
	CString szSQL,szMsg;
	char strID[80],strDate0[80],strDate1[80],strTemp[256],strCorp[80],strTax[80],strTax2[80],strEndDate[80];
	int nStatus,i,nSel;

	nStatus=lstStatus->ItemIndex;
	Date2Dbdate(edtDate0->Text.c_str(),strDate0);
	Date2Dbdate(edtDate1->Text.c_str(),strDate1);

	strcpy(strID,edtID->Text.c_str());

	szSQL.Format("select * from Manufactur where mf_code='%s'",strID);
	RunSQL(dm1->Query1,szSQL,true);
	if(!dm1->Query1->Eof)
	{
		ShowMessage("数据库中已有该编号");
		if(edtID->CanFocus())	edtID->SetFocus();
		return;
	}

	if((nSel=lstCorp->ItemIndex)>=0 && nSel<m_lstCorpID.GetSize())
		strcpy(strCorp,m_lstCorpID[nSel]);
	else
		strCorp[0]='\0';
	if((nSel=lstTaxType->ItemIndex)>=0 && nSel<m_lstTaxID.GetSize())
		sprintf(strTax,m_lstTaxID[nSel]);
	else
//		strTax[0]='\0';
        {
                ShowMessage("请选择主税别");
                return;
        }

	if((nSel=lstTaxType2->ItemIndex)>=0 && nSel<m_lstTaxID2.GetSize())
		sprintf(strTax2,m_lstTaxID2[nSel]);
	else
		strTax2[0]='\0';

	if(!edtEndDate->Text.IsEmpty())
	{
		if(!CheckDateEditor(edtEndDate))	return;
		Date2Dbdate(edtEndDate->Text.c_str(),strEndDate);
	}
	else
		strEndDate[0]='\0';

	try
	{
		BeginTransact();

		szSQL="insert into Manufactur (mf_code,mf_name,mf_shortname,mf_linkman,mf_tel,mf_fax,"
			"mf_addr,mf_type,mf_artific,mf_regmoney,mf_prodaddr,mf_areascale,mf_manscale,mf_monthcap,"
			"mf_workitem,mf_idaffix,mf_status,mf_statdate0,mf_statdate1,mf_postcode,mf_taxcode,"
			"mf_bankid,mf_bankname,mf_bandaddr,mf_judge,mf_advice,mf_mail,mf_inputdate,mf_corp,mf_taxtype,mf_enddate,mf_taxtype2"
			") values(";
		szSQL+=Str2DBString(strID);
		szSQL+=",";	szSQL+=Str2DBString(edtName			->Text.c_str());
		szSQL+=",";	szSQL+=Str2DBString(edtShortName->Text.c_str());
		szSQL+=",";	szSQL+=Str2DBString(edtLinkMan	->Text.c_str());
		szSQL+=",";	szSQL+=Str2DBString(edtTel			->Text.c_str());
		szSQL+=",";	szSQL+=Str2DBString(edtFax			->Text.c_str());
		szSQL+=",";	szSQL+=Str2DBString(edtAddr			->Text.c_str());
		szSQL+=",";	szSQL+=Str2DBString(edtType			->Text.c_str());
		szSQL+=",";	szSQL+=Str2DBString(edtArtific	->Text.c_str());
		szSQL+=",";	szSQL+=Str2DBString(edtRegmoney	->Text.c_str());
		szSQL+=",";	szSQL+=Str2DBString(edtProdAddr	->Text.c_str());
		szSQL+=",";	szSQL+=Int2DBString(atoi(edtAreaScale->Text.c_str()));
		szSQL+=",";	szSQL+=Int2DBString(atoi(edtManScale->Text.c_str()));
		szSQL+=",";	szSQL+=Int2DBString(atoi(edtMonthCap->Text.c_str()));
		szSQL+=",";	szSQL+=Str2DBString(edtWorkItem	->Text.c_str());
		szSQL+=",";	szSQL+=Str2DBString(edtIDAffix	->Text.c_str());
		szSQL+=",";	szSQL+=Str2DBString(m_lstStatusID[nStatus]);
		szSQL+=",";	szSQL+=Str2DBString(strDate0);
		szSQL+=",";	szSQL+=Str2DBString(strDate1);
		szSQL+=",";	szSQL+=Str2DBString(edtPostCode	->Text.c_str());
		szSQL+=",";	szSQL+=Str2DBString(edtTax			->Text.c_str());
		szSQL+=",";	szSQL+=Str2DBString(edtBankID		->Text.c_str());
		szSQL+=",";	szSQL+=Str2DBString(edtBankName	->Text.c_str());
		szSQL+=",";	szSQL+=Str2DBString(edtBankAddr	->Text.c_str());
		szSQL+=",";	szSQL+=Str2DBString(edtJudge		->Text.c_str());
		szSQL+=",";	szSQL+=Str2DBString(edtAdvice		->Text.c_str());
		szSQL+=",";	szSQL+=Str2DBString(edtMail			->Text.c_str());
		szSQL+=",getdate()";
		szSQL+=",";	szSQL+=Str2DBString(strCorp);
		szSQL+=",";	szSQL+=Str2DBString(strTax);
		szSQL+=",";	szSQL+=Str2DBString(strEndDate);
		szSQL+=",";	szSQL+=Str2DBString(strTax2);                   //副税率
		szSQL+=")";
		if(!RunTransactSQL(szSQL))	goto CANCEL_TRANSACT;

		szSQL.Format("delete FactoryProxy where fp_mfcode='%s'",strID);
		if(!RunTransactSQL(szSQL))	goto CANCEL_TRANSACT;

		for(i=0;i<lstProxy.GetSize();i++)
		{
			if(lstProxy[i].IsEmpty())	continue;
			szSQL.Format("insert into FactoryProxy (fp_mfcode,fp_proxy) values(%s,%s)",
				Str2DBString(strID),Str2DBString(lstProxy[i]));
			if(!RunTransactSQL(szSQL))	goto CANCEL_TRANSACT;
		}

		CommitTransact();
	}
	catch(...)
	{
		goto CANCEL_TRANSACT;
	}
	lstCode->Items->Add(strID);
	lstCode->ItemIndex=lstCode->Items->Count-1;
	m_szActiveID=strID;
	m_enState=EN_STATE_IDLE;
	ResetCtrl();
	if(btnNew->CanFocus())	btnNew->SetFocus();
	return;

CANCEL_TRANSACT:
	RollBackTransact();
	szMsg.Format("数据库操作失败,\nSQL=%s",szSQL);
	ShowMessage((LPCSTR)szMsg);
}

void TFactoryForm::OnEdit(CStringArray &lstProxy)
{
	CString szSQL,szMsg;
	char strID[80],strDate0[80],strDate1[80],strDateSrc0[80],strDateSrc1[80];
	char strCorp[80],strTax[80],strTax2[80],strEndDate[80];
	int nStatus,i,nSel;

	if(m_szActiveID.IsEmpty())	return;

	nStatus=lstStatus->ItemIndex;
	strcpy(strDateSrc0,edtDate0->Text.c_str());
	strcpy(strDateSrc1,edtDate1->Text.c_str());
	Date2Dbdate(strDateSrc0,strDate0);
	Date2Dbdate(strDateSrc1,strDate1);

	strcpy(strID,edtID->Text.c_str());

	szSQL.Format("select * from Manufactur where mf_code='%s'",strID);
	RunSQL(dm1->Query1,szSQL,true);
	if(dm1->Query1->Eof)
	{
		ShowMessage("数据库中没有该编号");
		if(edtID->CanFocus())	edtID->SetFocus();
		return;
	}
	strcpy(strID,edtID->Text.c_str());

	if((nSel=lstCorp->ItemIndex)>=0 && nSel<m_lstCorpID.GetSize())
		strcpy(strCorp,m_lstCorpID[nSel]);
	else
		strCorp[0]='\0';
	if((nSel=lstTaxType->ItemIndex)>=0 && nSel<m_lstTaxID.GetSize())
		sprintf(strTax,m_lstTaxID[nSel]);
	else
//		strTax[0]='\0';
        {
                ShowMessage("请选择主税别");
                return;
        }
	if((nSel=lstTaxType2->ItemIndex)>=0 && nSel<m_lstTaxID2.GetSize())
		sprintf(strTax2,m_lstTaxID2[nSel]);
	else
		strTax2[0]='\0';

	if(!edtEndDate->Text.IsEmpty())
	{
		if(!CheckDateEditor(edtEndDate))	return;
		Date2Dbdate(edtEndDate->Text.c_str(),strEndDate);
	}
	else
		strEndDate[0]='\0';

	try
	{
		BeginTransact();

		szSQL="update Manufactur set";
		szSQL+=" mf_name=";			szSQL+=Str2DBString(edtName			->Text.c_str());
		szSQL+=",mf_shortname=";szSQL+=Str2DBString(edtShortName->Text.c_str());
		szSQL+=",mf_linkman=";	szSQL+=Str2DBString(edtLinkMan	->Text.c_str());
		szSQL+=",mf_tel=";			szSQL+=Str2DBString(edtTel			->Text.c_str());
		szSQL+=",mf_fax=";			szSQL+=Str2DBString(edtFax			->Text.c_str());
		szSQL+=",mf_addr=";			szSQL+=Str2DBString(edtAddr			->Text.c_str());
		szSQL+=",mf_type=";			szSQL+=Str2DBString(edtType			->Text.c_str());
		szSQL+=",mf_artific=";	szSQL+=Str2DBString(edtArtific	->Text.c_str());
		szSQL+=",mf_regmoney=";	szSQL+=Str2DBString(edtRegmoney	->Text.c_str());
		szSQL+=",mf_prodaddr=";	szSQL+=Str2DBString(edtProdAddr	->Text.c_str());
		szSQL+=",mf_areascale=";szSQL+=Int2DBString(atoi(edtAreaScale->Text.c_str()));
		szSQL+=",mf_manscale=";	szSQL+=Int2DBString(atoi(edtManScale->Text.c_str()));
		szSQL+=",mf_monthcap=";	szSQL+=Int2DBString(atoi(edtMonthCap->Text.c_str()));
		szSQL+=",mf_workitem=";	szSQL+=Str2DBString(edtWorkItem	->Text.c_str());
		szSQL+=",mf_idaffix=";	szSQL+=Str2DBString(edtIDAffix	->Text.c_str());
		szSQL+=",mf_status=";		szSQL+=Str2DBString(m_lstStatusID[nStatus]);
		szSQL+=",mf_statdate0=";szSQL+=Str2DBString(strDate0);
		szSQL+=",mf_statdate1=";szSQL+=Str2DBString(strDate1);
		szSQL+=",mf_postcode=";	szSQL+=Str2DBString(edtPostCode	->Text.c_str());
		szSQL+=",mf_taxcode=";	szSQL+=Str2DBString(edtTax			->Text.c_str());
		szSQL+=",mf_bankid=";		szSQL+=Str2DBString(edtBankID		->Text.c_str());
		szSQL+=",mf_bankname=";	szSQL+=Str2DBString(edtBankName	->Text.c_str());
		szSQL+=",mf_bandaddr=";	szSQL+=Str2DBString(edtBankAddr	->Text.c_str());
		szSQL+=",mf_judge=";		szSQL+=Str2DBString(edtJudge		->Text.c_str());
		szSQL+=",mf_advice=";		szSQL+=Str2DBString(edtAdvice		->Text.c_str());
		szSQL+=",mf_mail=";			szSQL+=Str2DBString(edtMail			->Text.c_str());
		szSQL+=",mf_corp=";			szSQL+=Str2DBString(strCorp);
		szSQL+=",mf_taxtype=";	szSQL+=Str2DBString(strTax);
		szSQL+=",mf_enddate=";	szSQL+=Str2DBString(strEndDate);
		szSQL+=",mf_taxtype2=";	szSQL+=Str2DBString(strTax2);
		szSQL+=" where mf_code=";		szSQL+=Str2DBString(strID);

		if(!RunTransactSQL(szSQL))	goto CANCEL_TRANSACT;

		szSQL.Format("delete FactoryProxy where fp_mfcode='%s'",strID);
		if(!RunTransactSQL(szSQL))	goto CANCEL_TRANSACT;

		for(i=0;i<lstProxy.GetSize();i++)
		{
			if(lstProxy[i].IsEmpty())	continue;
			szSQL.Format("insert into FactoryProxy (fp_mfcode,fp_proxy) values(%s,%s)",
				Str2DBString(strID),Str2DBString(lstProxy[i]));
			if(!RunTransactSQL(szSQL))	goto CANCEL_TRANSACT;
		}

		CommitTransact();
	}
	catch(...)
	{
		goto CANCEL_TRANSACT;
	}
	m_enState=EN_STATE_IDLE;
	ResetCtrl();
	if(btnEdit->CanFocus())	btnEdit->SetFocus();
	return;

CANCEL_TRANSACT:
	RollBackTransact();
	szMsg.Format("数据库操作失败,\nSQL=%s",szSQL);
	ShowMessage((LPCSTR)szMsg);
}

//---------------------------------------------------------------------------
void __fastcall TFactoryForm::btnExitClick(TObject *Sender)
{
	if(m_enState==EN_STATE_IDLE)
		Close();
	else
	{
		m_enState=EN_STATE_IDLE;
		ResetCtrl();
	}
}
//---------------------------------------------------------------------------
void __fastcall TFactoryForm::lstCodeClick(TObject *Sender)
{
	int nSel;
  if((nSel=lstCode->ItemIndex)<0)
  {
  	m_szActiveID="";
    EmptyEditor();
    ResetCtrl();
    return;
  }
  edtID->Text=lstCode->Items->Strings[nSel];
  OnQuery();
}
//---------------------------------------------------------------------------


void __fastcall TFactoryForm::lstCorpExit(TObject *Sender)
{
	HandleListboxExit(lstCorp,&m_lstCorpID);	
}
//---------------------------------------------------------------------------

void __fastcall TFactoryForm::lstTaxTypeExit(TObject *Sender)
{
	HandleListboxExit(lstTaxType,&m_lstTaxID);
}
//---------------------------------------------------------------------------

void __fastcall TFactoryForm::lstSearchCorpExit(TObject *Sender)
{
	HandleListboxExit(lstCorp,&m_lstSearchCorpID);	
}
//---------------------------------------------------------------------------

void __fastcall TFactoryForm::btnCorpFreshClick(TObject *Sender)
{
	RefreshIDList();

 	m_szActiveID="";
  EmptyEditor();
  ResetCtrl();
}
//---------------------------------------------------------------------------

void __fastcall TFactoryForm::btnPickClientClick(TObject *Sender)
{
	TFactorySearchForm *pForm;

  pForm=new TFactorySearchForm(this);
  assert(pForm!=NULL);
  if(pForm->ShowModal()==mrOk && !pForm->m_szID.IsEmpty())
  {
  	edtID->Text=(LPCSTR)pForm->m_szID;
    btnQueryClick(NULL);
  }
  delete pForm;

}
//---------------------------------------------------------------------------




void __fastcall TFactoryForm::lstTaxType2Exit(TObject *Sender)
{
	HandleListboxExit(lstTaxType2,&m_lstTaxID2);        
}
//---------------------------------------------------------------------------

