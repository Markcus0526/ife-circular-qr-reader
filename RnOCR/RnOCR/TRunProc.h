// PxyRun.h: interface for the CRunProc class.
//
//////////////////////////////////////////////////////////////////////
#if !defined(_PXYRUN_H__)
#define _PXYRUN_H__

#include "Include/myType.h"
#include <math.h>

#define max(a,b)            (((a) > (b)) ? (a) : (b))
#define min(a,b)            (((a) < (b)) ? (a) : (b))
// 

#ifndef IMAGESIZE
#define  	IMAGESIZE		200000
#endif

#define SORT_PIXELNUM   0
#define SORT_SIZE       1
#define SORT_LEFT       2
#define SORT_TOP        3
#define SORT_CENTER_X   4
#define SORT_CENTER_Y   5
#define SORT_LINEID		6

// #ifdef _DEBUG
// #define new DEBUG_NEW
// #endif



template <class TRt>
class TRunProc
{

typedef CTypedPtrArray <CPtrArray, TRt*> TRtAry;

public:
	TRunProc();
	virtual ~TRunProc();
public:
	short*	m_pRunX;	//	X position of Run
	int*	m_pRunNo;	//	Index of Start Run in the Line
	int     m_h;
	int*    m_pDown;
	int*    m_pUp;
	int*    m_pLabel;

public:
	int				CreateRunTableFromImg(BYTE* Img,int w,int h,short *runX, int *runNo);
	int				CreateRunTableFromImg(BYTE* Img,int w,int h, short* runX,int* runNo,CRect subrect);
	int				CreateRunTableFromImg(BYTE* Img,int w,int h);
	int				CreateRunTableFromImg(BYTE* Img,int w,int h, CRect subrect);
	static void		UpdateRunTable(short *runX, int *runNo, int h);

	void			GetImgFromRunRt(BYTE* Img,TRt *pRunRt,CRect Rt);
	BYTE*			GetImgFromRunRt(TRt *pRunRt,int &w,int &h);
	void			GetImgFromRunRtAry(BYTE* Img,int w, int h,TRtAry& RunRtAry);
	BYTE*			GetImgFromRunRtAry(TRtAry& RunRtAry,CRect Rt);
	BYTE*			GetImgFromRunRtAry(TRtAry& RunRtAry,int& w,int& h);
	
	int 			MakeConnectComponent(short *runX, int *runNo,int h, TRtAry& RunRtAry,int nUserDataSize=0);
	int				MakeConnectComponentFromImg(BYTE* pImg, int w,int h, TRtAry& RunRtAry,int nUserDataSize=0);
	int				MakeConnectComponentFromImg(BYTE* pImg, int w,int h, TRtAry& RunRtAry, CRect subrect,int nUserDataSize=0);


	CRect			GetRealRect(TRtAry& RectAry);
	void			SortByOption(TRtAry& RunRtAry,int Option);
	void			SortByOption(TRtAry& RunRtAry,int nStart,int nEnd,int Option);

	static void		RemoveAllRunRt(TRtAry& RunRtAry);
	static int		RemoveNoneUseRunRt(TRtAry& RunRtAry);

protected:
	void			CreateMemory_UpDownLabel(int *runNo, int h);
	void			DeleteMemory_UpDownLabel();
	void			MakeRunData(short *runX, int *runNo,int* pLabel,TRtAry& RunRtAry,int nId);
	void			MakeDownTable(short *runX, int *runNo,int h,int* pDown);
	void			MakeDownTable();
	void			MakeUpTable(short *runX, int *runNo,int h,int* pUp);
	void			MakeUpTable();
	void			RunFollowing(short *runX, int *runNo,int h,int* pDown,int* pUp,int* pLabel,TRtAry& RunRtAry,bool bMakeRunData=false,int nUserDataSize=0);
	void			RunFollowing(TRtAry& RunRtAry,bool bMakeRunData=false,int nUserDataSize=0);
	bool			NextRunNumber(int* pDown,int* pUp,int &i,int &p);
	bool			NextRunNumber(int &i,int &p);

};

