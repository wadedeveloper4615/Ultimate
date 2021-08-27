// MbrEntry.cpp : implementation file
//

#include "pch.h"
#include "Ultimate.h"
#include "MbrEntry.h"
#include "afxdialogex.h"
#include "UltimateDlg.h"
#include "MBR.h"
#include "Attribute.h"

// CMbrEntry dialog

IMPLEMENT_DYNCREATE(CMbrEntry, CPropertyPage)

CMbrEntry::CMbrEntry() : CPropertyPage(CMbrEntry::IDD) {
    //{{AFX_DATA_INIT(CMbrEntry)
    m_begin_cyl = _T("");
    m_begin_head = _T("");
    m_begin_sect = _T("");
    m_boot_id = _T("");
    m_end_cyl = _T("");
    m_end_head = _T("");
    m_end_sect = _T("");
    m_size = _T("");
    m_start_lba = _T("");
    m_sys_id = _T("");
    //}}AFX_DATA_INIT
    m_dirty = FALSE;
}

CMbrEntry::~CMbrEntry() {
}

void CMbrEntry::DoDataExchange(CDataExchange* pDX) {
    CPropertyPage::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CMbrEntry)
    DDX_Text(pDX, IDC_MBR_BEGIN_CYL, m_begin_cyl);
    DDV_MaxChars(pDX, m_begin_cyl, 10);
    DDX_Text(pDX, IDC_MBR_BEGIN_HEAD, m_begin_head);
    DDV_MaxChars(pDX, m_begin_head, 10);
    DDX_Text(pDX, IDC_MBR_BEGIN_SECT, m_begin_sect);
    DDV_MaxChars(pDX, m_begin_sect, 10);
    DDX_Text(pDX, IDC_MBR_BOOT_ID, m_boot_id);
    DDV_MaxChars(pDX, m_boot_id, 10);
    DDX_Text(pDX, IDC_MBR_END_CYL, m_end_cyl);
    DDV_MaxChars(pDX, m_end_cyl, 10);
    DDX_Text(pDX, IDC_MBR_END_HEAD, m_end_head);
    DDV_MaxChars(pDX, m_end_head, 10);
    DDX_Text(pDX, IDC_MBR_END_SECT, m_end_sect);
    DDV_MaxChars(pDX, m_end_sect, 10);
    DDX_Text(pDX, IDC_MBR_SIZE, m_size);
    DDV_MaxChars(pDX, m_size, 10);
    DDX_Text(pDX, IDC_MBR_START_LBA, m_start_lba);
    DDV_MaxChars(pDX, m_start_lba, 10);
    DDX_Text(pDX, IDC_MBR_SYS_ID, m_sys_id);
    DDV_MaxChars(pDX, m_sys_id, 10);
    //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMbrEntry, CPropertyPage)
    //{{AFX_MSG_MAP(CMbrEntry)
    ON_BN_CLICKED(IDC_MBR_BEGIN_UPDATE, OnMbrBeginUpdate)
    ON_BN_CLICKED(IDC_MBR_END_UPDATE, OnMbrEndUpdate)
    ON_BN_CLICKED(ID_MBR_APPLY, OnMbrApply)
    ON_EN_CHANGE(IDC_MBR_SYS_ID, OnChangeMbrSysId)
    ON_EN_CHANGE(IDC_MBR_BEGIN_CYL, OnTabItemChange)
    ON_EN_CHANGE(IDC_MBR_BEGIN_HEAD, OnTabItemChange)
    ON_EN_CHANGE(IDC_MBR_BEGIN_SECT, OnTabItemChange)
    ON_EN_CHANGE(IDC_MBR_BOOT_ID, OnTabItemChange)
    ON_EN_CHANGE(IDC_MBR_END_CYL, OnTabItemChange)
    ON_EN_CHANGE(IDC_MBR_END_HEAD, OnTabItemChange)
    ON_EN_CHANGE(IDC_MBR_END_SECT, OnTabItemChange)
    ON_EN_KILLFOCUS(IDC_MBR_SIZE, OnTabItemChangeSize)
    ON_EN_CHANGE(IDC_MBR_START_LBA, OnTabItemChange)
    ON_BN_CLICKED(IDC_SYS_ID, OnSysId)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMbrEntry message handlers

