#include "CListView.h"

void CListView::AddColumn(LPSTR lpszTexto, int nAncho, int nIndice)
{
	LV_COLUMN   lvCol;      
	lvCol.cchTextMax = 260;
	lvCol.pszText = lpszTexto;
	lvCol.mask = LVCF_TEXT|LVCF_WIDTH;
	lvCol.cx = nAncho;
	ListView_InsertColumn(hListView, nIndice, &lvCol);
}

void CListView::AddItem(LPSTR lpszTexto, int nIndice, int nIndiceImagen)
{
    static LV_ITEM     lvItem; 
	lstrcpy(szbuffer, lpszTexto);  
	lstrcat(szbuffer, "\0");
	lvItem.pszText = szbuffer;
	lvItem.cchTextMax = sizeof(szbuffer);
	lvItem.mask = LVIF_TEXT|LVIF_IMAGE; 
	lvItem.iItem = nIndice; 
	lvItem.iImage = nIndiceImagen;
	ListView_InsertItem(hListView, &lvItem);
	ListView_Update(hListView, nIndice);
}


void CListView::AddSubItem(int nIndiceItem, int nIndiceSubItem, LPSTR lpszTexto)
{
	lstrcpy(szbuffer, lpszTexto);  
	lstrcat(szbuffer, "\0");
	LV_ITEM lv;
	lv.iSubItem = nIndiceSubItem;
	lv.pszText = szbuffer;
	SendMessage(hListView, LVM_SETITEMTEXT, (WPARAM) (int) nIndiceItem, (LPARAM) (LV_ITEM FAR *) &lv);
}
