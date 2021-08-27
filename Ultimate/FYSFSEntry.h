#if !defined(AFX_FYSFSENTRY_H__77907422_FB54_49BD_A3D2_B88DBDC629C3__INCLUDED_)
#define AFX_FYSFSENTRY_H__77907422_FB54_49BD_A3D2_B88DBDC629C3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FYSFSEntry.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFYSFSEntry dialog

class CFYSFSEntry : public CDialog
{
// Construction
public:
  CFYSFSEntry(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
  //{{AFX_DATA(CFYSFSEntry)
  enum { IDD = IDD_FYSFS_ENTRY };
  CString	m_attribute;
  CString	m_crc;
  CString	m_created;
  CString	m_fat_cont;
  CString	m_fat_entries;
  CString	m_file_size;
  CString	m_flags;
  CString	m_last_access;
  CString	m_name_cont;
  CString	m_name_fat;
  CString	m_name_len;
  CString	m_scratch;
  CString	m_slot_type;
  //}}AFX_DATA
  
  DWORD m_Sig;
  
// Overrides
  // ClassWizard generated virtual function overrides
  //{{AFX_VIRTUAL(CFYSFSEntry)
  protected:
  virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
  //}}AFX_VIRTUAL

// Implementation
protected:

  // Generated message map functions
  //{{AFX_MSG(CFYSFSEntry)
  afx_msg void OnCreated();
  afx_msg void OnLastAccess();
  //}}AFX_MSG
  DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FYSFSENTRY_H__77907422_FB54_49BD_A3D2_B88DBDC629C3__INCLUDED_)
