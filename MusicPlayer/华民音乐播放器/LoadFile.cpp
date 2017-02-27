// LoadFile.cpp : 实现文件
//

#include "stdafx.h"
#include "华民音乐播放器.h"
#include "LoadFile.h"
#include "afxdialogex.h"


// CLoadFile 对话框
UINT FindFile(LPVOID lParam);
IMPLEMENT_DYNAMIC(CLoadFile, CDialogEx)

CLoadFile::CLoadFile(CWnd* pParent /*=NULL*/)
	: CDialogEx(CLoadFile::IDD, pParent)
{

}

CLoadFile::~CLoadFile()
{
}

void CLoadFile::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_B_CLOSE, m_bclose);
	DDX_Control(pDX, IDC_S_SHOWPATH, m_sshow);
	DDX_Control(pDX, IDC_S1, m_sw1);
	DDX_Control(pDX, IDC_S2, m_sw2);
	DDX_Control(pDX, IDC_S3, m_sw3);
	DDX_Control(pDX, IDC_S_BNUM, m_bnum);
	DDX_Control(pDX, IDC_S_CNUM, m_cnum);
}


BEGIN_MESSAGE_MAP(CLoadFile, CDialogEx)
	ON_WM_PAINT()
	ON_WM_NCHITTEST()
	ON_BN_CLICKED(IDC_B_CLOSE, &CLoadFile::OnBnClickedBClose)
END_MESSAGE_MAP()


// CLoadFile 消息处理程序


BOOL CLoadFile::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_bclose.SetButtonImage(IDB_P_C1,IDB_P_C2,IDB_P_C3);
	m_bclose.SetTip(L"关闭");
	m_sw1.InputText(L"正在努力为你搜索中...");
	m_sw2.InputText(L"已搜索到文件:");
	m_sw3.InputText(L"已添加文件:");
	m_bnum.InputText(L"0");
	m_cnum.InputText(L"0");
	m_font.CreateFont(15,0,0,0,FW_BOLD,0,0,0,ANSI_CHARSET,OUT_DEFAULT_PRECIS,
								CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,
							    DEFAULT_PITCH|FF_SWISS,L"隶书");
		num=0;
		cnum=0;
		pthread=AfxBeginThread(FindFile,this);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CLoadFile::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	CRect rect;
	GetClientRect(&rect);
	dc.FillSolidRect(rect,RGB(153,217,234));
		dc.SetBkMode(TRANSPARENT);
		dc.SelectObject(m_font);
		dc.SetTextColor(RGB(225,245,245));
		dc.TextOutW(0,2,L"华民音乐播放器");
}


LRESULT CLoadFile::OnNcHitTest(CPoint point)
{
	CRect rect;
	GetClientRect(&rect);
	ClientToScreen(&rect);
	return rect.PtInRect(point)?HTCAPTION:CDialogEx::OnNcHitTest(point);
}


void CLoadFile::OnBnClickedBClose()
{
	if(pthread->m_hThread!=NULL)
	TerminateThread(pthread->m_hThread,0);
	EndDialog(0);
}

UINT FindFile(LPVOID lParam)
{
	CLoadFile *p=(CLoadFile*)lParam;
	p->TTfind(p->m_dir);
	p->SendMessage(WM_CLOSE,0,0);
	return 0;
}

void CLoadFile::TTfind(CString dir)
{
	if(dir.IsEmpty())
		return;
	CFileFind m_fd;
	BOOL bol=m_fd.FindFile(dir+"\\*.*");
	while(bol)
	{
		bol=m_fd.FindNextFile();
		if(m_fd.GetFileName()=="."||m_fd.GetFileName()=="..")
			continue;
		if(m_fd.IsDirectory())
			TTfind(m_fd.GetFilePath().AllocSysString());
		else
		{
			m_sshow.InputText(m_fd.GetFilePath().AllocSysString());
			num+=1;
			wchar_t data[12];
			wsprintf(data,L"%d",num);
			m_bnum.InputText(data);
			wchar_t *ExeString=PathFindExtension(m_fd.GetFilePath().AllocSysString());
			if(_wcsicmp(ExeString,L".mp3")==0||_wcsicmp(ExeString,L".wma")==0)
			{
			Add_Info pi;
			memset(&pi,0x00,sizeof(pi));
			wcscpy_s(pi.Name,m_fd.GetFileName().AllocSysString());
			wcscpy_s(pi.Path,m_fd.GetFilePath());
			wchar_t mdata[52];
			char m_dir[MAX_PATH];
			CHWcharToAchar(m_fd.GetFilePath().AllocSysString(),m_dir);
			
			DWORD len=CHGetTimeFromFile(m_dir);
			if(len==0)
				continue;
			M_TIME mi;
			CHNumToTime(len,&mi);
			if(mi.h2<10)
				wsprintf(mdata,L"0%d:0%d",mi.h1,mi.h2);
			else
				wsprintf(mdata,L"0%d:%d",mi.h1,mi.h2);
			wcscpy_s(pi.Time,mdata);
			Music_Info info;
			CHGetMusicInfo(m_dir,&info);
			if(info.tag[0]=='t'||info.tag[0]=='T')
			if(info.tag[1]=='a'||info.tag[1]=='A')
			if(info.tag[2]=='g'||info.tag[2]=='G')
				CHAcharToWchar(info.Album,pi.Data);
			if(GetParent()->SendMessage(WM_ADDSTRING,(WPARAM)&pi,0)==0)
			cnum+=1;
			memset(data,0x00,sizeof(data));
			wsprintf(data,L"%d",cnum);
			m_cnum.InputText(data);
			}
		}
		Sleep(1);
	}
	m_fd.Close();
}

BOOL CLoadFile::PreTranslateMessage(MSG* pMsg)
{
	if(pMsg->message==WM_KEYDOWN)
	{
		if(pMsg->wParam==VK_RETURN)
		{
			return true;
		}
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}
