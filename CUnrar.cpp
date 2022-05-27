#include "CUnrar.h"
#include "resource.h"


bool CUnrar::ListArchive(string strFileName,ofstream& out)
{
  struct RARHeaderDataEx HeaderData;
  struct RAROpenArchiveDataEx OpenArchiveData;
  HANDLE hArcData;
  int RHCode,PFCode;
  short i;

  char CmtBuf[16384];


  TCHAR *strTime=new TCHAR[50];
  if(!strTime)
   return false;

  TCHAR *strSize=new TCHAR[50];
  if(!strSize)
   return false;

  TCHAR *strComp=new TCHAR[50];
  if(!strComp)
   return false;

  memset(&OpenArchiveData,0,sizeof(OpenArchiveData));
  OpenArchiveData.ArcName=(char*)strFileName.c_str();
  OpenArchiveData.CmtBuf=CmtBuf;
  OpenArchiveData.CmtBufSize=sizeof(CmtBuf);
  OpenArchiveData.OpenMode=RAR_OM_LIST;
  hArcData=RAROpenArchiveEx(&OpenArchiveData);
  if (OpenArchiveData.OpenResult!=0)   
    return false;

  out << "<html>" << endl;
  out << "<head>" << endl;
  out << "<title>Free Unrar-Report</title>" << endl;
  out << "</head>" << endl;
  out << "<body text=#C0C0C0 bgcolor=#000000>" << endl;
  out << "<center>" << endl;
  out << "<H1>" << endl;
  out << "<B> " << w.GetFileNameShort(strFileName) << " </B>" << endl;
  out << "</H1>" << endl;
  out << "<TABLE BORDER=1 CELLSPACING=1 CELLPADDING=1><TR>"<<endl;
  out << " <TD align=center> " << endl;
  out << " <font color=#FFFFFF> <b>Nombre del Archivo</b></font></TD> " << endl;
  out << " <TD align=center>" << endl;
  out << " <font color=#FFFFFF> <b>Comprimido</b></font></TD>" << endl;
  out << " <TD align=center> " << endl;
  out << " <font color=#FFFFFF><b> Tamaño </b></font></TD>" << endl;
  out << " <TD align=center> " << endl;
  out << " <font color=#FFFFFF> <b>Fecha de Modificacion</b></font></TD>" << endl;
  out << " <TD align=center> " << endl;
  out << " <font color=#FFFFFF> <b>Tipo</b></font></TD>" << endl;
  out << " <TD align=center> " << endl;
  out << " <font color=#FFFFFF> <b>CRC32 </b></font></TD></TR>" << endl;

  string strType="";
  if(OpenArchiveData.CmtState > 0){		
	string strComment;
	out << "Comentario: <br><br>" << endl;
	strComment=CmtBuf;	
	char*p=strtok((char*)strComment.c_str(),"\r\n");
	while(p!=NULL){     
	 out << p << "<br>" << endl;
     p=strtok(NULL,"\r\n");
	}
  }
  
  out << "<br><br>" << endl;
  RARSetCallback(hArcData,CallbackProc,0);

  HeaderData.CmtBuf=CmtBuf;
  HeaderData.CmtBufSize=sizeof(CmtBuf);

  i=0; 
  FILETIME   ft;
  SYSTEMTIME st;
  
  while ((RHCode=RARReadHeaderEx(hArcData,&HeaderData))==0)
  {
    __int64 UnpSize=HeaderData.UnpSize+(((__int64)HeaderData.UnpSizeHigh)<<32);
    __int64 PackSize=HeaderData.PackSize+(((__int64)HeaderData.PackSizeHigh)<<32);

    wsprintf(strSize,"%ld",UnpSize);		
	wsprintf(strComp,"%ld",PackSize);

	DosDateTimeToFileTime(HIWORD(HeaderData.FileTime),LOWORD(HeaderData.FileTime),&ft);
	FileTimeToSystemTime(&ft,&st);    
    SystemTimeToFileTime(&st,&ft);
    wsprintf(strTime,"%02d/%02d/%02d %02d:%02d:%02d",st.wDay,st.wMonth,st.wYear,st.wHour,st.wMinute,st.wSecond);
  

	if((HeaderData.FileAttr & FILE_ATTRIBUTE_DIRECTORY) > 0)
	 strType = "Directorio";
	else if((HeaderData.FileAttr & FILE_ATTRIBUTE_ARCHIVE) > 0)
	 strType = "Archivo";
	else if((HeaderData.FileAttr & FILE_ATTRIBUTE_COMPRESSED) > 0)
	 strType = "Archivo que esta comprimido";	
	else if((HeaderData.FileAttr & FILE_ATTRIBUTE_HIDDEN) > 0)
	 strType ="Archivo Oculto";   
	else if((HeaderData.FileAttr & FILE_ATTRIBUTE_READONLY) > 0)
	 strType ="Archivo de solo lectura";
	else if((HeaderData.FileAttr & FILE_ATTRIBUTE_SYSTEM) > 0)
	 strType ="Archivo de sistema";
	else if((HeaderData.FileAttr & FILE_ATTRIBUTE_TEMPORARY) > 0)
     strType ="Archivo temporal";
	
	out << endl;
    out << "<tr><td> "<< HeaderData.FileName << "</td>" << endl;    
    out << "<td> "    << strComp <<  "</td>" << endl;
    out << "<td> "    << strSize <<  "</td>" << endl;
    out << "<td> "    << strTime <<  "</td>" << endl;
	out << "<td> "    << strType <<  "</td>" << endl;
	out << "<td> "    << hex << HeaderData.FileCRC << "</td></tr>" << endl;
	out << endl;

	
	i++;		
	if ((PFCode=RARProcessFile(hArcData,RAR_SKIP,NULL,NULL))!=0)
	 break;
    
  }
  if (RHCode==ERAR_BAD_DATA)
   return false;

  RARCloseArchive(hArcData);
 

  if(strTime!=0)
    delete [] strTime;

  if(strComp!=0)
	delete [] strComp;

  if(strSize!=0)
   delete [] strSize;

  out << "</TABLE>" << endl;
  out << "<br>" << endl;
  out << "<font size=2>Generado por <b>Free Unrar 0.1<b><br>"<<endl;  
  out << "</font>" << endl;
  out << "</center>" << endl;
  out << "</body>" << endl;
  out << "</html>" << endl;

  return true;
}

