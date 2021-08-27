#include "stdafx.h"
#include "pch.h"

#include "ultimate.h"
#include "Fat32Entry.h"

#include "Fat.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFat32Entry dialog
CFat32Entry::CFat32Entry(CWnd* pParent /*=NULL*/)
  : CDialog(CFat32Entry::IDD, pParent) {
  //{{AFX_DATA_INIT(CFat32Entry)
  m_cluster = _T("");
  m_date = _T("");
  m_last_acc = _T("");
  m_nt_resv = _T("");
  m_tenth = _T("");
  m_time = _T("");
  //}}AFX_DATA_INIT
}

void CFat32Entry::DoDataExchange(CDataExchange* pDX) {
  CDialog::DoDataExchange(pDX);
  //{{AFX_DATA_MAP(CFat32Entry)
  DDX_Text(pDX, IDC_FAT32_ENTRY_CLUST, m_cluster);
  DDX_Text(pDX, IDC_FAT32_ENTRY_DATE, m_date);
  DDX_Text(pDX, IDC_FAT32_ENTRY_LAST_ACC, m_last_acc);
  DDX_Text(pDX, IDC_FAT32_ENTRY_RESV, m_nt_resv);
  DDX_Text(pDX, IDC_FAT32_ENTRY_TENTH, m_tenth);
  DDX_Text(pDX, IDC_FAT32_ENTRY_TIME, m_time);
  //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CFat32Entry, CDialog)
  //{{AFX_MSG_MAP(CFat32Entry)
  ON_BN_CLICKED(IDC_UPDATE_DATE, OnUpdateDate)
  ON_BN_CLICKED(IDC_UPDATE_LAST, OnUpdateLast)
  ON_BN_CLICKED(IDC_UPDATE_TIME, OnUpdateTime)
  ON_EN_CHANGE(IDC_FAT32_ENTRY_TIME, OnChangeFat32EntryTime)
  ON_EN_CHANGE(IDC_FAT32_ENTRY_DATE, OnChangeFat32EntryDate)
  ON_EN_CHANGE(IDC_FAT32_ENTRY_LAST_ACC, OnChangeFat32EntryLastAcc)
  //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFat32Entry message handlers
BOOL CFat32Entry::OnInitDialog() {
  CDialog::OnInitDialog();
  
  OnChangeFat32EntryTime();
  OnChangeFat32EntryDate();
  OnChangeFat32EntryLastAcc();
  
  return TRUE;
}

void CFat32Entry::OnUpdateDate() {
  CString cs;
  CTime time = CTime::GetCurrentTime();
  unsigned d = ((time.GetYear() - 1980) << 9) | (time.GetMonth() << 5) | time.GetDay();
  cs.Format("0x%04X", d);
  SetDlgItemText(IDC_FAT32_ENTRY_DATE, cs);
}

void CFat32Entry::OnUpdateLast() {
  CString cs;
  CTime time = CTime::GetCurrentTime();
  unsigned d = ((time.GetYear() - 1980) << 9) | (time.GetMonth() << 5) | time.GetDay();
  cs.Format("0x%04X", d);
  SetDlgItemText(IDC_FAT32_ENTRY_LAST_ACC, cs);
}

void CFat32Entry::OnUpdateTime() {
  CString cs;
  CTime time = CTime::GetCurrentTime();
  unsigned t = (time.GetHour() << 11) | (time.GetMinute() << 5) | time.GetSecond();
  cs.Format("0x%04X", t);
  SetDlgItemText(IDC_FAT32_ENTRY_TIME, cs);
}

void CFat32Entry::OnChangeFat32EntryTime() {
  CString cs, time;
  GetDlgItemText(IDC_FAT32_ENTRY_TIME, time);
  
  unsigned t = convert16(time);
  cs.Format("%02i:%02i:%02i", t >> 11, (t & 0x07E0) >> 5, (t & 0x001F) >> 0);
  
  SetDlgItemText(IDC_FAT32_ENTRY_TIME_DISP, cs);
}

void CFat32Entry::OnChangeFat32EntryDate() {
  CString cs, date;
  GetDlgItemText(IDC_FAT32_ENTRY_DATE, date);
  
  unsigned d = convert16(date);
  cs.Format("%04i/%02i/%02i", (d >> 9) + 1980, (d & 0x01E0) >> 5, (d & 0x001F) >> 0);
  
  SetDlgItemText(IDC_FAT32_ENTRY_DATE_DISP, cs);
}

void CFat32Entry::OnChangeFat32EntryLastAcc() {
  CString cs, date;
  GetDlgItemText(IDC_FAT32_ENTRY_LAST_ACC, date);
  
  unsigned d = convert16(date);
  cs.Format("%04i/%02i/%02i", (d >> 9) + 1980, (d & 0x01E0) >> 5, (d & 0x001F) >> 0);
  
  SetDlgItemText(IDC_FAT32_ENTRY_LAST_DISP, cs);
}

