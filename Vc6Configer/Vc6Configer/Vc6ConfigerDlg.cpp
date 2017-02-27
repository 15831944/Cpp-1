
// Vc6ConfigerDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Vc6Configer.h"
#include "Vc6ConfigerDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CVc6ConfigerDlg 对话框




CVc6ConfigerDlg::CVc6ConfigerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CVc6ConfigerDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CVc6ConfigerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB1, m_TabCtrl);
	DDX_Control(pDX, IDC_STATIC_ABOUT, m_AboutStatic);
}

BEGIN_MESSAGE_MAP(CVc6ConfigerDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_WM_TIMER()
	ON_NOTIFY(NM_CLICK, IDC_SYSLINK, &CVc6ConfigerDlg::OnNMClickSyslink)
END_MESSAGE_MAP()


// CVc6ConfigerDlg 消息处理程序

BOOL CVc6ConfigerDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}
	pSysMenu->DeleteMenu(0, MF_BYPOSITION);
	pSysMenu->DeleteMenu(1, MF_BYPOSITION);
	pSysMenu->DeleteMenu(2, MF_BYPOSITION);

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	m_AboutStatic.SetTextColor(RGB(0, 0, 255));

	m_TabCtrl.AddPage(_T("包含目录设定"), &m_IncDlg, IDD_INCLUDE_DLG);
	m_TabCtrl.AddPage(_T("字体设定"), &m_FontDlg, IDD_FONT_DLG);
	m_TabCtrl.AddPage(_T("颜色设定"), &m_ColorDlg, IDD_COLOR_DLG);
	m_TabCtrl.AddPage(_T("颜色插件"), &m_PluginDlg, IDD_PLUGIN_DLG);
	m_TabCtrl.AddPage(_T("其他插件"), &m_OPluginDlg, IDD_OPLUGIN_DLG);
	m_TabCtrl.AddPage(_T("软件说明"), &m_AboutDlg, IDD_ABOUT_DLG);
	m_TabCtrl.AddPage(_T("-=VC驿站=-"), &m_TryDlg, IDD_CCTRY_DLG);
	m_TabCtrl.Show(5);
	SetProp(m_hWnd, _T("Vc6Configer_Prop"), (HANDLE)DIY_PROP_CODE);
	SetTimer(1, 1000, NULL);
	AnimateWindow(200, AW_CENTER);

	return FALSE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CVc6ConfigerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CVc6ConfigerDlg::OnPaint()
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
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CVc6ConfigerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CVc6ConfigerDlg::OnTimer(UINT_PTR nIDEvent)
{
	BOOL isCancel = FALSE;
	BOOL bRet = ((CVc6ConfigerApp *)AfxGetApp)->CheckProcessExist(_T("MSDEV.EXE"));
	if ( bRet ) {
		KillTimer(1);
		do {
			if ( IDRETRY == MessageBox(_T("请在运行本程序期间退出 Visual C++ 6.0，谢谢合作！\r\n\r\n\r\n点击 “重试” 按钮，重新检测 Visual C++ 6.0 是否存在；\r\n点击 “取消” 按钮，退出本程序 ！"), _T("友情提示"), MB_RETRYCANCEL | MB_ICONWARNING) ) {
				bRet = ((CVc6ConfigerApp *)AfxGetApp)->CheckProcessExist(_T("MSDEV.EXE"));
			}else{
				isCancel = TRUE;
				OnCancel();
				break;
			}
		} while ( bRet );
	}
	if ( isCancel == FALSE ) {
		SetTimer(1, 1000, NULL);
		CDialog::OnTimer(nIDEvent);
	}
}

void CVc6ConfigerDlg::OnNMClickSyslink(NMHDR *pNMHDR, LRESULT *pResult)
{
	ShellExecute(m_hWnd, _T("open"), _T("http://www.cctry.com"), NULL, NULL, SW_SHOW);
	*pResult = 0;
}

void CVc6ConfigerDlg::OnCancel()
{
	KillTimer(1);
	AnimateWindow(400, AW_HIDE | AW_CENTER);
	CDialog::OnCancel();
}
