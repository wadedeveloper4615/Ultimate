#if !defined(AFX_SFSENTRY_H__9482900B_99E4_4361_A22B_9570EE97B59F__INCLUDED_)
#define AFX_SFSENTRY_H__9482900B_99E4_4361_A22B_9570EE97B59F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SFSEntry.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSFSEntry dialog

class CSFSEntry : public CDialog
{
// Construction
public:
  CSFSEntry(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
  //{{AFX_DATA(CSFSEntry)
  enum { IDD = IDD_SFS_ENTRY };
  CString	m_cont_count;
  CString	m_crc;
  CString	m_end_block;
  CString	m_filelen;
  CString	m_name;
  CString	m_start_block;
  CString	m_time_stamp;
  CString	m_entry_type;
  CString	m_entry_index;
  //}}AFX_DATA
  
  BYTE m_type;
  BYTE m_entry[64];
  BYTE *m_index_block;
  int  m_index_size;  // in entries
  int  m_index;  // entry index into index_block
  
// Overrides
  // ClassWizard generated virtual function overrides
  //{{AFX_VIRTUAL(CSFSEntry)
  protected:
  virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
  //}}AFX_VIRTUAL

// Implementation
protected:

  // Generated message map functions
  //{{AFX_MSG(CSFSEntry)
  virtual BOOL OnInitDialog();
  afx_msg void OnChangeEntryTime();
  afx_msg void OnCrcUpdate();
  virtual void OnOK();
  //}}AFX_MSG
  DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SFSENTRY_H__9482900B_99E4_4361_A22B_9570EE97B59F__INCLUDED_)
