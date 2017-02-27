// OSlider.cpp : 实现文件
//

#include "stdafx.h"
#include "华民音乐播放器.h"
#include "OSlider.h"
#include "afxdialogex.h"


// COSlider 对话框

IMPLEMENT_DYNAMIC(COSlider, CDialogEx)

COSlider::COSlider(CWnd* pParent /*=NULL*/)
	: CDialogEx(COSlider::IDD, pParent)
{

}

COSlider::~COSlider()
{
}

void COSlider::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(COSlider, CDialogEx)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_PAINT()
	ON_WM_MOUSEHOVER()
	ON_WM_MOUSELEAVE()
END_MESSAGE_MAP()


// COSlider 消息处理程序


BOOL COSlider::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	hx=0;
	Num_Max=0;
	dstart=0;
	dsave=0;
	issize=isml=false;
	is_moveto_end=isup=false;
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void COSlider::OnLButtonDown(UINT nFlags, CPoint point)
{
	if(Num_Max==0)
	{
		hx=0;
			return;
	}
	CRect rect,crect;
	GetClientRect(&rect);
	crect.SetRect(0,hx,20,max_size+hx);
	if(crect.PtInRect(point))
	{
	dstart=point.y;
	isup=true;
	}
	CDialogEx::OnLButtonDown(nFlags, point);
}


void COSlider::OnLButtonUp(UINT nFlags, CPoint point)
{
	if(Num_Max==0)
	{
		hx=0;
			return;
	}
	CRect rect,crect;
	GetClientRect(&rect);
	crect.SetRect(0,hx,20,max_size+hx);
	if(crect.PtInRect(point))
	{
		dsave=hx;
		isup=false;
	}
	CDialogEx::OnLButtonUp(nFlags, point);
}


void COSlider::OnMouseMove(UINT nFlags, CPoint point)
{
	if(Num_Max==0)
	{
		hx=0;
			return;
	}
	TRACKMOUSEEVENT tme;
	if(!isml)
	{
		tme.cbSize=sizeof(TRACKMOUSEEVENT);
		tme.dwFlags=TME_HOVER|TME_LEAVE;
		tme.dwHoverTime=1;
		tme.hwndTrack=m_hWnd;
		_TrackMouseEvent(&tme);
	}
	CRect rect,crect;
	GetClientRect(&rect);
	crect.SetRect(0,hx,20,max_size+hx);
	if(nFlags&VK_LBUTTON)
	{
		if(crect.PtInRect(point))
		{
			hx=point.y-dstart+dsave;
			if(hx<=0)
				hx=0;
			if(hx>=(rect.bottom-max_size))
					hx=rect.bottom-max_size;
		DrawH();
		float dw=(float)Num_Max/(rect.bottom-max_size);
		float num=dw*(float)hx;
		GetParent()->SendMessage(WM_NUMBER,0,(DWORD)num);
		}
	}
	CDialogEx::OnMouseMove(nFlags, point);
}


void COSlider::OnPaint()
{
	CPaintDC pdc(this);
	DrawH();
}

void COSlider::DrawH()
{
	CRect rect;
	GetClientRect(&rect);
	if(!issize)
		max_size=rect.bottom;
	CDC *pdc=GetDC();
	CDC dc;
	dc.CreateCompatibleDC(pdc);
	CBitmap map,*old;
	map.CreateCompatibleBitmap(pdc,rect.right,rect.bottom);
	old=dc.SelectObject(&map);
	CPen pen,*oldpen;
	pen.CreatePen(BS_SOLID,1,RGB(255,255,255));
	oldpen=dc.SelectObject(&pen);

	CBrush brush,*oldbrush;
	brush.CreateSolidBrush(RGB(239,248,255));
	oldbrush=dc.SelectObject(&brush);
	dc.Rectangle(0,0,rect.right,rect.bottom);
	dc.SelectObject(oldbrush);
	brush.DeleteObject();

	brush.CreateSolidBrush(RGB(140,206,238));
	oldbrush=dc.SelectObject(&brush);
	dc.Rectangle(0,hx,20,max_size+hx);
	dc.SelectObject(oldbrush);
	brush.DeleteObject();
	pdc->BitBlt(0,0,rect.right,rect.bottom,&dc,0,0,SRCCOPY);
	dc.SelectObject(old);
	dc.SelectObject(oldpen);
	pen.DeleteObject();
	dc.DeleteDC();
	this->ReleaseDC(pdc);
}


void COSlider::SetSize(DWORD num,int Height)
{
	Num_Max=num;
	CRect rect;
	GetClientRect(&rect);
	if(num==0)
	{
		hx=0;
		max_size=rect.bottom;
	}
	CRect wrect;
	GetParent()->GetClientRect(&wrect);
	if(Height!=0)
	{
	int m_fnum=(wrect.bottom+25)/Height;
	if((int)num>m_fnum)
	{
		int dsize=num-m_fnum;
		max_size=rect.bottom-dsize;
		if(max_size<20)
			max_size=20;
	}
	}
	issize=true;
	DrawH();
}

void COSlider::OnMouseHover(UINT nFlags, CPoint point)
{
	isml=true;
	CDialogEx::OnMouseHover(nFlags, point);
}


void COSlider::OnMouseLeave()
{
	isml=false;
	if(isup)
		dsave=hx;
	CDialogEx::OnMouseLeave();
}

int COSlider::SelectNum(int num)
{
	CRect rect;
	GetClientRect(&rect);
	//每一格需要多少移动.hx代表移动几格
	float dw=(float)Num_Max/(rect.bottom-max_size);
		float sel=(float)num/dw;
		hx=(int)sel;
		dsave=hx;
	DrawH();
	return true;
}

void COSlider::MoveToEnd()
{
	//DrawH();
}