//---------------------------------------------------------------------------

#include <vcl.h>
#include <stdio.h>
#pragma hdrstop

#include "DicClient.h"
#include "DicClientQry.h"
#include "DataModule.h"
#include "BaseCode.h"
#include "LdyInterface.h"
#include "common.hpp"
#include "const.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "trayicon"
#pragma resource "*.dfm"
TDicClientForm *DicClientForm;
void DicClient(int nAuth)
{
//  CALL_FORM(TDicClientForm);
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
        pForm->m_nAuthor=nAuth;        
        pForm->ShowModal();
        delete pForm;
}
//---------------------------------------------------------------------------
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
        if(pItem==NULL)
                return;
        edtCid->Text=pItem->Caption;
        int i = 0;
        setDtp(dtpDate, pItem->SubItems->Strings[i++]);
	edtNameCh->Text = pItem->SubItems->Strings[i++];
	edtNameEn->Text = pItem->SubItems->Strings[i++];
	edtNameShort->Text = pItem->SubItems->Strings[i++];
        locateCbbByValue(cbbClientType, pItem->SubItems->Strings[i++]);
        locateCbbByValue(cbbOpType, pItem->SubItems->Strings[i++]);
	edtAddress->Text = pItem->SubItems->Strings[i++];
	edtTel->Text = pItem->SubItems->Strings[i++];
	edtFax->Text = pItem->SubItems->Strings[i++];
	edtLinkMan->Text = pItem->SubItems->Strings[i++];
	edtTelLinkMan->Text = pItem->SubItems->Strings[i++];
	edtQQ->Text = pItem->SubItems->Strings[i++];
	edtMsn->Text = pItem->SubItems->Strings[i++];
	edtEmail->Text = pItem->SubItems->Strings[i++];
        locateCbbByValue(cbbOpCodeSl, pItem->SubItems->Strings[i++]);
        locateCbbByValue(cbbSettlementType, pItem->SubItems->Strings[i++]);
        locateCbbByValue(cbbReputation, pItem->SubItems->Strings[i++]);
        locateCbbByValue(cbbSettlementCycle, pItem->SubItems->Strings[i++]);
	edtFirstOpId->Text = pItem->SubItems->Strings[i++];
	edtRemarks->Text = pItem->SubItems->Strings[i++];    
        locateCbbByValue(cbbOpCodeSl, pItem->SubItems->Strings[i++]);
        locateCbbByValue(cbbOpCodeOp, pItem->SubItems->Strings[i++]);


}

void TDicClientForm::Editor2Row2(TListItem *pItem)
{
        if(pItem==NULL)
                return;
        pItem->Caption = edtCid->Text;

        int i = 0;

	pItem->SubItems->Add(AnsiString(GetDate(dtpDate))  				  );        
	pItem->SubItems->Add(edtNameCh->Text );
	pItem->SubItems->Add(edtNameEn->Text );
	pItem->SubItems->Add(edtNameShort->Text  			);
	pItem->SubItems->Add(cbbClientType->Text  		  );
	pItem->SubItems->Add(cbbOpType->Text  				  );
	pItem->SubItems->Add(edtAddress->Text  				);
	pItem->SubItems->Add(edtTel->Text  						);
	pItem->SubItems->Add(edtFax->Text  						);
	pItem->SubItems->Add(edtLinkMan->Text  				);
	pItem->SubItems->Add(edtTelLinkMan->Text  		  );
	pItem->SubItems->Add(edtQQ->Text  						  );
	pItem->SubItems->Add(edtMsn->Text  						);
	pItem->SubItems->Add(edtEmail->Text  					);
	pItem->SubItems->Add(cbbOpCodeSl->Text  				  );
	pItem->SubItems->Add(cbbSettlementType->Text   );
	pItem->SubItems->Add(cbbReputation->Text  		  );
	pItem->SubItems->Add(cbbSettlementCycle->Text  );
	pItem->SubItems->Add(edtFirstOpId->Text  			);
	pItem->SubItems->Add(edtRemarks->Text  				);
	pItem->SubItems->Add(cbbOpCodeSl->Text  				);
	pItem->SubItems->Add(cbbOpCodeOp->Text  				);


}

