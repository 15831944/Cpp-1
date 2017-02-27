#pragma once


// CBlist

class CBlist : public CButton
{
	DECLARE_DYNAMIC(CBlist)

public:
	CBlist();
	virtual ~CBlist();

protected:
	DECLARE_MESSAGE_MAP()
public:
	int x;
	DWORD dwsize;
	CDC		m_dcBk;	
	bool isdown;
	bool ishl;
public:
	void SetSize(DWORD size);
	void SetNumber(DWORD num);
public:
	afx_msg void OnMouseLeave();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnMouseHover(UINT nFlags, CPoint point);
	virtual void PreSubclassWindow();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnPaint();
};


