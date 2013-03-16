//---------------------------------------------------------------------------

#include <vcl.h>
#include <stdio.h>
#pragma hdrstop

#include "DicSH.h"          
#include "DataModule.h"
#include "BaseCode.h"
#include "LdyInterface.h"
#include "common.hpp"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TDicSHForm *DicSHForm;
void DicSH(int nAuth)
{
	if(nAuth==AUTH_NONE)
  {
  	ShowMessage("抱歉，您没有这个权限");
    return;
  }

  TDicSHForm *pForm;
	try
	{
  	pForm=new TDicSHForm(Application);
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
//---------------------------------------------------------------------------
__fastcall TDicSHForm::TDicSHForm(TComponent* Owner)
        : TForm(Owner)
{
  m_enWorkState=EN_IDLE;
}

//---------------------------------------------------------------------------
void TDicSHForm::Row2Editor()
{
  TListItem *pItem;

  pItem=ListView1->Selected;
  if(pItem==NULL)	return;
  edtName->Text=pItem->Caption;
  edtAddress->Text=pItem->SubItems->Strings[0];
  edtTel->Text=pItem->SubItems->Strings[1];

}

void TDicSHForm::ResetCtrl()
{
	bool bAuth = m_nAuthor>=AUTH_FULL;
  if(m_enWorkState==EN_IDLE)
  {
    EnableEdit(edtName,false);
    EnableEdit(edtAddress,false);
    EnableEdit(edtTel,false);
    btnOK0->Enabled=false;
    btnCancel0->Enabled=false;

    btnAddNew->Enabled=true && bAuth;
    btnRefresh->Enabled=true;
    btnExit->Enabled=true;
    ListView1->Enabled=true;
//    ctlListBox->Enabled=true;
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
    btnAddNew->Enabled=false;
    btnRefresh->Enabled=false;
    btnExit->Enabled=false;
//    ctlListBox->Enabled=false;
    ListView1->Enabled=false;
    btnEdit->Enabled=false;
    btnDelete->Enabled=false;

    EnableEdit(edtAddress,true);
    EnableEdit(edtTel,true);
    btnOK0->Enabled=true;
    btnCancel0->Enabled=true;
    if(m_enWorkState==EN_ADDNEW)
	    EnableEdit(edtName,true);
    else //修改时不能修改产品编号
	    EnableEdit(edtName,false);
  }
}
void __fastcall TDicSHForm::ListView1Click(TObject *Sender)
{

  Row2Editor();
	ResetCtrl();         
}
//---------------------------------------------------------------------------
void __fastcall TDicSHForm::btnOK0Click(TObject *Sender)
{
  char strAddress[80],strName[80],strTel[80],*ptr,strTemp[80];
  int nState;
                             
  edtName->Text=edtName->Text.Trim();
  edtAddress->Text=edtAddress->Text.Trim();
  edtTel->Text=edtTel->Text.Trim();

  if(edtName->Text.IsEmpty())
  {
  	ShowMessage("请输入名称");
    if(edtName->CanFocus())	edtName->SetFocus();
    return;
  }
  if(edtAddress->Text.IsEmpty())
  {
  	ShowMessage("请输入地址");
    if(edtAddress->CanFocus())	edtAddress->SetFocus();
    return;
  }
  if(edtTel->Text.IsEmpty())
  {
  	ShowMessage("请输入电话");
    if(edtTel->CanFocus())	edtTel->SetFocus();
    return;
  }

  strcpy(strTel,edtTel->Text.c_str());
  strcpy(strAddress,edtAddress->Text.c_str());
  strcpy(strName,edtName->Text.c_str());

  char strSQL[1024];

  switch(m_enWorkState)
  {
    case EN_ADDNEW:
      sprintf(strSQL,"insert into dicsh(name,address,tel) values('%s','%s','%s')",strName,strAddress,strTel);
      break;
    case EN_EDIT:
      sprintf(strSQL,"update dicsh set address='%s',tel='%s' where name='%s'",strAddress,strTel,strName);
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
      sprintf(strAddSQL,"select * from dicsh where name='%s'",strName);
      if (checkDataExist(strAddSQL)){
        ShowMessage("数据库中已有该名称的记录!");
        edtName->SetFocus();
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
    pItem->Caption=edtName->Text;
    pItem->SubItems->Add(edtAddress->Text);
    pItem->SubItems->Add(edtTel->Text);

    ListView1->Selected=pItem;
  }
  else if(m_enWorkState==EN_EDIT)
  {
  	pItem=ListView1->Selected;
    if(pItem!=NULL)
    {
    	pItem->Caption=edtName->Text;
      pItem->SubItems->Strings[0]=edtAddress->Text;
      pItem->SubItems->Strings[1]=edtTel->Text;

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
void __fastcall TDicSHForm::btnCancel0Click(TObject *Sender)
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
void __fastcall TDicSHForm::btnAddNewClick(TObject *Sender)
{
  edtAddress->Text="";
  edtTel->Text="";
  edtName->Text="";
  m_enWorkState=EN_ADDNEW;
  ResetCtrl();
  msgState->Caption="工作状态：新增";
  edtName->SetFocus();
}
//---------------------------------------------------------------------------
void __fastcall TDicSHForm::btnEditClick(TObject *Sender)
{

  m_enWorkState=EN_EDIT;
  ResetCtrl();
  msgState->Caption="工作状态：修改";
  edtAddress->SetFocus();
  edtTel->SetFocus();
}
//---------------------------------------------------------------------------
void __fastcall TDicSHForm::btnDeleteClick(TObject *Sender)
{
  char strMsg[256],strSQL[512];
  sprintf(strMsg,"\n  真要删除名称为“%s”的记录吗？  \n",edtName->Text.c_str());
  if(Application->MessageBox(strMsg,"警告",MB_YESNOCANCEL | MB_ICONQUESTION | MB_DEFBUTTON2)!=IDYES)
   return;

  sprintf(strSQL,"delete from dicsh where name='%s'",edtName->Text.c_str());
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
void __fastcall TDicSHForm::btnRefreshClick(TObject *Sender)
{

  RefreshData();
  ResetCtrl();
}
//---------------------------------------------------------------------------
void __fastcall TDicSHForm::btnExitClick(TObject *Sender)
{

Close();
}
//---------------------------------------------------------------------------

void TDicSHForm::RefreshData()
{
  char strBuff[512];
  TListItem *pItem;

  if(!dm1->OpenDatabase())  return;
  try
  {
    dm1->Query1->SQL->Clear();
    dm1->Query1->SQL->Add("select * from dicsh");

    dm1->Query1->Prepare();
    dm1->Query1->Open();
    dm1->Query1->First();
    ListView1->Items->Clear();
    while(!dm1->Query1->Eof)
    {
    	pItem=ListView1->Items->Add();
      pItem->Caption=dm1->Query1->FieldByName("name")->AsString;
      pItem->SubItems->Add(dm1->Query1->FieldByName("address")->AsString);
        pItem->SubItems->Add(dm1->Query1->FieldByName("tel")->AsString);

      dm1->Query1->Next();
    }
  }
  catch(...)
  {
    ShowMessage("数据库操作错误");
    return;
  }
}
void __fastcall TDicSHForm::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{

  if (Key==VK_RETURN)
    KeyReturnHandle(ActiveControl);        
}
//---------------------------------------------------------------------------
void __fastcall TDicSHForm::FormShow(TObject *Sender)
{

  edtName->Text="";
  edtAddress->Text = "";
  edtTel->Text = "";
  RefreshData();
  m_enWorkState=EN_IDLE;
  ResetCtrl();        
}
//---------------------------------------------------------------------------

