#include <windows.h>
#include <commctrl.h> 

#pragma comment(lib,"comctl32.lib")

const LV_NORMAL    = WS_CHILD|WS_VISIBLE|WS_BORDER|LVS_SHOWSELALWAYS|LVS_SINGLESEL;
const LV_REPORTE   = LV_NORMAL|LVS_REPORT;

class CListView
{
private:
 HWND hListView;            
 TCHAR       szbuffer[256];
  
public:
 CListView(){
  hListView=NULL;
 }
 void SetHWND(HWND hWnd,UINT uID){
  hListView=GetDlgItem(hWnd,uID);
 }
 bool CreateListView(HWND hWnd)
 {
  RECT r;
  GetClientRect(hWnd, &r);			
  hListView = CreateWindowEx(WS_EX_CLIENTEDGE, WC_LISTVIEW, "", LV_REPORTE, 15, 30, r.right - 29, r.bottom - 45, hWnd, NULL, (HINSTANCE)GetModuleHandle(NULL), NULL);
  if(!hListView)
   return false;

  return true;
 }
 
 HWND GetHWND(){
  return hListView;
 }
 void DestroyListView(){
     DestroyWindow(hListView);
 }
 void DeleteAllItems(){ 
	ListView_DeleteAllItems(hListView); 
 }
 int  GetItem(){ 
  return ListView_GetNextItem(hListView,-1,LVNI_SELECTED); 
 }
 void DeleteItem(int iItem){
  ListView_DeleteItem(hListView,iItem);	
 }
 void SetTextColor(COLORREF c){
  ListView_SetTextColor(hListView,c);
 }
 void SetTextBkColor(COLORREF c){
   ListView_SetTextBkColor(hListView,c);
 }
 void SetBkColor(COLORREF c){
   ListView_SetBkColor(hListView,c);
 }
 void DrawGrid(){
	SendMessage(hListView, LVM_SETEXTENDEDLISTVIEWSTYLE,0,(LPARAM)LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
 }
 void AddColumn(LPSTR lpszTexto, int nAncho, int nIndice); 
 void AddItem(LPSTR lpszTexto, int nIndice, int nIndiceImagen);
 void AddSubItem(int nIndiceItem, int nIndiceSubItem, LPSTR lpszTexto);

};