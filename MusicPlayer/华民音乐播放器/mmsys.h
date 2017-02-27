#pragma once
class mmsys
{
public:
	mmsys(void);
	~mmsys(void);
public:
	BOOL LoadImageFromResource(UINT m_ID,LPCTSTR lpstr,CImage *image);
};

