// OList.cpp : 实现文件
//

#include "stdafx.h"
#include "华民音乐播放器.h"
#include "OList.h"
#include "afxdialogex.h"


// COList 对话框

IMPLEMENT_DYNAMIC(COList, CDialogEx)

COList::COList(CWnd* pParent /*=NULL*/)
	: CDialogEx(COList::IDD, pParent)
{

}

COList::~COList()
{
}

void COList::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(COList, CDialogEx)
	ON_WM_MOVE()
	ON_WM_PAINT()
	ON_MESSAGE(WM_NUMBER,OnNumber)
	ON_MESSAGE(WM_MOUSEHD,MouseHd)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_RBUTTONUP()
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// COList 消息处理程序


BOOL COList::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	bnum=0;
	ismove=false;
	pslider=new COSlider;
	pslider->Create(IDD_D_OSLIDER,this);
	pslider->ShowWindow(SW_SHOW);
	ismove=true;
	znum=0;    
	m_lb=m_move=-1;
	m_Height=0;
	m_fnum=0;
	m_font.CreateFont(14,0,0,0,FW_BOLD,0,0,0,ANSI_CHARSET,OUT_DEFAULT_PRECIS,
								CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,
							    DEFAULT_PITCH|FF_SWISS,L"隶书");
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void COList::OnPaint()
{
	CPaintDC pdc(this);
	DrawTextList();
}

void COList::DrawTextList()
{
	CDC *pdc=GetDC();
	CDC dc;
	dc.CreateCompatibleDC(pdc);
	CRect rect;
	GetClientRect(&rect);
	CBitmap map,*old;
	map.CreateCompatibleBitmap(pdc,rect.right,rect.bottom);
	old=dc.SelectObject(&map);
	rect.right=rect.right-20;
	dc.FillSolidRect(rect,RGB(255,255,255));
	CRect drect;
	drect.SetRect(0,0,rect.right,25);
	dc.FillSolidRect(drect,RGB(86,193,220));
	dc.SetBkMode(TRANSPARENT);
	int lx=5;
	dc.SelectObject(m_font);
	wchar_t *data[]={L"歌曲名称",L"专辑",L"歌曲时间"};
	int num[3]={300,200,50};
	for(int l=0;l<3;l++)
	{
		dc.TextOutW(lx,5,data[l]);
		lx=lx+num[l];
	}
	//因为有25为显示项的，所以应该在y加25处开始画列
	int gy=25;
	int y=m_Height;
	int i=-1;
	if(znum!=0)
	for(i=bnum;i<(bnum+m_fnum);i++)
	{
		dc.FillSolidRect(0,gy,rect.right,gy+y,RGB(255,255,255));
		CBrush brush,*oldbrush;
		CPen pen,*oldpen;
		pen.CreatePen(PS_NULL,0,RGB(0x00,0x00,0x00));
		oldpen=dc.SelectObject(&pen);
			if(i%2==0)
			{
				brush.CreateSolidBrush(RGB(235,246,250));
				oldbrush=dc.SelectObject(&brush);
			dc.Rectangle(0,gy,rect.right,gy+y);
			brush.DeleteObject();
			dc.SelectObject(oldbrush);
			}
		if(m_move!=-1&&m_move==i)
			{
				brush.CreateSolidBrush(RGB(206,248,241));
				oldbrush=dc.SelectObject(&brush);
			dc.Rectangle(0,gy-1,rect.right+1,gy+y+1);
			brush.DeleteObject();
			dc.SelectObject(oldbrush);
			}
		if(m_lb!=-1&&m_lb==i)
			{
				brush.CreateSolidBrush(RGB(186,231,241));
				oldbrush=dc.SelectObject(&brush);
			dc.Rectangle(0,gy,rect.right,gy+y);
			brush.DeleteObject();
			dc.SelectObject(oldbrush);
			}
		TextLink *p=phead;
		while(p!=NULL)
		{
			if(p->num==(int)i&&p->num!=-1)
		{
			CSize size=dc.GetTextExtent(p->Name);
			int center=(m_Height-size.cy)/2;
			CRect re;
			re.SetRect(5,gy+center,300,gy+y);
			CString st;
			wchar_t name[128]={0};
			int b=0;
			for(int j=0;j<(int)wcslen(p->Name);j++)
				if(p->Name[j]!='.')
					name[b++]=p->Name[j];
				else
					break;
			st.Format(L"%d  %s",i+1,name);
			dc.DrawText(st,re,DT_LEFT|DT_END_ELLIPSIS);
			re.SetRect(300+10,gy+center,500,gy+y);
			dc.DrawText(p->Data,re,DT_LEFT|DT_END_ELLIPSIS);
			re.SetRect(500+10,gy+center,rect.right,gy+y);
			dc.DrawText(p->Time,re,DT_LEFT|DT_END_ELLIPSIS);
		}
		p=p->link;
		}
		gy=gy+y;
	}
	pdc->BitBlt(0,0,rect.right,rect.bottom,&dc,0,0,SRCCOPY);
	dc.SelectObject(old);
	dc.DeleteDC();
	this->ReleaseDC(pdc);
}

