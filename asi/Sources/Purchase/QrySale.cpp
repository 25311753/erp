//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "Commition.h"
#include "LdyInterface.h"
#include "common.hpp"
#include "DataModule.h"
#include "BaseCode.h"
#include "const.h"
#include "QrySale.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "trayicon"
#pragma resource "*.dfm"
TQrySaleForm *QrySaleForm;
void QrySale(int nAuth)
{
  CALL_FORM(TQrySaleForm)
}
//---------------------------------------------------------------------------
__fastcall TQrySaleForm::TQrySaleForm(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TQrySaleForm::FormShow(TObject *Sender)
{
        CString szSQL = "";
        //cl_short_name
        szSQL = "select short_name from client where 1=1 ";
        if (g_theOperator.op_class==E_OPERATOR_TYPE_SALER){   
                szSQL += " and op_code_sl="; szSQL += Str2DBString(g_theOperator.op_code);
        }
        RunSQL(szSQL,true);
        cbbClShortName->Items->Add("");
	while(!dm1->Query1->Eof)
	{
                cbbClShortName->Items->Add(dm1->Query1->FieldByName("short_name")->AsString);
                dm1->Query1->Next();
        }
        //
}
//---------------------------------------------------------------------------
void __fastcall TQrySaleForm::btnQryYearClick(TObject *Sender)
{
        CString szSQL = "";
        /////////////////////////////////////////////////////////////////////////////////////////////
        //业绩查询
        szSQL = "select op_code_sl, isnull(busi_volume_cur,0) gross, \
                        dbo.gen_should_com(busi_volume_cur, dbo.gen_new_cli_prize_yearmonth(year_month,op_code_sl), busi_volume_base, ratio) should_com, \
                        cast(100*(1-isnull(busi_volume_cur,0)/isnull(busi_volume_base,100)) as decimal(9,2)) as pect_busi,  \
                        case sign(busi_volume_base-busi_volume_cur)           \
                                when 1 then (busi_volume_base-busi_volume_cur)\
                                else 0 end as last_busi,\
                        *\
                        from commition \
                        where 1=1 ";
        if (g_theOperator.op_class==E_OPERATOR_TYPE_SALER){
                szSQL += " and op_code_sl="; szSQL += Str2DBString(g_theOperator.op_code);
        }
        if (!cbbYear->Text.IsEmpty()){
                szSQL += " and year(year_month)="; szSQL += Str2DBString(cbbYear->Text.c_str());
        }
        if (!cbbMonth->Text.IsEmpty()){
                szSQL += " and month(year_month)="; szSQL += Str2DBString(cbbMonth->Text.c_str());
        }
        szSQL += "order by year_month, op_code_sl";
        Edit1->Text = AnsiString(szSQL);
        //run
        RunSQL(szSQL, true);
        if (dm1->Query1->Eof){
                ShowMessage("记录不存在");
        }

        lvTask->Clear();

        //show
        double sum_should_com = 0;
	while(!dm1->Query1->Eof)
	{
                TListItem *pItem = lvTask->Items->Add();
                double should_com = dm1->Query1->FieldByName("should_com")->AsFloat;
                sum_should_com += should_com;
                pItem->Caption = dm1->Query1->FieldByName("op_code_sl")->AsString;
                pItem->SubItems->Add(dm1->Query1->FieldByName("gross")->AsString);
                pItem->SubItems->Add(should_com);
                pItem->SubItems->Add(0.85*should_com);
                pItem->SubItems->Add(0.15*should_com);
                pItem->SubItems->Add(dm1->Query1->FieldByName("passed")->AsString);
                pItem->SubItems->Add(dm1->Query1->FieldByName("busi_volume_cur")->AsString);
                pItem->SubItems->Add(dm1->Query1->FieldByName("last_busi")->AsString);
                double last_busi = dm1->Query1->FieldByName("pect_busi")->AsFloat;
                last_busi = last_busi<0?0:last_busi;
                pItem->SubItems->Add(last_busi);

        	dm1->Query1->Next();
        }
        lbTotalPrize->Caption =  0.85*sum_should_com;
        /////////////////////////////////////////////////////////////////////////////////////////////
        //回扣查询
        szSQL = "select *, \
                CONVERT(varchar, acceptdate, 111) as date_accept, \
                case year(date) when 2099 then '-' else CONVERT(varchar, date, 111) end as date_kb \
                from detail_kb, operation \
                where dkoid=oid ";
        if (g_theOperator.op_class==E_OPERATOR_TYPE_SALER){   
                szSQL += " and op_code_sl="; szSQL += Str2DBString(g_theOperator.op_code);
        }
        if (!cbbClShortName->Text.IsEmpty()){
                szSQL += " and cl_shortname="; szSQL += Str2DBString(cbbClShortName->Text.c_str());
        }
        if (!cbbYear->Text.IsEmpty()){
                szSQL += " and year(acceptdate)="; szSQL += Str2DBString(cbbYear->Text.c_str());
        }
        if (!cbbMonth->Text.IsEmpty()){
                szSQL += " and month(acceptdate)="; szSQL += Str2DBString(cbbMonth->Text.c_str());
        }

        RunSQL(szSQL, true);
        if (dm1->Query1->Eof){
                ShowMessage("回扣记录不存在");
        }
        lvKB->Clear();
	while(!dm1->Query1->Eof)
	{
                TListItem *pItem = lvKB->Items->Add();
                pItem->Caption = dm1->Query1->FieldByName("oid")->AsString;
                pItem->SubItems->Add(dm1->Query1->FieldByName("date_accept")->AsString);
                pItem->SubItems->Add(dm1->Query1->FieldByName("cl_shortname")->AsString);
                pItem->SubItems->Add(dm1->Query1->FieldByName("kb_value")->AsFloat);
                pItem->SubItems->Add(dm1->Query1->FieldByName("date_kb")->AsString);

        	dm1->Query1->Next();
        }

}
//---------------------------------------------------------------------------

void __fastcall TQrySaleForm::Button1Click(TObject *Sender)
{
         this->TrayIcon1->Minimize();                  
}
//---------------------------------------------------------------------------

