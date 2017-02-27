// IncDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Vc6Configer.h"
#include "IncDlg.h"


// CIncDlg dialog

IMPLEMENT_DYNAMIC(CIncDlg, CDialog)

CIncDlg::CIncDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CIncDlg::IDD, pParent)
	, m_strAddPath(_T(""))
{
}

CIncDlg::~CIncDlg()
{
}

void CIncDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC1_FILEINDEX, m_FileIndex);
	DDX_Control(pDX, IDC_LISTBOX, m_FolderList);
	DDX_Text(pDX, IDC1_PATH, m_strAddPath);
}


BEGIN_MESSAGE_MAP(CIncDlg, CDialog)
	ON_BN_CLICKED(IDC1_BROWSE, &CIncDlg::OnBnClickedBrowse)
	ON_CBN_SELCHANGE(IDC1_FILEINDEX, &CIncDlg::OnCbnSelchangeFileindex)
	ON_LBN_SELCHANGE(IDC_LISTBOX, &CIncDlg::OnLbnSelchangeListbox)
	ON_BN_CLICKED(IDC1_UP, &CIncDlg::OnBnClickedUp)
	ON_BN_CLICKED(IDC1_DOWN, &CIncDlg::OnBnClickedDown)
	ON_BN_CLICKED(IDC1_ADD, &CIncDlg::OnBnClickedAdd)
	ON_BN_CLICKED(IDC1_MODIFY, &CIncDlg::OnBnClickedModify)
	ON_BN_CLICKED(IDC1_DEL, &CIncDlg::OnBnClickedDel)
END_MESSAGE_MAP()

BOOL CIncDlg::EnableWindow(UINT uID, BOOL bEnable)
{
	return ::EnableWindow(GetDlgItem(uID)->m_hWnd, bEnable);
}

// CIncDlg message handlers

BOOL CIncDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	CIncItem tItemExe;
	m_FileIndex.InsertString(0, _T("Executable Files"));
	m_FileIndex.InsertString(1, _T("Include Files"));
	m_FileIndex.InsertString(2, _T("Library Files"));
	m_FileIndex.InsertString(3, _T("Source Files"));
	m_FileIndex.SetCurSel(0);

	tItemExe.m_dwFileIndex = Executable_Files;
	ReadIncFolderInfo(tItemExe);
	ShowFolderInfo(tItemExe);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CIncDlg::OnBnClickedBrowse()
{
	TCHAR szFolderName[MAX_PATH] = {0}, szFullPath[MAX_PATH] = {0};
	BROWSEINFO mBroInfo = {0};
	mBroInfo.hwndOwner = m_hWnd;
	mBroInfo.iImage = 0;
	mBroInfo.lParam = 0;
	mBroInfo.lpfn = NULL;
	mBroInfo.lpszTitle = _T("请选择一个目录...");
	mBroInfo.pidlRoot = NULL;
	mBroInfo.pszDisplayName = szFolderName;
	mBroInfo.ulFlags = BIF_RETURNONLYFSDIRS;
	ITEMIDLIST *pidl = ::SHBrowseForFolder(&mBroInfo);
	if (::SHGetPathFromIDList(pidl, szFullPath) == TRUE){
		SetDlgItemText(IDC1_PATH, szFullPath);
	}
}

