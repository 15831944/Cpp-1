#pragma once


// CAddList �Ի���

class CAddList : public CDialogEx
{
	DECLARE_DYNAMIC(CAddList)

public:
	CAddList(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CAddList();

// �Ի�������
	enum { IDD = IDD_DIALOG2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg LRESULT OnNcHitTest(CPoint point);
	afx_msg void OnPaint();
};
