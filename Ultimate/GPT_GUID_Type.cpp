#include "stdafx.h"
#include "pch.h"

#include "ultimate.h"
#include "GPT_GUID_Type.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGUIDType dialog
CGUIDType::CGUIDType(CWnd* pParent /*=NULL*/)
  : CDialog(CGUIDType::IDD, pParent) {
  //{{AFX_DATA_INIT(CGUIDType)
  m_list_type = FALSE;
  m_title = _T("");
  m_type = _T("");
  //}}AFX_DATA_INIT
}

void CGUIDType::DoDataExchange(CDataExchange* pDX) {
  CDialog::DoDataExchange(pDX);
  //{{AFX_DATA_MAP(CGUIDType)
  DDX_Control(pDX, IDC_LIST, m_list);
  //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CGUIDType, CDialog)
  //{{AFX_MSG_MAP(CGUIDType)
  //}}AFX_MSG_MAP
END_MESSAGE_MAP()

// GPT partition types
// https://en.wikipedia.org/wiki/GUID_Partition_Table

struct S_CGUID_Strings {
  char name[33];
  char string[37];
} CGUIDType_str[] = {
  { "Zero              ", "00000000-0000-0000-0000-000000000000" },
  { "Random            ", "xxxxxxxx-xxxx-xxxx-xxxx-xxxxxxxxxxxx" },  // must stay as index 1
  { "Legacy            ", "024DEE41-33E7-11D3-9D69-0008C781F39F" },
  { "EFI System        ", "C12A7328-F81F-11D2-BA4B-00A0C93EC93B" },
  { "BIOS Boot         ", "21686148-6449-6E6F-744E-656564454649" },
  { "MS Reserved       ", "E3C9E316-0B5C-4DB8-817D-F92DF00215AE" },
  { "MS Basic          ", "EBD0A0A2-B9E5-4433-C087-68B6B72699C7" },
  { "Linux             ", "0FC63DAF-8483-4772-8E79-3D69D8477DE4" },
  { "RAID              ", "A19D880F-05FC-4D3B-A006-743F0F84911E" },
  { "Linux Root x86    ", "44479540-F297-41B2-9AF7-D131D5F0458A" },
  { "Linux Root x86-64 ", "4F68BCE3-E8CD-4DB1-96E7-FBCAF984B709" },
  { "Lean FS           ", "BB5A91B0-977E-11DB-B606-0800200C9A66" },

  { "", "" }
};

/////////////////////////////////////////////////////////////////////////////
// CGUIDType message handlers
BOOL CGUIDType::OnInitDialog() {
  S_GUID guid;
  CString cs, random;
  int i = 0;

  CDialog::OnInitDialog();
  
  // set the font to a fixed char font
  m_font.CreatePointFont(85, "Courier New", NULL);
  m_list.SetFont(&m_font);
  
  // create the random GUID
  GUID_Create(&guid, GUID_TYPE_RANDOM);
  GUID_Format(random, &guid);
  strcpy(CGUIDType_str[1].string, random);

  while (strlen(CGUIDType_str[i].name)) {
    cs.Format("%s (%s)", CGUIDType_str[i].name, CGUIDType_str[i].string);
    m_list.AddString(cs);
    // if we are the GUID list, we want only the first two
    if ((i == 1) && !m_list_type)
      break;
    i++;
  }

  // set the title of the window
  SetWindowText(m_title);
  
  return TRUE;
}

void CGUIDType::OnOK() {
  if (m_list.GetCurSel() != LB_ERR) {
    m_type = CGUIDType_str[m_list.GetCurSel()].string;
    CDialog::OnOK();
  } else
    CDialog::OnCancel();
}
