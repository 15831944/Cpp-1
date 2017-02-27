#pragma once


// CSlider

class CSlider : public CSliderCtrl
{
	DECLARE_DYNAMIC(CSlider)

public:
	CSlider();
	virtual ~CSlider();

protected:
	DECLARE_MESSAGE_MAP()
	virtual void PreSubclassWindow();
public:
	CDC m_dcBk;
	int x;
	CRect hrect;
public:
	afx_msg void OnPaint();
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};


