#include "stdafx.h"
#include "pch.h"

#include "ultimate.h"
#include "OurFind.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COurFind dialog


COurFind::COurFind(CWnd* pParent /*=NULL*/)
  : CDialog(COurFind::IDD, pParent) {
  //{{AFX_DATA_INIT(COurFind)
  m_match_case = FALSE;
  m_find_str = _T("");
  //}}AFX_DATA_INIT
}

void COurFind::DoDataExchange(CDataExchange* pDX) {
  CDialog::DoDataExchange(pDX);
  //{{AFX_DATA_MAP(COurFind)
  DDX_Check(pDX, IDC_CASE, m_match_case);
  DDX_Text(pDX, IDC_FIND_STR, m_find_str);
  //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(COurFind, CDialog)
  //{{AFX_MSG_MAP(COurFind)
  //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COurFind message handlers
