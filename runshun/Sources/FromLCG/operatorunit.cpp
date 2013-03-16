//---------------------------------------------------------------------------

#include <vcl.h>
#include <stdio.h>
#include <string.h>
#pragma hdrstop
#include "operatorunit.h"
#include "DataModule.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
Toperatorform *operatorform;
//---------------------------------------------------------------------------
__fastcall Toperatorform::Toperatorform(TComponent* Owner)
   : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void  Toperatorform::SetDBedit(bool btnvalue)
{
   dbedoptcode->Enabled=btnvalue;
   dbedoptname->Enabled=btnvalue;
   dbedpassword->Enabled=btnvalue;
   dbecorp->Enabled=btnvalue;
   confirmpass->Enabled=btnvalue;
   cmbclass->Enabled=btnvalue;
}
//---------------------------------------------------------------------------

void  Toperatorform::SetButton(bool btnstate)
{
   btnclose->Enabled=btnstate;
   btnadd->Enabled=btnstate;
   btndelete->Enabled=btnstate;
   btnedit->Enabled=btnstate;
   btnprior->Enabled=btnstate;
   btnnext->Enabled=btnstate;
   btnlast->Enabled=btnstate;
   btnfirst->Enabled=btnstate;
   btnquery->Enabled=btnstate;
   btnsave->Enabled=!btnstate;
   btncancel->Enabled=!btnstate;
}
//---------------------------------------------------------------------------

void __fastcall Toperatorform::FormShow(TObject *Sender)
{
   if (dm1->ConnectDB())
   {
      sclass = new TStringList;
      sclass->Clear();
      try
      {
         dm1->Query1->Close();
         dm1->Query1->SQL->Clear();
         dm1->Query1->SQL->Add("select * from operclass");
         dm1->Query1->Prepare();
         dm1->Query1->Open();
         dm1->Query1->First();
         cmbclass->Items->Clear();
         while(!dm1->Query1->Eof)
         {
             sclass->Add(dm1->Query1->Fields->Fields[0]->AsString);
             cmbclass->Items->Add(dm1->Query1->Fields->Fields[1]->AsString);
             dm1->Query1->Next();
         }
         dm1->Query1->Close();
         dm1->OperTab->Open();
         btnfirstClick(Sender);
      }
      catch(...)
      {
         Application->MessageBox("打开表失败,不能运行!","错误",MB_OK+MB_ICONERROR);
         SetButton(false);
         btnsave->Enabled=false;
         btncancel->Enabled=false;
         btnclose->Enabled=true;
         SetDBedit(false);
      }
   }
}
//---------------------------------------------------------------------------

void __fastcall Toperatorform::btnaddClick(TObject *Sender)
{
   SetButton(false);
   SetDBedit(true);
   dbedpassword->Text="";
   confirmpass->Text="";
   dm1->DSOper->Enabled = true;
   dm1->OperTab->Append();
   dbedoptcode->Enabled=true;
   dbedoptcode->SetFocus();
}
//---------------------------------------------------------------------------

void __fastcall Toperatorform::btneditClick(TObject *Sender)
{
   SetButton(false);
   SetDBedit(true);
   dm1->DSOper->Enabled = true;
   dm1->OperTab->Edit();
   dbedoptcode->Enabled=false;
}
//---------------------------------------------------------------------------

void __fastcall Toperatorform::btndeleteClick(TObject *Sender)
{
    if (dbedoptcode->Text=="root")
    {
       Application->MessageBox("不能删除这条总管理员纪录!","错误",MB_OK+MB_ICONERROR);
       return;
    }
    if (dm1->OperTab->RecordCount >0)
    {
       if (Application->MessageBox("真的想删除这条记录吗?","系统信息",MB_YESNO) == IDYES)
       {
          dm1->OperTab->Delete();
          if (dm1->OperTab->RecordCount <=0) btndelete->Enabled = false;
       }
    }
}
//---------------------------------------------------------------------------

AnsiString  Toperatorform::DecodePwd()
{
   AnsiString  password="";
   char *pbuf, buff[7];
   pbuf=&buff[0];
   strcpy(pbuf,(dbepwd->Text).c_str());
   for (int i=0; i<(dbepwd->Text).Length();i++)     //口令解密
      password=password+Char(buff[i]^73+9);
   return password;
}
//---------------------------------------------------------------------------

