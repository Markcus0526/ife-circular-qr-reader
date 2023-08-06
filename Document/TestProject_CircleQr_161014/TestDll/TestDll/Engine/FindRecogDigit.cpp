// FindRecogDigit.cpp: implementation of the CFindRecogDigit class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"//
#include "FindRecogDigit.h"
#include "ImageBase.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


// double g_bitangle[3][150]={ {	6.43,	9.93,	13.42,	16.91,	20.41,	23.9,	27.39,	42.6,	46.08,	49.56,	53.04,	56.52,	60,	63.48,
// 						66.96,	70.44,	73.92,	77.4,	92.61,	96.1,	99.59,	103.09,	106.58,	110.07,	113.57, 246.43, 249.93,
// 						253.42, 256.91, 260.41, 263.9,	267.39,	282.6,	286.08,	289.56,	293.04, 296.52, 300, 
// 						303.48,	306.96,	310.44,	313.92,	317.4,	332.61,	336.1,	339.59,	343.09,	346.58,	350.07,	353.57},
// 					  {	10.91,14.44,17.96,	21.48,	25.01,	28.53,	32.05,	35.58,	39.1,	42.62,	46.15,	49.67,
// 					  	53.19,	56.71,	73.71,	78.08,	82.45,	86.82,	91.19,	95.56,	99.92,	104.29,	108.66,	131.17,
// 						135.2,	139.23,	143.26,	147.28,	151.31,	155.34,	159.37,	163.4,	167.43,	171.46,	188.54,	192.57,
// 						196.6,	200.63,	204.66,	208.69,	212.72,	216.74,	220.77,	224.8,	228.83,	251.34,	255.71,	260.08,
// 						264.44,	268.81,	273.18,	277.55,	281.92,	286.29,	303.29,	306.81,	310.33,	313.85,	317.38,	320.9,
// 						324.42,	327.95,	331.47,	334.99,	338.52,	342.04,	345.56,	349.09},
// 					  {	8.15,	12.68,	17.22,	21.76,	26.3,	30.84,	35.38,	54.56,	58.97,	63.38,	67.8,	72.21, 	76.62,
// 						81.03,	85.44,	89.86,	94.27,	98.68,	103.09,	107.5,	111.92,	248.08,	252.5,	256.91,	261.32,	265.73,	
// 						270.14,	274.56,	278.97,	283.38,	287.79,	292.2,	296.62,	301.03,	305.44,	324.62,	329.16,	333.7,	338.24,
// 						342.78,	347.32,	351.85}
// };
double g_bitangle[160]={ 	6.43,	9.93,	13.42,	16.91,	20.41,	23.9,	27.39,	42.6,	46.08,	49.56,	53.04,	56.52,	60,	63.48,
	66.96,	70.44,	73.92,	77.4,	92.61,	96.1,	99.59,	103.09,	106.58,	110.07,	113.57, 246.43, 249.93,
	253.42, 256.91, 260.41, 263.9,	267.39,	282.6,	286.08,	289.56,	293.04, 296.52, 300, 
	303.48,	306.96,	310.44,	313.92,	317.4,	332.61,	336.1,	339.59,	343.09,	346.58,	350.07,	353.57,
	10.91,14.44,17.96,	21.48,	25.01,	28.53,	32.05,	35.58,	39.1,	42.62,	46.15,	49.67,
	53.19,	56.71,	73.71,	78.08,	82.45,	86.82,	91.19,	95.56,	99.92,	104.29,	108.66,	131.17,
	135.2,	139.23,	143.26,	147.28,	151.31,	155.34,	159.37,	163.4,	167.43,	171.46,	188.54,	192.57,
	196.6,	200.63,	204.66,	208.69,	212.72,	216.74,	220.77,	224.8,	228.83,	251.34,	255.71,	260.08,
	264.44,	268.81,	273.18,	277.55,	281.92,	286.29,	303.29,	306.81,	310.33,	313.85,	317.38,	320.9,
	324.42,	327.95,	331.47,	334.99,	338.52,	342.04,	345.56,	349.09,
	8.15,	12.68,	17.22,	21.76,	26.3,	30.84,	35.38,	54.56,	58.97,	63.38,	67.8,	72.21, 	76.62,
	81.03,	85.44,	89.86,	94.27,	98.68,	103.09,	107.5,	111.92,	248.08,	252.5,	256.91,	261.32,	265.73,	
	270.14,	274.56,	278.97,	283.38,	287.79,	292.2,	296.62,	301.03,	305.44,	324.62,	329.16,	333.7,	338.24,
	342.78,	347.32,	351.85
};
double g_checkbitangle[32]={	126.37,	129.74,	133.11,	136.48,	139.85,	143.22,	146.58,	149.95,	211.92,	215.04,	
								218.16,	221.28,	224.4,	227.52,	230.63,	233.75,	127.18,	129.77,	132.37,	134.96,
								137.56,	140.16,	142.75,	145.35,	213.71,	216.44,	219.16,	221.88,	224.6,	227.32,	230.04,	232.76
};

