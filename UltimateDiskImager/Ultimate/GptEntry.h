#pragma once

#include "resource.h"

class CGptEntry : public CPropertyPage {
	DECLARE_DYNCREATE(CGptEntry)

	// Construction
public:
	CGptEntry();
	~CGptEntry();

	// Dialog Data
	  //{{AFX_DATA(CGptEntry)
	enum { IDD = IDD_GPT_ENTRY };
	CString	m_guid_type;
	CString	m_guid;
	CString	m_start_lba;
	CString	m_last_lba;
	CString	m_attrib;
	CString	m_name;
	//}}AFX_DATA

	CString m_Title;
	int    m_index;
	BOOL   m_dirty;

	// Overrides
	  // ClassWizard generated virtual function overrides
	  //{{AFX_VIRTUAL(CGptEntry)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

  // Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CGptEntry)
public:
	afx_msg void OnGptApply();
protected:
	afx_msg void OnTabItemChange();
	afx_msg void OnKillfocusGpteGuid();
	afx_msg void OnKillfocusGpteGuidType();
	afx_msg void OnGuidSelectType();
	afx_msg void OnGuidSelectGUID();
	afx_msg void OnAttribute();
	afx_msg void OnPlusMinus();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

