#pragma once
#include "afxwin.h"
#include "Label/Label.h"


// CSAboutDlg dialog

class CSAboutDlg : public CDialog
{
	DECLARE_DYNAMIC(CSAboutDlg)

public:
	CSAboutDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CSAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUT_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedUseBtn();
	afx_msg void OnBnClickedDutyBtn();
	afx_msg void OnNMClickSyslinkAbout(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMClickSyslinkUpdate(NMHDR *pNMHDR, LRESULT *pResult);
};
