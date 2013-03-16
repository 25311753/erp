//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Commition.h"
#include "LdyInterface.h"
#include "common.hpp"
#include "DataModule.h"
#include "BaseCode.h"
#include "const.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "trayicon"
#pragma resource "*.dfm"
TCommitionForm *CommitionForm;
void Commition(int nAuth)
{
  CALL_FORM(TCommitionForm)
}

//---------------------------------------------------------------------------
__fastcall TCommitionForm::TCommitionForm(TComponent* Owner)
        : TForm(Owner)
{
        m_enWorkState=EN_IDLE;
}
//---------------------------------------------------------------------------
void __fastcall TCommitionForm::FormShow(TObject *Sender)
{
        clearInput();
        lvCommition->Clear();
        lvYearCommition->Clear();
        cbbOpCodeSl->Text = "";

        cbIsQryByDate->Checked = true;

        //ratio
        for (int i=100; i>0; --i){
                cbbRatio->Items->Add(i);

        }
        //load base data
        cbbYearOpCodeSl->Items->Add("");
        CString szSQL = "";
        szSQL.Format("select op_code from operator where op_class='%d'", E_OPERATOR_TYPE_SALER);
        RunSQL(dm1->Query1,szSQL,true);
	while(!dm1->Query1->Eof)
	{
                AnsiString opcode = dm1->Query1->FieldByName("op_code")->AsString;
                cbbOpCodeSl->Items->Add(opcode);
                cbbQryOpCodeSl->Items->Add(opcode);
                cbbYearOpCodeSl->Items->Add(opcode);


                dm1->Query1->Next();
        }
        TDateTime tNow=TDateTime::CurrentDateTime();
        dtpQryDateBegin->DateTime=tNow;
        dtpQryDateEnd->DateTime=tNow;
        ResetCtrl();
}
//---------------------------------------------------------------------------

void TCommitionForm::clearInput(){
        edtBusiVolume->Text = "";
        edtCntNewCli->Text = "";
}

bool TCommitionForm::checkInput(){
        bool rt = true;

        if (cbbOpCodeSl->Text.IsEmpty() || edtBusiVolume->Text.IsEmpty() || cbbRatio->Text.IsEmpty()){
                rt = false;
        }

        return rt;

}

int TCommitionForm::onAdd(){
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
        szSQL.Format("select 1 from commition where op_code_sl='%s' and \
                        year(year_month)='%s' and month(year_month)='%s'", \
                        cbbOpCodeSl->Text, GetYear(dtpYearMonth), GetMonth(dtpYearMonth));
        if (checkDataExist(szSQL)){
                ShowMessage("数据库中已有该编号的记录");
                return rt;
        }
        //insert
        szSQL.Format("insert into commition(op_code_sl,year_month,busi_volume_base, ratio) values('%s','%s','%s','%s')", \
                        cbbOpCodeSl->Text, GetDate(dtpYearMonth), getByEdt(edtBusiVolume).c_str(), cbbRatio->Text);
//        edtDebug->Text = AnsiString(szSQL);
        if(!RunSQL(dm1->Query1,szSQL))
        {
                ShowMessage("添加失败!") ;
                return rt;
        }
        //flush
        Editor2RowAdd(lvCommition);
        return 0;
}

