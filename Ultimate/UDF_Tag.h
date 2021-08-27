#if !defined(AFX_UDF_TAG_H__221AB24B_BB6F_4C7D_BD40_575A389F563C__INCLUDED_)
#define AFX_UDF_TAG_H__221AB24B_BB6F_4C7D_BD40_575A389F563C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// UDF_Tag.h : header file
//

#include "ISONSR.h"

/////////////////////////////////////////////////////////////////////////////
// CUDF_Tag dialog
class CUDF_Tag : public CDialog {
// Construction
public:
	CUDF_Tag(CWnd* pParent = NULL);   // standard constructor
	
// Dialog Data
	//{{AFX_DATA(CUDF_Tag)
	enum { IDD = IDD_UDF_TAG };
	CString m_crc;
	CString m_desc_crc;
	CString m_desc_crc_len;
	CString m_id;
	CString m_location;
	CString m_resv;
	CString m_ser_num;
	CString m_ver;
	//}}AFX_DATA
	
	DESC_TAG m_tag;
	
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUDF_Tag)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CUDF_Tag)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnUdfTagIdB();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_UDF_TAG_H__221AB24B_BB6F_4C7D_BD40_575A389F563C__INCLUDED_)
