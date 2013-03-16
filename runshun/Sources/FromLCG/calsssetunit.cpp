//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "calsssetunit.h"
#include "DataModule.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
Tclasssetform *classsetform;
//---------------------------------------------------------------------------
__fastcall Tclasssetform::Tclasssetform(TComponent* Owner)
   : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void   Tclasssetform::DoSelect()
{
      try
      {
         dm1->Query1->Close();
         dm1->Query1->SQL->Clear();
         dm1->Query1->SQL->Add("select * from operclass");
         dm1->Query1->Prepare();
         dm1->Query1->Open();
         dm1->Query1->First();
         edtclass->Text="";
         lbclass->Items->Clear();
         while(!dm1->Query1->Eof)
         {
             sclass->Add(dm1->Query1->Fields->Fields[0]->AsString);
             lbclass->Items->Add(dm1->Query1->Fields->Fields[1]->AsString);
             dm1->Query1->Next();
         }
         dm1->Query1->Close();
      }
      catch(...)
      {
         Application->MessageBox("打开表失败,不能运行!","错误",MB_OK+MB_ICONERROR);
         btnadd->Enabled=false;
         btnmodify->Enabled=false;
         btndelete->Enabled=false;
         btnclose->Enabled=true;
      }
}
//---------------------------------------------------------------------------

bool  Tclasssetform::FindRank()
{
   for (int i=0;i<lbclass->Items->Count;i++)
   {
      if (lbclass->Items->Strings[i]==edtclass->Text)
         return true;
   }
   return false;
}
//---------------------------------------------------------------------------

void __fastcall Tclasssetform::FormShow(TObject *Sender)
{
   sclass = new TStringList;
   sclass->Clear();
   if (dm1->ConnectDB())
   {
      DoSelect();
      dm1->db1->Connected=false;
   }
}
//---------------------------------------------------------------------------

void __fastcall Tclasssetform::FormClose(TObject *Sender,
      TCloseAction &Action)
{
   //dm1->db1->Connected=false;
   if (sclass)
      delete sclass;
}
//---------------------------------------------------------------------------

void __fastcall Tclasssetform::btnaddClick(TObject *Sender)
{
   if (edtclass->Text=="")
   {
      ShowMessage("请输入要加入的等级名称！");
      edtclass->SetFocus();
      return;
   }
   else if (FindRank())
   {
      ShowMessage("输入了相同的等级名称！");
      edtclass->SetFocus();
      return;
   }
   if (dm1->ConnectDB())
   {
      try
      {
         dm1->Query1->Close();
         dm1->Query1->SQL->Clear();
         dm1->Query1->SQL->Add(" insert into operclass values(:name)");
         dm1->Query1->ParamByName("name")->AsString=edtclass->Text;
         dm1->Query1->Prepare();
         dm1->Query1->ExecSQL();
         DoSelect();
         ShowMessage("新增完成！");
         edtclass->Text="";
         edtclass->SetFocus();
      }
      catch(...)
      {
         Application->MessageBox("新增失败!","错误",MB_OK+MB_ICONERROR);
      }
      dm1->db1->Connected=false;
   }
}
//---------------------------------------------------------------------------

void __fastcall Tclasssetform::btnmodifyClick(TObject *Sender)
{
   if (edtclass->Text=="")
   {
      ShowMessage("请选择要修改的等级名称！");
      lbclass->SetFocus();
      return;
   }
   else if (FindRank())
   {
      ShowMessage("输入了相同的等级名称！");
      edtclass->SetFocus();
      return;
   }
   else if (lbclass->Items->Strings[lbclass->ItemIndex]=="总管理员")
   {
      Beep();
      Application->MessageBox("不能修改总管理员等级！","系统信息",MB_OK+MB_ICONERROR);
      edtclass->Text="";
      return;
   }
   if (dm1->ConnectDB())
   {
      try
      {
         dm1->Query1->Close();
         dm1->Query1->SQL->Clear();
         dm1->Query1->SQL->Add("update operclass set oc_name=:name where oc_code=:code");
         dm1->Query1->ParamByName("name")->AsString=edtclass->Text;
         dm1->Query1->ParamByName("code")->AsInteger=StrToInt(sclass->Strings[lbclass->ItemIndex]);
         dm1->Query1->Prepare();
         dm1->Query1->ExecSQL();
         DoSelect();
         ShowMessage("修改完成！");
      }
      catch(...)
      {
         Application->MessageBox("修改失败!","错误",MB_OK+MB_ICONERROR);
      }
      dm1->db1->Connected=false;
   }
}
//---------------------------------------------------------------------------

void __fastcall Tclasssetform::btndeleteClick(TObject *Sender)
{
   if (edtclass->Text=="")
   {
      ShowMessage("请选择要删除的等级名称！");
      lbclass->SetFocus();
      return;
   }
   else if (edtclass->Text=="总管理员")
   {
      Beep();
      Application->MessageBox("不能删除总管理员等级！","系统信息",MB_OK+MB_ICONERROR);
      return;
   }
   else if (Application->MessageBox("真的想删除这个等级吗?","系统信息",MB_YESNO)==IDNO)
      return;
   if (dm1->ConnectDB())
   {
      try
      {
         dm1->Query1->Close();
         dm1->Query1->SQL->Clear();
         dm1->Query1->SQL->Add("delete from operclass where oc_code=:code");
         dm1->Query1->ParamByName("code")->AsInteger=StrToInt(sclass->Strings[lbclass->ItemIndex]);
         dm1->Query1->Prepare();
         dm1->Query1->ExecSQL();
         DoSelect();
         ShowMessage("删除完成！");
      }
      catch(...)
      {
         Application->MessageBox("删除失败!","错误",MB_OK+MB_ICONERROR);
      }
      dm1->db1->Connected=false;
   }
}
//---------------------------------------------------------------------------

void __fastcall Tclasssetform::lbclassClick(TObject *Sender)
{
   edtclass->Text=lbclass->Items->Strings[lbclass->ItemIndex];
}
//---------------------------------------------------------------------------