void COList::OnMove(int x, int y)
{
	CDialogEx::OnMove(x, y);
	if(ismove==true)
	{
		CRect rect;
		GetClientRect(&rect);
		m_rect.CopyRect(rect);
		::SetWindowPos(pslider->m_hWnd,HWND_TOP,rect.right-20,25,0,rect.bottom,SWP_NOSIZE);
		::SetWindowPos(pslider->m_hWnd,HWND_TOP,0,0,20,rect.bottom-25,SWP_NOMOVE);

		m_fnum=(rect.bottom-25)/m_Height;
		if(znum-m_fnum<0||znum<m_fnum)
			pslider->SetSize(0,0);
		else
		{
			int b_n=znum-m_fnum;
			pslider->SetSize(b_n,m_Height);
		}
		if((int)znum<m_fnum)
			m_fnum=znum;
		DrawTextList();
	}
}

BOOL COList::InsertText(wchar_t *name,wchar_t *path,wchar_t *time,wchar_t *data)
{
		pnew=new TextLink;
		pnew->num=znum;
		wcscpy_s(pnew->Name,name);
		wcscpy_s(pnew->Path,path);
		wcscpy_s(pnew->Time,time);
		wcscpy_s(pnew->Data,data);
		if(znum==0)
			phead=prear=pnew;
		else
			prear->link=pnew;
		pnew->link=NULL;
		prear=pnew;
		znum+=1;
		DrawTextList();
		CString st;
		CRect rect;
		GetClientRect(&rect);
		SendMessage(WM_MOVE,0,0);
		pslider->DrawH();
	return true;
}

BOOL COList::DeleteAllText()
{
	if(znum==0)
		return true;
	TextLink *p,*pi=phead;
		while(pi!=NULL)
		{
			p=pi->link;
			free(pi);
			pi=p;
		}
		znum=0;
		pslider->SetSize(0,0);
		DrawTextList();
		return true;
}

BOOL COList::DeleteText(DWORD num)
{
	TextLink *pi=phead;
	bool isdel=false;
	while(pi!=NULL)
	{
		if(isdel)
			pi->num=pi->num-1;
		if(pi->num==num&&!isdel)
		{
			pi->num=-1;
			znum-=1;
			isdel=true;
		}
		pi=pi->link;
	}
	CRect rect;
	GetClientRect(&rect);
	m_fnum=(rect.bottom-25)/m_Height;
		if(znum-m_fnum<0||znum<m_fnum)
			pslider->SetSize(0,0);
		else
		{
			int b_n=znum-m_fnum;
			pslider->SetSize(b_n,m_Height);
		}
		if((int)znum<m_fnum)
			m_fnum=znum;
		if((INT)num>znum-m_fnum)
		bnum=znum-m_fnum;
		DrawTextList();
		return isdel;
}

