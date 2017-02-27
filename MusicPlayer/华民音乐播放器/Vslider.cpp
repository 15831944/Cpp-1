// Vslider.cpp : 实现文件
//

#include "stdafx.h"
#include "华民音乐播放器.h"
#include "Vslider.h"
#include "afxdialogex.h"


// CVslider 对话框

IMPLEMENT_DYNAMIC(CVslider, CDialogEx)

CVslider::CVslider(CWnd* pParent /*=NULL*/)
	: CDialogEx(CVslider::IDD, pParent)
{

}

CVslider::~CVslider()
{
}

void CVslider::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CVslider, CDialogEx)
	ON_WM_PAINT()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_ERASEBKGND()
	ON_WM_MOUSELEAVE()
	ON_WM_MOUSEHOVER()
	ON_WM_SETCURSOR()
END_MESSAGE_MAP()


// CVslider 消息处理程序


BOOL CVslider::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	spt=lpt=hx=0;
	max_number=0;
	m_sel=-1;
	iscur=ishl=false;
	m_cur=AfxGetApp()->LoadCursorW(IDC_CUR1);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CVslider::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	DrawH();
}

void CVslider::DrawH()
{
	CDC *pdc=GetDC();
	CDC dc;
	dc.CreateCompatibleDC(pdc);
	CBitmap map,*old;
	CRect rect;
	GetClientRect(&rect);
	map.CreateCompatibleBitmap(pdc,rect.right,rect.bottom);
	old=dc.SelectObject(&map);
	dc.BitBlt(0,0,rect.right,rect.bottom,&m_dcBk,0,0,SRCCOPY);
	int center=(rect.right-4)/2;
	dc.FillSolidRect(center,0,4,rect.bottom,RGB(239,248,255));
	CBrush brush,*oldbrush;
	brush.CreateSolidBrush(RGB(140,206,238));
	oldbrush=dc.SelectObject(&brush);
	dc.Ellipse(0,hx,rect.right,14+hx);
	pdc->BitBlt(0,0,rect.right,rect.bottom,&dc,0,0,SRCCOPY);
	dc.SelectObject(oldbrush);
	brush.DeleteObject();
	//pdc->Rectangle(0,hx,rect.right,8+hx);
	dc.SelectObject(old);
	dc.DeleteDC();
	this->ReleaseDC(pdc);
}
void CVslider::OnMouseMove(UINT nFlags, CPoint point)
{
	if(ishl==false)
	{
		TRACKMOUSEEVENT tme;
		tme.cbSize=sizeof(tme);
		tme.dwFlags=TME_HOVER|TME_LEAVE;
		tme.dwHoverTime=1;
		tme.hwndTrack=m_hWnd;
		_TrackMouseEvent(&tme);
	}
	CRect rect;
	GetClientRect(&rect);
	CRect drect;
	drect.SetRect(0,hx,rect.right,hx+14);
		if(drect.PtInRect(point))
		{
			if(nFlags==VK_LBUTTON)
		{
			hx=point.y-lpt+spt;
			if(hx<=0)
				hx=0;
			if(hx>=rect.bottom-14)
				hx=rect.bottom-14;
			float tx=(float)max_number/(rect.bottom-14);
			float num=tx*(float)hx;
			if(num<=0)
				hx=0;
			GetParent()->SendMessage(WM_SENDVALUE,(WPARAM)m_hWnd,(LPARAM)(int)num);
			DrawH();
		}
			::SetCursor(m_cur);
			iscur=true;
		}
		else
		iscur=false;
	CDialogEx::OnMouseMove(nFlags, point);
}


void CVslider::OnLButtonDown(UINT nFlags, CPoint point)
{
	lpt=point.y;
	CDialogEx::OnLButtonDown(nFlags, point);
}


void CVslider::OnLButtonUp(UINT nFlags, CPoint point)
{
	spt=hx;
	CDialogEx::OnLButtonUp(nFlags, point);
}

BOOL CVslider::OnEraseBkgnd(CDC* pDC)
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

	return true;
}

void CVslider::SetSize(int num)
{
	max_number=num;
}

void CVslider::SelectNumber(int sel)
{
	m_sel=sel;
	CRect rect;
	GetClientRect(&rect);
	float tx=(float)max_number/(rect.bottom-14);
		float num=(float)(sel+14)/tx;
		hx=(int)num;
		spt=hx;
	DrawH();
}

void CVslider::OnMouseLeave()
{
	ishl=false;
	spt=hx;
	CDialogEx::OnMouseLeave();
}


void CVslider::OnMouseHover(UINT nFlags, CPoint point)
{
	ishl=true;
	CDialogEx::OnMouseHover(nFlags, point);
}


BOOL CVslider::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	if(iscur)
	return true;
	else
	return CDialogEx::OnSetCursor(pWnd, nHitTest, message);
}
