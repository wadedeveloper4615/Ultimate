#if !defined(AFX_GPT_GUID_TYPE_H__0DCE1553_D1BF_40FF_BF2E_BEBB78D70642__INCLUDED_)
#define AFX_GPT_GUID_TYPE_H__0DCE1553_D1BF_40FF_BF2E_BEBB78D70642__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CGUIDType dialog

class CGUIDType : public CDialog {
// Construction
public:
  CGUIDType(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
  //{{AFX_DATA(CGUIDType)
  enum { IDD = IDD_GPT_GUID };
  CListBox m_list;
  CFont m_font;
  bool m_list_type;  // 1 = type, 0 = guid
  CString m_title;
  CString m_type;
  //}}AFX_DATA
  
// Overrides
  // ClassWizard generated virtual function overrides
  //{{AFX_VIRTUAL(CGUIDType)
  protected:
  virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
  //}}AFX_VIRTUAL

// Implementation
protected:

  // Generated message map functions
  //{{AFX_MSG(CLeanTime)
  virtual BOOL OnInitDialog();
  virtual void OnOK();
  //}}AFX_MSG
  DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GPT_GUID_TYPE_H__0DCE1553_D1BF_40FF_BF2E_BEBB78D70642__INCLUDED_)
