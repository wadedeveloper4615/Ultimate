#if !defined(AFX_LEANTIME_H__0DCE1553_D1BF_40FF_BF2E_BEBB78D70642__INCLUDED_)
#define AFX_LEANTIME_H__0DCE1553_D1BF_40FF_BF2E_BEBB78D70642__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LeanTime.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CLeanTime dialog

class CLeanTime : public CDialog {
// Construction
public:
  CLeanTime(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
  //{{AFX_DATA(CLeanTime)
  enum { IDD = IDD_LEAN_TIME };
  CString	m_lean_time;
  //}}AFX_DATA
  
  CString m_title;
  DWORD m_divisor;
  INT32 m_adjustment;
  
// Overrides
  // ClassWizard generated virtual function overrides
  //{{AFX_VIRTUAL(CLeanTime)
  protected:
  virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
  //}}AFX_VIRTUAL

// Implementation
protected:

  // Generated message map functions
  //{{AFX_MSG(CLeanTime)
  virtual BOOL OnInitDialog();
  afx_msg void OnChangeLeanTime();
  afx_msg void OnTimeNow();
  //}}AFX_MSG
  DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LEANTIME_H__0DCE1553_D1BF_40FF_BF2E_BEBB78D70642__INCLUDED_)
