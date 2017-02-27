// AddList.cpp : 实现文件
//

#include "stdafx.h"
#include "华民音乐播放器.h"
#include "AddList.h"
#include "afxdialogex.h"


// CAddList 对话框

IMPLEMENT_DYNAMIC(CAddList, CDialogEx)

CAddList::CAddList(CWnd* pParent /*=NULL*/)
	: CDialogEx(CAddList::IDD, pParent)
{

}

CAddList::~CAddList()
{
}

void CAddList::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CAddList, CDialogEx)
	ON_WM_NCHITTEST()
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CAddList 消息处理程序


BOOL CAddList::OnInitDialog()
{
	CDialogEx::OnInitDialog();


	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


BOOL CAddList::PreTranslateMessage(MSG* pMsg)
{

	return CDialogEx::PreTranslateMessage(pMsg);
}


LRESULT CAddList::OnNcHitTest(CPoint point)
{
	CRect rect;
	GetClientRect(&rect);
	ClientToScreen(&rect);
	return rect.PtInRect(point)?HTCAPTION:CDialogEx::OnNcHitTest(point);
}


void CAddList::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	
}
