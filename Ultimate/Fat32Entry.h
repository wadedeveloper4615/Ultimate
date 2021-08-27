#if !defined(AFX_FAT32ENTRY_H__52D84A5B_EF59_4192_90CB_D82F6F15FD14__INCLUDED_)
#define AFX_FAT32ENTRY_H__52D84A5B_EF59_4192_90CB_D82F6F15FD14__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Fat32Entry.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFat32Entry dialog

class CFat32Entry : public CDialog
{
// Construction
public:
  CFat32Entry(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
  //{{AFX_DATA(CFat32Entry)
  enum { IDD = IDD_FAT32_ENTRY };
  CString	m_cluster;
  CString	m_date;
  CString	m_last_acc;
  CString	m_nt_resv;
  CString	m_tenth;
  CString	m_time;
  //}}AFX_DATA
  
// Overrides
  // ClassWizard generated virtual function overrides
  //{{AFX_VIRTUAL(CFat32Entry)
  protected:
  virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
  //}}AFX_VIRTUAL

// Implementation
protected:

  // Generated message map functions
  //{{AFX_MSG(CFat32Entry)
  afx_msg void OnUpdateDate();
  afx_msg void OnUpdateLast();
  afx_msg void OnUpdateTime();
  afx_msg void OnChangeFat32EntryTime();
  afx_msg void OnChangeFat32EntryDate();
  afx_msg void OnChangeFat32EntryLastAcc();
  virtual BOOL OnInitDialog();
  //}}AFX_MSG
  DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FAT32ENTRY_H__52D84A5B_EF59_4192_90CB_D82F6F15FD14__INCLUDED_)