void TDicClientForm::Editor2Row(TListItem *pItem)
{
        if(pItem==NULL)
                return;
        pItem->Caption = edtCid->Text;

        int i = 0;

	pItem->SubItems->Strings[i++]= AnsiString(GetDate(dtpDate))  				  ;
	pItem->SubItems->Strings[i++]= edtNameCh->Text ;
	pItem->SubItems->Strings[i++]= edtNameEn->Text ;
	pItem->SubItems->Strings[i++]= edtNameShort->Text  			;
	pItem->SubItems->Strings[i++]= cbbClientType->Text  		  ;
	pItem->SubItems->Strings[i++]= cbbOpType->Text  				  ;
	pItem->SubItems->Strings[i++]= edtAddress->Text  				;
	pItem->SubItems->Strings[i++]= edtTel->Text  						;
	pItem->SubItems->Strings[i++]= edtFax->Text  						;
	pItem->SubItems->Strings[i++]= edtLinkMan->Text  				;
	pItem->SubItems->Strings[i++]= edtTelLinkMan->Text  		  ;
	pItem->SubItems->Strings[i++]= edtQQ->Text  						  ;
	pItem->SubItems->Strings[i++]= edtMsn->Text  						;
	pItem->SubItems->Strings[i++]= edtEmail->Text  					;
	pItem->SubItems->Strings[i++]= cbbOpCodeSl->Text  				  ;
	pItem->SubItems->Strings[i++]= cbbSettlementType->Text   ;
	pItem->SubItems->Strings[i++]= cbbReputation->Text  		  ;
	pItem->SubItems->Strings[i++]= cbbSettlementCycle->Text  ;
	pItem->SubItems->Strings[i++]= edtFirstOpId->Text  			;
	pItem->SubItems->Strings[i++]= edtRemarks->Text  				;

}
void TDicClientForm::RefreshData(CString outsideSQL)
{
  char strBuff[512];
  TListItem *pItem;

  if(!dm1->OpenDatabase())  return;
  try
  {
    CString szSQL = "";
    if (outsideSQL!=""){
        szSQL = outsideSQL;
    } else {
            if (g_theOperator.op_class==E_OPERATOR_TYPE_SALER){
                    szSQL.Format("select * from client where op_code_sl='%s' order by cid", g_theOperator.op_code);
            } else if (g_theOperator.op_class==E_OPERATOR_TYPE_OPERATOR) {
                    szSQL.Format("select * from client where op_code_op='%s' order by cid", g_theOperator.op_code);
            } else {
                    szSQL.Format("select * from client order by cid");
            }
    }
    dm1->Query1->SQL->Clear();
    dm1->Query1->SQL->Add(AnsiString(szSQL));

    dm1->Query1->Prepare();
    dm1->Query1->Open();
    dm1->Query1->First();
    ListView1->Items->Clear();
    while(!dm1->Query1->Eof)
    {
        pItem=ListView1->Items->Add();

//        pItem->SubItems->f = pItem->ItemIndex%2==0 ? pIte->BackColor : Color.clSkyBlue;
	pItem->Caption			=dm1->Query1->FieldByName("cid")->AsString;
	pItem->SubItems->Add(dm1->Query1->FieldByName("op_date")->AsString);
	pItem->SubItems->Add(dm1->Query1->FieldByName("name_ch")->AsString);    
	pItem->SubItems->Add(dm1->Query1->FieldByName("name_en")->AsString);    
	pItem->SubItems->Add(dm1->Query1->FieldByName("short_name")->AsString);    
	pItem->SubItems->Add(dm1->Query1->FieldByName("type")->AsString);
	pItem->SubItems->Add(dm1->Query1->FieldByName("optype")->AsString);    
	pItem->SubItems->Add(dm1->Query1->FieldByName("address")->AsString);    
	pItem->SubItems->Add(dm1->Query1->FieldByName("tel")->AsString);    
	pItem->SubItems->Add(dm1->Query1->FieldByName("fax")->AsString);    
	pItem->SubItems->Add(dm1->Query1->FieldByName("link_man")->AsString);    
	pItem->SubItems->Add(dm1->Query1->FieldByName("tel_lk")->AsString);    
	pItem->SubItems->Add(dm1->Query1->FieldByName("qq_lk")->AsString);    
	pItem->SubItems->Add(dm1->Query1->FieldByName("msn_lk")->AsString);    
	pItem->SubItems->Add(dm1->Query1->FieldByName("email_lk")->AsString);    
	pItem->SubItems->Add(dm1->Query1->FieldByName("op_code_sl")->AsString);    
	pItem->SubItems->Add(dm1->Query1->FieldByName("settlement_type")->AsString);    
	pItem->SubItems->Add(dm1->Query1->FieldByName("reputation")->AsString);    
	pItem->SubItems->Add(dm1->Query1->FieldByName("settlement_cycle")->AsString);    
	pItem->SubItems->Add(dm1->Query1->FieldByName("first_opid")->AsString);
	pItem->SubItems->Add(dm1->Query1->FieldByName("remarks")->AsString);
	pItem->SubItems->Add(dm1->Query1->FieldByName("op_code_sl")->AsString);
	pItem->SubItems->Add(dm1->Query1->FieldByName("op_code_op")->AsString);

	
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
  bool bSaler = g_theOperator.op_class==E_OPERATOR_TYPE_SALER;
  bool bAuth = m_nAuthor>=AUTH_FULL;
//  bool bAuth = true;
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
      btnDelete->Enabled=true && bAuth && !bSaler;
    }
    else
    {
      btnEdit->Enabled=false;
      btnDelete->Enabled=false;
    }
//    plQry->Enabled = true;
  }
  else
  {
//    plQry->Enabled = false;
    btnAddNew->Enabled=false;
    btnRefresh->Enabled=false;
    btnExit->Enabled=false;
    ListView1->Enabled=false;
    btnEdit->Enabled=false;
    btnDelete->Enabled=false;
    
    enablePlCtrl(plInput, true);
    edtFirstOpId->Enabled = false;
//    edtSlName->Enabled = false;//特殊处理
    cbbOpCodeOp->Enabled = false;
    btnOK0->Enabled=true;
    btnCancel0->Enabled=true;
/*    if(m_enWorkState==EN_ADDNEW)
	    EnableEdit(edtCid,true);
    else //修改时
	    EnableEdit(edtCid,false);
*/
  }
  //any time false
  EnableEdit(edtCid,false);
}




