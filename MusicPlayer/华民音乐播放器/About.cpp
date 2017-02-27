// About.cpp : 实现文件
//

#include "stdafx.h"
#include "华民音乐播放器.h"
#include "About.h"
#include "afxdialogex.h"


// CAbout 对话框

IMPLEMENT_DYNAMIC(CAbout, CDialog)

CAbout::CAbout(CWnd* pParent /*=NULL*/)
	: CDialog(CAbout::IDD, pParent)
{

}

CAbout::~CAbout()
{
}

void CAbout::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_B_CLOSE, m_bclose);
}


BEGIN_MESSAGE_MAP(CAbout, CDialog)
	ON_BN_CLICKED(IDC_B_CLOSE, &CAbout::OnBnClickedBClose)
	ON_WM_PAINT()
	ON_WM_NCHITTEST()
	ON_WM_ERASEBKGND()
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CAbout 消息处理程序


void CAbout::OnBnClickedBClose()
{
	CHCloseMusic(id);
	m_font.DeleteObject();
	EndDialog(0);
}

BOOL CAbout::OnInitDialog()
{
	CDialog::OnInitDialog();
	m_bclose.SetButtonImage(IDB_P_C1,IDB_P_C2,IDB_P_C3);
	m_bclose.SetTip(L"关闭");
	GetCurrentDirectory(MAX_PATH,m_CurrentPath);
	wchar_t dir[MAX_PATH];
	wsprintf(dir,L"%s\\Image\\About1.jpeg",m_CurrentPath);
	image.Load(dir);
	memset(dir,0x00,sizeof(dir));
	wsprintf(dir,L"%s\\sounds\\sounds.mp3",m_CurrentPath);
	char path[MAX_PATH];
	CHWcharToAchar(dir,path);
	id=CHOpenMusic(path);
	CHPlayMusic(id);
	SetTimer(1,500,NULL);
	m_font.CreateFontW(15,0,0,0,FW_BOLD,0,0,0,ANSI_CHARSET,0,0,0,0,L"楷体");
	m_aflash=new CAFlash;
	m_aflash->Create(IDD_D_ABOUTFLASH,this);
	m_aflash->ShowWindow(SW_SHOW);
	CRect rect;
		GetClientRect(&rect);
		m_aflash->MoveWindow(0,20,rect.right,rect.bottom-20);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CAbout::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	CRect rect;
	dc.SetStretchBltMode(STRETCH_HALFTONE);
	GetClientRect(&rect);
	if(!image.IsNull())
	image.Draw(dc.m_hDC,rect);
	dc.SetBkMode(TRANSPARENT);
	dc.SetTextColor(RGB(10,10,23));
	dc.SelectObject(m_font);
	dc.FillSolidRect(0,0,rect.right,20,RGB(41,167,199));
	dc.TextOutW(2,2,L"关于华民");
}


LRESULT CAbout::OnNcHitTest(CPoint point)
{
	CRect rect;
	GetClientRect(&rect);
	ClientToScreen(&rect);
	return rect.PtInRect(point)?HTCAPTION:CDialog::OnNcHitTest(point);
}


BOOL CAbout::OnEraseBkgnd(CDC* pDC)
{
	return false;
}


void CAbout::OnTimer(UINT_PTR nIDEvent)
{
	if(nIDEvent==1)
	{
	DWORD pos=CHGetMusicPosition(id);
		if(pos==CHGetMusicTime(id))
		{
			CHSeekMusic(id,0);
			CHPlayMusic(id);
		}
	}
	CDialog::OnTimer(nIDEvent);
}
