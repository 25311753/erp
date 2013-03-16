//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "CommUnit.h"
#include "Tconst.h"
#include "DataModule.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------

bool  DoQuery(TQuery* pquery, AnsiString strsql, int action, bool showdlg)
{
   AnsiString  log;
   try
   {
      pquery->Close();
      pquery->SQL->Clear();
      pquery->SQL->Text=strsql;
      pquery->Prepare();
      if (action)
         pquery->ExecSQL();
      else
         pquery->Open();
   }
   catch(Exception &e)
   {
      log = sysdate+" "+systime+" error:"+e.Message+"\r\n"+"sql:"+strsql;
      WriteLogFile("error.log",log);
      //if (showdlg)
      //   ErrorDlg("数据库错误!");
      return false;
   }
   return true;
}
//---------------------------------------------------------------------------

void  WriteLogFile(AnsiString  fname, AnsiString log)
{
   int iFileHandle;
   int iFileLength;
   char *pszBuffer;

   if (FileExists(fname))
   {
      iFileHandle = FileOpen(fname,fmOpenReadWrite);
      iFileLength = FileSeek(iFileHandle,0,2);
      if (iFileLength>65536)
      {  //if filelength>64k then delete prehalf file.
         pszBuffer = new char[iFileLength/2+1];
         FileSeek(iFileHandle,iFileLength/2,2);
         FileRead(iFileHandle, pszBuffer,iFileLength/2);
         FileClose(iFileHandle);
         DeleteFile(fname);
         iFileHandle = FileCreate(fname);
         FileWrite(iFileHandle,pszBuffer,iFileLength/2);
      }
      FileWrite(iFileHandle,log.c_str(),log.Length());
   }
   else
   {
      iFileHandle = FileCreate(fname);
      FileWrite(iFileHandle,log.c_str(),log.Length());
   }
   FileClose(iFileHandle);
}
//---------------------------------------------------------------------------

int  ErrorDlg(const char *  msg)
{
   return Application->MessageBox(msg,"错误",MB_OK+MB_ICONERROR);
}
//---------------------------------------------------------------------------

int  InfoDlg(const char *  msg)
{
   return Application->MessageBox(msg,"系统提示",MB_OK+MB_ICONINFORMATION);
}
//---------------------------------------------------------------------------

int  AskDlg(const char *  msg)
{
   return Application->MessageBox(msg,"系统提示",MB_YESNO+MB_ICONQUESTION);
}
//---------------------------------------------------------------------------

