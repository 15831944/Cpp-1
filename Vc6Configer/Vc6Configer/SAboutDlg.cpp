// SAboutDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Vc6Configer.h"
#include "SAboutDlg.h"


// CSAboutDlg dialog

IMPLEMENT_DYNAMIC(CSAboutDlg, CDialog)

CSAboutDlg::CSAboutDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSAboutDlg::IDD, pParent)
{

}

CSAboutDlg::~CSAboutDlg()
{
}

void CSAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CSAboutDlg, CDialog)
	ON_BN_CLICKED(IDC_USE_BTN, &CSAboutDlg::OnBnClickedUseBtn)
	ON_BN_CLICKED(IDC_DUTY_BTN, &CSAboutDlg::OnBnClickedDutyBtn)
	ON_NOTIFY(NM_CLICK, IDC_SYSLINK_ABOUT, &CSAboutDlg::OnNMClickSyslinkAbout)
	ON_NOTIFY(NM_CLICK, IDC_SYSLINK_UPDATE, &CSAboutDlg::OnNMClickSyslinkUpdate)
END_MESSAGE_MAP()


// CSAboutDlg message handlers

BOOL CSAboutDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	//SetDlgItemText(IDC_EDIT, _T("/////////////////////////////////////////////////////////////////////////////////////////////////////\r\n\r\n�����ʲô������飬����ϵQQ��7657318 �� ���ʼ�����7657318@qq.com��net_sy@sina.com.cn��Ҳ�ɵ�½ -=VC ��վ=- WwW.CcTry.CoM �������ʣ�\r\n\r\nлл��ҵ�ʹ�ã�( ^_^ )	\
	//	\r\n\r\n/////////////////////////////////////////////////////////////////////////////////////////////////////"));
	OnBnClickedUseBtn();

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CSAboutDlg::OnBnClickedUseBtn()
{
	CString str;
	str = _T("/////////////////////////////////////////////////////////////////////////////////////////////////////\r\n\r\n                       Visual C++ 6.0 �������ù��� v1.0\r\n\r\n�� ���ܼ�飺\r\n\r\n        �������ù���΢��� Visual Studio 2005/2008 ��")
		_T("���û� Visual C++ 6.0 ��ʱ�򣬻�о� Visual C++ 6.0 �ڽ����Ϻܼ�ª���������塢����ɫ�ȵȣ�ֻ��Ԥ�ȶ�����Ǽ��֡�")
		_T("���С���������΢�����ҵ����󣬿����Զ������� Visual C++ 6.0 �������ڵ����塢�����С��������ɫ������ɫ�ȵȣ�\r\n\r\n�� ʹ��˵����\r\n\r\n        ����Լ���ĥ���ðɣ�( ^_^ )\r\n\r\n")
		_T("�� Bug�����飺\r\n\r\n        �������ʹ�õĹ���������ʲôBug����ʲô�õĽ��飬����ϵ�ң�\r\n\r\n        QQ��7657318\r\n        eMail��7657318@qq.com\r\n                    net_sy@sina.com.cn")
		_T("\r\n\r\n                                                     ллʹ�ã�\r\n\r\n/////////////////////////////////////////////////////////////////////////////////////////////////////");
	SetDlgItemText(IDC_EDIT, str);
}

void CSAboutDlg::OnBnClickedDutyBtn()
{
	CString str;
	str = _T("/////////////////////////////////////////////////////////////////////////////////////////////////////\r\n\r\n                                ����������\r\n\r\n        1. �����Ϊ�����������Ա����ɵ�ʹ�á�������")
		_T("Ϊ�������ߣ��벻Ҫ�����޸ģ����󼰷���࣬���޸��뱣��������Ϣ��\r\n\r\n")
		_T("        2. ��ʹ�ñ�����޸����Ĺ���ʱ������֮ǰ���ñ��ݣ����ⶪʧ��")
		_T("���������ɵ��κ���ʧ�ͺ���������ге��������߼� -=VC ��վ=- WwW.CcTry.CoM �����κθ���\r\n\r\n")
		_T("        3. ������Ѿ���ʼʹ�ñ��������Ĭ�����Ѿ�ͬ�Ȿ�����������ге����Σ�")
		_T("\r\n\r\n\r\n\r\n                                                                                                                              ���ߣ�Syc\r\n                                                                                                                              ����-����\r\n                                                                                                                              2009-10-18\r\n\r\n/////////////////////////////////////////////////////////////////////////////////////////////////////");
	SetDlgItemText(IDC_EDIT, str);
}

void CSAboutDlg::OnNMClickSyslinkAbout(NMHDR *pNMHDR, LRESULT *pResult)
{
	ShellExecute(m_hWnd, _T("open"), _T("http://www.cctry.com"), NULL, NULL, SW_SHOW);
	*pResult = 0;
}

void CSAboutDlg::OnNMClickSyslinkUpdate(NMHDR *pNMHDR, LRESULT *pResult)
{
	ShellExecute(m_hWnd, _T("open"), _T("http://www.cctry.com/thread-875-1-1.html"), NULL, NULL, SW_SHOW);
	*pResult = 0;
}
