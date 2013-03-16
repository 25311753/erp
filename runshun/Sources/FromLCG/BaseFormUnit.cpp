//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "BaseFormUnit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TBaseForm *BaseForm;
//---------------------------------------------------------------------------

__fastcall TBaseForm::TBaseForm(TComponent* Owner)
   : TForm(Owner)
{
}
//---------------------------------------------------------------------------

bool  TBaseForm::CheckEdit()
{
   edtcode->Text=Trim(edtcode->Text);
   if (edtcode->Text=="")
   {
       Application->MessageBox("请输入代码!","系统提示",MB_OK+MB_ICONINFORMATION);
       edtcode->SetFocus();
       return false;
   }

   edtname->Text=Trim(edtname->Text);
   if (edtname->Text=="")
   {
       Application->MessageBox("请输入名称!","系统提示",MB_OK+MB_ICONINFORMATION);
       edtname->SetFocus();
       return false;
   }
   return true;
}
//---------------------------------------------------------------------------

void  TBaseForm::ClearEdit()
{
    edtcode->Text="";
    edtname->Text="";
}
//---------------------------------------------------------------------------

void  TBaseForm::SetDefault()
{
    edtcode->Enabled=false;
    edtname->Enabled=false;
    btnidx=5;
    SetButton(1,1,1,1,0,0,1,1);
    PanelHint->Caption="";
    ClearEdit();
}
//---------------------------------------------------------------------------

void  TBaseForm::SetButton(bool v0, bool v1, bool v2, bool v3, bool v4, bool v5, bool v6, bool v7)
{
   btnadd->Enabled=v0;
   btnfind->Enabled=v1;
   btnmod->Enabled=v2;
   btndel->Enabled=v3;
   btnok->Enabled=v4;
   btncan->Enabled=v5;
   btnprint->Enabled=v6;
   btnref->Enabled=v7;
}
//---------------------------------------------------------------------------

void __fastcall TBaseForm::FormShortCut(TWMKey &Msg, bool &Handled)
{
    switch(Msg.CharCode)
    {
       case VK_F1:
            if (btnadd->Enabled)
               btnadd->Click();
            Handled=true;
            break;
       case VK_F2:
            if (btnfind->Enabled)
               btnfind->Click();
            Handled=true;
            break;
       case VK_F3:
            if (btnmod->Enabled)
               btnmod->Click();
            Handled=true;
            break;
       case VK_F4:
            if (btndel->Enabled)
               btndel->Click();
            Handled=true;
            break;
       case VK_F5:
            if (btnok->Enabled)
               btnok->Click();
            Handled=true;
            break;
       case VK_F6:
            if (btncan->Enabled)
               btncan->Click();
            Handled=true;
            break;
       case VK_F7:
            if (btnprint->Enabled)
               btnprint->Click();
            Handled=true;
            break;
       case VK_F9:
            if (btnref->Enabled)
               btnref->Click();
            Handled=true;
            break;
       case VK_ESCAPE:
            if (btnexit->Enabled)
               btnexit->Click();
            Handled=true;
            break;
    }
}
//---------------------------------------------------------------------------

void __fastcall TBaseForm::btnaddClick(TObject *Sender)
{
    btnidx=0;
    SetButton(0,0,0,0,1,1,0,0);
    ClearEdit();
    edtcode->Enabled=true;
    edtname->Enabled=true;
    edtcode->SetFocus();
    PanelHint->Caption=" 请输入数据";
}
//---------------------------------------------------------------------------

void __fastcall TBaseForm::btnmodClick(TObject *Sender)
{
    btnidx=2;
    edtcode->Enabled=false;
    edtname->Enabled=true;
    SetButton(0,0,0,0,1,1,0,0);
    PanelHint->Caption=" 请在列表中选择要修改的项次";
}
//---------------------------------------------------------------------------

void __fastcall TBaseForm::btndelClick(TObject *Sender)
{
    btnidx=3;
    SetButton(0,0,0,0,1,1,0,0);
    PanelHint->Caption=" 请在列表中选择要删除的项次";
}
//---------------------------------------------------------------------------

void __fastcall TBaseForm::btncanClick(TObject *Sender)
{
    SetDefault();
}
//---------------------------------------------------------------------------

void __fastcall TBaseForm::btnexitClick(TObject *Sender)
{
    Close();
}
//---------------------------------------------------------------------------

void __fastcall TBaseForm::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
   if (Key==13)
   {
      //Key=0;
      SelectNext(ActiveControl,true,true);
   }
}
//---------------------------------------------------------------------------

void __fastcall TBaseForm::btnfindClick(TObject *Sender)
{
    btnidx=1;
    edtcode->Enabled=true;
    edtname->Enabled=true;
    edtcode->SetFocus();
    SetButton(0,0,0,0,1,1,0,0);
    PanelHint->Caption=" 请在框里输入代码或名称";
}
//---------------------------------------------------------------------------


