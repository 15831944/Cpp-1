
// Vc6ConfigerDlg.h : 头文件
//

#pragma once
#include "afxcmn.h"
#include "TabSheet.h"
#include "IncDlg.h"
#include "FontDlg.h"
#include "ColorDlg.h"
#include "PluginDlg.h"
#include "CTryDlg.h"
#include "SAboutDlg.h"
#include "OPluginDlg.h"
#include "afxwin.h"
#include "Label/Label.h"


// CVc6ConfigerDlg 对话框
class CVc6ConfigerDlg : public CDialog
{
// 构造
public:
	CVc6ConfigerDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_VC6CONFIGER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CTabSheet m_TabCtrl;
	CIncDlg m_IncDlg;
	CFontDlg m_FontDlg;
	CColorDlg m_ColorDlg;
	CPluginDlg m_PluginDlg;
	CCTryDlg m_TryDlg;
	CSAboutDlg m_AboutDlg;
	COPluginDlg m_OPluginDlg;
	//CExtStatusControlBar m_wndStatusBar;
	CStatusBarCtrl m_wndStatusBar;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnNMClickSyslink(NMHDR *pNMHDR, LRESULT *pResult);
	CLabel m_AboutStatic;
protected:
	virtual void OnCancel();
};