bool CUnrar::ListArchive(string strFileName,CListView v)
{
  struct RARHeaderDataEx HeaderData;
  struct RAROpenArchiveDataEx OpenArchiveData;
  HANDLE hArcData;
  int RHCode,PFCode;
  short i;

  char CmtBuf[16384];

  TCHAR *strSize=new TCHAR[50];
  if(!strSize)
   return false;

  TCHAR *strTime=new TCHAR[50];
  if(!strTime)
   return false;

  TCHAR *Crc=new TCHAR[80];
  if(!Crc)
	return false;

  TCHAR *strComp=new TCHAR[50];
  if(!strComp)
   return false;

  memset(&OpenArchiveData,0,sizeof(OpenArchiveData));
  OpenArchiveData.ArcName=(char*)strFileName.c_str();
  OpenArchiveData.CmtBuf=CmtBuf;
  OpenArchiveData.CmtBufSize=sizeof(CmtBuf);
  OpenArchiveData.OpenMode=RAR_OM_LIST;
  hArcData=RAROpenArchiveEx(&OpenArchiveData);
  if (OpenArchiveData.OpenResult!=0)   
    return false;

  string strType="";
  if(OpenArchiveData.CmtState > 0){
	m_strComment="";
	m_strComment+="Comentario:\n";
	m_strComment+=CmtBuf;	
	m_Flag=true;	
  }
  else
    m_Flag=false;

  RARSetCallback(hArcData,CallbackProc,0);

  HeaderData.CmtBuf=CmtBuf;
  HeaderData.CmtBufSize=sizeof(CmtBuf);

  i=0; 
  FILETIME   ft;
  SYSTEMTIME st;
  while ((RHCode=RARReadHeaderEx(hArcData,&HeaderData))==0)
  {
    __int64 UnpSize=HeaderData.UnpSize+(((__int64)HeaderData.UnpSizeHigh)<<32);
    __int64 PackSize=HeaderData.PackSize+(((__int64)HeaderData.PackSizeHigh)<<32);

	wsprintf(strSize,"%ld",UnpSize);	
	wsprintf(Crc,"%0X",HeaderData.FileCRC);
	wsprintf(strComp,"%ld",PackSize);
    
	DosDateTimeToFileTime(HIWORD(HeaderData.FileTime),LOWORD(HeaderData.FileTime),&ft);
	FileTimeToSystemTime(&ft,&st);    
    SystemTimeToFileTime(&st,&ft);
    wsprintf(strTime,"%02d/%02d/%02d %02d:%02d:%02d",st.wDay,st.wMonth,st.wYear,st.wHour,st.wMinute,st.wSecond);

	if((HeaderData.FileAttr & FILE_ATTRIBUTE_DIRECTORY) > 0)
	 strType = "Directorio";
	else if((HeaderData.FileAttr & FILE_ATTRIBUTE_ARCHIVE) > 0)
	 strType = "Archivo";
	else if((HeaderData.FileAttr & FILE_ATTRIBUTE_COMPRESSED) > 0)
	 strType = "Archivo que esta comprimido";	
	else if((HeaderData.FileAttr & FILE_ATTRIBUTE_HIDDEN) > 0)
	 strType ="Archivo Oculto";   
	else if((HeaderData.FileAttr & FILE_ATTRIBUTE_READONLY) > 0)
	 strType ="Archivo de solo lectura";
	else if((HeaderData.FileAttr & FILE_ATTRIBUTE_SYSTEM) > 0)
	 strType ="Archivo de sistema";
	else if((HeaderData.FileAttr & FILE_ATTRIBUTE_TEMPORARY) > 0)
     strType ="Archivo temporal";

	v.AddItem(HeaderData.FileName,i,0);		
    v.AddSubItem(i,1,strSize);
	v.AddSubItem(i,2,strComp);
	v.AddSubItem(i,3,(char*)strType.c_str());
	v.AddSubItem(i,4,strTime);
	v.AddSubItem(i,5,Crc);
	
	i++;		
	if ((PFCode=RARProcessFile(hArcData,RAR_SKIP,NULL,NULL))!=0)
	 break;
    
  }
  if (RHCode==ERAR_BAD_DATA)
   return false;

  RARCloseArchive(hArcData);
 

  if(strSize!=0)
   delete [] strSize;

  if(strTime!=0)
    delete [] strTime;

  if(Crc!=0)
	delete [] Crc;

  if(strComp!=0)
	delete [] strComp;

  return true;
}

