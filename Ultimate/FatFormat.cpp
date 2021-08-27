#include "stdafx.h"
#include "pch.h"

#include "ultimate.h"
#include "FatFormat.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFatFormat dialog
CFatFormat::CFatFormat(CWnd* pParent /*=NULL*/)
  : CDialog(CFatFormat::IDD, pParent) {
  //{{AFX_DATA_INIT(CFatFormat)
  m_num_fats = 0;
  m_root_entries = 0;
  m_sect_cluster = 0;
  m_info = _T("");
  //}}AFX_DATA_INIT
}

void CFatFormat::DoDataExchange(CDataExchange* pDX) {
  CDialog::DoDataExchange(pDX);
  //{{AFX_DATA_MAP(CFatFormat)
  DDX_Text(pDX, IDC_NUM_FATS, m_num_fats);
  DDV_MinMaxInt(pDX, m_num_fats, 1, 2);
  DDX_Text(pDX, IDC_ROOT_ENTRIES, m_root_entries);
  DDX_Text(pDX, IDC_SECT_CLUSTER, m_sect_cluster);
  DDX_Text(pDX, IDC_INFO, m_info);
  //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CFatFormat, CDialog)
  //{{AFX_MSG_MAP(CFatFormat)
  //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFatFormat message handlers
BOOL CFatFormat::OnInitDialog() {
  
  m_calc_spc = 
  m_sect_cluster = CalcSPC(m_sectors, m_fat_size);
  m_info.Format("For FAT%i with %I64i sectors, you must have a count of\r\n"
                "'sectors per cluster' of at least %i.",
                m_fat_size == FS_FAT12 ? 12 : (m_fat_size == FS_FAT16) ? 16 : 32,
                m_sectors,
                m_sect_cluster);
  
  CDialog::OnInitDialog();
  
  return TRUE;
}

void CFatFormat::OnOK() {
  CString cs;
  
  UpdateData(TRUE);  // bring from dialog
  
  if (m_sect_cluster < m_calc_spc) {
    cs.Format("Sectors per Cluster must be at least %i", m_calc_spc);
    AfxMessageBox(cs);
    SetDlgItemInt(IDC_SECT_CLUSTER, m_calc_spc, FALSE);
    return;
  }
  
  CDialog::OnOK();
}

// - cluster count <  4085 is FAT12
//                 < 65525 is FAT16
//                 else       FAT32
int CFatFormat::CalcSPC(DWORD64 sectors, int fat_size) {
  int spc = 1;
  
  while (spc <= 64) {
    if ((fat_size == FS_FAT12) && ((sectors / spc) < 4085))
      return spc;
    if ((fat_size == FS_FAT16) && ((sectors / spc) < 65525))
      return spc;
    if (fat_size == FS_FAT32)
      return spc;
    spc++;
  }
  
  AfxMessageBox("Illegal combination of sectors per cluster, total sectors, and fat size");
  return 1;
}
