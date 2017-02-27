#pragma once


// CAddList 对话框

class CAddList : public CDialogEx
{
	DECLARE_DYNAMIC(CAddList)

public:
	CAddList(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CAddList();

// 对话框数据
	enum { IDD = IDD_DIALOG2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg LRESULT OnNcHitTest(CPoint point);
	afx_msg void OnPaint();
};
