#include "stdafx.h"
#include "pch.h"

#include "ultimate.h"
#include "ultimateDlg.h"

#include "Attribute.h"

#include "ISONSR.h"
#include "UDF_Tag.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



// https://wiki.osdev.org/UDF#Volume_Structure




/////////////////////////////////////////////////////////////////////////////
// CISONSR property page

IMPLEMENT_DYNCREATE(CISONSR, CPropertyPage)

CISONSR::CISONSR() : CPropertyPage(CISONSR::IDD) {
  //{{AFX_DATA_INIT(CISONSR)
  m_avdp_lba = _T("");
  m_avdp_len = _T("");
  m_avdp_lba_r = _T("");
  m_avdp_len_r = _T("");
  m_part_access_type = _T("");
  m_part_flags = _T("");
  m_part_number = _T("");
  m_part_sectors = _T("");
  m_part_sequ_num = _T("");
  m_part_start_lba = _T("");
  m_part_contents = _T("");
  m_part_implement = _T("");
  m_log_block_size = _T("");
  m_log_int_lba = _T("");
  m_log_int_len = _T("");
  m_log_map_table_len = _T("");
  m_log_part_maps = _T("");
  m_log_seq_num = _T("");
  m_log_log_id = _T("");
  m_log_domain_id = _T("");
  m_log_implementation_id = _T("");
  //}}AFX_DATA_INIT
  m_descriptors = NULL;
}

CISONSR::~CISONSR() {
  if (m_descriptors)
    free(m_descriptors);
}

