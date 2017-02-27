// PluginDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Vc6Configer.h"
#include "PluginDlg.h"


// CPluginDlg dialog

IMPLEMENT_DYNAMIC(CPluginDlg, CDialog)

CPluginDlg::CPluginDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPluginDlg::IDD, pParent)
{

}

CPluginDlg::~CPluginDlg()
{
}

void CPluginDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CPluginDlg, CDialog)
	ON_BN_CLICKED(IDC_APPLY_COLOR_PLUGIN, &CPluginDlg::OnBnClickedApplyPlugin)
	ON_BN_CLICKED(IDC_UN_COLOR_PLUGIN, &CPluginDlg::OnBnClickedUnColorPlugin)
END_MESSAGE_MAP()


// CPluginDlg message handlers

CString CPluginDlg::GetPluginPath()
{
	CString strPath;
	HKEY hKey = NULL;
	DWORD dwLen = MAX_PATH*sizeof(TCHAR);
	TCHAR szPath[MAX_PATH] = {0};
	CString strSubKeyInstall = _T("Software\\Microsoft\\DevStudio\\6.0\\Directories");
	DWORD dwRet = RegOpenKeyEx(HKEY_CURRENT_USER, strSubKeyInstall, 0, KEY_ALL_ACCESS, &hKey);
	if ( dwRet != ERROR_SUCCESS ){
		goto __Error_End;
	}
	dwRet = RegQueryValueEx(hKey, _T("Install Dirs"), 0, NULL, (LPBYTE)szPath, &dwLen);
	if ( dwRet != ERROR_SUCCESS ){
		goto __Error_End;
	}
	strPath = szPath;
	strPath = strPath.Left(strPath.Find(_T("MSDev98"))+7);
	strPath += _T("\\AddIns");
__Error_End:
	RegCloseKey(hKey);
	return strPath;
}

BOOL CPluginDlg::ReleasePlugin(CString strPluginFile)
{
	CFile mFile;
	HRSRC hRes = FindResource(NULL, MAKEINTRESOURCE(IDR_TRUE_COLOR_LIB),  _T("TRUE_COLOR_LIB"));
	if ( !hRes ) {
		return FALSE;
	}
	HGLOBAL gLobal = LoadResource(NULL, hRes);
	if ( !gLobal ) {
		return FALSE;
	}
	LPVOID pBuf = LockResource(gLobal);
	if ( !pBuf ) {
		return FALSE;
	}
	if ( mFile.Open(strPluginFile, CFile::modeCreate | CFile::modeWrite) ) {
		mFile.Write(pBuf, SizeofResource(AfxGetResourceHandle(), hRes));
		mFile.Close();
		return TRUE;
	}else{
		return FALSE;
	}
}
BOOL CPluginDlg::ModRegColorPlugin(CString strPluginFile)
{
	BOOL bRet = FALSE;
	HKEY hKey = NULL;
	DWORD dwRet = 0;
	TCHAR szPluginFile[MAX_PATH] = {0};
	_tcscpy_s(szPluginFile, MAX_PATH, strPluginFile);
	TCHAR szSubKeyAddIn[] = _T("Software\\Microsoft\\DevStudio\\6.0\\AddIns\\DevTrueColour.DSAddIn.1");
	TCHAR szDisplayName[] = _T("DevTrueColour.DSAddIn.1");
	TCHAR szDescription[] = _T("Adds true colour selection  to Developer Studio Tools | Options | Format");
	TCHAR szDefault[] = _T("1");
	dwRet = RegCreateKey(HKEY_CURRENT_USER, szSubKeyAddIn, &hKey);
	if ( dwRet != ERROR_SUCCESS ){
		goto __Error_End;
	}
	dwRet = RegSetValueEx(hKey, _T("Filename"), 0, REG_SZ, (LPBYTE)szPluginFile, _tcslen(szPluginFile)*sizeof(TCHAR));
	if ( dwRet != ERROR_SUCCESS ){
		goto __Error_End;
	}
	dwRet = RegSetValueEx(hKey, _T("DisplayName"), 0, REG_SZ, (LPBYTE)szDisplayName, _tcslen(szDisplayName)*sizeof(TCHAR));
	if ( dwRet != ERROR_SUCCESS ){
		goto __Error_End;
	}
	dwRet = RegSetValueEx(hKey, _T("Description"), 0, REG_SZ, (LPBYTE)szDescription, _tcslen(szDescription)*sizeof(TCHAR));
	if ( dwRet != ERROR_SUCCESS ){
		goto __Error_End;
	}
	dwRet = RegSetValueEx(hKey, NULL, 0, REG_SZ, (LPBYTE)szDefault, _tcslen(szDefault)*sizeof(TCHAR));
	if ( dwRet != ERROR_SUCCESS ){
		goto __Error_End;
	}
	bRet = TRUE;
__Error_End:
	RegCloseKey(hKey);
	return bRet;
}

BOOL CPluginDlg::RegDeleteColorPlugin()
{
	BOOL bRet = FALSE;
	HKEY hKey = NULL;
	TCHAR szSubKeyAddIn[] = _T("Software\\Microsoft\\DevStudio\\6.0\\AddIns");
	DWORD dwRet = RegOpenKeyEx(HKEY_CURRENT_USER, szSubKeyAddIn, 0, KEY_ALL_ACCESS, &hKey);
	if ( dwRet != ERROR_SUCCESS ){
		goto __Error_End;
	}
	if ( RegDeleteKey(hKey, _T("DevTrueColour.DSAddIn.1")) == ERROR_SUCCESS ) {
		bRet = TRUE;
	}
__Error_End:
	RegCloseKey(hKey);
	return bRet;
}

void CPluginDlg::OnBnClickedApplyPlugin()
{
	if ( MessageBox(_T("您确定要安装该颜色插件吗？"), _T("友情提示"), MB_OKCANCEL|MB_ICONQUESTION) == IDCANCEL) {
		return;
	}
	CString strPluginPath = GetPluginPath();
	CString strPluginFile = strPluginPath + _T("\\DevTrueColour.dll");
	if ( !strPluginPath.IsEmpty() && PathFileExists(strPluginPath) && ReleasePlugin(strPluginFile) && ModRegColorPlugin(strPluginFile) ) {
		MessageBox(_T("成功安装颜色插件！"), _T("友情提示"), MB_OK|MB_ICONWARNING);
	}else{
		MessageBox(_T("颜色插件安装失败！"), _T("友情提示"), MB_OK|MB_ICONERROR);
	}
}

void CPluginDlg::OnBnClickedUnColorPlugin()
{
	if ( MessageBox(_T("您确定要卸载该颜色插件吗？"), _T("友情提示"), MB_OKCANCEL|MB_ICONQUESTION) == IDCANCEL) {
		return;
	}
	int bResult = 0;
	CString strPluginFile = GetPluginPath() + _T("\\DevTrueColour.dll");
	if ( !PathFileExists(strPluginFile) ) {
		bResult = -1;
	}else{
		if ( DeleteFile(strPluginFile) && RegDeleteColorPlugin() ) {
			bResult = 1;
		}else{
			bResult = 0;
		}
	}
	if ( bResult == 1 ) {
		MessageBox(_T("成功卸载颜色插件！"), _T("友情提示"), MB_OK|MB_ICONWARNING);
	}else if ( bResult == 0 ) {
		MessageBox(_T("卸载颜色插件失败！"), _T("友情提示"), MB_OK|MB_ICONERROR);
	}else{
		MessageBox(_T("您没有安装该颜色插件，无需卸载！"), _T("友情提示"), MB_OK|MB_ICONWARNING);
	}
}
