#pragma once


// CAdd �Ի���

class CAdd : public CDialogEx
{
	DECLARE_DYNAMIC(CAdd)

public:
	CAdd(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CAdd();

// �Ի�������
	enum { IDD = IDD_D_ADD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
