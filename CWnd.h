#include <windows.h>
#include <shlobj.h>
#include "ImageMenu.h"
#include <string>

using namespace std;

class CWnd{
private:
 HWND  m_hWnd;
 HICON m_hIcon; 
 HINSTANCE m_hInst;
 string m_selectedFolder;
 string m_selectedFile;
 string m_selectedFile2;
public:
 CWnd(){
  m_hWnd=NULL;
 }
 void SetHWND(HWND hWnd){
  m_hWnd=hWnd;
 }
 void SethInstance(HINSTANCE hInst){
  m_hInst=hInst;
 }
 HINSTANCE GethInstance(){
  return m_hInst;
 }
 HWND GetHWND(){
  return m_hWnd;
 }
 bool Open(LPSTR lpszFilter, LPSTR lpszTitle);
 bool Save(LPSTR lpszFilter, LPSTR lpszTitle);
 void SetDlgIcon(UINT nIDIcon);
 void CenterDlg(); 
 void ShowError(string strText){
  MessageBox(m_hWnd,strText.c_str(),"Free UnRar",MB_ICONERROR);
 }
 void DestroyDlgIcon(){
  DestroyIcon(m_hIcon);
 } 
 void ShowMessage(string strText){
  MessageBox(m_hWnd,strText.c_str(),"Free UnRar",MB_ICONINFORMATION);
 }
 bool Browse(LPSTR strTitle);
 string GetFolderName() const;
 string GetFileName() const;
 string Get_SaveFileName() const;
 string GetFileNameShort(string Directory) const;

};