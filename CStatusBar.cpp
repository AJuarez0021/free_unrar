#include "CStatusBar.h"
#include <commctrl.h>

int CStatusBar::GetHeight()
{

 GetWindowRect(hStatus, &rcStatus);
 return rcStatus.bottom - rcStatus.top;
}


void CStatusBar::AutoSize()
{
 SendMessage(hStatus, WM_SIZE, 0, 0);
}

void CStatusBar::SetParts(int *StatWidths)
{
 SendMessage(hStatus, SB_SETPARTS, sizeof(StatWidths)/sizeof(int), (LPARAM)StatWidths);
}

bool CStatusBar::CreateStatusBar(HWND hWnd,UINT nIDMenu)
{
 hStatus = CreateWindowEx(0, STATUSCLASSNAME, NULL,
		  WS_CHILD | WS_VISIBLE | SBARS_SIZEGRIP, 0, 0, 0, 0,
		  hWnd, (HMENU)nIDMenu, GetModuleHandle(NULL), NULL);
 if(!hStatus)
  return false;

 return true;
}

void CStatusBar::DestroyStatusBar()
{
 DestroyWindow(hStatus);
}

void CStatusBar::SetText(LPCSTR strText)
{
 SendMessage(hStatus, SB_SETTEXT, (WPARAM) 0 | 0, (LPARAM) strText);
}