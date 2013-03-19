//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "DicClientQry.h"
#include "DataModule.h"
#include "BaseCode.h"
#include "LdyInterface.h"
#include "common.hpp"
#include "const.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TDicClientQryForm *DicClientQryForm;
//---------------------------------------------------------------------------

__fastcall TDicClientQryForm::TDicClientQryForm(TComponent* Owner)
        : TForm(Owner), m_outsideSQL("")
{
}
//---------------------------------------------------------------------------
void __fastcall TDicClientQryForm::btnExitClick(TObject *Sender)
{
        Close();        
}
//---------------------------------------------------------------------------
void TDicClientQryForm::clearInput(){
        cbIsQryByDate->Checked = false;
	edtQryCid->Text = "";
	edtQryNameShort->Text = "";
	edtQryNameCh->Text = "";
	edtQryNameEn->Text = "";
	cbbQryClientType->Text = "";
	cbbQryOpType->Text = "";
	edtQryAddress->Text = "";
	edtQryTel->Text = "";
	edtQryFax->Text = "";
	edtQryLinkMan->Text = "";
	edtQryTelLinkMan->Text = "";
	edtQryQQ->Text = "";
	edtQryMsn->Text = "";
	edtQryEmail->Text = "";
//	edtSlName->Text = "";

	cbbQrySettlementType->Text = "";
	cbbQryReputation->Text = "";
	cbbQrySettlementCycle->Text = "";
        SetDateTimePicketNow(dtpQryDateBegin);
        SetDateTimePicketNow(dtpQryDateEnd);


}

void __fastcall TDicClientQryForm::FormShow(TObject *Sender)
{
        clearInput();
        cbbQryOpCodeSl->ItemIndex = -1;
        cbbQryOpCodeSl->Items->Add("");
        CString szSQL="";
	szSQL.Format("select * from operator where op_class='%d'", E_OPERATOR_TYPE_SALER);
	RunSQL(dm1->Query1,szSQL,true);
	while(!dm1->Query1->Eof)
	{
                cbbQryOpCodeSl->Items->Add(dm1->Query1->FieldByName("op_code")->AsString);
		dm1->Query1->Next();
        }
        //
        if (g_theOperator.op_class==E_OPERATOR_TYPE_SALER){
                cbbQryOpCodeSl->Enabled = false;
                locateCbbByValue(cbbQryOpCodeSl, g_theOperator.op_code);
        }
}
//---------------------------------------------------------------------------
void __fastcall TDicClientQryForm::btnQryClick(TObject *Sender)
{
//g_theOperator.op_class==5
        m_outsideSQL = "select * from client where 1=1 ";
        if (!edtQryCid->Text.IsEmpty()){
             m_outsideSQL += " and cid="; m_outsideSQL += Str2DBString(edtQryCid->Text.c_str());
        }
        if (!edtQryNameCh->Text.IsEmpty()){
             m_outsideSQL += " and name_ch="; m_outsideSQL += Str2DBString(edtQryNameCh->Text.c_str());
        }
        if (!edtQryNameEn->Text.IsEmpty()){
             m_outsideSQL += " and name_en="; m_outsideSQL += Str2DBString(edtQryNameEn->Text.c_str());
        }
        if (!edtQryNameShort->Text.IsEmpty()){
             m_outsideSQL += " and short_name="; m_outsideSQL += Str2DBString(edtQryNameShort->Text.c_str());
        }
        if (!cbbQryClientType->Text.IsEmpty()){
             m_outsideSQL += " and type="; m_outsideSQL += Str2DBString(cbbQryClientType->Text.c_str());
        }
        if (!edtQryAddress->Text.IsEmpty()){
             m_outsideSQL += " and address="; m_outsideSQL += Str2DBString(edtQryAddress->Text.c_str());
        }
        if (!edtQryTel->Text.IsEmpty()){
             m_outsideSQL += " and tel="; m_outsideSQL += Str2DBString(edtQryTel->Text.c_str());
        }
        if (!edtQryFax->Text.IsEmpty()){
             m_outsideSQL += " and fax="; m_outsideSQL += Str2DBString(edtQryFax->Text.c_str());
        }
        if (!edtQryLinkMan->Text.IsEmpty()){
             m_outsideSQL += " and link_man="; m_outsideSQL += Str2DBString(edtQryLinkMan->Text.c_str());
        }
        if (!edtQryTelLinkMan->Text.IsEmpty()){
             m_outsideSQL += " and tel_lk="; m_outsideSQL += Str2DBString(edtQryTelLinkMan->Text.c_str());
        }
        if (!edtQryQQ->Text.IsEmpty()){
             m_outsideSQL += " and qq_lk="; m_outsideSQL += Str2DBString(edtQryQQ->Text.c_str());
        }
        if (!edtQryMsn->Text.IsEmpty()){
             m_outsideSQL += " and msn_lk="; m_outsideSQL += Str2DBString(edtQryMsn->Text.c_str());
        }
        if (!edtQryEmail->Text.IsEmpty()){
             m_outsideSQL += " and email_lk="; m_outsideSQL += Str2DBString(edtQryEmail->Text.c_str());
        }
        if (!cbbQrySettlementType->Text.IsEmpty()){
             m_outsideSQL += " and settlement_type="; m_outsideSQL += Str2DBString(cbbQrySettlementType->Text.c_str());
        }
        if (!cbbQrySettlementCycle->Text.IsEmpty()){
             m_outsideSQL += " and settllement_cycle="; m_outsideSQL += Str2DBString(cbbQrySettlementCycle->Text.c_str());
        }
        if (!cbbQryReputation->Text.IsEmpty()){
             m_outsideSQL += " and reputation="; m_outsideSQL += Str2DBString(cbbQryReputation->Text.c_str());
        }
        if (!cbbQryOpType->Text.IsEmpty()){
             m_outsideSQL += " and optype="; m_outsideSQL += Str2DBString(cbbQryOpType->Text.c_str());
        }
        if (g_theOperator.op_class==E_OPERATOR_TYPE_SALER){
                m_outsideSQL += " and op_code_sl="; m_outsideSQL += Str2DBString(g_theOperator.op_code);
        } else if (g_theOperator.op_class==E_OPERATOR_TYPE_OPERATOR){
                m_outsideSQL += " and op_code_op="; m_outsideSQL += Str2DBString(g_theOperator.op_code);
        } else {
                if (!cbbQryOpCodeSl->Text.IsEmpty()){
                        m_outsideSQL += " and op_code_sl="; m_outsideSQL += Str2DBString(cbbQryOpCodeSl->Text.c_str());
                }
        }

        if (cbIsQryByDate->Checked){
                m_outsideSQL += " and op_date between "; m_outsideSQL += Str2DBString(GetDate(dtpQryDateBegin));
                m_outsideSQL += " and ";
                m_outsideSQL += Str2DBString(GetTimeEnd(dtpQryDateEnd));
        }

        m_outsideSQL += " order by cid";
        Close();
}
//---------------------------------------------------------------------------

