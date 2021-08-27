#if !defined(AFX_INSERTVNAME_H__4B2FFF50_B1A8_45FE_BA06_6351A589D5B2__INCLUDED_)
#define AFX_InsertVName_H__4B2FFF50_B1A8_45FE_BA06_6351A589D5B2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// InsertVName.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CInsertVName dialog

class CInsertVName : public CDialog
{
// Construction
public:
  CInsertVName(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
  //{{AFX_DATA(CInsertVName)
  enum { IDD = IDD_VOLUME_NAME };
  CString	m_volume_name;
  //}}AFX_DATA

// Overrides
  // ClassWizard generated virtual function overrides
  //{{AFX_VIRTUAL(CInsertVName)
  protected:
  virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
  //}}AFX_VIRTUAL

// Implementation
protected:

  // Generated message map functions
  //{{AFX_MSG(CInsertVName)
  //}}AFX_MSG
  DECLARE_MESSAGE_MAP()
public:
  virtual BOOL OnInitDialog();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INSERTVNAME_H__4B2FFF50_B1A8_45FE_BA06_6351A589D5B2__INCLUDED_)
