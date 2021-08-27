#if !defined(AFX_ATTRIBUTE_H__5D0433D7_6136_4937_9034_53E1240E8037__INCLUDED_)
#define AFX_ATTRIBUTE_H__5D0433D7_6136_4937_9034_53E1240E8037__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Attribute.h : header file
//

typedef struct _S_ATTRIBUTES {
  DWORD64 attrb;
  DWORD64 mask;
  int   index;
  char  str[32];
  int   groups[10];  // up to 10 items can be grouped.  Increase if we need more.
} S_ATTRIBUTES;

/////////////////////////////////////////////////////////////////////////////
// CAttribute dialog

class CAttribute : public CDialog {
// Construction
public:
  CAttribute(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
  //{{AFX_DATA(CAttribute)
  enum { IDD = IDD_ATTRIBUTE };
  CListBox	m_list;
  //}}AFX_DATA
  
  CString m_title;
  BOOL    m_single;
  DWORD64 m_attrib;
  S_ATTRIBUTES *m_attributes;
  
// Overrides
  // ClassWizard generated virtual function overrides
  //{{AFX_VIRTUAL(CAttribute)
  protected:
  virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
  //}}AFX_VIRTUAL
  
// Implementation
protected:
  
  // Generated message map functions
  //{{AFX_MSG(CAttribute)
  virtual BOOL OnInitDialog();
  virtual void OnOK();
  afx_msg void OnSelchangeList();
  //}}AFX_MSG
  DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ATTRIBUTE_H__5D0433D7_6136_4937_9034_53E1240E8037__INCLUDED_)