template <class TRt>
TRunProc<TRt>::TRunProc()
{
	m_pRunX     = NULL;
	m_pRunNo    = NULL;
	m_pDown		= NULL;
	m_pUp		= NULL;
	m_pLabel	= NULL;
}
template <class TRt>
TRunProc<TRt>::~TRunProc()
{
	if(m_pRunX  != NULL) { delete[] m_pRunX;  m_pRunX  = NULL; }
	if(m_pRunNo != NULL) { delete[] m_pRunNo; m_pRunNo = NULL; }

	if(m_pDown  != NULL) { delete []m_pDown;  m_pDown  = NULL; }
	if(m_pUp    != NULL) { delete []m_pUp;    m_pUp    = NULL; }
	if(m_pLabel != NULL) { delete []m_pLabel; m_pLabel = NULL; }
}
template <class TRt>
int TRunProc<TRt>::CreateRunTableFromImg(BYTE* Img,int w,int h, CRect subrect)
{
	if(m_pRunNo != NULL){ delete []m_pRunNo; m_pRunNo = NULL;}
	if(m_pRunX  != NULL){ delete []m_pRunX;  m_pRunX = NULL;}
	m_pRunNo = new int[h+2 * max(w, h)+1];
	m_pRunX = new short[IMAGESIZE];
	m_h = h;
	return CreateRunTableFromImg(Img, w, h, m_pRunX, m_pRunNo, subrect);
}

template <class TRt>
int TRunProc<TRt>::CreateRunTableFromImg(BYTE* Img,int w,int h)
{
	if(m_pRunNo != NULL){ delete []m_pRunNo; m_pRunNo = NULL;}
	if(m_pRunX  != NULL){ delete []m_pRunX;  m_pRunX = NULL;}
	m_pRunNo = new int[h+2 * max(w, h)+1];
	m_pRunX = new short[IMAGESIZE];
	m_h = h;
	return CreateRunTableFromImg(Img, w, h, m_pRunX, m_pRunNo);
}
template <class TRt>
int TRunProc<TRt>::CreateRunTableFromImg(BYTE* Img,int w,int h,short *runX, int *runNo)
{
    int i,j,RunNum=1;
	int rem;
    bool b;
    BYTE By;

    runNo[0] = 1;
	for(i=0; i<h; i++)
	{
		b = true;
		for(j=0; j<w; j++) 
		{
			By = Img[i*w+j];
			if(b == false && By == 1) continue;
			if(b == true  && By == 1 )
			{
				runX[RunNum] = j;
				RunNum++;
				b = false;
			}
			else if(b == false && By == 0)
			{
				runX[RunNum] = j;
				RunNum++;
				b = true;
			}
		}
		rem =RunNum%2;
		if(rem == 0)
		{
			runX[RunNum] = w;
			RunNum++; 
		}
	runNo[i + 1] = RunNum;
	}
	return RunNum;
}
template <class TRt>
int TRunProc<TRt>::CreateRunTableFromImg(BYTE* Img,int w,int h, short* runX,int* runNo,CRect subrect)
{
    int i,j,RunNum=1;
	int rem;
    bool b;
    BYTE By;
	subrect.IntersectRect(subrect,CRect(0,0,w,h));
	for(i=0; i<=subrect.top; i++)    
		runNo[i] = 1;

	for(i=subrect.top; i<subrect.bottom; i++)
	{
		b = true;
		for(j=subrect.left; j<subrect.right; j++) 
		{
			By = Img[i*w+j];
			if(b == false && By == 1) continue;
			if(b == true  && By == 1 )
			{
				runX[RunNum] = j;
				RunNum++;
				b = false;
			}
			else if(b == false && By == 0)
			{
				runX[RunNum] = j;
				RunNum++;
				b = true;
			}
		}
		rem = RunNum % 2;
		if(rem == 0)
		{
			runX[RunNum] = (short)subrect.right;
			RunNum++; 
		}
		runNo[i + 1] = RunNum;
	}
	for(i=subrect.bottom; i<h+1; i++)    
		runNo[i] = RunNum;
	return RunNum;
}
template <class TRt>
void TRunProc<TRt>::UpdateRunTable(short *runX, int *runNo, int h)
{
	int i,j,st,num;
	
	st = num = 1;
	for(j=0; j<h; j++)
	{
		for(i=runNo[j]; i<runNo[j+1]; i+=2) 
		{
			if(runX[i] == -1) continue;
			runX[num] = runX[i];   num++;				
			runX[num] = runX[i+1]; num++;
		}
		runNo[j] = st; st = num;
	}
	runNo[j] = st;
}

