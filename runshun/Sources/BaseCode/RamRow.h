#ifndef  __SUNTEK_TELECOM_LAODY_LFC_RAMROW__
#define  __SUNTEK_TELECOM_LAODY_LFC_RAMROW__

#include <dbtables.hpp>

typedef const char* LPCSTR;
typedef unsigned long       DWORD;

#define MEMBER2STRING(row,mem) ((LPCSTR)row.Member2String(row.mem))

class CRamRow
{
public:
	CRamRow();
	~CRamRow();

public:
	bool m_bIsFromDB;
	bool m_bDirtied;

	int m_nFieldLen;
	char m_strSQL[2048];

  void SetAllMemberNULL(bool bNULL=true);
  void SetMemberNotNULL(void *pMember);
  void SetMemberNULL(char *pMember) 		{String2Member(pMember,"");}
  void SetMemberNULL(int &nMember) 			{String2Member(nMember,"");}
  void SetMemberNULL(double &fMember) 		{String2Member(fMember,"");}
  void SetMemberNULL(TDateTime &tMember){String2Member(tMember,"");}

  void SetMemberVal(char *pMember,LPCSTR lpszVal);
  void SetMemberVal(int &nMember,int nVal);
  void SetMemberVal(double &fMember,double fVal);
  void SetMemberVal(TDateTime &tMember,const TDateTime &tVal);

	void ReadMember(char *pMember,	TField *pField);
	void ReadMember(int &nMember,		TField *pField);
	void ReadMember(double &fMember,	TField *pField);
	void ReadMember(TDateTime &tMember,	TField *pField);

	CString Member2String(char *pMember);
	CString Member2String(int &nMember);
	CString Member2String(double &fMember,int nPrec=1); //nPrec精确到小数几位
  CString Member2String(TDateTime &tMember);

	void String2Member(char *pMember,char *pszString);
	void String2Member(int &nMember,char *pszString);
	void String2Member(double &fMember,char *pszString);

//注意输入日期的数据类型为：yyyymmdd，中间没有-号
	void String2Member(TDateTime &tMember,char *pszString);

  bool MemberIsNull(TDateTime &tMember);

  CString Member2DBString(char *pMember);
  CString Member2DBString(int &nMember);
  CString Member2DBString(double &fMember,int nPrec=1);
  CString Member2DBString(TDateTime &tMember,bool bDate=false);

	bool FieldIsNull(void *pMember,TField *pField);
	bool MemberIsNull(void *pMember);
	void SetMemberField(void *pMember,int nField);

	void SetMemberField(char *pMember,int nField)  {SetMemberField((void*)pMember,nField);}
	void SetMemberField(int &nMember,int nField)   {SetMemberField((void*)&nMember,nField);}
	void SetMemberField(double &fMember,int nField) {SetMemberField((void*)&fMember,nField);}
	void SetMemberField(TDateTime &tMember,int nField) {SetMemberField((void*)&tMember,nField);}

	void InitMemberField(char *pMember);
	void InitMemberField(int &nMember);
	void InitMemberField(double &fMember);
	void InitMemberField(TDateTime &tMember);

  int GetMemberIdx(void *pMember);
protected:
	void *m_aField[500];
	char m_aNull[500];
};

#endif  //__SUNTEK_TELECOM_LAODY_LFC_RAMROW__