
// Ultimate.h : main header file for the Ultimate application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


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

#define MAX_DIR_PARSE_DEPTH  75    // max recursive depth we allow
#define MAX_SUB_VOLUMES   16
#define COLOR_ISO    RGB(222, 0, 222)
#define COLOR_MBR    RGB(0, 0, 222)
#define COLOR_GPT    RGB(0, 222, 0)
#define COLOR_EMBR   RGB(222, 0, 0)
#define COLOR_VHD    RGB(222, 111, 0)
#define COLOR_UNKN   RGB(64, 64, 64)
#define COLOR_MBR_EMPTY  RGB(113,111,100)
#define ITEM_IS_FILE    (1<<0)
#define ITEM_IS_FOLDER  (1<<1)
#define ITEM_IS_FORK    (1<<2)
#define  DLG_FILE_TYPE_UNKWN    -1   // unknown file type
#define  DLG_FILE_TYPE_FLAT      0   // flat file, sector for sector file
#define  DLG_FILE_TYPE_UNDOABLE  1   // Bochs Virtual HD : REDOLOG : Undoable
#define  DLG_FILE_TYPE_VOLATILE  2   // Bochs Virtual HD : REDOLOG : Volatile
#define  DLG_FILE_TYPE_GROWING   3   // Bochs Virtual HD : REDOLOG : Growing
#define  DLG_FILE_TYPE_VB_VDI    4   // VirtualBox VDI file (Dynamic)

// CUltimateApp:
// See Ultimate.cpp for the implementation of this class
//

class CUltimateApp : public CWinApp
{
public:
	CUltimateApp() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation

public:
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CUltimateApp theApp;


void DumpIt(CString& csTarg, const void* buffer, DWORD start_addr, unsigned size, BOOL Append);
int ConvertDumpToBuffer(CString csSrc, void* buffer, int max);
BOOL IsBufferEmpty(const void* buffer, const int count);
DWORD64 convert64(CString& csSrc);
DWORD32 convert32(CString& csSrc);
WORD convert16(CString& csSrc);
BYTE convert8(CString& csSrc);

#define CRC32_POLYNOMIAL 0x04C11DB7

void crc32_initialize(void);
DWORD crc32_reflect(DWORD reflect, char ch);
DWORD crc32(void* data, DWORD len);
void crc32_partial(DWORD* crc, void* ptr, DWORD len);
BOOL BrowseForFolder(HWND hwnd, CString& csCurrent, LPTSTR szPath, UINT ulFlags);

typedef struct _S_GUID {
    DWORD  data1;
    WORD   data2;
    WORD   data3;
    WORD   data4;
    BYTE   data5[6];
}S_GUID;

void GUID_Format(CString& csguid, S_GUID* guid);
void GUID_Retrieve(CString& csguid, S_GUID* guid);
BOOL GUID_CheckFormat(CString csguid);

#define GUID_TYPE_MT         0  // Unused Entry 00000000-0000-0000-0000-000000000000
#define GUID_TYPE_EFI        1  // EFI System Partition C12A7328-F81F-11D2-BA4B-00A0C93EC93B
#define GUID_TYPE_LEGACY     2  // Partition containing a legacy MBR 024DEE41-33E7-11D3-9D69-0008C781F39F
#define GUID_TYPE_RANDOM   256  // create a random GUID

void GUID_Create(S_GUID* guid, const DWORD type);
float GetUTCOffset(void);

#define FNM_NOCASE      0x01

BOOL fnmatch(const char* wild_text, const char* tame_text, const DWORD flags);
void gLBAtoCHS(const DWORD lba, WORD* cyl, BYTE* head, BYTE* sect, const DWORD spt, const DWORD heads);
BOOL power_of_two(DWORD val);
