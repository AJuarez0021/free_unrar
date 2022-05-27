#ifndef __CSTATUSBAR_H
#define __CSTATUSBAR_H

#include <windows.h>

class CStatusBar
{
private:
 HWND hStatus;
 RECT rcStatus;
public:
 CStatusBar(){ hStatus=NULL; }
 bool CreateStatusBar(HWND hWnd,UINT nIDMenu);
 void DestroyStatusBar();
 void SetText(LPCSTR strText);
 void SetParts(int *StatWidths);
 void AutoSize();
 int GetHeight();
};

#endif