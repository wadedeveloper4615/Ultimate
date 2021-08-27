#if !defined(AFX_FAT32INFO_H__D648F884_0CE9_4945_8F7C_2C6E85AA0A40__INCLUDED_)
#define AFX_FAT32INFO_H__D648F884_0CE9_4945_8F7C_2C6E85AA0A40__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Fat32Info.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFat32Info dialog

class CFat32Info : public CDialog
{
// Construction
public:
  CFat32Info(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
  //{{AFX_DATA(CFat32Info)
  enum { IDD = IDD_FAT32_INFO };
  CString	m_free_count;
  CString	m_next_free;
  CString	m_sig0;
  CString	m_sig1;
  CString	m_sig2;
  CString	m_reserved;
  //}}AFX_DATA
  
  BOOL  m_clear_reserved;
  
// Overrides
  // ClassWizard generated virtual function overrides
  //{{AFX_VIRTUAL(CFat32Info)
  protected:
  virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
  //}}AFX_VIRTUAL

// Implementation
protected:

  // Generated message map functions
  //{{AFX_MSG(CFat32Info)
  afx_msg void OnUpdateFree();
  afx_msg void OnUpdateResved();
  afx_msg void OnUpdateSig0();
  afx_msg void OnUpdateSig1();
  afx_msg void OnUpdateSig2();
  afx_msg void OnChangeInfoSig0();
  afx_msg void OnChangeInfoSig1();
  virtual BOOL OnInitDialog();
  //}}AFX_MSG
  DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FAT32INFO_H__D648F884_0CE9_4945_8F7C_2C6E85AA0A40__INCLUDED_)
