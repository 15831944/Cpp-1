// OPluginDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Vc6Configer.h"
#include "OPluginDlg.h"


// COPluginDlg dialog

IMPLEMENT_DYNAMIC(COPluginDlg, CDialog)

COPluginDlg::COPluginDlg(CWnd* pParent /*=NULL*/)
	: CDialog(COPluginDlg::IDD, pParent)
{

}

COPluginDlg::~COPluginDlg()
{
}

void COPluginDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(COPluginDlg, CDialog)
	ON_NOTIFY(NM_CLICK, IDC_SYSLINK_WNDTABS, &COPluginDlg::OnNMClickSyslinkWndtabs)
	ON_NOTIFY(NM_CLICK, IDC_SYSLINK_VA, &COPluginDlg::OnNMClickSyslinkVa)
END_MESSAGE_MAP()


// COPluginDlg message handlers

void COPluginDlg::OnNMClickSyslinkWndtabs(NMHDR *pNMHDR, LRESULT *pResult)
{
	ShellExecute(m_hWnd, _T("open"), _T("http://www.cctry.com/thread-159-1-1.html"), NULL, NULL, SW_SHOW);
	*pResult = 0;
}

void COPluginDlg::OnNMClickSyslinkVa(NMHDR *pNMHDR, LRESULT *pResult)
{
	ShellExecute(m_hWnd, _T("open"), _T("http://www.cctry.com/thread-160-1-1.html"), NULL, NULL, SW_SHOW);
	*pResult = 0;
}
