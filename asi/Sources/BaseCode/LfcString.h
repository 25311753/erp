#ifndef __Lfc__CString__H__
#define __Lfc__CString__H__

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdarg.h>

#ifndef max
#define max(a,b)            (((a) > (b)) ? (a) : (b))
#endif

#ifndef min
#define min(a,b)            (((a) < (b)) ? (a) : (b))
#endif


//__stdcall  Windows APIÇ»Éø      ½Þ¨Û  UNIX      
#ifdef WIN32
	#define LFCAPI		__stdcall
	#define LFC_CDECL __cdecl
	#define PASCAL    __stdcall
	#define FASTCALL __fastcall
#else
	#define LFCAPI
	#define LFC_CDECL
	#define FASTCALL
#endif

#ifndef PASCAL
	#define PASCAL
#endif

typedef const char* LPCSTR;
typedef char * LPSTR;


typedef int BOOL;
typedef unsigned char       BYTE;
typedef unsigned int        UINT;

#define ASSERT(f)          ((void)0)

struct CStringData
{
	long nRefs;             // reference count
	int nDataLength;        // length of data (including terminator)
	int nAllocLength;       // length of allocation
	// char data[nAllocLength]

	char* data()           // char* to managed data
		{ return (char*)(this+1); }
};


class CString
{
public:
// Constructors

	// constructs empty CLfCString
	CString();
	// copy constructor
	CString(const CString& stringSrc);
	// from a single character
	CString(char ch, int nRepeat = 1);
	// from an ANSI string (converts to char)
	CString(LPCSTR lpsz);
	// subset of characters from an ANSI string (converts to char)
	CString(LPCSTR lpch, int nLength);
	// from unsigned characters
	CString(const unsigned char* psz);

// Attributes & Operations

	// get data length
	int GetLength() const;
	// TRUE if zero length
	BOOL IsEmpty() const;
	// clear contents to empty
	void Empty();

	// return single character at zero-based index
	char GetAt(int nIndex) const;
	// return single character at zero-based index
	char operator[](int nIndex) const;
	// set a single character at zero-based index
	void SetAt(int nIndex, char ch);
	// return pointer to const string
	operator LPCSTR() const;

	// overloaded assignment

	// ref-counted copy from another CString
	const CString& operator=(const CString& stringSrc);
	// set string content to single character
	const CString& operator=(char ch);
	// copy string content from ANSI string (converts to char)
	const CString& operator=(LPCSTR lpsz);
	// copy string content from unsigned chars
	const CString& operator=(const unsigned char* psz);

	// string concatenation

	// concatenate from another CString
	const CString& operator+=(const CString& string);

	// concatenate a single character
	const CString& operator+=(char ch);
	// concatenate a UNICODE character after converting it to char
	const CString& operator+=(LPCSTR lpsz);

	friend CString LFCAPI operator+(const CString& string1,
			const CString& string2);
	friend CString LFCAPI operator+(const CString& string, char ch);
	friend CString LFCAPI operator+(char ch, const CString& string);
	friend CString LFCAPI operator+(const CString& string, LPCSTR lpsz);
	friend CString LFCAPI operator+(LPCSTR lpsz, const CString& string);

	// string comparison

	// straight character comparison
	int Compare(LPCSTR lpsz) const;
	// compare ignoring case
	int CompareNoCase(LPCSTR lpsz) const;
	// NLS aware comparison, case sensitive


	// simple sub-string extraction

	// return nCount characters starting at zero-based nFirst
	CString Mid(int nFirst, int nCount) const;
	// return all characters starting at zero-based nFirst
	CString Mid(int nFirst) const;
	// return first nCount characters in string
	CString Left(int nCount) const;
	// return nCount characters from end of string
	CString Right(int nCount) const;

	//  characters from beginning that are also in passed string
	CString SpanIncluding(LPCSTR lpszCharSet) const;
	// characters from beginning that are not also in passed string
	CString SpanExcluding(LPCSTR lpszCharSet) const;

	// upper/lower/reverse conversion

	// NLS aware conversion to uppercase
	void MakeUpper();
	// NLS aware conversion to lowercase
	void MakeLower();
	// reverse string right-to-left
	void MakeReverse();

	// trimming whitespace (either side)

	// remove whitespace starting from right edge
	void TrimRight();
	// remove whitespace starting from left side
	void TrimLeft();

	// trimming anything (either side)

	// remove continuous occurrences of chTarget starting from right
	void TrimRight(char chTarget);
	// remove continuous occcurrences of characters in passed string,
	// starting from right
	void TrimRight(LPCSTR lpszTargets);
	// remove continuous occurrences of chTarget starting from left
	void TrimLeft(char chTarget);
	// remove continuous occcurrences of characters in
	// passed string, starting from left
	void TrimLeft(LPCSTR lpszTargets);

