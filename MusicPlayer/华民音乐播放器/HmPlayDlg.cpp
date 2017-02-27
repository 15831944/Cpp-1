
// HmPlayDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "华民音乐播放器.h"
#include "HmPlayDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CHmPlayDlg 对话框
CHmPlayDlg::CHmPlayDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CHmPlayDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CHmPlayDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_B_CLOSE, m_bclose);
	DDX_Control(pDX, IDC_B_MIN, m_bmin);
	DDX_Control(pDX, IDC_B_LEFT, m_bleft);
	DDX_Control(pDX, IDC_B_PLAY, m_bplay);
	DDX_Control(pDX, IDC_B_RIGHT, m_bright);
	DDX_Control(pDX, IDC_B_CHOSE, m_bchose);
	DDX_Control(pDX, IDC_B_MLIST, m_blist);
	DDX_Control(pDX, IDC_SLIDER, m_bslider);
	DDX_Control(pDX, IDC_S_TB, m_sb);
	DDX_Control(pDX, IDC_S_TE, m_se);
	DDX_Control(pDX, IDC_S_BT, m_sbt);
	DDX_Control(pDX, IDC_B_PLAYTYPE, m_bplaytype);
}

BEGIN_MESSAGE_MAP(CHmPlayDlg, CDialogEx)
	ON_WM_INITMENUPOPUP() 
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_B_CLOSE, &CHmPlayDlg::OnBnClickedBClose)
	ON_BN_CLICKED(IDC_B_MIN, &CHmPlayDlg::OnBnClickedBMin)
	ON_WM_NCHITTEST()
	ON_BN_CLICKED(IDC_B_LEFT, &CHmPlayDlg::OnBnClickedBLeft)
	ON_BN_CLICKED(IDC_B_PLAY, &CHmPlayDlg::OnBnClickedBPlay)
	ON_BN_CLICKED(IDC_B_RIGHT, &CHmPlayDlg::OnBnClickedBRight)
	ON_BN_CLICKED(IDC_B_MLIST, &CHmPlayDlg::OnBnClickedBMlist)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_B_CHOSE, &CHmPlayDlg::OnBnClickedBChose)
	ON_WM_TIMER()
	ON_WM_HSCROLL()
	ON_COMMAND(ID_CHOSE_ABOUT, &CHmPlayDlg::OnChoseAbout)
	ON_MESSAGE(WM_PLAYMUSIC,PlayMusic)
	ON_MESSAGE(WM_SENDVALUE,SetValue)
	ON_MESSAGE(WM_SETINFO,SaveInfo)
	ON_MESSAGE(WM_NOTIFYICON,NotifyIcon)
	ON_WM_MOVE()
	ON_BN_CLICKED(IDC_B_PLAYTYPE, &CHmPlayDlg::OnBnClickedBPlaytype)
	ON_COMMAND(ID_CHOSE_SET, &CHmPlayDlg::OnChoseSet)
	ON_COMMAND(ID_ICON_OPENPLAY, &CHmPlayDlg::OnIconOpenplay)
	ON_COMMAND(ID_ICON_PLAYLIST, &CHmPlayDlg::OnIconPlaylist)
	ON_COMMAND(ID_ICON_SET, &CHmPlayDlg::OnIconSet)
	ON_COMMAND(ID_ICON_ABOUT, &CHmPlayDlg::OnIconAbout)
	ON_COMMAND(ID_ICON_EXIT, &CHmPlayDlg::OnIconExit)
	ON_UPDATE_COMMAND_UI(ID_PLAYTYPE_DANQU, &CHmPlayDlg::OnUpdatePlaytypeDanqu)
	ON_UPDATE_COMMAND_UI(ID_PLAYTYPE_DANQUXH, &CHmPlayDlg::OnUpdatePlaytypeDanquxh)
	ON_UPDATE_COMMAND_UI(ID_PLAYTYPE_LBPLAY, &CHmPlayDlg::OnUpdatePlaytypeLbplay)
	ON_UPDATE_COMMAND_UI(ID_PLAYTYPE_LBXH, &CHmPlayDlg::OnUpdatePlaytypeLbxh)
	ON_UPDATE_COMMAND_UI(ID_PLAYTYPE_WRAND, &CHmPlayDlg::OnUpdatePlaytypeWrand)
	ON_UPDATE_COMMAND_UI(ID_PLAYTYPE_YRAND, &CHmPlayDlg::OnUpdatePlaytypeYrand)
	ON_COMMAND(ID_PLAYTYPE_DANQU, &CHmPlayDlg::OnPlaytypeDanqu)
	ON_COMMAND(ID_PLAYTYPE_DANQUXH, &CHmPlayDlg::OnPlaytypeDanquxh)
	ON_COMMAND(ID_PLAYTYPE_LBPLAY, &CHmPlayDlg::OnPlaytypeLbplay)
	ON_COMMAND(ID_PLAYTYPE_LBXH, &CHmPlayDlg::OnPlaytypeLbxh)
	ON_COMMAND(ID_PLAYTYPE_WRAND, &CHmPlayDlg::OnPlaytypeWrand)
	ON_COMMAND(ID_PLAYTYPE_YRAND, &CHmPlayDlg::OnPlaytypeYrand)
