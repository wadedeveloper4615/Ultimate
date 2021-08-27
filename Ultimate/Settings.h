#if !defined(AFX_SETTINGS_H__E1BCB50E_44E3_48A0_811C_8F3ECB3E73E5__INCLUDED_)
#define AFX_SETTINGS_H__E1BCB50E_44E3_48A0_811C_8F3ECB3E73E5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Settings.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSettings dialog

class CSettings : public CDialog
{
// Construction
public:
  CSettings(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
  //{{AFX_DATA(CSettings)
  enum { IDD = IDD_SETTINGS };
  int   m_max_error_count;
  CString m_mbr_path;
  CString m_embr_path;
  int   m_force_readonly;
  BOOL  m_clear_mru;
  CString m_extract_path;
  CString	m_help_path;
  BOOL	m_force_fysos;
  //}}AFX_DATA


// Overrides
  // ClassWizard generated virtual function overrides
  //{{AFX_VIRTUAL(CSettings)
  protected:
  virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
  //}}AFX_VIRTUAL

// Implementation
protected:

  // Generated message map functions
  //{{AFX_MSG(CSettings)
  afx_msg void OnMbrPathBrz();
  afx_msg void OnEmbrPathBrz();
  afx_msg void OnExtractPathBrz();
  //}}AFX_MSG
  DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SETTINGS_H__E1BCB50E_44E3_48A0_811C_8F3ECB3E73E5__INCLUDED_)
