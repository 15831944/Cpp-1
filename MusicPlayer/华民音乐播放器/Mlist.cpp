// Mlist.cpp : 实现文件
//

#include "stdafx.h"
#include "华民音乐播放器.h"
#include "Mlist.h"
#include "afxdialogex.h"


// CMlist 对话框

IMPLEMENT_DYNAMIC(CMlist, CDialogEx)

CMlist::CMlist(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMlist::IDD, pParent)
{

}

CMlist::~CMlist()
{
}

void CMlist::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_B_CLOSE, m_bclose);
	DDX_Control(pDX, IDC_B_CHOSETYPE, m_bchose);
	DDX_Control(pDX, IDC_B_PTYLE, m_btype);
}


BEGIN_MESSAGE_MAP(CMlist, CDialogEx)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_B_CLOSE, &CMlist::OnBnClickedBClose)
	ON_WM_NCHITTEST()
	ON_WM_MOVE()
	ON_MESSAGE(WM_CHECKLIST,CheckList)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_B_MOVE, &CMlist::OnBnClickedBMove)
	ON_BN_CLICKED(IDC_B_CHOSETYPE, &CMlist::OnBnClickedBChosetype)
	ON_COMMAND(ID_ADD_ADDFILE, &CMlist::OnAddAddfile)
	ON_COMMAND(ID_ADD_ADDDIRECTORY, &CMlist::OnAddAdddirectory)
	ON_MESSAGE(WM_ADDSTRING,OnAddString)
	ON_COMMAND(ID_ML_PLAY, &CMlist::OnMlPlay)
	ON_COMMAND(ID_MLIST_OPENFILE, &CMlist::OnMlistOpenfile)
	ON_COMMAND(ID_MLIST_LOADINFO, &CMlist::OnMlistLoadinfo)
	ON_COMMAND(ID_MLIST_DEL, &CMlist::OnMlistDel)
	ON_COMMAND(ID_MLIST_DELALL, &CMlist::OnMlistDelall)
	ON_COMMAND(ID_MLIST_MOVELIST, &CMlist::OnMlistMovelist)
	ON_COMMAND(ID_MLIST_DELALLLIST, &CMlist::OnMlistDelalllist)
	ON_WM_MOUSEWHEEL()
	ON_COMMAND(ID_PLAYTYPE_DANQU, &CMlist::OnPlaytypeDanqu)
	ON_COMMAND(ID_PLAYTYPE_DANQUXH, &CMlist::OnPlaytypeDanquxh)
	ON_COMMAND(ID_PLAYTYPE_LBPLAY, &CMlist::OnPlaytypeLbplay)
	ON_COMMAND(ID_PLAYTYPE_LBXH, &CMlist::OnPlaytypeLbxh)
	ON_COMMAND(ID_PLAYTYPE_WRAND, &CMlist::OnPlaytypeWrand)
	ON_COMMAND(ID_PLAYTYPE_YRAND, &CMlist::OnPlaytypeYrand)
	ON_BN_CLICKED(IDC_B_FINDSEL, &CMlist::OnBnClickedBFindsel)
	ON_BN_CLICKED(IDC_B_PTYLE, &CMlist::OnBnClickedBPtyle)
	ON_UPDATE_COMMAND_UI(ID_PLAYTYPE_DANQU, &CMlist::OnUpdatePlaytypeDanqu)
	ON_UPDATE_COMMAND_UI(ID_PLAYTYPE_DANQUXH, &CMlist::OnUpdatePlaytypeDanquxh)
	ON_UPDATE_COMMAND_UI(ID_PLAYTYPE_LBPLAY, &CMlist::OnUpdatePlaytypeLbplay)
	ON_UPDATE_COMMAND_UI(ID_PLAYTYPE_LBXH, &CMlist::OnUpdatePlaytypeLbxh)
	ON_UPDATE_COMMAND_UI(ID_PLAYTYPE_WRAND, &CMlist::OnUpdatePlaytypeWrand)
	ON_UPDATE_COMMAND_UI(ID_PLAYTYPE_YRAND, &CMlist::OnUpdatePlaytypeYrand)
	ON_WM_INITMENUPOPUP()
END_MESSAGE_MAP()


// CMlist 消息处理程序


