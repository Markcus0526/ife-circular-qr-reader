// include base header
#ifndef __PAGEOCR_DEFINE__
#define __PAGEOCR_DEFINE__

#define _LINUX
#include <dirent.h>

#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <errno.h>
#include <fnmatch.h>
#include <sys/types.h>
#include <sys/stat.h>


#ifndef ANDROID
	#define	ANDROID
#endif

//Define Base Data Type
#define lstrlen strlen
#define lstrcpy strcpy
#define TCHAR char
#define LPCTSTR TCHAR*
#define LPCSTR char*
#define LPTSTR TCHAR*
#define LPSTR char*
#define WCHAR unsigned short   // wc,   16-bit UNICODE character
#define PWCHAR WCHAR*
#define LPWCH WCHAR*
#define PWCH WCHAR*
#define LPCWCH WCHAR*
#define PCWCH WCHAR*
#define NWPSTR WCHAR*
#define LPWSTR WCHAR*
#define PWSTR WCHAR*
#define UINT unsigned int
#define LPCWSTR WCHAR*
#define PCWSTR WCHAR*
typedef unsigned short WORD;
#define LPWORD	WORD*
#define DWORD	unsigned int
#define LPCVOID	void*
//typedef unsigned int HANDLE;
#define LONGLONG __int64
#define LRESULT DWORD
#define WPARAM DWORD
#define LPARAM DWORD
#define VOID void
#define LPVOID void*
#define HBRUSH DWORD
#define LONG long
typedef unsigned char BYTE;
//typedef char _TSCHAR;
#define LPBYTE BYTE*

//Define Base Value
#define WM_USER QEvent::User
#define true 			1
#define false 			0
#define LF_FACECString         	32
#define USER_LITTLE_ENDIAN
#define MAX_PATH 256
#define _MAX_DRIVE  		3
#define _MAX_DIR  		256
#define _MAX_FNAME		64
#define _MAX_EXT		256
#define SpaceTwo	0xA1A1
#define SpaceOne	0x20
#define MB_OK                   0
#define MB_OKCANCEL             1
#define MB_ABORTRETRYIGNORE     2
#define MB_YESNOCANCEL          3
#define MB_YESNO                4
#define MB_RETRYCANCEL          5
#define IDOK		QMessageBox::Ok
#define IDCANCEL	QMessageBox::Cancel
#define IDYES		QMessageBox::Yes
#define IDNO		QMessageBox::No
#define IDCANCEL	QMessageBox::Cancel
#define hFileNull NULL

//Define Base Operation
#define max(a,b)            (((a) > (b)) ? (a) : (b))
#define min(a,b)            (((a) < (b)) ? (a) : (b))

#define MAKEWORD(a, b)      ((WORD)(((BYTE)(a)) | ((WORD)((BYTE)(b))) << 8))
#define MAKELONG(a, b)      ((LONG)(((WORD)(a)) | ((DWORD)((WORD)(b))) << 16))
#define LOWORD(l)           ((WORD)(l))
#define HIWORD(l)           ((WORD)(((DWORD)(l) >> 16) & 0xFFFF))
#define LOBYTE(w)           ((BYTE)(w))
#define HIBYTE(w)	    ((BYTE)(((WORD)(w) >> 8) & 0xFF))

#undef	ASSERT
#define ASSERT(a) 		assert(a)
#define ASSERT_VALID(a)
#define ASSERT_KINDOF(a,b)

#define _KoreanStr(x) QString::fromLocal8Bit(x)
#define _T(x)       x

#define		BLACK_OBJ		0	
#define		WHITE_OBJ		255 
#define		CAR_TYPE0		0	
#define		CAR_TYPE1		1

#define stricmp strcasecmp
//Define Base Class
// predeclearation

class CPoint;
class CSize;
class CRect;

typedef struct tagSIZE
{
	int cx;
	int cy;
} SIZE;
typedef struct tagPOINT
{
	int x;
	int y;
} POINT;

typedef struct tagRECT
{
	int left;
	int top;
	int right;
	int bottom;
} RECT;

typedef struct tagBITMAPINFOHEADER
{
	DWORD      biSize; 
	LONG       biWidth;
	LONG       biHeight;
	WORD       biPlanes;
	WORD       biBitCount;
	DWORD      biCompression;
	DWORD      biSizeImage;
	LONG       biXPelsPerMeter;
	LONG       biYPelsPerMeter;
	DWORD      biClrUsed;
	DWORD      biClrImportant;
} BITMAPINFOHEADER, *LPBITMAPINFOHEADER, *PBITMAPINFOHEADER;