	// advanced manipulation

	// replace occurrences of chOld with chNew
	int Replace(char chOld, char chNew);
	// replace occurrences of substring lpszOld with lpszNew;
	// empty lpszNew removes instances of lpszOld
	int Replace(LPCSTR lpszOld, LPCSTR lpszNew);
	// remove occurrences of chRemove
	int Remove(char chRemove);
	// insert character at zero-based index; concatenates
	// if index is past end of string
	int Insert(int nIndex, char ch);
	// insert substring at zero-based index; concatenates
	// if index is past end of string
	int Insert(int nIndex, LPCSTR pstr);
	// delete nCount characters starting at zero-based index
	int Delete(int nIndex, int nCount = 1);

	// searching

	// find character starting at left, -1 if not found
	int Find(char ch) const;
	// find character starting at right
	int ReverseFind(char ch) const;
	// find character starting at zero-based index and going right
	int Find(char ch, int nStart) const;
	// find first instance of any character in passed string
	int FindOneOf(LPCSTR lpszCharSet) const;
	// find first instance of substring
	int Find(LPCSTR lpszSub) const;
	// find first instance of substring starting at zero-based index
	int Find(LPCSTR lpszSub, int nStart) const;

	// simple formatting

	// printf-like formatting using passed string
	void LFC_CDECL Format(LPCSTR lpszFormat, ...);
	// printf-like formatting using variable arguments parameter
	void FormatV(LPCSTR lpszFormat, va_list argList);

	// formatting for localization (uses FormatMessage API)

	// input and output
#ifdef _DEBUG
//	friend CDumpContext& LFCAPI operator<<(CDumpContext& dc,const CString& string);
#endif
//	friend CArchive& LFCAPI operator<<(CArchive& ar, const CString& string);
//	friend CArchive& LFCAPI operator>>(CArchive& ar, CString& string);

	// Access to string implementation buffer as "C" character array

	// get pointer to modifiable buffer at least as long as nMinBufLength
	LPSTR GetBuffer(int nMinBufLength);
	// release buffer, setting length to nNewLength (or to first nul if -1)
	void ReleaseBuffer(int nNewLength = -1);
	// get pointer to modifiable buffer exactly as long as nNewLength
	LPSTR GetBufferSetLength(int nNewLength);
	// release memory allocated to but unused by string
	void FreeExtra();

	// Use LockBuffer/UnlockBuffer to turn refcounting off

	// turn refcounting back on
	LPSTR LockBuffer();
	// turn refcounting off
	void UnlockBuffer();

// Implementation
public:
	~CString();
	int GetAllocLength() const;

protected:
	LPSTR m_pchData;   // pointer to ref counted string data

	// implementation helpers
	CStringData* GetData() const;
	void Init();
	void AllocCopy(CString& dest, int nCopyLen, int nCopyIndex, int nExtraLen) const;
	void AllocBuffer(int nLen);
	void AssignCopy(int nSrcLen, LPCSTR lpszSrcData);
	void ConcatCopy(int nSrc1Len, LPCSTR lpszSrc1Data, int nSrc2Len, LPCSTR lpszSrc2Data);
	void ConcatInPlace(int nSrcLen, LPCSTR lpszSrcData);
	void CopyBeforeWrite();
	void AllocBeforeWrite(int nLen);
	void Release();
	static void PASCAL Release(CStringData* pData);
	static int PASCAL SafeStrlen(LPCSTR lpsz);
	static void FASTCALL FreeData(CStringData* pData);

};



// Compare helpers
bool LFCAPI operator==(const CString& s1, const CString& s2);
bool LFCAPI operator==(const CString& s1, LPCSTR s2);
bool LFCAPI operator==(LPCSTR s1, const CString& s2);
bool LFCAPI operator!=(const CString& s1, const CString& s2);
bool LFCAPI operator!=(const CString& s1, LPCSTR s2);
bool LFCAPI operator!=(LPCSTR s1, const CString& s2);
bool LFCAPI operator<(const CString& s1, const CString& s2);
bool LFCAPI operator<(const CString& s1, LPCSTR s2);
bool LFCAPI operator<(LPCSTR s1, const CString& s2);
bool LFCAPI operator>(const CString& s1, const CString& s2);
bool LFCAPI operator>(const CString& s1, LPCSTR s2);
bool LFCAPI operator>(LPCSTR s1, const CString& s2);
bool LFCAPI operator<=(const CString& s1, const CString& s2);
bool LFCAPI operator<=(const CString& s1, LPCSTR s2);
bool LFCAPI operator<=(LPCSTR s1, const CString& s2);
bool LFCAPI operator>=(const CString& s1, const CString& s2);
bool LFCAPI operator>=(const CString& s1, LPCSTR s2);
bool LFCAPI operator>=(LPCSTR s1, const CString& s2);

