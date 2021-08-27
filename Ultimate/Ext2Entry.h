#if !defined(AFX_EXT2ENTRY_H__E6C0906E_1857_40F2_9C96_3930B8789565__INCLUDED_)
#define AFX_EXT2ENTRY_H__E6C0906E_1857_40F2_9C96_3930B8789565__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Ext2Entry.h : header file
//

#include "Ext2.h"

/////////////////////////////////////////////////////////////////////////////
// CExt2Entry dialog

class CExt2Entry : public CDialog {
// Construction
public:
  CExt2Entry(CWnd* pParent = NULL);   // standard constructor
  
// Dialog Data
  //{{AFX_DATA(CExt2Entry)
  enum { IDD = IDD_EXT2_ENTRY };
  CListBox  m_list;
  CString m_atime;
  CString m_blocks;
  CString m_ctime;
  CString m_dir_acl;
  CString m_dtime;
  CString m_f_addr;
  CString m_file_acl;
  CString m_flags;
  CString m_generation;
  CString m_gid;
  CString m_link_count;
  CString m_mode;
  CString m_mtime;
  CString m_osd1;
  CString m_size;
  CString m_uid;
  CString m_sym_link;
  CString m_dbl_indirect;
  CString m_depth;
  CString m_entries;
  CString m_extent_gen;
  CString m_indirect;
  CString m_magic;
  CString m_max;
  CString m_trp_indirect;
  //}}AFX_DATA
  
  S_EXT2_INODE m_inode;
  unsigned m_sectors_per_block;
  
// Overrides
  // ClassWizard generated virtual function overrides
  //{{AFX_VIRTUAL(CExt2Entry)
  protected:
  virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
  //}}AFX_VIRTUAL

// Implementation
protected:

  // Generated message map functions
  //{{AFX_MSG(CExt2Entry)
  virtual BOOL OnInitDialog();
  virtual void OnOK();
  afx_msg void OnDomode();
  afx_msg void OnDoflags();
  afx_msg void OnAccTimeNow();
  afx_msg void OnCreTimeNow();
  afx_msg void OnModTimeNow();
  afx_msg void OnDelTimeNow();
  //}}AFX_MSG
  DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EXT2ENTRY_H__E6C0906E_1857_40F2_9C96_3930B8789565__INCLUDED_)