// **** not more than 31 chars each line ****
const TCHAR * fdisk_ids[] = {
  _T("Empty"),
  _T("FAT12"),
  _T("XENIX root"),
  _T("XENIX usr"),
  _T("FAT16 < 32M"),
  _T("Extended"),
  _T("FAT16"),
  _T("HPFS/NTFS/exFAT"),
  _T("ATX"),
  _T("ATX Bootable"),
  _T("OS/2 Boot Manage"),
  _T("W95 FAT32"),
  _T("W95 FAT32 (LBA)"),
  _T("*unknown*"),
  _T("W95 FAT16 (LBA)"),
  _T("W95 Ext'd (LBA)"),
  _T("OPUS"),                      // 16
  _T("Hidden FAT12"),
  _T("Compaq diagnostic"),
  _T("*unknown*"),
  _T("Hidden FAT16 < 32meg"),
  _T("*unknown*"),
  _T("Hidden FAT16"),
  _T("Hidded HPFS/NTFS"),
  _T("AST SmartSleep"),
  _T("*unknown*"),
  _T("*unknown*"),
  _T("Hidded W95 FAT32"),
  _T("Hidded W95 FAT32"),
  _T("*unknown*"),
  _T("Hidded W95 FAT36"),
  _T("*unknown*"),
  _T("*unknown*"),                 // 32
  _T("*unknown*"),
  _T("FYSFS"),
  _T("*unknown*"),
  _T("NEC DOS"),
  _T("*unknown*"),
  _T("*unknown*"),
  _T("*unknown*"),
  _T("*unknown*"),
  _T("*unknown*"),
  _T("*unknown*"),
  _T("*unknown*"),
  _T("*unknown*"),
  _T("*unknown*"),
  _T("*unknown*"),
  _T("*unknown*"),
  _T("*unknown*"),                 // 48
  _T("*unknown*"),
  _T("*unknown*"),
  _T("*unknown*"),
  _T("*unknown*"),
  _T("*unknown*"),
  _T("*unknown*"),
  _T("*unknown*"),
  _T("*unknown*"),
  _T("Plan 9"),
  _T("*unknown*"),
  _T("*unknown*"),
  _T("PartitionMagic"),
  _T("*unknown*"),
  _T("*unknown*"),
  _T("*unknown*"),
  _T("Venix 80286"),               // 64
  _T("PPC PRep Boot"),
  _T("*unknown*"),
  _T("*unknown*"),
  _T("*unknown*"),
  _T("*unknown*"),
  _T("*unknown*"),
  _T("*unknown*"),
  _T("*unknown*"),
  _T("*unknown*"),
  _T("*unknown*"),
  _T("*unknown*"),
  _T("*unknown*"),
  _T("QNX4.x"),
  _T("QNX4.x 2nd part"),
  _T("QNX4.x 3rd part"),
  _T("OnTrack DM"),
  _T("OnTrack DM6 Aux"),
  _T("CP/M"),
  _T("SFS"),
  _T("OnTrackDM6"),
  _T("EZ-DRIVE"),
  _T("Golden Bow"),
  _T("*unknown*"),
  _T("*unknown*"),
  _T("*unknown*"),
  _T("*unknown*"),
  _T("*unknown*"),
  _T("Priam Edisk"),
  _T("*unknown*"),
  _T("*unknown*"),
  _T("*unknown*"),
  _T("*unknown*"),                 // 96
  _T("SpeedStor"),
  _T("*unknown*"),
  _T("GNU HURD or Sys"),
  _T("Novell Netware"),
  _T("Novell Netware"),
  _T("*unknown*"),
  _T("*unknown*"),
  _T("*unknown*"),
  _T("*unknown*"),
  _T("*unknown*"),
  _T("*unknown*"),
  _T("*unknown*"),
  _T("*unknown*"),
  _T("*unknown*"),
  _T("*unknown*"),
  _T("DiskSecure Mult"),           // 112
  _T("*unknown*"),
  _T("*unknown*"),
  _T("*unknown*"),
  _T("*unknown*"),
  _T("PC/IX"),
  _T("*unknown*"),
  _T("*unknown*"),
  _T("*unknown*"),
  _T("*unknown*"),
  _T("*unknown*"),
  _T("*unknown*"),
  _T("*unknown*"),
  _T("*unknown*"),
  _T("*unknown*"),
  _T("*unknown*"),
  _T("Old Minix"),                 // 128
  _T("Minix / old Linux"),
  _T("Linux swap"),
  _T("Linux"),
  _T("OS/2 Hidden C:"),
  _T("Linux extended"),
  _T("NTFS volume set"),
  _T("NTFS volume set"),
  _T("*unknown*"),
  _T("*unknown*"),
  _T("*unknown*"),
  _T("*unknown*"),
  _T("*unknown*"),
  _T("*unknown*"),
  _T("Linux LVM"),
  _T("*unknown*"),
  _T("*unknown*"),                 // 144
  _T("*unknown*"),
  _T("*unknown*"),
  _T("Amoeba"),
  _T("Amoeba BBT"),
  _T("*unknown*"),
  _T("*unknown*"),
  _T("*unknown*"),
  _T("*unknown*"),
  _T("*unknown*"),
  _T("*unknown*"),
  _T("*unknown*"),
  _T("*unknown*"),
  _T("*unknown*"),
  _T("*unknown*"),
  _T("BSD/OS"),
  _T("IBM Thinkpad hi"),           // 160
  _T("*unknown*"),
  _T("*unknown*"),
  _T("*unknown*"),
  _T("*unknown*"),
  _T("FreeBSD"),
  _T("OpenBSD"),
  _T("NeXTSTEP"),
  _T("Darwin UFS"),
  _T("NetBSD"),
  _T("*unknown*"),
  _T("Darwin boot"),
  _T("*unknown*"),
  _T("*unknown*"),
  _T("*unknown*"),
  _T("*unknown*"),
  _T("*unknown*"),                 // 176
  _T("*unknown*"),
  _T("*unknown*"),
  _T("*unknown*"),
  _T("*unknown*"),
  _T("*unknown*"),
  _T("*unknown*"),
  _T("BSDI fs"),
  _T("BSDI swap"),
  _T("*unknown*"),
  _T("*unknown*"),
  _T("Boot Wizard hidden"),
  _T("*unknown*"),
  _T("*unknown*"),
  _T("Solaris boot"),
  _T("*unknown*"),
  _T("*unknown*"),                 // 192
  _T("DRDOS/sec (FAT-"),
  _T("*unknown*"),
  _T("*unknown*"),
  _T("DRDOS/sec (FAT-"),
  _T("*unknown*"),
  _T("DRDOS/sec (FAT-"),
  _T("Syrinx"),
  _T("*unknown*"),
  _T("*unknown*"),
  _T("*unknown*"),
  _T("*unknown*"),
  _T("*unknown*"),
  _T("*unknown*"),
  _T("*unknown*"),
  _T("*unknown*"),
  _T("*unknown*"),                 // 208
  _T("*unknown*"),
  _T("*unknown*"),
  _T("*unknown*"),
  _T("*unknown*"),
  _T("*unknown*"),
  _T("*unknown*"),
  _T("*unknown*"),
  _T("*unknown*"),
  _T("*unknown*"),
  _T("Non-FS data"),
  _T("*unknown*"),
  _T("*unknown*"),
  _T("CP/M / CTOS / "),
  _T("Dell Utility"),
  _T("BootIt"),
  _T("eMBR"),                      // 224
  _T("DOS access"),
  _T("*unknown*"),
  _T("DOS R/O"),
  _T("SpeedStor"),
  _T("*unknown*"),
  _T("*unknown*"),
  _T("*unknown*"),
  _T("*unknown*"),
  _T("*unknown*"),
  _T("LeanFS"),
  _T("BeOS fs"),
  _T("*unknown*"),
  _T("*unknown*"),
  _T("EFI GPT Protect"),
  _T("EFI (FAT-12/16/"),
  _T("Linux/PA-RISC b"),           // 240
  _T("SpeedStor"),
  _T("DOS secondary"),
  _T("*unknown*"),
  _T("SpeedStor"),
  _T("*unknown*"),
  _T("*unknown*"),
  _T("*unknown*"),
  _T("*unknown*"),
  _T("*unknown*"),
  _T("*unknown*"),
  _T("*unknown*"),
  _T("*unknown*"),
  _T("Linux raid auto"),
  _T("LANstep"),
  _T("BBT")
};

