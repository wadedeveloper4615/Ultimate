#include "stdafx.h"
#include "pch.h"

#include "ultimate.h"
#include "InsertVName.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CInsertVName dialog
CInsertVName::CInsertVName(CWnd* pParent /*=NULL*/)
  : CDialog(CInsertVName::IDD, pParent) {
  //{{AFX_DATA_INIT(CInsertVName)
  m_volume_name = _T("");
  //}}AFX_DATA_INIT
}

void CInsertVName::DoDataExchange(CDataExchange* pDX) {
  CDialog::DoDataExchange(pDX);
  //{{AFX_DATA_MAP(CInsertVName)
  DDX_Text(pDX, IDC_VOLUME_NAME, m_volume_name);
  //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CInsertVName, CDialog)
  //{{AFX_MSG_MAP(CInsertVName)
  //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CInsertVName message handlers
BOOL CInsertVName::OnInitDialog() {
  CDialog::OnInitDialog();

  GetDlgItem(IDC_VOLUME_NAME)->SetFocus();

  return FALSE;
}
