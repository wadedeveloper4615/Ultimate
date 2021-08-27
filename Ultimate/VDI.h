#if !defined(AFX_VDI_H__05E1ABFD_D61F_47B2_A6AF_92EF054CAEAD__INCLUDED_)
#define AFX_VDI_H__05E1ABFD_D61F_47B2_A6AF_92EF054CAEAD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// VHD.h : header file
//

#pragma pack(push, 1)

// https://forums.virtualbox.org/viewtopic.php?t=8046
typedef struct _VDI_HEADER1 {
  BYTE   cookie[64];         // '<<< **** VirtualBox Disk Image >>>'
  DWORD  signature;          // 0xBEDA017F
  DWORD  version;            // 0x00010001 // 1.1
  DWORD  size_header;        // size of the header below (usually 0x190 for 512-byte sectors)
  DWORD  image_type;         // image type (2 = Fixed, 1 = Dynamic)
  DWORD  image_flags;        // image flags
  BYTE   description[256];   // image description
  DWORD  offset_blocks;      // byte offset in file where the block table starts
  DWORD  offset_data;        // byte offset in file where the data blocks start
  DWORD  cylinders;          // cylinders value
  DWORD  heads;              // heads value
  DWORD  sectors;            // sectors value
  DWORD  sector_size;        // size of a sector
  DWORD  unused;             // unused
  DWORD64 disk_size;         // disk size in bytes
  DWORD  block_size;         // block size in bytes
  DWORD  block_extra;        // block extra data
  DWORD  block_count;        // blocks in this image
  DWORD  blocks_allocated;   // count of blocks allocated
  S_GUID uuid;        // UUID
  S_GUID snap;        // SNAP
  S_GUID link;        // LINK
  S_GUID parent;      // PARENT
  BYTE   reserved[56];       // remaining to fill 512-byte sector
}VDI_HEADER;

#pragma pack(pop)

#define VDI_IMAGE_TYPE_DYNAMIC   1
#define VDI_IMAGE_TYPE_FLAT      2

#define VDI_BLOCK_ID_UNALLOCATED  0xFFFFFFFF
#define VDI_BLOCK_ID_ZERO_BLOCK   0xFFFFFFFE

/////////////////////////////////////////////////////////////////////////////
// CVDI dialog

class CVDI : public CDialog
{
// Construction
public:
  CVDI(CWnd* pParent = NULL); // standard constructor
  
  BYTE   m_buffer[MAX_SECT_SIZE];
  
// Dialog Data
  //{{AFX_DATA(CVHD)
  enum { IDD = IDD_VDI };
  CString m_cookie;
  CString m_signature;
  CString m_version;
  CString m_size_header;
  CString m_image_type;
  CString m_image_flags;
  CString m_description;
  CString m_offset_blocks;
  CString m_offset_data;
  CString m_sector_size;
  CString m_unused;
  CString m_disk_size;
  CString m_block_size;
  CString m_block_extra;
  CString m_block_count;
  CString m_block_allocated;
  CString m_uuid;
  CString m_snap;
  CString m_link;
  CString m_parent;
  CString	m_cylinder;
  CString	m_head;
  CString	m_sect_track;
  //}}AFX_DATA


// Overrides
  // ClassWizard generate virtual function overrides
  //{{AFX_VIRTUAL(CVDI)
  protected:
  virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
  //}}AFX_VIRTUAL

// Implementation
protected:
  // Generated message map functions
  //{{AFX_MSG(CVDI)
  virtual BOOL OnInitDialog();
  afx_msg void OnApply();
  afx_msg void OnSigUpdate();
  afx_msg void OnUUIDUpdate();
  afx_msg void OnSnapUpdate();
  afx_msg void OnLinkUpdate();
  afx_msg void OnParentUpdate();
  afx_msg void OnChangeSize();
  afx_msg void OnChangeType();
  //}}AFX_MSG
  DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VDI_H__05E1ABFD_D61F_47B2_A6AF_92EF054CAEAD__INCLUDED_)
