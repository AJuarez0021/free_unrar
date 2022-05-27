#ifndef __CTOOLBAR_H
#define __CTOOLBAR_H

#include <windows.h>
#include <commctrl.h>

class CToolBar
{

private:
	HWND g_hToolBar;
	
    RECT rcTool;
public:
	 TBBUTTON tbb;
     CToolBar(){ 
	  INITCOMMONCONTROLSEX iccx;
	  iccx.dwSize=sizeof(INITCOMMONCONTROLSEX);
      iccx.dwICC=ICC_BAR_CLASSES;
      InitCommonControlsEx(&iccx);
	  g_hToolBar=NULL;
	 }
	~CToolBar(){ 
	}
	bool CreateToolBar(HWND hWnd,UINT uIDMenu);
	void AddButton(int nID,int iBitmap,const char *Text);
	void AddButtonExt(int nID,int iBitmap,const char *Text);
	void AddSeparator();
	void DestroyToolBar(){ DestroyWindow(g_hToolBar); }
    void Enable(BOOL bEnable,UINT uID);
	void AutoSize();
	int GetHeight();
	HWND GetHWNDToolBar(){ return g_hToolBar; }
};
#endif