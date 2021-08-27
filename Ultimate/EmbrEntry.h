#if !defined(AFX_EMBRENTRY_H__2599B2C4_469C_4364_95CD_CEF86C95F940__INCLUDED_)
#define AFX_EMBRENTRY_H__2599B2C4_469C_4364_95CD_CEF86C95F940__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// EmbrEntry.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CEmbrEntry dialog

class CEmbrEntry : public CPropertyPage
{
  DECLARE_DYNCREATE(CEmbrEntry)

// Construction
public:
  CEmbrEntry();
  ~CEmbrEntry();

// Dialog Data
  //{{AFX_DATA(CEmbrEntry)
  enum { IDD = IDD_EMBR_ENTRY };
  CString	m_created;
  CString	m_description;
  CString	m_flags;
  CString	m_os_sig;
  CString	m_sectors;
  CString	m_signature;
  CString	m_start_lba;
  CString	m_last_booted;
  CString	m_reserved;
  //}}AFX_DATA
  
  void  *m_entry_buffer;
  
  CString m_Title;
  int    m_index;
  BOOL   m_dirty;
  
// Overrides
  // ClassWizard generate virtual function overrides
  //{{AFX_VIRTUAL(CEmbrEntry)
  protected:
  virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
  //}}AFX_VIRTUAL

// Implementation
public:
  // Generated message map functions
  //{{AFX_MSG(CEmbrEntry)
  afx_msg void OnEmbreApply();
  afx_msg void OnEsigSet();
  afx_msg void OnFlagsSet();
  afx_msg void OnTabItemChange();
  afx_msg void OnEmbrClearResv();
  afx_msg void OnEdateNow();
  afx_msg void OnEbootNow();
  //}}AFX_MSG
  DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EMBRENTRY_H__2599B2C4_469C_4364_95CD_CEF86C95F940__INCLUDED_)
