// NewButton.cpp : 实现文件
//

#include "stdafx.h"
#include "华民音乐播放器.h"
#include "NewButton.h"


// NewButton

IMPLEMENT_DYNAMIC(NewButton, CButton)

NewButton::NewButton()
{
	isleave=true;
	isdc=false;
}

NewButton::~NewButton()
{
	if(!m1.IsNull())
		m1.Destroy();
	if(!m2.IsNull())
		m2.Destroy();
	if(!m3.IsNull())
		m3.Destroy();
	m_font.DeleteObject();
}


BEGIN_MESSAGE_MAP(NewButton, CButton)
	
	ON_WM_MOUSEMOVE()
	ON_WM_SETCURSOR()
	ON_WM_MOUSELEAVE()
	ON_WM_MOUSEHOVER()
	ON_WM_ERASEBKGND()
	ON_WM_CTLCOLOR_REFLECT()
END_MESSAGE_MAP()



// NewButton 消息处理程序



void NewButton::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	CRect rect=lpDrawItemStruct->rcItem;
	UINT state=lpDrawItemStruct->itemState;
	CDC *pdc=CDC::FromHandle(lpDrawItemStruct->hDC); 
   CRect crect;
    GetClientRect(crect);//得到DC绘图大小
	CBitmap map,*oldmap;
	map.CreateCompatibleBitmap(pdc,rect.right,rect.bottom);
	CDC bdc;
	bdc.CreateCompatibleDC(pdc);
	oldmap=bdc.SelectObject(&map);
	bdc.SetStretchBltMode(STRETCH_HALFTONE);
	if(isdc)
	{
	if(m_dcBk.m_hDC)
	BitBlt(bdc.m_hDC, 0, 0, crect.Width(),crect.Height(), m_dcBk.m_hDC, 0, 0, SRCCOPY);
	if(state&ODS_SELECTED)
	{
		if(!m3.IsNull())
		m3.Draw(bdc.m_hDC,rect);
	}
	else
	{
		if(isleave)
		{
		if(!m1.IsNull())
		m1.Draw(bdc.m_hDC,rect);
		}
		else
			if(!m2.IsNull())
		m2.Draw(bdc.m_hDC,rect);
	}
	CString st;
	GetWindowText(st);
	if(!st.IsEmpty())
	{
		bdc.SelectObject(m_font);
		CSize size=bdc.GetTextExtent(st);
		int x,y;
		x=(rect.right-size.cx)/2;
		y=(rect.bottom-size.cy)/2;
		bdc.SetBkMode(TRANSPARENT);
		bdc.TextOutW(x,y,st);
	}
	pdc->BitBlt(0,0,rect.right,rect.bottom,&bdc,0,0,SRCCOPY);
	}
	map.DeleteObject();
	bdc.SelectObject(oldmap);
	bdc.DeleteDC();
	ReleaseDC(pdc);
}

void NewButton::SetButtonImage(UINT id1,UINT id2,UINT id3)
{
	mmsys dl;
	if(!m1.IsNull())
		m1.Destroy();
	if(!m2.IsNull())
		m2.Destroy();
	if(!m3.IsNull())
		m3.Destroy();
	dl.LoadImageFromResource(id1,L"PNG",&m1);
	dl.LoadImageFromResource(id2,L"PNG",&m2);
	dl.LoadImageFromResource(id3,L"PNG",&m3);
	Invalidate(false);
}

void NewButton::OnMouseMove(UINT nFlags, CPoint point)
{
	if(isleave)
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


BOOL NewButton::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	::SetCursor(AfxGetApp()->LoadCursor(IDC_CUR1));
	return true;//CButton::OnSetCursor(pWnd, nHitTest, message);
}


void NewButton::OnMouseLeave()
{
	isleave=true;
		Invalidate();
	CButton::OnMouseLeave();
}


void NewButton::OnMouseHover(UINT nFlags, CPoint point)
{
	isleave=false;
	Invalidate();
	CButton::OnMouseHover(nFlags, point);
}


BOOL NewButton::OnEraseBkgnd(CDC* pDC)
{
	return TRUE;//CButton::OnEraseBkgnd(pDC);
}


BOOL NewButton::PreTranslateMessage(MSG* pMsg)
{
	if(m_tip.m_hWnd!=NULL)
		if(IsWindow(m_tip.m_hWnd))
			m_tip.RelayEvent(pMsg);
	return CButton::PreTranslateMessage(pMsg);
}

BOOL NewButton::SetTip(LPCTSTR lpstr)
{
	if(!m_tip)
	{
		m_tip.Create(this);
		m_tip.Activate(true);
		m_tip.SetDelayTime(500);
		m_tip.AddTool(this,lpstr);
	}
	else
		m_tip.UpdateTipText(lpstr,this);
	return true;
}


void NewButton::PreSubclassWindow()
{
	m_font.CreateFontW(14,0,0,0,FW_BOLD,0,0,0,ANSI_CHARSET,0,0,0,FF_SWISS,L"隶书");
	CButton::PreSubclassWindow();
}


HBRUSH NewButton::CtlColor(CDC* /*pDC*/, UINT /*nCtlColor*/)
{
	CClientDC clientDC(GetParent());///得到窗口DC 
    CRect crect;
    CRect wrect;
    GetClientRect(crect);//得到DC绘图大小
    GetWindowRect(wrect);//得到窗口大小
    GetParent()->ScreenToClient(wrect);//转化坐标
	if(isdc==false)
	{
		if(m_dcBk.m_hDC!=NULL)
			m_dcBk.DeleteDC();
    
	{
			CBitmap m_bmpBk,*m_bmpBkOld;
               m_dcBk.CreateCompatibleDC(&clientDC);//创建兼容DC  
               m_bmpBk.CreateCompatibleBitmap(&clientDC, crect.Width(), crect.Height());//创建兼容位图
               m_bmpBkOld = m_dcBk.SelectObject(&m_bmpBk);///将位图选入DC
               m_dcBk.BitBlt(0, 0, crect.Width(), crect.Height(), &clientDC, wrect.left, wrect.top, SRCCOPY);
			   m_bmpBk.DeleteObject();
			m_bmpBkOld->DeleteObject();
			isdc=true;
	}
	}
	return NULL;
}

void NewButton::SetFontSize(wchar_t *fname,int dsize)
{
	if(m_font.m_hObject)
		m_font.DeleteObject();
	m_font.CreateFontW(dsize,0,0,0,FW_BOLD,0,0,0,ANSI_CHARSET,0,0,0,FF_SWISS,fname);
}