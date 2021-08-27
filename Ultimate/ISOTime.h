#if !defined(AFX_ISOTIME_H__2F44FC99_198B_4E0D_BF80_C4955148DFBC__INCLUDED_)
#define AFX_ISOTIME_H__2F44FC99_198B_4E0D_BF80_C4955148DFBC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ISOTime.h : header file
//

#include "ISOPrimary.h"

/////////////////////////////////////////////////////////////////////////////
// CISOTime dialog

class CISOTime : public CDialog {
// Construction
public:
  CISOTime(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
  //{{AFX_DATA(CISOTime)
  enum { IDD = IDD_ISO_TIME };
  int m_day;
  int m_gmt_off;
  int m_hour;
  int m_jiffies;
  int m_minute;
  int m_month;
  int m_second;
  int m_year;
  //}}AFX_DATA
  
  void Convert(S_ISO_DATE_TIME *time, BOOL dir);
  
// Overrides
  // ClassWizard generated virtual function overrides
  //{{AFX_VIRTUAL(CISOTime)
  protected:
  virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
  //}}AFX_VIRTUAL

// Implementation
protected:

  // Generated message map functions
  //{{AFX_MSG(CISOTime)
  afx_msg void OnChangeTime();
  virtual BOOL OnInitDialog();
  //}}AFX_MSG
  DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ISOTIME_H__2F44FC99_198B_4E0D_BF80_C4955148DFBC__INCLUDED_)
