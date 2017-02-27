
#pragma once

class CIncItem {
public:
	enum {
		_Executable_Files = 1,
		_Include_Files,
		_Library_Files,
		_Source_Files,
	};
	DWORD m_dwFileIndex;
	CStringArray m_strArrFolder;
	CIncItem(){
		m_dwFileIndex = -1;
	}
};

#define  Executable_Files CIncItem::_Executable_Files
#define  Include_Files CIncItem::_Include_Files
#define  Library_Files CIncItem::_Library_Files
#define  Source_Files CIncItem::_Source_Files

class CFontItem {
public:
	CString m_strWnd;
	CString m_strFont;
	CString m_strSize;
	BOOL m_bModify;
	CFontItem() {
		m_strFont = _T("(null)");
		m_strSize = _T("(null)");
		m_bModify = FALSE;
	}
};

class CRgb {
public:
	UINT m_iRValue;
	UINT m_iGValue;
	UINT m_iBValue;
	CRgb() {
		m_iRValue = 0;
		m_iGValue = 0;
		m_iBValue = 0;
	}
	void SetColor(UINT iRcolor, UINT iGcolor, UINT iBcolor) {
		m_iRValue = iRcolor;
		m_iGValue = iGcolor;
		m_iBValue = iBcolor;
	};
	void SetColor(COLORREF colorREF) {
		m_iRValue = GetRValue(colorREF);
		m_iGValue = GetGValue(colorREF);
		m_iBValue = GetBValue(colorREF);
	};
	COLORREF GetColor() {
		return RGB(m_iRValue, m_iGValue, m_iBValue);
	};
};

class CColorItem {
public:
	CString m_strWnd;
	CRgb m_FontColor;
	CRgb m_BgColor;
	BOOL m_bExist;
	CColorItem() {
		m_bExist = FALSE;
	}
};

#define DIY_ERROR_CODE 95270
#define DIY_PROP_CODE 9527

class CProgWnd {
public:
	HWND hWnd;
	UINT iProcessID;
	CString strTitle;
	CProgWnd() {
		hWnd = NULL;
		iProcessID = -1;
	}
};