END_MESSAGE_MAP()


// CHmPlayDlg 消息处理程序

BOOL CHmPlayDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标
	m_bclose.SetButtonImage(IDB_P_C1,IDB_P_C2,IDB_P_C3);
	m_bclose.SetTip(L"关闭");
	m_bmin.SetButtonImage(IDB_P_X1,IDB_P_X2,IDB_P_X3);
	m_bmin.SetTip(L"最小化");
	m_bleft.SetButtonImage(IDB_P_L1,IDB_P_L2,IDB_P_L1);
	m_bleft.SetTip(L"上一曲");
	m_bplay.SetButtonImage(IDB_P_P1,IDB_P_P2,IDB_P_P1);
	m_bplay.SetTip(L"播放");	 
	m_bright.SetButtonImage(IDB_P_R1,IDB_P_R2,IDB_P_R1);
	m_bright.SetTip(L"下一曲");
	m_bchose.SetButtonImage(IDB_P_CL1,IDB_P_CL2,IDB_P_CL3);
	m_bchose.SetTip(L"主菜单");
	m_blist.SetButtonImage(IDB_P_LIST1,IDB_P_LIST2,IDB_P_LIST3);
	m_blist.SetTip(L"播放列表");
	m_bplaytype.SetButtonImage(IDB_P_PT1,IDB_P_PT2,IDB_P_PT1);
	m_bplaytype.SetTip(L"播放模式");
	is_play_stop=false;
	m_mlist=new CMlist;
	m_mlist->Create(IDD_D_LIST,GetDesktopWindow());
	m_mlist->ShowWindow(SW_HIDE);
	m_vslider=new CVslider;
	m_vslider->Create(IDD_D_VSLIDER,this);
	m_vslider->ShowWindow(SW_SHOW);
	m_vslider->SetSize(1000);
	m_font.CreateFont(14,0,0,0,FW_BOLD,0,0,0,ANSI_CHARSET,OUT_DEFAULT_PRECIS,
								CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,
							    DEFAULT_PITCH|FF_SWISS,L"隶书");
	m_vslider->MoveWindow(250,35,14,60);
	m_vslider->SelectNumber(1000);
	Init();
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}
//初始化
void CHmPlayDlg::Init(void)
{
	m_sb.InputText(L"00:00");
	m_se.InputText(L"00:00");
	m_sbt.SCreateFont(15,L"Arial");
	wcscpy_s(bdata,L"当前无歌曲播放");
	m_sbt.SetGD(true);
	item=-1;
	for(int i=0;i<Save_Number;i++)
		s_num[i]=-1;
	m_count=0;
	GetCurrentDirectory(MAX_PATH,Current_Path);
	wchar_t dir[MAX_PATH];
	wsprintf(dir,L"%s\\Image\\bk.jpg",Current_Path);
	image.Load(dir);
	for(int i=0;i<6;i++)
		m_mlist->menu_num[i]=0;
	ReadInitInfo();
}

