// ultimateDlg.h : header file
//

#if !defined(AFX_ULTIMATEDLG_H__8FB0EAE1_2647_4C69_B0E2_1A5D2D8A0E33__INCLUDED_)
#define AFX_ULTIMATEDLG_H__8FB0EAE1_2647_4C69_B0E2_1A5D2D8A0E33__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "afxadv.h"

#include "ImageBar.h"
#include "MyStatic.h"

#include "ISOImage.h"
#include "Mbr.h"
#include "Gpt.h"
#include "Embr.h"
#include "VHD.h"

#include "Fat.h"
#include "Lean.h"
#include "SFS.h"
#include "FYSFS.h"
#include "Ext2.h"
#include "ExFat.h"
#include "NTFS.h"
#include "fsz.h"

#include "Unknown.h"
#include "VDI.h"

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

/////////////////////////////////////////////////////////////////////////////
// CUltimateDlg dialog

#define  DLG_FILE_TYPE_UNKWN    -1   // unknown file type
#define  DLG_FILE_TYPE_FLAT      0   // flat file, sector for sector file
#define  DLG_FILE_TYPE_UNDOABLE  1   // Bochs Virtual HD : REDOLOG : Undoable
#define  DLG_FILE_TYPE_VOLATILE  2   // Bochs Virtual HD : REDOLOG : Volatile
#define  DLG_FILE_TYPE_GROWING   3   // Bochs Virtual HD : REDOLOG : Growing
#define  DLG_FILE_TYPE_VB_VDI    4   // VirtualBox VDI file (Dynamic)


class CUltimateDlg : public CDialog {
// Construction
public:
  CUltimateDlg(CWnd* pParent = NULL); // standard constructor
  
// Dialog Data
  //{{AFX_DATA(CUltimateDlg)
  enum { IDD = IDD_ULTIMATE_DIALOG };
  CMyStatic m_image_bar;
  CStatic m_StaticTabs;
  CPropertySheet m_TabControl;
  BOOL  m_force_gpt_presence;
  BOOL  m_force_mbr_presence;
  BOOL  m_force_gpt_enum;
  BOOL  m_ignore_empty_gpt_entries;
  BOOL  m_force_readonly;
  unsigned m_sect_size;
  int   m_sect_size_option;
  BOOL	m_force_no_mbr_presence;
  //}}AFX_DATA
  
  unsigned int m_dflt_sect_size;
  
  CFont m_DumpFont;
  
  CMbr  Mbr[MAX_SUB_VOLUMES];
  int  m_MBRCount;
  
  CGpt  Gpt;
  CEmbr Embr;
  
  BOOL  m_hasVHD;
  CVHD  VHD;
  
  BOOL  m_isISOImage;
  CISOImage ISO;
  
  CFat Fat[MAX_SUB_VOLUMES];
  CString m_FatNames[MAX_SUB_VOLUMES];
  int  m_FatCount;
  
  CLean Lean[MAX_SUB_VOLUMES];
  CString m_LeanNames[MAX_SUB_VOLUMES];
  int  m_LeanCount;
  
  CNTFS NTFS[MAX_SUB_VOLUMES];
  CString m_NTFSNames[MAX_SUB_VOLUMES];
  int  m_NTFSCount;
  
  CSFS SFS[MAX_SUB_VOLUMES];
  CString m_SFSNames[MAX_SUB_VOLUMES];
  int  m_SFSCount;
  
  CFYSFS FYSFS[MAX_SUB_VOLUMES];
  CString m_FYSNames[MAX_SUB_VOLUMES];
  int  m_FYSCount;
  
  CExt2 Ext2[MAX_SUB_VOLUMES];
  CString m_Ext2Names[MAX_SUB_VOLUMES];
  int  m_Ext2Count;
  
  CExFat ExFat[MAX_SUB_VOLUMES];
  CString m_ExFatNames[MAX_SUB_VOLUMES];
  int  m_ExFatCount;

