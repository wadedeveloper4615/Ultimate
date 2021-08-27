#if !defined(AFX_ISONSR_H__B7DC3890_2AF2_4001_AAE9_86D6F9F73735__INCLUDED_)
#define AFX_ISONSR_H__B7DC3890_2AF2_4001_AAE9_86D6F9F73735__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ISONSR.h : header file
//

#pragma pack(push, 1)

#define  CDROM_SECT_SIZE  2048

/*
TAG:ID:
    1 Primary Volume Descriptor (3/10.1)
    2 Anchor Volume Descriptor Pointer (3/10.2)
    3 Volume Descriptor Pointer (3/10.3)
    4 Implementation Use Volume Descriptor (3/10.4)
    5 Partition Descriptor (3/10.5)
    6 Logical Volume Descriptor (3/10.6)
    7 Unallocated Space Descriptor (3/10.8)
    8 Terminating Descriptor (3/10.9 and 4/14.2)
    9 Logical Volume Integrity Descriptor (3/10.10)
  256 File Set Descriptor (4/14.1)
  257 File Identifier Descriptor (4/14.4)
  258 Allocation Extent Descriptor (4/14.5)
  259 Indirect Entry (4/14.7)
  260 Terminal Entry (4/14.8)
  261 File Entry (4/14.9)
  262 Extended Attribute Header Descriptor (4/14.10.1)
  263 Unallocated Space Entry (4/14.11)
  264 Space Bitmap Descriptor (4/14.12)
  265 Partition Integrity Entry (4/14.13)
  266 Extended File Entry (4/14.17)
*/

typedef struct _DESC_TAG1 {
  WORD   id;
  WORD   ver;
  BYTE   crc;
  BYTE   resv;
  WORD   tagsernum;
  WORD   desccrc;
  WORD   desccrclen;
  DWORD  tagloc;
}DESC_TAG;

typedef struct _EXTENT1 {
  DWORD  length;
  DWORD  location;
}EXTENT;

typedef struct _AVDP1 {
  DESC_TAG tag;
  EXTENT main_vds;
  EXTENT resv_vds;
  BYTE   resv[480];
}AVDP;

typedef struct _CHARSPEC1 {
  BYTE  CharacterSetType;
  BYTE  CharacterSetInfo[63];
}CHARSPEC;

typedef struct _TIMESTAMP1 {
  WORD  TypeAndTimezone;
  INT16 Year;
  BYTE  Month;
  BYTE  Day;
  BYTE  Hour;
  BYTE  Minute;
  BYTE  Second;
  BYTE  Centiseconds;
  BYTE  HundredsofMicroseconds;
  BYTE  Microseconds;
}TIMESTAMP;
 
typedef struct _DESC_PVD1 { /* ECMA 167 3/10.1 */
  DESC_TAG tag;
  DWORD  VolumeDescriptorSequenceNumber;
  DWORD  PrimaryVolumeDescriptorNumber;
  BYTE   VolumeIdentifier[32];
  WORD   VolumeSequenceNumber;
  WORD   MaximumVolumeSequenceNumber;
  WORD   InterchangeLevel;
  WORD   MaximumInterchangeLevel;
  DWORD  CharacterSetList;
  DWORD  MaximumCharacterSetList;
  BYTE   VolumeSetIdentifier[128];
  CHARSPEC DescriptorCharacterSet;
  CHARSPEC ExplanatoryCharacterSet;
  EXTENT VolumeAbstract;
  EXTENT VolumeCopyrightNotice;
  BYTE   ApplicationIdentifier[32];
  TIMESTAMP RecordingDateandTime;
  BYTE   ImplementationIdentifier[32];
  BYTE   ImplementationUse[64];
  DWORD  PredecessorVolumeDescriptorSequenceLocation;
  WORD   Flags;
  BYTE   Reserved[22];
}DESC_PVD;

typedef struct _DESC_LVD1 {
  DESC_TAG tag;
  DWORD  seq_num;
  BYTE   char_set[64];
  BYTE   log_id[128];
  DWORD  block_size;
  BYTE   domain_id[32];
  BYTE   content_use[16];
  DWORD  map_table_len;
  DWORD  partition_maps;
  BYTE   implementation_id[32];
  BYTE   implementation_use[128];
  EXTENT integrity_seq;
  BYTE   maps[1608];
}DESC_LVD;

typedef struct _LVD_MAP_11 {
  BYTE   type;
  BYTE   len;
  WORD   sequ_num;
  WORD   part_num;
}LVD_MAP_1;

typedef struct _LVD_MAP_21 {
  BYTE   type;
  BYTE   len;
  BYTE   id[62];
}LVD_MAP_2;

