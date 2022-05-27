#include <windows.h>
#include "Unrar.h"
#include "CListView.h"
#include "CWnd.h"
#include <string>
#include <fstream>

using namespace std;

enum { EXTRACT, TEST, PRINT };

class CUnrar
{
private:
 string m_strComment;
 bool m_Flag;
 CWnd w;
public:
 
 CUnrar() 
 {
  m_Flag=false;  
 }
 string GetComment(){
  return m_strComment;
 }
 bool GetCommentFlag(){
  return m_Flag;
 }
 void ShowComment(){
  if(m_Flag)
   MessageBox(NULL,GetComment().c_str(),"Free Unrar",MB_ICONINFORMATION);
  else
   MessageBox(NULL,"El archivo no contiene comentarios","Free Unrar",MB_ICONINFORMATION);
 }
 bool ExtractArchive(string ArcName,string strOut);
 bool ListArchive(string,CListView);    
 bool GenerateInforme(string strFileName,string strRarFile);
 static int CALLBACK CallbackProc(UINT msg,LONG UserData,LONG P1,LONG P2); 
private:
  bool ListArchive(string,ofstream& );
};