template <class TRt>
void TRunProc<TRt>::CreateMemory_UpDownLabel(int *runNo, int h)
{
	int nSize = runNo[h] + 1;

	if(m_pDown != NULL) delete []m_pDown;
	m_pDown = new int[nSize];
	memset(m_pDown, 0, sizeof(int) * nSize);

	if(m_pUp != NULL) delete []m_pUp;
	m_pUp = new int[nSize];
	memset(m_pUp, 0, sizeof(int) * nSize);

	nSize = runNo[h];
	if(m_pLabel != NULL) delete []m_pLabel;
	m_pLabel = new int[nSize];
	memset(m_pLabel, 0, sizeof(int) * nSize);
}
template <class TRt>
void TRunProc<TRt>::DeleteMemory_UpDownLabel()
{
	if(m_pDown != NULL)  { delete []m_pDown;  m_pDown  = NULL; }
	if(m_pUp != NULL)    { delete []m_pUp;    m_pUp    = NULL; }
	if(m_pLabel != NULL) { delete []m_pLabel; m_pLabel = NULL; }
}
template <class TRt>
void TRunProc<TRt>::GetImgFromRunRt(BYTE* Img, TRt *pRunRt, CRect Rt)
{
	int i,j,y,nm,x1,x2;
	
	int wd = Rt.Width();
	int hi = Rt.Height();
	CRect rect;
	if(!rect.IntersectRect(pRunRt->m_Rect,Rt)) return;
	DWORD *data = pRunRt->pRunData;
	nm=pRunRt->nRunNum;
	for(i=0;i<nm;i+=2)
	{
		x1=(int)LOWORD(data[i]) - Rt.left;
		x2=(int)LOWORD(data[i+1]) - Rt.left; 
		y =(int)HIWORD(data[i]) - Rt.top;
		if(y<0 ||y>=hi || x2<0 ||x1>=wd) continue;
		x1 = max(0,x1);	x2 = min(wd-1,x2);
		y = wd * y;
		for(j=x1; j<x2; j++) Img[y + j] = 1;
	}
}
template <class TRt>
BYTE* TRunProc<TRt>::GetImgFromRunRt(TRt *pRunRt,int &w,int &h)
{
	int i,j,s,y,nm,x1,x2;

	w = pRunRt->m_Rect.Width();
	h = pRunRt->m_Rect.Height();
	s = w * h;
	
	BYTE *Img = new BYTE[s];
	memset(Img,0,s);

	DWORD *data = pRunRt->pRunData;
	nm=pRunRt->nRunNum; 
	for(i=0;i<nm;i+=2)
	{
		x1=(int)LOWORD(data[i]) - pRunRt->m_Rect.left;
		x2=(int)LOWORD(data[i+1]) - pRunRt->m_Rect.left; 
		y =(int)HIWORD(data[i]) - pRunRt->m_Rect.top;
		y = w * y;
		for(j=x1; j<x2; j++) Img[y + j] = 1;
	}
	return Img;
}