BOOL CIncDlg::ReadIncFolderInfo(CIncItem &tItem)
{
	HKEY hKey = NULL;
	LONG dwRet = 0;
	DWORD cbData = 0;
	CString strValueName;
	CString strSubKey = _T("Software\\Microsoft\\DevStudio\\6.0\\Build System\\Components\\Platforms\\Win32 (x86)\\Directories");
	switch(tItem.m_dwFileIndex)
	{
	case Executable_Files:
		strValueName = _T("Path Dirs");
		break;
	case Include_Files:
		strValueName = _T("Include Dirs");
		break;
	case Library_Files:
		strValueName = _T("Library Dirs");
		break;
	case Source_Files:
		strValueName = _T("Source Dirs");
		break;
	default:return FALSE;
	}

	dwRet = RegOpenKeyEx(HKEY_CURRENT_USER, strSubKey, 0, KEY_ALL_ACCESS, &hKey);
	if ( dwRet != ERROR_SUCCESS ){
		RegCloseKey(hKey);
		return FALSE;
	}
	dwRet = RegQueryValueEx(hKey, strValueName, NULL, NULL, NULL, &cbData);
	if ( dwRet != ERROR_SUCCESS ){
		RegCloseKey(hKey);
		return FALSE;
	}
	TCHAR *lpData = new TCHAR[cbData+1];
	ZeroMemory(lpData, cbData+1);
	dwRet = RegQueryValueEx(hKey, strValueName, NULL, NULL, (LPBYTE)lpData, &cbData);
	if ( dwRet != ERROR_SUCCESS ){
		RegCloseKey(hKey);
		delete [] lpData;
		return FALSE;
	}
	SplitStrWithCharacter(lpData, ';', tItem.m_strArrFolder);
	RegCloseKey(hKey);
	delete [] lpData;
	return TRUE;
}

BOOL CIncDlg::WriteRegIncFolderInfo(CIncItem &tItem)
{
	BOOL bRet = TRUE;
	HKEY hKey = NULL;
	TCHAR *lpszValue = NULL;
	LONG dwRet = 0;
	DWORD cbData = 0, dwLen;
	CString strValueName, strNewValue;
	CString strSubKey = _T("Software\\Microsoft\\DevStudio\\6.0\\Build System\\Components\\Platforms\\Win32 (x86)\\Directories");
	switch(tItem.m_dwFileIndex)
	{
	case Executable_Files:
		strValueName = _T("Path Dirs");
		break;
	case Include_Files:
		strValueName = _T("Include Dirs");
		break;
	case Library_Files:
		strValueName = _T("Library Dirs");
		break;
	case Source_Files:
		strValueName = _T("Source Dirs");
		break;
	default:return FALSE;
	}

	dwRet = RegOpenKeyEx(HKEY_CURRENT_USER, strSubKey, 0, KEY_ALL_ACCESS, &hKey);
	if ( dwRet != ERROR_SUCCESS ){
		RegCloseKey(hKey);
		return FALSE;
	}
	for ( INT_PTR idx = 0; idx < tItem.m_strArrFolder.GetCount(); idx++ ) {
		strNewValue += tItem.m_strArrFolder.GetAt(idx)+_T(";");
	}
	strNewValue.Delete(strNewValue.ReverseFind(';'));
	dwLen = strNewValue.GetLength()+1;
	lpszValue = new TCHAR[dwLen];
	ZeroMemory(lpszValue, dwLen);
	_tcscpy_s(lpszValue, dwLen, strNewValue);
	dwRet = RegSetValueEx(hKey, strValueName, 0, REG_SZ, (LPBYTE)lpszValue, dwLen*sizeof(TCHAR));
	if ( dwRet != ERROR_SUCCESS ) {
		bRet = FALSE;
	}
	delete [] lpszValue;
	RegCloseKey(hKey);
	return bRet;
}

void CIncDlg::SplitStrWithCharacter(CString in_Str, TCHAR in_Char, CStringArray &out_arrStr)
{
	out_arrStr.RemoveAll();
	int last = 0, cur = 0, i = 0, index = 0;
	for (i = 0; i < in_Str.GetLength(); i++){
		if ( in_Str[i] == in_Char ){
			cur = i;
			out_arrStr.Add( in_Str.Mid(last, cur-last) );
			last = cur+1;
		}
	}
	out_arrStr.Add( in_Str.Mid(last, in_Str.GetLength()-last) );
}

void CIncDlg::ShowFolderInfo(CIncItem &tItem)
{
	for ( UINT index = 0; index < (UINT)tItem.m_strArrFolder.GetCount(); index++ ){
		m_FolderList.InsertString(index, tItem.m_strArrFolder.GetAt(index));
	}
}

