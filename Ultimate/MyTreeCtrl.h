#if !defined(AFX_MYTREECTRL_H__D10F989D_088D_449D_8E72_E3E414D0E5BA__INCLUDED_)
#define AFX_MYTREECTRL_H__D10F989D_088D_449D_8E72_E3E414D0E5BA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MyImageList.h : header file
//

// list of items we "append" to each tree item
//#define MAX_ITEMS_ALLOWED  4096
#define MAX_ITEM_SIZE      (4096-16)
typedef struct _S_ITEMS1 {
  int  IsDir;   // 0 = file, 1 = dir, -1 = root dir
  BYTE reserved[15];
  BYTE fs_item[MAX_ITEM_SIZE];
}S_ITEMS;

class CMyTreeCtrl : public CTreeCtrl {
  DECLARE_DYNCREATE(CMyTreeCtrl)

// Construction
public:
  CMyTreeCtrl();
  ~CMyTreeCtrl();
  
  HTREEITEM Insert(LPCTSTR lpszItem, DWORD Flags, int nImage, int nSelectedImage, HTREEITEM hParent);
  void *GetDataStruct(HTREEITEM hItem);
  HTREEITEM GetFullPath(HTREEITEM hItem, int *IsDir, CString &csName, CString &csPath, BOOL Visible);
  int IsDir(HTREEITEM hItem);
  HTREEITEM FindFirst(HTREEITEM hParent, LPCTSTR text);
  
  S_ITEMS *m_items;
  int m_item_count;
  int m_item_alloc; // count of item blocks allocated for use
  
  // our search parameters
  HTREEITEM m_hStart;
  CString m_csSearchStr;
  BOOL m_bCase;
  HTREEITEM SearchTree(HTREEITEM hStart, CString csSearchStr, const BOOL bCase);
  HTREEITEM Search(void);
  
// Overrides
  // ClassWizard generate virtual function overrides
  //{{AFX_VIRTUAL(CMyTreeCtrl)
  afx_msg BOOL DeleteAllItems(void);
  protected:
  //}}AFX_VIRTUAL

// Implementation
protected:

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYTREECTRL_H__D10F989D_088D_449D_8E72_E3E414D0E5BA__INCLUDED_)
