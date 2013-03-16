//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "XkCSSZ.h"

#include "LdyInterface.h"
#include "common.hpp"
#include "DataModule.h"
#include "BaseCode.h"
#include "const.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TXkCSSZForm *XkCSSZForm;

void XkCSSZ(int nAuth)
{
  CALL_FORM(TXkCSSZForm);
}
//---------------------------------------------------------------------------
__fastcall TXkCSSZForm::TXkCSSZForm(TComponent* Owner)
        : TForm(Owner)
{
}

//---------------------------------------------------------------------------
bool TXkCSSZForm::checkInput(){
        bool rt = true;

        if (cbbOpCodeSl->Text.IsEmpty() || edtCntNewCli->Text.IsEmpty() ){
                rt = false;
        }

        return rt;

}

int TXkCSSZForm::onAdd(){
        int rt = -1;
        //valid check (empty check)
        if (!checkInput())
        {
                ShowMessage("输入信息不全");
                return rt;
        }

        CString szSQL;
        //key check
        szSQL = "";
        szSQL.Format("select 1 from commition where op_code_sl='%s' and cnt_new_cli!=0 and \
                        year(year_month)='%s' and month(year_month)='%s'", \
                        cbbOpCodeSl->Text, GetYear(dtpYearMonth), GetMonth(dtpYearMonth));
        if (checkDataExist(szSQL)){
                ShowMessage("数据库中已有该编号的记录");
                return rt;
        }
        szSQL.Format("select 1 from commition where op_code_sl='%s' and \
                        year(year_month)='%s' and month(year_month)='%s'", \
                        cbbOpCodeSl->Text, GetYear(dtpYearMonth), GetMonth(dtpYearMonth));

        if (checkDataExist(szSQL) ){  
                szSQL.Format("update commition set cnt_new_cli='%s' \
                                where op_code_sl='%s' and year(year_month)='%s' and month(year_month)='%s' ", \
                                edtCntNewCli->Text, cbbOpCodeSl->Text, GetYear(dtpYearMonth), GetMonth(dtpYearMonth));
        }else {
                szSQL.Format("insert into commition(op_code_sl,year_month,cnt_new_cli) values('%s','%s','%s')", \
                        cbbOpCodeSl->Text, GetDate(dtpYearMonth), edtCntNewCli->Text);
        }
        edtDebug->Text = AnsiString(szSQL);
        if(!RunSQL(dm1->Query1,szSQL))
        {
                ShowMessage("添加失败!") ;
                return rt;
        }
        //flush
        Editor2RowAdd(lvXkCSSZ);
        return 0;
}

void TXkCSSZForm::onMod(){

        CString szSQL = "";
        szSQL.Format("update commition \
                        set cnt_new_cli='%s' \
                        where op_code_sl='%s' and year_month between '%s' and '%s'", \
                        edtCntNewCli->Text.IsEmpty()?AnsiString("0"):edtCntNewCli->Text,\
                        cbbOpCodeSl->Text, GetMonthBegin(dtpYearMonth), GetMonthEnd(dtpYearMonth));
        edtDebug->Text = AnsiString(szSQL);
        if(!RunSQL(dm1->Query1,szSQL))
        {
                ShowMessage("更新应付记录失败!") ;
                return;
        }

        TListItem *pItem = lvXkCSSZ->Selected;
        if(pItem==NULL)
                return;
	pItem->SubItems->Strings[1] = edtCntNewCli->Text;
}

void __fastcall TXkCSSZForm::FormShow(TObject *Sender)
{

        edtCntNewCli->Text = "";
        lvXkCSSZ->Clear();
        //load base data
        cbbOpCodeSl->Items->Add("");
        CString szSQL = "";
        szSQL.Format("select op_code from operator where op_class='%d'", E_OPERATOR_TYPE_SALER);
        RunSQL(dm1->Query1,szSQL,true);
	while(!dm1->Query1->Eof)
	{
                AnsiString opcode = dm1->Query1->FieldByName("op_code")->AsString;
                cbbOpCodeSl->Items->Add(opcode);
                dm1->Query1->Next();
        }

        TDateTime tNow=TDateTime::CurrentDateTime();
        dtpYearMonth->DateTime=tNow;

        szSQL = "select op_code_sl,cast(DATEPART(yyyy,year_month) as varchar) + '-' + cast(DATEPART(mm,year_month) as varchar) as ym, \
                        cnt_new_cli \
                        from commition where (cnt_new_cli!=0) order by op_code_sl, year_month";
//        edtDebug->Text = AnsiString(szSQL);
        //run
        RunSQL(dm1->Query1, szSQL, true);
        if (dm1->Query1->Eof){
                ShowMessage("记录不存在");
        }
        //clear
//        clearInput();
        lvXkCSSZ->Clear();

        //show
	while(!dm1->Query1->Eof)
	{
                TListItem *pItem = lvXkCSSZ->Items->Add();
                pItem->Caption = dm1->Query1->FieldByName("op_code_sl")->AsString;
                pItem->SubItems->Add(dm1->Query1->FieldByName("ym")->AsString);
                pItem->SubItems->Add(dm1->Query1->FieldByName("cnt_new_cli")->AsString);
        	dm1->Query1->Next();
        }
}
//---------------------------------------------------------------------------
void __fastcall TXkCSSZForm::lvXkCSSZSelectItem(TObject *Sender,
      TListItem *Item, bool Selected)
{
        if (Selected == NULL){
                return;
        }
        locateCbbByValue(cbbOpCodeSl, Item->Caption);
        edtCntNewCli->Text = Item->SubItems->Strings[1];
        AnsiString strDate = Item->SubItems->Strings[0];
        strDate += AnsiString("-1");
        //toimp - 发放时间
        SetDateTimePicker(dtpYearMonth, strDate);        
        ResetCtrl();
}
//---------------------------------------------------------------------------

