#pragma once

#include "CWebBrowser.h"

// CCTryDlg dialog

class CCTryDlg : public CDialog
{
	DECLARE_DYNAMIC(CCTryDlg)

public:
	CCTryDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CCTryDlg();

// Dialog Data
	enum { IDD = IDD_CCTRY_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CWebBrowser m_WebBrw;
};
