#pragma once
#include "NewButton.h"
#include "OList.h"
#include "LoadFile.h"
#include "Minfo.h"
#include "PlayList.h"

// CMlist 对话框
#define LM_MOVE WM_USER+520
#define LM_LBDOWN WM_USER+521
#define LM_RBUP WM_USER+522
#define LM_LBDB WM_USER+523
#define WM_CHECKLIST WM_USER+1314
#define WM_PLAYMUSIC WM_USER+8214
#define WM_ADDSTRING WM_USER+8888
struct Save_Info
{
	char Name[128];
	char Path[MAX_PATH];
	char Time[52];
	char Album[128];
};
class CMlist : public CDialogEx
{
	DECLARE_DYNAMIC(CMlist)

public:
	CMlist(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CMlist();

// 对话框数据
	enum { IDD = IDD_D_LIST };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	COList *m_olist;
	CPlayList *m_plist;
	bool ismove;
	CFont m_font;
	wchar_t Current_Path[MAX_PATH];
	UINT Play_Type;
	int item;
	int menu_num[6];
	CImage image;
public:
	BOOL CheckListReturn(wchar_t *wn,wchar_t *wp);
	BOOL SaveMusciToFile(wchar_t *name,wchar_t *path,wchar_t *wtime,wchar_t *album);
	void ReadMusicListFromFile(wchar_t *fname);
	BOOL CheckFile(wchar_t *path);
	BOOL ChangeFile(wchar_t *name);
	void WriteIni();
	void ReadIni();
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	NewButton m_bclose;
	afx_msg void OnBnClickedBClose();
	afx_msg LRESULT OnNcHitTest(CPoint point);
	afx_msg void OnMove(int x, int y);
	afx_msg LRESULT CheckList(WPARAM wParam,LPARAM lParam);
	afx_msg void OnClose();
	afx_msg void OnBnClickedBMove();
	afx_msg void OnBnClickedBChosetype();
	NewButton m_bchose;
	afx_msg void OnAddAddfile();
	afx_msg void OnAddAdddirectory();
	afx_msg LRESULT OnAddString(WPARAM wParam,LPARAM lParam);
	afx_msg void OnMlPlay();
	afx_msg void OnMlistOpenfile();
	afx_msg void OnMlistLoadinfo();
	afx_msg void OnMlistDel();
	afx_msg void OnMlistDelall();
	afx_msg void OnMlistMovelist();
	afx_msg void OnMlistDelalllist();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnPlaytypeDanqu();
	afx_msg void OnPlaytypeDanquxh();
	afx_msg void OnPlaytypeLbplay();
	afx_msg void OnPlaytypeLbxh();
	afx_msg void OnPlaytypeWrand();
	afx_msg void OnPlaytypeYrand();
	afx_msg void OnBnClickedBFindsel();
	afx_msg void OnBnClickedBPtyle();
	afx_msg void OnUpdatePlaytypeDanqu(CCmdUI *pCmdUI);
	afx_msg void OnUpdatePlaytypeDanquxh(CCmdUI *pCmdUI);
	afx_msg void OnUpdatePlaytypeLbplay(CCmdUI *pCmdUI);
	afx_msg void OnUpdatePlaytypeLbxh(CCmdUI *pCmdUI);
	afx_msg void OnUpdatePlaytypeWrand(CCmdUI *pCmdUI);
	afx_msg void OnUpdatePlaytypeYrand(CCmdUI *pCmdUI);
	afx_msg void OnInitMenuPopup(CMenu* pPopupMenu, UINT nIndex, BOOL bSysMenu);
	NewButton m_btype;
};