void TXkCSSZForm::ResetCtrl(){
  bool bAuth = true; //= m_nAuthor>=AUTH_FULL;
  if(m_enWorkState==EN_IDLE)
  {
    bool isSelected = (lvXkCSSZ->Selected!=NULL);
    lvXkCSSZ->Enabled = true;
    //btn
    btnAdd->Enabled = true && bAuth;
    btnMod->Enabled = isSelected && bAuth;
    btnDel->Enabled = isSelected && bAuth;
    btnOK->Enabled  = false;
    btnCancel->Enabled = false;
    //input area -> all false
    enablePlCtrl(plInput, false);
  }
  else
  {
    //btn
    btnAdd->Enabled = false;
    btnMod->Enabled = false;
    btnDel->Enabled = false;
    btnCancel->Enabled=true;
    btnOK->Enabled  = true;
    //lstview
    lvXkCSSZ->Enabled = false;
    //input area ->true
    enablePlCtrl(plInput, true);
  }
}
void __fastcall TXkCSSZForm::btnModClick(TObject *Sender)
{
  m_enWorkState = EN_EDIT;
  ResetCtrl();                
}
//---------------------------------------------------------------------------
void __fastcall TXkCSSZForm::btnOKClick(TObject *Sender)
{
  char strName[80],*ptr,strTemp[80];
  int nState;
  int oldState = m_enWorkState;
  switch(m_enWorkState)
  {
    case EN_ADDNEW:
      if (-1 == onAdd())
        return;
      break;
    case EN_EDIT:
       onMod();
      break;
    default:
      ShowMessage("Work State not AddNew or Edit");
      return;
  }
  m_enWorkState = EN_IDLE;
  ResetCtrl();
  btnMod->Enabled=false;
  btnDel->Enabled=false;
  if(oldState==EN_EDIT){
    lvXkCSSZ->Selected=NULL;
  }                
}
//---------------------------------------------------------------------------
void __fastcall TXkCSSZForm::btnCancelClick(TObject *Sender)
{
  int nState;

  nState = m_enWorkState;
  m_enWorkState = EN_IDLE;
  ResetCtrl();
  lvXkCSSZ->Selected=NULL;

  switch(nState)
  { //设置确定後的光标位置
    case EN_ADDNEW:
        if (btnAdd->CanFocus())
                btnAdd->SetFocus();
        break;
    case EN_EDIT:
        if (btnMod->CanFocus())
                btnMod->SetFocus();
        break;
    default:  break;
  }
    btnMod->Enabled=false;
    btnDel->Enabled=false;        
}
//---------------------------------------------------------------------------

void TXkCSSZForm::Editor2RowAdd(TListView *lv){
        TListItem *pItem = lvXkCSSZ->Items->Add();
        if(pItem==NULL)
                return;
        pItem->Caption = cbbOpCodeSl->Text;
	pItem->SubItems->Add(AnsiString(GetYearMonth(dtpYearMonth)));
        pItem->SubItems->Add(edtCntNewCli->Text);
}
void __fastcall TXkCSSZForm::btnDelClick(TObject *Sender)
{
        char strMsg[256],strSQL[512];
        sprintf(strMsg,"\n  真要删除“%s - %s”的记录吗？  \n", cbbOpCodeSl->Text.c_str(), GetYearMonth(dtpYearMonth));
        if(Application->MessageBox(strMsg,"警告",MB_YESNOCANCEL | MB_ICONQUESTION | MB_DEFBUTTON2)!=IDYES)
                return;

        CString szSQL;
        szSQL.Format("update commition set cnt_new_cli=0 where op_code_sl='%s' and year_month between '%s' and '%s'", cbbOpCodeSl->Text.c_str(), GetMonthBegin(dtpYearMonth), GetMonthEnd(dtpYearMonth));
        if(!RunSQL(dm1->Query1,szSQL))
                ShowMessage("delete fail!");
        edtDebug->Text = AnsiString(szSQL);

        //btnQueryClick(Sender);
        delLvItem(lvXkCSSZ);
        ShowMessage("删除成功");
//        clearInput();        
}
//---------------------------------------------------------------------------

void __fastcall TXkCSSZForm::btnAddClick(TObject *Sender)
{
        edtCntNewCli->Text = "";
        cbbOpCodeSl->Text ="";
        m_enWorkState = EN_ADDNEW;
        ResetCtrl();
}
//---------------------------------------------------------------------------