DWORD CIncDlg::GetCurrFileIndex()
{
	UpdateData(TRUE);
	DWORD dwRet = 0;
	CString strFileIndex;
	GetDlgItemText(IDC1_FILEINDEX, strFileIndex);
	switch( strFileIndex[0] )
	{
	case 'E':
		{
			dwRet = Executable_Files;
			break;
		}
	case 'I':
		{
			dwRet = Include_Files;
			break;
		}
	case 'L':
		{
			dwRet = CIncItem::_Library_Files;
			break;
		}
	case 'S':
		{
			dwRet = CIncItem::_Source_Files;
			break;
		}
	default:break;
	}
	return dwRet;
}

DWORD CIncDlg::GetCurrFolderArray(CStringArray &arrFolders)
{
	CString strText;
	arrFolders.RemoveAll();
	for ( int idx = 0; idx < m_FolderList.GetCount(); idx++ ) {
		m_FolderList.GetText(idx, strText);
		arrFolders.Add(strText);
	}
	return arrFolders.GetCount();
}

void CIncDlg::OnCbnSelchangeFileindex()
{
	UpdateData(TRUE);
	m_FolderList.ResetContent();
	CString strTemp;
	GetDlgItemText(IDC1_FILEINDEX, strTemp);
	CIncItem tItem;
	switch( strTemp[0] )
	{
	case 'E':
		{
			tItem.m_dwFileIndex = Executable_Files;
			ReadIncFolderInfo(tItem);
			ShowFolderInfo(tItem);
			break;
		}
	case 'I':
		{
			tItem.m_dwFileIndex = Include_Files;
			ReadIncFolderInfo(tItem);
			ShowFolderInfo(tItem);
			break;
		}
	case 'L':
		{
			tItem.m_dwFileIndex = Library_Files;
			ReadIncFolderInfo(tItem);
			ShowFolderInfo(tItem);
			break;
		}
	case 'S':
		{
			tItem.m_dwFileIndex = Source_Files;
			ReadIncFolderInfo(tItem);
			ShowFolderInfo(tItem);
			break;
		}
	}
	SetDlgItemText(IDC1_PATH, _T(""));
}

void CIncDlg::OnLbnSelchangeListbox()
{
	UpdateData(TRUE);
	int iSelect = m_FolderList.GetCurSel();
	if ( iSelect >= 0 ) {
		m_FolderList.GetText(m_FolderList.GetCurSel(), m_strAddPath);
		UpdateData(FALSE);
	}
}

void CIncDlg::OnBnClickedUp()
{
	CString strText;
	int iSelect = m_FolderList.GetCurSel();
	if ( iSelect > 0  ) {
		CIncItem tItem;
		m_FolderList.GetText(iSelect, strText);
		m_FolderList.DeleteString(iSelect);
		m_FolderList.SetCurSel(m_FolderList.InsertString(iSelect-1, strText));
		GetCurrFolderSetInfo(tItem);
		if ( !WriteRegIncFolderInfo(tItem)  ) {
			MessageBox(_T("修改失败！"), _T("友情提示"), MB_OK|MB_ICONERROR);
			m_FolderList.InsertString(iSelect, strText);
		}
	}
}

void CIncDlg::OnBnClickedDown()
{
	CString strText;
	int iSelect = m_FolderList.GetCurSel();
	if ( iSelect >= 0 && iSelect < m_FolderList.GetCount()-1 ) {
		CIncItem tItem;
		m_FolderList.GetText(iSelect, strText);
		m_FolderList.DeleteString(iSelect);
		m_FolderList.SetCurSel(m_FolderList.InsertString(iSelect+1, strText));
		GetCurrFolderSetInfo(tItem);
		if ( !WriteRegIncFolderInfo(tItem)  ) {
			MessageBox(_T("修改失败！"), _T("友情提示"), MB_OK|MB_ICONERROR);
			m_FolderList.InsertString(iSelect, strText);
		}
	}
}