void __fastcall Toperatorform::btnsaveClick(TObject *Sender)
{
   dbedoptcode->Text=Trim(dbedoptcode->Text);
   dbedoptname->Text=Trim(dbedoptname->Text);
   if (dbedoptcode->Text=="")
   {
      Application->MessageBox("操作员工号不能为空!","系统信息",MB_OK);
      dbedoptcode->SetFocus();
      return;
   }
   if (dbedoptname->Text=="")
   {
      Application->MessageBox("操作员姓名不能为空!","系统信息",MB_OK);
      dbedoptname->SetFocus();
      return;
   }
   if (dbedpassword->Text=="")
   {
      Application->MessageBox("密码不能为空!","系统信息",MB_OK);
      dbedpassword->SetFocus();
      return;
   }
   if (dbedpassword->Text!= confirmpass->Text)
   {
      Application->MessageBox ("您输入的密码不一致，请重输！","系统信息",MB_OK);
      confirmpass->SetFocus();
      return;
   }
   else
   {
      AnsiString  password="";
      char *pbuf, buff[7];
      pbuf=&buff[0];
      strcpy(pbuf,(confirmpass->Text).c_str());
      for (int i=0; i<(confirmpass->Text).Length();i++)     //口令加密
        password=password+Char(buff[i]^73+9);
      dm1->OperTab->FieldByName("op_password")->AsString=password ;
   }
   if (cmbclass->Text=="")
   {
      Application->MessageBox("级别不能为空!","系统信息",MB_OK);
      cmbclass->SetFocus();
      return;
   }
   else
      dm1->OperTab->FieldByName("op_class")->AsInteger=StrToInt(sclass->Strings[cmbclass->ItemIndex]);

   if (dm1->OperTab->State == dsInsert)
   {
      dm1->Query1->Close();
      dm1->Query1->SQL->Clear();
      dm1->Query1->SQL->Add(" select * from operator where op_code = :code");
      dm1->Query1->ParamByName("code")->AsString = Trim(dbedoptcode->Text);
      dm1->Query1->Prepare();
      dm1->Query1->Open();
      if (! dm1->Query1->IsEmpty())
      {
         Application->MessageBox("该操作员工号已存在,请输入另外一个!", "系统信息", MB_OK);
         dm1->Query1->Close();
         return;
      }
   }
   if (dm1->OperTab->State == dsEdit)
   {
      if ((dbedoptcode->Text=="root")&&(cmbclass->Text!="总管理员"))
      {
         Application->MessageBox("不能修改root的管理员等级!", "错误", MB_OK+MB_ICONERROR);
         cmbclass->SetFocus();
         return;
      }
   }

   //Save record
   dm1->OperTab->DisableControls();
   try
   {
      dm1->OperTab->Post();
      dm1->OperTab->Refresh();
      //dbepwd->Text=dm1->OperTab->FieldByName("op_password")->AsString;
      //dbedpassword->Text=DecodePwd();
      //confirmpass->Text=dbedpassword->Text;
   }
   catch(...)
   {
      Application->MessageBox("保存失败!","错误",MB_OK+MB_ICONERROR);
   }
   dm1->OperTab->EnableControls();
   SetButton(true);
   SetDBedit(false);
}
//---------------------------------------------------------------------------

void __fastcall Toperatorform::btncancelClick(TObject *Sender)
{
   dm1->OperTab->DisableControls();
   dm1->OperTab->Cancel();
   dm1->OperTab->Refresh();
   cmbclass->ItemIndex=sclass->IndexOf(dm1->OperTab->FieldByName("op_class")->AsInteger);
   dbepwd->Text=dm1->OperTab->FieldByName("op_password")->AsString;
   dbedpassword->Text=DecodePwd();
   confirmpass->Text=dbedpassword->Text;
   dm1->OperTab->EnableControls();
   SetButton(true);
   SetDBedit(false);
}
//---------------------------------------------------------------------------

