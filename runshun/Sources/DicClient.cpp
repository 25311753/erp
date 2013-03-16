//---------------------------------------------------------------------------

#include <vcl.h>
#include <stdio.h>

#pragma hdrstop

#include "DicClient.h"

#include "DataModule.h"
#include "BaseCode.h"
#include "LdyInterface.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TDicClientForm *DicClientForm;
//---------------------------------------------------------------------------
 void DicClient(int nAuth)
{
  TDicClientForm *pForm;
	try
	{
  	        pForm=new TDicClientForm(Application);
        }
	catch (Exception &exception)
	{
		Application->ShowException(&exception);
                return;
	}
        pForm->ShowModal();
        delete pForm;
}
__fastcall TDicClientForm::TDicClientForm(TComponent* Owner)
        : TForm(Owner)
{
  m_enWorkState=EN_IDLE;
}
//---------------------------------------------------------------------------
void TDicClientForm::Row2Editor()
{
  TListItem *pItem;

  pItem=ListView1->Selected;
  if(pItem==NULL)	return;
  edtCid->Text=pItem->Caption;
  edtFullName->Text=pItem->SubItems->Strings[0];
  edtShortName->Text=pItem->SubItems->Strings[1];
  edtLinkMan->Text=pItem->SubItems->Strings[2];
  edtTel->Text=pItem->SubItems->Strings[3];
  edtCustomsCharge->Text=pItem->SubItems->Strings[4];


}

void TDicClientForm::RefreshData()
{
  char strBuff[512];
  TListItem *pItem;

  if(!dm1->OpenDatabase())  return;
  try
  {
    dm1->Query1->SQL->Clear();
    dm1->Query1->SQL->Add("select * from client order by cid");

    dm1->Query1->Prepare();
    dm1->Query1->Open();
    dm1->Query1->First();
    ListView1->Items->Clear();
    while(!dm1->Query1->Eof)
    {
        pItem=ListView1->Items->Add();
      pItem->Caption=dm1->Query1->FieldByName("cid")->AsString;
      pItem->SubItems->Add(dm1->Query1->FieldByName("fullname")->AsString);
      pItem->SubItems->Add(dm1->Query1->FieldByName("shortname")->AsString);
      pItem->SubItems->Add(dm1->Query1->FieldByName("linkman")->AsString);
      pItem->SubItems->Add(dm1->Query1->FieldByName("tel")->AsString);
      pItem->SubItems->Add(dm1->Query1->FieldByName("customs_charge")->AsString);

      dm1->Query1->Next();
    }
  }
  catch(...)
  {
    ShowMessage("数据库操作错误");
    return;
  }
}

void TDicClientForm::ResetCtrl()
{
  //bool bAuth = m_nAuthor>=AUTH_FULL;
  bool bAuth = true;
  if(m_enWorkState==EN_IDLE)
  {
    EnableEdit(edtCid,false);
    EnableEdit(edtFullName,false);
    EnableEdit(edtShortName,false);
    EnableEdit(edtLinkMan,false);
    EnableEdit(edtTel,false);
    EnableEdit(edtCustomsCharge,false);

    btnOK0->Enabled=false;
    btnCancel0->Enabled=false;

    btnAddNew->Enabled=true && bAuth;
    btnRefresh->Enabled=true;
    btnExit->Enabled=true;
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
    btnAddNew->Enabled=false;
    btnRefresh->Enabled=false;
    btnExit->Enabled=false;
    ListView1->Enabled=false;
    btnEdit->Enabled=false;
    btnDelete->Enabled=false;
    EnableEdit(edtCid,true);
            EnableEdit(edtFullName,true);
            EnableEdit(edtShortName,true);
            EnableEdit(edtLinkMan,true);
            EnableEdit(edtTel,true);
            EnableEdit(edtCustomsCharge,true);

    btnOK0->Enabled=true;
    btnCancel0->Enabled=true;
    if(m_enWorkState==EN_ADDNEW){
                EnableEdit(edtCid,true);
            EnableEdit(edtFullName,true);
            EnableEdit(edtShortName,true);
            EnableEdit(edtLinkMan,true);
            EnableEdit(edtTel,true);
            EnableEdit(edtCustomsCharge,true);
    }
    else{//修改时
                EnableEdit(edtCid,false);
            EnableEdit(edtFullName,true);
            EnableEdit(edtShortName,true);
            EnableEdit(edtLinkMan,true);
            EnableEdit(edtTel,true);
            EnableEdit(edtCustomsCharge,true);

    }
  }
}

void __fastcall TDicClientForm::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
  if (Key==VK_RETURN)
    KeyReturnHandle(ActiveControl);        
}
//---------------------------------------------------------------------------

void __fastcall TDicClientForm::FormShow(TObject *Sender)
{

  edtCid->Text = "";
edtFullName->Text = "";
edtShortName->Text = "";
edtLinkMan->Text = "";
edtTel->Text = "";
edtCustomsCharge->Text = "";

  RefreshData();
  m_enWorkState=EN_IDLE;
  ResetCtrl();        
}
//---------------------------------------------------------------------------

void __fastcall TDicClientForm::ListView1Click(TObject *Sender)
{
  Row2Editor();
	ResetCtrl();        
}
//---------------------------------------------------------------------------