typedef struct tagBITMAPFILEHEADER
{
	WORD    bfType;
	DWORD   bfSize;
	WORD    bfReserved1;
	WORD    bfReserved2;
	DWORD   bfOffBits;
} BITMAPFILEHEADER, *LPBITMAPFILEHEADER, *PBITMAPFILEHEADER;

typedef struct tagRGBQUAD
{
	BYTE rgbBlue;
	BYTE rgbGreen;
	BYTE rgbRed;
	BYTE rgbReserved;
} RGBQUAD;

typedef struct tagBITMAPINFO
{
	BITMAPINFOHEADER    bmiHeader;
	RGBQUAD             bmiColors[1];
} BITMAPINFO, *LPBITMAPINFO, *PBITMAPINFO;

//typedef const RECT*	LPRECT;
typedef RECT*	LPRECT;



class CSize : public tagSIZE
{
public:

// Constructors
	// construct an uninitialized size
	CSize();
	// create from two integers
	CSize(int initCX, int initCY);
	// create from another size
	CSize(SIZE initSize);
	// create from a point
	CSize(POINT initPt);
	// create from a DWORD: cx = LOWORD(dw) cy = HIWORD(dw)
	CSize(DWORD dwSize);

// Operations
	bool operator==(SIZE size) const;
	bool operator!=(SIZE size) const;
	void operator+=(SIZE size);
	void operator-=(SIZE size);

// Operators returning CSize values
	CSize operator+(SIZE size) const;
	CSize operator-(SIZE size) const;
	CSize operator-() const;

// Operators returning CPoint values
	CPoint operator+(POINT point) const;
	CPoint operator-(POINT point) const;

// Operators returning CRect values
	CRect operator+(const RECT* lpRect) const;
	CRect operator-(const RECT* lpRect) const;
};

class CPoint : public tagPOINT
{
public:
// Constructors

	// create an uninitialized point
	CPoint();
	// create from two integers
	CPoint(int initX, int initY);
	// create from another point
	CPoint(POINT initPt);
	// create from a size
	CPoint(SIZE initSize);
	// create from a dword: x = LOWORD(dw) y = HIWORD(dw)
	CPoint(DWORD dwPoint);

// Operations

// translate the point
	void Offset(int xOffset, int yOffset);
	void Offset(POINT point);
	void Offset(SIZE size);

	bool operator==(POINT point) const;
	bool operator!=(POINT point) const;
	void operator+=(SIZE size);
	void operator-=(SIZE size);
	void operator+=(POINT point);
	void operator-=(POINT point);

// Operators returning CPoint values
	CPoint operator+(SIZE size) const;
	CPoint operator-(SIZE size) const;
	CPoint operator-() const;
	CPoint operator+(POINT point) const;

// Operators returning CSize values
	SIZE operator-(POINT point) const;

// Operators returning CRect values
	CRect operator+(const RECT* lpRect) const;
	CRect operator-(const RECT* lpRect) const;
};

class CRect : public tagRECT
{
public:

// Constructors

	// uninitialized rectangle
	CRect();
	// from left, top, right, and bottom
	CRect(int l, int t, int r, int b);
	// copy constructor
	CRect(const RECT& srcRect);
	// from a pointer to another rect
	CRect(LPRECT lpSrcRect);
	// from a point and size
	CRect(POINT point, SIZE size);
	// from two points
	CRect(POINT topLeft, POINT bottomRight);

// Attributes (in addition to RECT members)

	// retrieves the width
	int Width() const;
	// returns the height
	int Height() const;
	// returns the size
	CSize Size() const;
	// reference to the top-left point
	CPoint TopLeft();
	// reference to the bottom-right point
	CPoint BottomRight();
	// const reference to the top-left point
	const CPoint TopLeft() const;
	// const reference to the bottom-right point
	const CPoint BottomRight() const;
	// the geometric center point of the rectangle
	CPoint CenterPoint() const;
	// swap the left and right
	void SwapLeftRight();
	static void SwapLeftRight(LPRECT lpRect);

	// convert between CRect and LPrRECT/LPRECT (no need for &)
	operator LPRECT();
	operator LPRECT() const;

	// returns true if rectangle has no area
	bool IsRectEmpty() const;
	// returns true if rectangle is at (0,0) and has no area
	bool IsRectNull() const;
	// returns true if point is within rectangle
	bool PtInRect(POINT point) const;

	// Operations

	// set rectangle from left, top, right, and bottom
	void SetRect(int x1, int y1, int x2, int y2);
	void SetRect(POINT topLeft, POINT bottomRight);
	// empty the rectangle
	void SetRectEmpty();
	// copy from another rectangle
	void CopyRect(LPRECT lpSrcRect);
	// true if exactly the same as another rectangle
	bool EqualRect(LPRECT lpRect) const;

