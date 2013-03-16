//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "DicSupplier.h"

#include "DataModule.h"
#include "BaseCode.h"
#include "LdyInterface.h"
#include "common.hpp"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "trayicon"
#pragma resource "*.dfm"
TDicSupplierForm *DicSupplierForm;
//---------------------------------------------------------------------------
void DicSupplier(int nAuth)
{
  CALL_FORM(TDicSupplierForm);
}
__fastcall TDicSupplierForm::TDicSupplierForm(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void TDicSupplierForm::RefreshData(){
  char strBuff[512];
  TListItem *pItem;

  if(!dm1->OpenDatabase())  return;
  try
  {
    CString szSQL;
    szSQL.Format("select * from supplier order by spid");
    dm1->Query1->SQL->Clear();
    dm1->Query1->SQL->Add(AnsiString(szSQL));

    dm1->Query1->Prepare();
    dm1->Query1->Open();
    dm1->Query1->First();
    ListView1->Items->Clear();
    while(!dm1->Query1->Eof)
    {
        pItem=ListView1->Items->Add();
	pItem->Caption			=dm1->Query1->FieldByName("spid")->AsString;
	pItem->SubItems->Add(dm1->Query1->FieldByName("name")->AsString);
	pItem->SubItems->Add(dm1->Query1->FieldByName("address")->AsString);
	pItem->SubItems->Add(dm1->Query1->FieldByName("tel")->AsString);
	pItem->SubItems->Add(dm1->Query1->FieldByName("fax")->AsString);
	pItem->SubItems->Add(dm1->Query1->FieldByName("chargeman")->AsString);
        pItem->SubItems->Add(dm1->Query1->FieldByName("tel_lk")->AsString);
	pItem->SubItems->Add(dm1->Query1->FieldByName("remarks_busi_license")->AsString); 
	pItem->SubItems->Add(dm1->Query1->FieldByName("reputation")->AsString);
	pItem->SubItems->Add(dm1->Query1->FieldByName("settlement_type")->AsString);
	pItem->SubItems->Add(dm1->Query1->FieldByName("bank")->AsString);
	pItem->SubItems->Add(dm1->Query1->FieldByName("bank_account")->AsString);
	pItem->SubItems->Add(dm1->Query1->FieldByName("huming")->AsString);

	
       dm1->Query1->Next();
    }
  }
  catch(...)
  {
    ShowMessage("数据库操作错误");
    return;
   }
}
void TDicSupplierForm::Row2Editor(){
        TListItem *pItem;

        pItem=ListView1->Selected;
        if(pItem==NULL)
                return;
        edtSpId->Text=pItem->Caption;
        int i = 0;
	edtName->Text					= pItem->SubItems->Strings[i++];
	edtAddress->Text			= pItem->SubItems->Strings[i++];
	edtTel->Text					= pItem->SubItems->Strings[i++];
	edtFax->Text					= pItem->SubItems->Strings[i++];
	edtChargeMan->Text		= pItem->SubItems->Strings[i++];
	edtTelLinkMan->Text		= pItem->SubItems->Strings[i++];
	locateCbbByValue(cbbLicense, pItem->SubItems->Strings[i++]);
	locateCbbByValue(cbbReputation, pItem->SubItems->Strings[i++]);
	locateCbbByValue(cbbSettlementType, pItem->SubItems->Strings[i++]);
	edtBank->Text		= pItem->SubItems->Strings[i++];
	edtBankAccount->Text		= pItem->SubItems->Strings[i++];
        edtHuMing->Text		= pItem->SubItems->Strings[i++];


}

void TDicSupplierForm::Editor2RowAdd(TListItem *pItem){
        if(pItem==NULL)
                return;
        pItem->Caption = edtSpId->Text;
	pItem->SubItems->Add(edtName->Text);
	pItem->SubItems->Add(edtAddress->Text);
	pItem->SubItems->Add(edtTel->Text);
	pItem->SubItems->Add(edtFax->Text);
	pItem->SubItems->Add(edtChargeMan->Text);
	pItem->SubItems->Add(edtTelLinkMan->Text);    
	pItem->SubItems->Add(cbbLicense->Text);       
	pItem->SubItems->Add(cbbReputation->Text);
	pItem->SubItems->Add(cbbSettlementType->Text);
	pItem->SubItems->Add(edtBank->Text);
	pItem->SubItems->Add(edtBankAccount->Text);
	pItem->SubItems->Add(edtHuMing->Text);


}
void TDicSupplierForm::Editor2RowUpdate(TListItem *pItem){
        if(pItem==NULL)
                return;
        pItem->Caption = edtSpId->Text;

        int i = 0;
	pItem->SubItems->Strings[i++] = edtName->Text;     
	pItem->SubItems->Strings[i++] = edtAddress->Text;
	pItem->SubItems->Strings[i++] = edtTel->Text;
	pItem->SubItems->Strings[i++] = edtFax->Text;
	pItem->SubItems->Strings[i++] = edtChargeMan->Text;
	pItem->SubItems->Strings[i++] = edtTelLinkMan->Text;   
	pItem->SubItems->Strings[i++] = cbbLicense->Text;
	pItem->SubItems->Strings[i++] = cbbReputation->Text;
	pItem->SubItems->Strings[i++] = cbbSettlementType->Text; 
	pItem->SubItems->Strings[i++] = edtBank->Text;
	pItem->SubItems->Strings[i++] = edtBankAccount->Text;
	pItem->SubItems->Strings[i++] = edtHuMing->Text;

}
void TDicSupplierForm::ResetCtrl(){
  //bool bAuth = m_nAuthor>=AUTH_FULL;
  bool bAuth = true;
  if(m_enWorkState==EN_IDLE)
  {
    enablePlCtrl(plInput, false);

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
    plQry->Enabled = true;
  }
  else
  {
    plQry->Enabled = false;
    btnAddNew->Enabled=false;
    btnRefresh->Enabled=false;
    btnExit->Enabled=false;
    ListView1->Enabled=false;
    btnEdit->Enabled=false;
    btnDelete->Enabled=false;
    
    enablePlCtrl(plInput, true);
    
    btnOK0->Enabled=true;
    btnCancel0->Enabled=true;
    if(m_enWorkState==EN_ADDNEW)
	    EnableEdit(edtSpId,true);
    else //修改时
	    EnableEdit(edtSpId,false);
   }

}
void TDicSupplierForm::clearInput(){
	edtSpId->Text = "";
	edtName->Text = "";
	edtTel->Text = "";
	edtFax->Text = "";
	edtChargeMan->Text = "";
	edtTelLinkMan->Text = "";
	cbbSettlementType->Text = "";
	cbbReputation->Text = "";
	cbbLicense->Text = "";
	edtBankAccount->Text = "";
	edtAddress->Text = "";
	edtBank->Text = "";
}
//rt: true-valid
bool TDicSupplierForm::checkInput(){
        bool rt = true;
        if (
		edtSpId->Text.IsEmpty() || 
		edtName->Text.IsEmpty() || 
		edtTel->Text.IsEmpty() || 
		edtFax->Text.IsEmpty() || 
		edtChargeMan->Text.IsEmpty() || 
		edtTelLinkMan->Text.IsEmpty() || 
		cbbSettlementType->Text.IsEmpty() || 
		cbbReputation->Text.IsEmpty() || 
		cbbLicense->Text.IsEmpty() || 
//		edtBankAccount->Text.IsEmpty() ||
		edtAddress->Text.IsEmpty()
//		edtBank->Text.IsEmpty()
        ){
                rt = false;
        }

        return rt;
}
void __fastcall TDicSupplierForm::ListView1Click(TObject *Sender)
{
        Row2Editor();
        ResetCtrl() ;
}
//---------------------------------------------------------------------------

void __fastcall TDicSupplierForm::btnRefreshClick(TObject *Sender)
{
  RefreshData();
  ResetCtrl();
}
//---------------------------------------------------------------------------

void __fastcall TDicSupplierForm::btnExitClick(TObject *Sender)
{
        Close();        
}
//---------------------------------------------------------------------------

void __fastcall TDicSupplierForm::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
  if (Key==VK_RETURN)
    KeyReturnHandle(ActiveControl) ;
}
//---------------------------------------------------------------------------

