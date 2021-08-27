#pragma once


// CModeless dialog

class CModeless : public CDialog {
	// Construction
public:
	CModeless(CWnd* pParent = NULL);   // standard constructor

  // Dialog Data
	//{{AFX_DATA(CModeless)
	enum { IDD = IDD_MODELESS };
	CString	m_edit;
	//}}AFX_DATA

	BOOL m_modeless;
	CString m_Title;

	// Overrides
	  // ClassWizard generated virtual function overrides
	  //{{AFX_VIRTUAL(CModeless)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

  // Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CModeless)
	afx_msg void OnDone();
	afx_msg void OnCopy();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
