
#include <stdio.h>
#include <math.h>
#include "BaseCode.h"
#include "DataModule.h"
#include "TConst.h"


bool BeginTransact()
{
	if(dm1->db1->InTransaction)	return false;
  dm1->db1->StartTransaction();
	return true;
}

bool CommitTransact()
{
	if(!dm1->db1->InTransaction)	return false;
  dm1->db1->Commit();
  return true;
}

bool RollBackTransact()
{
	if(!dm1->db1->InTransaction)	return false;
  dm1->db1->Rollback();
  return true;
}

bool RunTransactSQL(LPCSTR lpszSQL)
{
	if(!dm1->db1->InTransaction)
  {
  	ShowMessage("program not in transaction!");
		return false;
  }
	dm1->db1->Execute(lpszSQL,NULL,false,NULL);
	return true;
}

int GetFlowNumber(int nIdx,bool bAddFlow)
{
	int nFlow;
  char strSQL[1024];
  if(!dm1->OpenDatabase())	return 0;
	sprintf(strSQL,"select fn_no from flowno where fn_idx=%d",nIdx);
	RunSQL(strSQL,true);
  if(dm1->Query1->Eof)	return 0;
  nFlow=dm1->Query1->FieldByName("fn_no")->AsInteger;
  if(bAddFlow)
  {
  	sprintf(strSQL,"update flowno set fn_no=fn_no+1 where fn_idx=%d",nIdx);
		RunSQL(strSQL);
  }
  return nFlow;
}

CString GetFlowString(int nIdx)
{
	CString szFlow;
  char strSQL[1024];
  if(!dm1->OpenDatabase())	return "";
	sprintf(strSQL,"select fn_sno from flowno where fn_idx=%d",nIdx);
	RunSQL(strSQL,true);
  if(dm1->Query1->Eof)	return "";
  szFlow=dm1->Query1->FieldByName("fn_sno")->AsString.c_str();
  return szFlow;
}

bool OpenQuery(TQuery *pQuery,LPCSTR lpszSQL)
{
	AnsiString szMsg;
  if(!dm1->OpenDatabase())  return false;

  try
  {
    pQuery->Close();
    pQuery->SQL->Clear();
    pQuery->SQL->Add(lpszSQL);
    pQuery->Prepare();
    pQuery->Open();
  }
  catch(...)
  {
  	szMsg="数据库操作失败\nSQL="+AnsiString(lpszSQL);
    ShowMessage(szMsg);
    return false;
  }
  return true;
}

bool OpenTable(TTable *pTable,LPCSTR lpszName,LPCSTR lpszFilter)
{
	AnsiString szMsg;
  if(!dm1->OpenDatabase())  return false;

  try
  {
  	pTable->Active=false;
    pTable->TableName=lpszName;
    if(lpszFilter!=NULL && lpszFilter[0]!='\0')
    {
    	pTable->Filter=lpszFilter;
      pTable->Filtered=true;
    }
    pTable->Active=true;
    if(pTable->Eof)	return false;
  }
  catch(...)
  {
  	szMsg="数据库操作失败\nTable="+AnsiString(lpszName);
    ShowMessage(szMsg);
    return false;
  }
  return true;
}

bool RunSQL(TQuery *pQuery,LPCSTR lpszSQL,bool bSelect)
{
  if(!dm1->OpenDatabase())  return false;

  try
  {
    pQuery->Close();
    pQuery->SQL->Clear();
    pQuery->SQL->Add(lpszSQL);
    pQuery->Prepare();
    if(bSelect)
      pQuery->Open();
    else
      pQuery->ExecSQL();
  }
  catch(...)
  {
//  	AnsiString szMsg="数据库操作失败\nSQL="+AnsiString(lpszSQL);
        AnsiString szMsg="数据库操作失败\n";
        ShowMessage(szMsg);
        return false;
  }
  return true;
}

bool RunSQL(LPCSTR lpszSQL,bool bSelect)
{
  if(!dm1->OpenDatabase())  return false;

  try
  {
    dm1->Query1->Close();
    dm1->Query1->SQL->Clear();
    dm1->Query1->SQL->Add(lpszSQL);
    dm1->Query1->Prepare();
    if(bSelect)
      dm1->Query1->Open();
    else
      dm1->Query1->ExecSQL();
  }
  catch(...)
  {
//  	AnsiString szMsg="数据库操作失败\nSQL="+AnsiString(lpszSQL);
        AnsiString szMsg="数据库操作失败\n";
    ShowMessage(szMsg);
    return false;
  }
  return true;
}

bool RunSQL2(LPCSTR lpszSQL,bool bSelect)
{
  if(!dm1->OpenDatabase())  return false;

  try
  {
    dm1->Query2->Close();
    dm1->Query2->SQL->Clear();
    dm1->Query2->SQL->Add(lpszSQL);
    dm1->Query2->Prepare();
    if(bSelect)
      dm1->Query2->Open();
    else
      dm1->Query2->ExecSQL();
  }
  catch(...)
  {
//  	AnsiString szMsg="数据库操作失败\nSQL="+AnsiString(lpszSQL);
        AnsiString szMsg="数据库操作失败\n";
    ShowMessage(szMsg);
    return false;
  }
  return true;
}

