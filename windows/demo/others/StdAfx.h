// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__98417E44_7E59_43DB_A7B0_3B034BCB8473__INCLUDED_)
#define AFX_STDAFX_H__98417E44_7E59_43DB_A7B0_3B034BCB8473__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdisp.h>        // MFC Automation classes
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#include <afxtempl.h>
#include <math.h>

#endif // _AFX_NO_AFXCMN_SUPPORT



#pragma comment(lib,"CxImageU.lib") 

#pragma comment(lib,"Jpeg.lib") 
#pragma message("Automatically linking with Jpeg.lib") 
#pragma comment(lib,"Tiff.lib") 
#pragma message("Automatically linking with Tiff.lib") 
#pragma comment(lib,"zlib.lib") 
#pragma message("Automatically linking with zlib.lib") 
#pragma comment(lib,"png.lib") 
#pragma message("Automatically linking with png.lib") 
#pragma comment(lib,"j2k.lib") 
#pragma message("Automatically linking with j2k.lib") 
#pragma comment(lib,"jasper.lib") 
#pragma message("Automatically linking with jasper.lib") 
#pragma comment(lib,"jbig.lib") 
#pragma message("Automatically linking with jbig.lib") 

/*
#pragma comment(lib,"CharRecog.lib") 
#pragma message("Automatically linking with CharRecog.lib") 
*/

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__98417E44_7E59_43DB_A7B0_3B034BCB8473__INCLUDED_)
