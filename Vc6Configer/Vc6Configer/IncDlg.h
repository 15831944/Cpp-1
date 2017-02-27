#pragma once
#include "afxwin.h"
#include "Inc.h"


// CIncDlg dialog

class CIncDlg : public CDialog
{
	DECLARE_DYNAMIC(CIncDlg)

public:
	CIncDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CIncDlg();

// Dialog Data
	enum { IDD = IDD_INCLUDE_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CString m_strAddPath;
	CListBox m_FolderList;
	CComboBox m_FileIndex;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedBrowse();
	BOOL ReadIncFolderInfo(CIncItem &tItem);
	BOOL WriteRegIncFolderInfo(CIncItem &tItem);
	DWORD GetCurrFileIndex();
	void GetCurrFolderSetInfo(CIncItem &tItem);
	DWORD GetCurrFolderArray(CStringArray &arrFolders);
	void ShowFolderInfo(CIncItem &tItem);
	BOOL EnableWindow(UINT uID, BOOL bEnable = TRUE);
	void SplitStrWithCharacter(CString in_Str, TCHAR in_Char, CStringArray &out_arrStr);
	afx_msg void OnCbnSelchangeFileindex();
	afx_msg void OnLbnSelchangeListbox();
	afx_msg void OnBnClickedUp();
	afx_msg void OnBnClickedDown();
	afx_msg void OnBnClickedAdd();
	afx_msg void OnBnClickedModify();
	afx_msg void OnBnClickedDel();
};
