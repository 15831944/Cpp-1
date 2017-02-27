// SetMusic.cpp : 实现文件
//

#include "stdafx.h"
#include "华民音乐播放器.h"
#include "SetMusic.h"
#include "afxdialogex.h"


// CSetMusic 对话框

IMPLEMENT_DYNAMIC(CSetMusic, CDialogEx)

CSetMusic::CSetMusic(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSetMusic::IDD, pParent)
{

}

CSetMusic::~CSetMusic()
{
}

void CSetMusic::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_B_CLOSE, m_bclose);
	DDX_Control(pDX, IDC_B_SAVESET, m_bsaveset);
	DDX_Control(pDX, IDC_C_ROOT, m_croot);
	DDX_Control(pDX, IDC_C_CLOSESMALL, m_cclose);
	DDX_Control(pDX, IDC_C_SAVEWINDOWPOINT, m_csave);
	DDX_Control(pDX, IDC_C_OPENPLAYMUSIC, m_copen);
	DDX_Control(pDX, IDC_C_SEEKMUSIC, m_cseek);
}


BEGIN_MESSAGE_MAP(CSetMusic, CDialogEx)
	ON_BN_CLICKED(IDC_B_CLOSE, &CSetMusic::OnBnClickedBClose)
	ON_WM_PAINT()
	ON_WM_NCHITTEST()
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_C_CLOSESMALL, &CSetMusic::OnBnClickedCClosesmall)
	ON_BN_CLICKED(IDC_C_SAVEWINDOWPOINT, &CSetMusic::OnBnClickedCSavewindowpoint)
	ON_BN_CLICKED(IDC_C_OPENPLAYMUSIC, &CSetMusic::OnBnClickedCOpenplaymusic)
	ON_BN_CLICKED(IDC_C_SEEKMUSIC, &CSetMusic::OnBnClickedCSeekmusic)
	ON_BN_CLICKED(IDC_C_ROOT, &CSetMusic::OnBnClickedCRoot)
	ON_BN_CLICKED(IDC_B_SAVESET, &CSetMusic::OnBnClickedBSaveset)
END_MESSAGE_MAP()


// CSetMusic 消息处理程序


void CSetMusic::OnBnClickedBClose()
{
	if(issave)
		if(IDYES==MessageBox(L"你已经修改设置内容，是否保存!",L"提示",MB_YESNO|MB_ICONQUESTION))
			SaveInfo();
	m_font.DeleteObject();
	EndDialog(0);
}


BOOL CSetMusic::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_bclose.SetButtonImage(IDB_P_C1,IDB_P_C2,IDB_P_C3);
	m_bclose.SetTip(L"关闭");
	m_font.CreateFont(14,0,0,0,FW_BLACK,0,0,0,0,0,0,0,0,L"隶书");
	m_bsaveset.SetButtonImage(IDB_P_B1,IDB_P_B2,IDB_P_B1);
	m_bsaveset.SetTip(L"保存当前设置");
	issave=false;
	GetCurrentDirectory(MAX_PATH,Current_Path);
	ReadInfo();
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


BOOL CSetMusic::PreTranslateMessage(MSG* pMsg)
{
	
	return CDialogEx::PreTranslateMessage(pMsg);
}


void CSetMusic::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	CRect rect;
	GetClientRect(&rect);
	dc.FillSolidRect(rect,RGB(235,238,247));
	dc.FillSolidRect(0,0,rect.right,22,RGB(41,167,199));
	dc.SetBkMode(TRANSPARENT);
	dc.SelectObject(m_font);
	dc.SetTextColor(RGB(235,255,235));
	dc.TextOutW(0,2,L"设置");
}


LRESULT CSetMusic::OnNcHitTest(CPoint point)
{
	CRect rect;
	GetClientRect(&rect);
	ClientToScreen(&rect);
	return rect.PtInRect(point)?HTCAPTION:CDialogEx::OnNcHitTest(point);
}


void CSetMusic::OnClose()
{
	CDialogEx::OnClose();
}

void CSetMusic::OnBnClickedCClosesmall()
{
	issave=true;
}


void CSetMusic::OnBnClickedCSavewindowpoint()
{
	issave=true;
}


void CSetMusic::OnBnClickedCOpenplaymusic()
{
	issave=true;
}


void CSetMusic::OnBnClickedCSeekmusic()
{
	issave=true;
}


void CSetMusic::OnBnClickedCRoot()
{
	issave=true;
}


