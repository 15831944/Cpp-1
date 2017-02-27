#pragma once
#include "NewButton.h"
#include "AFlash.h"

// CAbout �Ի���

class CAbout : public CDialog
{
	DECLARE_DYNAMIC(CAbout)

public:
	CAbout(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CAbout();

// �Ի�������
	enum { IDD = IDD_D_ABOUT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CImage image;
	wchar_t m_CurrentPath[MAX_PATH];
	CFont m_font,m_f;
	CAFlash *m_aflash;
	M_ID id;
public:
	afx_msg void OnBnClickedBClose();
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	NewButton m_bclose;
	afx_msg LRESULT OnNcHitTest(CPoint point);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
