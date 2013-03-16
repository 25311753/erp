 //---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "MainFrame.h"
#include "DataModule.h"
#include "CommUnit.h"
#include "LargeTypeUnit.h"
#include "MiddleTypeUnit.h"
#include "SmallTypeUnit.h"
#include "MaterialNoUnit.h"
#include "TConst.h"
#include "operatorunit.h"
#include "operpwdunit.h"
#include "InputCorpUnit.h"
#include "calsssetunit.h"
//#include "SetRightsUnit.h"
//#include "ApPrintSetup.h"
#include "LdyInterface.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "trayicon"
#pragma resource "*.dfm"
TMainForm *MainForm;
//---------------------------------------------------------------------------
__fastcall TMainForm::TMainForm(TComponent* Owner)
   : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::GetTime()
{
   AnsiString  str;

   str = "select curtime=getdate()";
   if (DoQuery(dm1->Query1,str))
   {
      str=FormatDateTime("yyyy-mm-dd hh:mm:ss",dm1->Query1->FieldByName("curtime")->AsDateTime);
   }
   else
      str=FormatDateTime("yyyy-mm-dd hh:mm:ss",Now());
   //dm1->db1->Connected=false;
   sysdate=str.SubString(1,10);
   systime=str.SubString(12,8);
   StatusBar1->Panels->Items[1]->Text=str;
   Timer1->Enabled=true;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::Timer1Timer(TObject *Sender)
{
   Word   CHour,CMin,CSec,CMSec=0;
   try
   {
     systime=(StatusBar1->Panels->Items[1]->Text).SubString(12,8);
     CHour=StrToInt(systime.SubString(1,2));
     CMin=StrToInt(systime.SubString(4,2));
     CSec=StrToInt(systime.SubString(7,2));
     //adjust time once an hour, get datetime from database.
     if ((CMin==59)&&(CSec==59))
     {
        GetTime();
     }
     else
     {
        if (CSec==59)
        {
           CMin = CMin + 1;
           CSec = 0;
        }
        else
           CSec = CSec + 1;
        sysdate=(StatusBar1->Panels->Items[1]->Text).SubString(1,10);
        systime=(StatusBar1->Panels->Items[1]->Text).SubString(12,8);
        StatusBar1->Panels->Items[1]->Text = sysdate+" "
          + FormatDateTime("hh:mm:ss",EncodeTime(CHour,CMin,CSec,CMSec));
     }
   }
   catch(...)
   {
      return;
   }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::SetModule()
{
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::N7Click(TObject *Sender)
{
   Close();
}
//---------------------------------------------------------------------------

void TMainForm::ResetMenu(TMenuItem *pMenu)
{
	int i;
	if(pMenu->Count>0)
  {
		for(i=0;i<pMenu->Count;i++)
    	ResetMenu(pMenu->Items[i]);
  }
  else
  {
  	pMenu->Enabled = GetClassRight(StrToInt(operator_class),pMenu->Name.c_str())!=0
	  	&& pMenu->OnClick!=NULL; //有权限且有响应函数菜单才不变灰
//        pMenu->Visible = pMenu->Enabled;
  }
}

void __fastcall TMainForm::FormShow(TObject *Sender)
{
	int i;
  for(i=0;i<MainMenu1->Items->Count;i++)
  {
		ResetMenu(MainMenu1->Items->Items[i]);
  }

   DateSeparator = '-';
   TimeSeparator = ':';
   if (dm1->ConnectDB())
   {
      SetModule();
      GetTime();
      dm1->db1->Connected=false;
   }
   StatusBar1->Panels->Items[0]->Text="工号:"+operatorcode;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::FormShortCut(TWMKey &Msg, bool &Handled)
{
//
//    switch(Msg.CharCode)
//    {
//       case VK_ESCAPE:
//            Close();
//            Handled=true;
//            break;
//    }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::FormCloseQuery(TObject *Sender, bool &CanClose)
{
#ifndef _DEBUG
    if (Application->MessageBox("您真的要退出本系统吗?","系统提示", MB_YESNO+MB_ICONQUESTION)!= IDYES)
       CanClose = false;
    else
       CanClose= true;
#endif
}
//---------------------------------------------------------------------------





void MaterialEdit(int nAuth);


void __fastcall TMainForm::IDM_OPERATORClick(TObject *Sender)
{
    if (!operatorform)
      operatorform = new Toperatorform(Application);
    if (operatorform)
    {
       operatorform->ShowModal();
       delete operatorform;
       operatorform=NULL;
    }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::IDM_MODPWClick(TObject *Sender)
{
   if (!operpwdform)
      operpwdform = new Toperpwdform(Application);
   if (operpwdform)
   {
      operpwdform->ShowModal();
      delete operpwdform;
      operpwdform=NULL;
   }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::IDM_CLASSRIGHTClick(TObject *Sender)
{
	//取得操作等级的权限
	int nRight=GetOperatorRight(operatorcode.c_str(),"N10");
	//等级权限设置接口，文件ClassRight.*
	ClassRight(nRight);

/*
    if (!SetRightsForm)
       SetRightsForm = new TSetRightsForm(Application);
    if (SetRightsForm)
    {
       SetRightsForm->ShowModal();
       delete SetRightsForm;
       SetRightsForm=NULL;
    }
*/

}
//---------------------------------------------------------------------------


void __fastcall TMainForm::IDM_OPERCLASSSETClick(TObject *Sender)
{
   if (!classsetform)
      classsetform = new Tclasssetform(Application);
   if (classsetform)
   {
      classsetform->ShowModal();
      delete classsetform;
      classsetform=NULL;
   }

}














































#include "ShowPrintSetup.h"

#include "BfPrintSetup.h"
#include "BaseCode.h"}
//---------------------------------------------------------------------------
#include "SumEffect.h"

#include "ApFilePage.h"



//---------------------------------------------------------------------------
#include "ApFPList.h"#include "SumMaterialnoFactory.h"
#include "MaterialPicEdit.h"
#include "MaterialRem.h"


void __fastcall TMainForm::IDM_OPERCLASSSET1Click(TObject *Sender)
{
	//取得操作等级的权限
//	int nRight=GetOperatorRight(operatorcode.c_str(),"N10");
	//等级权限设置接口，文件ClassRight.*
	ClassRight(2);
}
//---------------------------------------------------------------------------






void __fastcall TMainForm::IDM_CLIENTClick(TObject *Sender)
{

//        int nRight = 2;
	int nRight=GetOperatorRight(operatorcode.c_str(),"IDM_CLIENT");
        DicClient(nRight);        
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::IDM_SUPPLIERClick(TObject *Sender)
{
        int nRight = 2;
        DicSupplier(nRight);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::IDM_OPERATIONClick(TObject *Sender)
{
//	int nRight=GetOperatorRight(operatorcode.c_str(),"IDM_OPERATION");
//        Operation(nRight);        
}
//---------------------------------------------------------------------------




void __fastcall TMainForm::N3Click(TObject *Sender)
{
	int nRight=GetOperatorRight(operatorcode.c_str(),"N3");
        FinanceOp(nRight);        
}
//---------------------------------------------------------------------------


void __fastcall TMainForm::IDM_COMMITIONClick(TObject *Sender)
{

        int nRight = 2;
        Commition(nRight);
}
//---------------------------------------------------------------------------




void __fastcall TMainForm::N4Click(TObject *Sender)
{
        ShowMessage("下个测试版本提供");
        return;        
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::N6Click(TObject *Sender)
{
        ShowMessage("下个测试版本提供");
        return;        
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::N8Click(TObject *Sender)
{
        ShowMessage("下个测试版本提供");
        return;        
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::IDM_NEW_CLI_PRIZEClick(TObject *Sender)
{
        int nRight = 2;
        NewClientPrize(nRight);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::IDM_SALE_QRYClick(TObject *Sender)
{
        int nRight = 2;
        QrySale(nRight);
}
//---------------------------------------------------------------------------



void __fastcall TMainForm::IDM_YJ_QRYClick(TObject *Sender)
{
        int nRight = 2;
        YjQry(nRight);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::IDM_TC_QRYClick(TObject *Sender)
{
        int nRight = 2;
        Tc(nRight);
}
//---------------------------------------------------------------------------


void __fastcall TMainForm::IDM_XK_QRYClick(TObject *Sender)
{
        int nRight = 2;
        XkQry(nRight);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::IDM_OP_QRYClick(TObject *Sender)
{
        int nRight = 2;
        OpQry(nRight);
}
//---------------------------------------------------------------------------


void __fastcall TMainForm::IDM_XK_CSSZClick(TObject *Sender)
{
        int nRight = 2;
        XkCSSZ(nRight);
}
//---------------------------------------------------------------------------



void __fastcall TMainForm::IDM_TC_CSSZClick(TObject *Sender)
{

        int nRight = 2;
        TcCSSZ(nRight);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::IDM_YJ_CSSZClick(TObject *Sender)
{

        int nRight = 2;
        YjCSSZ(nRight);
}
//---------------------------------------------------------------------------


