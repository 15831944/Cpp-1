// CTryDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Vc6Configer.h"
#include "CTryDlg.h"


// CCTryDlg dialog

IMPLEMENT_DYNAMIC(CCTryDlg, CDialog)

CCTryDlg::CCTryDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCTryDlg::IDD, pParent)
{

}

CCTryDlg::~CCTryDlg()
{
}

void CCTryDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EXPLORER, m_WebBrw);
}


BEGIN_MESSAGE_MAP(CCTryDlg, CDialog)
END_MESSAGE_MAP()


// CCTryDlg message handlers

BOOL CCTryDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_WebBrw.Navigate(_T("http://www.cctry.com"), NULL, NULL, NULL, NULL);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
