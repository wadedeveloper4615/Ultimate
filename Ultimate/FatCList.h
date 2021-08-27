#if !defined(AFX_FATCLIST_H__BE82240D_8DDF_4BF1_990A_4AC7FB4EEAA0__INCLUDED_)
#define AFX_FATCLIST_H__BE82240D_8DDF_4BF1_990A_4AC7FB4EEAA0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FatCList.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFatCList dialog

class CFatCList : public CDialog
{
// Construction
public:
  CFatCList(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
  //{{AFX_DATA(CFatCList)
  enum { IDD = IDD_FAT_CLUSTERS };
  CListBox	m_list;
  //}}AFX_DATA
  
  int m_fat_size;
  S_FAT_ENTRIES *m_entries;
  
// Overrides
  // ClassWizard generated virtual function overrides
  //{{AFX_VIRTUAL(CFatCList)
  protected:
  virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
  //}}AFX_VIRTUAL

// Implementation
protected:

  // Generated message map functions
  //{{AFX_MSG(CFatCList)
  virtual BOOL OnInitDialog();
  //}}AFX_MSG
  DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FATCLIST_H__BE82240D_8DDF_4BF1_990A_4AC7FB4EEAA0__INCLUDED_)