CFindRecogDigit::CFindRecogDigit()
{
}

CFindRecogDigit::~CFindRecogDigit()
{

}
int decart_to_polar(int x,int y,int cx,int cy,int rate,int &thita)
{
	int r = int(sqrt(double(x-cx)*(x-cx)+double(y-cy)*(y-cy))+0.5);
	thita = int((atan2(double(y-cy),double(x-cx)) + 3.141592628) * 180*rate / 3.141592628+0.5);
	return r;
}
float polar_to_decart(int r,int thita,int cx,int cy,float &y)
{
	float x = (float)(cx + r * cos(double(thita-180)*3.141592/180));
	y = (int)(cy - r * sin(double(thita)*3.141592/180));

	return x;
}
char convertIntBinary2char(int bit5[5])
{
	char a = 0;
	int i;
	for(i=0;i<5;++i){
		a = a | bit5[i];
		if(i==4) break;
		a = a<<1;
	}
	if(a<15)	a = a-5;
	else		a = a-13;
	if(a>=10){
		a = a-10;
		a = a + 0x61;
	}
	else{
		a = a + 0x30;
	}
	return a; 
}
unsigned char convInts2BYTE(int bits[],int len)
{
	unsigned char a = 0;
	int i;
	for(i=0;i<len;++i){
		a = a | bits[i];
		if(i==len-1) break;
		a = a<<1;
	}
	return a;
}
int CFindRecogDigit::Find_RecogDib(BYTE* p24Dib,TCHAR* pResult)
{
	int w,h;
	// convert RGB to Gray Image
	BYTE* pGrayImg = CImageBase::MakeGrayImgFromAnyDib(p24Dib,w,h);
	int ret = Find_RecogGrayImg(pGrayImg,w,h, pResult);
	delete[] pGrayImg;
	return ret;
}
//return value
//0:recog false,1:recog ok,2: check error

