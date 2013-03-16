//---------------------------------------------------------------------------

#include <vcl.h>
#include <stdio.h>
#pragma hdrstop

#include "BaseCode.h"
#include "ApPrintSetup.h"
#include "LdyInterface.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TApPrnSetupForm *ApPrnSetupForm;
//---------------------------------------------------------------------------
__fastcall TApPrnSetupForm::TApPrnSetupForm(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TApPrnSetupForm::FormShow(TObject *Sender)
{
	char strTop[256],strLeft[256],strBottom[256];

  GetPrivateProfileString("APPRINTSETUP","TOPMARGIN" ,	""	,strTop 	,250,INI_FILE_NAME);
  GetPrivateProfileString("APPRINTSETUP","BOTTOMMARGIN" ,""	,strBottom ,250,INI_FILE_NAME);
  GetPrivateProfileString("APPRINTSETUP","LEFTMARGIN",""		,strLeft,250,INI_FILE_NAME);
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

void __fastcall TApPrnSetupForm::btnOKClick(TObject *Sender)
{
	WritePrivateProfileString("APPRINTSETUP","TOPMARGIN" ,edtTop->Text.c_str()	,INI_FILE_NAME);
	WritePrivateProfileString("APPRINTSETUP","BOTTOMMARGIN" ,edtBottom->Text.c_str()	,INI_FILE_NAME);
	WritePrivateProfileString("APPRINTSETUP","LEFTMARGIN",edtLeft->Text.c_str() ,INI_FILE_NAME);
	Close();
}
//---------------------------------------------------------------------------

void __fastcall TApPrnSetupForm::btnCancelClick(TObject *Sender)
{
	Close();	
}
//---------------------------------------------------------------------------

