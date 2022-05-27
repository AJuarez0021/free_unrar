#include "CToolBar.h"
#include "resource.h"
void CToolBar::Enable(BOOL bEnable,UINT uID)
{
 SendMessage(g_hToolBar,TB_ENABLEBUTTON,uID,MAKELONG(bEnable, 0));
}

int CToolBar::GetHeight()
{
  GetWindowRect(g_hToolBar, &rcTool);

 return rcTool.bottom - rcTool.top;
}


bool CToolBar::CreateToolBar(HWND hWnd,UINT uIDMenu)
{
  g_hToolBar=CreateWindowEx(0,      
                            TOOLBARCLASSNAME,             
                            NULL,                         
                            WS_CHILD | WS_VISIBLE |TBSTYLE_TOOLTIPS|TBSTYLE_LIST,                           
                            0,                           
                            0,                            
                            0,                           
                            0,                            
                            hWnd,                        
                            (HMENU)uIDMenu,                       
                            GetModuleHandle(NULL),                      
                            NULL);                        

 
  if(g_hToolBar==NULL)
   return false;


  SendMessage(g_hToolBar, TB_BUTTONSTRUCTSIZE, (WPARAM)sizeof(TBBUTTON), 0);
  
  return true;

}

void CToolBar::AddButton(int nID,int iBitmap,const char *Text)
{
	                   
	        TBADDBITMAP tbab;		  
			tbab.hInst = HINST_COMMCTRL;
			tbab.nID = IDB_STD_SMALL_COLOR;
			SendMessage(g_hToolBar, TB_ADDBITMAP, 0, (LPARAM)&tbab);				
			tbb.iBitmap=iBitmap;			
			tbb.fsState= TBSTATE_ENABLED;
			tbb.fsStyle=TBSTYLE_BUTTON; 
			tbb.idCommand=nID;  
			tbb.iString=(Text!=NULL) ? (int)TEXT(Text) : 0; 	
			SendMessage(g_hToolBar, TB_ADDBUTTONS,sizeof(tbb)/sizeof(TBBUTTON), (LPARAM)&tbb);
								
}

void CToolBar::AddButtonExt(int nID,int iBitmap,const char *Text)
{
  TBADDBITMAP tbab;	


  tbab.hInst = HINST_COMMCTRL;
  tbab.nID = IDB_STD_SMALL_COLOR;
  SendMessage(g_hToolBar, TB_ADDBITMAP, 0, (LPARAM)&tbab);	
  
  tbb.iBitmap=iBitmap;			
  tbb.fsState= TBSTATE_ENABLED;
  tbb.fsStyle=TBSTYLE_DROPDOWN;
  tbb.idCommand=nID;  
  tbb.iString=(Text!=NULL) ? (int)TEXT(Text) : 0; 	
  
  SendMessage(g_hToolBar,TB_SETEXTENDEDSTYLE,(WPARAM)0,(LPARAM)TBSTYLE_EX_DRAWDDARROWS);
  SendMessage(g_hToolBar, TB_ADDBUTTONS,sizeof(tbb)/sizeof(TBBUTTON), (LPARAM)&tbb);
}

void CToolBar::AddSeparator()
{
 tbb.iBitmap=0;
 tbb.idCommand=-1;
 tbb.fsState=TBSTATE_ENABLED;
 tbb.fsStyle=TBSTYLE_SEP;	
 tbb.dwData=0;
 tbb.iString=0;
 SendMessage(g_hToolBar, TB_ADDBUTTONS,sizeof(tbb)/sizeof(TBBUTTON), (LPARAM)&tbb);

}


void CToolBar::AutoSize()
{
 SendMessage(g_hToolBar, TB_AUTOSIZE, 0, 0); 
}
