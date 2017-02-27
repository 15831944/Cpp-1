#pragma once
#include "NewButton.h"
#include "mmsys.h"
#include "AddList.h"
// CPlayList �Ի���
struct Play_ListItem
{
	wchar_t Name[52];
	int AllNumber;
	int num;
	Play_ListItem *link;
};
class CPlayList : public CDialogEx
{
	DECLARE_DYNAMIC(CPlayList)

public:
	CPlayList(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CPlayList();

// �Ի�������
	enum { IDD = IDD_D_PLAYLIST };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CFont m_font,m_lf;
public:
	void DrawH();
	BOOL InserList(wchar_t *name);
public:
	int znum;
	Play_ListItem *phead,*pnew,*prear;
	CImage image;
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg LRESULT OnNcHitTest(CPoint point);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnBnClickedBClose();
	NewButton m_bclose;
	afx_msg void OnBnClickedBAdd();
	afx_msg void OnClose();
};
