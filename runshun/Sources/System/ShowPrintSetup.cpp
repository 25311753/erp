//---------------------------------------------------------------------------

#include <vcl.h>
#include <stdio.h>
#pragma hdrstop

#include "BaseCode.h"
#include "ShowPrintSetup.h"
#include "LdyInterface.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TShowPrnSetupForm *ShowPrnSetupForm;
//---------------------------------------------------------------------------
__fastcall TShowPrnSetupForm::TShowPrnSetupForm(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TShowPrnSetupForm::FormShow(TObject *Sender)
{
	char strTop[256],strLeft[256],strBottom[256];

  GetPrivateProfileString("SHOWPRINTSETUP","TOPMARGIN" ,	""	,strTop 	,250,INI_FILE_NAME);
  GetPrivateProfileString("SHOWPRINTSETUP","BOTTOMMARGIN" ,""	,strBottom ,250,INI_FILE_NAME);
  GetPrivateProfileString("SHOWPRINTSETUP","LEFTMARGIN",""		,strLeft,250,INI_FILE_NAME);
	if(strTop[0]=='\0' || strLeft[0]=='\0' || strBottom[0]=='\0')
	{
		edtTop ->Text="";
    edtBottom->Text="";
		edtLeft->Text="";
	}
	else
	{
		edtTop ->Text=strTop;
    edtBottom->Text=strBottom;
		edtLeft->Text=strLeft;
	}
}
//---------------------------------------------------------------------------

void __fastcall TShowPrnSetupForm::btnOKClick(TObject *Sender)
{
	WritePrivateProfileString("SHOWPRINTSETUP","TOPMARGIN" ,edtTop->Text.c_str()	,INI_FILE_NAME);
	WritePrivateProfileString("SHOWPRINTSETUP","BOTTOMMARGIN" ,edtBottom->Text.c_str()	,INI_FILE_NAME);
	WritePrivateProfileString("SHOWPRINTSETUP","LEFTMARGIN",edtLeft->Text.c_str() ,INI_FILE_NAME);
	Close();
}
//---------------------------------------------------------------------------

void __fastcall TShowPrnSetupForm::btnCancelClick(TObject *Sender)
{
	Close();	
}
//---------------------------------------------------------------------------

