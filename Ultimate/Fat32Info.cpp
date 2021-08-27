#include "stdafx.h"
#include "pch.h"

#include "ultimate.h"
#include "ultimateDlg.h"

#include "Fat32Info.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFat32Info dialog


CFat32Info::CFat32Info(CWnd* pParent /*=NULL*/)
  : CDialog(CFat32Info::IDD, pParent) {
  //{{AFX_DATA_INIT(CFat32Info)
  m_free_count = _T("");
  m_next_free = _T("");
  m_sig0 = _T("");
  m_sig1 = _T("");
  m_sig2 = _T("");
  m_reserved = _T("");
  //}}AFX_DATA_INIT
  m_clear_reserved = FALSE;
}

void CFat32Info::DoDataExchange(CDataExchange* pDX) {
  CDialog::DoDataExchange(pDX);
  //{{AFX_DATA_MAP(CFat32Info)
  DDX_Text(pDX, IDC_INFO_FREE_COUNT, m_free_count);
  DDV_MaxChars(pDX, m_free_count, 32);
  DDX_Text(pDX, IDC_INFO_NEXT_FREE, m_next_free);
  DDV_MaxChars(pDX, m_next_free, 32);
  DDX_Text(pDX, IDC_INFO_SIG0, m_sig0);
  DDV_MaxChars(pDX, m_sig0, 16);
  DDX_Text(pDX, IDC_INFO_SIG1, m_sig1);
  DDV_MaxChars(pDX, m_sig1, 16);
  DDX_Text(pDX, IDC_INFO_SIG2, m_sig2);
  DDV_MaxChars(pDX, m_sig2, 16);
  DDX_Text(pDX, IDC_RESERVED, m_reserved);
  //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CFat32Info, CDialog)
  //{{AFX_MSG_MAP(CFat32Info)
  ON_BN_CLICKED(IDC_UPDATE_FREE, OnUpdateFree)
  ON_BN_CLICKED(IDC_UPDATE_RESVED, OnUpdateResved)
  ON_BN_CLICKED(IDC_UPDATE_SIG, OnUpdateSig0)
  ON_BN_CLICKED(IDC_UPDATE_SIG1, OnUpdateSig1)
  ON_BN_CLICKED(IDC_UPDATE_SIG2, OnUpdateSig2)
  ON_EN_CHANGE(IDC_INFO_SIG0, OnChangeInfoSig0)
  ON_EN_CHANGE(IDC_INFO_SIG1, OnChangeInfoSig1)
  //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFat32Info message handlers
BOOL CFat32Info::OnInitDialog() {
  CDialog::OnInitDialog();
  
  OnChangeInfoSig0();
  OnChangeInfoSig1();
  
  // set the font of the DUMP window to a fixed font
  CUltimateDlg *dlg = (CUltimateDlg *) AfxGetApp()->m_pMainWnd;
  GetDlgItem(IDC_RESERVED)->SetFont(&dlg->m_DumpFont);
  
  return TRUE;
}

void CFat32Info::OnUpdateFree() {
  SetDlgItemText(IDC_INFO_FREE_COUNT, "-1");
}

void CFat32Info::OnUpdateResved() {
  m_clear_reserved = TRUE;
  SetDlgItemText(IDC_RESERVED, "\r\n\r\n             Will clear on 'Apply' ");
}

void CFat32Info::OnUpdateSig0() {
  SetDlgItemText(IDC_INFO_SIG0, "0x41615252");
}

void CFat32Info::OnUpdateSig1() {
  SetDlgItemText(IDC_INFO_SIG1, "0x61417272");
}

void CFat32Info::OnUpdateSig2() {
  SetDlgItemText(IDC_INFO_SIG2, "0xAA550000");
}

void CFat32Info::OnChangeInfoSig0() {
  CString cs;
  
  GetDlgItemText(IDC_INFO_SIG0, cs);
  DWORD val = convert32(cs);
  BYTE *p = (BYTE *) &val;
  cs.Format("%c%c%c%c", p[3], p[2], p[1], p[0]);
  SetDlgItemText(IDC_INFO_SIG0_DISP, cs);
}

void CFat32Info::OnChangeInfoSig1() {
  CString cs;
  
  GetDlgItemText(IDC_INFO_SIG1, cs);
  DWORD val = convert32(cs);
  BYTE *p = (BYTE *) &val;
  cs.Format("%c%c%c%c", p[3], p[2], p[1], p[0]);
  SetDlgItemText(IDC_INFO_SIG1_DISP, cs);
}