void __fastcall Toperatorform::btnfirstClick(TObject *Sender)
{
    dm1->OperTab->DisableControls();
    dm1->OperTab->First();
    cmbclass->ItemIndex=sclass->IndexOf(dm1->OperTab->FieldByName("op_class")->AsInteger);
    rank = dm1->OperTab->FieldByName("op_class")->AsInteger;
    dm1->OperTab->EnableControls();
    dbedpassword->Text=DecodePwd();
    confirmpass->Text=dbedpassword->Text;
    if (dm1->OperTab->Bof)
    {
       btnfirst->Enabled = false;
       btnprior->Enabled = false;
    }
    btnnext->Enabled = true;
    btnlast->Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall Toperatorform::btnpriorClick(TObject *Sender)
{
    dm1->OperTab->DisableControls();
    dm1->OperTab->Prior();
    cmbclass->ItemIndex=sclass->IndexOf(dm1->OperTab->FieldByName("op_class")->AsInteger);
    rank = dm1->OperTab->FieldByName("op_class")->AsInteger;
    dm1->OperTab->EnableControls();
    dbedpassword->Text=DecodePwd();
    confirmpass->Text=dbedpassword->Text;
    if (dm1->OperTab->Bof)
    {
       btnfirst->Enabled = false;
       btnprior->Enabled = false;
    }
    btnnext->Enabled = true;
    btnlast->Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall Toperatorform::btnnextClick(TObject *Sender)
{
   dm1->OperTab->DisableControls();
   dm1->OperTab->Next();
   cmbclass->ItemIndex=sclass->IndexOf(dm1->OperTab->FieldByName("op_class")->AsInteger);
   rank = dm1->OperTab->FieldByName("op_class")->AsInteger;
   dm1->OperTab->EnableControls();
   dbedpassword->Text=DecodePwd();
   confirmpass->Text=dbedpassword->Text;
   if (dm1->OperTab->Eof)
   {
      btnnext->Enabled = false;
      btnlast->Enabled = false;
   }
   btnfirst->Enabled = true;
   btnprior->Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall Toperatorform::btnlastClick(TObject *Sender)
{
    dm1->OperTab->DisableControls();
    dm1->OperTab->Last();
    cmbclass->ItemIndex=sclass->IndexOf(dm1->OperTab->FieldByName("op_class")->AsInteger);
    rank = dm1->OperTab->FieldByName("op_class")->AsInteger;
    dm1->OperTab->EnableControls();
    dbedpassword->Text=DecodePwd();
    confirmpass->Text=dbedpassword->Text;
    if (dm1->OperTab->Eof)
    {
       btnnext->Enabled = false;
       btnlast->Enabled = false;
    }
    btnfirst->Enabled = true;
    btnprior->Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall Toperatorform::btnqueryClick(TObject *Sender)
{
    AnsiString  strcode;
    TLocateOptions Opts;

    Opts.Clear();
    Opts <<loCaseInsensitive;
    strcode= "123456";
    if (!InputQuery("请输入操作员工号:","操作员查找  ",strcode))
       return;
    dm1->OperTab->First();
    dm1->OperTab->DisableControls();
    if (!dm1->OperTab->Locate("op_code",strcode,Opts))
       Application->MessageBox("没有此操作员!","系统信息",MB_OK);
    cmbclass->ItemIndex=sclass->IndexOf(dm1->OperTab->FieldByName("op_class")->AsInteger);
    rank = dm1->OperTab->FieldByName("op_class")->AsInteger;
    dm1->OperTab->EnableControls();
    dbedpassword->Text=DecodePwd();
    confirmpass->Text=dbedpassword->Text;
}
//---------------------------------------------------------------------------

void __fastcall Toperatorform::FormClose(TObject *Sender,
      TCloseAction &Action)
{
   dm1->db1->Connected=false;
   if (sclass)
      delete sclass;
}
//---------------------------------------------------------------------------

void __fastcall Toperatorform::dbedoptnameKeyPress(TObject *Sender,
      char &Key)
{
   if (Key==13)
   {
      Key=0;
      SelectNext(ActiveControl,true,true);
   }
}
//---------------------------------------------------------------------------

void __fastcall Toperatorform::dbedoptcodeKeyPress(TObject *Sender,
      char &Key)
{
   if (Key==13)
   {
      Key=0;
      SelectNext(ActiveControl,true,true);
   }
}
//---------------------------------------------------------------------------

void __fastcall Toperatorform::dbedpasswordKeyPress(TObject *Sender,
      char &Key)
{
   if (Key==13)
   {
      Key=0;
      SelectNext(ActiveControl,true,true);
   }
}
//---------------------------------------------------------------------------

void __fastcall Toperatorform::confirmpassKeyPress(TObject *Sender,
      char &Key)
{
   if (Key==13)
   {
      Key=0;
      SelectNext(ActiveControl,true,true);
   }
}
//---------------------------------------------------------------------------

void __fastcall Toperatorform::cmbclassKeyPress(TObject *Sender, char &Key)
{
   if (Key==13)
   {
      Key=0;
      SelectNext(ActiveControl,true,true);
   }
}
//---------------------------------------------------------------------------




