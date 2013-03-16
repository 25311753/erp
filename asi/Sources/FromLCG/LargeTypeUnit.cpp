//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "LargeTypeUnit.h"
#include "DataModule.h"
#include "CommUnit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "BaseFormUnit"
#pragma resource "*.dfm"
TLargeTypeForm *LargeTypeForm;
//---------------------------------------------------------------------------

__fastcall TLargeTypeForm::TLargeTypeForm(TComponent* Owner)
   : TBaseForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TLargeTypeForm::FormShow(TObject *Sender)
{
   SetDefault();
   ListView1->Items->Clear();
   if (rights==0)
      SetButton(0,0,0,0,0,0,1,1);
   Screen->Cursor= crHourGlass;
   if (!prtform)
   {
      try
      {
         prtform= new TTypePrtForm(Application);
      }
      catch(...)
      {
         prtform=NULL;
      }
   }
   Screen->Cursor=crDefault;
   btnref->Click();
}
//---------------------------------------------------------------------------

void __fastcall TLargeTypeForm::FormClose(TObject *Sender,
      TCloseAction &Action)
{
    if (dm1->db1->Connected)
       dm1->db1->Connected=false;
    if (prtform)
    {
       delete prtform;
       prtform=NULL;
    }
}
//---------------------------------------------------------------------------

void __fastcall TLargeTypeForm::btnokClick(TObject *Sender)
{
   if (!dm1->ConnectDB())
      return;
   switch(btnidx)
   {
      case 0://do add
           if (!CheckEdit())
              break;
           strsql =AnsiString("select lt_code from diclargetype where lt_code='")
                  +edtcode->Text+"'";
           if (DoQuery(dm1->Query1,strsql))
           {
              if (!dm1->Query1->IsEmpty())
              {
                 ErrorDlg("输入了重复的代码!");
                 break;
              }
           }
           else
           {
              SetButton(1,1,1,1,0,0,1,1);
              break;
           }
           strsql =AnsiString("insert into diclargetype values('")+edtcode->Text+"','"
                  +edtname->Text+"')";
           if (DoQuery(dm1->Query1,strsql,1))
           {
              btnref->Click();
              ClearEdit();
              edtcode->SetFocus();
           }
           break;
      case 1:
           LocateRow();
           break;
      case 2://do modify
           if (ListView1->SelCount==0)
           {
              InfoDlg("请先在列表中选择要修改的项次!");
              break;
           }
           if (!CheckEdit())
              break;
           strsql =AnsiString("update diclargetype set lt_name='")
                  +edtname->Text+"' where lt_code='"
                  +ListView1->Selected->SubItems->Strings[0]+"'";
           if (DoQuery(dm1->Query1,strsql,1))
           {
              btnref->Click();
              ClearEdit();
              InfoDlg("修改完成!");
           }
           else
              SetButton(1,1,1,1,0,0,1,1);
           break;
      case 3://do delete
           if (ListView1->SelCount==0)
           {
              InfoDlg("请先在列表中选择要删除的项次!");
              break;
           }
           if (AskDlg("确实要删除该项次吗？")==IDNO)
              break;
           strsql =AnsiString("delete diclargetype where lt_code='")
                  +ListView1->Selected->SubItems->Strings[0]+"'";
           if (DoQuery(dm1->Query1,strsql,1))
           {
              ClearEdit();
              btnref->Click();
              InfoDlg("删除完成!");
           }
           else
              SetButton(1,1,1,1,0,0,1,1);
           break;
   }
   dm1->db1->Connected=false;
}
//---------------------------------------------------------------------------

void  TLargeTypeForm::LocateRow()
{
   AnsiString  fieldsval;
   char  idx;
   if (edtcode->Text!="")
   {
      fieldsval=edtcode->Text;
      idx=0;
   }
   else if (edtname->Text!="")
   {
      fieldsval=edtname->Text;
      idx=1;
   }
   else
   {
      InfoDlg("请输入代码或名称!");
      edtcode->Enabled=true;
      edtname->Enabled=true;
      edtcode->SetFocus();
      return;
   }
   for (int i=0;i<ListView1->Items->Count;i++)
   {
      if (ListView1->Items->Item[i]->SubItems->Strings[idx]==fieldsval)
      {
         ListView1->Items->Item[i]->Selected=true;
         ListView1->SetFocus();
         ListView1Click(LargeTypeForm);
         break;
      }
   }
}
//---------------------------------------------------------------------------

void __fastcall TLargeTypeForm::btnrefClick(TObject *Sender)
{
   if (!dm1->ConnectDB())
      return;
   strsql =AnsiString("select * from diclargetype order by lt_code");
   if (DoQuery(dm1->Query1,strsql))
   {
      ListView1->Items->Clear();
      TListItem  *ListItem;
      while (!dm1->Query1->Eof)
      {
         ListItem=ListView1->Items->Add();
         ListItem->SubItems->Add(dm1->Query1->Fields->Fields[0]->AsString);
         ListItem->SubItems->Add(dm1->Query1->Fields->Fields[1]->AsString);
         dm1->Query1->Next();
      }
   }
   dm1->db1->Connected=false;
}
//---------------------------------------------------------------------------

void __fastcall TLargeTypeForm::btnprintClick(TObject *Sender)
{
   if (!prtform)
   {
      ErrorDlg("不能列印,请检查印表机设置!");
      return;
   }
   if (!dm1->ConnectDB())
      return;
   strsql =AnsiString("select * from diclargetype order by lt_code");
   if (!DoQuery(dm1->Query1,strsql))
      return;
   if (dm1->Query1->IsEmpty())
   {
      InfoDlg("没有可以列印的数据!");
      return;
   }
   prtform->LabTitle->Caption="大类资料档";
   prtform->LabCode->Caption="大类代码";
   prtform->LabName->Caption="大类名称";
   prtform->QRDBText1->DataField="lt_code";
   prtform->QRDBText2->DataField="lt_name";
   prtform->QuickRep1->PreviewModal();
   dm1->db1->Connected=false;
}
//---------------------------------------------------------------------------

void __fastcall TLargeTypeForm::ListView1Click(TObject *Sender)
{
    if (ListView1->SelCount>0)
    {
       edtcode->Text=ListView1->Selected->SubItems->Strings[0];
       edtname->Text=ListView1->Selected->SubItems->Strings[1];
    }
}
//---------------------------------------------------------------------------

void __fastcall TLargeTypeForm::edtnameKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
   if (Key==13)
   {
      Key=0;
      if (btnidx==0||btnidx==2)
         btnok->Click();
   }
}
//---------------------------------------------------------------------------
