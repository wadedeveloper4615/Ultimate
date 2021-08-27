#if !defined(AFX_IMAGEBAR_H__2FD05154_F366_4E31_9AF1_217726BB4300__INCLUDED_)
#define AFX_IMAGEBAR_H__2FD05154_F366_4E31_9AF1_217726BB4300__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ImageBar.h : header file
//

#include "Mbr.h"
#include "fat.h"

/////////////////////////////////////////////////////////////////////////////
// CImageBar window

class CImageBar : public CWnd
{
// Construction
public:
  CImageBar();

// Attributes
public:

// Operations
public:
  void CheckForMBRRecusive(DWORD64 LBA, DWORD64 TotalBlocks);
  
  void ImageParse(CFile *file);
  void ImageParseVolume(const BYTE type, const DWORD64 lba, const DWORD64 size, const DWORD64 TotalBlocks);
  int  DrawBox(DWORD64 start, DWORD64 end, DWORD64 total, DWORD color, BOOL filled, char *title, CPropertyPage *page);
  void Clear(void);
  
  int  DetectFileSystem(const DWORD64 lba, const DWORD64 size);
  int  DetectFat(S_FAT1216_BPB *bpb, const unsigned sect_size);
  unsigned DetectFatSize(S_FAT1216_BPB *bpb);
  int  DetectExt2(void *buffer, const DWORD64 Size, const unsigned sect_size);
  int  DetectExFat(void *buffer);
  int  DetectLean(DWORD64 lba, const unsigned sect_size);
  int  DetectNTFS(void *buffer);
  int  DetectSFS(void *buffer, const unsigned sect_size);
  int  DetectFYSFS(void *buffer, const unsigned sect_size);
  int  DetectFSZ(DWORD64 lba);

// Overrides
  // ClassWizard generated virtual function overrides
  //{{AFX_VIRTUAL(CImageBar)
  //}}AFX_VIRTUAL

// Implementation
public:
  virtual ~CImageBar();

  // Generated message map functions
protected:
  //{{AFX_MSG(CImageBar)
    // NOTE - the ClassWizard will add and remove member functions here.
  //}}AFX_MSG
  DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IMAGEBAR_H__2FD05154_F366_4E31_9AF1_217726BB4300__INCLUDED_)
