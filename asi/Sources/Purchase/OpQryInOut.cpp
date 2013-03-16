//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "OpQryInOut.h"

#include "LdyInterface.h"
#include "common.hpp"
#include "DataModule.h"
#include "BaseCode.h"
#include "const.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TOpQryInOutForm *OpQryInOutForm;
//---------------------------------------------------------------------------
__fastcall TOpQryInOutForm::TOpQryInOutForm(TComponent* Owner)
        : TForm(Owner)
{
}
void TOpQryInOutForm::show(AnsiString oid){
        CString szSQL = "";
       
        szSQL.Format("select name, \
                        cnt, unitprice, unit\
                        from detail_in, dic_in_type \
                        where diid like '%s__' and cast(substring(diid, len(diid)-1,2) as int)  = itid", oid);
        RunSQL(dm1->Query1, szSQL, true);

        lvInDetail->Clear();
        while (!dm1->Query1->Eof){
                TListItem *pItem = lvInDetail->Items->Add();
                if (pItem==NULL){
                        return;
                }
                pItem->Caption = dm1->Query1->FieldByName("name")->AsString;
        	pItem->SubItems->Add(dm1->Query1->FieldByName("cnt")->AsString);
        	pItem->SubItems->Add(dm1->Query1->FieldByName("unitprice")->AsString);
//                pItem->SubItems->Add(dm1->Query1->FieldByName("way_calc")->AsString);
                pItem->SubItems->Add(dm1->Query1->FieldByName("unit")->AsString);
                float total = StrToFloat(dm1->Query1->FieldByName("cnt")->AsString)*StrToFloat(dm1->Query1->FieldByName("unitprice")->AsString);
                pItem->SubItems->Add(total);
                dm1->Query1->Next();
        }
//        lbSumIn->Caption = genSumMomey(lvInDetail, D_IN_MONEY_COLUMN);
        //out
        szSQL.Format("select name, \
                        cnt, \
                        unitprice, \
                        spid, \
                        unit \
                        from detail_out, dic_out_type where doid like '%s__' and cast(substring(doid, len(doid)-1,2) as int)  = otid", oid);
        RunSQL(dm1->Query1, szSQL, true);

        lvOutDetail->Clear();
        while (!dm1->Query1->Eof){
                TListItem *pItem = lvOutDetail->Items->Add();
                if (pItem==NULL){
                        return;
                }
                pItem->Caption = dm1->Query1->FieldByName("name")->AsString;
        	pItem->SubItems->Add(dm1->Query1->FieldByName("cnt")->AsString);
        	pItem->SubItems->Add(dm1->Query1->FieldByName("unitprice")->AsString);                
                AnsiString spid = (g_theOperator.op_class==E_OPERATOR_TYPE_SALER)?AnsiString(""):dm1->Query1->FieldByName("spid")->AsString;//业务员不能看 《应付账单-供应商》
                pItem->SubItems->Add(spid);
                pItem->SubItems->Add(dm1->Query1->FieldByName("unit")->AsString);
                float total = StrToFloat(dm1->Query1->FieldByName("cnt")->AsString)*StrToFloat(dm1->Query1->FieldByName("unitprice")->AsString);
                pItem->SubItems->Add(total);
                dm1->Query1->Next();
        }                                     
//        lbSumOut->Caption = genSumMomey(lvOutDetail, D_OUT_MONEY_COLUMN);
}
//---------------------------------------------------------------------------
