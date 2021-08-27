#include "stdafx.h"
#include "pch.h"

#include "ultimate.h"
#include "FYSOSSig.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFYSOSSig dialog
CFYSOSSig::CFYSOSSig(CWnd* pParent /*=NULL*/)
  : CDialog(CFYSOSSig::IDD, pParent) {
  //{{AFX_DATA_INIT(CFYSOSSig)
  m_sig_base = _T("");
  m_boot_sig = _T("");
  m_fysos_sig = _T("");
  //}}AFX_DATA_INIT
}

void CFYSOSSig::DoDataExchange(CDataExchange* pDX) {
  CDialog::DoDataExchange(pDX);
  //{{AFX_DATA_MAP(CFYSOSSig)
  DDX_Text(pDX, IDC_FYSOS_SIG_BASE, m_sig_base);
  DDX_Text(pDX, IDC_FYSOS_SIG_BOOTSIG, m_boot_sig);
  DDX_Text(pDX, IDC_FYSOS_SIG_SIG, m_fysos_sig);
  //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CFYSOSSig, CDialog)
  //{{AFX_MSG_MAP(CFYSOSSig)
  ON_BN_CLICKED(IDC_UPDATE_SIG, OnUpdateSig)
  ON_BN_CLICKED(IDC_UPDATE_BOOT_SIG, OnUpdateBootSig)
  ON_BN_CLICKED(IDC_UPDATE_BASE, OnUpdateBase)
  //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFYSOSSig message handlers
void CFYSOSSig::OnOK() {
  
  CDialog::OnOK();
}

void CFYSOSSig::OnUpdateSig() {
  CString cs;
  cs.Format("0x%08X", (rand() << 16) | rand());
  SetDlgItemText(IDC_FYSOS_SIG_SIG, cs);
}

void CFYSOSSig::OnUpdateBootSig() {
  SetDlgItemText(IDC_FYSOS_SIG_BOOTSIG, "0xAA55");
}

void CFYSOSSig::OnUpdateBase() {
  CString cs;
  cs.Format("%I64i", m_base_lba);
  SetDlgItemText(IDC_FYSOS_SIG_BASE, cs);
}