	// inflate rectangle's width and height without
	// moving its top or left
	void InflateRect(int x, int y);
	void InflateRect(SIZE size);
	void InflateRect(LPRECT lpRect);
	void InflateRect(int l, int t, int r, int b);
	// deflate the rectangle's width and height without
	// moving its top or left
	void DeflateRect(int x, int y);
	void DeflateRect(SIZE size);
	void DeflateRect(LPRECT lpRect);
	void DeflateRect(int l, int t, int r, int b);

	// translate the rectangle by moving its top and left
	void OffsetRect(int x, int y);
	void OffsetRect(SIZE size);
	void OffsetRect(POINT point);
	void NormalizeRect();

	// set this rectangle to intersection of two others
	bool IntersectRect(LPRECT lpRect1, LPRECT lpRect2);

	// set this rectangle to bounding union of two others
	bool UnionRect(LPRECT lpRect1, LPRECT lpRect2);

	// set this rectangle to minimum of two others
	bool SubtractRect(LPRECT lpRectSrc1, LPRECT lpRectSrc2);

// Additional Operations
	void operator=(const RECT& srcRect);
	bool operator==(const RECT& rect) const;
	bool operator!=(const RECT& rect) const;
	void operator+=(POINT point);
	void operator+=(SIZE size);
	void operator+=(LPRECT lpRect);
	void operator-=(POINT point);
	void operator-=(SIZE size);
	void operator-=(LPRECT lpRect);
	void operator&=(const RECT& rect);
	void operator|=(const RECT& rect);

// Operators returning CRect values
	CRect operator+(POINT point) const;
	CRect operator-(POINT point) const;
	CRect operator+(LPRECT lpRect) const;
	CRect operator+(SIZE size) const;
	CRect operator-(SIZE size) const;
	CRect operator-(LPRECT lpRect) const;
	CRect operator&(const RECT& rect2) const;
	CRect operator|(const RECT& rect2) const;
	CRect MulDiv(int nMultiplier, int nDivisor) const;
};

template<class TYPE> void CopyElements(TYPE* pDest, const TYPE* pSrc, int nCount);
template<class TYPE> void DestructElements(TYPE* pElements, int nCount);
template<class TYPE> void ConstructElements(TYPE* pElements, int nCount);

class CPtrArray
{
public:
// Construction
	CPtrArray();

// Attributes
	int GetSize() const;
	int GetUpperBound() const;
	void SetSize(int nNewSize, int nGrowBy = -1);

// Operations
	// Clean up
	void FreeExtra();
	void RemoveAll();

	// Accessing elements
	void* GetAt(int nIndex) const;
	void SetAt(int nIndex, void* newElement);

	void*& ElementAt(int nIndex);

	// Direct Access to the element data (may return NULL)
	void** GetData();

	// Potentially growing the array
	void SetAtGrow(int nIndex, void* newElement);

	int Add(void* newElement);

	int Append(const CPtrArray& src);
	void Copy(const CPtrArray& src);

	// overloaded operator helpers
	void* operator[](int nIndex) const;
	void*& operator[](int nIndex);

	// Operations that move elements around
	void InsertAt(int nIndex, void* newElement, int nCount = 1);

	void RemoveAt(int nIndex, int nCount = 1);
	void InsertAt(int nStartIndex, CPtrArray* pNewArray);
	void AssertValid() const;
// Implementation
protected:
	void** m_pData;   // the actual array of data
	int m_nSize;     // # of elements (upperBound - 1)
	int m_nMaxSize;  // max allocated
	int m_nGrowBy;   // grow amount


public:
	~CPtrArray();
protected:
	// local typedefs for class templates
	typedef void* BASE_TYPE;
	typedef void* BASE_ARG_TYPE;
};

/*template<class BASE_CLASS, class TYPE>
class CTypedPtrArray : public BASE_CLASS
{
public:
	// Accessing elements
	TYPE GetAt(int nIndex) const;
	TYPE& ElementAt(int nIndex);
	void SetAt(int nIndex, TYPE ptr);
	
	// Potentially growing the array
	void SetAtGrow(int nIndex, TYPE newElement);
	int Add(TYPE newElement);
	int Append(const CTypedPtrArray<BASE_CLASS, TYPE>& src);
	void Copy(const CTypedPtrArray<BASE_CLASS, TYPE>& src);
	
	// Operations that move elements around
	void InsertAt(int nIndex, TYPE newElement, int nCount = 1);
	void InsertAt(int nStartIndex, CTypedPtrArray<BASE_CLASS, TYPE>* pNewArray);
	
	TYPE operator[](int nIndex) const;
	TYPE& operator[](int nIndex);
};*/
template<class BASE_CLASS, class TYPE>
class CTypedPtrArray : public BASE_CLASS
{
public:
	// Accessing elements
	TYPE GetAt(int nIndex) const
	{ return (TYPE)BASE_CLASS::GetAt(nIndex); }
	TYPE& ElementAt(int nIndex)
	{ return (TYPE&)BASE_CLASS::ElementAt(nIndex); }
	void SetAt(int nIndex, TYPE ptr)
	{ BASE_CLASS::SetAt(nIndex, ptr); }
	
