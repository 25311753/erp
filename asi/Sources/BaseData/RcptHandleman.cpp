//---------------------------------------------------------------------------

#include <vcl.h>
#include <stdio.h>
#pragma hdrstop

#include "DataModule.h"
#include "BaseCode.h"
#include "RcptHandleman.h"
#include "LdyInterface.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TRcptHandlemanForm *RcptHandlemanForm;

// ==================================================================
//收货经办档接口，文件RcptHandleman.*
void RcptHandleman(int nAuth)
{
	if(nAuth==AUTH_NONE)
  {
  	ShowMessage("抱歉，您没有这个权限");
    return;
  }

  TRcptHandlemanForm *pForm;
	try
	{
  	pForm=new TRcptHandlemanForm(Application);
  }
	catch (Exception &exception)
	{
		Application->ShowException(&exception);
    return;
	}
  pForm->m_nAuthor=nAuth;
  pForm->ShowModal();
  delete pForm;
}
// ==================================================================


__fastcall TRcptHandlemanForm::TRcptHandlemanForm(TComponent* Owner)
  : TForm(Owner)
{
  m_enWorkState=EN_IDLE;
}
//---------------------------------------------------------------------------

void __fastcall TRcptHandlemanForm::btnRefreshClick(TObject *Sender)
{
  RefreshData();
  ResetCtrl();
}
//---------------------------------------------------------------------------


// --------------------------------------------------------------------------
void TRcptHandlemanForm::Row2Editor()
{
  TListItem *pItem;

  pItem=ListView1->Selected;
  if(pItem==NULL)	return;
  edtID		->Text=pItem->Caption;
  edtName	->Text=pItem->SubItems->Strings[0];
	edtTel	->Text=pItem->SubItems->Strings[1];
  lstCorp->ItemIndex=lstCorp->Items->IndexOf(pItem->SubItems->Strings[2]);
}


//---------------------------------------------------------------------------

void TRcptHandlemanForm::RefreshData()
{
  char strBuff[512],strDep[80];
  TListItem *pItem;
	int i;

  if(!dm1->OpenDatabase())  return;
  try
  {
    dm1->Query1->SQL->Clear();
    dm1->Query1->SQL->Add("select * from RcptHandleman order by rh_code");

    dm1->Query1->Prepare();
    dm1->Query1->Open();
    dm1->Query1->First();
    ListView1->Items->Clear();
    while(!dm1->Query1->Eof)
    {
    	pItem=ListView1->Items->Add();
      pItem->Caption=dm1->Query1->FieldByName("rh_code")->AsString;
      pItem->SubItems->Add(dm1->Query1->FieldByName("rh_name")->AsString);
			pItem->SubItems->Add(dm1->Query1->FieldByName("rh_tel")->AsString);
      strcpy(strBuff,dm1->Query1->FieldByName("rh_cpcode")->AsString.c_str());
      for(i=0;i<m_lstCorpID.GetSize();i++)
      {
      	if(m_lstCorpID[i]==strBuff)
        {
        	pItem->SubItems->Add(lstCorp->Items->Strings[i]);
          break;
        }
      }
      if(i==m_lstCorpID.GetSize())	pItem->SubItems->Add("");
      dm1->Query1->Next();
    }
  }
  catch(...)
  {
    ShowMessage("数据库操作错误!");
    return;
  }
}

void __fastcall TRcptHandlemanForm::btnAddNewClick(TObject *Sender)
{
  edtID->Text="";
  edtName->Text="";
	edtTel->Text="";
  m_enWorkState=EN_ADDNEW;
  ResetCtrl();
  msgState->Caption="工作状态：新增";
  edtID->SetFocus();
}
//---------------------------------------------------------------------------

void __fastcall TRcptHandlemanForm::btnEditClick(TObject *Sender)
{
  m_enWorkState=EN_EDIT;
  ResetCtrl();
  msgState->Caption="工作状态：修改";
  edtName->SetFocus();
}
//---------------------------------------------------------------------------


void __fastcall TRcptHandlemanForm::btnCancel0Click(TObject *Sender)
{
  int nState;

  nState=m_enWorkState;
  m_enWorkState=EN_IDLE;
  ResetCtrl();
  msgState->Caption="工作状态：查询";
  Row2Editor();
  switch(nState)
  { //设置确定後的光标位置
    case EN_ADDNEW: btnAddNew->SetFocus();  break;
    case EN_EDIT:   btnEdit->SetFocus();    break;
    default:  break;
  }
}
//---------------------------------------------------------------------------

