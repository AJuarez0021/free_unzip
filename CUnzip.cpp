#include "CUnzip.h"

bool CUnzip::ListArchive(string strFileName,ofstream &out)
{
 ZRESULT zRes;
 ZIPENTRY ze;
 HZIP hz;

 hz = OpenZip(m_strFullPath,0);
 zRes=SetUnzipBaseDir(hz,m_strBaseDir);

 if(zRes!=ZR_OK)
  return false;
 
 
 TCHAR *strSize=new TCHAR[40];
 if(!strSize)
  return false;

 TCHAR *strCompSize=new TCHAR[40];
 if(!strCompSize)
  return false;

 TCHAR *strTime=new TCHAR[50];
 if(!strTime)
  return false;


 GetZipItem(hz,-1,&ze); 
 int iNumItems=ze.index;

 FILETIME   ft;
 SYSTEMTIME st;
 string strType;

  out << "<html>" << endl;
  out << "<head>" << endl;
  out << "<title>Free Unzip-Report</title>" << endl;
  out << "</head>" << endl;
  out << "<body text=#C0C0C0 bgcolor=#000000>" << endl;
  out << "<center>" << endl;
  out << "<H1>" << endl;
  out << "<B> " << strFileName << " </B>" << endl;
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
  out << " <font color=#FFFFFF> <b>CRC32</b></font></TD></TR>" << endl;
  out << endl;

 for (int zi=0; zi<iNumItems; zi++){ 
  GetZipItem(hz,zi,&ze);

  ft.dwHighDateTime=ze.mtime.dwHighDateTime;
  ft.dwLowDateTime=ze.mtime.dwLowDateTime;
  FileTimeToSystemTime(&ft,&st);    
  SystemTimeToFileTime(&st,&ft);
  
  wsprintf(strTime,"%02d/%02d/%02d %02d:%02d:%02d",st.wDay,st.wMonth,st.wYear,st.wHour,st.wMinute,st.wSecond);
  wsprintf(strSize,"%ld",ze.unc_size);
  wsprintf(strCompSize,"%ld",ze.comp_size);
  
  
  if((ze.attr & FILE_ATTRIBUTE_DIRECTORY) > 0)
   strType = "Directorio";
  else
   strType = "Archivo";

  
    out << endl;
    out << "<tr><td> "<< ze.name << "</td>" << endl;    
    out << "<td> "    << strSize <<  "</td>" << endl;
    out << "<td> "    << strCompSize <<  "</td>" << endl;
    out << "<td> "    << strTime <<  "</td>" << endl;
	out << "<td> "    << strType <<  "</td>" << endl;	
	out << "<td> "    << hex << ze.crc << "</td></tr>" << endl;
	out << endl;  
 }
 CloseZip(hz);
 
  if(strTime!=0)
   delete [] strTime;

  if(strSize!=0)
   delete [] strSize;

  if(strCompSize!=0)
   delete [] strCompSize;

  out << "</TABLE>" << endl;
  out << "<br>" << endl;
  out << "<font size=2>Generado por <b>Free Unzip 0.1<b><br>"<<endl;  
  out << "</font>" << endl;
  out << "</center>" << endl;
  out << "</body>" << endl;
  out << "</html>" << endl;

  return true;
}

bool CUnzip::Export(string strFileName,string strInFile,CWnd w)
{
 ofstream out(strFileName.c_str());
 if(out.fail())
  return false;

 if(!ListArchive(w.GetFileNameShort(strInFile),out))
  return false;

 out.close();

 return true;
}

bool CUnzip::ExtractArchive(string strPathName)
{
 ZRESULT zRes;
 ZIPENTRY ze;
 HZIP hz;
 
 SetCurrentDirectory(strPathName.c_str());
 hz = OpenZip(m_strFullPath,0);
 
 zRes=GetZipItem(hz,-1,&ze); 
 if(zRes!=ZR_OK)
  return false;

 int iNumItems=ze.index;

 for (int zi=0; zi<iNumItems; zi++){ 
  zRes=GetZipItem(hz,zi,&ze);
  if(zRes!=ZR_OK)
   return false;
  
  zRes=UnzipItem(hz,zi,ze.name);
  if(zRes!=ZR_OK)
   return false;
 }
 CloseZip(hz);
 return true;
}

bool CUnzip::ListArchive(CListView v)
{
 ZRESULT zRes;
 ZIPENTRY ze;
 HZIP hz;

 hz = OpenZip(m_strFullPath,0);
 zRes=SetUnzipBaseDir(hz,m_strBaseDir);

 if(zRes!=ZR_OK)
  return false;

 TCHAR *strComment=new TCHAR[512];
 if(!strComment)
  return false;

 GetZipComment(hz,strComment,512);
 m_strComment=strComment;

 TCHAR *strSize=new TCHAR[40];
 if(!strSize)
  return false;

 TCHAR *strCompSize=new TCHAR[40];
 if(!strCompSize)
  return false;

 TCHAR *strTime=new TCHAR[50];
 if(!strTime)
  return false;

 TCHAR *strCrc=new TCHAR[40];
 if(!strCrc)
  return false;

 GetZipItem(hz,-1,&ze); 
 int iNumItems=ze.index;

 FILETIME   ft;
 SYSTEMTIME st;

 for (int zi=0; zi<iNumItems; zi++){ 
  GetZipItem(hz,zi,&ze);

  ft.dwHighDateTime=ze.mtime.dwHighDateTime;
  ft.dwLowDateTime=ze.mtime.dwLowDateTime;
  FileTimeToSystemTime(&ft,&st);    
  SystemTimeToFileTime(&st,&ft);
  
  wsprintf(strTime,"%02d/%02d/%02d %02d:%02d:%02d",st.wDay,st.wMonth,st.wYear,st.wHour,st.wMinute,st.wSecond);
  wsprintf(strSize,"%ld",ze.unc_size);
  wsprintf(strCompSize,"%ld",ze.comp_size);
  wsprintf(strCrc,"%X",ze.crc);
  v.AddItem(ze.name,zi,0);		
  v.AddSubItem(zi,1,strSize);
  v.AddSubItem(zi,2,strCompSize);
  if((ze.attr & FILE_ATTRIBUTE_DIRECTORY) > 0)
   v.AddSubItem(zi,3,"Directorio");
  else
   v.AddSubItem(zi,3,"Archivo");

  
  v.AddSubItem(zi,4,strTime);
  v.AddSubItem(zi,5,strCrc);
 }
 CloseZip(hz);
 if(strSize!=0)
  delete [] strSize;

 if(strCompSize!=0)
  delete [] strCompSize;

 if(strTime!=0)
  delete [] strTime;

 if(strCrc!=0)
  delete [] strCrc;

 if(strComment!=0)
  delete [] strComment;


 return true;
}