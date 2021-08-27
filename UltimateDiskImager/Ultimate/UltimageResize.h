#pragma once

#include "resource.h"

class CUltimageResize : public CDialog
{
	// Construction
public:
	CUltimageResize(CWnd* pParent = NULL);   // standard constructor

  // Dialog Data
	//{{AFX_DATA(CUltimageResize)
	enum { IDD = IDD_ULTIMATE_RESIZE };
	CString	m_cur_size;
	CString	m_new_size;
	CString m_title;
	//}}AFX_DATA


  // Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUltimageResize)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

  // Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CUltimageResize)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
};

