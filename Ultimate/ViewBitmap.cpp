#include "stdafx.h"
#include "pch.h"

#include "ultimate.h"

#include "ViewBitmap.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CViewBitmap dialog
CViewBitmap::CViewBitmap(CWnd* pParent /*=NULL*/)
  : CDialog(CViewBitmap::IDD, pParent) {
  //{{AFX_DATA_INIT(CViewBitmap)
  //}}AFX_DATA_INIT
  
  m_buffer = NULL;
}

void CViewBitmap::DoDataExchange(CDataExchange* pDX) {
  CDialog::DoDataExchange(pDX);
  //{{AFX_DATA_MAP(CViewBitmap)
  DDX_Control(pDX, IDC_SCROLLBAR, m_scroll);
  //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CViewBitmap, CDialog)
  //{{AFX_MSG_MAP(CViewBitmap)
  ON_WM_VSCROLL()
  ON_CONTROL_RANGE(BN_CLICKED, IDC_BITMAP_BIT0, IDC_BITMAP_BIT7, OnButtonClicked)
  //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CViewBitmap message handlers
BOOL CViewBitmap::OnInitDialog() {
  
  SetValues(0);
  
  CDialog::OnInitDialog();
  
  if (m_count > 7)
    m_scroll.SetScrollRange(0, m_count - 8, TRUE);
  else
    m_scroll.SetScrollRange(0, 0, TRUE);
  m_scroll.SetScrollPos(0, TRUE);
  
  return TRUE;
}

void CViewBitmap::SetValues(const DWORD start) {
  BYTE *p = (BYTE *) m_buffer;
  CString cs;
  
  cs.Format("%ss %i to %i of %i", m_item_name, start, start+7, m_count);
  SetDlgItemText(IDC_CLUSTER_TITLE, cs);
  
  for (int i=0; i<8; i++) {
    cs.Format("%s %i", m_item_name, start + i);
    GetDlgItem(IDC_BITMAP_BIT0 + i)->SetWindowText(cs);
    UINT checked = ((p[(start + i) / 8] & (1 << ((start + i) % 8))) > 0) ? BST_CHECKED : BST_UNCHECKED;
    CheckDlgButton(IDC_BITMAP_BIT0 + i, checked);
  }
  
  m_current = start;
}

void CViewBitmap::OnButtonClicked(UINT nID) {
  BYTE *p = (BYTE *) m_buffer;
  int pos = m_current + (nID - IDC_BITMAP_BIT0);
  
  // this is called after the button is toggled
  if (!IsDlgButtonChecked(nID))
    p[pos / 8] &= ~(1 << (pos % 8));
  else
    p[pos / 8] |= (1 << (pos % 8));
}

void CViewBitmap::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar *pScrollBar) {
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
  }
  
  if (info.nPos < 0)
    info.nPos = 0;
  if (info.nPos > (int) (m_count - 8))
    info.nPos = (int) (m_count - 8);
  
  pScrollBar->SetScrollInfo(&info, TRUE);
  
  SetValues(info.nPos);
}
