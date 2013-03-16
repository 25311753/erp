#ifndef __LFC__CSTRINGARRAY__H__
#define __LFC__CSTRINGARRAY__H__

#include "LfcString.h"

class CStringArray
{

//	DECLARE_SERIAL(CStringArray)
public:

// Construction
	CStringArray();

// Attributes
	int GetSize() const;
	int GetUpperBound() const;
	void SetSize(int nNewSize, int nGrowBy = -1);

// Operations
	// Clean up
	void FreeExtra();
	void RemoveAll();

	// Accessing elements
	CString GetAt(int nIndex) const;
	void SetAt(int nIndex, LPCSTR newElement);

	void SetAt(int nIndex, const CString& newElement);

	CString& ElementAt(int nIndex);

	// Direct Access to the element data (may return NULL)
	const CString* GetData() const;
	CString* GetData();

	// Potentially growing the array
	void SetAtGrow(int nIndex, LPCSTR newElement);

	void SetAtGrow(int nIndex, const CString& newElement);

	int Add(LPCSTR newElement);

	int Add(const CString& newElement);

	int Append(const CStringArray& src);
	void Copy(const CStringArray& src);

	// overloaded operator helpers
	CString operator[](int nIndex) const;
	CString& operator[](int nIndex);

	// Operations that move elements around
	void InsertAt(int nIndex, LPCSTR newElement, int nCount = 1);

	void InsertAt(int nIndex, const CString& newElement, int nCount = 1);

	void RemoveAt(int nIndex, int nCount = 1);
	void InsertAt(int nStartIndex, CStringArray* pNewArray);

// Implementation
protected:
	CString* m_pData;   // the actual array of data
	int m_nSize;     // # of elements (upperBound - 1)
	int m_nMaxSize;  // max allocated
	int m_nGrowBy;   // grow amount

	void InsertEmpty(int nIndex, int nCount);


public:
	~CStringArray();

//	void Serialize(CArchive&);
//#ifdef _DEBUG
//	void Dump(CDumpContext&) const;
//	void AssertValid() const;
//#endif

protected:
	// local typedefs for class templates
	typedef CString BASE_TYPE;
	typedef LPCSTR BASE_ARG_TYPE;
};


inline int CStringArray::GetSize() const
	{ return m_nSize; }
inline int CStringArray::GetUpperBound() const
	{ return m_nSize-1; }
inline void CStringArray::RemoveAll()
	{ SetSize(0); }
inline CString CStringArray::GetAt(int nIndex) const
	{ ASSERT(nIndex >= 0 && nIndex < m_nSize);
		return m_pData[nIndex]; }
inline void CStringArray::SetAt(int nIndex, LPCSTR newElement)
	{ ASSERT(nIndex >= 0 && nIndex < m_nSize);
		m_pData[nIndex] = newElement; }

inline void CStringArray::SetAt(int nIndex, const CString& newElement)
	{ ASSERT(nIndex >= 0 && nIndex < m_nSize);
		m_pData[nIndex] = newElement; }

inline CString& CStringArray::ElementAt(int nIndex)
	{ ASSERT(nIndex >= 0 && nIndex < m_nSize);
		return m_pData[nIndex]; }
inline const CString* CStringArray::GetData() const
	{ return (const CString*)m_pData; }
inline CString* CStringArray::GetData()
	{ return (CString*)m_pData; }
inline int CStringArray::Add(LPCSTR newElement)
	{ int nIndex = m_nSize;
		SetAtGrow(nIndex, newElement);
		return nIndex; }

inline int CStringArray::Add(const CString& newElement)
	{ int nIndex = m_nSize;
		SetAtGrow(nIndex, newElement);
		return nIndex; }

inline CString CStringArray::operator[](int nIndex) const
	{ return GetAt(nIndex); }
inline CString& CStringArray::operator[](int nIndex)
	{ return ElementAt(nIndex); }


#endif //__LFC__CSTRINGARRAY__H__