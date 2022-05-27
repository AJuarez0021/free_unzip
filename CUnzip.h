#ifndef __CUNZIP_H
#define __CUNZIP_H

#include <windows.h>
#include "CWnd.h"
#include "CListView.h"
#include "unzip.h"
#include <fstream>
using namespace std;

class CUnzip
{
 private:  
  TCHAR m_strFullPath[MAX_PATH];
  TCHAR m_strBaseDir[MAX_PATH];
  string m_strComment;
  bool ListArchive(string, ofstream &);
 public:

  CUnzip(){
   lstrcpy(m_strFullPath,"");
   lstrcpy(m_strBaseDir,"");  
   m_strComment="";
  }
  ~CUnzip()
  {
   
  }
  void SetPath(string strDir){
   GetCurrentDirectory(MAX_PATH,m_strBaseDir); 
   lstrcpy(m_strFullPath,strDir.c_str());   
  }
  TCHAR *GetFullPath(){
    return m_strFullPath;
  }
  TCHAR *GetBaseDir(){
   return m_strBaseDir;
  }
  
  bool ExtractArchive(string strPathName);
  bool ListArchive(CListView v);
  bool Export(string strOutFile,string InFile,CWnd w);    
  string GetComment(){
   return m_strComment;
  }
};

#endif