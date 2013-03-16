//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "operpwdunit.h"
#include "DataModule.h"
#include "TConst.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
Toperpwdform *operpwdform;
//---------------------------------------------------------------------------
__fastcall Toperpwdform::Toperpwdform(TComponent* Owner)
   : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall Toperpwdform::FormShow(TObject *Sender)
{
        Panel6->Font->Color = clScrollBar;
Panel7->Font->Color = clScrollBar;

//    Panel6->Enabled =false;
//    Panel7->Enabled =false;
    newpwd1->Enabled =false;
    newpwd2->Enabled =false;
    Bok->Enabled =true;
    Bmodify->Enabled =false;
    eoper->Text=operatorcode;
    oldpwd->Clear();
    newpwd1->Clear();
    newpwd2->Clear();
}
//---------------------------------------------------------------------------

void __fastcall Toperpwdform::oldpwdKeyPress(TObject *Sender, char &Key)
{
    if (Key==13) //enter key been pressed
    {
        Key=0;
        BokClick(Sender);
    }
}
//---------------------------------------------------------------------------

void __fastcall Toperpwdform::newpwd1KeyPress(TObject *Sender, char &Key)
{
    if (Key==13) //enter key been pressed
    {
        Key=0;
        SelectNext(ActiveControl,true,true);
    }
}
//---------------------------------------------------------------------------

void __fastcall Toperpwdform::newpwd2KeyPress(TObject *Sender, char &Key)
{
    if (Key==13) //enter key been pressed
    {
        Key=0;
        BmodifyClick(Sender);
    }
}
//---------------------------------------------------------------------------

void __fastcall Toperpwdform::BokClick(TObject *Sender)
{
     AnsiString  password;
     int i;
     char *pbuf, buff[7];

     dm1->Query1->DisableControls();
     try
     {
       dm1->Query1->Close();
       dm1->Query1->SQL->Clear();
       dm1->Query1->SQL->Add("select * from operator where op_code=:oper and op_password=:pass");
       dm1->Query1->Params->Items[0]->AsString=Trim(eoper->Text);
       pbuf=&buff[0];
       strcpy(pbuf,(oldpwd->Text).c_str());
       for (int i=0; i<(oldpwd->Text).Length();i++)     //口令加密
           password=password+Char(buff[i]^73+9);

       dm1->Query1->Params->Items[1]->AsString=password;
       dm1->Query1->Open();
       if (dm1->Query1->RecordCount>0)
       {
        //  Panel6->Enabled =true;
         // Panel7->Enabled =true;
        Panel6->Font->Color = clWindowText;
Panel7->Font->Color = clWindowText;
          newpwd1->Enabled =true;
          newpwd1->SetFocus();
          newpwd2->Enabled =true;
          Bmodify->Enabled =true;
          Bok->Enabled =false;
          oldpwd->Enabled =false;
       }
       else
       {
           Application->MessageBox("工号或密码错误！","系统信息",MB_OK);
       }
     }
     catch(...)
     {
        dm1->Query1->EnableControls();
     }
     dm1->Query1->Close();
}
//---------------------------------------------------------------------------

void __fastcall Toperpwdform::BmodifyClick(TObject *Sender)
{
    if (newpwd1->Text=="")
    {
        ShowMessage("请输入新密码！");
        newpwd1->SetFocus();
        return;
    }
    if (newpwd2->Text=="")
    {
        ShowMessage("请确认新密码！");
        newpwd2->SetFocus();
        return;
    }
    if (newpwd1->Text != newpwd2->Text)
    {
       ShowMessage("密码输入不一致，请重新输入！");
       newpwd1->Text="";
       newpwd2->Text="";
       newpwd1->SetFocus();
       return;
    }

    AnsiString  password;
    int i;
    char *pbuf, buff[7];
    pbuf=&buff[0];
    strcpy(pbuf,(newpwd2->Text).c_str());
    for (int i=0; i<(newpwd2->Text).Length();i++)     //口令加密
        password=password+Char(buff[i]^73+9);

    TLocateOptions Opts;
    Opts.Clear();
    Opts <<loCaseInsensitive;
    dm1->OperTab->Close();
    try
    {
       dm1->OperTab->Open();
    }
    catch(...)
    {
       Application->MessageBox("打开表失败!","错误",MB_OK+MB_ICONINFORMATION);
       return;
    }
    dm1->OperTab->First();
    if (dm1->OperTab->Locate("op_code",Trim(eoper->Text),Opts))
    {
       dm1->OperTab->Edit();
       dm1->OperTab->FieldByName("op_password")->AsString=password;
       dm1->OperTab->Post();
       dm1->OperTab->Refresh();
       Application->MessageBox("密码修改成功！下次登录请使用新密码","系统信息",MB_OK+MB_ICONINFORMATION);
    }
    else
    {
       Application->MessageBox("密码修改不成功！","系统信息",MB_OK);
       dm1->OperTab->Close();
    }
    Bok->Enabled =true;
    oldpwd->Enabled = true;
    oldpwd->Text=newpwd1->Text;
    oldpwd->SetFocus();
    Bmodify->Enabled = false;
//    Panel6->Enabled =false;
//    Panel7->Enabled =false;
        Panel6->Font->Color = clScrollBar;
Panel7->Font->Color = clScrollBar;

    newpwd1->Enabled =false;
    newpwd2->Enabled =false;
    newpwd1->Clear();
    newpwd2->Clear();
}
//---------------------------------------------------------------------------

void __fastcall Toperpwdform::BexitClick(TObject *Sender)
{
    Close();
}
//---------------------------------------------------------------------------

void __fastcall Toperpwdform::FormClose(TObject *Sender,
      TCloseAction &Action)
{
    oldpwd->Enabled =true;
    Bok->Enabled =true;
    dm1->Query1->Close();
    dm1->OperTab->Close();
    dm1->db1->Connected=false;
}
//---------------------------------------------------------------------------

