// Md5Test.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CMd5TestApp:
// See Md5Test.cpp for the implementation of this class
//

class CMd5TestApp : public CWinApp
{
public:
	CMd5TestApp();

// Overrides
	public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CMd5TestApp theApp;