void __fastcall TDicSupplierForm::FormShow(TObject *Sender)
{
  clearInput();
  RefreshData();
  m_enWorkState = EN_IDLE;
  ResetCtrl() ;
}
//---------------------------------------------------------------------------

void __fastcall TDicSupplierForm::btnOK0Click(TObject *Sender)
{
        if ( !checkInput() )
        {
                ShowMessage("输入信息不全");
                return;
        }

  int nState;
  CString szSQL;
  szSQL="";
  switch(m_enWorkState)
  {
    case EN_ADDNEW:
      szSQL.Format("insert into supplier(spid, name, address, tel, fax, \
                        chargeman, tel_lk, settlement_type, remarks_busi_license, \
                        reputation, bank, bank_account, huming) \
                        values('%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s')", \
                        edtSpId->Text, edtName->Text, edtAddress->Text, edtTel->Text, edtFax->Text, \
                        edtChargeMan->Text, edtTelLinkMan->Text, cbbSettlementType->Text, cbbLicense->Text, \
                        cbbReputation->Text, edtBank->Text, edtBankAccount->Text, getByEdt(edtHuMing).c_str());
      break;
    case EN_EDIT:
      szSQL.Format("update supplier set name='%s',  address='%s',  tel='%s',  fax='%s',  \
                        chargeman='%s',  tel_lk='%s', settlement_type='%s',  remarks_busi_license='%s',  \
                        reputation='%s',  bank='%s',  bank_account='%s', huming='%s' where spid='%s'",  \
                        edtName->Text, edtAddress->Text, edtTel->Text, edtFax->Text, \
                        edtChargeMan->Text, edtTelLinkMan->Text, cbbSettlementType->Text, cbbLicense->Text, \
                        cbbReputation->Text, edtBank->Text, edtBankAccount->Text, getByEdt(edtHuMing).c_str(), edtSpId->Text);
//      edtDebug->Text = AnsiString(szSQL);
      break;
    default:
      ShowMessage("Work State not AddNew or Edit");
      return;
  }
//  edtDebug->Text = AnsiString(szSQL);
  if(!dm1->OpenDatabase())  return;

  try
  {
    if(m_enWorkState==EN_ADDNEW)
    {
      char strAddSQL[256];
      sprintf(strAddSQL,"select * from supplier where spid='%s'", edtSpId->Text);
      RunSQL(strAddSQL,true);
      if(dm1->Query1->RecordCount>0)
      {
        ShowMessage("数据库中已有该编号的记录!");
        edtSpId->SetFocus();
        return;
      }
    }
    RunSQL(szSQL);
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
    Editor2RowAdd(pItem);
    ListView1->Selected=pItem;
  }
  else if(m_enWorkState==EN_EDIT)
  {
    pItem=ListView1->Selected;
    Editor2RowUpdate(pItem);
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

void __fastcall TDicSupplierForm::btnCancel0Click(TObject *Sender)
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

void __fastcall TDicSupplierForm::btnAddNewClick(TObject *Sender)
{
  clearInput();
  m_enWorkState=EN_ADDNEW;
  ResetCtrl();
  msgState->Caption="工作状态：新增";
  edtSpId->SetFocus();        
}
//---------------------------------------------------------------------------

void __fastcall TDicSupplierForm::btnEditClick(TObject *Sender)
{
  m_enWorkState=EN_EDIT;
  ResetCtrl();
  msgState->Caption="工作状态：修改";
//  edtName->SetFocus();               
}
//---------------------------------------------------------------------------

void __fastcall TDicSupplierForm::btnDeleteClick(TObject *Sender)
{
 char strMsg[256],strSQL[512];
  sprintf(strMsg,"\n  真要删除编号为“%s”的记录吗？  \n",edtSpId->Text.c_str());
  if(Application->MessageBox(strMsg,"警告",MB_YESNOCANCEL | MB_ICONQUESTION | MB_DEFBUTTON2)!=IDYES)
   return;

  sprintf(strSQL,"delete from supplier where spid='%s'",edtSpId->Text.c_str());
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











void __fastcall TDicSupplierForm::Button1Click(TObject *Sender)
{
         this->TrayIcon1->Minimize();          
}
//---------------------------------------------------------------------------



