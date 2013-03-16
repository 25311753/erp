//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "ContainerInfo.h"
#include "DataModule.h"
#include "BaseCode.h"
#include "LdyInterface.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TContainerInfoForm *ContainerInfoForm;
//---------------------------------------------------------------------------
__fastcall TContainerInfoForm::TContainerInfoForm(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TContainerInfoForm::FormShow(TObject *Sender)
{
        edtCaseNo->Text = "";
        edtCaseCount->Text = "";
        edtContainerInfo->Text = "";
        cbbCaseType->Text = "";
}
//---------------------------------------------------------------------------

void __fastcall TContainerInfoForm::btnAppendClick(TObject *Sender)
{
        AnsiString out;

        out =edtContainerInfo->Text + (edtContainerInfo->Text.IsEmpty()?"":"-")+ edtCaseNo->Text+ "/" + edtCaseCount->Text + "*" + cbbCaseType->Text;
        edtContainerInfo->Text = out;
        m_szContainerInfo = out;
}
//---------------------------------------------------------------------------
