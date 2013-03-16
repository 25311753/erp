#ifndef ComVarH
#define ComVarH
AnsiString  corpcode; //¹«Ë¾±ð
AnsiString  operatorcode,operatorname,operator_class;
AnsiString  sysdate, systime;
//---------------------------------------------------------------------------
void  WriteInfoFile(AnsiString  fname, AnsiString info)
{
   int iFileHandle;
   int iFileLength;

   if (FileExists(fname))
   {
      //FileClose(iFileHandle);
      DeleteFile(fname);
      iFileHandle = FileCreate(fname);
      FileWrite(iFileHandle,info.c_str(),info.Length());
   }
   else
   {
      iFileHandle = FileCreate(fname);
      FileWrite(iFileHandle,info.c_str(),info.Length());
   }
   FileClose(iFileHandle);
}
//---------------------------------------------------------------------------
AnsiString  ReadInfoFile(AnsiString  fname)
{
   AnsiString info;
   int iFileHandle;
   int iFileLength;
   char *pszBuffer;

   if (FileExists(fname))
   {
      iFileHandle = FileOpen(fname,fmOpenRead);
      iFileLength = FileSeek(iFileHandle,0,2);
      pszBuffer = new char[iFileLength+1];
      FileSeek(iFileHandle,0,0);
      FileRead(iFileHandle, pszBuffer, iFileLength);
      FileClose(iFileHandle);
      info = pszBuffer;
      delete [] pszBuffer;
   }
   else
      info="notexist";
   return info;
}
//---------------------------------------------------------------------------
#endif