bool ExecProc(AnsiString spname, AnsiString in){
  if(!dm1->OpenDatabase())  return false;
  try
  {
    AnsiString in_parm_tmp = "x";
    dm1->SPcomn->Close();
    dm1->SPcomn->StoredProcName=spname;
    dm1->SPcomn->Params->Clear();
//    dm1->SPcomn->Params->CreateParam(ftInteger, in_parm_tmp, ptInput);
    dm1->SPcomn->Params->CreateParam(ftString, in_parm_tmp, ptInput);
    dm1->SPcomn->ParamByName(in_parm_tmp)->AsString = in;
    dm1->SPcomn->Prepare();
    dm1->SPcomn->ExecProc();
    dm1->SPcomn->Close();

  }
  catch(...)
  {
  	ShowMessage("exec proc fail");
        return false;
  }
  return true;
}

bool Get1Field(LPCSTR lpszSQL,LPCSTR lpszField,char *pszResult)
{
  if(!dm1->OpenDatabase()) return false;
  bool bResult=false;

  try
  {
    dm1->Query1->Close();
    dm1->Query1->SQL->Clear();
    dm1->Query1->SQL->Add(lpszSQL);
    dm1->Query1->Prepare();
    dm1->Query1->Open();
    dm1->Query1->First();
    if(!dm1->Query1->Eof)
    {
      strcpy(pszResult,dm1->Query1->FieldByName(lpszField)->AsString.c_str());
      bResult=true;
    }
  }
  catch(...)
  {
    ShowMessage("数据库操作错误");
    return false;
  }
  return bResult;
}


bool Get1Field(LPCSTR lpszSQL,LPCSTR lpszField,CStringArray &lstResult)
{
  if(!dm1->OpenDatabase()) return false;

  lstResult.RemoveAll();

  try
  {
  	if(!RunSQL(lpszSQL,true))	return false;
    while(!dm1->Query1->Eof)
    {
    	lstResult.Add(dm1->Query1->FieldByName(lpszField)->AsString.c_str());
      dm1->Query1->Next();
    }
  }
  catch(...)
  {
    ShowMessage("数据库操作错误");
    return false;
  }
  return true;
}
//---------------------------------------------------------------------------

TDateTime GetSysTime(bool bCloseDb)
{
	bool bDbSuccess=false;
	char strSQL[256];
	TDateTime tDate;

 	if(!dm1->db1->InTransaction)
  {
		try
		{
			if(dm1->OpenDatabase())
  	  {
				sprintf(strSQL,"select getdate() as systime");
				RunSQL(strSQL,true);
				if(!dm1->Query1->Eof)
				{
      		tDate=dm1->Query1->FieldByName("systime")->AsDateTime;
		    }

				bDbSuccess=true;
				return tDate;
			}
	  }
		catch(...)
		{
			if(dm1->db1->Connected)
    	{
  	  }
    }
	}

	if(!bDbSuccess)
	{
    tDate=TDateTime::CurrentDate();
	}
  return tDate;
}

void GetSysDate(int &nYear,int &nMonth,int &nDay,bool bCloseDb)
{
  TDateTime tDate=GetSysTime(bCloseDb);
  unsigned short year,month,day;

  tDate.DecodeDate(&year,&month,&day);
  nYear =year;
  nMonth=month;
  nDay  =day;
}

CString GetSysDate(bool bCloseDb)
{
  int nYear,nMonth,nDay;
  char strDate[80];
  GetSysDate(nYear,nMonth,nDay,bCloseDb);
  sprintf(strDate,"%04d-%02d-%02d",nYear,nMonth,nDay);
  return CString(strDate);
}

CString GetSysTimeStr(){
  unsigned short year,month,day,h,m,s,u;
  
  char strDate[80];
  TDateTime tDate=GetSysTime(true);
  tDate.DecodeDate(&year,&month,&day);
  tDate.DecodeTime(&h, &m, &s, &u);
  sprintf(strDate,"%04d-%02d-%02d %02d:%02d:%02d",year,month,day,h,m,s);
  return CString(strDate);

}


//获取一个临时表的名称
//由於查询一个表是否存在需要查询系统表，这样要求程序必须有很高的权限
//为了简单，只从当前时间拼凑名称
CString GetTmpTableName()
{
	char strTemp[256],strSQL[1024];
  unsigned short hour,min,sec,msec,year,month,day;
  TDateTime tNow=TDateTime::CurrentDateTime();
  static int gnCount=0;

  tNow.DecodeDate(&year,&month,&day);
	tNow.DecodeTime(&hour,&min,&sec,&msec);
 	sprintf(strTemp,"tmp_prn_%02d%02d%02d%02d%02d%02d%s",month,day,hour,min,sec,gnCount++,operatorcode.c_str());
// 	sprintf(strTemp,"#%02d%02d%02d%02d%02d%02d%s",month,day,hour,min,sec,gnCount++,operatorcode.c_str());
  if(gnCount>99)	gnCount=0;

  return CString(strTemp);
}