BOOL CMlist::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	GetCurrentDirectory(MAX_PATH,Current_Path);
	ismove=false;
	Play_Type=item=-1;
	m_olist=new COList;
	m_olist->Create(IDD_D_OLIST,this);
	m_olist->ShowWindow(SW_SHOW);
	ismove=true;
	m_olist->SetHeight(22);
	m_plist=new CPlayList;
	m_plist->Create(IDD_D_PLAYLIST,this);
	m_plist->ShowWindow(SW_HIDE);
	m_font.CreateFont(15,0,0,0,FW_BOLD,0,0,0,ANSI_CHARSET,OUT_DEFAULT_PRECIS,
								CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,
							    DEFAULT_PITCH|FF_SWISS,L"隶书");
	m_bclose.SetButtonImage(IDB_P_C1,IDB_P_C2,IDB_P_C3);
	m_bclose.SetTip(L"关闭");
	m_bchose.SetButtonImage(IDB_P_CH1,IDB_P_CH2,IDB_P_CH1);
	m_bchose.SetTip(L"添加");
	ReadMusicListFromFile(L"Play_List.mat");
	ReadIni();
	m_bclose.isdc=false;
	m_bchose.isdc=false;
	wchar_t dir[MAX_PATH];
	wsprintf(dir,L"%s\\Image\\bk.jpg",Current_Path);
	image.Load(dir);
	m_btype.SetButtonImage(IDB_P_PT1,IDB_P_PT2,IDB_P_PT1);
	m_btype.SetTip(L"播放模式");
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CMlist::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	dc.SetStretchBltMode(STRETCH_HALFTONE);
		CRect rect;
		GetClientRect(&rect);
		if(!image.IsNull())
		image.Draw(dc.m_hDC,rect);
		dc.SetBkMode(TRANSPARENT);
		dc.SelectObject(m_font);
		dc.SetTextColor(RGB(235,255,235));
		dc.TextOutW(0,2,L"华民音乐播放器");
}


void CMlist::OnBnClickedBClose()
{
	ShowWindow(SW_HIDE);
}

LRESULT CMlist::OnNcHitTest(CPoint point)
{
	CRect rect;
	GetClientRect(&rect);
	ClientToScreen(rect);
	return rect.PtInRect(point)?HTCAPTION:CDialogEx::OnNcHitTest(point);
}


void CMlist::OnMove(int x, int y)
{
	CDialogEx::OnMove(x, y);
	if(ismove==true)
	{
		CRect rect;
		GetClientRect(&rect);
		m_olist->MoveWindow(1,22,rect.right-26,rect.bottom-23);
		m_olist->SendMessage(WM_MOVE,-1,-1);
	}
}

LRESULT CMlist::CheckList(WPARAM wParam,LPARAM lParam)
{
	switch(wParam)
	{
	case LM_LBDB:
		{
		wchar_t data[MAX_PATH];
		m_olist->GetListText(lParam,2,data);
		item=(int)lParam;
		GetParent()->SendMessage(WM_PLAYMUSIC,(WPARAM)item,(LPARAM)&data);
		}
		break;
	case LM_RBUP:
		{
			item=(int)lParam;
			CMenu menu,*pmenu;
			menu.LoadMenuW(IDR_M_MLIST);
			pmenu=menu.GetSubMenu(0);
			CPoint pt;
			GetCursorPos(&pt);
			pmenu->TrackPopupMenu(TPM_RIGHTBUTTON,pt.x,pt.y,this);
		}
		break;
	}
	return true;
}

void CMlist::OnClose()
{
	m_olist->DeleteAllText();
	m_font.DeleteObject();
	CDialogEx::OnClose();
}

void CMlist::OnBnClickedBChosetype()
{
	CMenu menu,*pmenu;
	menu.LoadMenuW(IDR_M_ADD);
	pmenu=menu.GetSubMenu(0);
	CPoint pt;
	GetCursorPos(&pt);
	pmenu->TrackPopupMenu(TPM_RIGHTBUTTON,pt.x,pt.y,this);
}