void TCommitionForm::Editor2RowAdd(TListView *lv){
        TListItem *pItem = lv->Items->Add();
        if(pItem==NULL)
                return;
        pItem->Caption = cbbOpCodeSl->Text;
	pItem->SubItems->Add(AnsiString(GetYearMonth(dtpYearMonth)));
	pItem->SubItems->Add("");
	pItem->SubItems->Add(edtBusiVolume->Text);
        pItem->SubItems->Add(edtCntNewCli->Text);
        pItem->SubItems->Add("");
	pItem->SubItems->Add("");
	pItem->SubItems->Add("");
	pItem->SubItems->Add("");
	pItem->SubItems->Add("");
        pItem->SubItems->Add("否");
        pItem->SubItems->Add(cbbRatio->Text);


}
void TCommitionForm::onMod(){
        CString szSQL = "";
        AnsiString date_grant = cbbPassed->Text == "是"?AnsiString(GetDate(dtpGrantDate)):AnsiString("");
        szSQL.Format("update commition \
                        set passed='%s',date_grant='%s',cnt_new_cli='%s', \
                        busi_volume_base='%s', ratio='%s' \
                        where op_code_sl='%s' and year_month between '%s' and '%s'", \
                        cbbPassed->Text, date_grant.c_str(), edtCntNewCli->Text.IsEmpty()?AnsiString("0"):edtCntNewCli->Text,\
                        edtBusiVolume->Text, cbbRatio->Text,\
                        cbbOpCodeSl->Text, GetMonthBegin(dtpYearMonth), GetMonthEnd(dtpYearMonth));
        edtDebug->Text = AnsiString(szSQL);
        if(!RunSQL(dm1->Query1,szSQL))
        {
                ShowMessage("更新应付记录失败!") ;
                return;
        }

        //flush
//        Editor2RowUpdateOut(lvOut->Selected);
        TListItem *pItem = lvCommition->Selected;
        if(pItem==NULL)
                return;
	pItem->SubItems->Strings[7] = date_grant;
	pItem->SubItems->Strings[8] = AnsiString(cbbPassed->Text);
        pItem->SubItems->Strings[10] = cbbRatio->Text;


}
void __fastcall TCommitionForm::btnOKClick(TObject *Sender)
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
    lvCommition->Selected=NULL;
  }        
}
//---------------------------------------------------------------------------

void __fastcall TCommitionForm::btnQryClick(TObject *Sender)
{
//                        dbo.gen_new_cli_prize_yearmonth(year_month,op_code_sl) as prize_new_cli, \ \\20120718 去掉新客奖励显示
       CString szSQL = "";
        szSQL = "select dbo.get_cnt_new_cli(op_code_sl, year_month) cnt_new_cli_cur,    \
                        cast(100*isnull(busi_volume_cur,0)/isnull(busi_volume_base,100) as decimal(9,2)) as pect_busi, \
                        *,  \
                        dbo.gen_should_com(busi_volume_cur, dbo.gen_new_cli_prize_yearmonth(year_month,op_code_sl), busi_volume_base, ratio) should_com, \
                        cast(DATEPART(yyyy,year_month) as varchar) + '-' + cast(DATEPART(mm,year_month) as varchar) as ym \
                from commition where 1=1 ";
        if (g_theOperator.op_class==E_OPERATOR_TYPE_SALER){    //业务职能看到自己所属
                szSQL += "and op_code_sl="; szSQL += Str2DBString(g_theOperator.op_code);
        } else if (!cbbQryOpCodeSl->Text.IsEmpty()){           //其他不受限制
                szSQL += "and op_code_sl="; szSQL += Str2DBString(cbbQryOpCodeSl->Text.c_str());
        }
        if (cbIsQryByDate->Checked) {
                szSQL += " and year_month between "; szSQL += Str2DBString(GetMonthBegin(dtpQryDateBegin));
                szSQL += " and ";
                szSQL += Str2DBString(GetMonthEnd(dtpQryDateEnd));
        }
        szSQL += " order by op_code_sl, year_month";
        edtDebug->Text = AnsiString(szSQL);
        //run
        RunSQL(dm1->Query1, szSQL, true);
        if (dm1->Query1->Eof){
                ShowMessage("记录不存在");
        }
        //clear
//        clearInput();
        lvCommition->Clear();

        //show
	while(!dm1->Query1->Eof)
	{
                TListItem *pItem = lvCommition->Items->Add();
                pItem->Caption = dm1->Query1->FieldByName("op_code_sl")->AsString;
                pItem->SubItems->Add(dm1->Query1->FieldByName("ym")->AsString);
                pItem->SubItems->Add(dm1->Query1->FieldByName("busi_volume_cur")->AsString);
                pItem->SubItems->Add(dm1->Query1->FieldByName("busi_volume_base")->AsString);
//                pItem->SubItems->Add(dm1->Query1->FieldByName("prize_new_cli")->AsString);
                int cnt_new_cli = dm1->Query1->FieldByName("cnt_new_cli")->AsInteger;
                int cnt_new_cli_cur = dm1->Query1->FieldByName("cnt_new_cli_cur")->AsInteger;
                pItem->SubItems->Add(cnt_new_cli);
                pItem->SubItems->Add(cnt_new_cli - cnt_new_cli_cur);
                pItem->SubItems->Add(dm1->Query1->FieldByName("should_com")->AsFloat);
                pItem->SubItems->Add(0.8*dm1->Query1->FieldByName("should_com")->AsFloat);
                pItem->SubItems->Add(dm1->Query1->FieldByName("date_grant")->AsString);
                pItem->SubItems->Add(dm1->Query1->FieldByName("passed")->AsString);
                pItem->SubItems->Add(dm1->Query1->FieldByName("pect_busi")->AsString);
                pItem->SubItems->Add(dm1->Query1->FieldByName("ratio")->AsString);

        	dm1->Query1->Next();
        }
        //点击具体记录是，才刷新in_detail(out_detail);

}
//---------------------------------------------------------------------------

