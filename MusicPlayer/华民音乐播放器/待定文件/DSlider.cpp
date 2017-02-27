// DSlider.cpp : 实现文件
//

#include "stdafx.h"
#include "华民音乐播放器.h"
#include "DSlider.h"
#include "afxdialogex.h"


// CDSlider 对话框

IMPLEMENT_DYNAMIC(CDSlider, CDialogEx)

CDSlider::CDSlider(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDSlider::IDD, pParent)
{

}

CDSlider::~CDSlider()
{
}

void CDSlider::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDSlider, CDialogEx)
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
	ON_WM_SETCURSOR()
	ON_WM_MOUSEMOVE()
	ON_WM_MOUSEHOVER()
	ON_WM_MOUSELEAVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()


// CDSlider 消息处理程序


BOOL CDSlider::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	x=0;
	issize=false;
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CDSlider::OnPaint()
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
	hrect.SetRect(x,2,x+5,14);
	dc.FillSolidRect(hrect,RGB(255,rand()%255,255));
	pdc.BitBlt(0,0,rect.right,rect.bottom,&dc,0,0,SRCCOPY);
	dc.DeleteDC();
	pdc.SelectObject(oldmap);
}


BOOL CDSlider::OnEraseBkgnd(CDC* pDC)
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

void CDSlider::SetSize(DWORD size)
{
	CRect rect;
	GetClientRect(&rect);
	if(DWORD(rect.right)>size)
	{
		dwsize=rect.right/size;
		issize=true;
	}
	else
	{
	dwsize=size/rect.right;
	issize=false;
	}
}

void CDSlider::SetNumber(DWORD num)
{
	CRect rect;
	GetClientRect(&rect);
	if(num<=0)
		return;
	if(issize)
		x=num*dwsize;
	else
	x=num/dwsize;
	if(x+10>=rect.right)
		return;
	Invalidate(false);
}


BOOL CDSlider::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
		::SetCursor(AfxGetApp()->LoadCursorW(IDC_CUR1));
		return true;
	//return CDialogEx::OnSetCursor(pWnd, nHitTest, message);
}


void CDSlider::OnMouseMove(UINT nFlags, CPoint point)
{

	CRect rect;
	GetClientRect(&rect);
	point.x=point.x-2;
	if(nFlags==MK_LBUTTON)
	{
		if(hrect.PtInRect(point))
		{
		x=point.x;
		if(x+5>rect.right)
		return;
		Invalidate();
		}
	}
	CDialogEx::OnMouseMove(nFlags, point);
}


void CDSlider::OnMouseHover(UINT nFlags, CPoint point)
{

	CDialogEx::OnMouseHover(nFlags, point);
}


void CDSlider::OnMouseLeave()
{

	CDialogEx::OnMouseLeave();
}


void CDSlider::OnLButtonDown(UINT nFlags, CPoint point)
{
	CRect rect;
	GetClientRect(&rect);
	x=(int)point.x-2;
	if(x+5>rect.right)
		return;
	Invalidate();
	CDialogEx::OnLButtonDown(nFlags, point);
}


void CDSlider::OnLButtonUp(UINT nFlags, CPoint point)
{
	CDialogEx::OnLButtonUp(nFlags, point);
}
