// ExFatUCase.cpp : implementation file
//

#include "stdafx.h"
#include "pch.h"

#include "ultimate.h"
#include "ExFatUCase.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CExFatUCase dialog


CExFatUCase::CExFatUCase(CWnd* pParent /*=NULL*/)
  : CDialog(CExFatUCase::IDD, pParent) {
  //{{AFX_DATA_INIT(CExFatUCase)
    // NOTE: the ClassWizard will add member initialization here
  //}}AFX_DATA_INIT
  
  m_buffer = NULL;
}

void CExFatUCase::DoDataExchange(CDataExchange* pDX) {
  CDialog::DoDataExchange(pDX);
  //{{AFX_DATA_MAP(CExFatUCase)
  DDX_Control(pDX, IDC_SCROLLBAR, m_scroll);
  //}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CExFatUCase, CDialog)
  //{{AFX_MSG_MAP(CExFatUCase)
  ON_WM_VSCROLL()
  ON_CONTROL_RANGE(EN_KILLFOCUS, IDC_UCHAR_0, IDC_UCHAR_3, OnChangeChar)
  //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CExFatUCase message handlers
BOOL CExFatUCase::OnInitDialog() {
  
  SetValues(0);
  
  CDialog::OnInitDialog();
  
  if (m_count > 4)
    m_scroll.SetScrollRange(0, m_count - 4, TRUE);
  else
    m_scroll.SetScrollRange(0, 0, TRUE);
  m_scroll.SetScrollPos(0, TRUE);
  
  return TRUE;
}

void CExFatUCase::SetValues(const DWORD start) {
  WORD *p = (WORD *) m_buffer;
  CString cs;
  
  cs.Format("Characters %i to %i of %i", start, start+3, m_count);
  SetDlgItemText(IDC_CHAR_TITLE, cs);
  
  for (int i=0; i<4; i++) {
    cs.Format("0x%04X", start + i);
    SetDlgItemText(IDC_CHAR_0 + i, cs);
    cs.Format("0x%04X", p[start + i]);
    SetDlgItemText(IDC_UCHAR_0 + i, cs);
  }
  
  m_current = start;
}

void CExFatUCase::OnChangeChar(UINT nID) {
  int pos = m_current + (nID - IDC_UCHAR_0);
  WORD *p = (WORD *) m_buffer;
  CString cs;
  
  GetDlgItemText(nID, cs);
  WORD word = convert16(cs);
  p[pos] = word;
}

void CExFatUCase::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar *pScrollBar) {
  SCROLLINFO info = { sizeof(SCROLLINFO) };
  pScrollBar->GetScrollInfo(&info, SIF_ALL);
  
  //update scroller
  switch (nSBCode) {
    case SB_LEFT: info.nPos = info.nMin; break;
    case SB_RIGHT: info.nPos = info.nMax; break;
    case SB_LINELEFT: info.nPos--; break;
    case SB_LINERIGHT: info.nPos++;  break;
    case SB_PAGELEFT: info.nPos -= info.nPage; break;
    case SB_PAGERIGHT: info.nPos += info.nPage; break;
    case SB_THUMBPOSITION: info.nPos = info.nTrackPos; break;
    case SB_THUMBTRACK: info.nPos = info.nTrackPos; break;
    //case SB_ENDSCROLL:  break;
  }
  
  if (info.nPos < 0)
    info.nPos = 0;
  if (info.nPos > (int) (m_count - 4))
    info.nPos = (int) (m_count - 4);
  
  pScrollBar->SetScrollInfo(&info, TRUE);
  
  SetValues(info.nPos);
}
