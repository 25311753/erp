//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "XkQry.h"
#include "LdyInterface.h"
#include "common.hpp"
#include "DataModule.h"
#include "BaseCode.h"
#include "const.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TXkQryForm *XkQryForm;
void XkQry(int nAuth)
{
  CALL_FORM(TXkQryForm)
}
//---------------------------------------------------------------------------
__fastcall TXkQryForm::TXkQryForm(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TXkQryForm::FormShow(TObject *Sender)
{
        cbbQryOpCodeSl->Items->Add("");
        CString szSQL = "";
        szSQL.Format("select op_code from operator where op_class='%d'", E_OPERATOR_TYPE_SALER);
        RunSQL(dm1->Query1,szSQL,true);
	while(!dm1->Query1->Eof)
	{
                AnsiString opcode = dm1->Query1->FieldByName("op_code")->AsString;
                cbbQryOpCodeSl->Items->Add(opcode);
                dm1->Query1->Next();
        }            
}
//---------------------------------------------------------------------------
void __fastcall TXkQryForm::btnQryClick(TObject *Sender)
{
        CString szSQL = "";
        szSQL = "select op_code_sl, cast(DATEPART(yyyy,year_month) as varchar) + '-' + cast(DATEPART(mm,year_month) as varchar) as ym ,  \
dbo.get_cnt_new_cli(op_code_sl, year_month) cnt_new_cli_cur,cnt_new_cli \
                        from commition where 1=1 ";
        if (g_theOperator.op_class==E_OPERATOR_TYPE_SALER){    //业务职能看到自己所属
                szSQL += "and op_code_sl="; szSQL += Str2DBString(g_theOperator.op_code);
        } else if (!cbbQryOpCodeSl->Text.IsEmpty()){           //其他不受限制
                szSQL += "and op_code_sl="; szSQL += Str2DBString(cbbQryOpCodeSl->Text.c_str());
        }
        if (!cbYear->Text.IsEmpty()) {
                szSQL += " and year(year_month)="; szSQL += cbYear->Text.c_str();
        }
        if (!cbQ->Text.IsEmpty()) {
                CString month="";
                if (cbQ->Text=="Q1"){
                        month = "1,2,3";
                }else if (cbQ->Text=="Q2"){
                        month = "4,5,6";
                }else if (cbQ->Text=="Q3"){
                        month = "7,8,9";
                }else if (cbQ->Text=="Q4"){
                        month = "10,11,12";
                }
                szSQL += " and month(year_month) in ("; szSQL += month; szSQL+=")";
        }
        //如选具体月份，可覆盖季度条件
        if (!cbMonth->Text.IsEmpty()){
                szSQL += " and month(year_month)="; szSQL += cbMonth->Text.c_str();
        }

        szSQL += " order by op_code_sl, year_month";
//        edtDebug->Text = AnsiString(szSQL);
        //run
        RunSQL(dm1->Query1, szSQL, true);
        if (dm1->Query1->Eof){
                ShowMessage("记录不存在");
        }

        lvQry->Clear();

        //show
	while(!dm1->Query1->Eof)
	{
                TListItem *pItem = lvQry->Items->Add();
                pItem->Caption = dm1->Query1->FieldByName("op_code_sl")->AsString;
                pItem->SubItems->Add(dm1->Query1->FieldByName("ym")->AsString);

                int cnt_new_cli = dm1->Query1->FieldByName("cnt_new_cli")->AsInteger;
                int cnt_new_cli_cur = dm1->Query1->FieldByName("cnt_new_cli_cur")->AsInteger;
                int remain = cnt_new_cli>=cnt_new_cli_cur?cnt_new_cli-cnt_new_cli_cur:0;
                pItem->SubItems->Add(cnt_new_cli_cur);
                pItem->SubItems->Add(cnt_new_cli);

                pItem->SubItems->Add(cnt_new_cli_cur>=cnt_new_cli?"是":"否");
                pItem->SubItems->Add(remain);
                pItem->SubItems->Add(remain==0?0:100*remain/cnt_new_cli);
        	dm1->Query1->Next();
        }
}
//---------------------------------------------------------------------------
