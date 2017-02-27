// ColorDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Vc6Configer.h"
#include "ColorDlg.h"


// CColorDlg dialog

IMPLEMENT_DYNAMIC(CColorDlg, CDialog)

CColorDlg::CColorDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CColorDlg::IDD, pParent)
{
	ZeroMemory(&mlFont, sizeof(mlFont));
	_tcscpy_s(mlFont.lfFaceName, LF_FACESIZE, _T("Times New Roman"));
	mlFont.lfHeight = 30;
	mlFont.lfWidth = 8;
	strTextOut = _T("AaBbCcXxYyZz");
	m_bkColor = GetSysColor(COLOR_3DFACE);
	m_gFontRGB.SetColor(m_bkColor);
	m_gBkRGB.SetColor(m_bkColor);
	m_pDc = NULL;
}

CColorDlg::~CColorDlg()
{
}

void CColorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC3_COLORSHOW, m_ColorListCtrl);
	DDX_Control(pDX, IDC3_SELWND, m_WndComBox);
}


BEGIN_MESSAGE_MAP(CColorDlg, CDialog)
	ON_NOTIFY(NM_CLICK, IDC3_COLORSHOW, &CColorDlg::OnNMClickColorshow)
	ON_WM_TIMER()
	ON_CBN_SELCHANGE(IDC3_SELWND, &CColorDlg::OnCbnSelchangeSelwnd)
	ON_BN_CLICKED(IDC3_CUS_FONTCOLOR, &CColorDlg::OnBnClickedCusFontcolor)
	ON_BN_CLICKED(IDC3_CUS_BGCOLOR, &CColorDlg::OnBnClickedCusBgcolor)
	ON_BN_CLICKED(IDC3_MODCOLOR, &CColorDlg::OnBnClickedModcolor)
END_MESSAGE_MAP()


// CColorDlg message handlers

BOOL CColorDlg::EnableWindow(UINT uID, BOOL bEnable)
{
	return ::EnableWindow(GetDlgItem(uID)->m_hWnd, bEnable);
}