	// Potentially growing the array
	void SetAtGrow(int nIndex, TYPE newElement)
	   { BASE_CLASS::SetAtGrow(nIndex, newElement); }
	int Add(TYPE newElement)
	   { return BASE_CLASS::Add(newElement); }
	int Append(const CTypedPtrArray<BASE_CLASS, TYPE>& src)
	   { return BASE_CLASS::Append(src); }
	void Copy(const CTypedPtrArray<BASE_CLASS, TYPE>& src)
	{ BASE_CLASS::Copy(src); }
	
	// Operations that move elements around
	void InsertAt(int nIndex, TYPE newElement, int nCount = 1)
	{ BASE_CLASS::InsertAt(nIndex, newElement, nCount); }
	void InsertAt(int nStartIndex, CTypedPtrArray<BASE_CLASS, TYPE>* pNewArray)
	   { BASE_CLASS::InsertAt(nStartIndex, pNewArray); }
	
	// overloaded operator helpers
	TYPE operator[](int nIndex) const
	{ return (TYPE)BASE_CLASS::operator[](nIndex); }
	TYPE& operator[](int nIndex)
	{ return (TYPE&)BASE_CLASS::operator[](nIndex); }
};

// CArray.h: interface for the CArray class.
//
//////////////////////////////////////////////////////////////////////

template<class TYPE,class ARG_TYPE>
class CArray  
{
public:
	CArray();
	~CArray();

// Implementation
protected:
	TYPE* m_pData;   // the actual array of data
	int m_nSize;     // # of elements (upperBound - 1)
	int m_nMaxSize;  // max allocated
	int m_nGrowBy;   // grow amount

public:
	// Attributes
	int GetSize() const;
	int GetUpperBound() const;
	void SetSize(int nNewSize, int nGrowBy);

	// Operations
	// Clean up
	void FreeExtra();
	void RemoveAll();

	// Accessing elements
	TYPE GetAt(int nIndex) const;
	void SetAt(int nIndex, ARG_TYPE newElement);
	TYPE& ElementAt(int nIndex);

	// Direct Access to the element data (may return NULL)
	const TYPE* GetData() const;
	TYPE* GetData();

	// Potentially growing the array
	void SetAtGrow(int nIndex, ARG_TYPE newElement);
	int Add(ARG_TYPE newElement);
	int Append(const CArray& src);
	void Copy(const CArray& src);

	// overloaded operator helpers
	TYPE operator[](int nIndex) const;
	TYPE& operator[](int nIndex);

	// Operations that move elements around
	void InsertAt(int nIndex, ARG_TYPE newElement, int nCount);
	void RemoveAt(int nIndex, int nCount);
	void InsertAt(int nStartIndex, CArray* pNewArray);
};

/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
class CFile
{
public:
	CFile();
	virtual ~CFile();

protected:
	char	m_szFileName[MAX_PATH + 1];
public:
	FILE*	m_hFile;

public:
//	enum { hFileNull = 0 };
//	static int hFileNull = 0;
	enum
	{
		modeRead =          0x0001,
		modeWrite =         0x0002,
		modeReadWrite =     0x0004,
		shareCompat =       0x0008,
		shareExclusive =    0x0010,
		shareDenyWrite =    0x0020,
		shareDenyRead =     0x0030,
		shareDenyNone =     0x0040,
		modeNoInherit =     0x0080,
		modeCreate =        0x1000,
		modeNoTruncate =    0x2000,
		typeText =          0x4000, // typeText and typeBinary are used in
		typeBinary =   (int)0x8000 // derived classes only
	};

	enum
	{ 
		begin =		0x0,
		current =	0x1,
		end =		0x2
	};

public:
	bool	Open(LPCTSTR lpszFileName, UINT nOpenFlags);
	void	Close();

	UINT	Read(void* lpBuf, UINT nCount);
	char*    ReadString(void* lpBuf,UINT nMax);
	void	Write(const void* lpBuf, UINT nCount);
	void	Write(LPCTSTR szStr) { Write(szStr, sizeof(TCHAR)*strlen(szStr)); }

	LONG	Seek(LONG lOff, UINT nFrom);
	DWORD	GetPosition() const;

	DWORD	GetLength();
	void	Flush();
	void	SeekToEnd();
	
};

#endif