void CMlist::OnAddAddfile()
{
	wchar_t str[]=L"*.mp3,*.wma|*.mp3;*.wma|"
				  L"All File(*.*)|*.*||";
	CFileDialog dlg(true,0,0,OFN_ALLOWMULTISELECT,str,0,0);
	wchar_t *p=new wchar_t[2048];
	dlg.m_ofn.nMaxFile=2048;
	dlg.m_ofn.lpstrFile=p;
	dlg.m_ofn.lpstrFile[0]=NULL;
	POSITION ps;
	if(dlg.DoModal()==IDOK)
	{
		ps=dlg.GetStartPosition();
		while(ps!=NULL)
		{
		CString path;
		path=dlg.GetNextPathName(ps);
		wchar_t *name=PathFindFileName(path);
		char dir[MAX_PATH];
		CHWcharToAchar(path.AllocSysString(),dir);
		DWORD dw=CHGetTimeFromFile(dir);
		M_TIME mt;
		CHNumToTime(dw,&mt);
		wchar_t data[25];
		if(mt.h2<10)
		wsprintf(data,L"0%d:0%d",mt.h1,mt.h2);
		else
			wsprintf(data,L"0%d:%d",mt.h1,mt.h2);
			Music_Info info;
			memset(&info,0x00,sizeof(info));
			CHGetMusicInfo(dir,&info);
			wchar_t adata[128];
			memset(adata,0x00,sizeof(adata));
			if(info.tag[0]=='t'||info.tag[0]=='T')
			if(info.tag[1]=='a'||info.tag[1]=='A')
			if(info.tag[2]=='g'||info.tag[2]=='G')
			CHAcharToWchar(info.Album,adata);
			if(!CheckListReturn(name,path.AllocSysString()))
				continue;
		m_olist->InsertText(name,path.AllocSysString(),data,adata);
		SaveMusciToFile(name,path.AllocSysString(),data,adata);
		}
	}
}


void CMlist::OnAddAdddirectory()
{
	BROWSEINFO bin;
	bin.hwndOwner=NULL;
	bin.lpszTitle=L"选择歌曲所在的文件夹";
	bin.pidlRoot=NULL;
	bin.ulFlags=BIF_EDITBOX;
	bin.lpfn=NULL;
	bin.pszDisplayName=NULL;
	LPITEMIDLIST lpid=SHBrowseForFolder(&bin);
	if(lpid)
	{
		wchar_t path[MAX_PATH];
		SHGetPathFromIDList(lpid,path);
		CLoadFile *dlg=new CLoadFile;
	wcscpy_s(dlg->m_dir,path);
	dlg->Create(IDD_D_LOADFILE,this);
	dlg->ShowWindow(SW_SHOW);
	}
	LPMALLOC lp;
	if(FAILED(SHGetMalloc(&lp)))
		return;
	lp->Free(lpid);
	lp->Release();
}

LRESULT CMlist::OnAddString(WPARAM wParam,LPARAM lParam)
{
	Add_Info *pi=(Add_Info*)wParam;
	if(!CheckListReturn(pi->Name,pi->Path))
		return -1;
	m_olist->InsertText(pi->Name,pi->Path,pi->Time,pi->Data);
	m_olist->SetSliderToListEnd();
	SaveMusciToFile(pi->Name,pi->Path,pi->Time,pi->Data);
	return 0;
}

BOOL CMlist::CheckListReturn(wchar_t *wn,wchar_t *wp)
{
	DWORD num=m_olist->GetListNum();
	for(int i=0;i<(int)num;i++)
	{
		wchar_t name[128],Path[MAX_PATH];
		m_olist->GetListText(i,0,name);
		m_olist->GetListText(i,2,Path);
		if(wcscmp(name,wn)==0&&wcscmp(Path,wp)==0)
			return false;
	}
	return true;
}

void CMlist::OnMlPlay()
{
	wchar_t data[MAX_PATH];
		m_olist->GetListText(item,2,data);
		GetParent()->SendMessage(WM_PLAYMUSIC,(WPARAM)item,(LPARAM)&data);
}


void CMlist::OnMlistOpenfile()
{
	wchar_t data[MAX_PATH];
	m_olist->GetListText(item,2,data);
	char dir[MAX_PATH];
	CHWcharToAchar(data,dir);
	if(!CHOpenFileSelect(dir))
	MessageBox(L"无法打开文件所在位置",L"错误",MB_ICONERROR);
}

void CMlist::OnMlistMovelist()
{
	if(IDOK==MessageBox(L"是否将当前选择的歌曲移出列表",L"提示",MB_OKCANCEL|MB_ICONQUESTION))
	m_olist->DeleteText(item);
	ChangeFile(L"Play_List.mat");
}


void CMlist::OnMlistDelalllist()
{
	if(IDOK==MessageBox(L"是否清空所有列表中的歌曲",L"提示",MB_OKCANCEL|MB_ICONQUESTION))
		m_olist->DeleteAllText();
	ChangeFile(L"Play_List.mat");
}