extern LPCSTR _afxPchNil;
#define afxEmptyString ((CString&)*(CString*)&_afxPchNil)


// CString
inline CStringData* CString::GetData() const
	{ ASSERT(m_pchData != NULL); return ((CStringData*)m_pchData)-1; }
inline void CString::Init()
	{ m_pchData = afxEmptyString.m_pchData; }
inline CString::CString()
	{ m_pchData = afxEmptyString.m_pchData; }
inline CString::CString(const unsigned char* lpsz)
	{ Init(); *this = (LPCSTR)lpsz; }
inline const CString& CString::operator=(const unsigned char* lpsz)
	{ *this = (LPCSTR)lpsz; return *this; }

inline int CString::GetLength() const
	{ return GetData()->nDataLength; }
inline int CString::GetAllocLength() const
	{ return GetData()->nAllocLength; }
inline BOOL CString::IsEmpty() const
	{ return GetData()->nDataLength == 0; }
inline CString::operator LPCSTR() const
	{ return m_pchData; }
inline int PASCAL CString::SafeStrlen(LPCSTR lpsz)
	{ return (lpsz == NULL) ? 0 : strlen(lpsz); }

// CString support (windows specific)
inline int CString::Compare(LPCSTR lpsz) const
	{ ASSERT(AfxIsValidString(lpsz)); return strcmp(m_pchData, lpsz); }    // MBCS/Unicode aware
inline int CString::CompareNoCase(LPCSTR lpsz) const
//#ifdef WIN32
	{ return stricmp(m_pchData, lpsz); }   // MBCS/Unicode aware
//#else
//	{ return strcasecmp(m_pchData, lpsz); }   // MBCS/Unicode aware
//#endif

inline char CString::GetAt(int nIndex) const
{
	ASSERT(nIndex >= 0);
	ASSERT(nIndex < GetData()->nDataLength);
	return m_pchData[nIndex];
}
inline char CString::operator[](int nIndex) const
{
	// same as GetAt
	ASSERT(nIndex >= 0);
	ASSERT(nIndex < GetData()->nDataLength);
	return m_pchData[nIndex];
}
inline bool LFCAPI operator==(const CString& s1, const CString& s2)
	{ return s1.Compare(s2) == 0; }
inline bool LFCAPI operator==(const CString& s1, LPCSTR s2)
	{ return s1.Compare(s2) == 0; }
inline bool LFCAPI operator==(LPCSTR s1, const CString& s2)
	{ return s2.Compare(s1) == 0; }
inline bool LFCAPI operator!=(const CString& s1, const CString& s2)
	{ return s1.Compare(s2) != 0; }
inline bool LFCAPI operator!=(const CString& s1, LPCSTR s2)
	{ return s1.Compare(s2) != 0; }
inline bool LFCAPI operator!=(LPCSTR s1, const CString& s2)
	{ return s2.Compare(s1) != 0; }
inline bool LFCAPI operator<(const CString& s1, const CString& s2)
	{ return s1.Compare(s2) < 0; }
inline bool LFCAPI operator<(const CString& s1, LPCSTR s2)
	{ return s1.Compare(s2) < 0; }
inline bool LFCAPI operator<(LPCSTR s1, const CString& s2)
	{ return s2.Compare(s1) > 0; }
inline bool LFCAPI operator>(const CString& s1, const CString& s2)
	{ return s1.Compare(s2) > 0; }
inline bool LFCAPI operator>(const CString& s1, LPCSTR s2)
	{ return s1.Compare(s2) > 0; }
inline bool LFCAPI operator>(LPCSTR s1, const CString& s2)
	{ return s2.Compare(s1) < 0; }
inline bool LFCAPI operator<=(const CString& s1, const CString& s2)
	{ return s1.Compare(s2) <= 0; }
inline bool LFCAPI operator<=(const CString& s1, LPCSTR s2)
	{ return s1.Compare(s2) <= 0; }
inline bool LFCAPI operator<=(LPCSTR s1, const CString& s2)
	{ return s2.Compare(s1) >= 0; }
inline bool LFCAPI operator>=(const CString& s1, const CString& s2)
	{ return s1.Compare(s2) >= 0; }
inline bool LFCAPI operator>=(const CString& s1, LPCSTR s2)
	{ return s1.Compare(s2) >= 0; }
inline bool LFCAPI operator>=(LPCSTR s1, const CString& s2)
	{ return s2.Compare(s1) <= 0; }


#endif //#define __Lfc__CString__H__

