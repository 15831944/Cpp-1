#pragma once


// COSlider �Ի���
#define WM_NUMBER WM_USER+8888
class COSlider : public CDialogEx
{
	DECLARE_DYNAMIC(COSlider)

public:
	COSlider(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~COSlider();

// �Ի�������
	enum { IDD = IDD_D_OSLIDER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	int hx;
	DWORD Num_Max,dstart,dsave;
	bool isml,issize;
	bool isup,is_moveto_end;
	int max_size;
public:
	void DrawH();
	void SetSize(DWORD num,int Height);
	int SelectNum(int num);
	void MoveToEnd();
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnPaint();
	afx_msg void OnMouseHover(UINT nFlags, CPoint point);
	afx_msg void OnMouseLeave();
};
