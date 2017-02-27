#pragma once
#include "newbutton.h"
#include "afxwin.h"


// CSetMusic 对话框
#define WM_SETINFO WM_USER+13142
struct SetInfo
{
	int notify;
	int windowspoint;
	int seek;
	int playup;
};
class CSetMusic : public CDialogEx
{
	DECLARE_DYNAMIC(CSetMusic)

public:
	CSetMusic(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSetMusic();

// 对话框数据
	enum { IDD = IDD_D_SET };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CFont m_font;
	bool issave;
	wchar_t Current_Path[MAX_PATH];
	void SaveInfo();
	void ReadInfo();
public:
	NewButton m_bclose;
	afx_msg void OnBnClickedBClose();
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnPaint();
	afx_msg LRESULT OnNcHitTest(CPoint point);
	afx_msg void OnClose();
	NewButton m_bsaveset;
	afx_msg void OnBnClickedCClosesmall();
	afx_msg void OnBnClickedCSavewindowpoint();
	afx_msg void OnBnClickedCOpenplaymusic();
	afx_msg void OnBnClickedCSeekmusic();
	CButton m_croot;
	CButton m_cclose;
	CButton m_csave;
	CButton m_copen;
	CButton m_cseek;
	afx_msg void OnBnClickedCRoot();
	afx_msg void OnBnClickedBSaveset();
};