void __fastcall TDicClientForm::btnOK0Click(TObject *Sender)
{
  char strID[80],strCid[80],strFullName[80],strShortName[80],strLinkMan[80],strTel[100],strCustomsCharge[20],*ptr,strTemp[80];
  int nState;

  edtCid->Text=edtCid->Text.Trim();
  edtFullName->Text=edtFullName->Text.Trim();
  edtShortName->Text=edtShortName->Text.Trim();
  edtLinkMan->Text=edtLinkMan->Text.Trim();
  edtTel->Text=edtTel->Text.Trim();
  edtCustomsCharge->Text=edtCustomsCharge->Text.Trim();


  if(edtCid->Text.IsEmpty() || edtFullName->Text.IsEmpty()|| edtShortName->Text.IsEmpty()|| edtLinkMan->Text.IsEmpty() || edtCustomsCharge->Text.IsEmpty())
  {
  	ShowMessage("请完善信息");

    return;
  }

  strcpy(strCid,edtCid->Text.c_str());
  strcpy(strFullName,edtFullName->Text.c_str());
  strcpy(strShortName,edtShortName->Text.c_str());
  strcpy(strLinkMan,edtLinkMan->Text.c_str());
  strcpy(strTel,edtTel->Text.IsEmpty()?"":edtTel->Text.c_str());
  strcpy(strCustomsCharge,edtCustomsCharge->Text.IsEmpty()?"":edtCustomsCharge->Text.c_str());


  char strSQL[1024];
//StrToFloat(edt->Text.IsEmpty()?"0":edt->Text.c_str());
  switch(m_enWorkState)
  {
    case EN_ADDNEW:
      sprintf(strSQL,"insert into client(cid,fullname,shortname,linkman,tel,customs_charge) values('%s','%s','%s','%s','%s','%s')",strCid,strFullName,strShortName,strLinkMan,strTel,strCustomsCharge);
      break;
    case EN_EDIT:
      sprintf(strSQL,"update client set fullname='%s',shortname='%s',linkman='%s',tel='%s',customs_charge='%s' where cid='%s'",strFullName,strShortName,strLinkMan,strTel,strCustomsCharge,strCid);
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
      sprintf(strAddSQL,"select * from client where cid='%s'",strCid);
      RunSQL(strAddSQL,true);
      if(dm1->Query1->RecordCount>0)
      {
        ShowMessage("数据库中已有该编号的记录!");
        edtCid->SetFocus();
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
      pItem->Caption=edtCid->Text;
      pItem->SubItems->Add(edtFullName->Text);
      pItem->SubItems->Add(edtShortName->Text);
      pItem->SubItems->Add(edtLinkMan->Text);
      pItem->SubItems->Add(edtTel->Text);
      pItem->SubItems->Add(edtCustomsCharge->Text);

    ListView1->Selected=pItem;
  }
  else if(m_enWorkState==EN_EDIT)
  {
  	pItem=ListView1->Selected;
    if(pItem!=NULL)
    {
    	pItem->Caption=edtCid->Text;
      pItem->SubItems->Strings[0]=edtFullName->Text;
      pItem->SubItems->Strings[1]=edtShortName->Text;
      pItem->SubItems->Strings[2]=edtLinkMan->Text;
      pItem->SubItems->Strings[3]=edtTel->Text;
      pItem->SubItems->Strings[4]=edtCustomsCharge->Text;

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

void __fastcall TDicClientForm::btnCancel0Click(TObject *Sender)
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

void __fastcall TDicClientForm::btnAddNewClick(TObject *Sender)
{

  edtCid->Text = "";
edtFullName->Text = "";
edtShortName->Text = "";
edtLinkMan->Text = "";
edtTel->Text = "";
edtCustomsCharge->Text = "";

  m_enWorkState=EN_ADDNEW;
  ResetCtrl();
  msgState->Caption="工作状态：新增";
  edtCid->SetFocus();
}
//---------------------------------------------------------------------------

void __fastcall TDicClientForm::btnEditClick(TObject *Sender)
{
  m_enWorkState=EN_EDIT;
  ResetCtrl();
  msgState->Caption="工作状态：修改";
//  edtCid->SetFocus();
}
//---------------------------------------------------------------------------

void __fastcall TDicClientForm::btnDeleteClick(TObject *Sender)
{
 char strMsg[256],strSQL[512];
  sprintf(strMsg,"\n  真要删除编号为“%s”的记录吗？  \n",edtCid->Text.c_str());
  if(Application->MessageBox(strMsg,"警告",MB_YESNOCANCEL | MB_ICONQUESTION | MB_DEFBUTTON2)!=IDYES)
   return;

  sprintf(strSQL,"delete from client where cid='%s'",edtCid->Text.c_str());
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
//  if(nSel>=ctlListBox->Items->Count)
//    nSel=ctlListBox->Items->Count-1;
//  ctlListBox->ItemIndex=nSel;
//  Row2Editor();
  m_enWorkState=EN_IDLE;
  ResetCtrl();
}
//---------------------------------------------------------------------------

void __fastcall TDicClientForm::btnRefreshClick(TObject *Sender)
{
  RefreshData();
  ResetCtrl();        
}
//---------------------------------------------------------------------------

void __fastcall TDicClientForm::btnExitClick(TObject *Sender)
{
Close();          
}
//---------------------------------------------------------------------------