int CFindRecogDigit::Find_RecogGrayImg(BYTE* grayImg,int w,int h,TCHAR* pRes)
{
	int debug_flag = 0;//1;
	int recog_value = RECOG_FALSE;
	int i,j,ii,k,n;
	memset(pRes,0,sizeof(TCHAR)*40);
	// if width is larger than height of image, rotate 90
	if(h<200 || w<200) return recog_value;
	// if image size is too large, reduce size.
	BYTE* binImg = Binarization_Windows(grayImg,w,h,5);
	if(debug_flag) CImageBase::SaveImgToFile(_T("d:\\temp\\bin.bmp"),binImg,w,h,1);

	int w1=w,h1=h;
	CRect inRect;
	CImageBase::GetCutRect(binImg,w1,h1,inRect);
	delete[] binImg; binImg= NULL;

	inRect.InflateRect(3,3);
	BYTE* cropImg = CImageBase::CropImg(grayImg,w,h,inRect);
	w1 = inRect.Width(); h1 = inRect.Height();
	if(debug_flag) CImageBase::SaveImgToFile(_T("d:\\temp\\cropgray.bmp"),cropImg,w1,h1,8);

	BYTE* zoomImg = CImageBase::ZoomImg(cropImg,w1,h1,400,400);
	delete[] cropImg; cropImg= NULL;
	w1 = 400;h1 = 400;
	binImg = Binarization_Windows(zoomImg,w1,h1,5);
	if(debug_flag) CImageBase::SaveImgToFile(_T("d:\\temp\\bin.bmp"),binImg,w1,h1,1);
	delete[] zoomImg; zoomImg= NULL;

	cropImg = binImg;
	if(debug_flag) CImageBase::SaveImgToFile(_T("d:\\temp\\zoom.bmp"),cropImg,w1,h1,1);

	int rate=2;//1;//2;
	int VIW = 360*rate;
	int VIH = max(w1,h1) / 2;
	int sr = 0;
	int er = sr + VIH;
	int cx = w1 / 2;
	int cy = h1 / 2;

	//convert decart to polar
	BYTE* pPolar = new BYTE[VIW*VIH];
	BYTE* pPolar1 = new BYTE[VIW*VIH];
	memset(pPolar,0,VIW*VIH);

	int r,thita;
	for(i = 0; i < h1; i++)
	{
		for(j = 0; j < w1; j ++)
		{
			if(cropImg[i*w1+j] == 0) continue;
			r = decart_to_polar(j,i,cx,cy,rate,thita);
			if(r < sr || r >= er) continue;
			thita = thita % VIW;
			pPolar[(r-sr)*VIW+thita] = 1;
		}
	}
	if(debug_flag) CImageBase::SaveImgToFile(_T("d:\\temp\\polar.bmp"),pPolar,VIW,VIH,1);
	memcpy(pPolar1,pPolar,VIW*VIH);
	
	float (*path)[1000];
	path = new float[3][1000];
	int avey[3],ord[3],gap;
	for(i=0;i<3;++i)
	{
		ord[i] = i;
		avey[i] = CircleViterbi_SAMZHU(pPolar,VIW,VIH,path[i]);
		RemoveLine(pPolar,VIW,VIH,path[i]);
	}
	
	int d,tm;
	for(i=0;i<3;i++)
	{
		d=avey[ord[i]];
		for (j = i+1; j <3; j++)
		{
			if ( d< avey[ord[j]] )
			{ 
				tm =  ord[j] ;  ord[j] = ord[i] ; ord[i] = tm;    
				d=avey[ord[i]]; 
			} 
		}	
	}

	gap = (avey[ord[0]]-avey[ord[2]])/2;
	
	int codebit[160];
	int checkbit[32];
	int bit5s[32][5];
	int bit8s[4][8];

	CRunProc runProc;
	CRunRt* pU;
	CRunRtAry rtAry;
	CPoint pt,axispt[3];
	int axisid[3];
	char uuid[33];
	int check_flag=0;
	int num = runProc.MakeConnectComponentFromImg(pPolar1,VIW,VIH,rtAry);

	memset(axisid,0,sizeof(int)*3);
	for(i=0;i<num;++i){
		pU = rtAry.GetAt(i);
		pt = pU->m_Rect.CenterPoint();
		if(pt.y>avey[ord[1]]-gap/5 && avey[ord[1]]+gap/5 && pU->m_Rect.Height() > gap/2){
			if(pt.x>80*rate && pt.x<100*rate )
			{
				axispt[0] = pt;
				axisid[0] = i;
			}
			else if(pt.x>200*rate && pt.x<220*rate)
			{
				axispt[1] = pt;
				axisid[1] = i;
			}
			else if(pt.x>320*rate && pt.x<340*rate)
			{	
				axispt[2] = pt;
				axisid[2] = i;
			}
		}
	}
	if(axisid[0]>0 && axisid[1]>0 && axisid[2]>0){
// 		for(i=0;i<num;++i){
// 			if(i == axisid[0] || i == axisid[1] ||i == axisid[2]) continue; 
// 			pU = rtAry.GetAt(i);
// 			pU->bUse = FALSE;
// 		}
		for(i=0;i<num;++i){
			if(i == axisid[0] || i == axisid[1] ||i == axisid[2]){
				pU = rtAry.GetAt(i);
				pU->bUse = FALSE;
			}
		}
		num = runProc.RemoveNoneUseRunRt(rtAry);
		runProc.GetImgFromRunRtAry(pPolar1,VIW,VIH,rtAry);

		if(debug_flag) CImageBase::SaveImgToFile(L"d:\\temp\\removeaxis.bmp",pPolar1,VIW,VIH,1);


		for(i=0;i<VIH;++i){
			k = 0;
			for(j=axispt[0].x;j>=0;--j){
				pPolar[i*VIW+k] = pPolar1[i*VIW+j];k++;
			}
			for(j=VIW-2;j>=axispt[0].x+1;--j){
				pPolar[i*VIW+k] = pPolar1[i*VIW+j];k++;
			}
		}

		if(debug_flag) CImageBase::SaveImgToFile(L"d:\\temp\\regular.bmp",pPolar,VIW,VIH,1);

		runProc.RemoveAllRunRt(rtAry);

		int vpos,lineid;
		for(i=0;i<160;++i){
			if(i>=0 && i<50) lineid = 0;
			else if(i>=50 && i<118) lineid = 1;
			else lineid = 2;
			vpos = avey[ord[lineid]];
			codebit[i] = GetBitFromImage(pPolar,VIW,VIH,g_bitangle[i]*rate,vpos);
		}
		for(i=0;i<32;++i){
			if(i>=0 && i<16) 
				lineid = 0;
			else 
				lineid = 2;
			vpos = avey[ord[lineid]];
			checkbit[i] = GetBitFromImage(pPolar,VIW,VIH,g_checkbitangle[i]*rate,vpos);
		}
		
		ii=0;k=0;
		for(i=0;i<160;++i){
			bit5s[k][ii]=codebit[i];
			ii++;
			if(ii==5){
				ii=0;
				k++;
			}
		}
		ii=0;k=0;
		for(i=0;i<32;++i){
			bit8s[k][ii]=checkbit[i];
			ii++;
			if(ii==8){
				ii=0;
				k++;
			}
		}
		check_flag = CheckCode(bit5s,bit8s);

		for(i=0;i<32;++i){
			uuid[i] = convertIntBinary2char(bit5s[i]);
		}
		uuid[i] = 0;
		//01234567-89ab-4cde-8fcd-bacd53271826
		k=0;
		for(i=0;i<32;++i){
			pRes[k++] = uuid[i];
			if(i==7 || i==11 || i==15 || i==19){
				pRes[k++] = 0x2d;
			}

		}
		pRes[k] = 0;
		if(check_flag == 1) recog_value = RECOG_OK;
		else				recog_value = RECOG_CHECK_ERROR;
		
	}
	runProc.RemoveAllRunRt(rtAry);

	delete[] path;
	delete[] pPolar;pPolar=NULL;
	delete[] pPolar1;pPolar1=NULL;
	
	delete[] cropImg; cropImg= NULL;
	return recog_value;
}