void __fastcall TCommitionForm::lvCommitionSelectItem(TObject *Sender,
      TListItem *Item, bool Selected)
{
        if (Selected == NULL){
                return;
        }
        locateCbbByValue(cbbOpCodeSl, Item->Caption);

        locateCbbByValue(cbbRatio, Item->SubItems->Strings[10]);
        edtCntNewCli->Text = Item->SubItems->Strings[3];
        edtBusiVolume->Text = Item->SubItems->Strings[2];
        AnsiString strDate = Item->SubItems->Strings[0];
        strDate += AnsiString("-1");
        //toimp - 发放时间
        SetDateTimePicker(dtpYearMonth, strDate);
        locateCbbByValue(cbbPassed, Item->SubItems->Strings[8]);
        ResetCtrl();
}
//---------------------------------------------------------------------------

void __fastcall TCommitionForm::btnDelClick(TObject *Sender)
{
        char strMsg[256],strSQL[512];
        sprintf(strMsg,"\n  真要删除“%s - %s”的记录吗？  \n", cbbOpCodeSl->Text.c_str(), GetYearMonth(dtpYearMonth));
        if(Application->MessageBox(strMsg,"警告",MB_YESNOCANCEL | MB_ICONQUESTION | MB_DEFBUTTON2)!=IDYES)
                return;

        CString szSQL;
        szSQL.Format("delete commition where op_code_sl='%s' and year_month between '%s' and '%s'", cbbOpCodeSl->Text.c_str(), GetMonthBegin(dtpYearMonth), GetMonthEnd(dtpYearMonth));
        if(!RunSQL(dm1->Query1,szSQL))
                ShowMessage("delete fail!");
        edtDebug->Text = AnsiString(szSQL);

        //btnQueryClick(Sender);
        delLvItem(lvCommition);
        ShowMessage("删除成功");
        clearInput();
}
//---------------------------------------------------------------------------

void __fastcall TCommitionForm::btnModClick(TObject *Sender)
{
  m_enWorkState = EN_EDIT;
  ResetCtrl();        
}
//---------------------------------------------------------------------------


