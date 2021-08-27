#include "stdafx.h"
#include "pch.h"

#include "ultimate.h"
#include "LeanFormat.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLeanFormat dialog


CLeanFormat::CLeanFormat(CWnd* pParent /*=NULL*/)
  : CDialog(CLeanFormat::IDD, pParent)
{
  //{{AFX_DATA_INIT(CLeanFormat)
  m_block_size = 512;
  m_pre_alloc_count = 0;
  m_eas_after_inode = FALSE;
  m_journal = FALSE;
  //}}AFX_DATA_INIT
}


void CLeanFormat::DoDataExchange(CDataExchange* pDX) {
  CDialog::DoDataExchange(pDX);
  //{{AFX_DATA_MAP(CLeanFormat)
  DDX_Text(pDX, IDC_BLOCK_SIZE, m_block_size);
  DDV_MinMaxInt(pDX, m_block_size, 256, 65536);
  DDX_Text(pDX, IDC_PRE_ALLOC_COUNT, m_pre_alloc_count);
  DDV_MinMaxInt(pDX, m_pre_alloc_count, 1, 12);
  DDX_Check(pDX, IDC_EAS_IN_INODE, m_eas_after_inode);
  DDX_Check(pDX, IDC_JOURNAL, m_journal);
  //}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CLeanFormat, CDialog)
  //{{AFX_MSG_MAP(CLeanFormat)
  ON_BN_CLICKED(IDOK, OnOkay)
  //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLeanFormat message handlers
void CLeanFormat::OnOkay() {

  UpdateData(TRUE);

  if (!power_of_two(m_block_size)) {
    AfxMessageBox("Block Size must be a power of two from 256 to 65536.");
    return;
  }

  CDialog::OnOK();
}
