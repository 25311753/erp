//---------------------------------------------------------------------------

#include <vcl.h>
#include <stdio.h>
#pragma hdrstop

#include "DataModule.h"
#include "BaseCode.h"
#include "HandleMan.h"
#include "LdyInterface.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
THandleManForm *HandleManForm;

// ==================================================================
//经办人员档接口，文件HandleMan.*
void HandleMan(int nAuth)
{
	if(nAuth==AUTH_NONE)
  {
  	ShowMessage("抱歉，您没有这个权限");
    return;
  }

  THandleManForm *pForm;
	try
	{
  	pForm=new THandleManForm(Application);
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


__fastcall THandleManForm::THandleManForm(TComponent* Owner)
  : TForm(Owner)
{
  m_enWorkState=EN_IDLE;
}
//---------------------------------------------------------------------------

void __fastcall THandleManForm::btnRefreshClick(TObject *Sender)
{
  RefreshData();
  ResetCtrl();
}
//---------------------------------------------------------------------------


// --------------------------------------------------------------------------
void THandleManForm::Row2Editor()
{
  TListItem *pItem;

  pItem=ListView1->Selected;
  if(pItem==NULL)	return;
  edtID		->Text=pItem->Caption;
  edtName	->Text=pItem->SubItems->Strings[0];
	lstDep	->ItemIndex=(int)pItem->Data;
	edtTel	->Text=pItem->SubItems->Strings[2];
}


//---------------------------------------------------------------------------

void THandleManForm::RefreshData()
{
  char strBuff[512],strDep[80];
  TListItem *pItem;
	int i;

  if(!dm1->OpenDatabase())  return;
  try
  {
    dm1->Query1->SQL->Clear();
    dm1->Query1->SQL->Add("select * from HandleMan order by hm_code");

    dm1->Query1->Prepare();
    dm1->Query1->Open();
    dm1->Query1->First();
    ListView1->Items->Clear();
    while(!dm1->Query1->Eof)
    {
    	pItem=ListView1->Items->Add();
      pItem->Caption=dm1->Query1->FieldByName("hm_code")->AsString;
      pItem->SubItems->Add(dm1->Query1->FieldByName("hm_name")->AsString);
			strcpy(strDep,dm1->Query1->FieldByName("hm_ddcode")->AsString.c_str());
			for(i=0;i<m_lstDepartID.GetSize();i++)
			{
				if(m_lstDepartID[i]==strDep)
				{
					pItem->SubItems->Add(lstDep->Items->Strings[i]);
					pItem->Data=(void*)i;
					break;
				}
			}
			if(i==m_lstDepartID.GetSize())	
			{
	      pItem->SubItems->Add(strDep);
				pItem->Data=(void*)-1;
			}
			pItem->SubItems->Add(dm1->Query1->FieldByName("hm_tel")->AsString);
      dm1->Query1->Next();
    }
  }
  catch(...)
  {
    ShowMessage("数据库操作错误!");
    return;
  }
}

void __fastcall THandleManForm::btnAddNewClick(TObject *Sender)
{
  edtID->Text="";
  edtName->Text="";
	lstDep->Text="";
	edtTel->Text="";
  m_enWorkState=EN_ADDNEW;
  ResetCtrl();
  msgState->Caption="工作状态：新增";
  edtID->SetFocus();
}
//---------------------------------------------------------------------------

void __fastcall THandleManForm::btnEditClick(TObject *Sender)
{
  m_enWorkState=EN_EDIT;
  ResetCtrl();
  msgState->Caption="工作状态：修改";
  edtName->SetFocus();
}
//---------------------------------------------------------------------------


void __fastcall THandleManForm::btnCancel0Click(TObject *Sender)
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

void __fastcall THandleManForm::btnOK0Click(TObject *Sender)
{
  char strID[80],strName[80],*ptr,strTemp[80];
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
	if((nSel=lstDep->ItemIndex)<0 || nSel>=m_lstDepartID.GetSize())
	{
		ShowMessage("请选择一个有效的部门");
		if(lstDep->CanFocus())	lstDep->SetFocus();
		return;
	}
	edtTel->Text=edtTel->Text.Trim();

  strcpy(strID,edtID->Text.c_str());
  strcpy(strName,edtName->Text.c_str());

  char strSQL[1024],strDep[80],strTel[256];
	sprintf(strDep,"%s",Str2DBString(m_lstDepartID[nSel]));
	strcpy(strTel,Str2DBString(edtTel->Text.c_str()));

  switch(m_enWorkState)
  {
    case EN_ADDNEW:
      sprintf(strSQL,"insert into HandleMan values('%s','%s',%s,%s)",strID,strName,strDep,strTel);
      break;
    case EN_EDIT:
      sprintf(strSQL,"update HandleMan set hm_name='%s',hm_ddcode=%s,hm_tel=%s where hm_code='%s'",
				strName,strDep,strTel,strID);
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
      sprintf(strAddSQL,"select * from HandleMan where hm_code='%s'",strID);
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
		pItem->SubItems->Add(lstDep->Items->Strings[nSel]);
		pItem->SubItems->Add(edtTel->Text);
		pItem->Data=(void*)nSel;
    ListView1->Selected=pItem;
  }
  else if(m_enWorkState==EN_EDIT)
  {
  	pItem=ListView1->Selected;
    if(pItem!=NULL)
    {
    	pItem->Caption=edtID->Text;
      pItem->SubItems->Strings[0]=edtName->Text;
			pItem->SubItems->Strings[1]=lstDep->Items->Strings[nSel];
			pItem->SubItems->Strings[2]=edtTel->Text;
			pItem->Data=(void*)nSel;
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

void __fastcall THandleManForm::btnDeleteClick(TObject *Sender)
{
  char strMsg[256],strSQL[512];
  sprintf(strMsg,"\n  真要删除编号为“%s”的记录吗？  \n",edtID->Text.c_str());
  if(Application->MessageBox(strMsg,"警告",MB_YESNOCANCEL | MB_ICONQUESTION | MB_DEFBUTTON2)!=IDYES)
   return;

  sprintf(strSQL,"delete from HandleMan where hm_code='%s'",edtID->Text.c_str());
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

void THandleManForm::ResetCtrl()
{
	bool bAuth = m_nAuthor>=AUTH_FULL;
  if(m_enWorkState==EN_IDLE)
  {
    EnableEdit(edtID	,false);
    EnableEdit(edtName,false);
		EnableCombo(lstDep,false);
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
		EnableCombo(lstDep,true);
		EnableEdit(edtTel	,true);
    btnOK0->Enabled=true;
    btnCancel0->Enabled=true;
    if(m_enWorkState==EN_ADDNEW)
	    EnableEdit(edtID,true);
    else //修改时不能修改产品编号
	    EnableEdit(edtID,false);
  }
}

void __fastcall THandleManForm::btnExitClick(TObject *Sender)
{
  Close();
}
//---------------------------------------------------------------------------


void __fastcall THandleManForm::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
  if (Key==VK_RETURN)
    KeyReturnHandle(ActiveControl);
}
//---------------------------------------------------------------------------


#include "PrnBaseData.h"
void __fastcall THandleManForm::btnPrintClick(TObject *Sender)
{
  if(!dm1->OpenDatabase())  return;
  AnsiString szSQL="select hm_code as prnID,hm_name as prnName,hm_ddcode as prnText2,hm_tel as prnText3 from HandleMan order by hm_code";
  if(!OpenQuery(dm1->sqlPrint,szSQL.c_str()))
  	return;

  try
  {
	  TPrnBaseDataForm *pForm;
  	pForm=new TPrnBaseDataForm(this);

    pForm->txtTitle->Caption="经办人员字典表";
    pForm->txtText2->Caption="部门";
    pForm->txtText3->Caption="分机";

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


void __fastcall THandleManForm::FormShow(TObject *Sender)
{
	CString szSQL;
	szSQL="select * from DicDepart,DepartCorp where substring(dd_code,1,2)*=dc_code order by dd_code";
	RunSQL(dm1->Query1,szSQL,true);
	while(!dm1->Query1->Eof)
	{
		m_lstDepartID.Add(dm1->Query1->FieldByName("dd_code")->AsString.c_str());
		lstDep->Items->Add(dm1->Query1->FieldByName("dc_name")->AsString+dm1->Query1->FieldByName("dd_name")->AsString);
		dm1->Query1->Next();
	}
	edtID->Text="";
  edtName->Text="";
	lstDep->ItemIndex=-1;
	edtTel->Text="";
  RefreshData();
  m_enWorkState=EN_IDLE;
  ResetCtrl();
}
//---------------------------------------------------------------------------



void __fastcall THandleManForm::ListView1Click(TObject *Sender)
{
  Row2Editor();
	ResetCtrl();
}
//---------------------------------------------------------------------------


