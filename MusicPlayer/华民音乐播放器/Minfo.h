#pragma once
#include "newbutton.h"
#include "stime.h"


// CMinfo 对话框

class CMinfo : public CDialogEx
{
	DECLARE_DYNAMIC(CMinfo)

public:
	CMinfo(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CMinfo();

// 对话框数据
	enum { IDD = IDD_D_INFO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	wchar_t m_Path[MAX_PATH];
	CFont m_font;
	void ReadMusicInfo();
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg LRESULT OnNcHitTest(CPoint point);
	NewButton m_bclose;
	afx_msg void OnBnClickedBClose();
	afx_msg void OnClose();
	afx_msg void OnBnClickedBuOk();
	CStime m_st1;
	CStime m_st2;
	CStime m_st3;
	CStime m_st6;
	CStime m_st4;
	CStime m_st5;
	CStime m_st7;
	CStime m_st8;
	CStime m_st9;
	CStime m_sname;
	CStime m_spath;
	CStime m_sfilesize;
	CStime m_sfiletype;
	CStime m_smusicname;
	CStime m_ssong;
	CStime m_syear;
	CStime m_sbt;
	CStime m_sbz;
	NewButton m_baclose;
	afx_msg void OnBnClickedBOpenfileselect();
	NewButton m_bopen;
};
