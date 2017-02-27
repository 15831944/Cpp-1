#pragma once
#include "newbutton.h"
#include "stime.h"


// CLoadFile 对话框
#define WM_ADDSTRING WM_USER+8888
struct Add_Info
{
	wchar_t Name[128];
	wchar_t Path[MAX_PATH];
	wchar_t Data[128];
	wchar_t Time[52];
};
class CLoadFile : public CDialogEx
{
	DECLARE_DYNAMIC(CLoadFile)

public:
	CLoadFile(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CLoadFile();

// 对话框数据
	enum { IDD = IDD_D_LOADFILE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CFont m_font;
	wchar_t m_dir[MAX_PATH];
	CWinThread *pthread;
	DWORD num,cnum;
public:
	void TTfind(CString dir);
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg LRESULT OnNcHitTest(CPoint point);
	NewButton m_bclose;
	afx_msg void OnBnClickedBClose();
	CStime m_sshow;
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	CStime m_sw1;
	CStime m_sw2;
	CStime m_sw3;
	CStime m_bnum;
	CStime m_cnum;
};
