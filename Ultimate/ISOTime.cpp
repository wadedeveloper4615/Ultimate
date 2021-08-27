#include "stdafx.h"
#include "pch.h"

#include "ultimate.h"
#include "ISOTime.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CISOTime dialog


CISOTime::CISOTime(CWnd* pParent /*=NULL*/)
  : CDialog(CISOTime::IDD, pParent) {
  //{{AFX_DATA_INIT(CISOTime)
  m_day = 0;
  m_gmt_off = 0;
  m_hour = 0;
  m_jiffies = 0;
  m_minute = 0;
  m_month = 0;
  m_second = 0;
  m_year = 0;
  //}}AFX_DATA_INIT
}

void CISOTime::DoDataExchange(CDataExchange* pDX) {
  CDialog::DoDataExchange(pDX);
  //{{AFX_DATA_MAP(CISOTime)
  DDX_Text(pDX, IDC_DAY, m_day);
  DDV_MinMaxInt(pDX, m_day, 1, 31);
  DDX_Text(pDX, IDC_GMT_OFF, m_gmt_off);
  DDV_MinMaxInt(pDX, m_gmt_off, -10, 10);
  DDX_Text(pDX, IDC_HOUR, m_hour);
  DDV_MinMaxInt(pDX, m_hour, 0, 23);
  DDX_Text(pDX, IDC_JIFFIES, m_jiffies);
  DDV_MinMaxInt(pDX, m_jiffies, 0, 99);
  DDX_Text(pDX, IDC_MINUTE, m_minute);
  DDV_MinMaxInt(pDX, m_minute, 0, 59);
  DDX_Text(pDX, IDC_MONTH, m_month);
  DDV_MinMaxInt(pDX, m_month, 1, 12);
  DDX_Text(pDX, IDC_SECOND, m_second);
  DDV_MinMaxInt(pDX, m_second, 0, 59);
  DDX_Text(pDX, IDC_YEAR, m_year);
  DDV_MinMaxInt(pDX, m_year, 0, 3000);
  //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CISOTime, CDialog)
  //{{AFX_MSG_MAP(CISOTime)
  ON_EN_CHANGE(IDC_DAY, OnChangeTime)
  ON_EN_CHANGE(IDC_GMT_OFF, OnChangeTime)
  ON_EN_CHANGE(IDC_HOUR, OnChangeTime)
  ON_EN_CHANGE(IDC_JIFFIES, OnChangeTime)
  ON_EN_CHANGE(IDC_MINUTE, OnChangeTime)
  ON_EN_CHANGE(IDC_MONTH, OnChangeTime)
  ON_EN_CHANGE(IDC_SECOND, OnChangeTime)
  ON_EN_CHANGE(IDC_YEAR, OnChangeTime)
  //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CISOTime message handlers
BOOL CISOTime::OnInitDialog() {
  CDialog::OnInitDialog();
  OnChangeTime();
  return TRUE;
}

void CISOTime::OnChangeTime() {
  CString csTime;
  
  // UpdateData() does the check
  //UpdateData(TRUE);  // Get from Dialog
  m_year = GetDlgItemInt(IDC_YEAR, NULL, FALSE);
  m_month = GetDlgItemInt(IDC_MONTH, NULL, FALSE);
  m_day = GetDlgItemInt(IDC_DAY, NULL, FALSE);
  m_hour = GetDlgItemInt(IDC_HOUR, NULL, FALSE);
  m_minute = GetDlgItemInt(IDC_MINUTE, NULL, FALSE);
  m_second = GetDlgItemInt(IDC_SECOND, NULL, FALSE);
  m_jiffies = GetDlgItemInt(IDC_JIFFIES, NULL, FALSE);
  
  csTime.Format("%04i/%02i/%02i %02i:%02i:%02i.%02i", 
    m_year, m_month, m_day,
    m_hour, m_minute, m_second, m_jiffies);
  SetDlgItemText(IDC_TIME_DISP, csTime);
}

// dir = TRUE = from time to CISOTime::members
// dir = FALSE = from CISOTime::members to time
void CISOTime::Convert(S_ISO_DATE_TIME *time, BOOL dir) {
  CString cs;
  
  if (dir) {
    memcpy(cs.GetBuffer(4), time->year, 4); cs.ReleaseBuffer(4);
    m_year = convert32(cs);
    memcpy(cs.GetBuffer(2), time->month, 2); cs.ReleaseBuffer(2);
    m_month = convert32(cs);
    memcpy(cs.GetBuffer(2), time->day, 2); cs.ReleaseBuffer(2);
    m_day = convert32(cs);
    memcpy(cs.GetBuffer(2), time->hour, 2); cs.ReleaseBuffer(2);
    m_hour = convert32(cs);
    memcpy(cs.GetBuffer(2), time->min, 2); cs.ReleaseBuffer(2);
    m_minute = convert32(cs);
    memcpy(cs.GetBuffer(2), time->sec, 2); cs.ReleaseBuffer(2);
    m_second = convert32(cs);
    memcpy(cs.GetBuffer(2), time->jiffies, 2); cs.ReleaseBuffer(2);
    m_jiffies = convert32(cs);
    m_gmt_off = time->gmt_off;
  } else {
    cs.Format("%i", m_year); memcpy(time->year, cs, 4);
    cs.Format("%i", m_month); memcpy(time->month, cs, 2);
    cs.Format("%i", m_day); memcpy(time->day, cs, 2);
    cs.Format("%i", m_hour); memcpy(time->hour, cs, 2);
    cs.Format("%i", m_minute); memcpy(time->min, cs, 2);
    cs.Format("%i", m_second); memcpy(time->sec, cs, 2);
    cs.Format("%i", m_jiffies); memcpy(time->jiffies, cs, 2);
    time->gmt_off = m_gmt_off;
  }
}
