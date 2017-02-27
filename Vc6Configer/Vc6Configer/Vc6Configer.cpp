
// Vc6Configer.cpp : 定义应用程序的类行为。
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


// CVc6ConfigerApp 构造

CVc6ConfigerApp::CVc6ConfigerApp()
{
	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}


// 唯一的一个 CVc6ConfigerApp 对象

CVc6ConfigerApp theApp;


// CVc6ConfigerApp 初始化

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

	// 如果一个运行在 Windows XP 上的应用程序清单指定要
	// 使用 ComCtl32.dll 版本 6 或更高版本来启用可视化方式，
	//则需要 InitCommonControlsEx()。否则，将无法创建窗口。
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// 将它设置为包括所有要在应用程序中使用的
	// 公共控件类。
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinAppEx::InitInstance();

	AfxEnableControlContainer();

	// 标准初始化
	// 如果未使用这些功能并希望减小
	// 最终可执行文件的大小，则应移除下列
	// 不需要的特定初始化例程
	// 更改用于存储设置的注册表项
	// TODO: 应适当修改该字符串，
	// 例如修改为公司或组织名
	SetRegistryKey(_T("应用程序向导生成的本地应用程序"));

	CVc6ConfigerDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: 在此放置处理何时用
		//  “确定”来关闭对话框的代码
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: 在此放置处理何时用
		//  “取消”来关闭对话框的代码
	}

	// 由于对话框已关闭，所以将返回 FALSE 以便退出应用程序，
	//  而不是启动应用程序的消息泵。
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
	mItem.strTitle = _T("Visual C++ 6.0 辅助配置工具");
	bRet = EnumWindows(EnumWndProc, (LPARAM)&mItem);
	if ( !bRet && GetLastError() == DIY_ERROR_CODE && mItem.hWnd != NULL ){
		hWnd = mItem.hWnd;
	}
	return hWnd;
}