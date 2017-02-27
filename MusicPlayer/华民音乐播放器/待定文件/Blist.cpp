// Blist.cpp : 实现文件
//

#include "stdafx.h"
#include "华民音乐播放器.h"
#include "Blist.h"


// CBlist

IMPLEMENT_DYNAMIC(CBlist, CButton)

CBlist::CBlist()
{
	x=0;
}

CBlist::~CBlist()
{
}


BEGIN_MESSAGE_MAP(CBlist, CButton)
	ON_WM_MOUSELEAVE()
	ON_WM_MOUSEMOVE()
	ON_WM_MOUSEHOVER()
	ON_WM_ERASEBKGND()
	ON_WM_PAINT()
END_MESSAGE_MAP()



// CBlist 消息处理程序


void CBlist::PreSubclassWindow()
{
	dwsize=0;
	isdown=false;
	ishl=false;
	CButton::PreSubclassWindow();
}



void CBlist::OnMouseLeave()
{
	ishl=false;
	CButton::OnMouseLeave();
}


void CBlist::OnMouseMove(UINT nFlags, CPoint point)
{
	if(ishl==false)
	{
		TRACKMOUSEEVENT tme;
		tme.cbSize=sizeof(TRACKMOUSEEVENT);
		tme.dwFlags=TME_HOVER|TME_LEAVE;
		tme.dwHoverTime=1;
		tme.hwndTrack=this->m_hWnd;
		_TrackMouseEvent(&tme);

	}
	CButton::OnMouseMove(nFlags, point);
}


void CBlist::OnMouseHover(UINT nFlags, CPoint point)
{
	ishl=true;
	CButton::OnMouseHover(nFlags, point);
}

void CBlist::SetSize(DWORD size)
{
	CRect rect;
	GetClientRect(&rect);
	dwsize=size/rect.right;
}

void CBlist::SetNumber(DWORD num)
{
	CRect rect;
	GetClientRect(&rect);
	if(num<=0)
		return;
	x=num/dwsize;
	if(x+5>=rect.right)
		return;
	Invalidate(false);
}


BOOL CBlist::OnEraseBkgnd(CDC* pDC)
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


void CBlist::OnPaint()
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
	int cx=0;
	cx=(rect.bottom-5)/2;
	dc.FillSolidRect(0,cx,rect.right,cx,RGB(223,233,222));
	CRect hrect;
	hrect.SetRect(x,2,x+5,14);
	dc.FillSolidRect(hrect,RGB(255,rand()%255,255));
	pdc.BitBlt(0,0,rect.right,rect.bottom,&dc,0,0,SRCCOPY);
	dc.DeleteDC();
	pdc.SelectObject(oldmap);
}