void __fastcall TRcptHandlemanForm::btnOK0Click(TObject *Sender)
{
  char strID[80],strName[80],*ptr,strTemp[80],strCorp[80];
  int nState,nSel;

  edtID->Text=edtID->Text.Trim();
  edtName->Text=edtName->Text.Trim();

  if(edtID->Text.IsEmpty())
  {
  	ShowMessage("请输入编号");
    if(edtID->CanFocus())	edtID->SetFocus();
    return;
  }
  if(edtName->Text.IsEmpty())
  {
  	ShowMessage("请输入名称");
    if(edtName->CanFocus())	edtName->SetFocus();
    return;
  }
	edtTel->Text=edtTel->Text.Trim();
  if((nSel=lstCorp->ItemIndex)<0 || nSel>=m_lstCorpID.GetSize())
  {
  	ShowMessage("请选择有效的公司");
    if(lstCorp->CanFocus())	lstCorp->SetFocus();
    return;
  }
  strcpy(strCorp,m_lstCorpID[nSel]);

  strcpy(strID,edtID->Text.c_str());
  strcpy(strName,edtName->Text.c_str());

  char szSQL[1024],strSQL[1024],strTel[256];
//------输入合法行检验----------------------------------------------------------
        sprintf(strSQL,"select * from operator where op_code='%s'",strID);
        RunSQL(strSQL,true);
        if(!dm1->Query1->RecordCount>0)
        {
                ShowMessage("没有该人员代号!请核对後重输.");
                if (edtID->CanFocus()) edtID->SetFocus();
                return;
        }

        sprintf(strSQL,"select * from operator where op_code='%s' and op_name='%s'", strID, strName);
        RunSQL(strSQL,true);
        if(!dm1->Query1->RecordCount>0)
        {
                ShowMessage("人员代号於员工名字不符，请核对後再输入!");
                if (edtName->CanFocus()) edtName->SetFocus();
                return;
        }
//------------------------------------------------------------------------------
  
	strcpy(strTel,Str2DBString(edtTel->Text.c_str()));

  switch(m_enWorkState)
  {
    case EN_ADDNEW:
      sprintf(strSQL,"insert into RcptHandleman"
      	" (rh_code,rh_name,rh_tel,rh_cpcode) values('%s','%s',%s,'%s')",strID,strName,strTel,strCorp);
      break;
    case EN_EDIT:
      sprintf(strSQL,"update RcptHandleman set rh_name='%s',rh_tel=%s,rh_cpcode='%s' where rh_code='%s'",
				strName,strTel,strCorp,strID);
      break;
    default:
      ShowMessage("Work State not AddNew or Edit");
      return;
  }

  if(!dm1->OpenDatabase())  return;

  try
  {
    if(m_enWorkState==EN_ADDNEW)
    {
      char strAddSQL[256];
      sprintf(strAddSQL,"select * from RcptHandleman where rh_code='%s'",strID);
      RunSQL(strAddSQL,true);
      if(dm1->Query1->RecordCount>0)
      {
        ShowMessage("数据库中已有该编号的记录!");
        edtID->SetFocus();
        return;
      }
    }
    RunSQL(strSQL);
  }
  catch(...)
  {
    ShowMessage("数据库操作错误!");
    return;
  }

  TListItem *pItem;
  if(m_enWorkState==EN_ADDNEW)
  {
  	pItem=ListView1->Items->Add();
    pItem->Caption=edtID->Text;
    pItem->SubItems->Add(edtName->Text);
		pItem->SubItems->Add(edtTel->Text);
    pItem->SubItems->Add(lstCorp->Text);
    ListView1->Selected=pItem;
  }
  else if(m_enWorkState==EN_EDIT)
  {
  	pItem=ListView1->Selected;
    if(pItem!=NULL)
    {
    	pItem->Caption=edtID->Text;
      pItem->SubItems->Strings[0]=edtName->Text;
			pItem->SubItems->Strings[1]=edtTel->Text;
      pItem->SubItems->Strings[2]=lstCorp->Text;
    }
  }

  nState=m_enWorkState;
  m_enWorkState=EN_IDLE;
  ResetCtrl();
  msgState->Caption="工作状态：查询";
  switch(nState)
  { //设置确定後的光标位置
    case EN_ADDNEW: btnAddNew->SetFocus();  break;
    case EN_EDIT:   btnEdit->SetFocus();    break;
    default:  break;
  }
}
//---------------------------------------------------------------------------

