
// Vc6Configer.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "Vc6Configer.h"
#include "Vc6ConfigerDlg.h"
#include "CWebBrowser.h"
#include "CWebBrowser2.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CVc6ConfigerApp

BEGIN_MESSAGE_MAP(CVc6ConfigerApp, CWinAppEx)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CVc6ConfigerApp ����

CVc6ConfigerApp::CVc6ConfigerApp()
{
	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CVc6ConfigerApp ����

CVc6ConfigerApp theApp;


// CVc6ConfigerApp ��ʼ��

BOOL CVc6ConfigerApp::InitInstance()
{
	BOOL bFound = FALSE;
	HANDLE hMutex = CreateMutex(NULL, TRUE, _T("Vc6Configer"));
	if ( GetLastError() == ERROR_ALREADY_EXISTS ){
		bFound = TRUE;
	}
	if ( hMutex != NULL ){
		ReleaseMutex(hMutex);
	}
	if ( bFound == TRUE ){
		HWND hWnd = FindAppWnd();
		if ( hWnd ){
			::ShowWindow(hWnd, SW_SHOWNA);
			::ShowWindow(hWnd, SW_RESTORE);
			SetForegroundWindow(hWnd);
		}
		return FALSE;
	}

	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControlsEx()�����򣬽��޷��������ڡ�
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ��������Ϊ��������Ҫ��Ӧ�ó�����ʹ�õ�
	// �����ؼ��ࡣ
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinAppEx::InitInstance();

	AfxEnableControlContainer();

	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));

	CVc6ConfigerDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: �ڴ˷��ô����ʱ��
		//  ��ȷ�������رնԻ���Ĵ���
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: �ڴ˷��ô����ʱ��
		//  ��ȡ�������رնԻ���Ĵ���
	}

	// ���ڶԻ����ѹرգ����Խ����� FALSE �Ա��˳�Ӧ�ó���
	//  ����������Ӧ�ó������Ϣ�á�
	return FALSE;
}

BOOL CVc6ConfigerApp::CheckProcessExist(CString strName, DWORD *pPID)
{
	BOOL bExist = FALSE;
	HANDLE handle = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0);
	PROCESSENTRY32 info = {0};
	info.dwSize = sizeof(PROCESSENTRY32);
	BOOL bRet = Process32First(handle, &info);
	if( bRet ){
		do {
			if ( strName.Compare(info.szExeFile) == 0 ){
				if (pPID != NULL){
					*pPID = info.th32ProcessID;
				}
				bExist = TRUE;
				break;
			}
			bRet = Process32Next(handle, &info);
		} while( bRet );
		CloseHandle(handle);
	}
	return bExist;
}

BOOL CALLBACK EnumWndProc( HWND hwnd, LPARAM lParam )
{
	TCHAR szTitle[_MAX_PATH] = {0};
	CProgWnd *pItem = (CProgWnd *)lParam;
	HANDLE hProp = GetProp(hwnd, _T("Vc6Configer_Prop"));
	if ( hProp ) {
		LONG LProp = (LONG)hProp;
		GetWindowText(hwnd, szTitle, _MAX_PATH);
		CString str(szTitle);
		if( LProp == DIY_PROP_CODE && !(str.IsEmpty()) && str.Find(pItem->strTitle) != -1) {
			pItem->hWnd = hwnd;
			SetLastError(DIY_ERROR_CODE);
			return FALSE;
		}
	}
	return TRUE;
}

HWND CVc6ConfigerApp::FindAppWnd()
{
	HWND hWnd = NULL;
	UINT iProcessID = 0;
	BOOL bRet = FALSE;
	CProgWnd mItem;
	mItem.hWnd = NULL;
	mItem.strTitle = _T("Visual C++ 6.0 �������ù���");
	bRet = EnumWindows(EnumWndProc, (LPARAM)&mItem);
	if ( !bRet && GetLastError() == DIY_ERROR_CODE && mItem.hWnd != NULL ){
		hWnd = mItem.hWnd;
	}
	return hWnd;
}