#pragma once
#include "afxcmn.h"
#include "afxwin.h"
#include "Inc.h"


// CFontDlg dialog

class CFontDlg : public CDialog
{
	DECLARE_DYNAMIC(CFontDlg)

public:
	CFontDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CFontDlg();

// Dialog Data
	enum { IDD = IDD_FONT_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	// for show the example;
	CDC *m_pDc;
	CFont mFont;
	CString strTextOut;
	LOGFONT mlFont;
	HWND m_hExample;
	CRect m_ShowRect;
	CString m_strFontName;
	CString m_strFontSize;
	COLORREF m_bkColor;

	CListCtrl m_FontListCtrl;
	virtual BOOL OnInitDialog();
	void GetSysFontList();
	BOOL ReadDefaultFontInfo(CFontItem &tItem);
	BOOL EnableWindow(UINT uID, BOOL bEnable = TRUE);
	CComboBox m_WndComBox;
	CComboBox m_FontComBox;
	CComboBox m_FontSizeComBox;
	afx_msg void OnNMClickListctrl(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnCbnSelchangeSelwnd();
	afx_msg void OnCbnSelchangeSelfont();
	afx_msg void OnCbnSelchangeFontsize();
	afx_msg void OnBnClickedSet();
	BOOL ModRegFontKeyValue(CFontItem tItem);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	CPoint GetShowTextPos(HDC hDc, CRect tRect);
};
