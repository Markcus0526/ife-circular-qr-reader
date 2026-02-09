// FindRecogDigit.h: interface for the CFindRecogDigit class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FINDRECOGDIGIT_H__DC78FAF4_0ED7_49D1_93EA_4702DB7CB782__INCLUDED_)
#define AFX_FINDRECOGDIGIT_H__DC78FAF4_0ED7_49D1_93EA_4702DB7CB782__INCLUDED_



#include "Include/myType.h"
#include "TRunProc.h"

#define RECOG_FALSE			0
#define RECOG_OK			1
#define RECOG_CHECK_ERROR	2
class CFindRecogDigit
{
public:
    CFindRecogDigit();
    virtual ~CFindRecogDigit();
    
    static int	Find_RecogDib(BYTE* p24Dib,char* pResult);
    static int	Find_RecogGrayImg(BYTE* grayImg,int w,int h,char* pResult);
    static int		GetBitFromImage(BYTE* pPolar,int w, int h ,int xpos,int vpos);//double angle,int vpos);
    static int		CheckCode(int bit5s[32][5],int bit8s[4][8]);
    static int		getDiffedPos(int xpos,int lineid,double miniDotDiff[10],int miniDotNum,int rate);
    static double	getMiniDotDiff(int xpos,int vpos,CRunRtAry& rtAry);
    static int		CircleViterbi_SAMZHU(BYTE* pPolar,int w,int h,float* hpath);
    static void	RemoveLine(BYTE* pPolar,int w, int h ,float* hpath);
    static void	DebugViterbi(int w,int h,float* hpath);
    static BYTE*	Binarization_Windows(BYTE* pImg,int w,int h,int nWinSize);
};

#endif // !defined(AFX_FINDRECOGDIGIT_H__DC78FAF4_0ED7_49D1_93EA_4702DB7CB782__INCLUDED_)