void CMbrEntry::OnMbrBeginUpdate() {
    UpdateData(TRUE);  // bring from Dialog
    DWORD lba;
    BYTE head, sect;
    WORD cyl;

    lba = convert32(m_start_lba);
    LBAtoCHS(lba, &cyl, &head, &sect);

    m_begin_cyl.Format(_T("0x%02X"), cyl);
    m_begin_head.Format(_T("0x%02X"), head);
    m_begin_sect.Format(_T("0x%02X"), sect);

    OnTabItemChange();
    UpdateData(FALSE);  // send to Dialog
}

void CMbrEntry::OnMbrEndUpdate() {
    UpdateData(TRUE);  // bring from Dialog
    DWORD lba;
    BYTE head, sect;
    WORD cyl;

    lba = convert32(m_start_lba);
    lba += convert32(m_size);
    LBAtoCHS(lba, &cyl, &head, &sect);

    m_end_cyl.Format(_T("0x%02X"), cyl);
    m_end_head.Format(_T("0x%02X"), head);
    m_end_sect.Format(_T("0x%02X"), sect);

    OnTabItemChange();
    UpdateData(FALSE);  // send to Dialog
}

void CMbrEntry::OnMbrApply() {
    MBR_PART_ENTRY* entry;
    CUltimateDlg* dlg = (CUltimateDlg*)AfxGetApp()->m_pMainWnd;
    CMbr* mbr = (CMbr*)m_parent;

    UpdateData(TRUE);  // bring from Dialog

    entry = (MBR_PART_ENTRY*)(&mbr->m_buffer[512 - 2 - (4 * 16)] + (DWORD64)((DWORD64)16 * (DWORD64)m_index));
    entry->boot_id = convert8(m_boot_id);
    entry->start.cyl = convert8(m_begin_cyl);
    entry->start.head = convert8(m_begin_head);
    entry->start.sector = convert8(m_begin_sect);
    entry->sys_id = convert8(m_sys_id);
    entry->end.cyl = convert8(m_end_cyl);
    entry->end.head = convert8(m_end_head);
    entry->end.sector = convert8(m_end_sect);

    entry->start_lba = convert32(m_start_lba);
    entry->sectors = convert32(m_size);

    // Add the '*' to the tab title
    CPropertySheet* Sheet = (CPropertySheet*)GetParent();
    TC_ITEM ti;
    TCHAR szText[64];
    _tcscpy_s(szText, 64, m_Title);
    ti.mask = TCIF_TEXT;
    ti.pszText = szText;
    Sheet->GetTabControl()->SetItem(m_index, &ti);
    m_dirty = FALSE;
}

