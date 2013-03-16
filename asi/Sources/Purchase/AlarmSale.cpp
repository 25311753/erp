//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Commition.h"
#include "LdyInterface.h"
#include "common.hpp"
#include "DataModule.h"
#include "BaseCode.h"
#include "const.h"
#include "AlarmSale.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TAlarmSaleForm *AlarmSaleForm;
//---------------------------------------------------------------------------
void AlarmSale(int nAuth)
{
  CALL_FORM(TAlarmSaleForm)
}
__fastcall TAlarmSaleForm::TAlarmSaleForm(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TAlarmSaleForm::FormShow(TObject *Sender)
{

        lvArrival->Clear();
        lvDelay->Clear();
        lvTask->Clear();
        
        CString szSQL = "";
        ///////////////////////////////////////////////////////////////////////
        //δ����
        szSQL += "select oid, acceptdate, cl_shortname from operation where is_arrival=0 and "  ;
        if (m_iOpType==E_OPERATOR_TYPE_SALER){
                szSQL += " op_code_sl="; szSQL += Str2DBString(g_theOperator.op_code);
                Caption = "��½��ʾ - ҵ��Ա";                
        } else if (m_iOpType==E_OPERATOR_TYPE_OPERATOR){
                szSQL += " op_code_op="; szSQL += Str2DBString(g_theOperator.op_code);
                //����ʾҵ��澯��Ϣ���������ڴ�С
                Caption = "��½��ʾ - ����Ա";
                lvDelay->Visible = false;
                lvTask->Visible  = false;
                Height=300;
        } else{
                return;     //ҵ�񡢲�����û�����ʾ
        }

        RunSQL(szSQL, true);

	while(!dm1->Query1->Eof)
	{
                TListItem *pItem = lvArrival->Items->Add();
                pItem->Caption = dm1->Query1->FieldByName("oid")->AsString;
                pItem->SubItems->Add(dm1->Query1->FieldByName("acceptdate")->AsString);
                pItem->SubItems->Add(dm1->Query1->FieldByName("cl_shortname")->AsString);

        	dm1->Query1->Next();                
        }
        if (m_iOpType==E_OPERATOR_TYPE_OPERATOR){
                return;                         //�����Ļ�������Ϊֹ
        }
        ///////////////////////////////////////////////////////////////////////
        //������������
        szSQL.Format("select oid, acceptdate, cl_shortname, c.settlement_cycle, in_date \
                        from operation o, client c, rec_in i \
                        where o.op_code_sl='%s' and o.oid=i.rioid and o.cl_shortname=c.short_name and \
                        dbo.just_isdelay(c.settlement_cycle,i.in_date,o.acceptdate)=1", g_theOperator.op_code);
        RunSQL(szSQL, true);

	while(!dm1->Query1->Eof)
	{
                TListItem *pItem = lvDelay->Items->Add();
                pItem->Caption = dm1->Query1->FieldByName("oid")->AsString;
                pItem->SubItems->Add(dm1->Query1->FieldByName("acceptdate")->AsString);
                pItem->SubItems->Add(dm1->Query1->FieldByName("cl_shortname")->AsString);
                pItem->SubItems->Add(dm1->Query1->FieldByName("settlement_cycle")->AsString);
                pItem->SubItems->Add(dm1->Query1->FieldByName("in_date")->AsString);

        	dm1->Query1->Next();
        }
        ///////////////////////////////////////////////////////////////////////
        //ʣ������ʣ���¿���
        szSQL.Format("select dbo.gen_year_month(year_month) as yeas_month,\
                        dbo.gen_positive(busi_volume_base-busi_volume_cur) as busi,\
                        dbo.gen_positive(cnt_new_cli-dbo.get_cnt_new_cli(op_code_sl, year_month)) as client \
                        from commition \
                        where op_code_sl='%s'", g_theOperator.op_code);
        RunSQL(szSQL, true);

	while(!dm1->Query1->Eof)
	{
                TListItem *pItem = lvTask->Items->Add();
                pItem->Caption = dm1->Query1->FieldByName("yeas_month")->AsString;
                pItem->SubItems->Add(dm1->Query1->FieldByName("busi")->AsString);
                pItem->SubItems->Add(dm1->Query1->FieldByName("client")->AsString);

        	dm1->Query1->Next();
        }



}
//---------------------------------------------------------------------------


