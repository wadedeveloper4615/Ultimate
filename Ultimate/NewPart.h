#if !defined(AFX_NEWPART_H__6B96F861_CC5C_47F0_B4A4_B7A698016A53__INCLUDED_)
#define AFX_NEWPART_H__6B96F861_CC5C_47F0_B4A4_B7A698016A53__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// NewPart.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CNewPart dialog

class CNewPart : public CPropertyPage {
  DECLARE_DYNCREATE(CNewPart)

// Construction
public:
  CNewPart();
  ~CNewPart();

// Dialog Data
  //{{AFX_DATA(CNewPart)
  enum { IDD = IDD_NEW_PART };
  CString	m_filename;
  DWORD	m_sectors;
  CString	m_name;
  BOOL	m_bootable;
  int		m_emulation;
  //}}AFX_DATA
  
  CString m_Title;
  int  m_index;
  BOOL m_dirty;
  
  DWORD64 m_lba;  // calculated at "create image" time
  void *m_parent;
  
// Overrides
  // ClassWizard generate virtual function overrides
  //{{AFX_VIRTUAL(CNewPart)
  protected:
  virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
  //}}AFX_VIRTUAL

// Implementation
public:
  afx_msg void OnSizeChanged();
protected:
  // Generated message map functions
  //{{AFX_MSG(CNewPart)
  afx_msg void OnPartChanged();
  afx_msg void OnBrowse();
  virtual BOOL OnInitDialog();
  afx_msg LRESULT OnDropFiles(WPARAM wParam, LPARAM lParam);
  //}}AFX_MSG
  DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NEWPART_H__6B96F861_CC5C_47F0_B4A4_B7A698016A53__INCLUDED_)
