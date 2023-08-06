// RecogInterface.h: interface for the CRecogInterface class.

#define		RC_OK		1
#define		RC_FALSE	0
#define		English			1 //	 È Ã
#define		digit			2 //	º≠æÀ
#define		Symbol			3 //	º≠æÀ
#define		ALL				4 //	ºø∫∫ Ã∂ÅE

#define DllExport   __declspec( dllexport )

DllExport int __stdcall	isRecogInit();
DllExport int __stdcall	isRecogChar(unsigned char *Img,int w,int h,
												int nCharSet,int Type,void* pCand,int RecogStep);