int CFindRecogDigit::CheckCode(int bit5s[32][5],int bit8s[4][8])
{
	int i,j,k,check_flag = 1;
	BYTE bit5byte[32],bit8byte[4],check_byte;
	for(i=0;i<32;++i) bit5byte[i] = convInts2BYTE(bit5s[i],5);
	for(i=0;i<4;++i) bit8byte[i] = convInts2BYTE(bit8s[i],8);

	for(i=0;i<4;++i){
		check_byte = 0;
		for(j=0;j<8;++j){
			k = i*8+j;
			check_byte = check_byte + bit5byte[k];
		}
		if(check_byte != bit8byte[i]) {
			check_flag = 0;
			//break;
		}
	} 

	return check_flag;
}
int CFindRecogDigit::GetBitFromImage(BYTE* pPolar,int w, int h ,double angle,int vpos)
{
	int gap = 5;
	int i,j,k,fg = 0,count=0;
	//for(j = 0; j < w; j ++)
	j = (int)(angle+0.5f);
	//j = (int)(angle-1);
	{
		for(i=-5;i<=5;++i){
			k = min(h-1,max(0,vpos+i));
			if(pPolar[k*w+j] == 1) {
				fg = 1;
				count++;
			}
		}
	}
	if(fg == 1 && count<3) fg = 0;
	return fg;
}

