#if !defined(AFX_ISOENTRY_H__42BA9B80_467C_46ED_B4B3_84C5D9C39A11__INCLUDED_)
#define AFX_ISOENTRY_H__42BA9B80_467C_46ED_B4B3_84C5D9C39A11__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ISOEntry.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CISOEntry dialog

class CISOEntry : public CDialog {
// Construction
public:
  CISOEntry(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
  //{{AFX_DATA(CISOEntry)
  enum { IDD = IDD_ISO_ENTRY };
  CString	m_attribute;
  CString	m_data_len;
  CString	m_extent_loc;
  CString	m_fi_len;
  CString	m_flags;
  CString	m_gap_size;
  CString	m_ident;
  CString	m_length;
  CString	m_sequ_num;
  CString	m_unit_size;
  int		m_day;
  int		m_gmt_off;
  int		m_hour;
  int		m_minute;
  int		m_month;
  int		m_second;
  int		m_year;
  CString	m_ident_extra;
  //}}AFX_DATA
  int   m_ident_extra_cnt;

// Overrides
  // ClassWizard generated virtual function overrides
  //{{AFX_VIRTUAL(CISOEntry)
  protected:
  virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
  //}}AFX_VIRTUAL

// Implementation
protected:

  // Generated message map functions
  //{{AFX_MSG(CISOEntry)
  afx_msg void OnFlagsB();
  virtual BOOL OnInitDialog();
  afx_msg void OnExtraCopy();
  //}}AFX_MSG
  DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ISOENTRY_H__42BA9B80_467C_46ED_B4B3_84C5D9C39A11__INCLUDED_)
