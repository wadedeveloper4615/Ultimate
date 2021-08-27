#include "stdafx.h"
#include "pch.h"

#include "ultimate.h"
#include "Settings.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSettings dialog


CSettings::CSettings(CWnd* pParent /*=NULL*/)
  : CDialog(CSettings::IDD, pParent) {
  //{{AFX_DATA_INIT(CSettings)
  m_max_error_count = 0;
  m_mbr_path = _T("");
  m_embr_path = _T("");
  m_force_readonly = FALSE;
  m_clear_mru = FALSE;
  m_extract_path = _T("");
  m_help_path = _T("");
  m_force_fysos = FALSE;
  //}}AFX_DATA_INIT
}

void CSettings::DoDataExchange(CDataExchange* pDX) {
  CDialog::DoDataExchange(pDX);
  //{{AFX_DATA_MAP(CSettings)
  DDX_Text(pDX, IDC_SETTINGS_ERR_CNT, m_max_error_count);
  DDV_MinMaxInt(pDX, m_max_error_count, -1, 100);
  DDX_Text(pDX, IDC_MBR_PATH, m_mbr_path);
  DDX_Text(pDX, IDC_EMBR_PATH, m_embr_path);
  DDX_Check(pDX, IDC_FORCE_READONLY, m_force_readonly);
  DDX_Check(pDX, IDC_CLEAR_MRU, m_clear_mru);
  DDX_Text(pDX, IDC_EXTRACT_PATH, m_extract_path);
  DDX_Text(pDX, IDC_HELP_PATH, m_help_path);
  DDX_Check(pDX, IDC_FORCE_FYSOS, m_force_fysos);
  //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CSettings, CDialog)
  //{{AFX_MSG_MAP(CSettings)
  ON_BN_CLICKED(IDC_MBR_PATH_BRZ, OnMbrPathBrz)
  ON_BN_CLICKED(IDC_EMBR_PATH_BRZ, OnEmbrPathBrz)
  ON_BN_CLICKED(IDC_EXTRACT_PATH_BRZ, OnExtractPathBrz)
  //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSettings message handlers

void CSettings::OnMbrPathBrz() {
  CString csStart;
  char szPath[MAX_PATH];
  
  GetDlgItemText(IDC_MBR_PATH, csStart);
  if (BrowseForFolder(GetSafeHwnd(), csStart, szPath, BIF_RETURNFSANCESTORS | BIF_RETURNONLYFSDIRS))
    SetDlgItemText(IDC_MBR_PATH, szPath);
}

void CSettings::OnEmbrPathBrz() {
  CString csStart;
  char szPath[MAX_PATH];
  
  GetDlgItemText(IDC_MBR_PATH, csStart);
  if (BrowseForFolder(GetSafeHwnd(), csStart, szPath, BIF_RETURNFSANCESTORS | BIF_RETURNONLYFSDIRS))
    SetDlgItemText(IDC_EMBR_PATH, szPath);
}

void CSettings::OnExtractPathBrz() {
  CString csStart;
  char szPath[MAX_PATH];
  
  GetDlgItemText(IDC_EXTRACT_PATH, csStart);
  if (BrowseForFolder(GetSafeHwnd(), csStart, szPath, BIF_RETURNFSANCESTORS | BIF_RETURNONLYFSDIRS))
    SetDlgItemText(IDC_EXTRACT_PATH, szPath);
}
