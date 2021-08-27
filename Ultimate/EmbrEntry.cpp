// EmbrEntry.cpp : implementation file
//

#include "stdafx.h"
#include "pch.h"

#include "ultimate.h"

#include "EmbrEntry.h"
#include "Embr.h"

#include "Attribute.h"
#include "LeanTime.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEmbrEntry property page

IMPLEMENT_DYNCREATE(CEmbrEntry, CPropertyPage)

CEmbrEntry::CEmbrEntry() : CPropertyPage(CEmbrEntry::IDD) {
  //{{AFX_DATA_INIT(CEmbrEntry)
  m_created = _T("");
  m_description = _T("");
  m_flags = _T("");
  m_os_sig = _T("");
  m_sectors = _T("");
  m_signature = _T("");
  m_start_lba = _T("");
  m_last_booted = _T("");
  m_reserved = _T("");
  //}}AFX_DATA_INIT
}

CEmbrEntry::~CEmbrEntry() {
}

void CEmbrEntry::DoDataExchange(CDataExchange* pDX) {
  CPropertyPage::DoDataExchange(pDX);
  //{{AFX_DATA_MAP(CEmbrEntry)
  DDX_Text(pDX, IDC_EMBRE_CREATED, m_created);
  DDX_Text(pDX, IDC_EMBRE_DESCRIPT, m_description);
  DDV_MaxChars(pDX, m_description, 63);
  DDX_Text(pDX, IDC_EMBRE_FLAGS, m_flags);
  DDX_Text(pDX, IDC_EMBRE_OS_SIG, m_os_sig);
  DDX_Text(pDX, IDC_EMBRE_SECTORS, m_sectors);
  DDX_Text(pDX, IDC_EMBRE_SIG, m_signature);
  DDX_Text(pDX, IDC_EMBRE_START_LBA, m_start_lba);
  DDX_Text(pDX, IDC_EMBRE_LAST, m_last_booted);
  DDX_Text(pDX, IDC_EMBRE_RESERVED, m_reserved);
  //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CEmbrEntry, CPropertyPage)
  //{{AFX_MSG_MAP(CEmbrEntry)
  ON_BN_CLICKED(ID_EMBRE_APPLY, OnEmbreApply)
  ON_BN_CLICKED(IDC_ESIG_SET, OnEsigSet)
  ON_BN_CLICKED(IDC_FLAGS_SET, OnFlagsSet)
  ON_EN_CHANGE(IDC_EMBRE_CREATED, OnTabItemChange)
  ON_BN_CLICKED(IDC_EMBR_CLEAR_RESV, OnEmbrClearResv)
  ON_EN_CHANGE(IDC_EMBRE_DESCRIPT, OnTabItemChange)
  ON_EN_CHANGE(IDC_EMBRE_FLAGS, OnTabItemChange)
  ON_EN_CHANGE(IDC_EMBRE_LAST, OnTabItemChange)
  ON_EN_CHANGE(IDC_EMBRE_OS_SIG, OnTabItemChange)
  ON_EN_CHANGE(IDC_EMBRE_RESERVED, OnTabItemChange)
  ON_EN_CHANGE(IDC_EMBRE_SECTORS, OnTabItemChange)
  ON_EN_CHANGE(IDC_EMBRE_SIG, OnTabItemChange)
  ON_EN_CHANGE(IDC_EMBRE_START_LBA, OnTabItemChange)
  ON_BN_CLICKED(IDC_EDATE_NOW, OnEdateNow)
  ON_BN_CLICKED(IDC_EBOOT_NOW, OnEbootNow)
  //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEmbrEntry message handlers
void CEmbrEntry::OnEmbreApply() {
  S_EMBR_ENTRY *entry = (S_EMBR_ENTRY *) ((BYTE *) m_entry_buffer + sizeof(S_EMBR_HDR) + (m_index * sizeof(S_EMBR_ENTRY)));
  UpdateData(TRUE); // bring from Dialog
  
  entry->flags = convert32(m_flags);
  entry->signature = convert32(m_signature);
  entry->starting_sector = convert64(m_start_lba);
  entry->sector_count = convert64(m_sectors);
  entry->date_created = convert64(m_created);
  entry->date_last_booted = convert64(m_last_booted);
  entry->OS_signature = convert32(m_os_sig);
  strcpy((char *) entry->description, m_description);
  
  // get the reserved field
  CString cs;
  for (int i=0; i<16; i++) {
    // the format will be "00 00 00 00 ..."
    cs = "0x" + m_reserved.Mid(i * 3, 2);
    entry->reserved[i] = convert8(cs);
  }
  
  // Add the '*' to the tab title
  CPropertySheet *Sheet = (CPropertySheet *) GetParent();
  TC_ITEM ti;
  char szText[64];
  strcpy(szText, m_Title);
  ti.mask = TCIF_TEXT;
  ti.pszText = szText;
  Sheet->GetTabControl()->SetItem(m_index, &ti);
  m_dirty = FALSE;
}

void CEmbrEntry::OnTabItemChange() {
  if (!m_dirty) {
    CPropertySheet *Sheet = (CPropertySheet *) GetParent();
    TC_ITEM ti;
    char szText[64];
    ti.mask = TCIF_TEXT;
    ti.pszText = szText;
    ti.cchTextMax = 64;
    Sheet->GetTabControl()->GetItem(m_index, &ti);
    strcat(szText, "*");
    Sheet->GetTabControl()->SetItem(m_index, &ti);
    m_dirty = TRUE;
  }
}

void CEmbrEntry::OnEsigSet() {
  SetDlgItemText(IDC_EMBRE_SIG, "0x52424D65");
}

S_ATTRIBUTES embr_entry_flags[] = {
                              //            |                               | <- max (col 67)
  { EMBR_VALID_ENTRY, EMBR_VALID_ENTRY,  0, "Is Valid Entry"                 , {-1, } },
  { EMBR_HIDDN_ENTRY, EMBR_HIDDN_ENTRY,  1, "Is Hidden Entry"                , {-1, } },
  { 0,                       (DWORD) -1, -1, NULL                             , {-1, } }
};

void CEmbrEntry::OnFlagsSet() {
  CAttribute dlg;
  CString cs;
  
  GetDlgItemText(IDC_EMBRE_FLAGS, cs);
  dlg.m_title = "Entry Flags";
  dlg.m_attrib = convert32(cs);
  dlg.m_attributes = embr_entry_flags;
  if (dlg.DoModal() == IDOK) {
    cs.Format("0x%08X", dlg.m_attrib);
    SetDlgItemText(IDC_EMBRE_FLAGS, cs);
  }
}

void CEmbrEntry::OnEmbrClearResv() {
  SetDlgItemText(IDC_EMBRE_RESERVED, "00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00");
}

// Secs since 01Jan1980
void CEmbrEntry::OnEdateNow() {
  CLeanTime dlg;
  
  dlg.m_title = "Date Created";
  dlg.m_adjustment = 315532800;  // count of seconds between 01Jan1980 and 01Jan1970
  GetDlgItemText(IDC_EMBRE_CREATED, dlg.m_lean_time);
  if (dlg.DoModal() == IDOK)
    SetDlgItemText(IDC_EMBRE_CREATED, dlg.m_lean_time);
}

// Secs since 01Jan1980
void CEmbrEntry::OnEbootNow() {
  CLeanTime dlg;
  
  dlg.m_title = "Last Booted";
  dlg.m_adjustment = 315532800;  // count of seconds between 01Jan1980 and 01Jan1970
  GetDlgItemText(IDC_EMBRE_LAST, dlg.m_lean_time);
  if (dlg.DoModal() == IDOK)
    SetDlgItemText(IDC_EMBRE_LAST, dlg.m_lean_time);
}
