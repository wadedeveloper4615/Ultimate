#if !defined(AFX_OURFIND_H__9B7959E2_ECB7_492A_99A9_92F47E468B2C__INCLUDED_)
#define AFX_OURFIND_H__9B7959E2_ECB7_492A_99A9_92F47E468B2C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// OurFind.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// COurFind dialog

class COurFind : public CDialog {
// Construction
public:
  COurFind(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
  //{{AFX_DATA(COurFind)
  enum { IDD = IDD_FIND };
  BOOL  m_match_case;
  CString m_find_str;
  //}}AFX_DATA


// Overrides
  // ClassWizard generated virtual function overrides
  //{{AFX_VIRTUAL(COurFind)
  protected:
  virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
  //}}AFX_VIRTUAL

// Implementation
protected:

  // Generated message map functions
  //{{AFX_MSG(COurFind)
  //}}AFX_MSG
  DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OURFIND_H__9B7959E2_ECB7_492A_99A9_92F47E468B2C__INCLUDED_)
