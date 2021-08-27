#include "stdafx.h"
#include "pch.h"

#include "ultimate.h"

#include "Fat.h"
#include "FatCList.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFatCList dialog
CFatCList::CFatCList(CWnd* pParent /*=NULL*/)
  : CDialog(CFatCList::IDD, pParent) {
  //{{AFX_DATA_INIT(CFatCList)
    // NOTE: the ClassWizard will add member initialization here
  //}}AFX_DATA_INIT
}

void CFatCList::DoDataExchange(CDataExchange* pDX) {
  CDialog::DoDataExchange(pDX);
  //{{AFX_DATA_MAP(CFatCList)
  DDX_Control(pDX, IDC_LIST, m_list);
  //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CFatCList, CDialog)
  //{{AFX_MSG_MAP(CFatCList)
  //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFatCList message handlers

BOOL CFatCList::OnInitDialog() {
  CDialog::OnInitDialog();
  
  CString cs;
  for (int i=0; i<m_entries->entry_count; i++) {
    switch (m_fat_size) {
      case FS_FAT12:
        cs.Format("0x%03X (%i)", m_entries->entries[i], m_entries->entries[i]);
        break;
      case FS_FAT16:
        cs.Format("0x%04X (%i)", m_entries->entries[i], m_entries->entries[i]);
        break;
      case FS_FAT32:
        cs.Format("0x%08X (%i)", m_entries->entries[i], m_entries->entries[i]);
        break;
    }
    m_list.AddString(cs);
  }
  
  return TRUE;
}
