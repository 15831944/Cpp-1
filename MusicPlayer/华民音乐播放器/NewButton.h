#pragma once


// NewButton
#include "mmsys.h"
class NewButton : public CButton
{
	DECLARE_DYNAMIC(NewButton)

public:
	NewButton();
	virtual ~NewButton();

protected:
	DECLARE_MESSAGE_MAP()
public:
	CImage m1,m2,m3;
	bool isleave;
	CToolTipCtrl m_tip;
	CDC		m_dcBk;	
	bool isdc;
	CFont m_font;
public:
	void SetButtonImage(UINT id1,UINT id2,UINT id3);
	BOOL SetTip(LPCTSTR lpstr);
	void SetFontSize(wchar_t *fname,
		int dsize);
public:
	virtual void DrawItem(LPDRAWITEMSTRUCT /*lpDrawItemStruct*/);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnMouseLeave();
	afx_msg void OnMouseHover(UINT nFlags, CPoint point);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual void PreSubclassWindow();
	afx_msg HBRUSH CtlColor(CDC* /*pDC*/, UINT /*nCtlColor*/);
};


