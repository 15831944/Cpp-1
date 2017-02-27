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

	//SetDlgItemText(IDC_EDIT, _T("/////////////////////////////////////////////////////////////////////////////////////////////////////\r\n\r\n如果有什么问题或建议，请联系QQ：7657318 或 发邮件至：7657318@qq.com、net_sy@sina.com.cn，也可登陆 -=VC 驿站=- WwW.CcTry.CoM 进行提问！\r\n\r\n谢谢大家的使用！( ^_^ )	\
	//	\r\n\r\n/////////////////////////////////////////////////////////////////////////////////////////////////////"));
	OnBnClickedUseBtn();

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CSAboutDlg::OnBnClickedUseBtn()
{
	CString str;
	str = _T("/////////////////////////////////////////////////////////////////////////////////////////////////////\r\n\r\n                       Visual C++ 6.0 辅助配置工具 v1.0\r\n\r\n■ 功能简介：\r\n\r\n        如果大家用惯了微软的 Visual Studio 2005/2008 ，")
		_T("再用回 Visual C++ 6.0 的时候，会感觉 Visual C++ 6.0 在界面上很简陋，编码字体、背景色等等，只有预先定义的那几种。")
		_T("这个小软件可以稍微满足大家的需求，可以自定义设置 Visual C++ 6.0 各个窗口的字体、字体大小、字体颜色、背景色等等！\r\n\r\n■ 使用说明：\r\n\r\n        大家自己琢磨着用吧！( ^_^ )\r\n\r\n")
		_T("■ Bug及建议：\r\n\r\n        若大家在使用的过程中遇到什么Bug或有什么好的建议，请联系我：\r\n\r\n        QQ：7657318\r\n        eMail：7657318@qq.com\r\n                    net_sy@sina.com.cn")
		_T("\r\n\r\n                                                     谢谢使用！\r\n\r\n/////////////////////////////////////////////////////////////////////////////////////////////////////");
	SetDlgItemText(IDC_EDIT, str);
}

void CSAboutDlg::OnBnClickedDutyBtn()
{
	CString str;
	str = _T("/////////////////////////////////////////////////////////////////////////////////////////////////////\r\n\r\n                                ※免责声明\r\n\r\n        1. 本软件为免费软件，可以被自由的使用、传播。")
		_T("为尊重作者，请不要进行修改，捆绑及反汇编，若修改请保留作者信息！\r\n\r\n")
		_T("        2. 在使用本软件修改您的工程时，请您之前做好备份，以免丢失，")
		_T("凡因本软件造成的任何损失和后果，请自行承担，本作者及 -=VC 驿站=- WwW.CcTry.CoM 不做任何负责！\r\n\r\n")
		_T("        3. 如果您已经开始使用本软件，则默认您已经同意本声明，并自行承担责任！")
		_T("\r\n\r\n\r\n\r\n                                                                                                                              作者：Syc\r\n                                                                                                                              辽宁-大连\r\n                                                                                                                              2009-10-18\r\n\r\n/////////////////////////////////////////////////////////////////////////////////////////////////////");
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
