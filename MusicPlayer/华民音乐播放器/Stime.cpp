// Stime.cpp : 实现文件
//

#include "stdafx.h"
#include "华民音乐播放器.h"
#include "Stime.h"


// CStime

IMPLEMENT_DYNAMIC(CStime, CStatic)

CStime::CStime()
{

}

CStime::~CStime()
{
}


BEGIN_MESSAGE_MAP(CStime, CStatic)
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
	ON_WM_TIMER()
END_MESSAGE_MAP()



// CStime 消息处理程序



void CStime::PreSubclassWindow()
{
	memset(st,0x00,sizeof(st));
	iscl=isgd=false;
	mx=0;
	m_font.CreateFont(14,0,0,0,400,0,0,ANSI_CHARSET,0,0,0,0,0,L"Arial");
	CStatic::PreSubclassWindow();
}

void CStime::OnPaint()
{
	CPaintDC pdc(this);
	CDC dc;
	CBitmap map,*old;
	CRect rect;
	GetClientRect(&rect);
	map.CreateCompatibleBitmap(&pdc,rect.right,rect.bottom);
	dc.CreateCompatibleDC(&pdc);
	old=dc.SelectObject(&map);
	dc.BitBlt(0,0,rect.right,rect.bottom,& m_dcBk,0,0,SRCCOPY);
	dc.SelectObject(&m_font);
	dc.SetBkMode(TRANSPARENT);
	if(!iscl)
	dc.SetTextColor(RGB(255,255,255));
	else
		dc.SetTextColor(m_cl);
	if(isgd)
	{
	size=dc.GetTextExtent(st);
	if(size.cx>rect.right)
		SetTimer(1,200,NULL);
	else
	{
		KillTimer(1);
		mx=0;
	}
	}
	dc.TextOut(mx,0,st);
	pdc.BitBlt(0,0,rect.right,rect.bottom,&dc,0,0,SRCCOPY);
	dc.SelectObject(old);
	dc.DeleteDC();
}

void CStime::InputText(wchar_t *text)
{
	memset(st,0x00,sizeof(st));
	wcscpy_s(st,text);
	Invalidate();
}

void CStime::SetColor(COLORREF cl)
{
	iscl=true;
	m_cl=cl;
	Invalidate(false);
}

BOOL CStime::OnEraseBkgnd(CDC* pDC)
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

void CStime::SCreateFont(int size,wchar_t *name)
{
	if(m_font.m_hObject)
	m_font.DeleteObject();
	m_font.CreateFont(size,0,0,0,400,0,0,ANSI_CHARSET,0,0,0,0,0,name);
}

void CStime::OnTimer(UINT_PTR nIDEvent)
{
	if(nIDEvent==1)
	{
		CRect rect;
		GetClientRect(&rect);
		mx-=2;
		if(mx+size.cx<0)
			mx=6;
		Invalidate(false);
	}
	CStatic::OnTimer(nIDEvent);
}

void CStime::SetGD(bool gd)
{
	isgd=gd;
}