template <class TRt>
void TRunProc<TRt>::GetImgFromRunRtAry(BYTE* Img,int w, int h,TRtAry& RunRtAry)
{
	int i;
	CRect Rt = CRect(0,0,w,h);
	memset(Img, 0, w*h);
	int num = RunRtAry.GetSize();
	for(i=0; i<num; i++)
		GetImgFromRunRt(Img, RunRtAry[i], Rt);
}

template <class TRt>
BYTE* TRunProc<TRt>::GetImgFromRunRtAry(TRtAry& RunRtAry,CRect Rt)
{
	int i;
	int w = Rt.Width();
	int h = Rt.Height();
	int s = w * h;
	BYTE* Img = new BYTE[s];
	memset(Img, 0, s);
	int num = RunRtAry.GetSize();
	for(i=0; i<num; i++)
		GetImgFromRunRt(Img, RunRtAry[i], Rt);
	return Img;
}
template <class TRt>
BYTE* TRunProc<TRt>::GetImgFromRunRtAry(TRtAry& RunRtAry,int& w,int& h)
{
	int i;
	CRect Rt = GetRealRect(RunRtAry);
	w = Rt.Width();
	h = Rt.Height();
	int s = w * h;
	BYTE* Img = new BYTE[s];
	memset(Img, 0, s);
	int num = RunRtAry.GetSize();
	for(i=0; i<num; i++)
		GetImgFromRunRt(Img, RunRtAry[i], Rt);
	return Img;
}

template <class TRt>
CRect TRunProc<TRt>::GetRealRect(TRtAry& RunRtAry)
{
	int i;
	TRt* pRunRt;
	CRect rect;
	int l=10000,t=10000,r=0,b=0;
	int num = RunRtAry.GetSize();
	if(num==0){ rect.SetRect(0,0,0,0);return rect;}
	for(i=0;i<num;i++){
		pRunRt = RunRtAry.GetAt(i);
		l = min(l,pRunRt->m_Rect.left);t = min(t,pRunRt->m_Rect.top);
		r = max(r,pRunRt->m_Rect.right);b = max(b,pRunRt->m_Rect.bottom);
	}
	rect.SetRect(l,t,r+1,b+1);
	return rect;
}

template <class TRt>
void TRunProc<TRt>::MakeDownTable()
{
	MakeDownTable(m_pRunX, m_pRunNo,m_h,m_pDown);
}

