#if !defined(AFX_UNKNOWN_H__51679AF6_0C29_4B6C_9E5A_8287B836030F__INCLUDED_)
#define AFX_UNKNOWN_H__51679AF6_0C29_4B6C_9E5A_8287B836030F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Unknown.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CUnknown dialog

class CUnknown : public CPropertyPage
{
  DECLARE_DYNCREATE(CUnknown)

// Construction
public:
  CUnknown();
  ~CUnknown();

// Dialog Data
  //{{AFX_DATA(CUnknown)
  enum { IDD = IDD_UNKNOWN };
  CString	m_dump;
  //}}AFX_DATA
  
  void Start(const DWORD64 lba, const DWORD64 size, const DWORD color, const int index, BOOL IsNewTab);
  void FormatLean(void);
  void FormatFat(int Type);
  void FormatExFat(void);
  void FormatFYSFS(void);
  void FormatSFS(void);
  void FormatExt2(void);
  
  int     m_index; // index into dlg->Unknown[]
  DWORD64 m_lba;   // starting lba of this partition
  DWORD64 m_size;  // size of this partition in sectors
  DWORD   m_color; // color used in image bar
  int     m_draw_index;
  
  DWORD64 m_current;  // current LSN of dump sector
  
// Overrides
  // ClassWizard generate virtual function overrides
  //{{AFX_VIRTUAL(CUnknown)
  protected:
  virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
  //}}AFX_VIRTUAL

// Implementation
protected:
  // Generated message map functions
  //{{AFX_MSG(CUnknown)
  virtual BOOL OnInitDialog();
  afx_msg void OnClean();
  afx_msg void OnFormat();
  afx_msg void OnInsert();
  afx_msg void OnDumpPrev();
  afx_msg void OnDumpNext();
  //}}AFX_MSG
  DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_UNKNOWN_H__51679AF6_0C29_4B6C_9E5A_8287B836030F__INCLUDED_)
