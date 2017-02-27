// AFlash.cpp : 实现文件
//

#include "stdafx.h"
#include "华民音乐播放器.h"
#include "AFlash.h"
#include "afxdialogex.h"


// CAFlash 对话框

IMPLEMENT_DYNAMIC(CAFlash, CDialogEx)

CAFlash::CAFlash(CWnd* pParent /*=NULL*/)
	: CDialogEx(CAFlash::IDD, pParent)
{

}

CAFlash::~CAFlash()
{
}

void CAFlash::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CAFlash, CDialogEx)
	ON_WM_PAINT()
	ON_WM_CTLCOLOR()
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CAFlash 消息处理程序


BOOL CAFlash::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	m_font.CreateFontW(15,0,0,0,FW_BOLD,0,0,0,ANSI_CHARSET,0,0,0,0,L"隶书");
	Init();
	SetTimer(1,4,NULL);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CAFlash::Init()
{
	int y=10;
	for(int i=0;i<8;i++)
	{
		movey[i]=280;
		movex[i]=30;
		endmovey[i]=y;
		y=20+y;
	}
	int y1=270;
	for(int j=0;j<8;j++)
	{
		smovey[j]=y1;
		y1=y1-30;
		m_k[j]=0;
	}
	mcount=0;
	ismove=false;
	isshu=false;
	knum=0;
}

void CAFlash::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	DrawImageText();
}


HBRUSH CAFlash::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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
	return NULL;
}

void CAFlash::DrawImageText()
{
	wchar_t *move_str[8]={L"编译员： 成明",L"界面设计： 成明",L"软件测试： 陈立波",
		L"后期维护： 成明",L"如果大家喜欢本软件或则有兴趣一起研究的话",L"请联系以下方式:",
		L"QQ:1028912140",L"邮箱:cheng8214@163.com"};
	wchar_t *move_str1[8]={L"划\r\n地\r\n三\r\n尺\r\n只\r\n为\r\n转\r\n世\r\n灵\r\n魂\r\n换\r\n你\r\n的\r\n生\r\n辰",
		L"诵\r\n一\r\n段\r\n因\r\n果",
		L"结\r\n来\r\n世\r\n的\r\n红\r\n绳",
		L"绣\r\n花\r\n针\r\n针\r\n恨",
		L"缝\r\n鸳\r\n鸯\r\n的\r\n枕",
		L"我\r\n用\r\n一\r\n生\r\n来\r\n陪\r\n你\r\n等",
		L"等\r\n缘\r\n分\r\n认\r\n真",L"  |\r\n  |\r\n  |\r\n成\r\n明"};
	CDC *pdc=GetDC();
	CDC dc;
	CBitmap map,*oldmap;
	dc.CreateCompatibleDC(pdc);
	CRect rect;
	GetClientRect(&rect);
	map.CreateCompatibleBitmap(pdc,rect.right,rect.bottom);
	oldmap=dc.SelectObject(&map);
	dc.BitBlt(0,0,rect.right,rect.bottom,&m_dcBk,0,0,SRCCOPY);
	dc.SetStretchBltMode(STRETCH_HALFTONE);
	dc.SetBkMode(TRANSPARENT);
	dc.SetTextColor(RGB(10,10,23));
	dc.SelectObject(m_font);
	for(int i=0;i<8;i++)
	{
	dc.TextOutW(movex[i],movey[i],move_str[i]);
	CSize size=dc.GetTextExtent(move_str[i]);
	endmovex[i]=size.cx;
	}
	for(int j=0;j<8;j++)
	{
		CRect rect;
		rect.top=20;
		rect.left=smovey[j];
		rect.right=smovey[j]+12;
		rect.bottom=m_k[j];
		dc.SetTextColor(RGB(223,30,23));
		dc.DrawText(move_str1[j],rect,0);
		CSize size=dc.GetTextExtent(move_str1[j]);
		endsmovey[j]=size.cx;
	}
	pdc->BitBlt(0,0,rect.right,rect.bottom,&dc,0,0,SRCCOPY);
	dc.SelectObject(oldmap);
	map.DeleteObject();
	ReleaseDC(pdc);
	if(isshu)
	{
		KillTimer(1);
		SetTimer(2,4,NULL);
	}
	else
	{
		KillTimer(2);
		SetTimer(1,4,NULL);
	}
}


void CAFlash::OnTimer(UINT_PTR nIDEvent)
{
	if(nIDEvent==1)
	{
		if(!ismove)
		{
		movey[mcount]--;
		if(movey[mcount]==endmovey[mcount])
			mcount+=1;
		}
		else
		{
			movex[mcount]--;
			if(movex[mcount]==-endmovex[mcount])
			mcount+=1;
			if(mcount>=8)
		{
			isshu=true;
			mcount=0;
			ismove=false;
		}
		}
		if(mcount>=8)
		{
			ismove=true;
			mcount=0;
		}
		DrawImageText();
	}
	if(nIDEvent==2)
	{
		knum++;
		m_k[mcount]++;
		if(m_k[mcount]>=endsmovey[mcount]+50)
			mcount+=1;
		if(mcount>=8&&knum>1500)
		{
			Init();
		}
		DrawImageText();
	}
	CDialogEx::OnTimer(nIDEvent);
}