BOOL CColorDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	EnableWindow(IDC3_MODCOLOR, FALSE);
	int idx = 0, index = 0;
	m_ColorListCtrl.SetExtendedStyle( m_ColorListCtrl.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES );
	m_ColorListCtrl.InsertColumn(0, _T("窗口名称"), 0, 120);
	m_ColorListCtrl.InsertColumn(1, _T("字体颜色"), 0, 100);
	m_ColorListCtrl.InsertColumn(2, _T("背景颜色"), 0, 70);

	::GetWindowRect(GetDlgItem(IDC3_SHOW_EXAMPLE)->GetSafeHwnd(), &m_ShowRect);
	ScreenToClient(&m_ShowRect);
	m_ShowRect.top += 2; m_ShowRect.bottom += 2; m_ShowRect.left += 2; m_ShowRect.right += 2;

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
		CColorItem tItem;
		tItem.m_strWnd = szWnd[idx];
		ReadDefaultColorInfo(tItem);
		m_WndComBox.InsertString(idx, szWnd[idx]);
		m_ColorListCtrl.InsertItem(idx, _T(""));
		m_ColorListCtrl.SetItemText(idx, 0, szWnd[idx]);
		ShowColorInfo(tItem);
	}

	SetTimer(0, 100, NULL);
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CColorDlg::ReadDefaultColorInfo(CColorItem &tItem)
{
	BOOL bRet = FALSE;
	LONG dwRet = 0;
	HKEY hKey = NULL;
	DWORD cbValueName = 0, cbData = 0, nValueCount = 0;
	DWORD cbMaxValueName = 0, cbMaxData = 0;
	LPBYTE szData = NULL;
	TCHAR *szValueName = NULL;
	CString strSubKey = _T("Software\\Microsoft\\DevStudio\\6.0\\Format\\") + tItem.m_strWnd;
	dwRet = RegOpenKeyEx(HKEY_CURRENT_USER, strSubKey, 0, KEY_ALL_ACCESS, &hKey);
	if ( dwRet != ERROR_SUCCESS ){
		goto __Error_End;
	}
	dwRet = RegQueryInfoKey(hKey, NULL, NULL, NULL, NULL, NULL, NULL, &nValueCount,  &cbMaxValueName, &cbMaxData, NULL, NULL);
	if ( dwRet == ERROR_SUCCESS && nValueCount > 0 ){
		for ( DWORD dwIndex = 0; ; dwIndex++ ){
			cbValueName = cbMaxValueName + 1;
			cbData = cbMaxData + 1;
			szData = new BYTE[cbData];
			szValueName = new TCHAR[cbValueName];
			ZeroMemory(szData, cbData);
			ZeroMemory(szValueName, cbValueName+1);
			dwRet = RegEnumValue(hKey, dwIndex, szValueName, &cbValueName, NULL, NULL, szData, &cbData);
			if ( dwRet == ERROR_SUCCESS ){
				if ( _tcscmp(_T("Text"), szValueName) == 0 ){
					tItem.m_bExist = TRUE;
					tItem.m_FontColor.SetColor(szData[0], szData[1], szData[2]);
					tItem.m_BgColor.SetColor(szData[4], szData[5], szData[6]);
					break;
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

void CColorDlg::ShowColorInfo(CColorItem &tItem)
{
	for ( int idx = 0; idx < m_ColorListCtrl.GetItemCount(); idx++ ) {
		if ( m_ColorListCtrl.GetItemText(idx, 0) == tItem.m_strWnd ) {
			if ( tItem.m_bExist ) {
				m_ColorListCtrl.SetItemBkColor(idx, 1, tItem.m_FontColor.GetColor());
				m_ColorListCtrl.SetItemBkColor(idx, 2, tItem.m_BgColor.GetColor());
			}else{
				m_ColorListCtrl.SetItemText(idx, 1, _T("(null)"));
				m_ColorListCtrl.SetItemText(idx, 2, _T("(null)"));
			}
			break;
		}
	}
}
void CColorDlg::OnNMClickColorshow(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	int index = 0;
	CString strText = m_ColorListCtrl.GetItemText(pNMItemActivate->iItem, 1);
	if ( pNMItemActivate->iItem >= 0 ){
		m_WndComBox.SetCurSel(m_WndComBox.FindString(0, m_ColorListCtrl.GetItemText(pNMItemActivate->iItem, 0)));
		if ( strText != _T("(null)") ) {
			m_gFontRGB.SetColor(m_ColorListCtrl.GetItemBkColor(pNMItemActivate->iItem, 1));
			m_gBkRGB.SetColor(m_ColorListCtrl.GetItemBkColor(pNMItemActivate->iItem, 2));
		}else{
			m_gFontRGB.SetColor(m_bkColor);
			m_gBkRGB.SetColor(m_bkColor);
		}
	}else{
		m_gFontRGB.SetColor(m_bkColor);
		m_gBkRGB.SetColor(m_bkColor);
		m_WndComBox.SetCurSel(-1);
	}
	*pResult = 0;
}

void CColorDlg::OnTimer(UINT_PTR nIDEvent)
{
	CDC dcMemory;
	CBitmap mBitmap;
	m_pDc = ( !m_pDc ) ? GetDC() : m_pDc;
	if ( !m_pDc ) return;
	if ( !dcMemory.CreateCompatibleDC(m_pDc) || !mBitmap.CreateCompatibleBitmap(m_pDc, 162, 36) || !dcMemory.SelectObject(&mBitmap) ) {
		goto __Error_End;
	}
	dcMemory.FillSolidRect(0, 0, 162, 36, m_gBkRGB.GetColor());
	if ( !mFont.CreateFontIndirect(&mlFont) || !dcMemory.SelectObject(mFont) ) {
		goto __Error_End;
	}
	dcMemory.SetTextColor(m_gFontRGB.GetColor());
	dcMemory.SetBkMode(TRANSPARENT);
	dcMemory.TextOut(14, 2, strTextOut);
	m_pDc->BitBlt(m_ShowRect.left, m_ShowRect.top, m_ShowRect.Width(), m_ShowRect.Height(), &dcMemory, 0, 0, SRCCOPY);

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

void CColorDlg::OnCbnSelchangeSelwnd()
{
	CString strText;
	BOOL bRet = FALSE;
	GetDlgItemText(IDC3_SELWND, strText);
	for ( int idx = 0; idx < m_ColorListCtrl.GetItemCount(); idx++ ) {
		if ( m_ColorListCtrl.GetItemText(idx, 0) == strText && m_ColorListCtrl.GetItemText(idx, 1) != _T("(null)") ) {
			m_gFontRGB.SetColor(m_ColorListCtrl.GetItemBkColor(idx, 1));
			m_gBkRGB.SetColor(m_ColorListCtrl.GetItemBkColor(idx, 2));
			bRet = TRUE;
			break;
		}
	}
	if ( !bRet ) {
		m_gFontRGB.SetColor(m_bkColor);
		m_gBkRGB.SetColor(m_bkColor);
	}
}

void CColorDlg::OnBnClickedCusFontcolor()
{
	if ( m_WndComBox.GetCurSel() != -1 ){
		CColorDialog dlg(m_gFontRGB.GetColor(), CC_FULLOPEN);
		if ( dlg.DoModal() == IDOK ){
			COLORREF cRef= dlg.GetColor();
			m_gFontRGB.SetColor(GetRValue(cRef), GetGValue(cRef), GetBValue(cRef));
			EnableWindow(IDC3_MODCOLOR);
		}
	}else{
		MessageBox(_T("请先选择要修改的窗口！"), _T("文字色"), MB_OK|MB_ICONWARNING);
	}
}

void CColorDlg::OnBnClickedCusBgcolor()
{
	if ( m_WndComBox.GetCurSel() != -1 ){
		CColorDialog dlg(m_gBkRGB.GetColor(), CC_FULLOPEN);
		if ( dlg.DoModal() == IDOK ){
			COLORREF cRef= dlg.GetColor();
			m_gBkRGB.SetColor(GetRValue(cRef), GetGValue(cRef), GetBValue(cRef));
			EnableWindow(IDC3_MODCOLOR);
		}
	}else{
		MessageBox(_T("请先选择要修改的窗口！"), _T("背景色"), MB_OK|MB_ICONWARNING);
	}
}

BOOL CColorDlg::ModRegFontAndBgColor(CColorItem &tItem)
{
	BOOL bRet = FALSE;
	HKEY hKey = NULL;
	LONG dwRet = 0;
	BYTE szData[12] = {0};
	szData[0] = tItem.m_FontColor.m_iRValue;
	szData[1] = tItem.m_FontColor.m_iGValue;
	szData[2] = tItem.m_FontColor.m_iBValue;

	szData[4] = tItem.m_BgColor.m_iRValue;
	szData[5] = tItem.m_BgColor.m_iGValue;
	szData[6] = tItem.m_BgColor.m_iBValue;

	CString strSubKey = _T("Software\\Microsoft\\DevStudio\\6.0\\Format\\") + tItem.m_strWnd;
	dwRet = RegOpenKeyEx(HKEY_CURRENT_USER, strSubKey, 0, KEY_ALL_ACCESS, &hKey);
	if ( dwRet != ERROR_SUCCESS && dwRet != ERROR_FILE_NOT_FOUND ){
		goto __Error_End;
	}else if (dwRet == ERROR_FILE_NOT_FOUND &&
		MessageBox(_T("注册表键值不存在，你想要创建吗？"), _T("友情提示"), MB_OKCANCEL | MB_ICONQUESTION) == IDOK ){
			if ( RegCreateKey(HKEY_CURRENT_USER, strSubKey, &hKey) != ERROR_SUCCESS ) {
				goto __Error_End;
			}
	}
	dwRet = RegSetValueEx(hKey, _T("Text"), 0, REG_BINARY, szData, 12);
	if ( dwRet != ERROR_SUCCESS ){
		goto __Error_End;
	}
	bRet = TRUE;
__Error_End:
	RegCloseKey(hKey);
	return bRet;
}

void CColorDlg::OnBnClickedModcolor()
{
	CColorItem tItem;
	GetDlgItemText(IDC3_SELWND, tItem.m_strWnd);
	tItem.m_FontColor.SetColor(m_gFontRGB.GetColor());
	tItem.m_BgColor.SetColor(m_gBkRGB.GetColor());
	if ( ModRegFontAndBgColor(tItem) ) {
		for ( int idx = 0; idx < m_ColorListCtrl.GetItemCount(); idx++ ) {
			if ( m_ColorListCtrl.GetItemText(idx, 0) == tItem.m_strWnd ) {
				m_ColorListCtrl.SetItemText(idx, 1, _T(""));
				m_ColorListCtrl.SetItemText(idx, 2, _T(""));
				m_ColorListCtrl.SetItemBkColor(idx, 1, m_gFontRGB.GetColor());
				m_ColorListCtrl.SetItemBkColor(idx, 2, m_gBkRGB.GetColor());
				break;
			}
		}
		MessageBox(_T("修改成功！"), _T("友情提示"), MB_OK|MB_ICONWARNING);
		EnableWindow(IDC3_MODCOLOR, FALSE);
	}else{
		MessageBox(_T("修改失败！"), _T("友情提示"), MB_OK|MB_ICONERROR);
	}
}
