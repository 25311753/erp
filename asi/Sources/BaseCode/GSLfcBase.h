#ifndef  __LAODY_LFC_GRACESTOCK_GSLFCLIB__
#define  __LAODY_LFC_GRACESTOCK_GSLFCLIB__

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

typedef const char* LPCSTR;

bool IsDateNULL(TDateTime &tDate);
bool IsDateFieldNULL(TField *pField);

//把字符串中的空格替换为0，用这个函数是因为sprintf不能补0
CString ReplaceSpaceTo0(LPCSTR lpszString);

void EnableEdit(TEdit *pEdit,bool bEnable=true);
void EnableCombo(TComboBox *pBox,bool bEnable=true);

//把 yyyymmdd 类型的日期转换为 yyyy-mm-dd 类型的数据库日期
void Date2Dbdate(LPCSTR lpszIn,char *pszOut);
//把 yyyymmdd 类型的日期转换为年月日数据
void Date2YYMMDD(LPCSTR lpszIn,int &nYear,int &nMon,int &nDay);
TDateTime YYMMDD2Date(LPCSTR lpszDate);
//把 TDateTime转换为yyyymmdd类型字符串
CString Date2YYMMDD(TDateTime tDate);

//把 TDateTime 数据转换成数据库的“yyyy-mm-dd”日期字符串，注意两边没有单引号
CString Time2DBDateString(const TDateTime &tTime);
//把 TDateTime 数据转换成数据库的“yyyy-mm-dd hh:MM:ss”日期字符串，注意两边没有单引号
CString Time2DBTimeString(const TDateTime &tTime);

void TrimLeft(char *pszString);
void TrimRight(char *pszString);
bool HasSpaceInString(LPCSTR lpszString);
bool StringIsInt(LPCSTR lpszString);
bool StringIsFloat(LPCSTR lpszString);

//重量计算,重量（Kg）=厚度(u)*宽度(mm)*长度(M)*10^-6*0.907*支数
//输入参数：厚度(u)、宽度(mm)、长度(M)、支数
//返回重量(Kg)，重量是一位小数
double CalcWeight(double fThick,int nWidth,int nLength,int nBunch=1);

//计算支数，支数=重量/(厚度(u)*宽度(mm)*长度(M)*1e-6*0.907)
//输入参数：厚度(u)、宽度(mm)、长度(M)、重量(Kg)
//返回支数，结果是整数，四舍五入，如果小於1则返回1
int CalcBunch(double fThick,int nWidth,int nLength,double fWeight);

void KeyReturnHandle(TWinControl *ActiveControl);
void EditorKeyMaxLenHandle(TWinControl *ActiveControl,WORD Key);
void EditorArrowHandle(TWinControl *ActiveControl,WORD Key);

//给数字加上逗号
CString AddComma(LPCSTR lpszSrc);

// 转 Excel 操作接口
bool OpenExcel(LPCSTR lpszFName,Variant &vExcel,Variant &vSheet);
void InsertExcelItem(Variant &vSheet,int nLine,...);
void CloseExcel(Variant &vExcel);
void SetExcelColumnWidth(Variant &vExcel,int nColumn,int nWidth);
void ListHead2Excel(TListView *pList,Variant &vSheet,int nLine);

//将输入字符串中的单引号处理成数据库能接受的形式
CString ReplaceSingleQuote(LPCSTR lpszSrc);

AnsiString Text2DBString(AnsiString szText);
AnsiString Text2DBDate(AnsiString szText);
AnsiString Text2DBInt(AnsiString szText);
AnsiString Text2DBFloat(AnsiString szText,int nPrec=1);

CString Str2DBString	(LPCSTR lpszText);
CString Int2DBString	(int nVal);
CString Float2DBString(double fVal,int nPrec=1);

AnsiString StringField2Text(TField *pField);
AnsiString DateField2Text(TField *pField);
AnsiString IntField2Text(TField *pField);
AnsiString FloatField2Text(TField *pField);

AnsiString Field2DateString(TField *pField);
AnsiString Field2TimeString(TField *pField);

// 重量转换公式
double LB2KG(double fLB);
double Metre2KG(double fThick,double fWidth,double fLength,double fProp=0);
double YD2KG(double fThick,double fWidth,double fYD,double fProp=0);
double MM2KG(double fThick,double fWidth,double fMM,double fProp=0);

AnsiString IntField2String(TField *pField);
AnsiString FloatField2String(TField *pField,int nPrec=1);

typedef struct _ntime_row
{
	char 	dn_code[80];
  int		dn_type;
  char  dn_name[80];
} NTIME_ROW;
//利用二分法快速查找非生产时间类型
int GetNTimePos(LPCSTR lpszID,CArray<NTIME_ROW,NTIME_ROW>&lstData);

typedef struct _base_2coldata
{
	char strCode[80];
  char strName[256];
} BASE2COLDATA;

typedef struct _base_4coldata
{
	char strCode[80];
  char strName[256];
	char strCol2[256];
	char strCol3[256];
} BASE4COLDATA;

//利用二分法快速查找
int SearchBaseDataPos(LPCSTR lpszID,CArray<BASE2COLDATA,BASE2COLDATA>&lstData);

//把输入字符串中用回车符分隔的字符串提取出来，保存到lstResult中
void SplitLine(LPCSTR lpszData,CStringArray &lstResult);
void SplitString(LPCSTR lpszSrc,CStringArray &lstResult,char cSplit);

CString SimpleEncode(LPCSTR lpszSrc);
CString SimpleDecode(LPCSTR lpszSrc);

//把一字符串分解成多行,width 为每行字数
int SplitStrToLines(LPCSTR lpszSrc,int nWidth,CStringArray &lstLine);

bool CheckDateEditor(TEdit *pEdit);
bool CheckFloatEditor(TEdit *pEdit,bool bAllowEmpty=false);
bool CheckIntEditor(TEdit *pEdit,bool bAllowEmpty=false);

void HandleListboxExit(TComboBox *pBox,CStringArray *plstID);

#endif  //__LAODY_LFC_GRACESTOCK_GSLFCLIB__