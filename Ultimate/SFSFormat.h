#if !defined(AFX_SFSFORMAT_H__420BA489_89EC_4E77_B320_1571674E34B6__INCLUDED_)
#define AFX_SFSFORMAT_H__420BA489_89EC_4E77_B320_1571674E34B6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SFSFormat.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSFSFormat dialog

class CSFSFormat : public CDialog
{
// Construction
public:
  CSFSFormat(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
  //{{AFX_DATA(CSFSFormat)
  enum { IDD = IDD_SFS_FORMAT };
  int		m_block_size;
  CString	m_info;
  //}}AFX_DATA


// Overrides
  // ClassWizard generated virtual function overrides
  //{{AFX_VIRTUAL(CSFSFormat)
  protected:
  virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
  //}}AFX_VIRTUAL

// Implementation
protected:

  // Generated message map functions
  //{{AFX_MSG(CSFSFormat)
  virtual void OnOK();
  //}}AFX_MSG
  DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SFSFORMAT_H__420BA489_89EC_4E77_B320_1571674E34B6__INCLUDED_)
