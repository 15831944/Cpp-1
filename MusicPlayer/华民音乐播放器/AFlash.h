#pragma once


// CAFlash �Ի���

class CAFlash : public CDialogEx
{
	DECLARE_DYNAMIC(CAFlash)

public:
	CAFlash(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CAFlash();

// �Ի�������
	enum { IDD = IDD_D_ABOUTFLASH };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CDC m_dcBk;
	CFont m_font;
	int movey[8],movex[8],endmovey[8],endmovex[8];
	int smovex[8],smovey[8],endsmovex[8],endsmovey[8];
	int mcount;
	bool ismove,isshu;
	int m_k[8];
	int knum;
public:
	void DrawImageText();
	void Init();
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
