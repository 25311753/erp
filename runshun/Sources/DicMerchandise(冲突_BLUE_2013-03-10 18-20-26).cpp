//---------------------------------------------------------------------------

#include <vcl.h>       
#include <stdio.h>
#pragma hdrstop

#include "DicMerchandise.h"
#include "common.hpp"
#include "DataModule.h"
#include "BaseCode.h"
#include "LdyInterface.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TDicMerchandiseForm *DicMerchandiseForm;
//---------------------------------------------------------------------------
void DicMerchandise(int nAuth)
{
  TDicMerchandiseForm *pForm;
	try
	{
  	        pForm=new TDicMerchandiseForm(Application);
        }
	catch (Exception &exception)
	{
		Application->ShowException(&exception);
                return;
	}
        pForm->ShowModal();
        delete pForm;
}
__fastcall TDicMerchandiseForm::TDicMerchandiseForm(TComponent* Owner)
        : TForm(Owner)
{
  m_enWorkState=EN_IDLE;
}
//---------------------------------------------------------------------------

void TDicMerchandiseForm::Row2Editor()
{
  TListItem *pItem;

  pItem=ListView1->Selected;
  if(pItem==NULL)	return;
  edtNo->Text = pItem->Caption;
  edtMCode->Text=pItem->SubItems->Strings[0];
  edtMname->Text=pItem->SubItems->Strings[1];
  edtSpec->Text=pItem->SubItems->Strings[2];
  edtFU->Text=pItem->SubItems->Strings[3];
  edtSU->Text=pItem->SubItems->Strings[4];
  edtWeightPercent->Text = pItem->SubItems->Strings[5].IsEmpty()?AnsiString(""):pItem->SubItems->Strings[4];
locateCbbByValue(cbbCrName1,  pItem->SubItems->Strings[6].IsEmpty()?AnsiString(""):pItem->SubItems->Strings[5]);
edtUnitPrice1->Text = pItem->SubItems->Strings[7].IsEmpty()?AnsiString(""):pItem->SubItems->Strings[6];
locateCbbByValue(cbbCrName2,  pItem->SubItems->Strings[8].IsEmpty()?AnsiString(""):pItem->SubItems->Strings[7]);
edtUnitPrice2->Text = pItem->SubItems->Strings[9].IsEmpty()?AnsiString(""):pItem->SubItems->Strings[8];

}

void TDicMerchandiseForm::RefreshData()
{
  char strBuff[512];
  TListItem *pItem;

  if(!dm1->OpenDatabase())  return;
  try
  {
    dm1->Query1->SQL->Clear();
    dm1->Query1->SQL->Add("select * from merchandise order by mcode");

    dm1->Query1->Prepare();
    dm1->Query1->Open();
    dm1->Query1->First();
    ListView1->Items->Clear();
    while(!dm1->Query1->Eof)
    {
    	pItem=ListView1->Items->Add();
      pItem->Caption=dm1->Query1->FieldByName("no")->AsString; 
      pItem->SubItems->Add(dm1->Query1->FieldByName("mcode")->AsString);
      pItem->SubItems->Add(dm1->Query1->FieldByName("mname")->AsString);
      pItem->SubItems->Add(dm1->Query1->FieldByName("spec")->AsString);
      pItem->SubItems->Add(dm1->Query1->FieldByName("firstmeasunit")->AsString);
      pItem->SubItems->Add(dm1->Query1->FieldByName("secondmeasunit")->AsString);
      pItem->SubItems->Add(dm1->Query1->FieldByName("weight_percent")->AsString);
      pItem->SubItems->Add(dm1->Query1->FieldByName("crname1")->AsString);
      pItem->SubItems->Add(dm1->Query1->FieldByName("unitprice1")->AsString);
      pItem->SubItems->Add(dm1->Query1->FieldByName("crname2")->AsString);
      pItem->SubItems->Add(dm1->Query1->FieldByName("unitprice2")->AsString);

       dm1->Query1->Next();
    }
  }
  catch(...)
  {
    ShowMessage("数据库操作错误");
    return;
  }
}

