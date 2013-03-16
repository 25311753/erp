//---------------------------------------------------------------------------

#include <vcl.h>
#include <stdio.h>
#pragma hdrstop

#include "BaseCode.h"
#include "BfPrintSetup.h"
#include "LdyInterface.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TBfPrnSetupForm *BfPrnSetupForm;
//---------------------------------------------------------------------------
__fastcall TBfPrnSetupForm::TBfPrnSetupForm(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TBfPrnSetupForm::FormShow(TObject *Sender)
{
	char strTop[256],strLeft[256],strBottom[256];

  GetPrivateProfileString("BFPRINTSETUP","TOPMARGIN" ,	""	,strTop 	,250,INI_FILE_NAME);
  GetPrivateProfileString("BFPRINTSETUP","BOTTOMMARGIN" ,""	,strBottom ,250,INI_FILE_NAME);
  GetPrivateProfileString("BFPRINTSETUP","LEFTMARGIN",""		,strLeft,250,INI_FILE_NAME);
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

void __fastcall TBfPrnSetupForm::btnOKClick(TObject *Sender)
{
	WritePrivateProfileString("BFPRINTSETUP","TOPMARGIN" ,edtTop->Text.c_str()	,INI_FILE_NAME);
	WritePrivateProfileString("BFPRINTSETUP","BOTTOMMARGIN" ,edtBottom->Text.c_str()	,INI_FILE_NAME);
	WritePrivateProfileString("BFPRINTSETUP","LEFTMARGIN",edtLeft->Text.c_str() ,INI_FILE_NAME);
	Close();
}
//---------------------------------------------------------------------------

void __fastcall TBfPrnSetupForm::btnCancelClick(TObject *Sender)
{
	Close();	
}
//---------------------------------------------------------------------------

