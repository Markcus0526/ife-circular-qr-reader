// FindRecogDigit.h: interface for the CFindRecogDigit class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FINDRECOGDIGIT_H__DC78FAF4_0ED7_49D1_93EA_4702DB7CB782__INCLUDED_)
#define AFX_FINDRECOGDIGIT_H__DC78FAF4_0ED7_49D1_93EA_4702DB7CB782__INCLUDED_




#include "TRunProc.h"

#define RECOG_FALSE			0
#define RECOG_OK			1
#define RECOG_CHECK_ERROR	2
class CFindRecogDigit  
{
public:
	CFindRecogDigit();
	virtual ~CFindRecogDigit();

	BOOL	Find_RecogDib(BYTE* p24Dib,TCHAR* pResult);
	BOOL	Find_RecogGrayImg(BYTE* grayImg,int w,int h,TCHAR* pResult);
	int		GetBitFromImage(BYTE* pPolar,int w, int h ,double angle,int vpos);
	int		CheckCode(int bit5s[32][5],int bit8s[4][8]);
	int		CircleViterbi_SAMZHU(BYTE* pPolar,int w,int h,float* hpath);
	void	RemoveLine(BYTE* pPolar,int w, int h ,float* hpath);
	void	DebugViterbi(int w,int h,float* hpath);
	BYTE*	Binarization_Windows(BYTE* pImg,int w,int h,int nWinSize);
};

#endif // !defined(AFX_FINDRECOGDIGIT_H__DC78FAF4_0ED7_49D1_93EA_4702DB7CB782__INCLUDED_)
