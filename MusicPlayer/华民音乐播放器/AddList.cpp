// AddList.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "�������ֲ�����.h"
#include "AddList.h"
#include "afxdialogex.h"


// CAddList �Ի���

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


// CAddList ��Ϣ�������


BOOL CAddList::OnInitDialog()
{
	CDialogEx::OnInitDialog();


	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
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
