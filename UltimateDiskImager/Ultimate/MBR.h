#pragma once

#include "MbrEntry.h"
#include "resource.h"

#pragma pack(push, 1)
typedef struct _MBR_CHS_ENTRY {
	BYTE  head;
	BYTE  sector;
	BYTE  cyl;
}MBR_CHS_ENTRY;

typedef struct _MBR_PART_ENTRY {
	BYTE  boot_id;
	MBR_CHS_ENTRY start;
	BYTE  sys_id;
	MBR_CHS_ENTRY end;
	DWORD start_lba;
	DWORD sectors;
}MBR_PART_ENTRY;
#pragma pack(pop)

// CMBR dialog

class CMbr : public CPropertyPage {
	DECLARE_DYNCREATE(CMbr)

	// Construction
public:
	CMbr();
	~CMbr();

	bool Exists(DWORD64 LBA);
	void Begin(void);
	void UpdateEntry(CMbrEntry* Entry, int index);
	void Destroy(void);
	bool IsPMBR(void);

	CString m_Title;
	int     m_index;   // index of MBR[x]

	bool  m_exists;
	DWORD m_color;
	DWORD64 m_lba;
	DWORD64 m_parent_lba;  // in extended MBRs, this is the LBA of the parent MBR
	int   m_draw_index;

	BYTE   m_buffer[MAX_SECT_SIZE];

	CPropertySheet m_Sheet;
	CMbrEntry  m_Pages[4];

	// Dialog Data
	  //{{AFX_DATA(CMbr)
	enum { IDD = IDD_MBR };
	CStatic	m_mbr_pages;
	CString	m_MbrDump;
	CString	m_spt;
	CString	m_head_count;
	CString	m_id_sig;
	CString	m_id_zero;
	//}}AFX_DATA


  // Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CMbr)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

  // Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CMbr)
	virtual BOOL OnInitDialog();
	afx_msg BOOL OnHelpInfo(HELPINFO* pHelpInfo);
	afx_msg void OnMbrApply();
	afx_msg void OnExtractMbr();
	afx_msg void OnUpdateMbr();
	afx_msg void OnUpdateMbrSig();
	afx_msg void OnIdSigUpdate();
	afx_msg void OnIdZeroUpdate();
	afx_msg void OnPrependMBR();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};