typedef struct _DESC_PART1 {
  DESC_TAG tag;
  DWORD  sequ_num;
  WORD   flags;
  WORD   number;
  BYTE   contents[32];
  BYTE   content_use[128];
  DWORD  access_type;
  DWORD  start_lba;
  DWORD  sectors;
  BYTE   implement[32];
  BYTE   implement_use[128];
  BYTE   resv[156];
}DESC_PART;

typedef struct _IDENTIFIER1 {
  BYTE    flags;
  BYTE    ident[23];
  BYTE    suffix[8];
}IDENTIFIER;

typedef struct _REC_ADDR1 {
  DWORD   block;
  WORD    part_ref;
}REC_ADDR;

typedef struct _LONG_EXTENT1 {
  DWORD  length;
  REC_ADDR location;
  BYTE   implementation_use[6];
}LONG_EXTENT;

typedef struct _ICB_TAG1 {
  DWORD prior_rec_num;
  WORD  strategy_type;
  WORD  strategy_param;
  WORD  max_num_entries;
  BYTE  resv;
  BYTE  file_type;
  REC_ADDR parent;
  WORD  flags;
}ICB_TAG;

typedef struct _EX_FILE_ENTRY1 {
  DESC_TAG tag;
  ICB_TAG icbtag;
  DWORD  uid;
  DWORD  gid;
  DWORD  permissions;
  WORD   link_count;
  BYTE   rec_format;
  BYTE   rec_display_attrbs;
  DWORD  rec_length;
  DWORD64 info_length;
  DWORD64 object_size;
  DWORD64 log_blocks;
  TIMESTAMP access_time;
  TIMESTAMP modification_time;
  TIMESTAMP creation_time;
  TIMESTAMP attrib_time;
  DWORD  check_point;
  DWORD  resv;
  LONG_EXTENT ext_attrib;
  LONG_EXTENT stream_directory;
  IDENTIFIER implementation_id;
  DWORD64 unique_id;
  DWORD  ex_attribs_len;  // =L_EA
  DWORD  alloc_descp_len; // =L_AD
  //  L_EA Extended Attribute s bytes
  //  L_AD Allocation descriptors bytes
}EX_FILE_ENTRY;

#pragma pack(pop)

/////////////////////////////////////////////////////////////////////////////
// CISONSR dialog

class CISONSR : public CPropertyPage {
  DECLARE_DYNCREATE(CISONSR)

// Construction
public:
  CISONSR();
  ~CISONSR();

// Dialog Data
  //{{AFX_DATA(CISONSR)
  enum { IDD = IDD_ISO_NSR };
  CString	m_avdp_lba;
  CString	m_avdp_len;
  CString	m_avdp_lba_r;
  CString	m_avdp_len_r;
  CString m_part_access_type;
  CString m_part_flags;
  CString m_part_number;
  CString m_part_sectors;
  CString m_part_sequ_num;
  CString m_part_start_lba;
  CString	m_part_contents;
  CString	m_part_implement;
  CString m_log_block_size;
  CString m_log_int_lba;
  CString m_log_int_len;
  CString m_log_map_table_len;
  CString m_log_part_maps;
  CString m_log_seq_num;
  CString	m_log_log_id;
  CString m_log_domain_id;
  CString m_log_implementation_id;
  //}}AFX_DATA
  
  void Start(const DWORD64 lba, DWORD color, BOOL IsNewTab);
  
  bool    m_is_valid;
  DWORD64 m_lba;   // starting lba of this partition
  DWORD64 m_size;  // size of this partition in sectors
  DWORD   m_color; // color used in image bar
  int     m_draw_index;
  
  BYTE  m_descriptor[MAX_SECT_SIZE];
  BYTE  m_avdp_desc[MAX_SECT_SIZE];
  void *m_descriptors;
  DESC_PART *m_part_desc;
  DESC_PVD *m_pvd;
  DESC_LVD *m_lvd;
  LVD_MAP_1 *m_map;
  LVD_MAP_2 *m_map2;
  
// Overrides
  // ClassWizard generate virtual function overrides
  //{{AFX_VIRTUAL(CISONSR)
  protected:
  virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
  //}}AFX_VIRTUAL

// Implementation
protected:
  // Generated message map functions
  //{{AFX_MSG(CISONSR)
  afx_msg void OnApplyB();
  virtual BOOL OnInitDialog();
  afx_msg void OnAvdpTag();
  afx_msg void OnPartFlagsB();
  afx_msg void OnPartTag();
  afx_msg void OnPartAccessTypeB();
  //}}AFX_MSG
  DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ISONSR_H__B7DC3890_2AF2_4001_AAE9_86D6F9F73735__INCLUDED_)