void __fastcall TRcptHandlemanForm::btnDeleteClick(TObject *Sender)
{
  char strMsg[256],strSQL[512];
  sprintf(strMsg,"\n  真要删除编号为“%s”的记录吗？  \n",edtID->Text.c_str());
  if(Application->MessageBox(strMsg,"警告",MB_YESNOCANCEL | MB_ICONQUESTION | MB_DEFBUTTON2)!=IDYES)
   return;

  sprintf(strSQL,"delete from RcptHandleman where rh_code='%s'",edtID->Text.c_str());
  if(!dm1->OpenDatabase())  return;

  if(!RunSQL(strSQL))	return;

  TListItem *pItem;
  pItem=ListView1->Selected;
  if(pItem!=NULL)
  {
  	int nSel=ListView1->Items->IndexOf(pItem);
    ListView1->Items->Delete(nSel);
    ListView1->Selected=NULL;
  }
  m_enWorkState=EN_IDLE;
  ResetCtrl();
}
//---------------------------------------------------------------------------

void TRcptHandlemanForm::ResetCtrl()
{
	bool bAuth = m_nAuthor>=AUTH_FULL;
  if(m_enWorkState==EN_IDLE)
  {
    EnableEdit(edtID	,false);
    EnableEdit(edtName,false);
		EnableEdit(edtTel,false);
    btnOK0->Enabled=false;
    btnCancel0->Enabled=false;

    btnAddNew->Enabled=true && bAuth;
    btnRefresh->Enabled=true;
    btnExit->Enabled=true;
    btnPrint->Enabled=true;
    ListView1->Enabled=true;
    if(ListView1->Selected!=NULL)
    {
      btnEdit->Enabled=true && bAuth;
      btnDelete->Enabled=true && bAuth;
    }
    else
    {
      btnEdit->Enabled=false;
      btnDelete->Enabled=false;
    }
  }
  else
  {
    btnAddNew->Enabled	=false;
    btnRefresh->Enabled	=false;
    btnExit->Enabled		=false;
    ListView1->Enabled	=false;
    btnEdit->Enabled		=false;
    btnDelete->Enabled	=false;
    btnPrint->Enabled		=false;

    EnableEdit(edtName,true);
		EnableEdit(edtTel	,true);
    btnOK0->Enabled=true;
    btnCancel0->Enabled=true;
    if(m_enWorkState==EN_ADDNEW)
	    EnableEdit(edtID,true);
    else //修改时不能修改产品编号
	    EnableEdit(edtID,false);
  }
  EnableCombo(lstCorp,m_enWorkState!=EN_IDLE);
}

void __fastcall TRcptHandlemanForm::btnExitClick(TObject *Sender)
{
  Close();
}
//---------------------------------------------------------------------------


void __fastcall TRcptHandlemanForm::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
  if (Key==VK_RETURN)
    KeyReturnHandle(ActiveControl);
}
//---------------------------------------------------------------------------


#include "PrnBaseData.h"
void __fastcall TRcptHandlemanForm::btnPrintClick(TObject *Sender)
{
  if(!dm1->OpenDatabase())  return;
  AnsiString szSQL="select rh_code as prnID,rh_name as prnName,rh_tel as prnText2 from RcptHandleman order by rh_code";
  if(!OpenQuery(dm1->sqlPrint,szSQL.c_str()))
  	return;

  try
  {
	  TPrnBaseDataForm *pForm;
  	pForm=new TPrnBaseDataForm(this);

    pForm->txtTitle->Caption="收货经办字典表";
    pForm->txtText2->Caption="分机";
    pForm->txtText3->Caption="";

    pForm->PrnView->PreviewModal() ;
    delete pForm;
  }
  catch(...)
  {
    ShowMessage("打印机返回错误信息，请检查是否安装并设置了默认打印机");
    return;
  }
}
//---------------------------------------------------------------------------


void __fastcall TRcptHandlemanForm::FormShow(TObject *Sender)
{
	edtID->Text="";
  edtName->Text="";
	edtTel->Text="";
  lstCorp->Text="";
  CString szSQL="select * from diccorp order by cp_code";
  RunSQL(dm1->Query1,szSQL,true);
  while(!dm1->Query1->Eof)
  {
  	m_lstCorpID.Add(dm1->Query1->FieldByName("cp_code")->AsString.c_str());
    lstCorp->Items->Add(dm1->Query1->FieldByName("cp_name")->AsString);
    
  	dm1->Query1->Next();
  }

  RefreshData();
  m_enWorkState=EN_IDLE;

  ResetCtrl();
}
//---------------------------------------------------------------------------



void __fastcall TRcptHandlemanForm::ListView1Click(TObject *Sender)
{
  Row2Editor();
	ResetCtrl();
}
//---------------------------------------------------------------------------

void __fastcall TRcptHandlemanForm::lstCorpExit(TObject *Sender)
{
	HandleListboxExit(lstCorp,&m_lstCorpID);	
}
//---------------------------------------------------------------------------