void CHmPlayDlg::OnMove(int x, int y)
{
	CDialogEx::OnMove(x, y);
}

void CHmPlayDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文
		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CPaintDC dc(this);
		dc.SetStretchBltMode(STRETCH_HALFTONE);
		CRect rect;
		GetClientRect(&rect);
		if(!image.IsNull())
		image.Draw(dc.m_hDC,rect);
		CImage l_image;
		dl.LoadImageFromResource(IDB_P_LOGO,L"PNG",&l_image);
		if(!l_image.IsNull())
		{
		l_image.Draw(dc.m_hDC,0,0,24,24);
		l_image.Destroy();
		}
		dl.LoadImageFromResource(IDB_P_VOLUME,L"PNG",&l_image);
		if(!l_image.IsNull())
		{
		l_image.Draw(dc.m_hDC,248,98,16,16);
		l_image.Destroy();
		}
		DrawBText();
		CDialogEx::OnPaint();
	}
}

void CHmPlayDlg::DrawBText()
{
	m_sbt.InputText(bdata);
}

HCURSOR CHmPlayDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CHmPlayDlg::OnBnClickedBClose()
{
	if(sii.notify)
		ShowWindow(SW_HIDE);
	else
	{
	CHCloseMusic(id);
	m_font.DeleteObject();
	SaveInfo();
	Shell_NotifyIcon(NIM_DELETE,&nid);
	EndDialog(0);
	}
}


void CHmPlayDlg::OnBnClickedBMin()
{
	ShowWindow(SW_MINIMIZE);
}

LRESULT CHmPlayDlg::OnNcHitTest(CPoint point)
{
	CRect rect;
	GetClientRect(rect);
	ClientToScreen(rect);
	return rect.PtInRect(point)?HTCAPTION:CDialogEx::OnNcHitTest(point);
}

void CHmPlayDlg::OnBnClickedBPlay()
{
	if(!is_play_stop)
	{
		if(!CHPlayMusic(id))//播放音乐
		{
			m_sbt.InputText(L"播放当前歌曲错误");
			return;
		}
		m_bplay.SetButtonImage(IDB_P_S1,IDB_P_S2,IDB_P_S1);
		m_bplay.SetTip(L"暂停");
		DWORD pos=CHGetMusicPosition(id);
		m_bslider.SetPos(pos);
		DrawTimeText(pos);
		SetTimer(1,1000,NULL);
		is_play_stop=true;
	}
	else
	{
	CHPauseMusic(id);//暂停音乐
	m_bplay.SetButtonImage(IDB_P_P1,IDB_P_P2,IDB_P_P1);
	m_bplay.SetTip(L"播放");
	is_play_stop=false;
		KillTimer(1);
	}
}
//下一曲
void CHmPlayDlg::OnBnClickedBRight()
{
	item=item+1;
	DWORD num=m_mlist->m_olist->GetListNum();
	if(item>(int)num-1)
	{
		item=num-1;
		m_sbt.InputText(L"列表播放完毕");
		return;
	}
	memset(Path,0x00,sizeof(Path));
	m_mlist->m_olist->GetListText(item,2,Path);
	OpenMusic(Path);
		if(!is_play_stop)
	OnBnClickedBPlay();
	m_mlist->m_olist->SelectText(item);
	
}
//上一曲
void CHmPlayDlg::OnBnClickedBLeft()
{
	item=item-1;
	if(item<0)
	{
		item=-1;
		return;
	}
	memset(Path,0x00,sizeof(Path));
	m_mlist->m_olist->GetListText(item,2,Path);
	OpenMusic(Path);
	if(!is_play_stop)
	OnBnClickedBPlay();
	m_mlist->m_olist->SelectText(item);
}

