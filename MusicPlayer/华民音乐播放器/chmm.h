/*     ********************************���ú����ķ�װ*********************************
       ****************************����:cheng8214@163.com*****************************
       ********************************�硢�к�***********************************
       ********************************��Щ����***************************************
*/
#ifndef _CHMM_H_
#define _CHMM_H_

#ifndef WINVER
#define WINVER 0x0500
#endif /* WINVER */
#include <STDIO.H>
#include <windows.h>
#define M_ID UINT
#ifdef __cplusplus
extern "C" {
#endif

#define WINAPI      __stdcall

BOOL CHOpenFileSelect(char *FilePath);
BOOL CHAcharToWchar(char *st,wchar_t *wst);
BOOL CHWcharToAchar(wchar_t *wst,char *st);
#ifdef __cplusplus
}
#endif
#endif