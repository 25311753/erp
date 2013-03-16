//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "DicCharge.h"     
#include "DataModule.h"
#include "BaseCode.h"
#include "LdyInterface.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TDicChargeForm *DicChargeForm;
//---------------------------------------------------------------------------
void DicCharge(int nAuth)
{
  TDicChargeForm *pForm;
	try
	{
  	        pForm=new TDicChargeForm(Application);
        }
	catch (Exception &exception)
	{
		Application->ShowException(&exception);
                return;
	}
        pForm->ShowModal();
        delete pForm;
}
__fastcall TDicChargeForm::TDicChargeForm(TComponent* Owner)
        : TForm(Owner)
{                      
  m_enWorkState=EN_IDLE;
}
//---------------------------------------------------------------------------
void TDicChargeForm::Row2Editor()
{
  TListItem *pItem;

  pItem=ListView1->Selected;
  if(pItem==NULL)	return;
  edtCharge->Text=pItem->Caption;
}

void TDicChargeForm::RefreshData()
{
  char strBuff[512];
  TListItem *pItem;

  if(!dm1->OpenDatabase())  return;
  try
  {
    dm1->Query1->SQL->Clear();
    dm1->Query1->SQL->Add("select * from charges order by chid");

    dm1->Query1->Prepare();
    dm1->Query1->Open();
    dm1->Query1->First();
    ListView1->Items->Clear();
    while(!dm1->Query1->Eof)
    {
    	pItem=ListView1->Items->Add();
      pItem->Caption=dm1->Query1->FieldByName("chname")->AsString;
      dm1->Query1->Next();
    }
  }
  catch(...)
  {
    ShowMessage("数据库操作错误");
    return;
  }
}

void TDicChargeForm::ResetCtrl()
{
  //bool bAuth = m_nAuthor>=AUTH_FULL;
  bool bAuth = true;
  if(m_enWorkState==EN_IDLE)
  {
    EnableEdit(edtCharge,false);
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

    EnableEdit(edtCharge,true);
    btnOK0->Enabled=true;
    btnCancel0->Enabled=true;
    if(m_enWorkState==EN_ADDNEW)
	    EnableEdit(edtCharge,true);
    else //修改时
	    EnableEdit(edtCharge,true);
  }
}
void __fastcall TDicChargeForm::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
  if (Key==VK_RETURN)
    KeyReturnHandle(ActiveControl);          
}
//---------------------------------------------------------------------------
void __fastcall TDicChargeForm::FormShow(TObject *Sender)
{
  edtCharge->Text="";
  RefreshData();
  m_enWorkState=EN_IDLE;
  ResetCtrl();
}
//---------------------------------------------------------------------------
void __fastcall TDicChargeForm::ListView1Click(TObject *Sender)
{
        Row2Editor();
	ResetCtrl();         
}
//---------------------------------------------------------------------------
void __fastcall TDicChargeForm::btnOK0Click(TObject *Sender)
{
  char strCharge[80],*ptr,strTemp[80];
  int nState;

  edtCharge->Text=edtCharge->Text.Trim();

  if(edtCharge->Text.IsEmpty())
  {
  	ShowMessage("请输入");
    if(edtCharge->CanFocus())	edtCharge->SetFocus();
    return;
  }

  strcpy(strCharge,edtCharge->Text.c_str());

  char strSQL[1024];

  switch(m_enWorkState)
  {
    case EN_ADDNEW:
      sprintf(strSQL,"insert into charges select (select max(chid)+1 from charges where chid!=99), '%s'",strCharge);
      break;
    case EN_EDIT:
      {TListItem *pItem = ListView1->Selected;
      sprintf(strSQL,"update charges set chname='%s' where chname='%s'",strCharge,pItem->Caption.c_str());
      }break;
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
      sprintf(strAddSQL,"select * from charges where chname='%s'",strCharge);
      RunSQL(strAddSQL,true);
      if(dm1->Query1->RecordCount>0)
      {
        ShowMessage("数据库中已有该编号的记录!");
        edtCharge->SetFocus();
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
    pItem->Caption=edtCharge->Text;
    ListView1->Selected=pItem;
  }
  else if(m_enWorkState==EN_EDIT)
  {
  	pItem=ListView1->Selected;
    if(pItem!=NULL)
    {
    	pItem->Caption=edtCharge->Text;
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
void __fastcall TDicChargeForm::btnCancel0Click(TObject *Sender)
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
void __fastcall TDicChargeForm::btnAddNewClick(TObject *Sender)
{
  edtCharge->Text="";
  m_enWorkState=EN_ADDNEW;
  ResetCtrl();
  msgState->Caption="工作状态：新增";
  edtCharge->SetFocus();        
}
//---------------------------------------------------------------------------
void __fastcall TDicChargeForm::btnEditClick(TObject *Sender)
{

  m_enWorkState=EN_EDIT;
  ResetCtrl();
  msgState->Caption="工作状态：修改";
  edtCharge->SetFocus();
}
//---------------------------------------------------------------------------
void __fastcall TDicChargeForm::btnDeleteClick(TObject *Sender)
{
  char strMsg[256],strSQL[512];
  sprintf(strMsg,"\n  真要删除“%s”的记录吗？  \n",edtCharge->Text.c_str());
  if(Application->MessageBox(strMsg,"警告",MB_YESNOCANCEL | MB_ICONQUESTION | MB_DEFBUTTON2)!=IDYES)
   return;

  sprintf(strSQL,"delete from charges where chname='%s'",edtCharge->Text.c_str());
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
void __fastcall TDicChargeForm::btnRefreshClick(TObject *Sender)
{

  RefreshData();
  ResetCtrl();           
}
//---------------------------------------------------------------------------
void __fastcall TDicChargeForm::btnExitClick(TObject *Sender)
{

Close();              
}
//---------------------------------------------------------------------------