void CHmPlayDlg::OnBnClickedBMlist()
{
	CRect wrect,rect;
	GetWindowRect(&wrect);
	GetClientRect(&rect);
	CRect lrect;
	m_mlist->GetClientRect(&lrect);
	m_mlist->MoveWindow(wrect.left+rect.right,wrect.top,lrect.right,lrect.bottom);
	m_mlist->ShowWindow(SW_SHOW);
}

void CHmPlayDlg::OnClose()
{
	OnBnClickedBClose();
}

void CHmPlayDlg::OpenMusic(wchar_t *path)
{
	CHCloseMusic(id);
	char dir[MAX_PATH];
	CHWcharToAchar(path,dir);
	id=CHOpenMusic(dir);
	if(!id)
	{
		is_play_stop=true;
	OnBnClickedBPlay();
	return;
	}
	CHPlayMusic(id);
	CHSetVolume(id,volume);
	DWORD size=CHGetMusicTime(id);
	m_bslider.SetRange(0,size);
	DrawTimeText(0);
	wchar_t *name,fname[128]={0};
	name=PathFindFileName(path);
	int b=0;
	for(int j=0;j<(int)wcslen(name);j++)
		if(name[j]!='.')
			fname[b++]=name[j];
				else
					break;
	wcscpy_s(bdata,fname);
	DrawBText();
}

void CHmPlayDlg::OnTimer(UINT_PTR nIDEvent)
{
	DWORD pos=CHGetMusicPosition(id);
	DWORD zpos=m_bslider.GetPos();
	DWORD num=m_mlist->m_olist->GetListNum();
	if(zpos==pos)
	{
		switch(m_mlist->Play_Type)
		{
		case 0://单曲
			is_play_stop=true;
			CHSeekMusic(id,0);
			OnBnClickedBPlay();
			break;
		case 1://单曲循环播放
			CHSeekMusic(id,0);
			is_play_stop=false;
			OnBnClickedBPlay();
			break;
		case 2://列表播放
		OnBnClickedBRight();
			break;
		case 3://列表循环
			{
				int sel=item+1;//假想播放下一曲,判断是否超出边界
				if(sel>(int)num-1)
					item=-1;
					OnBnClickedBRight();
			}
			break;
		case 4://乱随机
			{
				srand(unsigned(time(NULL)));
				int sel=rand()%num;
				if(sel==num)
					 sel=rand()%num;
				item=sel;
				memset(Path,0x00,sizeof(Path));
				m_mlist->m_olist->GetListText(item,2,Path);
				m_mlist->m_olist->SelectText(item);
				OpenMusic(Path);
			}
			break;
		case 5://有序随机
			{
				int sel=-1;
				if(m_count>(int)num)
				{
					m_sbt.InputText(L"歌曲已经播放完毕");
					return;
				}
				while(1)
				{
					bool is_have=false;
					srand(unsigned(time(NULL)));
					sel=rand()%num;
					if(sel==num)
					 sel=rand()%num;
					if(m_count==-1)
						break;
					for(int i=0;i<m_count;i++)
					{
						if(s_num[i]==sel)
						{
							is_have=true;
							break;
						}
					}
						if(!is_have)
							break;
				}
				s_num[m_count]=sel;
				item=sel;
				m_mlist->m_olist->SelectText(item);
				memset(Path,0x00,sizeof(Path));
				m_mlist->m_olist->GetListText(sel,2,Path);
				OpenMusic(Path);
				m_count+=1;
			}
			break;
		default:
			return;
		}
	}
	m_bslider.SetPos(pos);
	DrawTimeText(pos);
	CDialogEx::OnTimer(nIDEvent);
}

void CHmPlayDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	CSliderCtrl *slider=(CSliderCtrl*)GetDlgItem(IDC_SLIDER);
	DWORD pos=slider->GetPos();
	CHSeekMusic(id,pos);
	CHPlayMusic(id);
	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CHmPlayDlg::DrawTimeText(DWORD num)
{
	M_TIME tp,ti;
	wchar_t st[52];
	DWORD size=CHGetMusicTime(id);
	CHNumToTime(size,&ti);
	if(ti.h2<10)
	wsprintf(st,L"0%d:0%d",ti.h1,ti.h2);
	else
		wsprintf(st,L"0%d:%d",ti.h1,ti.h2);
	m_se.InputText(st);
	Shell_NotifyIcon(NIM_MODIFY,&nid);
	if(num<=0)
		return;
	wchar_t st1[52];
	CHNumToTime(num,&tp);
		memset(st1,0x00,sizeof(st1));
	if(tp.h2<10)
	wsprintf(st1,L"0%d:0%d",tp.h1,tp.h2);
	else
		wsprintf(st1,L"0%d:%d",tp.h1,tp.h2);
	m_sb.InputText(st1);
	CString tipst;
	tipst.Format(L"华民播放器\n正在播放:%s\n播放进度:%s\n歌曲时间:%s",bdata,st1,st);
	wcscpy_s(nid.szTip,tipst);
}

