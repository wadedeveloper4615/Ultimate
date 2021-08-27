#include "stdafx.h"
#include "pch.h"

#include "ultimate.h"
#include "ultimateDlg.h"

#include "ISOBEA.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CISOBEA property page

IMPLEMENT_DYNCREATE(CISOBEA, CPropertyPage)

CISOBEA::CISOBEA() : CPropertyPage(CISOBEA::IDD) {
  //{{AFX_DATA_INIT(CISOBEA)
  m_cd001 = _T("");
  m_version = _T("");
  m_sys_use = _T("");
  //}}AFX_DATA_INIT
}

CISOBEA::~CISOBEA() {
}

void CISOBEA::DoDataExchange(CDataExchange* pDX) {
  CPropertyPage::DoDataExchange(pDX);
  //{{AFX_DATA_MAP(CISOBEA)
  DDX_Text(pDX, IDC_TYPE, m_type);
  DDX_Text(pDX, IDC_CD001, m_cd001);
  DDX_Text(pDX, IDC_VERSION, m_version);
  DDX_Text(pDX, IDC_SYS_USE, m_sys_use);
  //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CISOBEA, CPropertyPage)
  //{{AFX_MSG_MAP(CISOBEA)
  ON_BN_CLICKED(ID_APPLY, OnApplyB)
  //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CISOBEA message handlers
BOOL CISOBEA::OnInitDialog() {
  CPropertyPage::OnInitDialog();
  
  // set the font of the DUMP window to a fixed font
  CUltimateDlg *dlg = (CUltimateDlg *) AfxGetApp()->m_pMainWnd;
  GetDlgItem(IDC_SYS_USE)->SetFont(&dlg->m_DumpFont);
  
  return TRUE;
}

void CISOBEA::Start(const DWORD64 lba, DWORD color, BOOL IsNewTab) {
  S_ISO_BVD *bvd = (S_ISO_BVD *) m_descriptor;
  
  m_is_valid = TRUE;
  m_lba = lba;
  m_size = 1; ////
  m_color = color;
  
  m_type = 0;
  m_cd001 = "BEA01";
  m_version.Format("%i", bvd->ver);
  
  DWORD offset = (DWORD) ((BYTE *) bvd->sys_use - (BYTE *) bvd);
  DumpIt(m_sys_use, bvd->sys_use, offset, 2048 - offset, FALSE);
}

void CISOBEA::OnApplyB() {
  // nothing to apply
}
