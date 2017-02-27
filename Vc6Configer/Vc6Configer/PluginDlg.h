#pragma once


// CPluginDlg dialog

class CPluginDlg : public CDialog
{
	DECLARE_DYNAMIC(CPluginDlg)

public:
	CPluginDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CPluginDlg();

// Dialog Data
	enum { IDD = IDD_PLUGIN_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedApplyPlugin();
	CString GetPluginPath();
	BOOL ReleasePlugin(CString strPluginFile);
	BOOL ModRegColorPlugin(CString strPluginFile);
	BOOL RegDeleteColorPlugin();
	afx_msg void OnBnClickedUnColorPlugin();
};
