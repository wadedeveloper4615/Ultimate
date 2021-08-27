#include "stdafx.h"
#include "pch.h"

#include "ultimate.h"
#include "FYSFSFormat.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFYSFSFormat dialog
CFYSFSFormat::CFYSFSFormat(CWnd* pParent /*=NULL*/)
  : CDialog(CFYSFSFormat::IDD, pParent) {
  //{{AFX_DATA_INIT(CFYSFSFormat)
  m_num_bitmaps = 0;
  m_root_entries = 0;
  m_sect_cluster = 0;
  m_case_sensitive = TRUE;
  m_has_super_backup = TRUE;
  m_info = _T("");
  //}}AFX_DATA_INIT
}

void CFYSFSFormat::DoDataExchange(CDataExchange* pDX) {
  CDialog::DoDataExchange(pDX);
  //{{AFX_DATA_MAP(CFYSFSFormat)
  DDX_Text(pDX, IDC_NUM_BITMAPS, m_num_bitmaps);
  //DDV_MinMaxInt(pDX, m_num_bitmaps, 1, 2);
  DDX_Text(pDX, IDC_ROOT_ENTRIES, m_root_entries);
  //DDV_MinMaxInt(pDX, m_root_entries, 128, 65536);
  DDX_Text(pDX, IDC_SECT_CLUSTER, m_sect_cluster);
  //DDV_MinMaxInt(pDX, m_sect_cluster, 1, 16);
  DDX_Check(pDX, IDC_CASE_SENSITIVE, m_case_sensitive);
  DDX_Check(pDX, IDC_HAS_SUP_BACKUP, m_has_super_backup);
  DDX_Text(pDX, IDC_INFO, m_info);
  //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CFYSFSFormat, CDialog)
  //{{AFX_MSG_MAP(CFYSFSFormat)
  //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFYSFSFormat message handlers
BOOL CFYSFSFormat::OnInitDialog() {
  
  m_info.Format("Root Entries must be at least 128.\r\n");
  
  CDialog::OnInitDialog();
  
  return TRUE;
}

void CFYSFSFormat::OnOK() {
  CString cs;
  
  UpdateData(TRUE);  // bring from dialog
  
  if (m_root_entries < 128) {
    cs.Format("Root Entries must be at least 128.");
    AfxMessageBox(cs);
    SetDlgItemInt(IDC_ROOT_ENTRIES, 128, FALSE);
    return;
  }
  if ((m_num_bitmaps < 1) || (m_num_bitmaps > 2)) {
    cs.Format("Number of Bitmaps must be 1 or 2.");
    AfxMessageBox(cs);
    SetDlgItemInt(IDC_NUM_BITMAPS, 1, FALSE);
    return;
  }
  
  CDialog::OnOK();
}
