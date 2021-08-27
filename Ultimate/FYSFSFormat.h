#if !defined(AFX_FYSFSFORMAT_H__900DB027_8CEC_48BA_9C49_40EA8CC45E26__INCLUDED_)
#define AFX_FYSFSFORMAT_H__900DB027_8CEC_48BA_9C49_40EA8CC45E26__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FYSFSFormat.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFYSFSFormat dialog

class CFYSFSFormat : public CDialog {
// Construction
public:
  CFYSFSFormat(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
  //{{AFX_DATA(CFYSFSFormat)
  enum { IDD = IDD_FYSFS_FORMAT };
  int   m_num_bitmaps;
  int   m_root_entries;
  int   m_sect_cluster;
  BOOL  m_case_sensitive;
  BOOL  m_has_super_backup;
  CString m_info;
  //}}AFX_DATA

// Overrides
  // ClassWizard generated virtual function overrides
  //{{AFX_VIRTUAL(CFYSFSFormat)
  protected:
  virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
  //}}AFX_VIRTUAL

// Implementation
protected:

  // Generated message map functions
  //{{AFX_MSG(CFYSFSFormat)
  virtual void OnOK();
  virtual BOOL OnInitDialog();
  //}}AFX_MSG
  DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FYSFSFORMAT_H__900DB027_8CEC_48BA_9C49_40EA8CC45E26__INCLUDED_)
