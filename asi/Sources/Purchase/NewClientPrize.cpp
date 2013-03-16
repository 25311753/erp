//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "NewClientPrize.h"
#include "LdyInterface.h"
#include "common.hpp"
#include "DataModule.h"
#include "BaseCode.h"
#include "const.h"
#include <assert>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "trayicon"
#pragma resource "*.dfm"
TNewClientPrizeForm *NewClientPrizeForm;

void NewClientPrize(int nAuth)
{
//  CALL_FORM(TOperationForm)
        TNewClientPrizeForm *pForm;
	try
	{
  	        pForm=new TNewClientPrizeForm(Application);
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
__fastcall TNewClientPrizeForm::TNewClientPrizeForm(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TNewClientPrizeForm::FormShow(TObject *Sender)
{
        cbbClShortName->Items->Add("");
        CString szSQL = "";
        szSQL.Format("select short_name from client");
        RunSQL(dm1->Query1,szSQL,true);
	while(!dm1->Query1->Eof)
	{
                cbbClShortName->Items->Add(dm1->Query1->FieldByName("short_name")->AsString);
                dm1->Query1->Next();
        }
}
//---------------------------------------------------------------------------
void __fastcall TNewClientPrizeForm::btnQryClick(TObject *Sender)
{
        CString szSQL = "";
        szSQL = ("select CONVERT(varchar, acceptdate, 111) acceptdate_op_date,\
                n.oid noid, \
                n.cl_shortname nshortname, \
                dbo.get_profit(o.oid) oprofit, \
                dbo.gen_new_cli_prize(dbo.get_profit(o.oid) ) nprize,\
                c.passed npassed,\
                c.date_grant ndate_grant \
                from new_cli_prize n, \
                operation o, commition c \
                where n.oid=o.oid \
                and n.cl_shortname=o.cl_shortname     \
                and o.op_code_sl=c.op_code_sl   \
                and DATEPART(yyyy,o.acceptdate)=DATEPART(yyyy,c.year_month)     \
                and DATEPART(mm,o.acceptdate)=DATEPART(mm,c.year_month) ");
        if (!cbbClShortName->Text.IsEmpty()){
                szSQL += " and o.cl_shortname="; szSQL += Str2DBString(cbbClShortName->Text.c_str());
        }
        if (cbIsQryByDate->Checked){
                CString tmp = "";
                tmp.Format(" and o.acceptdate between     \
                CONVERT(datetime,CONVERT(char(8),'%s',120)+'1') and      \
                CONVERT(char(8),DATEADD(Month,1,'%s'),120)+'1' ", GetDate(dtpQryDateBegin), GetDate(dtpQryDateEnd));
                szSQL += tmp;
        }

        szSQL += " order by o.oid";
        Edit1->Text = AnsiString(szSQL);
        RunSQL(szSQL, true);
        if (dm1->Query1->Eof){
                ShowMessage("记录不存在");
                lvNewCliPrize->Clear();
                return;
        }

        lvNewCliPrize->Clear();

	while(!dm1->Query1->Eof)
	{
                TListItem *pItem = lvNewCliPrize->Items->Add();
//                pItem->Caption = dm1->Query1->FieldByName("noid")->AsString;
                pItem->Caption = dm1->Query1->FieldByName("acceptdate_op_date")->AsString;
		pItem->SubItems->Add(dm1->Query1->FieldByName("noid")->AsString);
		pItem->SubItems->Add(dm1->Query1->FieldByName("nshortname")->AsString);
		pItem->SubItems->Add(dm1->Query1->FieldByName("oprofit")->AsString);
		pItem->SubItems->Add(dm1->Query1->FieldByName("nprize")->AsString);
		pItem->SubItems->Add(dm1->Query1->FieldByName("npassed")->AsString);
		pItem->SubItems->Add(dm1->Query1->FieldByName("ndate_grant")->AsString);

 		dm1->Query1->Next();
        }
        lbTotalNewCliCnt->Caption = lvNewCliPrize->Items->Count;
        //是否发放 - 概念整合为经理审批字段passed
        

}
//---------------------------------------------------------------------------

void __fastcall TNewClientPrizeForm::Button1Click(TObject *Sender)
{
         this->TrayIcon1->Minimize();           
}
//---------------------------------------------------------------------------

