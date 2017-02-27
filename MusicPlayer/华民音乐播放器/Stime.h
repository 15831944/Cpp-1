#pragma once


// CStime

class CStime : public CStatic
{
	DECLARE_DYNAMIC(CStime)

public:
	CStime();
	virtual ~CStime();

protected:
	DECLARE_MESSAGE_MAP()
public:
	wchar_t st[255];
	CDC  m_dcBk;
	CFont m_font;
	int mx;
	CSize size;
	bool isgd,iscl;
	COLORREF m_cl;
public:
	void SCreateFont(int size,wchar_t *name);
	void InputText(wchar_t *text);
	void SetGD(bool gd);
	void SetColor(COLORREF cl);
public:
	afx_msg void OnPaint();
	virtual void PreSubclassWindow();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};


