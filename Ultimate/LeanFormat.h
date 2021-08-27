#if !defined(AFX_LEANFORMAT_H__FCDC8D1D_E440_4FDF_B9A1_842F69522B5F__INCLUDED_)
#define AFX_LEANFORMAT_H__FCDC8D1D_E440_4FDF_B9A1_842F69522B5F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LeanFormat.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CLeanFormat dialog

class CLeanFormat : public CDialog {
// Construction
public:
  CLeanFormat(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
  //{{AFX_DATA(CLeanFormat)
  enum { IDD = IDD_LEAN_FORMAT };
  DWORD m_block_size;
  int   m_pre_alloc_count;
  BOOL	m_eas_after_inode;
  BOOL	m_journal;
  //}}AFX_DATA


// Overrides
  // ClassWizard generated virtual function overrides
  //{{AFX_VIRTUAL(CLeanFormat)
  protected:
  virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
  //}}AFX_VIRTUAL

// Implementation
protected:

  // Generated message map functions
  //{{AFX_MSG(CLeanFormat)
  afx_msg void OnOkay();
  //}}AFX_MSG
  DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LEANFORMAT_H__FCDC8D1D_E440_4FDF_B9A1_842F69522B5F__INCLUDED_)
