#pragma once


// CDSlider �Ի���

class CDSlider : public CDialogEx
{
	DECLARE_DYNAMIC(CDSlider)

public:
	CDSlider(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDSlider();

// �Ի�������
	enum { IDD = IDD_D_SLIDER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CDC m_dcBk;
	int x;
	DWORD dwsize;
	bool issize;
	HCURSOR m_cur;
	CRect hrect;
public:
	void SetSize(DWORD size);
	void SetNumber(DWORD num);
	DWORD GetNumber();
	void SetWindowSize(int x,int y,int x1,int y1);
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnMouseHover(UINT nFlags, CPoint point);
	afx_msg void OnMouseLeave();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
};
