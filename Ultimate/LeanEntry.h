#if !defined(AFX_LEANENTRY_H__4FFAF00C_12A4_4350_B5A4_8F7DA054DD6F__INCLUDED_)
#define AFX_LEANENTRY_H__4FFAF00C_12A4_4350_B5A4_8F7DA054DD6F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LeanEntry.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CLeanEntry dialog

class CLeanEntry : public CDialog {
// Construction
public:
  CLeanEntry(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
  //{{AFX_DATA(CLeanEntry)
  enum { IDD = IDD_LEAN_ENTRY };
  CListBox	m_ext_start;
  CListBox	m_ext_size;
  CString	m_acc_time;
  CString	m_attribs;
  CString	m_cre_time;
  CString	m_ext_count;
  CString	m_filesize;
  CString	m_first_ind;
  CString	m_fork;
  CString	m_gid;
  CString	m_ind_count;
  CString	m_last_indirect;
  CString	m_links_count;
  CString	m_magic;
  CString	m_mod_time;
  CString	m_sch_time;
  CString	m_block_count;
  CString	m_uid;
  CString	m_entry_crc;
  CString	m_name;
  //}}AFX_DATA
  
  S_LEAN_INODE m_inode;
  CLean    *m_parent;
  HTREEITEM m_hItem;
  DWORD64 m_inode_num;
  
// Overrides
  // ClassWizard generated virtual function overrides
  //{{AFX_VIRTUAL(CLeanEntry)
  protected:
  virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
  //}}AFX_VIRTUAL

// Implementation
protected:

  // Generated message map functions
  //{{AFX_MSG(CLeanEntry)
  virtual BOOL OnInitDialog();
  afx_msg void OnSelchangeExtStart();
  afx_msg void OnSelchangeExtSize();
  afx_msg void OnAttribute();
  afx_msg void OnCrcUpdate();
  afx_msg void OnAccTimeNow();
  afx_msg void OnCreTimeNow();
  afx_msg void OnModTimeNow();
  afx_msg void OnSchTimeNow();
  afx_msg void OnEas();
  virtual void OnOK();
  //}}AFX_MSG
  DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LEANENTRY_H__4FFAF00C_12A4_4350_B5A4_8F7DA054DD6F__INCLUDED_)