BOOL CHmPlayDlg::PreTranslateMessage(MSG* pMsg)
{
	if(pMsg->message==WM_KEYDOWN)
	{
		if(pMsg->wParam==VK_RETURN||pMsg->wParam==VK_SPACE)
		{
			OnBnClickedBPlay();
			return true;
		}
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}

void CHmPlayDlg::OnChoseAbout()
{
	CAbout *dlg;
	dlg=new CAbout;
	dlg->Create(IDD_D_ABOUT,this);
	dlg->ShowWindow(SW_SHOW);
}

void CHmPlayDlg::OnBnClickedBChose()
{
	CMenu menu,*pmenu;
	menu.LoadMenuW(IDR_M_CHOSE);
	pmenu=menu.GetSubMenu(0);
	POINT pt;
	GetCursorPos(&pt);
	pmenu->TrackPopupMenu(TPM_RIGHTBUTTON,pt.x,pt.y,this);
}

LRESULT CHmPlayDlg::PlayMusic(WPARAM wParam,LPARAM lParam)
{
	wsprintf(Path,L"%s",lParam);
	OpenMusic(Path);
	item=(int)wParam;
	if(!is_play_stop)
	OnBnClickedBPlay();
	return true;
}

void CHmPlayDlg::ReadInitInfo()
{
	wchar_t dir[MAX_PATH];
	wsprintf(dir,L"%s\\SetInfo.ini",Current_Path);
	wchar_t ws_num[12];
	GetPrivateProfileString(L"Volume",L"Number",0,ws_num,12,dir);
	volume=_wtoi(ws_num);
	m_vslider->SelectNumber(1000-volume);

	wchar_t data[52]={0};
	GetPrivateProfileString(L"SETINFO",L"NOTIF",0,data,52,dir);
	sii.notify=_wtoi(data);
	if(sii.notify)
	{
		nid.cbSize=sizeof(NOTIFYICONDATA);
		nid.hIcon=AfxGetApp()->LoadIconW(IDR_MAINFRAME);
		nid.hWnd=this->m_hWnd;
		wcscpy_s(nid.szTip,L"华民音乐播放器");
		nid.uCallbackMessage=WM_NOTIFYICON;
		nid.uFlags=NIF_ICON|NIF_MESSAGE|NIF_TIP;
		Shell_NotifyIcon(NIM_ADD,&nid);
	}
	memset(data,0x00,sizeof(data));
	GetPrivateProfileString(L"SETINFO",L"WINDOWPOINT",0,data,52,dir);
	sii.windowspoint=_wtoi(data);
	if(sii.windowspoint)
	{
		memset(data,0x00,sizeof(data));
		GetPrivateProfileString(L"POINT",L"POINTX",0,data,52,dir);
		int x=_wtoi(data);
		memset(data,0x00,sizeof(data));
		GetPrivateProfileString(L"POINT",L"POINTY",0,data,52,dir);
		int y=_wtoi(data);
		::SetWindowPos(m_hWnd,HWND_NOTOPMOST,x,y,0,0,SWP_NOSIZE);
	}
	memset(data,0x00,sizeof(data));
	GetPrivateProfileString(L"SETINFO",L"PLAYUP",0,data,52,dir);
	sii.playup=_wtoi(data);
	if(sii.playup)
	{
		wchar_t wpath[MAX_PATH]={0};
		GetPrivateProfileString(L"PLAY_UP_INFO",L"Path",0,wpath,MAX_PATH,dir);
		memset(data,0x00,sizeof(data));
		GetPrivateProfileString(L"PLAY_UP_INFO",L"Item",0,data,52,dir);
		int i=_wtoi(data);
		this->SendMessage(WM_PLAYMUSIC,i,(LPARAM)&wpath);
	}
	memset(data,0x00,sizeof(data));
	GetPrivateProfileString(L"SETINFO",L"SEEK",0,data,52,dir);
	sii.seek=_wtoi(data);
	if(sii.seek)
	{
		memset(data,0x00,sizeof(data));
	GetPrivateProfileString(L"SEEK_INFO",L"Value",0,data,52,dir);
		int dw=_wtoi(data);
		CHSeekMusic(id,dw);
		CHPlayMusic(id);
	}
	memset(data,0x00,sizeof(data));
	GetPrivateProfileString(L"Play_Type",L"Value_Type",0,data,52,dir);
		m_mlist->menu_num[_wtoi(data)]=1;
}

void CHmPlayDlg::SaveInfo()
{
	wchar_t dir[MAX_PATH];
	wsprintf(dir,L"%s\\SetInfo.ini",Current_Path);
	if(sii.windowspoint)//保存当前的窗口位置
	{
		CRect re;
		GetWindowRect(&re);
		CString st;
		st.Format(L"%d",re.left);
		WritePrivateProfileString(L"POINT",L"POINTX",st,dir);
		st.Empty();
		st.Format(L"%d",re.top);
		WritePrivateProfileString(L"POINT",L"POINTY",st,dir);
	}
	if(sii.playup)//打开上次播放的音乐
	{
		WritePrivateProfileString(L"PLAY_UP_INFO",L"Path",Path,dir);
		CString st;
		st.Format(L"%d",item);
		WritePrivateProfileString(L"PLAY_UP_INFO",L"Item",st,dir);
	}
	if(sii.seek)//移动指定点播放
	{
		int dw=m_bslider.GetPos();
		CString st;
		st.Format(L"%d",dw);
		WritePrivateProfileString(L"SEEK_INFO",L"Value",st,dir);
	}
}

LRESULT CHmPlayDlg::SetValue(WPARAM wParam,LPARAM lParam)
{
	volume=1000-(int)lParam;
	CHSetVolume(id,volume);
	wchar_t dir[MAX_PATH];
	wsprintf(dir,L"%s\\SetInfo.ini",Current_Path);
	wchar_t s_num[12];
	wsprintf(s_num,L"%d",volume);
	WritePrivateProfileString(L"Volume",L"Number",s_num,dir);
	return true;
}

void CHmPlayDlg::OnChoseSet()
{
	CSetMusic *m_set;
	m_set=new CSetMusic;
	m_set->Create(IDD_D_SET,this);
	m_set->ShowWindow(SW_SHOW);
}

void CHmPlayDlg::OnBnClickedBPlaytype()
{
	CMenu menu,*pmenu;
	menu.LoadMenuW(IDR_M_PTYPE);
	pmenu=menu.GetSubMenu(0);
	CPoint pt;
	GetCursorPos(&pt);
	pmenu->TrackPopupMenu(TPM_RIGHTBUTTON,pt.x,pt.y,this);
}

LRESULT CHmPlayDlg::SaveInfo(WPARAM wParam,LPARAM lParam)
{
	SetInfo *si;
	memset(&si,0x00,sizeof(si));
	si=(SetInfo*)lParam;
	sii=*si;
	if(sii.notify)
	{
		nid.cbSize=sizeof(NOTIFYICONDATA);
		nid.hIcon=AfxGetApp()->LoadIconW(IDR_MAINFRAME);
		nid.hWnd=this->m_hWnd;
		wcscpy_s(nid.szTip,L"华民音乐播放器");
		nid.uCallbackMessage=WM_NOTIFYICON;
		nid.uFlags=NIF_ICON|NIF_MESSAGE|NIF_TIP;
		Shell_NotifyIcon(NIM_ADD,&nid);
	}
	else
	{
		Shell_NotifyIcon(NIM_DELETE,&nid);
		ShowWindow(SW_SHOW);
	}
	return true;
}

LRESULT CHmPlayDlg::NotifyIcon(WPARAM wParam,LPARAM lParam)
{
	switch(lParam)
	{
	case WM_LBUTTONDBLCLK:
			ShowWindow(SW_SHOW);break;
	case WM_RBUTTONDOWN:
		{
			CMenu menu,*pmenu;
	menu.LoadMenuW(IDR_M_ICON);
	pmenu=menu.GetSubMenu(0);
	CPoint pt;
	GetCursorPos(&pt);
	pmenu->TrackPopupMenu(TPM_RIGHTBUTTON,pt.x,pt.y,this);
	pmenu->DestroyMenu();
		}
		break;
	}
	return 0;
}

void CHmPlayDlg::OnIconOpenplay()
{
	ShowWindow(SW_SHOW);
}

void CHmPlayDlg::OnIconPlaylist()
{
	OnBnClickedBMlist();
}

void CHmPlayDlg::OnIconSet()
{
	CSetMusic dlg;
	dlg.DoModal();
}

void CHmPlayDlg::OnIconAbout()
{
	CAbout dlg;
	dlg.DoModal();
}

void CHmPlayDlg::OnIconExit()
{
	CHCloseMusic(id);
	m_font.DeleteObject();
	Shell_NotifyIcon(NIM_DELETE,&nid);
	SaveInfo();
	EndDialog(0);
}

void CHmPlayDlg::OnUpdatePlaytypeDanqu(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_mlist->menu_num[0]);
}

