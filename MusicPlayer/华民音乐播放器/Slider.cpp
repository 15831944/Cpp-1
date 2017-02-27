// Slider.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "�������ֲ�����.h"
#include "Slider.h"


// CSlider

IMPLEMENT_DYNAMIC(CSlider, CSliderCtrl)

CSlider::CSlider()
{

}

CSlider::~CSlider()
{
}


BEGIN_MESSAGE_MAP(CSlider, CSliderCtrl)
	ON_WM_PAINT()
	ON_WM_SETCURSOR()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()



// CSlider ��Ϣ�������




void CSlider::PreSubclassWindow()
{
	// TODO: �ڴ����ר�ô����/����û���
	x=0;
	CSliderCtrl::PreSubclassWindow();
}


void CSlider::OnPaint()
{
	CPaintDC pdc(this); // device context for painting
	CRect rect;
	GetClientRect(&rect);
	CBitmap map,*oldmap;
	CDC dc;
	dc.CreateCompatibleDC(&pdc);
	map.CreateCompatibleBitmap(&pdc,rect.right,rect.bottom);
	oldmap=dc.SelectObject(&map);
	pdc.SetStretchBltMode(SBM_ENABLE_ARROWS);
	dc.SetStretchBltMode(SBM_ENABLE_ARROWS);
	dc.BitBlt(0,0,rect.right,rect.bottom,&m_dcBk,0,0,SRCCOPY);
	CRect drect;
	this->GetChannelRect(&drect);
	dc.FillSolidRect(drect,RGB(255,234,243));
	this->GetThumbRect(&drect);
	dc.FillSolidRect(drect,RGB(255,123,134));
	pdc.BitBlt(0,0,rect.right,rect.bottom,&dc,0,0,SRCCOPY);
	dc.DeleteDC();
	pdc.SelectObject(oldmap);
}


BOOL CSlider::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	::SetCursor(AfxGetApp()->LoadCursorW(IDC_CUR1));
	return true;//CSliderCtrl::OnSetCursor(pWnd, nHitTest, message);
}


BOOL CSlider::OnEraseBkgnd(CDC* pDC)
{
	CClientDC clientDC(GetParent());///�õ�����DC 
    CRect crect;
    CRect wrect;
    GetClientRect(crect);//�õ�DC��ͼ��С
    GetWindowRect(wrect);//�õ����ڴ�С
    GetParent()->ScreenToClient(wrect);//ת������
    if(m_dcBk.m_hDC==NULL)
	{
			CBitmap m_bmpBk,*m_bmpBkOld;
               m_dcBk.CreateCompatibleDC(&clientDC);//��������DC  
               m_bmpBk.CreateCompatibleBitmap(&clientDC, crect.Width(), crect.Height());//��������λͼ
               m_bmpBkOld = m_dcBk.SelectObject(&m_bmpBk);///��λͼѡ��DC
               m_dcBk.BitBlt(0, 0, crect.Width(), crect.Height(), &clientDC, wrect.left, wrect.top, SRCCOPY);
			   m_bmpBk.DeleteObject();
			m_bmpBkOld->DeleteObject();
	}
	return true;//CButton::OnEraseBkgnd(pDC);
}