int CFindRecogDigit::CircleViterbi_SAMZHU(BYTE* pPolar,int w,int h,float* hpath)
{

	int VITERBISEGWIDTH  = max(4,w / 30);
	int VITERBISEGHEIGHT = VITERBISEGWIDTH / 2;
	int i, ii ,j,k, y;
	float yy;
	int **fangxiang = new int*[VITERBISEGWIDTH+1];
	for(i = 0; i < VITERBISEGWIDTH + 1; i ++)
		fangxiang[i] = new int[VITERBISEGHEIGHT*2+1];

	float **ffangxiang = new float*[VITERBISEGWIDTH+1];
	for(i = 0; i < VITERBISEGWIDTH + 1; i ++)
		ffangxiang[i] = new float[VITERBISEGHEIGHT*2+1];
	int vsH = VITERBISEGHEIGHT*2+1;
	int vsW = w / VITERBISEGWIDTH;


	int *score = new int[vsW * h*vsH];
	for(i=0;i<vsW*h*vsH;i++)
		score[i] = 10;
	//memset(score,0,sizeof(int)*(vsW* h*vsH));

	int *hwai = new int[vsW*h*vsH];
	memset(hwai,0,sizeof(int)*vsW*h*vsH);

	for(i = 0; i < VITERBISEGWIDTH; i ++)
	{
		for(j = - VITERBISEGHEIGHT; j <= VITERBISEGHEIGHT; j ++)
		{
			yy = (float)(j*i)/(float)(VITERBISEGWIDTH - 1);
			ffangxiang[i][j+VITERBISEGHEIGHT] = yy - j;
			fangxiang[i][j+VITERBISEGHEIGHT] = (int)floorf(yy+0.5f) - j;
		}
	}
	for(ii = 1; ii < (w / VITERBISEGWIDTH); ii ++)
	{
		int *pDetectLine;
		for(i = 0; i < VITERBISEGWIDTH; i ++)
		{
			pDetectLine = fangxiang[i];
			for(j = 0; j < h; j ++)
			{
				if(pPolar[j*w+(ii-1)*VITERBISEGWIDTH+i] == 0) continue;
				for(k = -VITERBISEGHEIGHT; k <= VITERBISEGHEIGHT; k ++)
				{
					//j + k + g_DetectLine[i][k+MAXHEIGHTDIFF][0];
					y = j + pDetectLine[k+VITERBISEGHEIGHT];
					if(y >= 0 && y < h && y + k>=0 && y+k < h) score[ii*h*vsH+ y*vsH+ k + VITERBISEGHEIGHT] += 10;
					if(y >= -1 && y < h - 1 && j < h - 1 && pPolar[(j+1)*w+(ii-1)*VITERBISEGWIDTH+i] == 0
						&& y+1 + k>=0 && y+1+k < h) score[ii*h*vsH+ (y+1)*vsH + k + VITERBISEGHEIGHT] += 3;
					if(y > 0 && y <= h && j >= 2 && pPolar[(j-1)*w+(ii-1)*VITERBISEGWIDTH+i] == 0 &&
						pPolar[(j-2)*w+(ii-1)*VITERBISEGWIDTH+i] == 0
						&& y-1 + k>=0 && y-1+k < h) score[ii*h*vsH+ (y-1)*vsH + k + VITERBISEGHEIGHT] += 3;
				}
			}
		}
	}
	int alpha[]={3,4,5,4,3};
	int xx;
	for(ii = 1; ii < vsW; ii ++ )
	{
		for(i = 0; i < h; i ++)
		{
			for(k = -VITERBISEGHEIGHT; k <= VITERBISEGHEIGHT; k ++)
			{
				if(i+k < 0 || i + k >= h) continue;
				hwai[ii*h*vsH + i * vsH + k + VITERBISEGHEIGHT] = k;
				y = score[ii*h*vsH + i * vsH + k + VITERBISEGHEIGHT];
				score[ii*h*vsH + i * vsH + k + VITERBISEGHEIGHT] = y + score[(ii-1)*h*vsH + (i+k) * vsH + k + VITERBISEGHEIGHT];
				for(j = -2;j<=2;j++)
				{
					if(j + k >= -VITERBISEGHEIGHT && j + k <= VITERBISEGHEIGHT)
					{
						xx = y * alpha[j+2] / 5 + score[(ii-1)*h*vsH + (i+k) * vsH + k + VITERBISEGHEIGHT+j];
						if(xx > score[ii*h*vsH + i * vsH + k + VITERBISEGHEIGHT])
						{
							score[ii*h*vsH + i * vsH + k + VITERBISEGHEIGHT] = xx;
							hwai[ii*h*vsH + i * vsH + k + VITERBISEGHEIGHT] = k+j;
						}
					}
				}

			}
		}
	}


	int maxscore = 0,maxscoreid = 0,maxscoreid1 = 0;

	int t1,t2,t3;
	float hpath1[1000];
	for(i = h/5; i < h; i ++)
	{
		for(k = -VITERBISEGHEIGHT; k <= VITERBISEGHEIGHT; k ++)
		{
			if(score[(vsW-1)*h*vsH + i * vsH + k + VITERBISEGHEIGHT] > maxscore)
			{
				memcpy(hpath1,hpath,sizeof(float)*1000);
				t1 = i;t2 = k;
				for(j = (vsW - 1)*VITERBISEGWIDTH; j < w; j ++)
					hpath[j] = t1;
				for(ii=vsW - 1;ii>0;ii--)
				{
					//hpath[0][j-1]=hwai[hpath[0][j]*w+j];
					for(j = 0; j < VITERBISEGWIDTH; j ++)
						hpath[ii*VITERBISEGWIDTH-j] = max(0,min(h-1,t1+(ffangxiang[j][t2+VITERBISEGHEIGHT]+t2)));
					t3 = t2;
					t2 = hwai[ii*h*vsH+t1*vsH+t2+VITERBISEGHEIGHT];
					t1 = t1 + t3;

				}
				hpath[0] = t1;
				if(abs(t1 - i) > 2) {memcpy(hpath,hpath1,sizeof(float)*1000);continue;}

				maxscore = score[(vsW-1)*h*vsH + i * vsH + k + VITERBISEGHEIGHT];
				maxscoreid = i;
				maxscoreid1 = k;
			}
		}
	}
	int hpathcount = 1;
	if(maxscore == 0)
		hpathcount = 0;
	else
	{
		hpath[0] = hpath[w-1];
		if(maxscore-vsW*10 < w) hpathcount = 0;
	}
	delete hwai;

	delete score;
	for(i = 0; i < VITERBISEGWIDTH + 1; i ++)
		delete fangxiang[i];
	for(i = 0; i < VITERBISEGWIDTH + 1; i ++)
		delete ffangxiang[i];
	delete fangxiang;delete ffangxiang;
	//DebugViterbi(w,h,hpath);

	//return hpathcount;
	int aveh=0;
	for(i=0;i<w;++i){
		aveh += (int)hpath[i];
	}
	aveh /= w;
	return aveh;
}

