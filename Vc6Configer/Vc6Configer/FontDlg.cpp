// FontDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Vc6Configer.h"
#include "FontDlg.h"


// CFontDlg dialog

IMPLEMENT_DYNAMIC(CFontDlg, CDialog)

CFontDlg::CFontDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CFontDlg::IDD, pParent)
{
	m_pDc = NULL;
	m_hExample = NULL;
	ZeroMemory(&mlFont, sizeof(mlFont));
	m_strFontName = _T("Times New Roman");
	m_strFontSize = _T("12");
	m_bkColor = 0;
}

CFontDlg::~CFontDlg()
{
}

void CFontDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC2_LISTCTRL, m_FontListCtrl);
	DDX_Control(pDX, IDC2_SELWND, m_WndComBox);
	DDX_Control(pDX, IDC2_SELFONT, m_FontComBox);
	DDX_Control(pDX, IDC2_FONTSIZE, m_FontSizeComBox);
}


BEGIN_MESSAGE_MAP(CFontDlg, CDialog)
	ON_NOTIFY(NM_CLICK, IDC2_LISTCTRL, &CFontDlg::OnNMClickListctrl)
	ON_CBN_SELCHANGE(IDC2_SELWND, &CFontDlg::OnCbnSelchangeSelwnd)
	ON_CBN_SELCHANGE(IDC2_SELFONT, &CFontDlg::OnCbnSelchangeSelfont)
	ON_CBN_SELCHANGE(IDC2_FONTSIZE, &CFontDlg::OnCbnSelchangeFontsize)
	ON_BN_CLICKED(IDC2_SET, &CFontDlg::OnBnClickedSet)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CFontDlg message handlers

BOOL CFontDlg::EnableWindow(UINT uID, BOOL bEnable)
{
	return ::EnableWindow(GetDlgItem(uID)->m_hWnd, bEnable);
}

BOOL CFontDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	EnableWindow(IDC2_SET, FALSE);

	int idx = 0, index = 0;
	m_FontListCtrl.SetExtendedStyle( m_FontListCtrl.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES );
	m_FontListCtrl.InsertColumn(0, _T("窗口名称"), 0, 120);
	m_FontListCtrl.InsertColumn(1, _T("字体名称"), 0, 100);
	m_FontListCtrl.InsertColumn(2, _T("字体大小"), 0, 70);
	TCHAR *szWnd[] = {
		_T("Source Window"),
		_T("Debugger Window"),
		_T("Source Browser"),
		_T("Output Window"),
		_T("Workspace Window"),
		_T("Registers Window"),
		_T("Memory Window"),
		_T("Calls Window"),
		_T("Variables Window"),
		_T("Watch Window"),
		_T("Disassembly Window"),
		//_T("All Windows")
		0
	};

	for ( idx = 0; szWnd[idx]; idx++ ) {
		CFontItem tItem;
		tItem.m_strWnd = szWnd[idx];
		ReadDefaultFontInfo(tItem);
		m_WndComBox.InsertString(idx, szWnd[idx]);
		m_FontListCtrl.InsertItem(idx, _T(""));
		m_FontListCtrl.SetItemText(idx, 0, szWnd[idx]);
		m_FontListCtrl.SetItemText(idx, 1, tItem.m_strFont);
		m_FontListCtrl.SetItemText(idx, 2, tItem.m_strSize);
	}

	GetSysFontList();
	CString str;
	for ( idx = 0, index = 6; index <= 24; idx++, index++ ){
		str.Format(_T("%d"), index);
		m_FontSizeComBox.InsertString(idx, str);
	}

	m_hExample = GetDlgItem(IDC_STATIC_FONT)->GetSafeHwnd();
	::GetWindowRect(m_hExample, &m_ShowRect);
	ScreenToClient(&m_ShowRect);
	m_bkColor = GetSysColor(COLOR_3DFACE);
	SetTimer(1, 100, NULL);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