template <class TRt>
void TRunProc<TRt>::MakeDownTable(short *runX, int *runNo,int h,int* pDown)
{
	int i,j,m,n1,n2,n3,x,y,k,l,p;
    bool st;
    m=h-1;
	for(i=0;i<h;i++) 
	{
		n1=runNo[i]; 
		n2=k=runNo[i+1]; 
        if(i==m)
		{
            y=n2-1;
            for(l=n1;l<n2;l++) pDown[l]=y;
            continue;
        }
		n3=runNo[i+2]; 

        if(n2==n3)
		{
            y=n2-1;
            for(l=n1;l<n2;l++) pDown[l]=y;
            continue;
        }

		for(j=n1;j<n2;j+=2) 
		{
			x=runX[j]-1; st=false;
			for(p=k;p<n3;p++) {
                if(runX[p]>x) { pDown[j]=p-1; k=p; st=true; break; }
			}
            if(p==n3 && st==false) { pDown[j]=p-1; k=p; }
		}

		k=n2;
		for(j=n1+1;j<n2;j+=2) 
		{
			x=runX[j]; st=false;
			for(p=k;p<n3;p++) 
			{
                if(runX[p]>x) { pDown[j]=p-1; k=p; st=true; break; }
			}
            if(p==n3 && st==false) { pDown[j]=p-1; k=p; }
		}
	}
}
template <class TRt>
void TRunProc<TRt>::MakeUpTable()
{
	MakeUpTable(m_pRunX, m_pRunNo, m_h, m_pUp);
}
template <class TRt>
void TRunProc<TRt>::MakeUpTable(short *runX, int *runNo,int h,int* pUp)
{
	int i,j,n1,n2,n3,x,y,k,l,p;
    bool st;

	for(i=h;i>0;i--)
	{
		n1=runNo[i]; 
		n2=runNo[i-1]; 
        if(i==1) 
		{
            y=n2-1;
            for(l=n2;l<n1;l++) pUp[l]=y;
            continue;
        }
		n3=k=runNo[i-2]; 

        if(n2==n3) 
		{
            y=n2-1;
            for(l=n2;l<n1;l++) pUp[l]=y;
            continue;
        }

		for(j=n2;j<n1;j+=2) 
		{
			x=runX[j]-1; st=false;
			for(p=k;p<n2;p++) 
			{
                if(runX[p]>x) { pUp[j]=p-1; k=p; st=true; break; }
			}
            if(p==n2 && st==false) { pUp[j]=p-1; k=p; }
		}

		k=n3;
		for(j=n2+1;j<n1;j+=2) 
		{
			x=runX[j]; st=false;
			for(p=k;p<n2;p++) 
			{
                if(runX[p]>x) { pUp[j]=p-1; k=p; st=true; break; }
			}
            if(p==n2 && st==false) { pUp[j]=p-1; k=p; }
		}
	}
}
template <class TRt>
bool TRunProc<TRt>::NextRunNumber(int &i,int &p)
{
	return  NextRunNumber(m_pDown,m_pUp,i,p);
}
template <class TRt>
bool TRunProc<TRt>::NextRunNumber(int* pDown,int* pUp,int &i,int &p)
{
	int j,k,w;
	bool  st;

	w=i%2;
	if(w!=0)
	{
		j=pDown[i];
		w=j%2;
		if(w!=0) 
		{
			k=i-1;
			if(pDown[k]==j) i=k;
			else { i=j; p++; }
		}
		else
		{
			k=i+1;
			if(pDown[k]==j) i=k;
			else { i=j+1; p++; }
		}
	}
	else
	{
		j=pUp[i];
		w=j%2;
		if(w!=0) 
		{
			k=i+1;
			if(pUp[k]==j) i=k;
			else { i=j+1; p--; }
		}
		else
		{
			k=i-1;
			if(pUp[k]==j) i=k;
			else { i=j; p--; }
		}

	}
	w=i%2;
	st=(w)? true: false;
	return st;
}
template <class TRt>
void TRunProc<TRt>::MakeRunData(short *runX, int *runNo,int *pLabel,TRtAry& RunRtAry,int nId)
{
	int j,k,t,p;
	int label,runEnd,runStart,runNum;
	
	TRt* pRunRt = RunRtAry[nId];
	runStart = pRunRt->nRunStart;	
	runEnd = pRunRt->nRunEnd;
	runNum = pRunRt->nRunNum; 
	label = pRunRt->nLabelNo;
	t = j = pRunRt->m_Rect.top;
	
	if(pRunRt->pRunData!=NULL){ delete[] pRunRt->pRunData;pRunRt->pRunData=NULL;}
	pRunRt->pRunData = new DWORD[runNum];
	if(pRunRt->pRunLabel!=NULL){ delete[] pRunRt->pRunLabel;pRunRt->pRunLabel=NULL;}
	pRunRt->pRunLabel = new short[runNum];
	p = 0;

	for(t++, k=runStart; k<=runEnd; k+=2)
	{
		if(runNo[t] <= k) { t++; j++; }
		if(pLabel[k] == label)
		{
			pRunRt->pRunData[p] = MAKELONG((WORD)runX[k],  (WORD)j); 
			pRunRt->pRunLabel[p] = label; 
			p++;
			pRunRt->pRunData[p] = MAKELONG((WORD)runX[k+1],(WORD)j); 
			pRunRt->pRunLabel[p] = label; 
			p++;
		}
	}
}
template <class TRt>
void TRunProc<TRt>::RunFollowing(TRtAry& RunRtAry,bool bMakeRunData/*=false*/,int nUserDataSize/*=0*/)
{
	if(m_pRunX==NULL || m_pRunNo==NULL || 
	   m_pDown==NULL || m_pUp==NULL || m_pLabel==NULL)
		return;
	RunFollowing(m_pRunX, m_pRunNo,m_h,m_pDown,m_pUp,m_pLabel,RunRtAry, bMakeRunData, nUserDataSize);
}
template <class TRt>
void TRunProc<TRt>::RunFollowing(short *runX, int *runNo,int h,int* pDown,int* pUp,int* pLabel,TRtAry& RunRtAry,bool bMakeRunData/*=false*/,int nUserDataSize/*=0*/)
{
	int i,j,k,m,g;
	int label,pixelNum,runEnd,runStart,runNum;
	int xmin,xmax,ymin,ymax;
	int maxrunlen;
	
	bool st;
	TRt *pRunRt;

	for(k=0, j=0; j<h; j++) for(i=runNo[j]; i<runNo[j+1]; i++) 
	{    
		if(pLabel[i] == 0) 
		{
			if(i % 2) { runStart = i; st = true; k++; label = k;  } 
			else { label = pLabel[i-1]; i++; runStart = i; st = false; }
			
			xmin = ymin = 10000;
			xmax = ymax = pixelNum = runEnd = runNum = maxrunlen = 0;
			
			do
			{
				if(i % 2)
				{ 
					m = runX[i + 1] - runX[i];
					pixelNum += m; 
					runEnd = max(runEnd, i);
				}
				runNum++;
				xmin = min(xmin, runX[i]);
				xmax = max(xmax, runX[i]);
				ymin = min(ymin, j);
				ymax = max(ymax, j);
				pLabel[i] = label;
				NextRunNumber(pDown,pUp,i, j);
			}while(i != runStart);
			
			if(st == true) 
			{
				pRunRt = new TRt;
				pRunRt->m_Rect = CRect(xmin, ymin, xmax, ymax + 1);
				pRunRt->nRunStart = runStart;  pRunRt->nRunEnd = runEnd;
				pRunRt->nLabelNo = label;
				pRunRt->nPixelNum = pixelNum;
				pRunRt->nMaxLength = maxrunlen;
				pRunRt->nRunNum = runNum;
				RunRtAry.Add(pRunRt);
			}
			else
			{
				g = label - 1;
				RunRtAry[g]->nPixelNum += pixelNum;
				RunRtAry[g]->nMaxLength = max(RunRtAry[g]->nMaxLength,maxrunlen);
				RunRtAry[g]->nRunNum += runNum;
			}
		}
	}
	if(nUserDataSize>0)
	{
		int num = RunRtAry.GetSize();
		for(i=0; i<num; i++)
		{
			void* pUserData = malloc(nUserDataSize);
			memset(pUserData,0,nUserDataSize);
			RunRtAry.GetAt(i)->pUserData = pUserData;
		}
	}
	if(bMakeRunData)
	{
		int num = RunRtAry.GetSize();
		for(i=0; i<num; i++) MakeRunData(runX, runNo, pLabel,RunRtAry,i);
	}
}

