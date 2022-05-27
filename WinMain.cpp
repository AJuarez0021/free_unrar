//Free Unrar
//Version 0.1
//Programa compilado con Visual C++ 6.0
//http://www.programacioncpp.irandohosting.0lx.net
#include <windows.h>
#include "CToolBar.h"
#include "CStatusBar.h"
#include "CUnrar.h"
#include "resource.h"
#include "hyperlink.h"

LRESULT CALLBACK WndProc (HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK AboutProc(HWND hWnd,UINT uMesg,WPARAM wParam,LPARAM lParam);
BOOL CALLBACK CommentProc(HWND hWnd,UINT uMesg,WPARAM wParam,LPARAM lParam);
void GenerateImageList(HWND hWnd,CToolBar t);
static CUnrar     u;

#define ID_TOOL_OPEN        0
#define ID_TOOL_EXTRACT     1
#define ID_TOOL_ABOUT       2
#define ID_TOOL_COMMENT     3
#define ID_TOOL_INFORME     4
#define ID_TOOL_CLOSE       5

int WINAPI WinMain (HINSTANCE hInst, HINSTANCE hPreInst,LPSTR lpszCmdLine,int nCmdShow)

{
	static TCHAR NombreClase[]   = TEXT("MiClaseVentana");
    HWND hWnd;               
    MSG Mensaje;            
    WNDCLASSEX ClaseVentana;        
    
	ClaseVentana.cbSize        = sizeof (WNDCLASSEX);
	ClaseVentana.style         = CS_HREDRAW | CS_VREDRAW;
	ClaseVentana.lpfnWndProc   = WndProc; 
	ClaseVentana.cbClsExtra    = 0;                      
    ClaseVentana.cbWndExtra    = 0; 
	ClaseVentana.hInstance     = hInst;
    ClaseVentana.hIcon         = LoadIcon (NULL, IDI_APPLICATION);
	ClaseVentana.hIconSm       = LoadIcon (NULL, IDI_APPLICATION);
    ClaseVentana.hCursor       = LoadCursor (NULL, IDC_ARROW);
	ClaseVentana.hbrBackground = (HBRUSH)COLOR_BACKGROUND; 
	ClaseVentana.lpszMenuName  = MAKEINTRESOURCE(IDR_MENU1);
    ClaseVentana.lpszClassName = NombreClase;
	
    if (!RegisterClassEx (&ClaseVentana))
        return 0;

    
    hWnd = CreateWindowEx (
           0,                   
           NombreClase,         
           TEXT("Free Unrar"),       
           WS_VISIBLE | WS_OVERLAPPEDWINDOW, 
           CW_USEDEFAULT,      
           CW_USEDEFAULT,       
           640,                 
           480,                 
           NULL,       
           NULL,                
           hInst,       
           NULL                 
           );

    if(!hWnd) 
	  return 0;
	
    ShowWindow (hWnd, SW_SHOWNORMAL);
    UpdateWindow(hWnd);
	
	InitCommonControls();		
    
    while (GetMessage (&Mensaje, NULL, 0, 0))
    {        
        TranslateMessage(&Mensaje);
        DispatchMessage(&Mensaje);
    }

    return (int)Mensaje.wParam;
}


BOOL CALLBACK CommentProc(HWND hWnd,UINT uMesg,WPARAM wParam,LPARAM lParam)
{
 CWnd w;

 switch(uMesg){
   case WM_INITDIALOG:  
	   {
	     w.SetHWND(hWnd);	
		 w.SetDlgIcon(IDI_ICON1);
		 string strComment=u.GetComment().c_str();
		 char *p=strtok((char*)strComment.c_str(),"\r\n");
		 while(p!=NULL){               
		   SendDlgItemMessage(hWnd,IDC_LIST1,LB_ADDSTRING,0,(LPARAM)p);
		   p=strtok(NULL,"\r\n");
		 }
		 SetFocus(GetDlgItem(hWnd,IDC_LIST1));
	   }
        return TRUE;    
   case WM_CLOSE:
	   EndDialog(hWnd,0);
	   return TRUE;
   case WM_COMMAND:
	   switch(LOWORD(wParam))
	   {
	    
         case ID_COMMENT_CANCEL: 
		      EndDialog(hWnd,0);
		      return TRUE;			
	   }
	   break;
 }
 return FALSE;
}

BOOL CALLBACK AboutProc(HWND hWnd,UINT uMesg,WPARAM wParam,LPARAM lParam)
{
 CWnd w;
 HYPCTRL hc;
 switch(uMesg){
   case WM_INITDIALOG:  
	    w.SetHWND(hWnd);	
		w.SetDlgIcon(IDI_ICON1);
		InitHypCtrl(&hc);
		hc.ulStyle	 = ulHover;
		hc.szLink	 = TEXT("http://www.programacioncpp.irandohosting.0lx.net");
		hc.szTooltip = TEXT("Visitar pagina Web");
		CreateHypCtrl(hWnd, &hc,25, 88, 0, 0);

		
        return TRUE;    
   case WM_CLOSE:
	   EndDialog(hWnd,0);
	   return TRUE;
   case WM_COMMAND:
	   switch(LOWORD(wParam))
	   {
         case IDC_ABOUT_OK: 
		      EndDialog(hWnd,0);
		      return TRUE;			
	   }
	   break;
 }
 return FALSE;
}


void GenerateImageList(HWND hWnd,CToolBar t)
{
 #define CX_ICON  16 
 #define CY_ICON  16 
 #define MAX 6

 HIMAGELIST himlIcons,hImglBtn;
 HBITMAP hBitmap; 
 
 long lStyle = GetWindowLong(t.GetHWNDToolBar(), GWL_STYLE );
 lStyle |= TBSTYLE_FLAT;
 SetWindowLong(t.GetHWNDToolBar(), GWL_STYLE, lStyle );

 hImglBtn = ImageList_Create(CX_ICON, CY_ICON, ILC_COLORDDB|ILC_MASK, MAX, 1);  
 hBitmap = LoadBitmap((HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE),MAKEINTRESOURCE(IDB_BITMAP2));
 ImageList_AddMasked(hImglBtn,hBitmap,RGB(255,0,255));
 DeleteObject(hBitmap);
 SendMessage(t.GetHWNDToolBar(), TB_SETIMAGELIST, (WPARAM)0, (WPARAM)hImglBtn);

 

 himlIcons = ImageList_Create(CX_ICON, CY_ICON, ILC_COLORDDB|ILC_MASK, MAX, 1);  
 hBitmap = LoadBitmap((HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE),MAKEINTRESOURCE(IDB_BITMAP3));
 ImageList_AddMasked(himlIcons,hBitmap,RGB(255,0,255));
 DeleteObject(hBitmap);
 SendMessage(t.GetHWNDToolBar(), TB_SETHOTIMAGELIST, (WPARAM)0, (LPARAM)himlIcons);


}
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMesg, WPARAM wParam, LPARAM lParam)
{
	static CToolBar   t;
	static CWnd       w;
	static CStatusBar s;
	static CListView  v;
	static HMENU hMenu;
	RECT  r;
	IMITEMIMAGE imi;
	
	
    switch (uMesg){
        case WM_DESTROY:	
			 CoUninitialize();		
		     s.DestroyStatusBar(); 
             t.DestroyToolBar();   
			 v.DestroyListView();  
             PostQuitMessage (0);   			
             return 0;
		
		case WM_CREATE:				 		 
		     w.SetHWND(hWnd);	
			 w.SetDlgIcon(IDI_ICON1);
			 t.CreateToolBar(hWnd,NULL); 
             GenerateImageList(hWnd,t);			 
			 t.AddButton(ID_TOOL_OPEN,0,TEXT("Abrir")); 			 								
			 t.AddSeparator();
			 t.AddButton(ID_TOOL_EXTRACT,1,TEXT("Extraer en..."));
			 t.AddButton(ID_TOOL_COMMENT,3,TEXT("Ver comentario"));
			 t.AddButton(ID_TOOL_INFORME,4,TEXT("Generar informe"));						 
			 t.AddSeparator();			 			 
			 t.AddButton(ID_TOOL_ABOUT,2,TEXT("Acerca de")); 
             t.Enable(FALSE,ID_TOOL_EXTRACT);
			 t.Enable(FALSE,ID_TOOL_COMMENT);
			 t.Enable(FALSE,ID_TOOL_INFORME);
 			 s.CreateStatusBar(hWnd,IDR_MENU1); 
			 s.SetText("Listo");
			 v.CreateListView(hWnd); 			 		 
			 GetClientRect(hWnd,&r);			 
			 MoveWindow(v.GetHWND(),0,t.GetHeight(),r.right,r.bottom-s.GetHeight()-t.GetHeight(),TRUE);	
			 v.AddColumn("Nombre",190,0);
		     v.AddColumn("Tamaño",90,1);
		     v.AddColumn("Comprimido",80,2);
		     v.AddColumn("Tipo",120,3);
		     v.AddColumn("Modificado",140,4);
		     v.AddColumn("CRC",140,5);		
		     v.SetTextColor(RGB(75,75,75)); 			 			
			
             hMenu=GetMenu(hWnd);			 
             ImageMenu_Create(hWnd, hMenu);
             ImageMenu_SetStyle(OFFICE2003);
			 ImageMenu_SetMenuTitleProps(GetSubMenu(hMenu,0), TEXT("Archivo"), TRUE);
			 ImageMenu_SetMenuTitleBkProps(GetSubMenu(hMenu,0), RGB(255,237,213), RGB(255,186,94), TRUE, TRUE);
             EnableMenuItem(hMenu,ID_FILE_EXTRACT,MF_GRAYED);
			 EnableMenuItem(hMenu,ID_FILE_SHOWCOMMENT,MF_GRAYED);
			 EnableMenuItem(hMenu,ID_FILE_INFORME,MF_GRAYED);
			 
             imi.mask = IMIMF_LOADFROMRES|IMIMF_ICON;
             imi.hInst = GetModuleHandle(NULL);
            
             imi.itemID = ID_FILE_EXIT;
             imi.imageStr = MAKEINTRESOURCE(IDI_ICON3);
             ImageMenu_SetItemImage(&imi);

			 imi.itemID = ID_FILE_OPENFILE;
             imi.imageStr = MAKEINTRESOURCE(IDI_ICON4);
             ImageMenu_SetItemImage(&imi);

             imi.itemID = ID_HELP_ABOUT;
             imi.imageStr = MAKEINTRESOURCE(IDI_ICON5);
             ImageMenu_SetItemImage(&imi);

			 if(FAILED(CoInitialize(NULL))){
               w.ShowError(TEXT("Error al iniciar CoInitialize"));
		       SendMessage(hWnd,WM_CLOSE,0,0);
			 }          
			 
			 w.CenterDlg(); 
			 return 0;
		case WM_NOTIFY:
			  switch (((LPNMHDR) lParam)->code){
               case TTN_GETDISPINFO:
				 {
			       LPTOOLTIPTEXT lpttt; 
			       lpttt = (LPTOOLTIPTEXT) lParam; 
			       lpttt->hinst = GetModuleHandle(NULL); 
			       switch(lpttt->hdr.idFrom){		
			         case ID_TOOL_EXTRACT:
					  lpttt->lpszText=TEXT("Extrae el archivo .rar\nen la ruta que se le especifique");
					  break;
				     case ID_TOOL_OPEN:
					  lpttt->lpszText=TEXT("Abre archivo .rar");
					  break;
				     case ID_TOOL_ABOUT:
					  lpttt->lpszText=TEXT("Muestra informacion del programa");
					  break;
					 case ID_TOOL_COMMENT:
                      lpttt->lpszText=TEXT("Muestra el comentario del archivo .rar");
					  break;
					 case ID_TOOL_INFORME:
					  lpttt->lpszText=TEXT("Genera un Informe\ncon la informacion de los archivos");
					  break;
					 case ID_TOOL_CLOSE:
					  lpttt->lpszText=TEXT("Cierra la aplicacion");
					  break;
				   }
	 
				 }
			     break;
			  }
			 return 0;
		case WM_SIZE:
			{
			 t.AutoSize(); 
			 s.AutoSize();			
			 RECT r;
			 GetClientRect(hWnd,&r);			 
			 MoveWindow(v.GetHWND(),0,t.GetHeight(),r.right,r.bottom-s.GetHeight()-t.GetHeight(),TRUE);	
			}
			 return 0;
		case WM_COMMAND:
           switch(wParam){
		     case ID_TOOL_COMMENT:
		     case ID_FILE_SHOWCOMMENT:				   				  
				  if(u.GetCommentFlag())
				    DialogBox(GetModuleHandle(NULL),MAKEINTRESOURCE(IDD_COMMENT),hWnd,(DLGPROC)CommentProc);
				  else
					w.ShowMessage("El archivo no contiene comentarios");
				  break;
		     case ID_TOOL_EXTRACT: 				  
			 case ID_FILE_EXTRACT:
				  if(w.Browse("Buscar directorio")){
					if(u.ExtractArchive(w.GetFileName(),w.GetFolderName())){
				     w.ShowMessage("El archivo: " + w.GetFileNameShort(w.GetFileName()) + " se ha descomprimido correctamente"); 
				     EnableMenuItem(hMenu,ID_FILE_EXTRACT,MF_GRAYED);
					 EnableMenuItem(hMenu,ID_FILE_SHOWCOMMENT,MF_GRAYED);
					 EnableMenuItem(hMenu,ID_FILE_INFORME,MF_GRAYED);
					 t.Enable(FALSE,ID_TOOL_EXTRACT);
					 t.Enable(FALSE,ID_TOOL_COMMENT);
			         t.Enable(FALSE,ID_TOOL_INFORME);
					}
				  }
				  break;
			 case ID_TOOL_OPEN:	 
			 case ID_FILE_OPENFILE:
				  if(w.Open("Archivos .RAR\0*.rar\0","Abrir")){
                    s.SetText(w.GetFileName().c_str());
					v.DeleteAllItems();
					if(u.ListArchive(w.GetFileName(),v)){					
					 EnableMenuItem(hMenu,ID_FILE_EXTRACT,MF_ENABLED);
					 EnableMenuItem(hMenu,ID_FILE_SHOWCOMMENT,MF_ENABLED);
					 EnableMenuItem(hMenu,ID_FILE_INFORME,MF_ENABLED);
					 t.Enable(TRUE,ID_TOOL_EXTRACT);
					 t.Enable(TRUE,ID_TOOL_COMMENT);
			         t.Enable(TRUE,ID_TOOL_INFORME);
					}
					else
					 w.ShowError("Error al leer el archivo " + w.GetFileNameShort(w.GetFileName()));
				  }				  
				  break;
			 case ID_TOOL_INFORME:
			 case ID_FILE_INFORME:
				  if(w.Save("Archivos .HTML\0*.html\0","Guardar")){
				   if(u.GenerateInforme(w.Get_SaveFileName(),w.GetFileName()))
					w.ShowMessage(TEXT("El informe se ha generado correctamente"));
				   else
					w.ShowError(TEXT("Error: No se pudo generar el reporte"));
				  }
				  break;
		     case ID_FILE_EXIT:				  				 
                  SendMessage(hWnd,WM_CLOSE,0,0);
				  break;			 			
			 case ID_HELP_ABOUT:				 
			 case ID_TOOL_ABOUT:
				  DialogBox(GetModuleHandle(NULL),MAKEINTRESOURCE(IDD_ABOUT),hWnd,(DLGPROC)AboutProc);
				  break;			 			 				 				 							
		   }
	       return 0;
        
    }
    return DefWindowProc (hWnd, uMesg, wParam, lParam);
}