void __fastcall TDicClientForm::ListView1Click(TObject *Sender)
{
        Row2Editor();
        ResetCtrl();
//        ListView1->Canvas->Brush->Color= clSkyBlue;
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

void __fastcall TDicClientForm::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
  if (Key==VK_RETURN)
    KeyReturnHandle(ActiveControl);
}
//---------------------------------------------------------------------------

void __fastcall TDicClientForm::FormShow(TObject *Sender)
{

        clearInput();
        //sl
        cbbOpCodeSl->ItemIndex = -1;
        cbbOpCodeSl->Items->Add("");
        CString szSQL="";
	szSQL.Format("select * from operator where op_class='%d'", E_OPERATOR_TYPE_SALER);
	RunSQL(dm1->Query1,szSQL,true);
	while(!dm1->Query1->Eof)
	{
                cbbOpCodeSl->Items->Add(dm1->Query1->FieldByName("op_code")->AsString);
		dm1->Query1->Next();
        }
        //op
        cbbOpCodeOp->ItemIndex = -1;
        cbbOpCodeOp->Items->Add("");
	szSQL.Format("select * from operator where op_class='%d'", E_OPERATOR_TYPE_OPERATOR);
	RunSQL(dm1->Query1,szSQL,true);
	while(!dm1->Query1->Eof)
	{
                cbbOpCodeOp->Items->Add(dm1->Query1->FieldByName("op_code")->AsString);
		dm1->Query1->Next();
        }

  //~
  RefreshData();
  m_enWorkState = EN_IDLE;
  ResetCtrl();
}
//---------------------------------------------------------------------------
AnsiString TDicClientForm::getInsertedId(){
        AnsiString rt="";
        //sl
        CString szSQL="";
	szSQL.Format("select DISTINCT @@IDENTITY as inserted_id  from client");
	RunSQL(dm1->Query1,szSQL,true);
	if(!dm1->Query1->Eof)
	{
                rt = dm1->Query1->FieldByName("inserted_id")->AsString;
        }
        return rt;
}
void TDicClientForm::clearInput(){
	edtCid->Text = "";
	edtNameShort->Text = "";          
	edtNameCh->Text = "";
	edtNameEn->Text = "";
	cbbClientType->Text = "";
	cbbOpType->Text = "";
	edtAddress->Text = "";
	edtTel->Text = "";                
	edtFax->Text = "";
	edtLinkMan->Text = "";            
	edtTelLinkMan->Text = "";
	edtQQ->Text = "";
	edtMsn->Text = "";
	edtEmail->Text = "";
//	edtSlName->Text = "";

	cbbSettlementType->Text = "";
	cbbReputation->Text = "";
	cbbSettlementCycle->Text = "";
	edtFirstOpId->Text = "";
	edtRemarks->Text = "";
        cbbOpCodeOp->Text = "";
        SetDateTimePicketNow(dtpDate);
}