void CMbrEntry::OnTabItemChangeSize() {
    CString cs;

    OnTabItemChange();

    GetDlgItemText(IDC_MBR_SIZE, cs);
    DWORD size = convert32(cs);
    if (size == 0) {
        SetDlgItemText(IDC_MBR_SYS_ID, _T("0x00"));
        OnChangeMbrSysId();
        GetDlgItem(IDC_SYS_ID)->EnableWindow(FALSE);
        GetDlgItem(IDC_MBR_SYS_ID)->EnableWindow(FALSE);
    }
    else {
        GetDlgItem(IDC_SYS_ID)->EnableWindow(TRUE);
        GetDlgItem(IDC_MBR_SYS_ID)->EnableWindow(TRUE);
    }
}

void CMbrEntry::OnTabItemChange() {
    if (!m_dirty) {
        CPropertySheet* Sheet = (CPropertySheet*)GetParent();
        TC_ITEM ti;
        TCHAR szText[64];

        ti.mask = TCIF_TEXT;
        ti.pszText = szText;
        ti.cchTextMax = 64;
        Sheet->GetTabControl()->GetItem(m_index, &ti);
        _tcscat_s(szText, 64, _T("*"));
        Sheet->GetTabControl()->SetItem(m_index, &ti);
        m_dirty = TRUE;
    }
}

