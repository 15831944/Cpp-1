#pragma once


// COPluginDlg dialog

class COPluginDlg : public CDialog
{
	DECLARE_DYNAMIC(COPluginDlg)

public:
	COPluginDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~COPluginDlg();

// Dialog Data
	enum { IDD = IDD_OPLUGIN_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnNMClickSyslinkWndtabs(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMClickSyslinkVa(NMHDR *pNMHDR, LRESULT *pResult);
};