bool CUnrar::ExtractArchive(string ArcName,string strOut)
{
  HANDLE hArcData;
  int RHCode,PFCode;
  char *CmtBuf=new char[16384];
  int Mode=EXTRACT;
  struct RARHeaderData HeaderData;
  struct RAROpenArchiveDataEx OpenArchiveData;

  if(!CmtBuf)
   return false;

  memset(&OpenArchiveData,0,sizeof(OpenArchiveData));
  OpenArchiveData.ArcName=(char*)ArcName.c_str();
  OpenArchiveData.CmtBuf=CmtBuf;
  OpenArchiveData.CmtBufSize=sizeof(CmtBuf);
  OpenArchiveData.OpenMode=RAR_OM_EXTRACT;
  hArcData=RAROpenArchiveEx(&OpenArchiveData);

  if (OpenArchiveData.OpenResult!=0)   
    return false;
  

  SetCurrentDirectory(strOut.c_str());


  RARSetCallback(hArcData,CallbackProc,(LONG)&Mode);
  HeaderData.CmtBuf=NULL;

  while ((RHCode=RARReadHeader(hArcData,&HeaderData))==0){
    
    PFCode=RARProcessFile(hArcData,RAR_EXTRACT, NULL,NULL);
                         
    if (PFCode!=0)
      return false;
    
  }

  if (RHCode==ERAR_BAD_DATA)  
    false;

  RARCloseArchive(hArcData);

  if(CmtBuf!=0)
   delete [] CmtBuf;

  return true;
}

bool CUnrar::GenerateInforme(string strFileName,string strRarFile)
{
 ofstream out;
 out.open(strFileName.c_str());
 if(out.fail())
  return false;

 ListArchive(strRarFile,out);
 out.close();
 return true;
}


int CALLBACK CUnrar::CallbackProc(UINT msg,LONG UserData,LONG P1,LONG P2)
{
  static TCHAR strMsg[80];
  switch(msg)
  {
    case UCM_CHANGEVOLUME:
      if (P2==RAR_VOL_ASK)
      {        		
		wsprintf(strMsg,"El volume %s es requerido\nPosibles Opciones:\nCancel - Cancelar\nRetry - Intentar nuevamente",(char*)P1);
        int iRes=MessageBox(NULL,strMsg,"Free Unrar",MB_RETRYCANCEL|MB_ICONWARNING);
        switch(iRes)
        {
          case IDCANCEL:
            return -1;	
		  case IDRETRY:
			return 0;
          default:
            return 0;
        }
      }
      if (P2==RAR_VOL_NOTIFY){
        wsprintf(strMsg,"\n  ... Volume: %s\n",(char *)P1);
		MessageBox(NULL,strMsg,"Free Unrar",MB_OK);
	  }
	    
      return(0);
    case UCM_PROCESSDATA:      
      return(0);
    case UCM_NEEDPASSWORD:      
	  MessageBox(NULL,"Requiere Password","Free Unrar",MB_ICONINFORMATION);
      return(0);
  }
  return(0);
}
