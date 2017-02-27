#pragma once
#include "afxcmn.h"
#include "afxwin.h"
#include "Inc.h"
#include "ReportCtrl.h"


// CColorDlg dialog

class CColorDlg : public CDialog
{
	DECLARE_DYNAMIC(CColorDlg)

public:
	CColorDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CColorDlg();

// Dialog Data
	enum { IDD = IDD_COLOR_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CDC *m_pDc;
	CFont mFont;
	CString strTextOut;
	LOGFONT mlFont;
	CRect m_ShowRect;
	COLORREF m_bkColor;

	CRgb m_gFontRGB, m_gBkRGB;
	virtual BOOL OnInitDialog();
	CReportCtrl m_ColorListCtrl;
	CComboBox m_WndComBox;
	BOOL EnableWindow(UINT uID, BOOL bEnable = TRUE);
	BOOL ReadDefaultColorInfo(CColorItem &tItem);
	void ShowColorInfo(CColorItem &tItem);
	afx_msg void OnNMClickColorshow(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnCbnSelchangeSelwnd();
	afx_msg void OnBnClickedCusFontcolor();
	afx_msg void OnBnClickedCusBgcolor();
	afx_msg void OnBnClickedModcolor();
	BOOL ModRegFontAndBgColor(CColorItem &tItem);
};
