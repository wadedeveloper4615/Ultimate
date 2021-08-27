#if !defined(AFX_MODELESS_H__D2045E36_6220_4E04_A050_E574E637A6D2__INCLUDED_)
#define AFX_MODELESS_H__D2045E36_6220_4E04_A050_E574E637A6D2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Modeless.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CModeless dialog

class CModeless : public CDialog {
// Construction
public:
  CModeless(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
  //{{AFX_DATA(CModeless)
  enum { IDD = IDD_MODELESS };
  CString	m_edit;
  //}}AFX_DATA
  
  BOOL m_modeless;
  CString m_Title;
  
// Overrides
  // ClassWizard generated virtual function overrides
  //{{AFX_VIRTUAL(CModeless)
  protected:
  virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
  //}}AFX_VIRTUAL
  
// Implementation
protected:
  
  // Generated message map functions
  //{{AFX_MSG(CModeless)
  afx_msg void OnDone();
  afx_msg void OnCopy();
  virtual BOOL OnInitDialog();
  //}}AFX_MSG
  DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MODELESS_H__D2045E36_6220_4E04_A050_E574E637A6D2__INCLUDED_)
