//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "DataModule.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
Tdm1 *dm1;
//---------------------------------------------------------------------------

AnsiString g_szODBC;
AnsiString g_szDBUser;
AnsiString g_szDBPass;


__fastcall Tdm1::Tdm1(TComponent* Owner)
   : TDataModule(Owner)
{

}
//---------------------------------------------------------------------------

bool Tdm1::ConnectDB()

{
   if (db1->Connected==false)
   {
      try
      {
         db1->Connected=true;
      }
      catch(...)
      {
         Application->MessageBox("联接不上数据库!","系统提示",MB_OK+MB_ICONERROR);
         return false;
      }
   }
   return true;
}
//---------------------------------------------------------------------------

void	DropTmpPrnTable();

bool Tdm1::OpenDatabase()
{
  if(db1->Connected)  return true;
  try
  {
    db1->Open();
  }
  catch(...)
  {
    Application->MessageBox("\n  打开数据库失败!    \n","错误",MB_OK+MB_ICONERROR);
    return false;
  }
	DropTmpPrnTable();

  return true;
}

bool Tdm1::OpenDatabase(TDatabase *pDB)
{
  if(pDB->Connected)  return true;

  try
  {
    pDB->Open();
  }
  catch(...)
  {
    Application->MessageBox("\n  打开数据库失败!    \n","错误",MB_OK+MB_ICONERROR);
    return false;
  }
  return true;
}

void Tdm1::CloseDatabase(TDatabase *pDB)
{


	pDB->Close();


}


void Tdm1::CloseDatabase()
{
	db1->Close();

}

void Tdm1::SetupDB()
{
	if(!g_szODBC.IsEmpty() && !g_szDBUser.IsEmpty() && !g_szDBPass.IsEmpty())
	{
		int i;
    db1->Connected=false;
		for(i=0;i<db1->Params->Count;i++)
  	{
//    	if(strstr(db1->Params->Strings[i].c_str(),"DATABASE NAME=")!=NULL)
// 				db1->Params->Strings[i]="DATABASE NAME="+g_szODBC;
//    	else
      if(strstr(db1->Params->Strings[i].c_str(),"USER NAME=")!=NULL)
				db1->Params->Strings[i]="USER NAME="+g_szDBUser;
    	else if(strstr(db1->Params->Strings[i].c_str(),"ODBC DSN=")!=NULL)
				db1->Params->Strings[i]="ODBC DSN="+g_szODBC;
    	else if(strstr(db1->Params->Strings[i].c_str(),"PASSWORD=")!=NULL)
				db1->Params->Strings[i]="PASSWORD="+g_szDBPass;
    }
    db1->Connected=true;
	}
}

#include "BaseCode.h"

void DropTmpPrnTable()
{
/*
	try
  {
//		dm1->db1->Execute("exec PickTmpPrnTable",NULL,false,NULL);
    dm1->SPcomn->Close();
    dm1->SPcomn->StoredProcName="PickTmpPrnTable;1";
    dm1->SPcomn->Prepare();
    dm1->SPcomn->ExecProc();
    dm1->SPcomn->Close();
  }
  catch(...)
  {
//  	ShowMessage("fuckyou");
  }
	AnsiString szName;
  CString szSQL;

  szSQL="select * from RuntimeData where rd_key='tmp_prn_table'";
  RunSQL(szSQL,true);
	while(!dm1->Query1->Eof)
  {
  	szName=dm1->Query1->FieldByName("rd_string")->AsString;
    szSQL.Format("drop table dbo.%s",szName.c_str());
		dm1->db1->Execute((LPCSTR)szSQL,NULL,false,NULL);

    dm1->Query1->Next();
  }
	dm1->db1->Execute("delete RuntimeData where rd_key='tmp_prn_table'",NULL,false,NULL);
*/
}



//http://pjf1225.blog.163.com/blog/static/9394838201122673011501/