int CALLBACK EnumFontListProc( ENUMLOGFONTEX *lpelfe, NEWTEXTMETRICEX *lpntme, DWORD FontType, LPARAM lParam )
{
	CStringList *strFontList = (CStringList *)lParam;
	POSITION pos = strFontList->Find((LPCTSTR)lpelfe->elfFullName);
	if ( pos == NULL && lpelfe->elfFullName[0] != '@'){
		pos = strFontList->AddTail((LPCTSTR)lpelfe->elfFullName);
	}
	return TRUE;
}

void CFontDlg::GetSysFontList()
{
	CString strFont;
	POSITION pos = 0;
	CStringList arrFontList;
	arrFontList.RemoveAll();
	m_FontComBox.ResetContent();
	LOGFONT m_LogFont = {0};
	m_LogFont.lfCharSet = DEFAULT_CHARSET;
	m_LogFont.lfFaceName[0] = NULL;
	m_LogFont.lfPitchAndFamily = 0;
	CClientDC dc(this);
	EnumFontFamiliesEx(dc.m_hDC, &m_LogFont, (FONTENUMPROC)EnumFontListProc, (LPARAM)&arrFontList, 0);
	for ( pos = arrFontList.GetHeadPosition(); pos != NULL; ){
		strFont = arrFontList.GetNext(pos);
		m_FontComBox.AddString(strFont);
	}
}

BOOL CFontDlg::ReadDefaultFontInfo(CFontItem &tItem)
{
	BOOL bRet = FALSE;
	HKEY hKey = NULL;
	LONG dwRet = 0;
	TCHAR *szValueName = NULL, *szData = NULL;
	DWORD cbMaxValueName = 0, cbMaxData = 0;
	DWORD cbValueName = 0, cbData = 0, nValueCount = 0;
	CString strSubKey = _T("Software\\Microsoft\\DevStudio\\6.0\\Format\\") + tItem.m_strWnd;
	dwRet = RegOpenKeyEx(HKEY_CURRENT_USER, strSubKey, 0, KEY_ALL_ACCESS, &hKey);
	if ( dwRet != ERROR_SUCCESS ){
		RegCloseKey(hKey);
		return FALSE;
	}
	dwRet = RegQueryInfoKey(hKey, NULL, NULL, NULL, NULL, NULL, NULL, &nValueCount,  &cbMaxValueName, &cbMaxData, NULL, NULL);
	if ( dwRet == ERROR_SUCCESS && nValueCount > 0 ){
		for ( DWORD dwIndex = 0; ; dwIndex++ ){
			cbValueName = cbMaxValueName + 1;
			cbData = cbMaxData + 1;
			szData = new TCHAR[cbData];
			szValueName = new TCHAR[cbValueName];
			ZeroMemory(szData, cbData+1);
			ZeroMemory(szValueName, cbValueName+1);
			dwRet = RegEnumValue(hKey, dwIndex, szValueName, &cbValueName, NULL, NULL, (LPBYTE)szData, &cbData);
			if ( dwRet == ERROR_SUCCESS ){
				if ( _tcscmp(_T("FontFace"), szValueName) == 0 ){
					tItem.m_strFont = szData;
				}
				if ( _tcscmp(_T("FontSize"), szValueName) == 0 ){
					tItem.m_strSize.Format(_T("%d"), *szData);
				}
			}else{
				goto __Error_End;
			}
		}
		bRet = TRUE;
	}
__Error_End:
	if ( szData ) {
		delete [] szData;
	}
	if ( szValueName ) {
		delete [] szValueName;
	}
	RegCloseKey(hKey);
	return bRet;
}
void CFontDlg::OnNMClickListctrl(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	int index = 0;
	if ( pNMItemActivate->iItem >= 0 ){
		CString strWnd, strFontFace, strFontSize;
		strWnd = m_FontListCtrl.GetItemText(pNMItemActivate->iItem, 0);
		strFontFace = m_FontListCtrl.GetItemText(pNMItemActivate->iItem, 1);
		strFontSize = m_FontListCtrl.GetItemText(pNMItemActivate->iItem, 2);

		index = m_WndComBox.FindString(0, strWnd);
		m_WndComBox.SetCurSel(index);
		index = m_FontComBox.FindString(0, strFontFace);
		m_FontComBox.SetCurSel(index);
		(index >= 0) ? (m_strFontName = strFontFace, strTextOut = _T("AaBbCcXxYyZz")) : (strTextOut.Empty());
		index = m_FontSizeComBox.FindString(0, strFontSize);
		m_FontSizeComBox.SetCurSel(index);
		(index >= 0) ? (m_strFontSize = strFontSize, strTextOut = _T("AaBbCcXxYyZz")) : (strTextOut.Empty());
	}else{
		m_WndComBox.SetCurSel(-1);
		m_FontComBox.SetCurSel(-1);
		m_FontSizeComBox.SetCurSel(-1);
		m_strFontName.Empty();
		m_strFontSize.Empty();
	}
	EnableWindow(IDC2_SET, FALSE);
	*pResult = 0;
}