void CMbrEntry::OnChangeMbrSysId() {
    UpdateData(TRUE);  // bring from Dialog

    int i = convert8(m_sys_id);
    SetDlgItemText(IDC_SYS_STR, fdisk_ids[(i & 0xFF)]);

    OnTabItemChange();
}

BOOL CMbrEntry::OnInitDialog() {
    CPropertyPage::OnInitDialog();

    CString cs;
    DWORD size = convert32(m_size);
    if (size > 0) {
        GetDlgItem(IDC_SYS_ID)->EnableWindow(TRUE);
        GetDlgItem(IDC_MBR_SYS_ID)->EnableWindow(TRUE);
    }

    int i = convert8(m_sys_id);
    SetDlgItemText(IDC_SYS_STR, fdisk_ids[(i & 0xFF)]);
    m_dirty = FALSE;

    return TRUE;
}

// Sector   = (LBA mod SPT) + 1       (SPT = Sectors per Track)
// Head     = (LBA  /  SPT) mod Heads
// Cylinder = (LBA  /  SPT)  /  Heads
void CMbrEntry::LBAtoCHS(const DWORD lba, WORD* cyl, BYTE* head, BYTE* sect) {
    CMbr* mbr = (CMbr*)m_parent;
    DWORD heads, spt;

    mbr->UpdateData(TRUE); // bring from Dialog

    spt = convert32(mbr->m_spt);
    heads = convert32(mbr->m_head_count);
    gLBAtoCHS(lba, cyl, head, sect, spt, heads);
}

void CMbrEntry::OnSysId() {
    CAttribute dlg;
    CString cs;
    int i, j = 0;

    // we create a list from fdisk_ids[] above
    S_ATTRIBUTES* mbr_entry_attrbs = (S_ATTRIBUTES*)malloc((256 + 1) * sizeof(S_ATTRIBUTES));
    for (i = 0; i < 256; i++) {
        if (_tcscmp(fdisk_ids[i], _T("*unknown*")) != 0) {
            mbr_entry_attrbs[j].attrb = i;
            mbr_entry_attrbs[j].mask = (DWORD)-1;  // must equal the m_attrb value
            mbr_entry_attrbs[j].index = j;
            _tcscpy_s(mbr_entry_attrbs[j].str, 32, fdisk_ids[i]);
            mbr_entry_attrbs[j].groups[0] = -1;
            j++;
        }
    }
    // mark the last one
    mbr_entry_attrbs[j].index = -1;

    GetDlgItemText(IDC_MBR_SYS_ID, cs);
    dlg.m_title = "MBR Sys ID";
    dlg.m_attrib = convert32(cs);
    dlg.m_attributes = mbr_entry_attrbs;
    dlg.m_single = TRUE;
    if (dlg.DoModal() == IDOK) {
        cs.Format(_T("0x%02X"), dlg.m_attrib);
        SetDlgItemText(IDC_MBR_SYS_ID, cs);
        SetDlgItemText(IDC_SYS_STR, fdisk_ids[(dlg.m_attrib & 0xFF)]);
        OnTabItemChange();
    }

    free(mbr_entry_attrbs);
}
