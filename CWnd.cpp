#include "CWnd.h"

string CWnd::GetFolderName() const
{
	return m_selectedFolder;
}

string CWnd::GetFileName() const
{
 return m_selectedFile;
}

string CWnd::Get_SaveFileName() const
{
 return m_selectedFile2;
}
bool CWnd::Browse(LPSTR strTitle)
{
 BROWSEINFO bi;
 ZeroMemory(&bi, sizeof(BROWSEINFO));
 char strBuffer[MAX_PATH];
 bi.hwndOwner      = m_hWnd;
 bi.pidlRoot       = 0;
 bi.pszDisplayName = strBuffer;
 bi.lpszTitle      = strTitle;
 bi.ulFlags        = BIF_RETURNONLYFSDIRS | BIF_RETURNFSANCESTORS; 
 bi.lParam         = 0;


 LPITEMIDLIST pidl = SHBrowseForFolder(&bi);
 if (pidl != 0){  
  SHGetPathFromIDList(pidl, strBuffer);  
  m_selectedFolder = strBuffer;
 }
 return (m_selectedFolder.length() > 0) ? true : false;
}

void CWnd::CenterDlg()
{
 RECT r;	
 GetClientRect(m_hWnd,&r);
	int m_Width		= r.right;
	int m_Height	= r.bottom;

	RECT ScreenRect;
	GetWindowRect (GetDesktopWindow(), &ScreenRect);
	SetWindowPos (m_hWnd, HWND_TOP, (((ScreenRect.right + ScreenRect.left) / 2) - (m_Width / 2)),
				 (((ScreenRect.bottom + ScreenRect.top) / 2) - (m_Height / 2)),
				  m_Width, m_Height, SWP_NOCOPYBITS | SWP_NOZORDER | SWP_NOSIZE | SWP_SHOWWINDOW);
}

void CWnd::SetDlgIcon(UINT nIDIcon)
{
 m_hIcon=LoadIcon((HINSTANCE)GetWindowLong(m_hWnd, GWL_HINSTANCE),MAKEINTRESOURCE(nIDIcon));
 SendMessage(m_hWnd,WM_SETICON,ICON_BIG, (LPARAM) m_hIcon);
 SendMessage(m_hWnd,WM_SETICON,ICON_SMALL,(LPARAM)m_hIcon);
}

string CWnd::GetFileNameShort(string Directory) const
{
 int i;
 string strResult="";
 string strTemp="";

 for(i=strlen(Directory.c_str())-1;i>=0;i--){
  if(Directory[i]=='\\')
	break;

  strResult+=Directory[i];
 }

 for(i=strResult.length()-1;i>=0;i--)
  strTemp+=strResult[i];

 return strTemp;
}

bool CWnd::Open(LPSTR lpszFilter, LPSTR lpszTitle)
{
    OPENFILENAME  ofn;  
	static TCHAR szBufferIn[MAX_PATH];
	ZeroMemory(&ofn,sizeof(OPENFILENAME));
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.lpstrTitle  = "Abrir\0";
	ofn.hwndOwner   = m_hWnd;
	ofn.lpstrFilter = (lpszFilter);
	ofn.lpstrFile   = szBufferIn;
	ofn.nMaxFile    = MAX_PATH;
	ofn.lpstrFileTitle    = (lpszTitle);
	ofn.lpstrInitialDir   = ".\0";
	ofn.Flags = OFN_EXPLORER | OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST; 

	if(!GetOpenFileName (&ofn))	 
	 return false;
	

	m_selectedFile=szBufferIn;
	return true;
}

bool CWnd::Save(LPSTR lpszFilter, LPSTR lpszTitle)
{
    OPENFILENAME  ofn;  
	static TCHAR szBufferOut[MAX_PATH];
	ZeroMemory(&ofn,sizeof(OPENFILENAME));
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.lpstrTitle  = TEXT("Abrir\0");
	ofn.hwndOwner   = m_hWnd;
	ofn.lpstrFilter = (lpszFilter);
	ofn.lpstrFile   = szBufferOut;
	ofn.lpstrDefExt = TEXT(".html");
	ofn.nMaxFile    = MAX_PATH;
	ofn.lpstrFileTitle    = (lpszTitle);
	ofn.lpstrInitialDir   = TEXT(".\0");
	ofn.Flags = OFN_EXPLORER | OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST; 

	if(!GetSaveFileName (&ofn))	 
	 return false;
	
	m_selectedFile2=szBufferOut;
	return true;
}