// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently

#pragma once

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // Exclude rarely-used stuff from Windows headers
#endif

#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // some CString constructors will be explicit

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions

#ifndef _AFX_NO_OLE_SUPPORT
#include <afxole.h>         // MFC OLE classes
#include <afxodlgs.h>       // MFC OLE dialog classes
#include <afxdisp.h>        // MFC Automation classes
#endif // _AFX_NO_OLE_SUPPORT

#ifndef _AFX_NO_DB_SUPPORT
#include <afxdb.h>                      // MFC ODBC database classes
#endif // _AFX_NO_DB_SUPPORT

#ifndef _AFX_NO_DAO_SUPPORT
#include <afxdao.h>                     // MFC DAO database classes
#endif // _AFX_NO_DAO_SUPPORT

#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // MFC support for Internet Explorer 4 Common Controls
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>                     // MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT


#include <afxtempl.h>
#include <math.h>

// 
// #pragma comment(lib,"CxImageU.lib") 
// 
// #pragma comment(lib,"Jpeg.lib") 
// #pragma message("Automatically linking with Jpeg.lib") 
// #pragma comment(lib,"Tiff.lib") 
// #pragma message("Automatically linking with Tiff.lib") 
// #pragma comment(lib,"zlib.lib") 
// #pragma message("Automatically linking with zlib.lib") 
// #pragma comment(lib,"png.lib") 
// #pragma message("Automatically linking with png.lib") 
// #pragma comment(lib,"j2k.lib") 
// #pragma message("Automatically linking with j2k.lib") 
// #pragma comment(lib,"jasper.lib") 
// #pragma message("Automatically linking with jasper.lib") 
// #pragma comment(lib,"jbig.lib") 
// #pragma message("Automatically linking with jbig.lib") 