bool TDicClientForm::checkInput(){
    bool rt = true;

    if (	//edtCid->Text.IsEmpty() ||                
	edtNameShort->Text.IsEmpty() ||          
	edtNameCh->Text.IsEmpty() ||             
	edtNameEn->Text.IsEmpty() ||             
	cbbClientType->Text.IsEmpty() ||     
	cbbOpType->Text.IsEmpty() ||         
	edtAddress->Text.IsEmpty() ||            
	edtTel->Text.IsEmpty() ||                
	edtFax->Text.IsEmpty() ||                
	edtLinkMan->Text.IsEmpty() ||            
	edtTelLinkMan->Text.IsEmpty() ||         
//	edtQQ->Text.IsEmpty() ||
//	edtMsn->Text.IsEmpty() ||
//	edtEmail->Text.IsEmpty() ||              
	cbbOpCodeSl->Text.IsEmpty() ||             
	cbbSettlementType->Text.IsEmpty() || 
	cbbReputation->Text.IsEmpty() ||     
	cbbSettlementCycle->Text.IsEmpty() ||
//	edtFirstOpId->Text.IsEmpty() ||              
	edtRemarks->Text.IsEmpty())
    {
        rt = false;
    }

    return rt;
}
void __fastcall TDicClientForm::btnOK0Click(TObject *Sender)
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
      szSQL.Format("insert into client(name_ch, name_en, short_name, type, \
                        optype, address, tel, fax, \
                        link_man, tel_lk, qq_lk, msn_lk, email_lk, \
                        op_code_sl, settlement_type, reputation, settlement_cycle, /*first_opid, */op_date, remarks, op_code_op) \
                        values('%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', \
                        '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s')", \
                        edtNameCh->Text, edtNameEn->Text, edtNameShort->Text, cbbClientType->Text, \
                        cbbOpType->Text, edtAddress->Text, edtTel->Text, edtFax->Text, \
                        edtLinkMan->Text, edtTelLinkMan->Text, edtQQ->Text, edtMsn->Text, edtEmail->Text, \
                        cbbOpCodeSl->Text, cbbSettlementType->Text, cbbReputation->Text, cbbSettlementCycle->Text, \
                        /*edtFirstOpId->Text, */GetDate(dtpDate), edtRemarks->Text, cbbOpCodeOp->Text);
      break;
    case EN_EDIT:
      szSQL.Format("update client set name_ch='%s', name_en='%s', short_name='%s', type='%s', \
                        optype='%s', address='%s', tel='%s', fax='%s', \
                        link_man='%s', tel_lk='%s', qq_lk='%s', msn_lk='%s', email_lk='%s', \
                        settlement_type='%s', reputation='%s', settlement_cycle='%s', op_date='%s', remarks='%s' \
                     where cid='%s' and op_code_sl='%s'", edtNameCh->Text, edtNameEn->Text, edtNameShort->Text, cbbClientType->Text, \
                        cbbOpType->Text, edtAddress->Text, edtTel->Text, edtFax->Text, \
                        edtLinkMan->Text, edtTelLinkMan->Text, edtQQ->Text, edtMsn->Text, edtEmail->Text, \
                        /*edtSlName->Text, */cbbSettlementType->Text, cbbReputation->Text, cbbSettlementCycle->Text, \
                        /*edtFirstOpId->Text, */GetDate(dtpDate), edtRemarks->Text, \
                        edtCid->Text, cbbOpCodeSl->Text);

      break;
    default:
      ShowMessage("Work State not AddNew or Edit");
      return;
  }
  edtDebug->Text = AnsiString(szSQL);
  if(!dm1->OpenDatabase())  return;

  try
  {
    if(m_enWorkState==EN_ADDNEW)
    {
      CString strAddSQL = "";
      strAddSQL.Format("select * from client where short_name='%s'", edtNameShort->Text);
//      edtDebug->Text = AnsiString(strAddSQL);
      if (checkDataExist(strAddSQL)){
        ShowMessage("数据库中已有该编号或简称的记录!");
        edtCid->SetFocus();
        return;
      }
    } else if (m_enWorkState==EN_EDIT){
      char strEditSQL[256];
      memset(strEditSQL, 0x00, sizeof(strEditSQL));
      sprintf(strEditSQL,"select * from client where cid!='%s' and short_name='%s'", edtCid->Text, edtNameShort->Text);
      RunSQL(strEditSQL,true);
      if(!dm1->Query1->Eof)
      {
        ShowMessage("数据库中已有该简称的记录!");
        edtNameShort->SetFocus();
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
    //flush cid first
    edtCid->Text = getInsertedId();
    Editor2Row2(pItem);
    ListView1->Selected=pItem;
  }
  else if(m_enWorkState==EN_EDIT)
  {
    pItem=ListView1->Selected;
    Editor2Row(pItem);
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
  clearInput();
  m_enWorkState=EN_ADDNEW;
  //flush slname

//  locateCbbByValue(cbbOpCodeSl, g_theOperator.op_code);
  locateCbbByValue(cbbOpCodeOp, g_theOperator.op_code);

  //~
  ResetCtrl();
  msgState->Caption="工作状态：新增";
  edtNameCh->SetFocus();         
}
//---------------------------------------------------------------------------

void __fastcall TDicClientForm::btnEditClick(TObject *Sender)
{
  m_enWorkState=EN_EDIT;
  ResetCtrl();
  msgState->Caption="工作状态：修改";
//  edtName->SetFocus();
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
















void __fastcall TDicClientForm::ListView1DrawItem(TCustomListView *Sender,
      TListItem *Item, TRect &Rect, TOwnerDrawState State)
{
//Sender->Canvas->Font->Color = clRed;

 ListView1->Canvas->Brush->Color   =     Item->Index %2 ?   clSkyBlue  :   clInfoBk ;          
}
//---------------------------------------------------------------------------


void __fastcall TDicClientForm::ListView1CustomDrawItem(
      TCustomListView *Sender, TListItem *Item, TCustomDrawState State,
      bool &DefaultDraw)
{
 ListView1->Canvas->Brush->Color   =     Item->Index %2 ?   clSkyBlue  :   clInfoBk ;        
}
//---------------------------------------------------------------------------



void __fastcall TDicClientForm::btnQryClick(TObject *Sender)
{
        CString outsideSQL = "";
        TDicClientQryForm *pForm;
	try
	{
  	        pForm=new TDicClientQryForm(Application);
        }
	catch (Exception &exception)
	{
		Application->ShowException(&exception);
                return;
	}
        pForm->m_outsideSQL = outsideSQL;        
        pForm->ShowModal();
//        delete pForm;

        //qry
        CString sql = pForm->m_outsideSQL;
        delete pForm;
        RefreshData(sql);
        edtDebug->Text = AnsiString(sql);

}
//---------------------------------------------------------------------------
  /*
void __fastcall TDicClientForm::FormCreate(TObject *Sender)
{

}
*/
//---------------------------------------------------------------------------

void __fastcall TDicClientForm::Button1Click(TObject *Sender)
{
         this->TrayIcon1->Minimize();               
}
//---------------------------------------------------------------------------


