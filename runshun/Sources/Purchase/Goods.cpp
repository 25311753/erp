//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Goods.h"
#include "DataModule.h"
#include "BaseCode.h"
#include "LdyInterface.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TGoodsForm *GoodsForm;
//---------------------------------------------------------------------------
__fastcall TGoodsForm::TGoodsForm(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TGoodsForm::btnQueryClick(TObject *Sender)
{
        //init combobox list
        TListItem *pItem;
        CString szSQL;
	szSQL.Format("select * from merchandise where mname like '%%%s%%'", edtMname->Text.c_str());
	RunSQL(dm1->Query1,szSQL,true);
        lstViewGoods->Items->Clear();
	while(!dm1->Query1->Eof)
	{
                //m_lstBoatno.Add(dm1->Query1->FieldByName("bnid")->AsString.c_str());
                pItem=lstViewGoods->Items->Add();
                pItem->Caption=dm1->Query1->FieldByName("mid")->AsString;
		pItem->SubItems->Add(dm1->Query1->FieldByName("mname")->AsString);
		pItem->SubItems->Add(dm1->Query1->FieldByName("spec")->AsString);
		pItem->SubItems->Add(dm1->Query1->FieldByName("firstmeasunit")->AsString);
		pItem->SubItems->Add(dm1->Query1->FieldByName("secondmeasunit")->AsString);
     		pItem->SubItems->Add(dm1->Query1->FieldByName("unitprice")->AsString);
		dm1->Query1->Next();
	}
}
//---------------------------------------------------------------------------
void __fastcall TGoodsForm::lstViewGoodsSelectItem(TObject *Sender,
      TListItem *Item, bool Selected)
{
        m_szMid = Item->Caption;
        m_szMname  = Item->SubItems->Strings[0].c_str();
        m_szSpec = Item->SubItems->Strings[1].c_str();
        m_szFirstmeasunit = Item->SubItems->Strings[2].c_str();
        m_szSecondmeasunit = Item->SubItems->Strings[3].c_str();
        m_szUnitprice = Item->SubItems->Strings[4].c_str();
}
//---------------------------------------------------------------------------
