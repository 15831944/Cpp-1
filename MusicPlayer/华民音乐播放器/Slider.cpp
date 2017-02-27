// Slider.cpp : 实现文件
//

#include "stdafx.h"
#include "华民音乐播放器.h"
#include "Slider.h"


// CSlider

IMPLEMENT_DYNAMIC(CSlider, CSliderCtrl)

CSlider::CSlider()
{

}

CSlider::~CSlider()
{
}


BEGIN_MESSAGE_MAP(CSlider, CSliderCtrl)
	ON_WM_PAINT()
	ON_WM_SETCURSOR()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()



// CSlider 消息处理程序




void CSlider::PreSubclassWindow()
{
	// TODO: 在此添加专用代码和/或调用基类
	x=0;
	CSliderCtrl::PreSubclassWindow();
}


void CSlider::OnPaint()
{
	CPaintDC pdc(this); // device context for painting
	CRect rect;
	GetClientRect(&rect);
	CBitmap map,*oldmap;
	CDC dc;
	dc.CreateCompatibleDC(&pdc);
	map.CreateCompatibleBitmap(&pdc,rect.right,rect.bottom);
	oldmap=dc.SelectObject(&map);
	pdc.SetStretchBltMode(SBM_ENABLE_ARROWS);
	dc.SetStretchBltMode(SBM_ENABLE_ARROWS);
	dc.BitBlt(0,0,rect.right,rect.bottom,&m_dcBk,0,0,SRCCOPY);
	CRect drect;
	this->GetChannelRect(&drect);
	dc.FillSolidRect(drect,RGB(255,234,243));
	this->GetThumbRect(&drect);
	dc.FillSolidRect(drect,RGB(255,123,134));
	pdc.BitBlt(0,0,rect.right,rect.bottom,&dc,0,0,SRCCOPY);
	dc.DeleteDC();
	pdc.SelectObject(oldmap);
}


BOOL CSlider::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	::SetCursor(AfxGetApp()->LoadCursorW(IDC_CUR1));
	return true;//CSliderCtrl::OnSetCursor(pWnd, nHitTest, message);
}


BOOL CSlider::OnEraseBkgnd(CDC* pDC)
{
	CClientDC clientDC(GetParent());///得到窗口DC 
    CRect crect;
    CRect wrect;
    GetClientRect(crect);//得到DC绘图大小
    GetWindowRect(wrect);//得到窗口大小
    GetParent()->ScreenToClient(wrect);//转化坐标
    if(m_dcBk.m_hDC==NULL)
	{
			CBitmap m_bmpBk,*m_bmpBkOld;
               m_dcBk.CreateCompatibleDC(&clientDC);//创建兼容DC  
               m_bmpBk.CreateCompatibleBitmap(&clientDC, crect.Width(), crect.Height());//创建兼容位图
               m_bmpBkOld = m_dcBk.SelectObject(&m_bmpBk);///将位图选入DC
               m_dcBk.BitBlt(0, 0, crect.Width(), crect.Height(), &clientDC, wrect.left, wrect.top, SRCCOPY);
			   m_bmpBk.DeleteObject();
			m_bmpBkOld->DeleteObject();
	}
	return true;//CButton::OnEraseBkgnd(pDC);
}
