#if !defined(AFX_FATENTRY_H__5170C875_4DE7_442A_9FAF_0AA5E03CC2A7__INCLUDED_)
#define AFX_FATENTRY_H__5170C875_4DE7_442A_9FAF_0AA5E03CC2A7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FatEntry.h : header file
//

#include "Fat.h"

/////////////////////////////////////////////////////////////////////////////
// CFatEntry dialog

class CFatEntry : public CDialog
{
// Construction
public:
  CFatEntry(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
  //{{AFX_DATA(CFatEntry)
  enum { IDD = IDD_FAT_ENTRY };
  CString	m_data_disp;
  CString	m_attrib;
  CString	m_cluster;
  CString	m_date;
  CString	m_ext;
  CString	m_filesize;
  CString	m_lfn_attrb;
  CString	m_lfn_cluster;
  CString	m_lfn_resv;
  CString	m_name;
  CString	m_lfn_name;
  CString	m_resvd;
  CString	m_sequ;
  CString	m_sfn_crc;
  CString	m_time;
  CString	m_sequ_disp;
  CString	m_time_disp;
  CString	m_error_code;
  //}}AFX_DATA
  
  void LFNtoDialog();
  void DialogtoLFN();
  
  S_FAT_ROOT m_sfn;
  void *m_lfns;
  int   m_lfn_count;
  int   m_lfn_cur;
  int   m_fat_size;
  BOOL  m_lfn_deleted;
  BOOL  m_show_bytes;
  
  S_FAT_ENTRIES m_fat_entries;
  
// Overrides
  // ClassWizard generated virtual function overrides
  //{{AFX_VIRTUAL(CFatEntry)
  protected:
  virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
  //}}AFX_VIRTUAL

// Implementation
protected:

  // Generated message map functions
  //{{AFX_MSG(CFatEntry)
  afx_msg void OnDate();
  afx_msg void OnDellfn();
  afx_msg void OnLFNRClear();
  afx_msg void OnNext();
  afx_msg void OnPrev();
  afx_msg void OnTime();
  afx_msg void OnSFNRClear();
  afx_msg void OnChangeEntryDate();
  afx_msg void OnChangeEntryTime();
  virtual BOOL OnInitDialog();
  virtual void OnOK();
  afx_msg void OnAttribute();
  afx_msg void OnFatentries();
  afx_msg void OnCrcUpdate();
  afx_msg void OnShowBytes();
  //}}AFX_MSG
  DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FATENTRY_H__5170C875_4DE7_442A_9FAF_0AA5E03CC2A7__INCLUDED_)
