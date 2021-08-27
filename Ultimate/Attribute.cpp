// Attribute.cpp : implementation file
//

#include "stdafx.h"
#include "pch.h"

#include "ultimate.h"

#include "Attribute.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAttribute dialog


CAttribute::CAttribute(CWnd* pParent /*=NULL*/)
  : CDialog(CAttribute::IDD, pParent) {
  //{{AFX_DATA_INIT(CAttribute)
    // NOTE: the ClassWizard will add member initialization here
  //}}AFX_DATA_INIT
  m_title = "Please Choose:";
  m_single = FALSE;
  m_attrib = 0;
}

void CAttribute::DoDataExchange(CDataExchange* pDX) {
  CDialog::DoDataExchange(pDX);
  //{{AFX_DATA_MAP(CAttribute)
  DDX_Control(pDX, IDC_LIST, m_list);
  //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAttribute, CDialog)
  //{{AFX_MSG_MAP(CAttribute)
  ON_LBN_SELCHANGE(IDC_LIST, OnSelchangeList)
  //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAttribute message handlers

BOOL CAttribute::OnInitDialog() {
  CDialog::OnInitDialog();
  int i=0;
  
  SetWindowText(m_title);
  m_list.ResetContent();
  while (m_attributes[i].index > -1) {
    m_list.AddString((LPCTSTR) m_attributes[i].str);
    if ((m_attrib & m_attributes[i].mask) == m_attributes[i].attrb)
      m_list.SetSel(i, TRUE);
    i++;
  }
  
  return TRUE;
}

void CAttribute::OnOK() {
  int i=0;
  
  m_attrib = 0;
  while (m_attributes[i].index > -1) {
    if (m_list.GetSel(i))
      m_attrib |= m_attributes[i].attrb;
    i++;
  }
  
  CDialog::OnOK();
}

// deselect any other items if this one is selected.
void CAttribute::OnSelchangeList() {
  int i, j=0;
  
  i = m_list.GetCaretIndex(); // index to just clicked item
  if (m_list.GetSel(i)) {
    if (m_single) {
      for (j=0; j<m_list.GetCount(); j++)
        if (j != i)
          m_list.SetSel(j, FALSE);
    } else {
      while (m_attributes[i].groups[j] > -1) {
        m_list.SetSel(m_attributes[i].groups[j], FALSE);
        j++;
      }
    }
  }
}
