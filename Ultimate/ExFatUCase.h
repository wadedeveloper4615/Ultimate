#if !defined(AFX_EXFATUCASE_H__A42B4056_DBD0_4570_8212_3714A2214D37__INCLUDED_)
#define AFX_EXFATUCASE_H__A42B4056_DBD0_4570_8212_3714A2214D37__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ExFatUCase.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CExFatUCase dialog

class CExFatUCase : public CDialog {
// Construction
public:
  CExFatUCase(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
  //{{AFX_DATA(CExFatUCase)
  enum { IDD = IDD_EXFAT_UCASE };
  CScrollBar  m_scroll;
  //}}AFX_DATA
  
  void SetValues(const DWORD start);
  
  void *m_buffer;
  DWORD m_data_len;
  DWORD m_count;
  int   m_current;
  
// Overrides
  // ClassWizard generated virtual function overrides
  //{{AFX_VIRTUAL(CExFatUCase)
  protected:
  virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
  //}}AFX_VIRTUAL

// Implementation
protected:

  // Generated message map functions
  //{{AFX_MSG(CExFatUCase)
  virtual BOOL OnInitDialog();
  afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
  afx_msg void OnChangeChar(UINT nID);
  //}}AFX_MSG
  DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EXFATUCASE_H__A42B4056_DBD0_4570_8212_3714A2214D37__INCLUDED_)