void CFindRecogDigit::RemoveLine(BYTE* pPolar,int w, int h ,float* hpath)
{
	int gap = 5;
	int i,j,k;
	for(j = 0; j < w; j ++)
	{
		for(i=-5;i<=5;++i){
			k = int(hpath[j]+0.5f)+i;
			k = min(h-1,max(0,k));
			pPolar[k*w+j] = 0;
		}
	}


//	CImageBase::SaveImgToFile(L"d:\\temp\\removeline.bmp",pPolar,w,h,1);


}
void CFindRecogDigit::DebugViterbi(int w,int h,float* hpath)
{
	BYTE* pImg = new BYTE[w*h];
	memset(pImg,0,w*h);
	int j;
	for(j = 0; j < w; j ++)
	{

		pImg[int(hpath[j]+0.5f)*w+j] = 1;
	}


//	CImageBase::SaveImgToFile(L"d:\\temp\\horzviterbi.bmp",pImg,w,h,1);

	delete pImg;
}
#define	    HIGH_LEVEL		0
#define	    LOW_LEVEL		1//255
BYTE* CFindRecogDigit::Binarization_Windows(BYTE* pImg,int w,int h,int nWinSize)
{
	if (!pImg || w<1 || h<1)
		return NULL;
	int nWindowSize = nWinSize;
	int i=0,j=0,i1,j1;
	int nSum = 0,nTemp=0;
	int divid = (2*nWindowSize+1)*(2*nWindowSize+1)-1;

	int ww = w+2*nWindowSize+1;
	int hh = h+2*nWindowSize;
	BYTE* temp = new BYTE[ww*hh];
	memset(temp,255,ww*hh);
	for(i = 0; i < h; i++) memcpy(temp+(i+nWindowSize)*ww+nWindowSize+1 , pImg + i*w, w);


	BYTE* pbImage = new BYTE[w*h];
	memset(pbImage,0,w*h);
	for(i = nWindowSize; i < hh-nWindowSize; i++)
	{
		nSum = 0;
		for(i1 = i-nWindowSize; i1 <= i+nWindowSize; i1++)
			for(j1 = 0; j1 < 2*nWindowSize+1; j1++)
			{
				nSum += temp[i1*ww+j1];
			}
			for(j = nWindowSize+1; j < ww-nWindowSize; j++)
			{
				for(i1 = i-nWindowSize; i1 <= i+nWindowSize; i1++)
				{
					nSum -= temp[i1*ww+j-nWindowSize-1];
					nSum += temp[i1*ww+j+nWindowSize];
				}
				nTemp = (i-nWindowSize)*w+(j-nWindowSize-1);
				if(pImg[nTemp]+10 < (nSum-pImg[nTemp])/divid)
					pbImage[nTemp] = LOW_LEVEL;
				else
					pbImage[nTemp] = HIGH_LEVEL;
			}
	}
	delete[] temp;
	return pbImage;
}

