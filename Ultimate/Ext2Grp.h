#if !defined(AFX_EXT2GRP_H__8C10DE6D_94DE_48C7_A4B4_5C2C0E48AA85__INCLUDED_)
#define AFX_EXT2GRP_H__8C10DE6D_94DE_48C7_A4B4_5C2C0E48AA85__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Ext2Grp.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CExt2Grp dialog

class CExt2Grp : public CDialog
{
// Construction
public:
  CExt2Grp(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
  //{{AFX_DATA(CExt2Grp)
  enum { IDD = IDD_EXT2_GRP };
  CString m_block_bitmap;
  CString m_crc;
  CString m_flags;
  CString m_free_blocks_cnt;
  CString m_free_inodes_cnt;
  CString m_inode_bitmap;
  CString m_inode_table;
  CString m_unused_inode;
  CString m_used_dir_cnt;
  //}}AFX_DATA

  void UpdateDialog(void);
  void UpdateGroup(void);
  
  void   *m_desc_table;
  int     m_groups;      // total groups
  int     m_cur_group;   // index of current displaid group
  DWORD   m_ourflags;
  
// Overrides
  // ClassWizard generated virtual function overrides
  //{{AFX_VIRTUAL(CExt2Grp)
  protected:
  virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
  //}}AFX_VIRTUAL

// Implementation
protected:

  // Generated message map functions
  //{{AFX_MSG(CExt2Grp)
  afx_msg void OnNext();
  afx_msg void OnPrev();
  virtual BOOL OnInitDialog();
  virtual void OnOK();
  //}}AFX_MSG
  DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EXT2GRP_H__8C10DE6D_94DE_48C7_A4B4_5C2C0E48AA85__INCLUDED_)
