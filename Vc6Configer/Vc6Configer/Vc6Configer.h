
// Vc6Configer.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CVc6ConfigerApp:
// �йش����ʵ�֣������ Vc6Configer.cpp
//

class CVc6ConfigerApp : public CWinAppEx
{
public:
	CVc6ConfigerApp();

// ��д
	public:
	virtual BOOL InitInstance();
	BOOL CheckProcessExist(CString strName, DWORD *pPID = NULL);
	HWND FindAppWnd();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CVc6ConfigerApp theApp;