void CFontDlg::OnCbnSelchangeSelwnd()
{
	BOOL bFind = FALSE;
	CString strText, strFName, strFSize;
	GetDlgItemText(IDC2_SELWND, strText);
	for ( int idx = 0; idx < m_FontListCtrl.GetItemCount(); idx++ ) {
		if ( m_FontListCtrl.GetItemText(idx, 0) == strText && m_FontListCtrl.GetItemText(idx, 1) != _T("(null)") ) {
			strFName = m_FontListCtrl.GetItemText(idx, 1);
			m_FontComBox.SetCurSel(m_FontComBox.FindString(-1, strFName));
			strFSize = m_FontListCtrl.GetItemText(idx, 2);
			m_FontSizeComBox.SetCurSel(m_FontSizeComBox.FindString(-1, strFSize));
			bFind = TRUE;
			break;
		}
	}
	bFind ? (strTextOut = _T("AaBbCcXxYyZz")) : (m_FontComBox.SetCurSel(-1), m_FontSizeComBox.SetCurSel(-1), strTextOut.Empty());
	EnableWindow(IDC2_SET);
}

void CFontDlg::OnCbnSelchangeSelfont()
{
	CString strText;
	GetDlgItemText(IDC2_SELFONT, m_strFontName);
	GetDlgItemText(IDC2_FONTSIZE, strText);
	if ( !strText.IsEmpty() ) {
		strTextOut = _T("AaBbCcXxYyZz");
	}
	EnableWindow(IDC2_SET);
}

void CFontDlg::OnCbnSelchangeFontsize()
{
	CString strText;
	GetDlgItemText(IDC2_FONTSIZE, m_strFontSize);
	GetDlgItemText(IDC2_SELFONT, strText);
	if ( !strText.IsEmpty() ) {
		strTextOut = _T("AaBbCcXxYyZz");
	}
	EnableWindow(IDC2_SET);
}

void CFontDlg::OnBnClickedSet()
{
	CString strText;
	CFontItem tItem;
	GetDlgItemText(IDC2_SELWND, tItem.m_strWnd);
	GetDlgItemText(IDC2_SELFONT, tItem.m_strFont);
	GetDlgItemText(IDC2_FONTSIZE, tItem.m_strSize);
	if ( tItem.m_strWnd.IsEmpty() || tItem.m_strFont.IsEmpty() || tItem.m_strSize.IsEmpty() ) {
		MessageBox(_T("信息填写不完整！"), _T("友情提示"), MB_OK | MB_ICONWARNING);
		return;
	}

	if ( ModRegFontKeyValue(tItem) ) {
		for ( int idx = 0; idx < m_FontListCtrl.GetItemCount(); idx++ ) {
			if ( m_FontListCtrl.GetItemText(idx, 0) == tItem.m_strWnd ) {
				m_FontListCtrl.SetItemText(idx, 1, tItem.m_strFont);
				m_FontListCtrl.SetItemText(idx, 2, tItem.m_strSize);
				break;
			}
		}
		MessageBox(_T("修改成功！"), _T("友情提示"), MB_OK|MB_ICONWARNING);
		EnableWindow(IDC2_SET, FALSE);
	}else{
		MessageBox(_T("修改失败！"), _T("友情提示"), MB_OK|MB_ICONERROR);
	}
}

