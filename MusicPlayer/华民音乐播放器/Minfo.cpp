// Minfo.cpp : 实现文件
//

#include "stdafx.h"
#include "华民音乐播放器.h"
#include "Minfo.h"
#include "afxdialogex.h"


// CMinfo 对话框

IMPLEMENT_DYNAMIC(CMinfo, CDialogEx)

CMinfo::CMinfo(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMinfo::IDD, pParent)
{

}

CMinfo::~CMinfo()
{
}

void CMinfo::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_B_CLOSE, m_bclose);
	DDX_Control(pDX, IDC_ST1, m_st1);
	DDX_Control(pDX, IDC_ST2, m_st2);
	DDX_Control(pDX, IDC_ST3, m_st3);
	DDX_Control(pDX, IDC_ST6, m_st6);
	DDX_Control(pDX, IDC_ST4, m_st4);
	DDX_Control(pDX, IDC_ST5, m_st5);
	DDX_Control(pDX, IDC_ST7, m_st7);
	DDX_Control(pDX, IDC_ST8, m_st8);
	DDX_Control(pDX, IDC_ST9, m_st9);
	DDX_Control(pDX, IDC_S_NAME, m_sname);
	DDX_Control(pDX, IDC_S_PATH, m_spath);
	DDX_Control(pDX, IDC_S_FILESIZE, m_sfilesize);
	DDX_Control(pDX, IDC_S_FIELTYPE, m_sfiletype);
	DDX_Control(pDX, IDC_S_MUSICNAME, m_smusicname);
	DDX_Control(pDX, IDC_S_SONG, m_ssong);
	DDX_Control(pDX, IDC_S_YEAR, m_syear);
	DDX_Control(pDX, IDC_S_BT, m_sbt);
	DDX_Control(pDX, IDC_S_BZ, m_sbz);
	DDX_Control(pDX, IDC_BU_OK, m_baclose);
	DDX_Control(pDX, IDC_B_OPENFILESELECT, m_bopen);
}


BEGIN_MESSAGE_MAP(CMinfo, CDialogEx)
	ON_WM_PAINT()
	ON_WM_NCHITTEST()
	ON_BN_CLICKED(IDC_B_CLOSE, &CMinfo::OnBnClickedBClose)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BU_OK, &CMinfo::OnBnClickedBuOk)
	ON_BN_CLICKED(IDC_B_OPENFILESELECT, &CMinfo::OnBnClickedBOpenfileselect)
END_MESSAGE_MAP()


// CMinfo 消息处理程序


BOOL CMinfo::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_bclose.SetButtonImage(IDB_P_C1,IDB_P_C2,IDB_P_C3);
	m_bclose.SetTip(L"关闭");
		m_font.CreateFont(15,0,0,0,FW_BOLD,0,0,0,ANSI_CHARSET,OUT_DEFAULT_PRECIS,
								CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,
							    DEFAULT_PITCH|FF_SWISS,L"隶书");
		
		m_st1.InputText(L"文件名称:");
		m_st1.SetColor(RGB(0,0,0));
		m_st2.InputText(L"文件路径:");
		m_st2.SetColor(RGB(0,0,0));
		m_st3.InputText(L"文件大小:");
		m_st3.SetColor(RGB(0,0,0));
		m_st6.InputText(L"文件类型:");
		m_st6.SetColor(RGB(0,0,0));
		m_st5.InputText(L"歌手:");
		m_st5.SetColor(RGB(0,0,0));
		m_st4.InputText(L"音乐名称:");
		m_st4.SetColor(RGB(0,0,0));
		m_st7.InputText(L"年份:");
		m_st7.SetColor(RGB(0,0,0));
		m_st8.InputText(L"唱片标题:");
		m_st8.SetColor(RGB(0,0,0));
		m_st9.InputText(L"备注:");
		m_st9.SetColor(RGB(0,0,0));
		m_bopen.SetButtonImage(IDB_P_WJ1,IDB_P_WJ2,IDB_P_WJ1);
		m_bopen.SetTip(L"打开文件所在位置");
		m_baclose.SetButtonImage(IDB_P_B1,IDB_P_B2,IDB_P_B1);
		m_baclose.SetTip(L"关闭");
		ReadMusicInfo();
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CMinfo::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	CRect rect;
	GetClientRect(&rect);
	dc.FillSolidRect(rect,RGB(165,205,220));
	dc.FillSolidRect(0,0,rect.right,22,RGB(41,167,199));
	dc.SetBkMode(TRANSPARENT);
	dc.SelectObject(m_font);
	dc.SetTextColor(RGB(235,255,235));
	dc.TextOutW(0,2,L"音乐信息");
}


