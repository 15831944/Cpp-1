/*     ********************************MciPlay函数*********************************
       ****************************邮箱:cheng8214@163.com*****************************
       ********************************风、残痕***********************************
       ********************************有些待测***************************************
*/
#ifndef _MCIPLAY_H_
#define _MCIPLAY_H_

#ifndef WINVER
#define WINVER 0x0500
#endif /* WINVER */
#include <stdio.h>
#include <windows.h>
#define M_ID UINT
#ifdef __cplusplus
extern "C" {
#endif

#define WINAPI      __stdcall
struct M_TIME
{
	DWORD h1;
	DWORD h2;
};

typedef struct tagMusic_Info 
{
	char tag[3];
	char Title[30];
	char Artist[30];
	char Album[30];
	char Year[4];
	char Comment[28];
	unsigned char reserved;  //保留位，1个字节 
	unsigned char reserved2; //保留位，1个字节 
	unsigned char reserved3;
}Music_Info;


M_ID CHOpenMusic(char *Path);
BOOL CHPlayMusic(M_ID id);
BOOL CHStopMusic(M_ID id);
BOOL CHPauseMusic(M_ID id);
BOOL CHCloseMusic(M_ID id);
BOOL CHSeekMusic(M_ID id,DWORD dw);

DWORD CHGetMusicTime(M_ID id);
DWORD CHGetMusicPosition(M_ID id);

BOOL CHSetVolume(M_ID id,int num);
BOOL CHNumToTime(DWORD Length,M_TIME *ti);

BOOL CHGetMusicInfo(char *Path,Music_Info *m_info);
BOOL CHResumeMusic(M_ID id);
BOOL CHGetTimeFromFile(char *Path);
#ifdef __cplusplus
}
#endif
#endif