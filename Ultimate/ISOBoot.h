#if !defined(AFX_ISOBOOT_H__ABC3C8F3_34B3_4500_80A3_74B9AED8E6DA__INCLUDED_)
#define AFX_ISOBOOT_H__ABC3C8F3_34B3_4500_80A3_74B9AED8E6DA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ISOBoot.h : header file
//
#pragma pack(push, 1)

typedef struct _S_ISO_BVD {
  BYTE   type;      // 0
  char   ident[5];  // CD001
  BYTE   ver;       // 
  char   sys_ident[32];
  char   boot_ident[32];
  DWORD  boot_cat;
  BYTE   sys_use[1973];
}S_ISO_BVD;

typedef struct _S_ISO_BC_VALIDATION {
  BYTE   id;
  BYTE   platform;
  WORD   resv0;
  char   ident[24];
  WORD   crc;         // word offset 14
  BYTE   key55;
  BYTE   keyAA;
}S_ISO_BC_VALIDATION;

typedef struct _S_ISO_BC_ENTRY_EXT {
  BYTE   bootable;
  BYTE   media;               // 0 = no boot image, standard image only
                              // 1 = 1.22m
                              // 2 = 1.44m
                              // 3 = 2.88m
                              // 4 = hard drive
  WORD   load_seg;            // 0 = 0x07C0, else segment to use
  BYTE   sys_type;
  BYTE   resv0;
  WORD   load_cnt;
  DWORD  load_rba;
  BYTE   resv1[20];
}S_ISO_BC_ENTRY_EXT;

typedef struct _S_ISO_BC_END_ENTRY {
  BYTE   id;
  BYTE   platform;
  WORD   num;
  BYTE   resv1[28];
}S_ISO_BC_END_ENTRY;

typedef struct _S_ISO_BOOT_CAT {
  S_ISO_BC_VALIDATION val_entry;
  S_ISO_BC_ENTRY_EXT init_entry;
  S_ISO_BC_END_ENTRY end_entry;
  BYTE   filler[1952];
}S_ISO_BOOT_CAT;

#pragma pack(pop)

/////////////////////////////////////////////////////////////////////////////
// CISOBoot dialog

class CISOBoot : public CPropertyPage
{
  DECLARE_DYNCREATE(CISOBoot)

// Construction
public:
  CISOBoot();
  ~CISOBoot();

// Dialog Data
  //{{AFX_DATA(CISOBoot)
  enum { IDD = IDD_ISO_BVD };
  CComboBox	m_di_media;
  CComboBox	m_di_bootable;
  CComboBox m_val_platform;
  int     m_type;
  int     m_boot_cat_lba;
  CString	m_cd001;
  CString	m_version;
  CString	m_sys_id;
  CString	m_sys_use;
  CString	m_boot_id;
  CString m_val_crc;
  CString m_val_id;
  CString m_val_ident;
  CString m_val_key55;
  CString m_val_keyaa;
  CString m_val_reserved;
  CString	m_di_count;
  CString	m_di_lba;
  CString	m_di_load_seg;
  CString	m_di_reserved;
  CString	m_di_sys_type;
  //}}AFX_DATA

  void Start(const DWORD64 lba, DWORD color, BOOL IsNewTab);
  void SendToDialog(void);
  void ReceiveFromDialog(void);
  
  bool    m_is_valid;
  DWORD64 m_lba;   // starting lba of this partition
  DWORD64 m_size;  // size of this partition in sectors
  DWORD   m_color; // color used in image bar
  int     m_draw_index;
  
  BYTE  m_descriptor[MAX_SECT_SIZE];
  BYTE  m_boot_cat[MAX_SECT_SIZE];
  
// Overrides
  // ClassWizard generate virtual function overrides
  //{{AFX_VIRTUAL(CISOBoot)
  protected:
  virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
  //}}AFX_VIRTUAL

// Implementation
protected:
  // Generated message map functions
  //{{AFX_MSG(CISOBoot)
  afx_msg void OnApplyB();
  virtual BOOL OnInitDialog();
  afx_msg void OnValCrcUpdate();
  afx_msg void OnValKeyUpdate();
  afx_msg void OnDiInsert();
  afx_msg void OnDiExtract();
  afx_msg void OnClearReserved();
  //}}AFX_MSG
  DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ISOBOOT_H__ABC3C8F3_34B3_4500_80A3_74B9AED8E6DA__INCLUDED_)