  CFSZ FSZ[MAX_SUB_VOLUMES];
  CString m_FSZNames[MAX_SUB_VOLUMES];
  int  m_FSZCount;
  
  CUnknown Unknown[MAX_SUB_VOLUMES];
  int  m_UCount;
  
  int   m_file_type;  // type of file we are accessing
  int   DetFileType(void);
  
  void FileOpen(CString csPath);
  int GetString(char *buffer, CString &str);
  BOOL FileOpenInfo(CString csPath);
  LARGE_INTEGER GetFileLength(HANDLE hFile);
  DWORD64 GetFileSectCount(void);
  BOOL SetFileLength(HANDLE hFile, const DWORD64 Size);
  long ReadFromFile(void *buffer, DWORD64 lba, long count);
  void WriteToFile(void *buffer, DWORD64 lba, long count);
  void ReadBlocks(void *buffer, DWORD64 base, DWORD64 block, DWORD block_size, long count);
  void WriteBlocks(void *buffer, DWORD64 base, DWORD64 block, DWORD block_size, long count);
  void InsertSectors(const DWORD64 lba, const long count);
  void RemoveSectors(const DWORD64 lba, const long count);
  
  BOOL UpdateSig(DWORD64 lba);

  // ClassWizard generated virtual function overrides
  //{{AFX_VIRTUAL(CUltimateDlg)
protected:
  virtual void DoDataExchange(CDataExchange* pDX);  // DDX/DDV support
  //}}AFX_VIRTUAL
  
// Implementation
public:  // protected:
  HICON m_hIcon;
  
  CImageBar m_ImageBar;
  
  bool    m_bIsOpen;
  CString m_cur_file;
  CFile   m_file;
  LARGE_INTEGER m_file_length;
  bool    m_overwrite_okay;

  // VDI stuff
  int     vdi_open_file(VDI_HEADER *vdi_header);
  void    vdi_close_file();
  DWORD   m_vdi_image_type;
  DWORD   m_vdi_image_flags;
  DWORD   m_vdi_offset_blocks;
  DWORD64 m_vdi_offset_data;
  DWORD64 m_vdi_disk_size;
  DWORD   m_vdi_block_size;
  DWORD   m_vdi_block_count;   // fixed.  Count of total blocks in file that can be used/allocated
  DWORD   m_vdi_blocks_allocated;
  DWORD   *m_vdi_blocks;
  BOOL    m_vdi_table_dirty;

  
  CRecentFileList *m_rfl;
  void UpdateMenu(CMenu *pMenu, UINT nIndex);
  void AddToMRUList(CString csPath);
  void RemoveFromMRUList(CString csPath);
  
  // Generated message map functions
  //{{AFX_MSG(CUltimateDlg)
  virtual BOOL OnInitDialog();
  afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
  afx_msg void OnPaint();
  afx_msg HCURSOR OnQueryDragIcon();
  afx_msg void OnFileNew();
  afx_msg void OnFileOpen();
  afx_msg void OnFileClose();
  afx_msg void OnFileReload();
  afx_msg void OnFileExit();
  afx_msg void OnToolsResize();
  afx_msg void OnToolsGetDisk();
  afx_msg void OnToolsAppendVHD();
  afx_msg void OnToolsErase();
  afx_msg void OnViewVDIHeader();
  afx_msg void OnToolsHybridCDROM();
  afx_msg void OnHelpHelp();
  afx_msg void OnHelpAbout();
  afx_msg void OnChangeSectSize();
  afx_msg void OnRecentFileMenu(UINT uID);
  afx_msg void OnInitMenuPopup(CMenu *pMenu, UINT nIndex, BOOL bSysMenu);
  afx_msg void OnAppSettings();
  afx_msg void OnUpdateFileMRUFile1(CCmdUI* pCmdUI);
  afx_msg void OnForceMbr();
  afx_msg void OnForceNoMbr();
  //}}AFX_MSG
  DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ULTIMATEDLG_H__8FB0EAE1_2647_4C69_B0E2_1A5D2D8A0E33__INCLUDED_)
