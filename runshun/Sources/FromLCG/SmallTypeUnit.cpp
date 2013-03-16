//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "SmallTypeUnit.h"
#include "DataModule.h"
#include "CommUnit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "BaseFormUnit"
#pragma resource "*.dfm"
TSmallTypeForm *SmallTypeForm;
//---------------------------------------------------------------------------

__fastcall TSmallTypeForm::TSmallTypeForm(TComponent* Owner)
   : TBaseForm(Owner)
{
}
//---------------------------------------------------------------------------

bool  TSmallTypeForm::CheckCode()
{
   if (edtcode->Text.Length()<4)
   {
      ErrorDlg("小类代码长度必须是四位!");
      edtcode->SetFocus();
      return false;
   }
   else
   {  //是否存在中类代码
      strsql =AnsiString("select mt_code from dicmiddletype where mt_code='")
             +edtcode->Text.SubString(1,2)+"'";
      if (DoQuery(dm1->Query1,strsql))
      {
         if (dm1->Query1->IsEmpty())
         {
            ErrorDlg("前二位中类代码不存在,请重新输入!");
            edtcode->SetFocus();
            return false;
         }
      }
      else
         return false;
   }
   return true;
}
//---------------------------------------------------------------------------

void __fastcall TSmallTypeForm::FormShow(TObject *Sender)
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
   smtype = new TStringList;
   strsql =AnsiString("select * from dicmiddletype order by mt_code ");
   if (DoQuery(dm1->Query1,strsql))
   {
      if (!dm1->Query1->IsEmpty())
      {
         cbmtype->Items->Clear();
         while (!dm1->Query1->Eof)
         {
            smtype->Add(dm1->Query1->FieldByName("mt_code")->AsString);
            cbmtype->Items->Add(dm1->Query1->FieldByName("mt_name")->AsString);
            dm1->Query1->Next();
         }
      }
   }
}
//---------------------------------------------------------------------------

void __fastcall TSmallTypeForm::FormClose(TObject *Sender,
      TCloseAction &Action)
{
    if (dm1->db1->Connected)
       dm1->db1->Connected=false;
    if (prtform)
    {
       delete prtform;
       prtform=NULL;
    }
    if (smtype)
       delete smtype;
}
//---------------------------------------------------------------------------

void __fastcall TSmallTypeForm::btnokClick(TObject *Sender)
{
   if (!dm1->ConnectDB())
      return;
   switch(btnidx)
   {
      case 0://do add
           if (!CheckEdit())
              break;
           if (!CheckCode())
              break;
           strsql =AnsiString("select st_code from dicsmalltype where st_code='")
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
           strsql =AnsiString("insert into dicsmalltype values('")+edtcode->Text+"','"
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
           if (!CheckCode())
              break;
           strsql =AnsiString("update dicsmalltype set st_name='")
                  +edtname->Text+"' where st_code='"
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
           strsql =AnsiString("delete dicsmalltype where st_code='")
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

void  TSmallTypeForm::LocateRow()
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
         ListView1Click(SmallTypeForm);
         break;
      }
   }
}
//---------------------------------------------------------------------------

void __fastcall TSmallTypeForm::btnrefClick(TObject *Sender)
{
   if (!dm1->ConnectDB())
      return;
   //if (cbmtype->ItemIndex<0)
      strsql=AnsiString("select * from dicsmalltype order by st_code ");
   /*else
      strsql =AnsiString("select * from dicsmalltype where st_code like '")
          +smtype->Strings[cbmtype->ItemIndex]+"%' order by st_code ";*/
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

void __fastcall TSmallTypeForm::btnprintClick(TObject *Sender)
{
   if (!prtform)
   {
      ErrorDlg("不能列印,请检查印表机设置!");
      return;
   }
   if (cbmtype->ItemIndex<0)
      strsql =AnsiString("select * from dicsmalltype order by st_code ");
   else
      strsql =AnsiString("select * from dicsmalltype where st_code like '")
          +smtype->Strings[cbmtype->ItemIndex]+"%' order by st_code ";
   if (!dm1->ConnectDB())
      return;
   if (!DoQuery(dm1->Query1,strsql))
      return;
   if (dm1->Query1->IsEmpty())
   {
      InfoDlg("没有可以列印的数据!");
      return;
   }
   prtform->LabTitle->Caption="小类资料档";
   prtform->LabCode->Caption="小类代码";
   prtform->LabName->Caption="小类名称";
   prtform->QRDBText1->DataField="st_code";
   prtform->QRDBText2->DataField="st_name";
   prtform->QuickRep1->PreviewModal();
   dm1->db1->Connected=false;
}
//---------------------------------------------------------------------------

void __fastcall TSmallTypeForm::ListView1Click(TObject *Sender)
{
    if (ListView1->SelCount>0)
    {
       edtcode->Text=ListView1->Selected->SubItems->Strings[0];
       edtname->Text=ListView1->Selected->SubItems->Strings[1];
       edtcodeExit(Sender);
    }
}
//---------------------------------------------------------------------------

void __fastcall TSmallTypeForm::edtnameKeyDown(TObject *Sender, WORD &Key,
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

void __fastcall TSmallTypeForm::cbmtypeChange(TObject *Sender)
{
   if (cbmtype->ItemIndex>=0)
   {
      edtcode->Text=smtype->Strings[cbmtype->ItemIndex];
      //btnref->Click();
   }
}
//---------------------------------------------------------------------------

void __fastcall TSmallTypeForm::edtcodeExit(TObject *Sender)
{
    edtcode->Text=Trim(edtcode->Text);
    if (edtcode->Text=="")
       return;
    if (smtype->IndexOf(edtcode->Text.SubString(1,2))>=0)
       cbmtype->ItemIndex=smtype->IndexOf(edtcode->Text.SubString(1,2));
}
//---------------------------------------------------------------------------

void __fastcall TSmallTypeForm::btncanClick(TObject *Sender)
{
    cbmtype->ItemIndex=-1;
    SetDefault();
}
//---------------------------------------------------------------------------

void __fastcall TSmallTypeForm::FormActivate(TObject *Sender)
{
    if (ListView1->Items->Count<1)
       btnref->Click();
}
//---------------------------------------------------------------------------

