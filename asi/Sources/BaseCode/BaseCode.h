#ifndef  __LAODY_LFC_HONGXINERP_BASECODE__
#define  __LAODY_LFC_HONGXINERP_BASECODE__

#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Db.hpp>
#include <DBTables.hpp>
#include <comctrls.hpp>

#include <vcl.h>
#include "utilcls.h"
#include <stdarg.h>

#include "LfcString.h"
#include "LfcArray_s.h"
#include "LfcTempl.h"

#include "GSLfcBase.h"

#include "GlobalVal.h"

typedef const char* LPCSTR;

#define FLOW_CUT2STORE_IDX		1  //缴库单流水号的索引号
#define FLOW_ORDER_IDX				7	 //订单流水号的索引号
#define FLOW_BURSARMONTH_IDX	8  //会计月份的索引号

#define ITEMSIZE(p) (sizeof(p)/sizeof(p[0]))

int GetFlowNumber(int nIdx,bool bAddFlow=true);
CString GetFlowString(int nIdx);

bool BeginTransact();
bool CommitTransact();
bool RollBackTransact();
bool RunTransactSQL(LPCSTR lpszSQL);

bool OpenQuery(TQuery *pQuery,LPCSTR lpszSQL);
bool OpenTable(TTable *pTable,LPCSTR lpszName,LPCSTR lpszFilter=NULL);
bool RunSQL(LPCSTR lpszSQL,bool bSelect=false);
bool RunSQL(TQuery *pQuery,LPCSTR lpszSQL,bool bSelect=false);
bool RunSQL2(LPCSTR lpszSQL,bool bSelect=false);

bool ExecProc(AnsiString spname, AnsiString in);

bool Get1Field(LPCSTR lpszSQL,LPCSTR lpszField,CStringArray &lstResult);
bool Get1Field(LPCSTR lpszSQL,LPCSTR lpszField,char *pszResult);

void GetSysDate(int &nYear,int &nMonth,int &nDay,bool bCloseDb=true);
TDateTime GetSysTime(bool bCloseDb=true);
//注意返回的日期数据类型为：yyyy-mm-dd
CString GetSysDate(bool bCloseDb=true);
CString GetSysTimeStr();
//获取一个临时表的名称
CString GetTmpTableName();

#endif  //__LAODY_LFC_TAISHUERP_BASECODE__