void CISONSR::DoDataExchange(CDataExchange* pDX) {
  CPropertyPage::DoDataExchange(pDX);
  //{{AFX_DATA_MAP(CISONSR)
  DDX_Text(pDX, IDC_AVDP_LBA, m_avdp_lba);
  DDX_Text(pDX, IDC_AVDP_LEN, m_avdp_len);
  DDX_Text(pDX, IDC_AVDP_LBA_R, m_avdp_lba_r);
  DDX_Text(pDX, IDC_AVDP_LEN_R, m_avdp_len_r);
  DDX_Text(pDX, IDC_PART_ACCESS_TYPE, m_part_access_type);
  DDX_Text(pDX, IDC_PART_FLAGS, m_part_flags);
  DDX_Text(pDX, IDC_PART_NUMBER, m_part_number);
  DDX_Text(pDX, IDC_PART_SECTOR_COUNT, m_part_sectors);
  DDX_Text(pDX, IDC_PART_SEQ_NUM, m_part_sequ_num);
  DDX_Text(pDX, IDC_PART_START_LBA, m_part_start_lba);
  DDX_Text(pDX, IDC_PART_CONTENTS, m_part_contents);
  DDX_Text(pDX, IDC_PART_IMPLEMENT, m_part_implement);
  DDX_Text(pDX, IDC_LOG_BLOCK_SIZE, m_log_block_size);
  DDX_Text(pDX, IDC_LOG_INT_LBA, m_log_int_lba);
  DDX_Text(pDX, IDC_LOG_INT_LEN, m_log_int_len);
  DDX_Text(pDX, IDC_LOG_MAP_TABLE_LEN, m_log_map_table_len);
  DDX_Text(pDX, IDC_LOG_PART_MAPS, m_log_part_maps);
  DDX_Text(pDX, IDC_LOG_SEQ_NUM, m_log_seq_num);
  DDX_Text(pDX, IDC_LOG_LOG_ID, m_log_log_id);
  DDX_Text(pDX, IDC_LOG_DOMAIN_ID, m_log_domain_id);
  DDX_Text(pDX, IDC_LOG_IMPLEMENTATION_ID, m_log_implementation_id);
  //}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CISONSR, CPropertyPage)
  //{{AFX_MSG_MAP(CISONSR)
  ON_BN_CLICKED(ID_APPLY, OnApplyB)
  ON_BN_CLICKED(IDC_AVDP_TAG, OnAvdpTag)
  ON_BN_CLICKED(IDC_PART_FLAGS_B, OnPartFlagsB)
  ON_BN_CLICKED(IDC_PART_TAG, OnPartTag)
  ON_BN_CLICKED(IDC_PART_ACCESS_TYPE_B, OnPartAccessTypeB)
  //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CISONSR message handlers
BOOL CISONSR::OnInitDialog() {
  CPropertyPage::OnInitDialog();
  
  // set the font of the DUMP window to a fixed font
  CUltimateDlg *dlg = (CUltimateDlg *) AfxGetApp()->m_pMainWnd;
  GetDlgItem(IDC_SYS_USE)->SetFont(&dlg->m_DumpFont);
  
  return TRUE;
}

void CISONSR::Start(const DWORD64 lba, DWORD color, BOOL IsNewTab) {
  CUltimateDlg *dlg = (CUltimateDlg *) AfxGetApp()->m_pMainWnd;
  DESC_TAG *tag;
  DWORD dword;
  CString cs; /////////////////////////
  
  m_lba = lba;
  m_size = 1;
  m_color = color;
  m_is_valid = FALSE;
  
  // read in the anchor sector
  dlg->ReadFromFile(m_avdp_desc, 256, 1);
  AVDP *avdp = (AVDP *) m_avdp_desc;
  
  // send to dialog
  m_avdp_lba.Format("%i", avdp->main_vds.location);
  m_avdp_len.Format("%i", avdp->main_vds.length);
  m_avdp_lba_r.Format("%i", avdp->resv_vds.location);
  m_avdp_len_r.Format("%i", avdp->resv_vds.length);
  
  // TODO: check that avdp is valid.
  int len = avdp->main_vds.length;
  
  dword = (len + (CDROM_SECT_SIZE - 1)) & ~(CDROM_SECT_SIZE - 1);
  if (m_descriptors) free(m_descriptors);
  m_descriptors = malloc(dword);
  dlg->ReadFromFile(m_descriptors, avdp->main_vds.location, dword / CDROM_SECT_SIZE);
  
  tag = (DESC_TAG *) m_descriptors;
  while (len > 0) {
    // TODO: check that tag is valid.
    switch (tag->id) {
      case 0x0001:  // Primary Volume Descriptor
        m_pvd = (DESC_PVD *) tag;
        //cs.Format("AAAA: %i", tag->id);
        //AfxMessageBox(cs);
        //AfxMessageBox("Found Primary Volume Descriptor");
        //DumpIt(cs, tag, 0, 128, FALSE);
        //AfxMessageBox(cs);
        //AfxMessageBox((char *) m_pvd->VolumeSetIdentifier);
        break;
      case 0x0002:  // AVDP (shouldn't find this one)
        //AfxMessageBox("Found AVDP");
        break;
      case 0x0003:  // Volume Descriptor Pointer
        //AfxMessageBox("Found VDP");
        break;
      case 0x0004:  // Implement Use Volume Descriptor
        //AfxMessageBox("Found Implement Use Volume Descriptor");
        break;
      case 0x0005:  // Partition Descriptor
        //AfxMessageBox("Found Partition Descriptor");
        m_part_desc = (DESC_PART *) tag;
        m_part_sequ_num.Format("0x%08X", m_part_desc->sequ_num);
        m_part_flags.Format("0x%04X", m_part_desc->flags);
        m_part_number.Format("0x%04X", m_part_desc->number);
        m_part_access_type.Format("0x%08X", m_part_desc->sequ_num);
        m_part_start_lba.Format("%i", m_part_desc->start_lba);
        m_part_sectors.Format("%i", m_part_desc->sectors);
        memcpy(m_part_contents.GetBuffer(24), &m_part_desc->contents[1], 23); m_part_contents.ReleaseBuffer(23);
        memcpy(m_part_implement.GetBuffer(24), &m_part_desc->implement[1], 23); m_part_implement.ReleaseBuffer(23);
        if (m_part_desc->flags & 1) {
          m_lba = m_part_desc->start_lba;
          m_size = m_part_desc->sectors;
        }
        break;
      case 0x0006:  // Logical Volume Descriptor
        //AfxMessageBox("Found Logical Volume Descriptor");
        m_lvd = (DESC_LVD *) tag;
        m_log_block_size.Format("%i", m_lvd->block_size);
        m_log_int_lba.Format("%i", m_lvd->integrity_seq.location);
        m_log_int_len.Format("%i", m_lvd->integrity_seq.length);
        m_log_map_table_len.Format("%i", m_lvd->map_table_len);
        m_log_part_maps.Format("%i", m_lvd->partition_maps);
        m_log_seq_num.Format("%i", m_lvd->seq_num);
        memcpy(m_log_implementation_id.GetBuffer(24), &m_lvd->implementation_id[1], 23); m_log_implementation_id.ReleaseBuffer(23);
        memcpy(m_log_domain_id.GetBuffer(24), &m_lvd->domain_id[1], 23); m_log_domain_id.ReleaseBuffer(23);
        WideCharToMultiByte(CP_ACP, 0, (LPCWSTR) &m_lvd->log_id[2], -1, m_log_log_id.GetBuffer(128), 128, NULL, NULL); m_log_log_id.ReleaseBuffer(128);
        
        /*
        m_map = (struct LVD_MAP_1 *) m_lvd->maps;
        for (UINT i=0; i<m_lvd->partition_maps; i++) {
          if (m_map->type == 1) {
            cs.Format(" Map %i: type 1:  sequ = %i, part = %i", i, m_map->sequ_num, m_map->part_num);
            AfxMessageBox(cs);
          } else if (m_map->type == 2) {
            m_map2 = (struct LVD_MAP_2 *) m_map;
            cs.Format(" Map %i: type 2:  [%02X %02X %02X %02X]", i, m_map2->id[0], m_map2->id[1], m_map2->id[2], m_map2->id[3]);
            AfxMessageBox(cs);
          } else 
            break;
          m_map = (struct LVD_MAP_1 *) ((BYTE *) m_map + m_map->len);
        }
        */
        break;
      case 0x0007:  // Unallocated Space Descriptor
        //AfxMessageBox("Found Unallocated Space Descriptor");
        break;
      case 0x0008:  // Terminating Descriptor
        //AfxMessageBox("Found Terminating Descriptor");
        len = CDROM_SECT_SIZE;
        break;
      case 0x0009:  // Logical Volume Integrity Descriptor
        //AfxMessageBox("Found Logical Volume Integrity Descriptor");
        break;
      default:
        //AfxMessageBox("Found unknown Volume Descriptor (0x%04X)", tag->id);
        len = CDROM_SECT_SIZE;
    }
    len -= CDROM_SECT_SIZE;
    tag = (DESC_TAG *) ((BYTE *) tag + CDROM_SECT_SIZE);
  }
  
  m_is_valid = TRUE; ///////////////////
  
  
  /*
  struct EX_FILE_ENTRY *entry = (struct EX_FILE_ENTRY *) malloc(MAX_SECT_SIZE);
  dlg->ReadFromFile(entry, m_lba, 1);
  
  CString id;
  memcpy(id.GetBuffer(32), entry->implementation_id.ident, 23); id.ReleaseBuffer(23);
  //cs.Format(id);
  AfxMessageBox(id);
  
  free(entry);
  */
  
}

void CISONSR::OnApplyB() {
  
}

void CISONSR::OnAvdpTag() {
  AVDP *avdp = (AVDP *) m_avdp_desc;
  CUDF_Tag tag;
  
  memcpy(&tag.m_tag, &avdp->tag, sizeof(DESC_TAG));
  if (tag.DoModal() == IDOK)
    memcpy(&avdp->tag, &tag.m_tag, sizeof(DESC_TAG));
}

S_ATTRIBUTES udf_part_flags[] = {
                                           //            |                               | <- max (col 67)
  { (1<<0),                  (1<<0),                  0, "Allocated"                      , {-1, } },
  { 0,                   (DWORD) -1,                 -1, NULL                             , {-1, } }
};

void CISONSR::OnPartFlagsB() {
  CAttribute dlg;
  CString cs;
  
  GetDlgItemText(IDC_PART_FLAGS, cs);
  dlg.m_title = "Partition Flags";
  dlg.m_attrib = convert16(cs);
  dlg.m_attributes = udf_part_flags;
  if (dlg.DoModal() == IDOK) {
    cs.Format("0x%04X", dlg.m_attrib);
    SetDlgItemText(IDC_PART_FLAGS, cs);
  }
}

void CISONSR::OnPartTag() {
  CUDF_Tag tag;
  
  memcpy(&tag.m_tag, &m_part_desc->tag, sizeof(DESC_TAG));
  if (tag.DoModal() == IDOK)
    memcpy(&m_part_desc->tag, &tag.m_tag, sizeof(DESC_TAG));
}

S_ATTRIBUTES udf_part_access[] = {
                                           //            |                               | <- max (col 67)
  { 0,                   0xFFFFFFFF,                  0, "Not Specified"                  , {-1, } },
  { 1,                   0xFFFFFFFF,                  1, "Read Only"                      , {-1, } },
  { 2,                   0xFFFFFFFF,                  2, "Write Once"                     , {-1, } },
  { 3,                   0xFFFFFFFF,                  3, "Rewritable"                     , {-1, } },
  { 4,                   0xFFFFFFFF,                  4, "Overwritable"                   , {-1, } },
  { 0,                   (DWORD) -1,                 -1, NULL                             , {-1, } }
};

void CISONSR::OnPartAccessTypeB() {
  CAttribute dlg;
  CString cs;
  
  GetDlgItemText(IDC_PART_ACCESS_TYPE, cs);
  dlg.m_title = "Access Type";
  dlg.m_attrib = convert32(cs);
  dlg.m_attributes = udf_part_access;
  if (dlg.DoModal() == IDOK) {
    cs.Format("0x%08X", dlg.m_attrib);
    SetDlgItemText(IDC_PART_ACCESS_TYPE, cs);
  }
}
