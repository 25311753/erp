#ifndef  _common_util_asi_
#define  _common_util_asi_

#include <vcl.h>
#include "DataModule.h"
#include "LdyInterface.h"
#include "BaseCode.h"

void flushFinanceDetail(const AnsiString OId, TListView *lvIn, TListView *lvOut){
        lvIn->Clear();
        lvOut->Clear();
        CString szSQL = "";
        //in
        szSQL.Format("select name, cnt, way_calc \
                        from detail_in, dic_in_type \
                        where diid like '%s__' and cast(substring(diid, len(diid)-1,2) as int)  = itid", \
                        OId);
        RunSQL(szSQL, true);
        while (!dm1->Query1->Eof){
                TListItem *pItem = lvIn->Items->Add();
                if (pItem==NULL){
                        return;
                }
                pItem->Caption = dm1->Query1->FieldByName("name")->AsString;
        	pItem->SubItems->Add(dm1->Query1->FieldByName("cnt")->AsString);
                pItem->SubItems->Add(dm1->Query1->FieldByName("way_calc")->AsString);
                dm1->Query1->Next();
        }
        //out
        szSQL.Format("select name, cnt, spid, way_calc \
                        from detail_out, dic_out_type \
                        where doid like '%s__' and cast(substring(doid, len(doid)-1,2) as int)  = otid", \
                        OId);
        RunSQL(szSQL, true);
        while (!dm1->Query1->Eof){
                TListItem *pItem = lvOut->Items->Add();
                if (pItem==NULL){
                        return;
                }
                pItem->Caption = dm1->Query1->FieldByName("name")->AsString;
        	pItem->SubItems->Add(dm1->Query1->FieldByName("cnt")->AsString);
                pItem->SubItems->Add(dm1->Query1->FieldByName("spid")->AsString);
                pItem->SubItems->Add(dm1->Query1->FieldByName("way_calc")->AsString);
                dm1->Query1->Next();
        }
}

#endif
