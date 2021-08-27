#if !defined(AFX_FYSOSSIG_H__6B48FDAC_9B59_4344_8409_A3F59F60F6A3__INCLUDED_)
#define AFX_FYSOSSIG_H__6B48FDAC_9B59_4344_8409_A3F59F60F6A3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FYSOSSig.h : header file
//

#pragma pack(push, 1)

typedef struct _S_FYSOSSIG {
  DWORD32  sig;
  DWORD64  base;
  WORD     boot_sig;
}S_FYSOSSIG;

#pragma pack(pop)

#define S_FYSOSSIG_OFFSET  (512 - sizeof(S_FYSOSSIG))

/////////////////////////////////////////////////////////////////////////////
// CFYSOSSig dialog

class CFYSOSSig : public CDialog {
// Construction
public:
  CFYSOSSig(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
  //{{AFX_DATA(CFYSOSSig)
  enum { IDD = IDD_FYSOS_SIG };
  CString	m_sig_base;
  CString	m_boot_sig;
  CString	m_fysos_sig;
  //}}AFX_DATA
  
  DWORD64 m_base_lba;
  
// Overrides
  // ClassWizard generated virtual function overrides
  //{{AFX_VIRTUAL(CFYSOSSig)
  protected:
  virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
  //}}AFX_VIRTUAL

// Implementation
protected:

  // Generated message map functions
  //{{AFX_MSG(CFYSOSSig)
  virtual void OnOK();
  afx_msg void OnUpdateSig();
  afx_msg void OnUpdateBootSig();
  afx_msg void OnUpdateBase();
  //}}AFX_MSG
  DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FYSOSSIG_H__6B48FDAC_9B59_4344_8409_A3F59F60F6A3__INCLUDED_)
