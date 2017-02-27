#pragma once


// CVslider �Ի���
#define WM_SENDVALUE WM_USER+5555
class CVslider : public CDialogEx
{
	DECLARE_DYNAMIC(CVslider)

public:
	CVslider(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CVslider();

// �Ի�������
	enum { IDD = IDD_D_VSLIDER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	int hx,lpt,spt;
	CDC m_dcBk;
	int max_number,m_sel;
	bool ishl,iscur;
	HCURSOR m_cur;
public:
	void DrawH();
	void SetSize(int num);
	void SelectNumber(int sel);

public:
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnMouseLeave();
	afx_msg void OnMouseHover(UINT nFlags, CPoint point);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnMove(int x, int y);
};
