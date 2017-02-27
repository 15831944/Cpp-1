#pragma once


// CAdd 对话框

class CAdd : public CDialogEx
{
	DECLARE_DYNAMIC(CAdd)

public:
	CAdd(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CAdd();

// 对话框数据
	enum { IDD = IDD_D_ADD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
