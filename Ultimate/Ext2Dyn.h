#if !defined(AFX_EXT2DYN_H__8180705D_F81A_461A_B42C_DC597BC49B0A__INCLUDED_)
#define AFX_EXT2DYN_H__8180705D_F81A_461A_B42C_DC597BC49B0A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Ext2Dyn.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CExt2Dyn dialog

class CExt2Dyn : public CDialog
{
// Construction
public:
  CExt2Dyn(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
  //{{AFX_DATA(CExt2Dyn)
  enum { IDD = IDD_EXT2_DYN };
  CString m_algo_usage_bitmap;
  CString m_block_gr_num;
  CString m_ext2_guid;
  CString m_feature_comp;
  CString m_feature_incomp;
  CString m_feature_ro_comp;
  CString m_first_inode;
  CString m_inode_size;
  CString m_last_mount;
  CString m_pre_alloc_blocks;
  CString m_pre_alloc_dir_blocks;
  CString m_pre_alloc_gdt_blocks;
  CString m_vol_name;
  //}}AFX_DATA


// Overrides
  // ClassWizard generated virtual function overrides
  //{{AFX_VIRTUAL(CExt2Dyn)
  protected:
  virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
  //}}AFX_VIRTUAL

// Implementation
protected:

  // Generated message map functions
  //{{AFX_MSG(CExt2Dyn)
  afx_msg void OnFeatureComp();
  afx_msg void OnFeatureIncomp();
  afx_msg void OnFeatureRoIncomp();
  //}}AFX_MSG
  DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EXT2DYN_H__8180705D_F81A_461A_B42C_DC597BC49B0A__INCLUDED_)