template <class TRt>
void TRunProc<TRt>::RemoveAllRunRt(TRtAry& RunRtAry)
{
	int i,num;
	num = RunRtAry.GetSize();
	if(num<1) return;
	for(i=0; i<num; i++) 
		delete (TRt*)RunRtAry.GetAt(i);
	RunRtAry.RemoveAll();
}

template <class TRt>
int TRunProc<TRt>::RemoveNoneUseRunRt(TRtAry& RunRtAry)
{
	int i,num;
	num = RunRtAry.GetSize();
	for(i=0; i<num; i++) {
		if(RunRtAry[i]->bUse == false){
			delete (TRt*)RunRtAry.GetAt(i);
			RunRtAry.RemoveAt(i);
			i--;num--;
		}
	}
	return num;	
}

template <class TRt>
int TRunProc<TRt>::MakeConnectComponentFromImg(BYTE* pImg,int w,int h,TRtAry& RunRtAry,int nUserDataSize/*=0*/)
{
	CRect subrect(0,0,w,h);
	return MakeConnectComponentFromImg(pImg, w, h, RunRtAry, subrect, nUserDataSize);
}

template <class TRt>
int TRunProc<TRt>::MakeConnectComponentFromImg(BYTE* pImg, int w,int h, TRtAry& RunRtAry, CRect subrect, int nUserDataSize/*=0*/)
{
	RemoveAllRunRt(RunRtAry);
	int* runNo = new int[h+2];
	short* runX = new short[IMAGESIZE];
	CreateRunTableFromImg(pImg,w,h, runX,runNo,subrect);
	int num = MakeConnectComponent(runX, runNo, h, RunRtAry, nUserDataSize);
	delete[] runNo;
	delete[] runX;
	return num;
}

