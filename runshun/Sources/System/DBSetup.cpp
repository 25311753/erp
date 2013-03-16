//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "BaseCode.h"
#include "DataModule.h"
#include "DBSetup.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TDBSetupForm *DBSetupForm;

void InitialODBC()
{
	char strODBC[256],strUID[256],strPwd[256],strTemp[256];

  GetPrivateProfileString("DATABASE","ODBC","",strODBC,250,INI_FILE_NAME);
  GetPrivateProfileString("DATABASE","USER","",strUID ,250,INI_FILE_NAME);
  GetPrivateProfileString("DATABASE","PASS","",strTemp,250,INI_FILE_NAME);
	if(strODBC[0]!='\0' && strUID[0]!='\0' && strTemp[0]!='\0')
	{
		strcpy(strPwd,SimpleDecode(strTemp));
    g_szODBC	=strODBC;
    g_szDBUser=strUID;
    g_szDBPass=strPwd;
		dm1->SetupDB();
	}
}

//---------------------------------------------------------------------------
__fastcall TDBSetupForm::TDBSetupForm(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TDBSetupForm::FormShow(TObject *Sender)
{
	edtODBC	->Text=g_szODBC;
	edtUID	->Text=g_szDBUser;
	edtPwd	->Text=g_szDBPass;
	edtPwd2	->Text=g_szDBPass;
	if(edtODBC->CanFocus())	edtODBC->SetFocus();
}
//---------------------------------------------------------------------------
void __fastcall TDBSetupForm::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
	if(Key==VK_RETURN)
		KeyReturnHandle(ActiveControl);
}

//---------------------------------------------------------------------------
void __fastcall TDBSetupForm::btnTestClick(TObject *Sender)
{
	if(TestSetup())
  	ShowMessage("连接成功");
  else
  	ShowMessage("连接失败");
}

bool TDBSetupForm::TestSetup()
{
	edtODBC->Text=edtODBC->Text.Trim();
  edtUID->Text=edtUID->Text.Trim();
  edtPwd->Text=edtPwd->Text.Trim();
  edtPwd2->Text=edtPwd->Text.Trim();
  if(edtODBC->Text.IsEmpty())
	{
  	ShowMessage("请输入ODBC");
    if(edtODBC->CanFocus())	edtODBC->SetFocus();
    return false;
  }
  if(edtUID->Text.IsEmpty())
	{
  	ShowMessage("请输入账号");
    if(edtUID->CanFocus())	edtUID->SetFocus();
    return false;
  }
  if(edtPwd->Text.IsEmpty())
	{
  	ShowMessage("请输入密码");
    if(edtPwd->CanFocus())	edtPwd->SetFocus();
    return false;
  }
	if(edtPwd->Text!=edtPwd2->Text)
  {
  	ShowMessage("密码与确认密码不相同");
    if(edtPwd->CanFocus())	edtPwd->SetFocus();
    return false;
	}

	g_szODBC	=edtODBC->Text;
	g_szDBUser=edtUID->Text;
	g_szDBPass=edtPwd->Text;

	dm1->CloseDatabase();
  dm1->SetupDB();
  return dm1->OpenDatabase();
}
//---------------------------------------------------------------------------

void __fastcall TDBSetupForm::btnOKClick(TObject *Sender)
{
	if(!TestSetup())
	{
  	ShowMessage("连接失败");
    return;
  }

  char strPwd[256];
  strcpy(strPwd,SimpleEncode(g_szDBPass.c_str()));

	WritePrivateProfileString("DATABASE","ODBC",g_szODBC.c_str()	,INI_FILE_NAME);
	WritePrivateProfileString("DATABASE","USER",g_szDBUser.c_str(),INI_FILE_NAME);
	WritePrivateProfileString("DATABASE","PASS",strPwd						,INI_FILE_NAME);

	Close();
}
//---------------------------------------------------------------------------

void __fastcall TDBSetupForm::btnCancelClick(TObject *Sender)
{
	Close();	
}
//---------------------------------------------------------------------------

