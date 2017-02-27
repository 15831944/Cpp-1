#pragma once

#include "OSlider.h"

struct TextLink
{
	DWORD num;
	wchar_t Name[128];
	wchar_t Path[MAX_PATH];
	wchar_t Time[52];
	wchar_t Data[128];
	TextLink *link;
};
#define WM_NUMBER WM_USER+8888
#define LM_MOVE WM_USER+520
#define LM_LBDOWN WM_USER+521
#define LM_RBUP WM_USER+522
#define LM_LBDB WM_USER+523
#define WM_CHECKLIST WM_USER+1314
#define WM_MOUSEHD WM_USER+1315
// COList 对话框
class COList : public CDialogEx
{
	DECLARE_DYNAMIC(COList)

public:
	COList(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~COList();

// 对话框数据
	enum { IDD = IDD_D_OLIST };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	int bnum,znum;
	bool ismove;
	COSlider *pslider;
	TextLink *phead,*pnew,*prear;
	DWORD m_move,m_lb;
	int m_Height,m_fnum;
	CFont m_font;
	CRect m_rect;
public:
	void DrawTextList();
	BOOL InsertText(wchar_t *name,wchar_t *path,wchar_t *time,wchar_t *data);
	BOOL DeleteText(DWORD num);
	BOOL DeleteAllText();
	BOOL GetListText(int sel,int list,wchar_t *data);
	void SetHeight(int Height);
	DWORD GetListNum();
	DWORD CheckPoint(UINT type,POINT point);
	DWORD SelectText(int sel);
	void SetSliderToListEnd();
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnMove(int x, int y);
	afx_msg void OnPaint();
	afx_msg LRESULT OnNumber(WPARAM wParam,LPARAM lParam);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnClose();
	afx_msg LRESULT MouseHd(WPARAM wParam,LPARAM lParam);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
