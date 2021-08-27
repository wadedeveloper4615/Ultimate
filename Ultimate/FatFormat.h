#if !defined(AFX_FATFORMAT_H__900DB027_8CEC_48BA_9C49_40EA8CC45E26__INCLUDED_)
#define AFX_FATFORMAT_H__900DB027_8CEC_48BA_9C49_40EA8CC45E26__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FatFormat.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFatFormat dialog

class CFatFormat : public CDialog {
// Construction
public:
  CFatFormat(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
  //{{AFX_DATA(CFatFormat)
  enum { IDD = IDD_FAT_FORMAT };
  int   m_num_fats;
  int   m_root_entries;
  int   m_sect_cluster;
  CString m_info;
  //}}AFX_DATA
  int      m_fat_size;
  DWORD64  m_sectors;
  int      m_calc_spc;

  int CalcSPC(DWORD64 sectors, int fat_size);
  
// Overrides
  // ClassWizard generated virtual function overrides
  //{{AFX_VIRTUAL(CFatFormat)
  protected:
  virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
  //}}AFX_VIRTUAL

// Implementation
protected:

  // Generated message map functions
  //{{AFX_MSG(CFatFormat)
  virtual void OnOK();
  virtual BOOL OnInitDialog();
  //}}AFX_MSG
  DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FATFORMAT_H__900DB027_8CEC_48BA_9C49_40EA8CC45E26__INCLUDED_)
