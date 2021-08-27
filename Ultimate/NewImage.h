#if !defined(AFX_NEWIMAGE_H__D0C1550D_2958_4A0E_9B99_44D8616A2B70__INCLUDED_)
#define AFX_NEWIMAGE_H__D0C1550D_2958_4A0E_9B99_44D8616A2B70__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// NewImage.h : header file
//

#include "NewPart.h"

#define MAX_PARTS   16

/////////////////////////////////////////////////////////////////////////////
// CNewImage dialog
class CNewImage : public CDialog {
// Construction
public:
  CNewImage(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
  //{{AFX_DATA(CNewImage)
  enum { IDD = IDD_NEW_FILE };
  CComboBox m_boundary;
  CProgressCtrl m_progress;
  CSpinButtonCtrl m_count_spin;
  CStatic m_partitions;
  int   m_sect_size;
  int   m_type;
  int   m_options;
  CString m_new_name;
  CString m_status;
  UINT	m_gpt_entry_start;
  //}}AFX_DATA
  
  void UpdateStatus(CString csStatus);
  void CreateNewPart(const int index);
  BOOL RemovePart(const int index, const BOOL ask);
  void UpdateEntry(CString cs, const int index);
  
  CPropertySheet m_Sheet;
  CNewPart m_Parts[MAX_PARTS];
  int m_max_parts;
  int m_cur_parts;
  CString m_Status;
  BOOL m_created;
  
  unsigned int m_sector_size;  // size of sectors for this type of image
  
// Overrides
  // ClassWizard generated virtual function overrides
  //{{AFX_VIRTUAL(CNewImage)
  protected:
  virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
  //}}AFX_VIRTUAL

// Implementation
protected:
  // Generated message map functions
  //{{AFX_MSG(CNewImage)
  virtual BOOL OnInitDialog();
  afx_msg void OnDeltaposCountSpin(NMHDR* pNMHDR, LRESULT* pResult);
  afx_msg LRESULT OnDropFiles(WPARAM wParam, LPARAM lParam);
  afx_msg void OnTypeChange();
  afx_msg void OnSectSizeChange();
  afx_msg void OnCreateImage();
  virtual void OnCancel();
  //}}AFX_MSG
  DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NEWIMAGE_H__D0C1550D_2958_4A0E_9B99_44D8616A2B70__INCLUDED_)
