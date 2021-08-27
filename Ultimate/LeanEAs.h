#if !defined(AFX_LEANEAS_H__121D5E71_F101_405D_98E2_E916BD5C2C27__INCLUDED_)
#define AFX_LEANEAS_H__121D5E71_F101_405D_98E2_E916BD5C2C27__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LeanEAs.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CLeanEAs dialog

class CLeanEAs : public CDialog {
// Construction
public:
  CLeanEAs(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
  //{{AFX_DATA(CLeanEAs)
  enum { IDD = IDD_LEAN_EAS };
  CListBox	m_list;
  int		m_as_utf8;
  CString	m_name;
  CString	m_attrib_as_byte;
  CString	m_attrib_as_utf8;
  CString	m_attrib_as_value;
  BOOL	m_force_fork;
  //}}AFX_DATA
  
  S_EA_STRUCT *m_ea_struct;
  int m_count;
  
// Overrides
  // ClassWizard generated virtual function overrides
  //{{AFX_VIRTUAL(CLeanEAs)
  protected:
  virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
  //}}AFX_VIRTUAL
  
// Implementation
protected:
  
  // Generated message map functions
  //{{AFX_MSG(CLeanEAs)
  virtual BOOL OnInitDialog();
  afx_msg void OnSelchangeList();
  afx_msg void OnAdd();
  afx_msg void OnAsChange();
  afx_msg void OnDelete();
  afx_msg void OnDone();
  afx_msg void OnApply();
  //}}AFX_MSG
  DECLARE_MESSAGE_MAP()
  
  void UpdateMembers(const int index);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LEANEAS_H__121D5E71_F101_405D_98E2_E916BD5C2C27__INCLUDED_)
