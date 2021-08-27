#if !defined(AFX_ISOBEA_H__E0708764_950A_460A_B502_7661EC824202__INCLUDED_)
#define AFX_ISOBEA_H__E0708764_950A_460A_B502_7661EC824202__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ISOBEA.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CISOBEA dialog
class CISOBEA : public CPropertyPage {
  DECLARE_DYNCREATE(CISOBEA)

// Construction
public:
  CISOBEA();
  ~CISOBEA();
  
// Dialog Data
  //{{AFX_DATA(CISOBEA)
  enum { IDD = IDD_ISO_BEA };
  int   m_type;
  CString m_cd001;
  CString m_version;
  CString	m_sys_use;
  //}}AFX_DATA
  
  void Start(const DWORD64 lba, DWORD color, BOOL IsNewTab);
  
  bool    m_is_valid;
  DWORD64 m_lba;   // starting lba of this partition
  DWORD64 m_size;  // size of this partition in sectors
  DWORD   m_color; // color used in image bar
  int     m_draw_index;
  
  BYTE  m_descriptor[2048];
  
// Overrides
  // ClassWizard generate virtual function overrides
  //{{AFX_VIRTUAL(CISOBEA)
  protected:
  virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
  //}}AFX_VIRTUAL

// Implementation
protected:
  // Generated message map functions
  //{{AFX_MSG(CISOBEA)
  afx_msg void OnApplyB();
  virtual BOOL OnInitDialog();
  //}}AFX_MSG
  DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ISOBEA_H__E0708764_950A_460A_B502_7661EC824202__INCLUDED_)
