
// Vc6ConfigerDlg.h : ͷ�ļ�
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


// CVc6ConfigerDlg �Ի���
class CVc6ConfigerDlg : public CDialog
{
// ����
public:
	CVc6ConfigerDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_VC6CONFIGER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