void CHmPlayDlg::OnUpdatePlaytypeDanquxh(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_mlist->menu_num[1]);
}

void CHmPlayDlg::OnUpdatePlaytypeLbplay(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_mlist->menu_num[2]);
}

void CHmPlayDlg::OnUpdatePlaytypeLbxh(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_mlist->menu_num[3]);
}

void CHmPlayDlg::OnUpdatePlaytypeWrand(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_mlist->menu_num[4]);
}

void CHmPlayDlg::OnUpdatePlaytypeYrand(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_mlist->menu_num[5]);
}

void CHmPlayDlg::OnInitMenuPopup(CMenu *pPopupMenu, UINT nIndex,BOOL bSysMenu)
{ 
    ASSERT(pPopupMenu != NULL); 
    CCmdUI state; 
    state.m_pMenu = pPopupMenu; 
    ASSERT(state.m_pOther == NULL); 
    ASSERT(state.m_pParentMenu == NULL);
    HMENU hParentMenu; 
    if (AfxGetThreadState()->m_hTrackingMenu == pPopupMenu->m_hMenu) 
      state.m_pParentMenu = pPopupMenu;   // Parent == child for tracking popup. 
    else if ((hParentMenu = ::GetMenu(m_hWnd)) != NULL) 
    { 
      CWnd* pParent = this; 
      if (pParent != NULL && 
        (hParentMenu = ::GetMenu(pParent->m_hWnd)) != NULL) 
      { 
        int nIndexMax = ::GetMenuItemCount(hParentMenu); 
        for (int nIndex = 0; nIndex < nIndexMax; nIndex++) 
        { 
          if (::GetSubMenu(hParentMenu, nIndex) == pPopupMenu->m_hMenu) 
          { 
            state.m_pParentMenu = CMenu::FromHandle(hParentMenu); 
            break; 
          } 
        } 
      } 
    }

    state.m_nIndexMax = pPopupMenu->GetMenuItemCount(); 
    for (state.m_nIndex = 0; state.m_nIndex < state.m_nIndexMax; 
      state.m_nIndex++) 
    { 
      state.m_nID = pPopupMenu->GetMenuItemID(state.m_nIndex); 
      if (state.m_nID == 0) 
        continue; // Menu separator or invalid cmd - ignore it.

      ASSERT(state.m_pOther == NULL); 
      ASSERT(state.m_pMenu != NULL); 
      if (state.m_nID == (UINT)-1) 
      { 
        // Possibly a popup menu, route to first item of that popup. 
        state.m_pSubMenu = pPopupMenu->GetSubMenu(state.m_nIndex); 
        if (state.m_pSubMenu == NULL || 
          (state.m_nID = state.m_pSubMenu->GetMenuItemID(0)) == 0 || 
          state.m_nID == (UINT)-1) 
        { 
          continue;     // First item of popup can't be routed to. 
        } 
        state.DoUpdate(this, TRUE);   // Popups are never auto disabled. 
      } 
      else 
      { 
        // Normal menu item. 
        // Auto enable/disable if frame window has m_bAutoMenuEnable 
        // set and command is _not_ a system command. 
        state.m_pSubMenu = NULL; 
        state.DoUpdate(this, FALSE); 
      }

      // Adjust for menu deletions and additions. 
      UINT nCount = pPopupMenu->GetMenuItemCount(); 
      if (nCount < state.m_nIndexMax) 
      { 
        state.m_nIndex -= (state.m_nIndexMax - nCount); 
        while (state.m_nIndex < nCount && 
          pPopupMenu->GetMenuItemID(state.m_nIndex) == state.m_nID) 
        { 
          state.m_nIndex++; 
        } 
      } 
      state.m_nIndexMax = nCount; 
    } 
}  

