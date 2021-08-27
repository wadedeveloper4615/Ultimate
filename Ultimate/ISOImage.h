#if !defined(AFX_ISOIMAGE_H__588672E1_1003_41C7_B8F0_45300AC10AFC__INCLUDED_)
#define AFX_ISOIMAGE_H__588672E1_1003_41C7_B8F0_45300AC10AFC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ISOImage.h : header file
//

#include "ISOPrimary.h"
#include "ISOSupple.h"
#include "ISOBoot.h"

#include "ISOBEA.h"
#include "ISONSR.h"

// http://www.ecma-international.org/publications/files/ECMA-ST/Ecma-119.pdf

#define VD_TYPE_BOOT  0  // Boot Record Volume Descriptor
#define VD_TYPE_PRIM  1  // Primary Volume Descriptor
#define VD_TYPE_SUMP  2  // Supplementary Volume Descriptor or Enhanced Volume Descriptor
#define VD_TYPE_VOL   3  // Volume Partition Descriptor
#define VD_TYPE_END 255  // Volume Descriptor Set Terminator 


#pragma pack(push, 1)

/*
struct S_ISO_PVD_3 {  // type 3
  BYTE   type;
  char   ident[5];  // CD001
  BYTE   ver;
  BYTE   resv0;
  char   sys_ident[32];
  char   part_ident[32];
  DWORD  part_location;
  DWORD  part_location_b;
  DWORD  part_size;
  DWORD  part_size_b;
  BYTE   app_use[1960];
};

*/

#pragma pack(pop)

/////////////////////////////////////////////////////////////////////////////
// CISOImage dialog

class CISOImage {

// Construction
public:
  CISOImage();
  ~CISOImage();

// Dialog Data
  //{{AFX_DATA(CISOImage)
    // NOTE - ClassWizard will add data members here.
    //    DO NOT EDIT what you see in these blocks of generated code !
  //}}AFX_DATA
  
  DWORD GetNewColor(int index);
  bool Start(void);
  
  CISOPrimary m_PVD;
  CISOSupple  m_SVD;
  CISOBoot    m_BVD;
  
  CISOBEA     m_BEA;
  CISONSR     m_NSR;
  
// Overrides
  // ClassWizard generate virtual function overrides
  //{{AFX_VIRTUAL(CISOImage)
  protected:
  //}}AFX_VIRTUAL

// Implementation
protected:
  // Generated message map functions
  //{{AFX_MSG(CISOImage)
    // NOTE: the ClassWizard will add member functions here
  //}}AFX_MSG
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ISOIMAGE_H__588672E1_1003_41C7_B8F0_45300AC10AFC__INCLUDED_)
