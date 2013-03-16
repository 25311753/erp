//---------------------------------------------------------------------------
#ifndef CommUnitH
#define CommUnitH
#include <Db.hpp>
#include <DBTables.hpp>
//---------------------------------------------------------------------------
bool  DoQuery(TQuery* pquery, AnsiString strsql, int action=0, bool showdlg=true);//action=0 Open, action=1 ExecSQL
void  WriteLogFile(AnsiString  fname, AnsiString log);
int   ErrorDlg(const char *  msg);
int   InfoDlg(const char *  msg);
int   AskDlg(const char *  msg);
#endif