void CHmPlayDlg::OnPlaytypeDanqu()
{
	m_mlist->menu_num[0]=1;
	m_mlist->menu_num[1]=0;
	m_mlist->menu_num[2]=0;
	m_mlist->menu_num[3]=0;
	m_mlist->menu_num[4]=0;
	m_mlist->menu_num[5]=0;
	m_mlist->OnPlaytypeDanqu();
}


void CHmPlayDlg::OnPlaytypeDanquxh()
{
	m_mlist->menu_num[0]=0;
	m_mlist->menu_num[1]=1;
	m_mlist->menu_num[2]=0;
	m_mlist->menu_num[3]=0;
	m_mlist->menu_num[4]=0;
	m_mlist->menu_num[5]=0;
	m_mlist->OnPlaytypeDanquxh();
}

void CHmPlayDlg::OnPlaytypeLbplay()
{
	m_mlist->menu_num[0]=0;
	m_mlist->menu_num[1]=0;
	m_mlist->menu_num[2]=1;
	m_mlist->menu_num[3]=0;
	m_mlist->menu_num[4]=0;
	m_mlist->menu_num[5]=0;
	m_mlist->OnPlaytypeLbplay();
}

void CHmPlayDlg::OnPlaytypeLbxh()
{
	m_mlist->menu_num[0]=0;
	m_mlist->menu_num[1]=0;
	m_mlist->menu_num[2]=0;
	m_mlist->menu_num[3]=1;
	m_mlist->menu_num[4]=0;
	m_mlist->menu_num[5]=0;
	m_mlist->OnPlaytypeLbxh();
}

void CHmPlayDlg::OnPlaytypeWrand()
{
	m_mlist->menu_num[0]=0;
	m_mlist->menu_num[1]=0;
	m_mlist->menu_num[2]=0;
	m_mlist->menu_num[3]=0;
	m_mlist->menu_num[4]=1;
	m_mlist->menu_num[5]=0;
	m_mlist->OnPlaytypeWrand();
}


void CHmPlayDlg::OnPlaytypeYrand()
{
	m_mlist->menu_num[0]=0;
	m_mlist->menu_num[1]=0;
	m_mlist->menu_num[2]=0;
	m_mlist->menu_num[3]=0;
	m_mlist->menu_num[4]=0;
	m_mlist->menu_num[5]=1;
	m_mlist->OnPlaytypeYrand();
}
