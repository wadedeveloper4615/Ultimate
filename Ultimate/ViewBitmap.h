#if !defined(AFX_ViewBitmap_H__1DA2FAB2_D1CC_4BFD_A3F5_13C805ECA3B4__INCLUDED_)
#define AFX_ViewBitmap_H__1DA2FAB2_D1CC_4BFD_A3F5_13C805ECA3B4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ViewBitmap.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CViewBitmap dialog

class CViewBitmap : public CDialog {
// Construction
public:
  CViewBitmap(CWnd* pParent = NULL);   // standard constructor
  
// Dialog Data
  //{{AFX_DATA(CViewBitmap)
  enum { IDD = IDD_VIEW_BITMAP };
  CScrollBar  m_scroll;
  //}}AFX_DATA
  
  void SetValues(const DWORD start);
  
  void *m_buffer;
  DWORD m_data_len;
  DWORD m_count;
  int   m_current;
  CString m_item_name;
  
// Overrides
  // ClassWizard generated virtual function overrides
  //{{AFX_VIRTUAL(CViewBitmap)
  protected:
  virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
  //}}AFX_VIRTUAL

// Implementation
protected:

  // Generated message map functions
  //{{AFX_MSG(CViewBitmap)
  virtual BOOL OnInitDialog();
  afx_msg void OnButtonClicked(UINT nID);
  afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
  //}}AFX_MSG
  DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ViewBitmap_H__1DA2FAB2_D1CC_4BFD_A3F5_13C805ECA3B4__INCLUDED_)
