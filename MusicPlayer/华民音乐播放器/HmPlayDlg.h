
// HmPlayDlg.h : 头文件
//

#pragma once
#include "NewButton.h"
#include "afxwin.h"
#include "Mlist.h"
#include "afxcmn.h"
#include "Slider.h"
#include "stime.h"
#include "About.h"
#include "mmsys.h"
#include "Vslider.h"
#include "SetMusic.h"
#define WM_PLAYMUSIC WM_USER+8214
#define WM_NOTIFYICON WM_USER+8215
#define Save_Number 80000
// CHmPlayDlg 对话框
class CHmPlayDlg : public CDialogEx
{
// 构造
public:
	CHmPlayDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_MY_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	bool is_play_stop;
	CMlist *m_mlist;
	CFont m_font;
	M_ID id;
	wchar_t Path[MAX_PATH],Current_Path[MAX_PATH];
	mmsys dl;
	wchar_t bdata[128];
	int item,volume,m_count;
	CVslider *m_vslider;
	CImage image;
	int s_num[Save_Number];
	SetInfo sii;
	NOTIFYICONDATA nid;
public:
	void OpenMusic(wchar_t *path);
	void Init(void);
	void ReadInitInfo();
	void DrawTimeText(DWORD num);
	void DrawBText();
	void SaveInfo();
public:
	afx_msg void OnBnClickedBClose();
	afx_msg void OnBnClickedBMin();
	NewButton m_bclose;
	afx_msg LRESULT OnNcHitTest(CPoint point);
	NewButton m_bmin;
	NewButton m_bleft;
	NewButton m_bplay;
	NewButton m_bright;
	afx_msg void OnBnClickedBLeft();
	afx_msg void OnBnClickedBPlay();
	afx_msg void OnBnClickedBRight();
	afx_msg void OnBnClickedBMlist();
	afx_msg void OnClose();
	afx_msg void OnBnClickedBChose();
	NewButton m_bchose;
	NewButton m_blist;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	CSlider m_bslider;
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	CStime m_sb;
	CStime m_se;
	afx_msg void OnChoseAbout();
	afx_msg LRESULT PlayMusic(WPARAM wParam,LPARAM lParam);
	CStime m_sbt;
	afx_msg void OnMove(int x, int y);
	afx_msg LRESULT SetValue(WPARAM wParam,LPARAM lParam);
	afx_msg LRESULT SaveInfo(WPARAM wParam,LPARAM lParam);
	afx_msg LRESULT NotifyIcon(WPARAM wParam,LPARAM lParam);
	afx_msg void OnBnClickedBPlaytype();
	NewButton m_bplaytype;
	afx_msg void OnChoseSet();
	afx_msg void OnIconOpenplay();
	afx_msg void OnIconPlaylist();
	afx_msg void OnIconSet();
	afx_msg void OnIconAbout();
	afx_msg void OnIconExit();
	afx_msg void OnUpdatePlaytypeDanqu(CCmdUI *pCmdUI);
	afx_msg void OnInitMenuPopup(CMenu *pPopupMenu, UINT nIndex,BOOL bSysMenu);
	afx_msg void OnUpdatePlaytypeDanquxh(CCmdUI *pCmdUI);
	afx_msg void OnUpdatePlaytypeLbplay(CCmdUI *pCmdUI);
	afx_msg void OnUpdatePlaytypeLbxh(CCmdUI *pCmdUI);
	afx_msg void OnUpdatePlaytypeWrand(CCmdUI *pCmdUI);
	afx_msg void OnUpdatePlaytypeYrand(CCmdUI *pCmdUI);
	afx_msg void OnPlaytypeDanqu();
	afx_msg void OnPlaytypeDanquxh();
	afx_msg void OnPlaytypeLbplay();
	afx_msg void OnPlaytypeLbxh();
	afx_msg void OnPlaytypeWrand();
	afx_msg void OnPlaytypeYrand();
};