void TDicMerchandiseForm::ResetCtrl()
{
  //bool bAuth = m_nAuthor>=AUTH_FULL;
  bool bAuth = true;
  if(m_enWorkState==EN_IDLE)
  {
    EnableEdit(edtNo,false);
    EnableEdit(edtMCode,false);
EnableEdit(edtMname,false);
EnableEdit(edtSpec,false);
EnableEdit(edtFU,false);
EnableEdit(edtSU,false);
EnableEdit(edtUnitPrice,false);
EnableEdit(edtUnitPrice1,false);
EnableEdit(edtUnitPrice2,false);
    cbbCrName1->Enabled = false;
    cbbCrName2->Enabled = false;
//    cbbWeightPercent->Enabled = false;
   edtWeightPercent->Enabled = false;

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
        EnableEdit(edtMCode,true);
        EnableEdit(edtNo,true);
EnableEdit(edtMname,true);
EnableEdit(edtSpec,true);
EnableEdit(edtFU,true);
EnableEdit(edtSU,true);
EnableEdit(edtUnitPrice,true);
//    cbbWeightPercent->Enabled = true
    edtWeightPercent->Enabled = true;
EnableEdit(edtUnitPrice,true);
EnableEdit(edtUnitPrice1,true);
EnableEdit(edtUnitPrice2,true);
    cbbCrName1->Enabled = true;
    cbbCrName2->Enabled = true;
    
    btnOK0->Enabled=true;
    btnCancel0->Enabled=true;
    if(m_enWorkState==EN_ADDNEW)
	    EnableEdit(edtMCode,true);  
	    EnableEdit(edtNo,true);
    else //修改时
	    EnableEdit(edtMCode,true);   
	    EnableEdit(edtNo,true);
  }
}
void __fastcall TDicMerchandiseForm::FormKeyDown(TObject *Sender,
      WORD &Key, TShiftState Shift)
{
  if (Key==VK_RETURN)
    KeyReturnHandle(ActiveControl);        
}
//---------------------------------------------------------------------------
void __fastcall TDicMerchandiseForm::FormShow(TObject *Sender)
{
  edtNo->Text="";
  edtMCode->Text="";
  edtMname->Text="";
  edtSpec->Text="";
  edtFU->Text="";
  edtSU->Text="";
  edtUnitPrice->Text="";

  RefreshData();
  m_enWorkState=EN_IDLE;
  ResetCtrl();
}
//---------------------------------------------------------------------------
void __fastcall TDicMerchandiseForm::ListView1Click(TObject *Sender)
{
        Row2Editor();
	ResetCtrl();        
}
//---------------------------------------------------------------------------
void __fastcall TDicMerchandiseForm::btnOK0Click(TObject *Sender)
{
  char strNo[80], strMCode[80],strMname[800],strSpec[800],strFU[80],strSU[80],strUnitPrice[80],*ptr,strTemp[800], strWeightPercent[80], strCrName1[80], strUnitPrice1[80], strCrName2[80], strUnitPrice2[80];
  memset(strNo, 0x00, sizeof(strNo));
  memset(strMCode, 0x00, sizeof(strMCode));
  memset(strMname, 0x00, sizeof(strMname));
  memset(strSpec, 0x00, sizeof(strSpec));
  memset(strFU, 0x00, sizeof(strFU));
  memset(strSU, 0x00, sizeof(strSU));
  memset(strUnitPrice, 0x00, sizeof(strUnitPrice));
  memset(strTemp, 0x00, sizeof(strTemp));
  memset(strWeightPercent, 0x00, sizeof(strWeightPercent));
  memset(strCrName1, 0x00, sizeof(strCrName1));
  memset(strCrName2, 0x00, sizeof(strCrName2));
  memset(strUnitPrice1, 0x00, sizeof(strUnitPrice1));
  memset(strUnitPrice2, 0x00, sizeof(strUnitPrice2));

  int nState;

  edtMCode->Text=edtMCode->Text.Trim();

  if(edtMCode->Text.IsEmpty())
  {
  	ShowMessage("请输入编号");
    if(edtMCode->CanFocus())	edtMCode->SetFocus();
    return;
  }
  if (cbbCrName1->ItemIndex == cbbCrName2->ItemIndex){
	ShowMessage("币制不能相同");
        return;
  }

  strcpy(strNO,edtNo->Text==""?"0":edtNo->Text.c_str());
  strcpy(strMCode,edtMCode->Text.c_str());
strcpy(strMname,edtMname->Text.c_str());
strcpy(strSpec,edtSpec->Text.c_str());
strcpy(strFU,edtFU->Text.c_str());
strcpy(strSU,edtSU->Text.c_str());
strcpy(strWeightPercent,edtWeightPercent->Text.c_str());
//strcpy(strWeightPercent,cbbWeightPercent->Text.c_str());
strcpy(strCrName1, cbbCrName1->Text.IsEmpty()?AnsiString("").c_str():cbbCrName1->Text.c_str());
strcpy(strCrName2, cbbCrName2->Text.IsEmpty()?AnsiString("").c_str():cbbCrName2->Text.c_str());



AnsiString sp = "0";
if (!edtUnitPrice->Text.IsEmpty()){
        sp = edtUnitPrice->Text.c_str();
}
strcpy(strUnitPrice,sp.c_str());
AnsiString sp1 = "0";
if (!edtUnitPrice1->Text.IsEmpty()){
        sp1 = edtUnitPrice1->Text.c_str();
}
strcpy(strUnitPrice1,sp1.c_str());
AnsiString sp2 = "0";
if (!edtUnitPrice2->Text.IsEmpty()){
        sp2 = edtUnitPrice2->Text.c_str();
}
strcpy(strUnitPrice2,sp2.c_str());

         TListItem *pItemOld  = ListView1->Selected;

  char strSQL[4024];
  memset(strSQL, 0x00, sizeof(strSQL));
  switch(m_enWorkState)
  {
    case EN_ADDNEW:
      sprintf(strSQL,"insert into merchandise(no,mcode,mname,spec,firstmeasunit,secondmeasunit,weight_percent,crname1,unitprice1,crname2,unitprice2) values('%s','%s','%s','%s','%s','%s','%s','%s','%s','%s')",\
              strNo,strMCode,strMname,strSpec,strFU,strSU,strWeightPercent,strCrName1,strUnitPrice1,strCrName2,strUnitPrice2);
      break;
    case EN_EDIT:
      {
        TListItem *pItem = ListView1->Selected;
        sprintf(strSQL,"update merchandise set no='%s', mcode='%s', mname='%s',spec='%s',firstmeasunit='%s',secondmeasunit='%s',weight_percent='%s',crname1='%s',unitprice1='%s',crname2='%s',unitprice2='%s' where mcode='%s' and mname='%s'",\
        strNo,strMCode,strMname,strSpec,strFU,strSU,strWeightPercent,strCrName1,strUnitPrice1,strCrName2,strUnitPrice2,\
        pItemOld->SubItems->Strings[0],pItemOld->SubItems->Strings[1]);
        edtDebug->Text = AnsiString(strSQL);
      }
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
      char strAddSQL[4024];
      sprintf(strAddSQL,"select * from merchandise where mcode='%s' or mname='%s' or (no='%s' and on!=0 ) order by mcode",strMCode, strMname, strNo);  //20130810 and->or: 不允许重复商品名
      RunSQL(strAddSQL,true);
      if(dm1->Query1->RecordCount>0)
      {
        ShowMessage("数据库中已有该商品的记录!");
        edtMCode->SetFocus();
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
    pItem->Caption = edtNo->Text;   
    pItem->SubItems->Add(edtMCode->Text);
    pItem->SubItems->Add(edtMname->Text);
    pItem->SubItems->Add(edtSpec->Text);
    pItem->SubItems->Add(edtFU->Text);
    pItem->SubItems->Add(edtSU->Text);
    pItem->SubItems->Add(edtWeightPercent->Text);
    pItem->SubItems->Add(cbbCrName1->Text);
    pItem->SubItems->Add(edtUnitPrice1->Text);
    pItem->SubItems->Add(cbbCrName2->Text);
    pItem->SubItems->Add(edtUnitPrice2->Text);

    ListView1->Selected=pItem;
  }
  else if(m_enWorkState==EN_EDIT)
  {
  	pItem=ListView1->Selected;
    if(pItem!=NULL)
    {

            pItem->Caption=edtNo->Text;
            pItem->SubItems->Strings[0] = edtMCode->Text;
            pItem->SubItems->Strings[1] = edtMname->Text;
pItem->SubItems->Strings[2] = edtSpec->Text;
pItem->SubItems->Strings[3] = edtFU->Text;
pItem->SubItems->Strings[4] = edtSU->Text;
pItem->SubItems->Strings[5] = edtWeightPercent->Text;
pItem->SubItems->Strings[6] = cbbCrName1->Text;
pItem->SubItems->Strings[7] = edtUnitPrice1->Text;
pItem->SubItems->Strings[8] = cbbCrName2->Text;
pItem->SubItems->Strings[9] = edtUnitPrice2->Text;

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
void __fastcall TDicMerchandiseForm::btnCancel0Click(TObject *Sender)
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
void __fastcall TDicMerchandiseForm::btnAddNewClick(TObject *Sender)
{
  edtNo->Text = "";
  edtMCode->Text="";
      edtMname->Text="";
  edtSpec->Text="";
  edtFU->Text="";
  edtSU->Text="";
         edtUnitPrice->Text="";
//  cbbWeightPercent->ItemIndex = 0;
  edtWeightPercent->Text = 0;

  cbbCrName1->ItemIndex = -1;
  cbbCrName2->ItemIndex = -1;
  edtUnitPrice1->Text = "";
  edtUnitPrice2->Text = "";

  m_enWorkState=EN_ADDNEW;
  ResetCtrl();
  msgState->Caption="工作状态：新增";
  edtMCode->SetFocus();        
}
//---------------------------------------------------------------------------
void __fastcall TDicMerchandiseForm::btnEditClick(TObject *Sender)
{
  m_enWorkState=EN_EDIT;
  ResetCtrl();
  msgState->Caption="工作状态：修改";
  edtMCode->SetFocus();        
}
//---------------------------------------------------------------------------
void __fastcall TDicMerchandiseForm::btnDeleteClick(TObject *Sender)
{
  char strMsg[256],strSQL[4024];
  memset(strMsg, 0x00, sizeof(strMsg));
  memset(strSQL, 0x00, sizeof(strSQL));
  sprintf(strMsg,"\n  真要删除“%s”的记录吗？  \n",edtMCode->Text.c_str());
  if(Application->MessageBox(strMsg,"警告",MB_YESNOCANCEL | MB_ICONQUESTION | MB_DEFBUTTON2)!=IDYES)
   return;

  sprintf(strSQL,"delete from merchandise where mcode='%s' and mname='%s'",edtMCode->Text.c_str(), edtMname->Text.c_str());
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
void __fastcall TDicMerchandiseForm::btnRefreshClick(TObject *Sender)
{
  RefreshData();
  ResetCtrl();
}
//---------------------------------------------------------------------------
void __fastcall TDicMerchandiseForm::btnExitClick(TObject *Sender)
{
Close();
}
//---------------------------------------------------------------------------



void __fastcall TDicMerchandiseForm::btnQryClick(TObject *Sender)
{
  char strBuff[4024];
  memset(strBuff, 0x00, sizeof(strBuff));
  TListItem *pItem;

  if(!dm1->OpenDatabase())  return;
  try
  {
    CString szSQL;
    szSQL.Format("select * from merchandise where mname like '%%%s%%' order by mcode", edtQryMname->Text.c_str());
    dm1->Query1->SQL->Clear();
    dm1->Query1->SQL->Add(AnsiString(szSQL));

    dm1->Query1->Prepare();
    dm1->Query1->Open();
    dm1->Query1->First();
    ListView1->Items->Clear();
    while(!dm1->Query1->Eof)
    {
    	pItem=ListView1->Items->Add();
      pItem->Caption= dm1->Query1->FieldByName("no")->AsString;
      pItem->SubItems->Add(dm1->Query1->FieldByName("mcode")->AsString);
      pItem->SubItems->Add(dm1->Query1->FieldByName("mname")->AsString);
      pItem->SubItems->Add(dm1->Query1->FieldByName("spec")->AsString);
      pItem->SubItems->Add(dm1->Query1->FieldByName("firstmeasunit")->AsString);
      pItem->SubItems->Add(dm1->Query1->FieldByName("secondmeasunit")->AsString);
      pItem->SubItems->Add(dm1->Query1->FieldByName("weight_percent")->AsString);
      pItem->SubItems->Add(dm1->Query1->FieldByName("crname1")->AsString);
      pItem->SubItems->Add(dm1->Query1->FieldByName("unitprice1")->AsString);
      pItem->SubItems->Add(dm1->Query1->FieldByName("crname2")->AsString);
      pItem->SubItems->Add(dm1->Query1->FieldByName("unitprice2")->AsString);
       dm1->Query1->Next();
    }
  }
  catch(...)
  {
    ShowMessage("数据库操作错误");
    return;
  }
}
//---------------------------------------------------------------------------

void __fastcall TDicMerchandiseForm::edtQryMnameKeyPress(TObject *Sender,
      char &Key)
{
    if (Key==13) //enter key been pressed
    {
        Key=0;
        btnQryClick(Sender);
    }        
}
//---------------------------------------------------------------------------



