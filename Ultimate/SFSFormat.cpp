#include "stdafx.h"
#include "pch.h"

#include "ultimate.h"
#include "SFSFormat.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSFSFormat dialog
CSFSFormat::CSFSFormat(CWnd* pParent /*=NULL*/)
  : CDialog(CSFSFormat::IDD, pParent) {
  //{{AFX_DATA_INIT(CSFSFormat)
  m_block_size = 0;
  m_info = _T("");
  //}}AFX_DATA_INIT
}

void CSFSFormat::DoDataExchange(CDataExchange* pDX) {
  CDialog::DoDataExchange(pDX);
  //{{AFX_DATA_MAP(CSFSFormat)
  DDX_Text(pDX, IDC_BLOCK_SIZE, m_block_size);
  DDX_Text(pDX, IDC_INFO, m_info);
  //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CSFSFormat, CDialog)
  //{{AFX_MSG_MAP(CSFSFormat)
  //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSFSFormat message handlers
void CSFSFormat::OnOK() {
  UpdateData(TRUE); // bring from dialog
  
  switch (m_block_size) {
    case 512:
    case 1024:
    case 2048:
    case 4096:
      CDialog::OnOK();
      break;
    default:
      AfxMessageBox("Please choose a valid Block Size");
  }
}
