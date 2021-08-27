#if !defined(AFX_EMBR_H__4692C7EB_8C3C_4273_A1BB_A40B6A0CB407__INCLUDED_)
#define AFX_EMBR_H__4692C7EB_8C3C_4273_A1BB_A40B6A0CB407__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Embr.h : header file
//

#include "EmbrEntry.h"

#define MAX_EMBR_ENTRIES  16

#pragma pack(push, 1)

#define EMBR_SIG_SIG  0x456D627272626D45ULL
typedef struct _S_EMBR_SIG {
  DWORD64  sig;
  WORD     offset;     // sectors to S_EMBR_HDR (LBA of S_EMBR_HDR)
  WORD     remaining;
  WORD     boot_sig;
}S_EMBR_SIG;

#define EMBR_HDR_SIG0   0x52424D45  // EMBR
#define EMBR_HDR_SIG1   0x454D4252  // RBME

typedef struct _S_EMBR_HDR {
  DWORD   sig0;          // 'EMBR'
  DWORD   crc;           // crc of this sector
  WORD    entry_count;   // total entries in EMBR (reserved in all but first sector)
  BYTE    boot_delay;    // seconds to delay before booting last booted (reserved in all but first sector)
  BYTE    version;       //  1.05 = 001_00101b
  DWORD64 total_sectors; // total sectors this eMBR encompasses
  BYTE    resv1[8];      // 
  DWORD   sig1;          // 'RBME'
}S_EMBR_HDR;

#define EMBR_ENTRY_SIG   0x52424D65
#define EMBR_VALID_ENTRY  (1<<0)
#define EMBR_HIDDN_ENTRY  (1<<1)

typedef struct _S_EMBR_ENTRY {
  DWORD   flags;       // bit 0 = 1 = valid, bit 1 = 1 = hidden (rest are preserved)
  DWORD   signature;   // 'eMBR'
  DWORD64 starting_sector;
  DWORD64 sector_count;
  BYTE    description[64];
  DWORD64 date_created;      // Secs since 01Jan1980
  DWORD64 date_last_booted;  // Secs since 01Jan1980
  DWORD64 OS_signature;
  BYTE    reserved[16];
}S_EMBR_ENTRY;

#pragma pack(pop)

/////////////////////////////////////////////////////////////////////////////
// CEmbr dialog

class CEmbr : public CPropertyPage
{
  DECLARE_DYNCREATE(CEmbr)

// Construction
public:
  CEmbr();
  ~CEmbr();
  
  bool Exists(DWORD64 LBA);
  void Begin(void);
  void UpdateEntry(CEmbrEntry *Entry, int index);
  BOOL CheckEntry(int index);
  void Destroy(void);
  
  bool  m_exists;
  DWORD m_color;
  DWORD64 m_lba;
  int   m_draw_index;
  
  bool    m_hdr_valid;
  void   *m_entry_buffer;
  int     m_embr_entries;
  DWORD64 m_total_sectors;
  
  CPropertySheet m_Sheet;
  CEmbrEntry  m_Pages[MAX_EMBR_ENTRIES];
  
// Dialog Data
  //{{AFX_DATA(CEmbr)
  enum { IDD = IDD_EMBR };
  CStatic m_embr_pages;
  CString m_boot_sig;
  CString m_entry_offset;
  CString m_remaining;
  CString m_embr_sig;
  CString m_embr_dump;
  CString m_entry_crc;
  CString m_entries;
  CString m_reserved;
  CString m_sig0;
  CString m_sig1;
  int		  m_boot_delay;
  CString	m_tot_sectors;
  CString	m_version;
  //}}AFX_DATA


// Overrides
  // ClassWizard generate virtual function overrides
  //{{AFX_VIRTUAL(CEmbr)
  protected:
  virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
  //}}AFX_VIRTUAL

// Implementation
protected:
  // Generated message map functions
  //{{AFX_MSG(CEmbr)
  afx_msg void OnEmbrApply();
  virtual BOOL OnInitDialog();
  afx_msg BOOL OnHelpInfo(HELPINFO *pHelpInfo);
  afx_msg void OnBootSigUpdate();
  afx_msg void OnCrcSet();
  afx_msg void OnResvClear();
  afx_msg void OnSig0Set();
  afx_msg void OnSig1Set();
  afx_msg void OnSignatureSet();
  afx_msg void OnUpdateCode();
  afx_msg void OnChangeEmbrVersion();
  afx_msg void OnUpdateTotSects();
  //}}AFX_MSG
  DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EMBR_H__4692C7EB_8C3C_4273_A1BB_A40B6A0CB407__INCLUDED_)