BOOL CMlist::SaveMusciToFile(wchar_t *name,wchar_t *path,wchar_t *wtime,wchar_t *album)
{
	CFile m_file;
	wchar_t Path[MAX_PATH];
	wsprintf(Path,L"%s\\Data\\Play_List.mat",Current_Path);
	if(!CheckFile(Path))
	m_file.Open(Path,CFile::modeCreate|CFile::typeBinary|CFile::modeWrite);
	else
	m_file.Open(Path,CFile::modeWrite|CFile::typeBinary);
	m_file.SeekToEnd();
	Save_Info si;
	memset(&si,0x00,sizeof(si));
	CHWcharToAchar(name,si.Name);
	CHWcharToAchar(path,si.Path);
	CHWcharToAchar(wtime,si.Time);
	CHWcharToAchar(album,si.Album);
	m_file.Write((char*)&si,sizeof(Save_Info));
	m_file.Close();
	return true;
}

BOOL CMlist::CheckFile(wchar_t *path)
{
	WIN32_FIND_DATA fd;
	HANDLE handle=FindFirstFile(path,&fd);
	if(handle==INVALID_HANDLE_VALUE)
		return false;
	FindClose(handle);
	return true;
}

void CMlist::ReadMusicListFromFile(wchar_t *fname)
{
	CFile m_file;
	wchar_t Path[MAX_PATH];
	wsprintf(Path,L"%s\\Data\\%s",Current_Path,fname);
	if(!CheckFile(Path))
	{
		MessageBox(L"无法读取列表数据，可能文件已经损坏",Path,MB_OK|MB_ICONERROR);
		return;
	}
	else
	m_file.Open(Path,CFile::modeRead|CFile::typeBinary);
	Save_Info si;
	memset(&si,0x00,sizeof(si));
	while(m_file.Read((char*)&si,sizeof(si)))
	{
		wchar_t name[128]={0},dir[MAX_PATH]={0},Time[52]={0},data[128]={0};
		CHAcharToWchar(si.Name,name);
		CHAcharToWchar(si.Path,dir);
		CHAcharToWchar(si.Time,Time);
		CHAcharToWchar(si.Album,data);
		m_olist->InsertText(name,dir,Time,data);
		memset(&si,0x00,sizeof(si));
	}
	m_file.Close();
}

BOOL CMlist::ChangeFile(wchar_t *name)
{
	DWORD num=m_olist->GetListNum();
	wchar_t Del_File[MAX_PATH];
	wsprintf(Del_File,L"%s\\Data\\%s",Current_Path,name);
	if(!DeleteFile(Del_File))
		return false;
	for(int i=0;i<(int)num;i++)
	{
		wchar_t path[MAX_PATH]={0},name[128]={0},wtime[52]={0},data[128]={0};
		m_olist->GetListText(i,0,name);
		m_olist->GetListText(i,2,path);
		m_olist->GetListText(i,1,wtime);
		m_olist->GetListText(i,3,data);
	SaveMusciToFile(name,path,wtime,data);
	}
	return true;
}

BOOL CMlist::PreTranslateMessage(MSG* pMsg)
{
	if(pMsg->message==WM_KEYDOWN)
	{
		if(pMsg->wParam==VK_RETURN)
			return 0;
		if(pMsg->wParam==VK_ESCAPE)
			return 0;
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}

BOOL CMlist::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	m_olist->SendMessage(WM_MOUSEHD,(WPARAM)nFlags,(LPARAM)zDelta);
	
	return CDialogEx::OnMouseWheel(nFlags, zDelta, pt);
}

void CMlist::OnMlistDel()
{
	if(IDOK==MessageBox(L"是否将当前选择的歌曲移出列表并删除文件",L"提示",MB_OKCANCEL|MB_ICONQUESTION))
	{
		wchar_t path[MAX_PATH];
		m_olist->GetListText(item,2,path);
		if(!DeleteFile(path))
			MessageBox(L"无法删除文件，可能文件已经损坏或路径已经改变",L"提示",MB_OK|MB_ICONWARNING);
		else
	m_olist->DeleteText(item);
			ChangeFile(L"Play_List.mat");
	}
}


void CMlist::OnMlistDelall()
{
	if(IDOK==MessageBox(L"是否将当前列表所有的歌曲移出列表并删除文件",L"提示",MB_OKCANCEL|MB_ICONQUESTION))
	{
		int num=m_olist->GetListNum();
		for(int i=num-1;i>=0;i--)
		{
			wchar_t dir[MAX_PATH]={0};
		m_olist->GetListText(i,2,dir);
		if(!DeleteFile(dir))
			MessageBox(L"无法删除文件，可能文件已经损坏或路径已经改变",L"提示",MB_OK|MB_ICONWARNING);
		else
	m_olist->DeleteText(i);
		}
		ChangeFile(L"Play_List.mat");
	}
}