BOOL CFontDlg::ModRegFontKeyValue(CFontItem tItem)
{
	BOOL bRet = FALSE;
	HKEY hKey = NULL;
	DWORD dwData = 0;
	dwData = _tstol(tItem.m_strSize);
	CString strSubKey = _T("Software\\Microsoft\\DevStudio\\6.0\\Format\\") + tItem.m_strWnd;
	DWORD dwRet = RegOpenKeyEx(HKEY_CURRENT_USER, strSubKey, 0, KEY_ALL_ACCESS, &hKey);
	if ( dwRet != ERROR_SUCCESS && dwRet != ERROR_FILE_NOT_FOUND ){
		goto __Error_End;
	}else if (dwRet == ERROR_FILE_NOT_FOUND &&
		MessageBox(_T("注册表键值不存在，你想要创建吗？"), _T("友情提示"), MB_OKCANCEL | MB_ICONQUESTION) == IDOK ){
			if ( RegCreateKey(HKEY_CURRENT_USER, strSubKey, &hKey) != ERROR_SUCCESS ) {
				goto __Error_End;
			}
	}
	dwRet = RegSetValueEx(hKey, _T("FontFace"), 0, REG_SZ, (LPBYTE)tItem.m_strFont.GetBuffer(), tItem.m_strFont.GetLength()*sizeof(TCHAR));
	tItem.m_strFont.ReleaseBuffer();
	if ( dwRet != ERROR_SUCCESS ){
		goto __Error_End;
	}
	dwRet = RegSetValueEx(hKey, _T("FontSize"), 0, REG_DWORD, (LPBYTE)&dwData, sizeof(dwData));
	if ( dwRet != ERROR_SUCCESS ){
		goto __Error_End;
	}
	bRet = TRUE;
__Error_End:
	RegCloseKey(hKey);
	return bRet;
}

CPoint CFontDlg::GetShowTextPos(HDC hDc, CRect tRect)
{
	CPoint rPt(0, 0);
	SIZE tSize = {0};
	CString strText = _T("AaBbCcXxYyZz");
	if ( GetTextExtentPoint32(hDc, strText, strText.GetLength(), &tSize) ) {
		if ( tSize.cx < tRect.Width() ) {
			rPt.x = (tRect.Width()-tSize.cx)/2;
		}
		if ( tSize.cy < tRect.Height() ) {
			rPt.y = (tRect.Height()-tSize.cy)/2;
		}
	}
	return rPt;
}

void CFontDlg::OnTimer(UINT_PTR nIDEvent)
{
	CPoint ptShow;
	CDC dcMemory;
	CBitmap mBitmap;
	m_pDc = (!m_pDc) ? (CDC::FromHandle(::GetDC(m_hExample))) : m_pDc;
	if ( !m_pDc ) return;
	if ( !dcMemory.CreateCompatibleDC(m_pDc) || !mBitmap.CreateCompatibleBitmap(m_pDc, m_ShowRect.Width(), m_ShowRect.Height()) || !dcMemory.SelectObject(&mBitmap) ) {
		goto __Error_End;
	}

	dcMemory.FillSolidRect(0, 0, m_ShowRect.Width(), m_ShowRect.Height(), m_bkColor);
	_tcscpy_s(mlFont.lfFaceName, LF_FACESIZE, m_strFontName);
	mlFont.lfHeight = -MulDiv(_tstoi(m_strFontSize), GetDeviceCaps(m_pDc->m_hDC, LOGPIXELSY), 72);
	if ( !mFont.CreateFontIndirect(&mlFont) || !dcMemory.SelectObject(mFont) ) {
		goto __Error_End;
	}
	ptShow = GetShowTextPos(dcMemory.m_hDC, CRect(0, 0, m_ShowRect.Width(), m_ShowRect.Height()));
	dcMemory.TextOut(ptShow.x, ptShow.y, strTextOut);
	m_pDc->BitBlt(0, 0, m_ShowRect.Width(), m_ShowRect.Height(), &dcMemory, 0, 0, SRCCOPY);

__Error_End:
	if ( mFont.m_hObject ) {
		mFont.DeleteObject();
	}
	if ( mBitmap.m_hObject ) {
		mBitmap.DeleteObject();
	}
	if ( dcMemory.m_hDC ) {
		dcMemory.DeleteDC();
	}
	CDialog::OnTimer(nIDEvent);
}