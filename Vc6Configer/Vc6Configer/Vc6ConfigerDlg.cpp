
// Vc6ConfigerDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Vc6Configer.h"
#include "Vc6ConfigerDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

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

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CVc6ConfigerDlg �Ի���




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


// CVc6ConfigerDlg ��Ϣ�������

BOOL CVc6ConfigerDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	m_AboutStatic.SetTextColor(RGB(0, 0, 255));

	m_TabCtrl.AddPage(_T("����Ŀ¼�趨"), &m_IncDlg, IDD_INCLUDE_DLG);
	m_TabCtrl.AddPage(_T("�����趨"), &m_FontDlg, IDD_FONT_DLG);
	m_TabCtrl.AddPage(_T("��ɫ�趨"), &m_ColorDlg, IDD_COLOR_DLG);
	m_TabCtrl.AddPage(_T("��ɫ���"), &m_PluginDlg, IDD_PLUGIN_DLG);
	m_TabCtrl.AddPage(_T("�������"), &m_OPluginDlg, IDD_OPLUGIN_DLG);
	m_TabCtrl.AddPage(_T("���˵��"), &m_AboutDlg, IDD_ABOUT_DLG);
	m_TabCtrl.AddPage(_T("-=VC��վ=-"), &m_TryDlg, IDD_CCTRY_DLG);
	m_TabCtrl.Show(5);
	SetProp(m_hWnd, _T("Vc6Configer_Prop"), (HANDLE)DIY_PROP_CODE);
	SetTimer(1, 1000, NULL);
	AnimateWindow(200, AW_CENTER);

	return FALSE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CVc6ConfigerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
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
			if ( IDRETRY == MessageBox(_T("�������б������ڼ��˳� Visual C++ 6.0��лл������\r\n\r\n\r\n��� �����ԡ� ��ť�����¼�� Visual C++ 6.0 �Ƿ���ڣ�\r\n��� ��ȡ���� ��ť���˳������� ��"), _T("������ʾ"), MB_RETRYCANCEL | MB_ICONWARNING) ) {
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
