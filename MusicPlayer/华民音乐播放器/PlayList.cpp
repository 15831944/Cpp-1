// PlayList.cpp : 实现文件
//

#include "stdafx.h"
#include "华民音乐播放器.h"
#include "PlayList.h"
#include "afxdialogex.h"


// CPlayList 对话框

IMPLEMENT_DYNAMIC(CPlayList, CDialogEx)

CPlayList::CPlayList(CWnd* pParent /*=NULL*/)
	: CDialogEx(CPlayList::IDD, pParent)
{

}

CPlayList::~CPlayList()
{
}

void CPlayList::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_B_CLOSE, m_bclose);
}


BEGIN_MESSAGE_MAP(CPlayList, CDialogEx)
	ON_WM_PAINT()
	ON_WM_NCHITTEST()
	ON_BN_CLICKED(IDC_B_CLOSE, &CPlayList::OnBnClickedBClose)
	ON_BN_CLICKED(IDC_B_ADD, &CPlayList::OnBnClickedBAdd)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CPlayList 消息处理程序


BOOL CPlayList::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_bclose.SetButtonImage(IDB_P_C1,IDB_P_C2,IDB_P_C3);
	m_bclose.SetTip(L"关闭");
	m_font.CreateFontW(14,0,0,0,FW_BOLD,0,0,0,0,0,0,0,FF_SWISS,L"楷体");
	m_lf.CreateFontW(14,0,0,0,FW_BOLD,0,0,0,0,0,0,0,FF_SWISS,L"隶书");
	m_bclose.isdc=false;
	mmsys dl;
	dl.LoadImageFromResource(IDB_P_LOGO1,L"PNG",&image);
	znum=0;
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CPlayList::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	CRect rect;
	GetClientRect(&rect);
	dc.FillSolidRect(rect,RGB(0,122,204));
	dc.FillSolidRect(0,0,rect.right,20,RGB(41,167,199));
	dc.SetBkMode(TRANSPARENT);
	dc.SelectObject(m_font);
	dc.SetTextColor(RGB(235,255,235));
	dc.TextOutW(0,2,L"播放列表");
	DrawH();
}

LRESULT CPlayList::OnNcHitTest(CPoint point)
{
	CRect rect;
	GetClientRect(&rect);
	ClientToScreen(&rect);
	return rect.PtInRect(point)?HTCAPTION:CDialogEx::OnNcHitTest(point);
}


BOOL CPlayList::PreTranslateMessage(MSG* pMsg)
{
	if(pMsg->message==WM_KEYDOWN)
	{
		if(pMsg->wParam==VK_RETURN)
			return true;
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}


void CPlayList::OnBnClickedBClose()
{
	ShowWindow(SW_HIDE);
}

void CPlayList::DrawH()
{
	CRect rect;
	GetClientRect(&rect);
	CDC *pdc=GetDC();
	CDC dc;
	dc.CreateCompatibleDC(pdc);
	CBitmap map,*oldmap;
	CPen pen,*oldpen;
	map.CreateCompatibleBitmap(pdc,rect.right,rect.bottom-45);
	pen.CreatePen(PS_SOLID,1,RGB(0,122,204));
	oldmap=dc.SelectObject(&map);
	oldpen=dc.SelectObject(&pen);
	dc.Rectangle(0,0,rect.right,rect.bottom-45);
	dc.SelectObject(oldpen);
	pen.DeleteObject();
	int y=2;
	CBrush brush,*oldbrush;
	brush.CreateSolidBrush(RGB(217,222,220));
	oldbrush=dc.SelectObject(&brush);
	dc.SelectObject(m_lf);
	dc.SetStretchBltMode(STRETCH_HALFTONE);
	if(znum==0)
	{
		CImage m_image;
		mmsys dl;
		dl.LoadImageFromResource(IDB_P_LISTTIP,TEXT("PNG"),&m_image);
		if(!m_image.IsNull())
			m_image.Draw(dc.m_hDC,2,80);
	}else
	for(int i=0;i<znum;i++)
	{
		dc.Rectangle(2,y,rect.right-2,25+y);
		if(!image.IsNull())
			image.Draw(dc.m_hDC,2,y+2,18,18);
		Play_ListItem *p=phead;
		while(p!=NULL)
		{
		dc.SetTextColor(RGB(0,122,204));
		dc.SetBkMode(TRANSPARENT);
		CString data;
		data.Format(L"%s(%d)",p->Name,p->AllNumber);
		dc.TextOutW(24,y+5,data);
		p=p->link;
		}
		y=y+27;
	}
	dc.SelectObject(oldbrush);
	brush.DeleteObject();
	pdc->BitBlt(0,20,rect.right,rect.bottom,&dc,0,0,SRCCOPY);
	dc.SelectObject(oldmap);
	map.DeleteObject();
	dc.DeleteDC();
	ReleaseDC(pdc);
}

void CPlayList::OnBnClickedBAdd()
{
	CAddList dlg;
	dlg.DoModal();
}

BOOL CPlayList::InserList(wchar_t *name)
{
	pnew=new Play_ListItem;
	wcscpy_s(pnew->Name,name);
	pnew->num+=1;
	pnew->AllNumber=0;
	if(znum==0)
		phead=prear=pnew;
	else
		prear->link=pnew;
	pnew->link=NULL;
	prear=pnew;
	znum+=1;
	DrawH();
	return true;
}

void CPlayList::OnClose()
{
	m_font.DeleteObject();
	m_lf.DeleteObject();
	if(!image.IsNull())
	image.Destroy();
	Play_ListItem *p=phead,*pd;
		while(p!=NULL)
		{
			pd=p->link;
			delete p;
			p=pd;
		}
	CDialogEx::OnClose();
}
