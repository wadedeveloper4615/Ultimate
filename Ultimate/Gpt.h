#if !defined(AFX_GPT_H__A4B5F5F6_FC0E_4DE0_BBB3_E9C5A9C583A6__INCLUDED_)
#define AFX_GPT_H__A4B5F5F6_FC0E_4DE0_BBB3_E9C5A9C583A6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Gpt.h : header file
//

#include "GptEntry.h"

#pragma pack(push, 1)

// EFI GUID Partition Table
// page 11-9 of EFISpec_v110.pdf
typedef struct _S_GPT_HDR {
  BYTE    sig[8];
  DWORD   version;
  DWORD   hdr_size;
  DWORD   crc32;   // only bytes 0 -> hdr_size are checked
  DWORD   resv0;
  DWORD64 primary_lba;  // my LBA
  DWORD64 backup_lba;   // alternate LBA
  DWORD64 first_usable;
  DWORD64 last_usable;
  S_GUID guid;
  DWORD64 entry_offset;
  DWORD   entries;
  DWORD   entry_size;
  DWORD   crc32_entries;
  BYTE    reserved[420];
}S_GPT_HDR;

typedef struct _S_GPT_ENTRY1 {
  S_GUID guid_type;
  S_GUID guid;
  DWORD64 first_lba;
  DWORD64 last_lba;
  DWORD64 attribute;
  WORD    name[36];
}S_GPT_ENTRY;

#pragma pack(pop)

#define MAX_GPT_ENTRIES  16

/////////////////////////////////////////////////////////////////////////////
// CGpt dialog

class CGpt : public CPropertyPage
{
  DECLARE_DYNCREATE(CGpt)

// Construction
public:
  CGpt();
  ~CGpt();
  
  bool Exists(DWORD64 LBA);
  void Begin(void);
  void UpdateEntry(CGptEntry *Entry, int index, const int entry_size);
  BOOL CheckEntry(int index);
  void Destroy(void);
  
  void GetGPTHdr(void);
  void GetGPTEntries(void);
  BOOL CheckGPT(DWORD64 LBA, BOOL CheckAlternate);

  bool  m_exists;
  DWORD m_color;
  DWORD64 m_lba;
  int   m_draw_index;
  
  BYTE   m_buffer[MAX_SECT_SIZE];
  S_GPT_HDR m_hdr;
  S_GPT_ENTRY *m_entry_buffer;
  int    m_gpt_entries;
  
  CPropertySheet m_Sheet;
  CGptEntry  m_Pages[MAX_GPT_ENTRIES];
  
// Dialog Data
  //{{AFX_DATA(CGpt)
  enum { IDD = IDD_GPT };
  CStatic	m_gpt_pages;
  CString	m_GptDump;
  CString	m_backup_lba;
  CString	m_crc32;
  CString	m_entry_count;
  CString	m_entry_crc32;
  CString	m_entry_offset;
  CString	m_entry_size;
  CString	m_first_lba;
  CString	m_gpt_guid;
  CString	m_hdr_size;
  CString	m_last_lba;
  CString	m_primary_lba;
  CString	m_rsvd;
  CString	m_gpt_sig;
  CString	m_gpt_version;
  CString	m_sig_chars;
  CString	m_version_num;
  //}}AFX_DATA


// Overrides
  // ClassWizard generate virtual function overrides
  //{{AFX_VIRTUAL(CGpt)
  protected:
  virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
  //}}AFX_VIRTUAL

// Implementation
protected:
  // Generated message map functions
  //{{AFX_MSG(CGpt)
  virtual BOOL OnInitDialog();
  afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
  afx_msg void OnCrcButton();
  afx_msg void OnKillfocusGptGuid();
  afx_msg void OnGuidCreate();
  afx_msg void OnGPTBackup();
  afx_msg void OnGPTFromBackup();
  afx_msg void OnGPTTotalCheck();
public:
  afx_msg void OnGptApply();
  afx_msg void OnEcrcButton();
  //}}AFX_MSG
  DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GPT_H__A4B5F5F6_FC0E_4DE0_BBB3_E9C5A9C583A6__INCLUDED_)