template <class TRt>
int TRunProc<TRt>::MakeConnectComponent(short *runX, int *runNo,int h,TRtAry& RunRtAry,int nUserDataSize/*=0*/)
{
	RemoveAllRunRt(RunRtAry);
	CreateMemory_UpDownLabel(runNo,h);
	MakeDownTable(runX, runNo, h, m_pDown);
	MakeUpTable(runX, runNo, h, m_pUp);
	RunFollowing(runX, runNo, h, m_pDown, m_pUp, m_pLabel, RunRtAry,true, nUserDataSize);
	int num = RunRtAry.GetSize();
	return num;
}
template <class TRt>
void TRunProc<TRt>::SortByOption(TRtAry& RunRtAry,int Option) 
{
	int num;
	num = RunRtAry.GetSize();
	SortByOption(RunRtAry,0,num,Option);
}

template <class TRt>
void TRunProc<TRt>::SortByOption(TRtAry& RunRtAry,int nStart,int nEnd,int Option) 
{// Big->Small order sorting by Saturation of nPixelNum
	int i,j,num;
	TRt* swap,*pU,*pU1;
	num = RunRtAry.GetSize();
	nStart = max(0,nStart);
	nEnd = min(num, nEnd);
	switch(Option) {
	case SORT_PIXELNUM:
		for(i=nStart; i<nEnd-1; i++){
			for(j=i+1; j<nEnd; j++){
				pU = RunRtAry.GetAt(i);
				pU1 = RunRtAry.GetAt(j);
				if(pU->nPixelNum > pU1->nPixelNum)
				{
					swap = RunRtAry[i];	RunRtAry[i] = RunRtAry[j];RunRtAry[j] = swap;
				}
			}
		}
		break;
	case SORT_SIZE:
		for(i=nStart; i<nEnd-1; i++){
			for(j=i+1; j<nEnd; j++){
				pU = RunRtAry.GetAt(i);
				pU1 = RunRtAry.GetAt(j);
				if( pU->m_Rect.Width()*pU->m_Rect.Height() > pU1->m_Rect.Width()*pU1->m_Rect.Height())
				{
					swap = RunRtAry[i];	RunRtAry[i] = RunRtAry[j];RunRtAry[j] = swap;
				}
			}
		}
		break;
	case SORT_LEFT:
		for(i=nStart; i<nEnd-1; i++){
			for(j=i+1; j<nEnd; j++){
				pU = RunRtAry.GetAt(i);
				pU1 = RunRtAry.GetAt(j);
				if(pU->m_Rect.left > pU1->m_Rect.left)
				{
					swap = RunRtAry[i];	RunRtAry[i] = RunRtAry[j];RunRtAry[j] = swap;
				}
			}
		}
		break;
	case SORT_TOP:
		for(i=nStart; i<nEnd-1; i++){
			for(j=i+1; j<nEnd; j++){
				pU = RunRtAry.GetAt(i);
				pU1 = RunRtAry.GetAt(j);
				if(pU->m_Rect.top > pU1->m_Rect.top)
				{
					swap = RunRtAry[i];	RunRtAry[i] = RunRtAry[j];RunRtAry[j] = swap;
				}
			}
		}
		break;
	case SORT_CENTER_X:
		for(i=nStart; i<nEnd-1; i++){
			for(j=i+1; j<nEnd; j++){
				pU = RunRtAry.GetAt(i);
				pU1 = RunRtAry.GetAt(j);
				if((pU->m_Rect.CenterPoint().x > pU1->m_Rect.CenterPoint().x)
					|| (pU->m_Rect.CenterPoint().x == pU1->m_Rect.CenterPoint().x
					&& pU->m_Rect.CenterPoint().y > pU1->m_Rect.CenterPoint().y))
				{
					swap = RunRtAry[i];	RunRtAry[i] = RunRtAry[j];RunRtAry[j] = swap;
				}
			}
		}
		break;
	case SORT_CENTER_Y:
		for(i=nStart; i<nEnd-1; i++){
			for(j=i+1; j<nEnd; j++){
				pU = RunRtAry.GetAt(i);
				pU1 = RunRtAry.GetAt(j);
				if((pU->m_Rect.CenterPoint().y > pU1->m_Rect.CenterPoint().y)
					|| (pU->m_Rect.CenterPoint().y == pU1->m_Rect.CenterPoint().y
					&& pU->m_Rect.CenterPoint().x > pU1->m_Rect.CenterPoint().x))
				{
					swap = RunRtAry[i];	RunRtAry[i] = RunRtAry[j];RunRtAry[j] = swap;
				}
			}
		}
		break;
	case SORT_LINEID:
		for(i=nStart; i<nEnd-1; i++){
			for(j=i+1; j<nEnd; j++){
				pU = RunRtAry.GetAt(i);
				pU1 = RunRtAry.GetAt(j);
				if((pU->nLineNo > pU1->nLineNo)
					|| (pU->nLineNo == pU1->nLineNo
					&& pU->m_Rect.CenterPoint().x > pU1->m_Rect.CenterPoint().x))
				{
					swap = RunRtAry[i];	RunRtAry[i] = RunRtAry[j];RunRtAry[j] = swap;
				}
			}
		}
		break;
	default:
		for(i=nStart; i<nEnd-1; i++){
			for(j=i+1; j<nEnd; j++){
				pU = RunRtAry.GetAt(i);
				pU1 = RunRtAry.GetAt(j);
				if(pU->nPixelNum > pU1->nPixelNum)
				{
					swap = RunRtAry[i];	RunRtAry[i] = RunRtAry[j];RunRtAry[j] = swap;
				}
			}
		}
	}
}

class  CRunRt{
public:
	CRect		m_Rect;		//
	int		nRunStart;
	int		nRunEnd;
	int		nLabelNo;
	int		nPixelNum;//(Black)
	int		nMaxLength;		//Max length of run. by KBG  
	
	DWORD*	pRunData;
	short*	pRunLabel;
	int		nRunNum;
	
	bool	bUse;
	int		nLineNo;
	
	void*   pUserData;
	int		nAddNum;
	CRunRt() {
		nRunStart=nRunEnd=nLabelNo=nPixelNum=nRunNum=nLineNo=nMaxLength=0;
		m_Rect = CRect(0,0,0,0);
		pRunData = NULL;
		pRunLabel = NULL;
		pUserData = NULL;
		bUse = true;
		nAddNum = 1;
	};
	virtual ~CRunRt() {
		if(pRunData !=NULL) delete[] pRunData; pRunData=NULL;
		if(pRunLabel!=NULL) delete[] pRunLabel;pRunLabel=NULL;
		if(pUserData!=NULL) free(pUserData); pUserData=NULL;
	};
};

typedef TRunProc<CRunRt> CRunProc;

typedef CTypedPtrArray <CPtrArray, CRunRt*> CRunRtAry;

#endif // !defined(_PXYRUN_H__)
