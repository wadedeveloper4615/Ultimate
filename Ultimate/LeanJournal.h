#if !defined(AFX_LEANJOURNAL_H__C9732BA8_60FD_4297_A9D6_24AD243EFB59__INCLUDED_)
#define AFX_LEANJOURNAL_H__C9732BA8_60FD_4297_A9D6_24AD243EFB59__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LeanJournal.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CLeanJournal dialog

class CLeanJournal : public CDialog {
// Construction
public:
  CLeanJournal(CWnd* pParent = NULL);   // standard constructor
  
// Dialog Data
  //{{AFX_DATA(CLeanJournal)
  enum { IDD = IDD_LEAN_JOURNAL };
  CString m_entry_count;
  CString m_flags;
  CString m_crc;
  CString m_magic;
  CString m_new_inode;
  CString m_org_inode;
  CString m_padding;
  CString	m_entry_reserved;
  CString	m_reserved;
  //}}AFX_DATA
  
  void EntrytoDialog();
  void DialogtoEntry();
  
  CLean *m_parent;
  void  *m_buffer;
  int    m_current;
  int    m_count;
  
// Overrides
  // ClassWizard generated virtual function overrides
  //{{AFX_VIRTUAL(CLeanJournal)
  protected:
  virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
  //}}AFX_VIRTUAL

// Implementation
protected:
  // Generated message map functions
  //{{AFX_MSG(CLeanJournal)
  afx_msg void OnClear();
  afx_msg void OnEntryClear();
  afx_msg void OnNext();
  afx_msg void OnPrev();
  afx_msg void OnFlagsB();
  afx_msg void OnLeanCrcUpdate();
  afx_msg void OnLeanMagicUpdate();
  virtual BOOL OnInitDialog();
  //}}AFX_MSG
  DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LEANJOURNAL_H__C9732BA8_60FD_4297_A9D6_24AD243EFB59__INCLUDED_)