void CSetMusic::OnBnClickedBSaveset()
{
	SaveInfo();
	EndDialog(0);
}

void CSetMusic::SaveInfo()
{
	wchar_t path[MAX_PATH];
	wsprintf(path,L"%s\\SetInfo.ini",Current_Path);
	SetInfo si;
	memset(&si,0x00,sizeof(si));
	if(m_croot.GetCheck())
	{
		HKEY key;
		wchar_t value[MAX_PATH]=L"Software\\Microsoft\\Windows\\CurrentVersion\\Run";
		wchar_t name[128]=L"Hm Play";
		if(RegOpenKeyEx(HKEY_CURRENT_USER,value,0,KEY_ALL_ACCESS,&key)!=ERROR_SUCCESS)
		{
			MessageBox(L"保存开启自动运行失败，无法保存",L"错误",MB_OK|MB_ICONERROR);
			WritePrivateProfileString(L"SETINFO",L"Run",L"0",path);
		}
		else
		{
			wchar_t dir[MAX_PATH];
			GetModuleFileName(NULL,dir,MAX_PATH);
			if(RegSetValueEx(key,name,0,REG_SZ,(BYTE*)dir,wcslen(dir)*2)!=ERROR_SUCCESS)
			{
				MessageBox(L"写入开启自动运行失败，无法保存",L"错误",MB_OK|MB_ICONERROR);
				WritePrivateProfileString(L"SETINFO",L"Run",L"0",path);
			}
			RegCloseKey(key);
			WritePrivateProfileString(L"SETINFO",L"Run",L"1",path);
		}
	}
	else
	{
		HKEY key;
		wchar_t value[MAX_PATH]=L"Software\\Microsoft\\Windows\\CurrentVersion\\Run";
		wchar_t name[128]=L"Hm Play";
		if(RegOpenKeyEx(HKEY_CURRENT_USER,value,0,KEY_ALL_ACCESS,&key)!=ERROR_SUCCESS)
			MessageBox(L"保存开启自动运行失败，无法保存",L"错误",MB_OK|MB_ICONERROR);
		else
		{
			RegDeleteValue(key,name);
			RegCloseKey(key);
			WritePrivateProfileString(L"SETINFO",L"Run",L"0",path);
		}
	}
	if(si.notify=m_cclose.GetCheck())//关闭时缩小
		WritePrivateProfileString(L"SETINFO",L"NOTIF",L"1",path);
	else
		WritePrivateProfileString(L"SETINFO",L"NOTIF",L"0",path);
	if(si.windowspoint=m_csave.GetCheck())//保存当前的窗口位置
		WritePrivateProfileString(L"SETINFO",L"WINDOWPOINT",L"1",path);
	else
		WritePrivateProfileString(L"SETINFO",L"WINDOWPOINT",L"0",path);
	if(si.playup=m_copen.GetCheck())//打开上次播放的音乐
		WritePrivateProfileString(L"SETINFO",L"PLAYUP",L"1",path);
	else
		WritePrivateProfileString(L"SETINFO",L"PLAYUP",L"0",path);
	if(si.seek=m_cseek.GetCheck())//移动指定点播放
		WritePrivateProfileString(L"SETINFO",L"SEEK",L"1",path);
	else
		WritePrivateProfileString(L"SETINFO",L"SEEK",L"0",path);
	this->GetParent()->SendMessage(WM_SETINFO,0,(LPARAM)&si);
}

void CSetMusic::ReadInfo()
{
	wchar_t path[MAX_PATH];
	wsprintf(path,L"%s\\SetInfo.ini",Current_Path);
	wchar_t data[52]={0};
	GetPrivateProfileString(L"SETINFO",L"RUN",0,data,52,path);
	m_croot.SetCheck(_wtoi(data));
	memset(data,0x00,sizeof(data));
	GetPrivateProfileString(L"SETINFO",L"NOTIF",0,data,52,path);
	m_cclose.SetCheck(_wtoi(data));
	memset(data,0x00,sizeof(data));
	GetPrivateProfileString(L"SETINFO",L"WINDOWPOINT",0,data,52,path);
	m_csave.SetCheck(_wtoi(data));
	memset(data,0x00,sizeof(data));
	GetPrivateProfileString(L"SETINFO",L"PLAYUP",0,data,52,path);
	m_copen.SetCheck(_wtoi(data));
	memset(data,0x00,sizeof(data));
	GetPrivateProfileString(L"SETINFO",L"SEEK",0,data,52,path);
	m_cseek.SetCheck(_wtoi(data));

}