#if !defined(AFX_MYSTATIC_H__D10F989D_088D_449D_8E72_E3E414D0E5BA__INCLUDED_)
#define AFX_MYSTATIC_H__D10F989D_088D_449D_8E72_E3E414D0E5BA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MyStatic.h : header file
//

#define IMAGE_BAR_MAX  64
typedef struct _S_IMAGE_BAR1 {
  CPropertyPage *page;
  int  left;
  int  right;
  DWORD color;
  BOOL filled;
  char title[32];
}S_IMAGE_BAR;

class CMyStatic : public CStatic {
  DECLARE_DYNCREATE(CMyStatic)

// Construction
public:
  CMyStatic();
  ~CMyStatic();
  
  int AddItem(int left, int right, DWORD color, BOOL filled, char *title, CPropertyPage *page);
  void UpdateTitle(int index, char *title);
  void Clear();
  
  S_IMAGE_BAR m_items[IMAGE_BAR_MAX];
  int m_item_count;
  CPropertySheet *m_TabControl;
  
// Overrides
  // ClassWizard generate virtual function overrides
  //{{AFX_VIRTUAL(CMyStatic)
  protected:
  //}}AFX_VIRTUAL

// Implementation
protected:
  
  // Generated message map functions
  //{{AFX_MSG(CMyStatic)
  afx_msg void OnPaint();
  afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
  //}}AFX_MSG
  DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYSTATIC_H__D10F989D_088D_449D_8E72_E3E414D0E5BA__INCLUDED_)
