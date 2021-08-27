#include "stdafx.h"
#include "pch.h"

#include "ultimate.h"
#include "LeanTime.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLeanTime dialog
CLeanTime::CLeanTime(CWnd* pParent /*=NULL*/)
  : CDialog(CLeanTime::IDD, pParent) {
  //{{AFX_DATA_INIT(CLeanTime)
  m_lean_time = _T("");
  //}}AFX_DATA_INIT
  m_divisor = 1;    // default to 1
  m_adjustment = 0; // default to no adjustment
}

void CLeanTime::DoDataExchange(CDataExchange* pDX) {
  CDialog::DoDataExchange(pDX);
  //{{AFX_DATA_MAP(CLeanTime)
  DDX_Text(pDX, IDC_LEAN_TIME, m_lean_time);
  //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CLeanTime, CDialog)
  //{{AFX_MSG_MAP(CLeanTime)
  ON_EN_CHANGE(IDC_LEAN_TIME, OnChangeLeanTime)
  ON_BN_CLICKED(IDC_TIME_NOW, OnTimeNow)
  //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLeanTime message handlers
BOOL CLeanTime::OnInitDialog() {
  CDialog::OnInitDialog();
  
  SetWindowText(m_title);
  
  OnChangeLeanTime();  
  
  return TRUE;
}

void CLeanTime::OnChangeLeanTime() {
  CString cs;
  
  GetDlgItemText(IDC_LEAN_TIME, cs);
  DWORD64 timestamp = (((INT64) convert64(cs) / m_divisor) + m_adjustment);  // convert from ? to Seconds
#if _MSC_VER <= 1310
  if (timestamp > 0xFFFFFFFF)  // VC++ 6.0 limited the value to 32-bits  (Crashes if larger)
    cs = "Error in Timestamp";
  else
#endif
  {
    CTime cTime((time_t) timestamp);  // converts seconds since 1 Jan 1970 to CTime
    cs.Format("%04i/%02i/%02i  %02i:%02i:%02i", cTime.GetYear(), cTime.GetMonth(), cTime.GetDay(), cTime.GetHour(), cTime.GetMinute(), cTime.GetSecond());
  }
  SetDlgItemText(IDC_LEAN_TIME_DISP, cs);
}

void CLeanTime::OnTimeNow() {
  CString cs;
  CTime cTime;
  time_t now;
  
  cTime = CTime::GetCurrentTime();
  now = cTime.GetTime();
  cs.Format("%I64i", ((INT64) now * m_divisor) - m_adjustment);
  
  SetDlgItemText(IDC_LEAN_TIME, cs);
  
  OnChangeLeanTime();  
}
