#include "stdafx.h"
#include "mmsys.h"


mmsys::mmsys(void)
{
}


mmsys::~mmsys(void)
{
}

BOOL mmsys::LoadImageFromResource(UINT m_ID,LPCTSTR lpstr,CImage *image)
{
	HMODULE hm=AfxGetResourceHandle();
	HRSRC hr=::FindResource(hm,MAKEINTRESOURCE(m_ID),lpstr);
	if(!hr)
		return false;
	if(!image->IsNull())
		image->Destroy();
	HGLOBAL hg=::LoadResource(hm,hr);
	if(hg==NULL)
		return false;
	LPVOID lpvoid=::LockResource(hg);
	DWORD dwsize=::SizeofResource(hm,hr);
	HGLOBAL hnew=::GlobalAlloc(GHND,dwsize);
	LPBYTE lpbyte=(LPBYTE)::GlobalLock(hnew);
	memcpy(lpbyte,lpvoid,dwsize);
	GlobalUnlock(hnew);
	LPSTREAM lpstream=NULL;
	HRESULT m_hr=::CreateStreamOnHGlobal(hnew,true,&lpstream);
	if(m_hr!=S_OK)
	{
		FreeResource(hg);
		GlobalFree(hnew);
	}
	image->Load(lpstream);
	FreeResource(hg);
	GlobalFree(hnew);
	if(image->GetBPP()==32)
	{
		int x,y;
		for(x=0;x<image->GetWidth();x++)
			for(y=0;y<image->GetHeight();y++)
			{
				byte *by=(byte*)image->GetPixelAddress(x,y);
				by[0]=by[0]*by[3]/255;
				by[1]=by[1]*by[3]/255;
				by[2]=by[2]*by[3]/255;
			}
	}
	return true;
}