#include "stdafx.h"
#include "pch.h"

#include "ultimate.h"
#include "ultimateDlg.h"

#include "ISOImage.h"

#include "ISOBoot.h"
#include "ISOPrimary.h"
#include "ISOSupple.h"

#include "ISOBEA.h"
#include "ISONSR.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CISOImage property page

CISOImage::CISOImage() {
  //{{AFX_DATA_INIT(CISOImage)
    // NOTE: the ClassWizard will add member initialization here
  //}}AFX_DATA_INIT
}

CISOImage::~CISOImage() {
}

/////////////////////////////////////////////////////////////////////////////
// CISOImage message handlers

// ISO colors will have a ???? shade to them.
DWORD CISOImage::GetNewColor(int index) {
  int r = ((106 - (index * 20)) > -1) ? (106 - (index * 20)) : 0;
  int g = ((126 - (index * 18)) > -1) ? (126 - (index * 18)) : 0;
  int b = ((239 - (index *  2)) > -1) ? (239 - (index *  2)) : 0;
  return RGB(r, g, b);
}

// LBA = lba of volume descriptor (16 -> end)
bool CISOImage::Start(void) {
  CUltimateDlg *dlg = (CUltimateDlg *) AfxGetApp()->m_pMainWnd;
  BYTE buffer[MAX_SECT_SIZE];
  DWORD64 lba = 16;
  int     cindex = 0;
  BOOL    cont = TRUE;
  
  while (cont) {
    dlg->ReadFromFile(buffer, lba, 1);
    if (memcmp(buffer + 1, "CD001", 5) == 0) {
      switch (buffer[0]) {
        case VD_TYPE_BOOT:
          memcpy(m_BVD.m_descriptor, buffer, 2048);
          m_BVD.Start(lba, GetNewColor(cindex), TRUE);
          dlg->m_TabControl.AddPage(&m_BVD);
          break;
        case VD_TYPE_PRIM:
          memcpy(m_PVD.m_descriptor, buffer, 2048);
          m_PVD.Start(lba, GetNewColor(cindex), TRUE);
          dlg->m_TabControl.AddPage(&m_PVD);
          break;
        case VD_TYPE_SUMP:
          memcpy(m_SVD.m_descriptor, buffer, 2048);
          m_SVD.Start(lba, GetNewColor(cindex), TRUE);
          dlg->m_TabControl.AddPage(&m_SVD);
          break;
        case VD_TYPE_VOL:
          //dlg->m_ISONames[index] = "Volume Partition";
          AfxMessageBox("Found Volume Desc");
          break;
        case VD_TYPE_END:
          //AfxMessageBox("Found End");
          cont = FALSE;
          break;
        default:
          //dlg->m_ISONames[index] = "Unknown";
          AfxMessageBox("Found Other");
          cont = FALSE;
          break;
      }
    } else if (memcmp(buffer + 1, "BEA01", 5) == 0) {
      memcpy(m_BEA.m_descriptor, buffer, 2048);
      m_BEA.Start(lba, GetNewColor(cindex), TRUE);
      dlg->m_TabControl.AddPage(&m_BEA);
    } else if ((memcmp(buffer + 1, "NSR02", 5) == 0) ||
               (memcmp(buffer + 1, "NSR03", 5) == 0)) {
      memcpy(m_NSR.m_descriptor, buffer, 2048);
      m_NSR.Start(lba, GetNewColor(cindex), TRUE);
      dlg->m_TabControl.AddPage(&m_NSR);
    } else
      break;
    lba++;
    cindex++;
  }
  
  return TRUE;
}
