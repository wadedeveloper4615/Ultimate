// ultimate.h : main header file for the ULTIMATE application
//

#if !defined(AFX_ULTIMATE_H__54500165_D296_435D_B65D_3F50E4759072__INCLUDED_)
#define AFX_ULTIMATE_H__54500165_D296_435D_B65D_3F50E4759072__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
  #error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

#include <math.h>
#define LOG2(x) (int) (log((double) (x)) / log(2.0))  // log2(x) = log(x) / log(2.0)

#define MAX_SECT_SIZE   4096

// different FSs we support
#define FS_LEAN     1
#define FS_EXT2     2
#define FS_SFS      3
#define FS_NTFS     4
#define FS_EXFAT   11
#define FS_FAT12   12
#define FS_FAT16   16
#define FS_FYSFS   22
#define FS_FAT32   32
#define FS_FSZ     90

#define ENDIAN_16U(x)   ((((x) & 0xFF) << 8) | (((x) & 0xFF00) >> 8))
#define ENDIAN_32U(x)   ((((x) & 0xFF) << 24) | (((x) & 0xFF00) << 8) | (((x) & 0xFF0000) >> 8) | (((x) & 0xFF000000) >> 24))
#define ENDIAN_64U(x)   (                                              \
                         ((DWORD64) ((x) & 0x00000000000000FF) << 56) | \
                         ((DWORD64) ((x) & 0x000000000000FF00) << 40) | \
                         ((DWORD64) ((x) & 0x0000000000FF0000) << 24) | \
                         ((DWORD64) ((x) & 0x00000000FF000000) <<  8) | \
                         ((DWORD64) ((x) & 0x000000FF00000000) >>  8) | \
                         ((DWORD64) ((x) & 0x0000FF0000000000) >> 24) | \
                         ((DWORD64) ((x) & 0x00FF000000000000) >> 40) | \
                         ((DWORD64) ((x) & 0xFF00000000000000) >> 56)   \
                        )

/////////////////////////////////////////////////////////////////////////////
// CUltimateApp:
// See ultimate.cpp for the implementation of this class
//

class CUltimateApp : public CWinAppEx {
public:
  CUltimateApp();

// Overrides
  // ClassWizard generated virtual function overrides
  //{{AFX_VIRTUAL(CUltimateApp)
  public:
  virtual BOOL InitInstance();
  //}}AFX_VIRTUAL
  
// Implementation
  
  //{{AFX_MSG(CUltimateApp)
  //}}AFX_MSG
  DECLARE_MESSAGE_MAP()
};

void DumpIt(CString &csTarg, const void *buffer, DWORD start_addr, unsigned size, BOOL Append);
int ConvertDumpToBuffer(CString csSrc, void *buffer, int max);
BOOL IsBufferEmpty(const void *buffer, const int count);

/////////////////////////////////////////////////////////////////////////////

DWORD64 convert64(CString &csSrc);
DWORD32 convert32(CString &csSrc);
WORD convert16(CString &csSrc);
BYTE convert8(CString &csSrc);

/////////////////////////////////////////////////////////////////////////////

#define CRC32_POLYNOMIAL 0x04C11DB7

void crc32_initialize(void);
DWORD crc32_reflect(DWORD reflect, char ch);
DWORD crc32(void *data, DWORD len);
void crc32_partial(DWORD *crc, void *ptr, DWORD len);

/////////////////////////////////////////////////////////////////////////////

BOOL BrowseForFolder(HWND hwnd, CString &csCurrent, LPTSTR szPath, UINT ulFlags);

/////////////////////////////////////////////////////////////////////////////

// ex: 3F2504E0-4F89-11D3-9A0C-0305E82C3301
//       data1    2    3    4     5[6]
typedef struct _S_GUID {
  DWORD  data1;
  WORD   data2;
  WORD   data3;
  WORD   data4;
  BYTE   data5[6];
}S_GUID;

void GUID_Format(CString &csguid, S_GUID *guid);
void GUID_Retrieve(CString &csguid, S_GUID *guid);
BOOL GUID_CheckFormat(CString csguid);

#define GUID_TYPE_MT         0  // Unused Entry 00000000-0000-0000-0000-000000000000
#define GUID_TYPE_EFI        1  // EFI System Partition C12A7328-F81F-11D2-BA4B-00A0C93EC93B
#define GUID_TYPE_LEGACY     2  // Partition containing a legacy MBR 024DEE41-33E7-11D3-9D69-0008C781F39F

#define GUID_TYPE_RANDOM   256  // create a random GUID

void GUID_Create(S_GUID *guid, const DWORD type);

/////////////////////////////////////////////////////////////////////////////

#include "MyTreeCtrl.h"

void ExpandIt(CMyTreeCtrl *dir_tree, BOOL Expand);

/////////////////////////////////////////////////////////////////////////////

float GetUTCOffset(void);

/////////////////////////////////////////////////////////////////////////////

#define FNM_NOCASE      0x01
BOOL fnmatch(const char *wild_text, const char *tame_text, const DWORD flags);

/////////////////////////////////////////////////////////////////////////////
void gLBAtoCHS(const DWORD lba, WORD *cyl, BYTE *head, BYTE *sect, const DWORD spt, const DWORD heads);

/////////////////////////////////////////////////////////////////////////////
BOOL power_of_two(DWORD val);

/////////////////////////////////////////////////////////////////////////////



//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ULTIMATE_H__54500165_D296_435D_B65D_3F50E4759072__INCLUDED_)
