#if !defined(AFX_MYIMAGELIST_H__D10F989D_088D_449D_8E72_E3E414D0E5BA__INCLUDED_)
#define AFX_MYIMAGELIST_H__D10F989D_088D_449D_8E72_E3E414D0E5BA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MyImageList.h : header file
//

// these must stay in the order matching MyImageList[]
#define IMAGE_FOLDER  0
#define IMAGE_FILE    1
#define IMAGE_DELETE  2
#define IMAGE_FORKED  3
#define IMAGE_LABEL   4
#define IMAGE_DEVICE  5
#define IMAGE_FOLDER_HIDDEN  6
#define IMAGE_FILE_HIDDEN    7

class CMyImageList : public CImageList {
  DECLARE_DYNCREATE(CMyImageList)

// Construction
public:
  CMyImageList();
  ~CMyImageList();

  void DoCreate();

// Overrides
  // ClassWizard generate virtual function overrides
  //{{AFX_VIRTUAL(CMyImageList)
  protected:
  //}}AFX_VIRTUAL

// Implementation
protected:

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYIMAGELIST_H__D10F989D_088D_449D_8E72_E3E414D0E5BA__INCLUDED_)
