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
#include "ApPrintSetup.h"
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
//---------------------------------------------------------------------------





void __fastcall TMainForm::IDM_DICSTATUSClick(TObject *Sender)
{
	int nRight=GetOperatorRight(operatorcode.c_str(),"IDM_DICSTATUS");
	//状态档输入接口，文件DicStatus.*
	DicStatus(nRight);
}
//---------------------------------------------------------------------------














































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






void __fastcall TMainForm::IDM_ACCEPTClick(TObject *Sender)
{
        int nRight = 1;
        Accept(nRight);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::IDM_DOClick(TObject *Sender)
{
        int nRight = 1;
        Do(nRight);        
}
//---------------------------------------------------------------------------


void __fastcall TMainForm::IDM_FINANCEClick(TObject *Sender)
{
        int nRight = 1;
        Finance(nRight);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::IDM_CALCClick(TObject *Sender)
{
        int nRight = 1;
//        Calc(nRight);
        CostAccounting(nRight);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::N19Click(TObject *Sender)
{
 Assignment(1);
}
//---------------------------------------------------------------------------



void __fastcall TMainForm::IDM_CURRENCYClick(TObject *Sender)
{
        int nRight = 2;
        DicDicCurrency(nRight);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::IDM_TARGETCOUNTRYClick(TObject *Sender)
{
        int nRight = 2;
        DicTargetCountry(nRight);

}
//---------------------------------------------------------------------------

void __fastcall TMainForm::IDM_STATUSClick(TObject *Sender)
{
        int nRight = 2;
        DicStatus1(nRight);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::IDM_BARGAINClick(TObject *Sender)
{
        int nRight = 2;
        DicBargain(nRight);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::IDM_EXCHARGEClick(TObject *Sender)
{
        int nRight = 2;
        DicExcharge(nRight);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::IDM_TRADEClick(TObject *Sender)
{
        int nRight = 2;
        DicTrade(nRight);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::IDM_TRANSPORTClick(TObject *Sender)
{
        int nRight = 2;
        DicTransport(nRight);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::IDM_PACKClick(TObject *Sender)
{
        int nRight = 2;
        DicPack(nRight);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::IDM_BOATNOClick(TObject *Sender)
{
        int nRight = 2;
        DicBoatNo(nRight);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::IDM_BOATORDERClick(TObject *Sender)
{
        int nRight = 2;
        DicBoatOrder(nRight);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::IDM_ZHENGMIANClick(TObject *Sender)
{
         int nRight = 2;
        DicZhengMian(nRight);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::IDM_MERCHANDISEClick(TObject *Sender)
{
        int nRight = 2;
        DicMerchandise(nRight);
}
//---------------------------------------------------------------------------


void __fastcall TMainForm::IDM_CLIENTClick(TObject *Sender)
{
        int nRight = 2;
        DicClient(nRight);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::IDM_SHIPAGENTClick(TObject *Sender)
{
        int nRight = 2;
        DicShipAgent1(nRight);
}
//---------------------------------------------------------------------------


void __fastcall TMainForm::IDM_OPERCLASSSET1Click(TObject *Sender)
{
	//取得操作等级的权限
//	int nRight=GetOperatorRight(operatorcode.c_str(),"N10");
	//等级权限设置接口，文件ClassRight.*
	ClassRight(2);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::IDM_SHClick(TObject *Sender)
{

        int nRight = 2;
        DicSH(nRight);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::IDM_OPERUNITClick(TObject *Sender)
{

        int nRight = 2;
        DicOperUnit(nRight);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::IDM_CHARGEClick(TObject *Sender)
{
                       
        int nRight = 2;
        DicCharge(nRight);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::timer_keepaliveTimer(TObject *Sender)
{
        RunSQL("select 1",true);    
}
//---------------------------------------------------------------------------

