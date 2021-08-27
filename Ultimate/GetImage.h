#if !defined(AFX_GETIMAGE_H__42ED13CE_4B80_4726_8FE1_8A5A775FFEE5__INCLUDED_)
#define AFX_GETIMAGE_H__42ED13CE_4B80_4726_8FE1_8A5A775FFEE5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GetImage.h : header file
//

#include "winioctl.h"

typedef struct _DISK_TYPE {
  DWORD64 total_sects;
  DWORD   cylinders;
  DWORD   sec_per_track;
  DWORD   num_heads;
  DWORD64 size;
}DISK_TYPE;

#define MAX_VOLUMES  16
//  DRIVE_REMOVABLE
//  DRIVE_FIXED
//  DRIVE_REMOTE
//  DRIVE_CDROM
//  DRIVE_RAMDISK
typedef struct _VOLUMES {
  TCHAR szDriveName[3]; // = TEXT(" :");
  TCHAR szName[65];
  UINT  iType;
}VOLUMES;

/////////////////////////////////////////////////////////////////////////////
// CGetImage dialog

class CGetImage : public CDialog {
// Construction
public:
  CGetImage(CWnd* pParent = NULL);   // standard constructor
  
// Dialog Data
  //{{AFX_DATA(CGetImage)
  enum { IDD = IDD_GET_IMAGE };
  CEdit	m_status;
  CListBox	m_vol_list;
  CProgressCtrl	m_progress;
  CString m_new_name;
  int		m_type;
  //}}AFX_DATA
  
  DISK_TYPE *m_disk_info;
  VOLUMES *m_volumes;
  int   m_vol_count;
  
  BOOL GetDrvGeometry(DISK_GEOMETRY *pdg, const TCHAR drv);
  BOOL GetDrvGeometryEx(DISK_GEOMETRY_EX *pdg, const TCHAR drv, LARGE_INTEGER *liSize);
  int GetDrives(VOLUMES *volumes, const int max);
  void FillDrives(VOLUMES *volumes, const int count);
  
// Overrides
  // ClassWizard generated virtual function overrides
  //{{AFX_VIRTUAL(CGetImage)
  protected:
  virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
  //}}AFX_VIRTUAL
  
// Implementation
protected:
  // Generated message map functions
  //{{AFX_MSG(CGetImage)
  virtual BOOL OnInitDialog();
  afx_msg void OnButtonClicked(UINT nID);
  virtual void OnCancel();
  virtual void OnOK();
  afx_msg void OnKillfocusSectorCount();
  afx_msg void OnSelchangeVolumeList();
  //}}AFX_MSG
  DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GETIMAGE_H__42ED13CE_4B80_4726_8FE1_8A5A775FFEE5__INCLUDED_)
