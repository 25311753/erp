//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "YjQry.h"

#include "LdyInterface.h"
#include "common.hpp"
#include "DataModule.h"
#include "BaseCode.h"
#include "const.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TYjQryForm *YjQryForm;
void YjQry(int nAuth)
{
  CALL_FORM(TYjQryForm)
}
//---------------------------------------------------------------------------
__fastcall TYjQryForm::TYjQryForm(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TYjQryForm::btnQryClick(TObject *Sender)
{
        CString szSQL = "";
        szSQL = "select op_code_sl, cast(DATEPART(yyyy,year_month) as varchar) + '-' + cast(DATEPART(mm,year_month) as varchar) as ym , \
                        busi_volume_cur,busi_volume_base \
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
                pItem->SubItems->Add(dm1->Query1->FieldByName("busi_volume_cur")->AsString);
                pItem->SubItems->Add(dm1->Query1->FieldByName("busi_volume_base")->AsString);

                double cur = dm1->Query1->FieldByName("busi_volume_cur")->AsFloat;
                double base = dm1->Query1->FieldByName("busi_volume_base")->AsFloat;
                int pect_done = base==0?0:100*cur/base;
                pItem->SubItems->Add(cur>=base?"是":"否");
                pItem->SubItems->Add(pect_done);
                pItem->SubItems->Add("xxx");
                pItem->SubItems->Add(cur>=base?0:base-cur);
                pItem->SubItems->Add(cur>=base?0:(base==0?0:100-pect_done));

        	dm1->Query1->Next();
        }
}
//---------------------------------------------------------------------------
void __fastcall TYjQryForm::FormShow(TObject *Sender)
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

