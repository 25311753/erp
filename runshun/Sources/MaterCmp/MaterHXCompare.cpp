//---------------------------------------------------------------------------

#include <vcl.h>
#include <stdio.h>
#include <assert.h>
#pragma hdrstop

#include "DataModule.h"
#include "BaseCode.h"
#include "MaterHXCompare.h"
#include "LdyInterface.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TMaterHXCompareForm *MaterHXCompareForm;

//-----------------------------------------------------------------------------
//宏信技术代号与材料编号对照表接口，文件：MaterHXCompare.*
void MaterHXCompare(int nAuth)
{
	TMaterHXCompareForm *pForm;
	pForm=new TMaterHXCompareForm(Application);
	assert(pForm!=NULL);
	pForm->m_nAuthor=nAuth;
	pForm->ShowModal();
	delete pForm;
}


//---------------------------------------------------------------------------
__fastcall TMaterHXCompareForm::TMaterHXCompareForm(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TMaterHXCompareForm::btnExitClick(TObject *Sender)
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
void __fastcall TMaterHXCompareForm::FormShow(TObject *Sender)
{
	edtTech->Text="";
	edtType->Text="";
	edtMater->Text="";
	edtSpec->Text="";

	EnableEdit(edtTech,false);
	EnableEdit(edtType,false);
	EnableEdit(edtSpec,false);

	m_enState=EN_STATE_IDLE;
	ResetCtrl();

	RefreshData();
}
//---------------------------------------------------------------------------

void TMaterHXCompareForm::ResetCtrl()
{
	bool bAuth = m_nAuthor==AUTH_FULL;
	bool bIdle = m_enState==EN_STATE_IDLE;

	btnEdit->Enabled = lstView->Selected!=NULL && bIdle && bAuth;
	btnOK->Enabled = !bIdle;
	btnExit->Caption = bIdle ? "退　出" : "放　弃";
	lstView->Enabled = bIdle;
	btnRefresh->Enabled=bIdle;
	btnPrint->Enabled = bIdle;
	
//	EnableEdit(edtTech	,!bIdle);
	EnableEdit(edtMater	,!bIdle);	
	btnPickup->Enabled = !bIdle;
}

void __fastcall TMaterHXCompareForm::btnRefreshClick(TObject *Sender)
{
	RefreshData();
}
//---------------------------------------------------------------------------

void TMaterHXCompareForm::RefreshData()
{
	TListItem *pItem;
	CString szSQL;

	lstView->Items->Clear();
	if(!dm1->OpenDatabase(dm1->db2))	return;

	szSQL="select * from MeterTech,MeterTechType where mt_type=mtt_code order by mt_code";
	dm1->sqlElse->DatabaseName="hxerpdb";
	RunSQL(dm1->sqlElse,szSQL,true);
	while(!dm1->sqlElse->Eof)
	{
		pItem=lstView->Items->Add();
		assert(pItem!=NULL);
		pItem->Caption=dm1->sqlElse->FieldByName("mt_code")->AsString;
		pItem->SubItems->Add(dm1->sqlElse->FieldByName("mtt_name")->AsString);
		pItem->SubItems->Add("");
		pItem->SubItems->Add("");

		dm1->sqlElse->Next();
	}
	
	szSQL="select * from MaterHXCmp,materialno where hx_mncode=mn_code order by hx_tech";
	RunSQL(dm1->Query1,szSQL,true);
	
	int nItem;
	char strID[80];

	nItem=0;
	while(!dm1->Query1->Eof)
	{
		strcpy(strID,dm1->Query1->FieldByName("hx_tech")->AsString.c_str());
		for(;nItem<lstView->Items->Count;nItem++)
		{
			if(lstView->Items->Item[nItem]->Caption==strID)
			{
				pItem=lstView->Items->Item[nItem];
				pItem->SubItems->Strings[1]=dm1->Query1->FieldByName("mn_code")->AsString;
				pItem->SubItems->Strings[2]=dm1->Query1->FieldByName("mn_name")->AsString;
				break;
			}
		}
		dm1->Query1->Next();
	}
}

void __fastcall TMaterHXCompareForm::lstViewSelectItem(TObject *Sender,TListItem *Item, bool Selected)
{
	TListItem *pItem;

	if(!Selected)	return;
	if((pItem=lstView->Selected)==NULL)	return;

	edtTech->Text	=pItem->Caption;
	edtType->Text	=pItem->SubItems->Strings[0];
	edtMater->Text=pItem->SubItems->Strings[1];
	edtSpec->Text	=pItem->SubItems->Strings[2];

	ResetCtrl();
}
//---------------------------------------------------------------------------

void __fastcall TMaterHXCompareForm::lstViewClick(TObject *Sender)
{
	if(lstView->Selected==NULL)	ResetCtrl();
}
//---------------------------------------------------------------------------

#include "AskPurchaseMT.h"
void __fastcall TMaterHXCompareForm::btnPickupClick(TObject *Sender)
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

void __fastcall TMaterHXCompareForm::btnEditClick(TObject *Sender)
{
	m_enState=EN_STATE_EDIT;
	ResetCtrl();

	if(edtMater->CanFocus())	edtMater->SetFocus();
}
//---------------------------------------------------------------------------

void __fastcall TMaterHXCompareForm::edtMaterExit(TObject *Sender)
{
	CString szSQL;
	edtMater->Text=edtMater->Text.Trim();
	if(edtMater->Text.IsEmpty())
	{
		edtSpec->Text="";
	}
	else
	{
		szSQL.Format("select * from materialno where mn_code='%s'",edtMater->Text.c_str());
		RunSQL(dm1->Query1,szSQL,true);
		if(dm1->Query1->Eof)
			edtSpec->Text="";
		else
			edtSpec->Text=dm1->Query1->FieldByName("mn_name")->AsString;
	}
}
//---------------------------------------------------------------------------

void __fastcall TMaterHXCompareForm::btnOKClick(TObject *Sender)
{
	TListItem *pItem;
	CString szSQL;

	if((pItem=lstView->Selected)==NULL)	return;
	if(edtTech->Text.IsEmpty())	return;

	edtMater->Text=edtMater->Text.Trim();
	if(!edtMater->Text.IsEmpty())
	{
		szSQL.Format("select * from materialno where mn_code='%s'",edtMater->Text.c_str());
		RunSQL(dm1->Query1,szSQL,true);
		if(dm1->Query1->Eof)
		{
			ShowMessage("没有该材料编号");
			if(edtMater->CanFocus())	edtMater->SetFocus();
			return;
		}
	}

	try
	{
		BeginTransact();
		szSQL.Format("delete MaterHXCmp where hx_tech='%s'",edtTech->Text.c_str());
		RunTransactSQL(szSQL);

		if(!edtMater->Text.IsEmpty())
		{
			szSQL="insert into MaterHXCmp (hx_tech,hx_mncode) values(";
			szSQL+=Str2DBString(edtTech->Text.c_str());
			szSQL+=",";	szSQL+=Str2DBString(edtMater->Text.c_str());
			szSQL+=")";
			RunTransactSQL(szSQL);
		}
		CommitTransact();
	}
	catch(...)
	{
		RollBackTransact();
		ShowMessage("数据库操作异常");
		return;
	}

	pItem->SubItems->Strings[1]=edtMater->Text;
	pItem->SubItems->Strings[2]=edtSpec->Text;

	m_enState=EN_STATE_IDLE;
	ResetCtrl();
}
//---------------------------------------------------------------------------

#include "PrnBaseData.h"
void __fastcall TMaterHXCompareForm::btnPrintClick(TObject *Sender)
{
	CString szSQL,szTable;
	int i;
	TListItem *pItem;
  TPrnBaseDataForm *pForm;

	szTable=GetTmpTableName();
	try
	{
		BeginTransact();
		szSQL.Format("create table dbo.%s ("
			"hx_tech    varchar(80),"
			"hx_type    varchar(80),"
			"hx_mncode  varchar(80),"
			"hx_mnname  varchar(80))",szTable);
		RunTransactSQL(szSQL);
		
		for(i=0;i<lstView->Items->Count;i++)
		{
			pItem=lstView->Items->Item[i];
			szSQL.Format("insert into %s values(",szTable);
			szSQL+=Str2DBString(pItem->Caption.c_str());
			szSQL+=",";	szSQL+=Str2DBString(pItem->SubItems->Strings[0].c_str());
			szSQL+=",";	szSQL+=Str2DBString(pItem->SubItems->Strings[1].c_str());
			szSQL+=",";	szSQL+=Str2DBString(pItem->SubItems->Strings[2].c_str());
			szSQL+=")";
			RunTransactSQL(szSQL);
		}
		CommitTransact();
	}
	catch(...)
	{
		RollBackTransact();
		ShowMessage("数据库操作异常");
		return;
	}

  szSQL.Format("select hx_tech as prnID,hx_type as prnName,hx_mncode as prnText2,hx_mnname as prnText3"
		" from %s order by hx_tech",szTable);
  if(OpenQuery(dm1->sqlPrint,szSQL))
  {
		try
		{
			TPrnBaseDataForm *pForm;
  		pForm=new TPrnBaseDataForm(this);
			assert(pForm!=NULL);

			pForm->txtTitle->Caption="宏信技术代号与材料编号对照表";
			pForm->txtText0->Caption="技术代号";
			pForm->txtText1->Caption="类别";
			pForm->txtText2->Caption="材料编号";
			pForm->txtText3->Caption="品名规格";

      pForm->PrnView->Page->Orientation=poLandscape;
			pForm->PrnView->PreviewModal() ;
			delete pForm;
		}
		catch(...)
		{
			ShowMessage("打印机返回错误信息，请检查是否安装并设置了默认打印机");
		}
	}	
	szSQL.Format("drop table dbo.%s",szTable);
	RunSQL(dm1->Query1,szSQL);
}
//---------------------------------------------------------------------------

void __fastcall TMaterHXCompareForm::edtMaterKeyUp(TObject *Sender,
      WORD &Key, TShiftState Shift)
{
	if(Key==VK_RETURN)
  {
  	if(btnOK->CanFocus())	btnOK->SetFocus();
  }
}
//---------------------------------------------------------------------------