void TCommitionForm::ResetCtrl(){
  bool bAuth = true; //= m_nAuthor>=AUTH_FULL;
  if(m_enWorkState==EN_IDLE)
  {
    bool isSelected = (lvCommition->Selected!=NULL);
    lvCommition->Enabled = true;
    //btn
    btnAdd->Enabled = true && bAuth;
    btnMod->Enabled = isSelected && bAuth;
    btnDel->Enabled = isSelected && bAuth;
    btnOK->Enabled  = false;
    btnCancel->Enabled = false;
    //input area -> all false
    enablePlCtrl(plInput, false);
    //qry area -> true :: TODO
    enablePlCtrl(plQuery, true);
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
    lvCommition->Enabled = false;
    //input area ->true
    enablePlCtrl(plInput, true);
    //some especial
//    edtOId->Enabled = m_enWorkState==EN_ADDNEW;
    //TODO: qry area ->false
    enablePlCtrl(plQuery, false);    
  }
}









void __fastcall TCommitionForm::btnAddClick(TObject *Sender)
{
        clearInput();
        lvCommition->Clear();

        m_enWorkState = EN_ADDNEW;
        ResetCtrl();        
}
//---------------------------------------------------------------------------

void __fastcall TCommitionForm::btnCancelClick(TObject *Sender)
{
  int nState;

  nState = m_enWorkState;
  m_enWorkState = EN_IDLE;
  ResetCtrl();
  lvCommition->Selected=NULL;

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

void __fastcall TCommitionForm::btnQryYearClick(TObject *Sender)
{

      CString szSQL = "";
        szSQL = "select op_code_sl, sum(isnull(busi_volume_cur,0)) sum_gross, \
                        sum(dbo.get_cnt_new_cli(op_code_sl, year_month)) sum_cnt_new_cli_real, \
                        sum(cnt_new_cli) sum_cnt_new_cli,\
                        cast(100*isnull(sum(dbo.get_cnt_new_cli(op_code_sl, year_month)),0)/isnull(sum(cnt_new_cli),100) as decimal(9,2)) as pect_new_cli,\
                        sum(dbo.gen_should_com(busi_volume_cur, dbo.gen_new_cli_prize_yearmonth(year_month,op_code_sl), busi_volume_base, ratio) ) sum_should_com \
                        from commition \
                        where 1=1 ";
        if (g_theOperator.op_class==E_OPERATOR_TYPE_SALER){    //业务职能看到自己所属
                szSQL += "and op_code_sl="; szSQL += Str2DBString(g_theOperator.op_code);
        } else if (!cbbYearOpCodeSl->Text.IsEmpty()){
                szSQL += " and op_code_sl="; szSQL += Str2DBString(cbbYearOpCodeSl->Text.c_str());
        }
        szSQL += " and year(year_month)="; szSQL += Str2DBString(cbbQryYear->Text.c_str());
        szSQL += " group by op_code_sl order by op_code_sl";
                        ;
        edtDebug->Text = AnsiString(szSQL);
        //run
        RunSQL(szSQL, true);
        if (dm1->Query1->Eof){
                ShowMessage("记录不存在");
        }
        //clear
//        clearInput();
        lvYearCommition->Clear();

        //show
	while(!dm1->Query1->Eof)
	{
                double sum_should_com = dm1->Query1->FieldByName("sum_should_com")->AsFloat;
                TListItem *pItem = lvYearCommition->Items->Add();
                pItem->Caption = dm1->Query1->FieldByName("op_code_sl")->AsString;
                pItem->SubItems->Add(dm1->Query1->FieldByName("sum_gross")->AsString);
                pItem->SubItems->Add(sum_should_com);
                pItem->SubItems->Add(0.85*sum_should_com);
                pItem->SubItems->Add(0.15*sum_should_com);
                pItem->SubItems->Add("");
                pItem->SubItems->Add(dm1->Query1->FieldByName("sum_cnt_new_cli")->AsInteger);                
                pItem->SubItems->Add(dm1->Query1->FieldByName("sum_cnt_new_cli_real")->AsInteger);

                pItem->SubItems->Add(dm1->Query1->FieldByName("pect_new_cli")->AsInteger);
        	dm1->Query1->Next();
        }

}
//---------------------------------------------------------------------------



void __fastcall TCommitionForm::Button1Click(TObject *Sender)
{
         this->TrayIcon1->Minimize();        
}
//---------------------------------------------------------------------------