void CIncDlg::OnBnClickedAdd()
{
	UpdateData(TRUE);
	CIncItem tItem;
	if ( !m_strAddPath.IsEmpty()) {
		int iFind = m_FolderList.FindString(-1, m_strAddPath);
		if ( iFind != -1 ) {
			m_FolderList.SetCurSel(iFind);
			MessageBox(_T("列表中已经存在相同路径的目录，请不要重复添加！"), _T("友情提示"), MB_OK|MB_ICONWARNING);
			return;
		}
		int iInsert = m_FolderList.InsertString(m_FolderList.GetCount(), m_strAddPath);
		m_FolderList.SetCurSel(iInsert);
		GetCurrFolderSetInfo(tItem);
		if ( !WriteRegIncFolderInfo(tItem)  ) {
			MessageBox(_T("添加失败！"), _T("友情提示"), MB_OK|MB_ICONERROR);
			m_FolderList.DeleteString(iInsert);
		}else{
			MessageBox(_T("添加成功！"), _T("友情提示"), MB_OK|MB_ICONWARNING);
		}
	}else{
		MessageBox(_T("请先选择一个目录！"), _T("友情提示"), MB_OK|MB_ICONWARNING);
	}
}

void CIncDlg::OnBnClickedModify()
{
	CIncItem tItem;
	CString strText;
	int iInsert = -1;
	int iSelect = m_FolderList.GetCurSel();
	if ( iSelect >= 0 ) {
		UpdateData(TRUE);
		if ( !m_strAddPath.IsEmpty() && m_strAddPath != strText && m_strAddPath.GetLength() < MAX_PATH) {
			if ( m_FolderList.FindString(-1, m_strAddPath) != -1 ) {
				MessageBox(_T("列表中已存在相同路径的目录，请核对后再修改！"), _T("友情提示"), MB_OK|MB_ICONWARNING);
				return;
			}
			m_FolderList.GetText(iSelect, strText);
			m_FolderList.DeleteString(iSelect);
			iInsert = m_FolderList.InsertString(iSelect, m_strAddPath);
			m_FolderList.SetCurSel(iInsert);
			GetCurrFolderSetInfo(tItem);
			if ( !WriteRegIncFolderInfo(tItem)  ) {
				MessageBox(_T("修改失败！"), _T("友情提示"), MB_OK|MB_ICONERROR);
				m_FolderList.DeleteString(iInsert);
			}
		}
	}else{
		MessageBox(_T("请先从以下列表中选择一项！"), _T("友情提示"), MB_OK|MB_ICONWARNING);
	}
}

void CIncDlg::OnBnClickedDel()
{
	int iSelect = m_FolderList.GetCurSel();
	if ( iSelect >= 0 ) {
		CIncItem tItem;
		CString strText;
		m_FolderList.GetText(iSelect, strText);
		if ( MessageBox(_T("确定要删除  ") + strText + _T("  吗？"), _T("友情提示"), MB_OKCANCEL | MB_ICONQUESTION ) != IDOK ) {
			return;
		}
		m_FolderList.DeleteString(iSelect);
		GetCurrFolderSetInfo(tItem);
		if ( !WriteRegIncFolderInfo(tItem)  ) {
			MessageBox(_T("删除失败！"), _T("友情提示"), MB_OK|MB_ICONERROR);
			m_FolderList.InsertString(iSelect, strText);
		}
	}else{
		MessageBox(_T("请先从以下列表中选择一项！"), _T("友情提示"), MB_OK|MB_ICONWARNING);
	}
}

void CIncDlg::GetCurrFolderSetInfo(CIncItem &tItem)
{
	UpdateData(TRUE);
	CString strTemp;
	GetDlgItemText(IDC1_FILEINDEX, strTemp);
	switch( strTemp[0] )
	{
	case 'E':
		{
			tItem.m_dwFileIndex = Executable_Files;
			break;
		}
	case 'I':
		{
			tItem.m_dwFileIndex = Include_Files;
			break;
		}
	case 'L':
		{
			tItem.m_dwFileIndex = Library_Files;
			break;
		}
	case 'S':
		{
			tItem.m_dwFileIndex = Source_Files;
			break;
		}
	}
	CString strText;
	tItem.m_strArrFolder.RemoveAll();
	for ( int idx = 0; idx < m_FolderList.GetCount(); idx++ ) {
		m_FolderList.GetText(idx, strText);
		tItem.m_strArrFolder.Add(strText);
	}
}