LRESULT CMinfo::OnNcHitTest(CPoint point)
{
	CRect rect;
	GetClientRect(&rect);
	ClientToScreen(&rect);
	return rect.PtInRect(point)?HTCAPTION:CDialogEx::OnNcHitTest(point);
}


void CMinfo::OnBnClickedBClose()
{
	EndDialog(0);
}


void CMinfo::OnClose()
{
	m_font.DeleteObject();
	CDialogEx::OnClose();
}



void CMinfo::OnBnClickedBuOk()
{
	EndDialog(0);
}

void CMinfo::ReadMusicInfo()
{
	wchar_t *name;
	name=PathFindFileName(m_Path);
	m_sname.InputText(name);
	m_sname.SetColor(RGB(0,0,0));
	m_sname.SetGD(true);
	m_spath.InputText(m_Path);
	m_spath.SetColor(RGB(0,0,0));
	m_spath.SetGD(true);
	HANDLE hfile=CreateFile(m_Path,GENERIC_READ,0,0,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,0);
	if(hfile==INVALID_HANDLE_VALUE)
		return;
	int size=GetFileSize(hfile,NULL);
	CloseHandle(hfile);
	wchar_t File_Size[52];
	wsprintf(File_Size,L"%dKB",size/1024);
	m_sfilesize.InputText(File_Size);
	m_sfilesize.SetColor(RGB(0,0,0));
	SHFILEINFO sfi;
	SHGetFileInfo(m_Path,0,&sfi,sizeof(sfi),SHGFI_TYPENAME);
	m_sfiletype.InputText(sfi.szTypeName);
	m_sfiletype.SetColor(RGB(0,0,0));
	Music_Info info;
	char path[MAX_PATH];
	CHWcharToAchar(m_Path,path);
	if(CHGetMusicInfo(path,&info))
	{
		if(info.tag[0]=='t'||info.tag[0]=='T')
			if(info.tag[1]=='a'||info.tag[1]=='A')
			if(info.tag[2]=='g'||info.tag[2]=='G')
			{
				wchar_t ti[52]={0},gs[52]={0},year[52]={0},bt[52]={0},bz[52];
		CHAcharToWchar(info.Title,ti);
		m_smusicname.InputText(ti);
		m_smusicname.SetColor(RGB(0,0,0));
		CHAcharToWchar(info.Artist,gs);
		m_ssong.InputText(gs);
		m_ssong.SetColor(RGB(0,0,0));
		CHAcharToWchar(info.Year,year);
		wchar_t data[52]={0};
		for(int i=0;i<4;i++)
			data[i]=year[i];
		m_syear.InputText(data);
		m_syear.SetColor(RGB(0,0,0));
		CHAcharToWchar(info.Album,bt);
		m_sbt.InputText(bt);
		m_sbt.SetColor(RGB(0,0,0));
		CHAcharToWchar(info.Comment,bz);
		memset(data,0x00,sizeof(data));
		for(int i=0;i<28;i++)
			data[i]=bz[i];
		m_sbz.InputText(data);
		m_sbz.SetColor(RGB(0,0,0));
			}
	}
}


void CMinfo::OnBnClickedBOpenfileselect()
{
	char path[MAX_PATH];
	CHWcharToAchar(m_Path,path);
	CHOpenFileSelect(path);
}
