#include "stdafx.h"
#include "pch.h"

#include "ultimate.h"
#include "ultimateDlg.h"

#include "MyImageList.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

UINT MyImageList[] = {
  IDB_FOLDER,
  IDB_FILE,
  IDB_DELETED,
  IDB_FORKED,
  IDB_LABEL,
  IDB_DEVICE,
  IDB_FOLDER_HIDDEN,
  IDB_FILE_HIDDEN,
  
  0xFFFFFFFF  // last marker
};

/////////////////////////////////////////////////////////////////////////////
// CMyImageList property page

IMPLEMENT_DYNCREATE(CMyImageList, CImageList)

CMyImageList::CMyImageList() : CImageList() {
}

CMyImageList::~CMyImageList() {
}

void CMyImageList::DoCreate() {
  CBitmap bmp;
  BITMAP bmpObj;
  int i = 0;
  
  Create(16, 16, ILC_MASK | ILC_COLOR24, 0, 0);
  
  while (MyImageList[i] < 0xFFFFFFFF) {
    bmp.LoadBitmap(MyImageList[i]);
    bmp.GetBitmap(&bmpObj);
    Add(&bmp, RGB(255, 0, 255));  // RGB(255, 0, 255) ????? // Color used to generate the mask. Each pixel of this color in the given bitmap is changed
    i++;                                                    //   to black and the corresponding bit in the mask is set to one.
  }
}