void COList::SetSliderToListEnd()
{
	bnum=znum-m_fnum;
	pslider->MoveToEnd();
	DrawTextList();
}

DWORD COList::GetListNum()
{
	return znum;
}

DWORD COList::SelectText(int sel)
{
	if(sel<0||sel>znum)
		return false;
	m_lb=sel;
	DrawTextList();
	return true;
}

BOOL COList::GetListText(int sel,int list,wchar_t *data)
{
	TextLink *pi=phead;
	while(pi!=NULL)
	{
		if(pi->num==sel)
		{
			switch(list)
			{
			case 0:
				wcscpy_s(data,128,pi->Name);
				break;
			case 1:
				wcscpy_s(data,52,pi->Time);
				break;
			case 2:
				wcscpy_s(data,MAX_PATH,pi->Path);
				break;
			case 3:
				wcscpy_s(data,128,pi->Data);
				break;
			default:
				return false;
			}
		}
		pi=pi->link;
	}
	return true;
}

LRESULT COList::OnNumber(WPARAM wParam,LPARAM lParam)
{
	if(bnum==-1)
		return true;
	bnum=(DWORD)lParam;
	DrawTextList();
	return true;
}

void COList::SetHeight(int Height)
{
	m_Height=Height;
}


void COList::OnMouseMove(UINT nFlags, CPoint point)
{
	m_move=CheckPoint(LM_MOVE,point);
			DrawTextList();
	CDialogEx::OnMouseMove(nFlags, point);
}

void COList::OnLButtonDown(UINT nFlags, CPoint point)
{
	m_lb=CheckPoint(LM_LBDOWN,point);
	DrawTextList();
	CDialogEx::OnLButtonDown(nFlags, point);
}

void COList::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	CheckPoint(LM_LBDB,point);
	CDialogEx::OnLButtonDblClk(nFlags, point);
}


void COList::OnRButtonUp(UINT nFlags, CPoint point)
{
	CRect rect;
	int gy=25;
	int y=m_Height;;
	GetClientRect(&rect);
	rect.top=rect.top+25;
	rect.right=rect.right-20;
	CRect brect;
	for(int i=bnum;i<(bnum+m_fnum);i++)
	{
		brect.SetRect(0,(int)gy,rect.right,(int)gy+y);
	if(brect.PtInRect(point))
	{
		m_lb=i;
		DrawTextList();
		GetParent()->SendMessage(WM_CHECKLIST,LM_RBUP,i);
	}
	gy=gy+y;
	}
	CDialogEx::OnRButtonUp(nFlags, point);
}

DWORD COList::CheckPoint(UINT type,POINT point)
{
	CRect rect;
	int gy=25;
	int y=m_Height;;
	GetClientRect(&rect);
	rect.top=rect.top+25;
	rect.right=rect.right-20;
	CRect brect;
	for(int i=bnum;i<(bnum+m_fnum);i++)
	{
		brect.SetRect(0,(int)gy,rect.right,(int)gy+y);
	if(brect.PtInRect(point))
	{
		GetParent()->SendMessage(WM_CHECKLIST,type,i);
		return i;
	}
	gy=gy+y;
	}
	return -1;
}

void COList::OnClose()
{
	m_font.DeleteObject();
	CDialogEx::OnClose();
}


BOOL COList::PreTranslateMessage(MSG* pMsg)
{
	if(pMsg->message==WM_KEYDOWN)
	{
		if(pMsg->wParam==VK_RETURN)
			return 0;
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}

 LRESULT COList::MouseHd(WPARAM wParam,LPARAM lParam)
 {
	 short sh=(short)lParam;
	 if(sh==-120)
	 {
		bnum=bnum+2;
		if(bnum>znum-m_fnum)
			bnum=znum-m_fnum;
	 }
		 if(sh==120)
		 {
			bnum=bnum-2;
			if(bnum<0)
			{
				bnum=0;
			}
		 }
		 pslider->SelectNum(bnum);
	 DrawTextList();
	 return true;
 }