void CMlist::OnMlistLoadinfo()
{
	CMinfo dlg;
	m_olist->GetListText(item,2,dlg.m_Path);
	dlg.DoModal();
}

void CMlist::OnBnClickedBMove()
{
	CRect drect,rect,wrect;
	GetWindowRect(&wrect);
	GetClientRect(&rect);
	m_plist->GetClientRect(&drect);
	int x=0;
	x=rect.left+wrect.right;
	if(x+drect.right>wrect.right)
		x=wrect.left+rect.right;
	m_plist->MoveWindow(x,wrect.top,drect.right,drect.bottom);
	m_plist->ShowWindow(SW_SHOW);
}


void CMlist::OnPlaytypeDanqu()
{
	Play_Type=0;
	menu_num[0]=1;
	menu_num[1]=0;
	menu_num[2]=0;
	menu_num[3]=0;
	menu_num[4]=0;
	menu_num[5]=0;
	WriteIni();
}


void CMlist::OnPlaytypeDanquxh()
{
	Play_Type=1;
	menu_num[0]=0;
	menu_num[1]=1;
	menu_num[2]=0;
	menu_num[3]=0;
	menu_num[4]=0;
	menu_num[5]=0;
	WriteIni();
}


void CMlist::OnPlaytypeLbplay()
{
	Play_Type=2;
	menu_num[0]=0;
	menu_num[1]=0;
	menu_num[2]=1;
	menu_num[3]=0;
	menu_num[4]=0;
	menu_num[5]=0;
	WriteIni();
}


void CMlist::OnPlaytypeLbxh()
{
	Play_Type=3;
	menu_num[0]=0;
	menu_num[1]=0;
	menu_num[2]=0;
	menu_num[3]=1;
	menu_num[4]=0;
	menu_num[5]=0;
	WriteIni();
}


void CMlist::OnPlaytypeWrand()
{
	Play_Type=4;
	menu_num[0]=0;
	menu_num[1]=0;
	menu_num[2]=0;
	menu_num[3]=0;
	menu_num[4]=1;
	menu_num[5]=0;
	WriteIni();
}


void CMlist::OnPlaytypeYrand()
{
	Play_Type=5;
	menu_num[0]=0;
	menu_num[1]=0;
	menu_num[2]=0;
	menu_num[3]=0;
	menu_num[4]=0;
	menu_num[5]=1;
	WriteIni();
}

void CMlist::WriteIni()
{
	wchar_t dir[MAX_PATH];
	wsprintf(dir,L"%s\\SetInfo.ini",Current_Path);
	wchar_t data[12];
	wsprintf(data,L"%d",Play_Type);
	WritePrivateProfileString(L"Play_Type",L"Value_Type",data,dir);
}

void CMlist::ReadIni()
{
	wchar_t dir[MAX_PATH];
	wsprintf(dir,L"%s\\SetInfo.ini",Current_Path);
	wchar_t ws_num[12];
	GetPrivateProfileString(L"Play_Type",L"Value_Type",0,ws_num,12,dir);
	Play_Type=_wtoi(ws_num);
}

void CMlist::OnUpdatePlaytypeDanqu(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(menu_num[0]);
}

void CMlist::OnUpdatePlaytypeDanquxh(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(menu_num[1]);
}

void CMlist::OnUpdatePlaytypeLbplay(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(menu_num[2]);
}

void CMlist::OnUpdatePlaytypeLbxh(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(menu_num[3]);
}

void CMlist::OnUpdatePlaytypeWrand(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(menu_num[4]);
}

void CMlist::OnUpdatePlaytypeYrand(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(menu_num[5]);
}

void CMlist::OnInitMenuPopup(CMenu* pPopupMenu, UINT nIndex, BOOL bSysMenu)
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

void CMlist::OnBnClickedBPtyle()
{
	CMenu menu,*pmenu;
	menu.LoadMenuW(IDR_M_PTYPE);
	pmenu=menu.GetSubMenu(0);
	CPoint pt;
	GetCursorPos(&pt);
	pmenu->TrackPopupMenu(TPM_RIGHTBUTTON,pt.x,pt.y,this);
}

void CMlist::OnBnClickedBFindsel()
{
	
}