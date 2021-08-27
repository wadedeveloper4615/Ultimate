#include "stdafx.h"
#include "pch.h"

#include "ultimate.h"
#include "FYSFSEntry.h"

#include "LeanTime.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFYSFSEntry dialog
CFYSFSEntry::CFYSFSEntry(CWnd* pParent /*=NULL*/)
  : CDialog(CFYSFSEntry::IDD, pParent) {
  //{{AFX_DATA_INIT(CFYSFSEntry)
  m_attribute = _T("");
  m_crc = _T("");
  m_created = _T("");
  m_fat_cont = _T("");
  m_fat_entries = _T("");
  m_file_size = _T("");
  m_flags = _T("");
  m_last_access = _T("");
  m_name_cont = _T("");
  m_name_fat = _T("");
  m_name_len = _T("");
  m_scratch = _T("");
  m_slot_type = _T("");
  //}}AFX_DATA_INIT
}

void CFYSFSEntry::DoDataExchange(CDataExchange* pDX) {
  CDialog::DoDataExchange(pDX);
  //{{AFX_DATA_MAP(CFYSFSEntry)
  DDX_Text(pDX, IDC_ATTRIBUTE, m_attribute);
  DDX_Text(pDX, IDC_CRC, m_crc);
  DDX_Text(pDX, IDC_CREATED, m_created);
  DDX_Text(pDX, IDC_FAT_CONT, m_fat_cont);
  DDX_Text(pDX, IDC_FAT_ENTRIES, m_fat_entries);
  DDX_Text(pDX, IDC_FILE_SIZE, m_file_size);
  DDX_Text(pDX, IDC_FLAGS, m_flags);
  DDX_Text(pDX, IDC_LAST_ACC, m_last_access);
  DDX_Text(pDX, IDC_NAME_CONT, m_name_cont);
  DDX_Text(pDX, IDC_NAME_FAT, m_name_fat);
  DDX_Text(pDX, IDC_NAME_LEN, m_name_len);
  DDX_Text(pDX, IDC_SCRATCH, m_scratch);
  DDX_Text(pDX, IDC_SLOT_TYPE, m_slot_type);
  //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CFYSFSEntry, CDialog)
  //{{AFX_MSG_MAP(CFYSFSEntry)
  ON_BN_CLICKED(IDC_CREATED_CHANGE, OnCreated)
  ON_BN_CLICKED(IDC_LAST_CHANGE, OnLastAccess)
  //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFYSFSEntry message handlers

// Secs since 01Jan1980
void CFYSFSEntry::OnCreated() {
  CLeanTime dlg;
  
  dlg.m_title = "Date Created";
  dlg.m_adjustment = 315532800;  // count of seconds between 01Jan1980 and 01Jan1970
  GetDlgItemText(IDC_CREATED, dlg.m_lean_time);
  if (dlg.DoModal() == IDOK)
    SetDlgItemText(IDC_CREATED, dlg.m_lean_time);
}

// Secs since 01Jan1980
void CFYSFSEntry::OnLastAccess() {
  CLeanTime dlg;
  
  dlg.m_title = "Last Accessed";
  dlg.m_adjustment = 315532800;  // count of seconds between 01Jan1980 and 01Jan1970
  GetDlgItemText(IDC_LAST_ACC, dlg.m_lean_time);
  if (dlg.DoModal() == IDOK)
    SetDlgItemText(IDC_LAST_ACC, dlg.m_lean_time);
}

