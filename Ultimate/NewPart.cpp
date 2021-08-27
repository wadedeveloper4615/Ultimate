#include "stdafx.h"
#include "pch.h"

#include "ultimate.h"
#include "ultimateDlg.h"

#include "NewImage.h"
#include "NewPart.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNewPart property page

IMPLEMENT_DYNCREATE(CNewPart, CPropertyPage)

CNewPart::CNewPart() : CPropertyPage(CNewPart::IDD) {
  //{{AFX_DATA_INIT(CNewPart)
  m_filename = _T("");
  m_sectors = 10240;
  m_name = _T("");
  m_bootable = FALSE;
  m_emulation = 0;
  //}}AFX_DATA_INIT
  m_dirty = FALSE;
}

CNewPart::~CNewPart() {
}

void CNewPart::DoDataExchange(CDataExchange* pDX) {
  CPropertyPage::DoDataExchange(pDX);
  //{{AFX_DATA_MAP(CNewPart)
  DDX_Text(pDX, IDC_NEW_PART_NAME, m_filename);
  DDX_Text(pDX, IDC_SECTORS, m_sectors);
  DDX_Text(pDX, IDC_NEW_NAME, m_name);
  DDX_Check(pDX, IDC_BOOTABLE, m_bootable);
  DDX_Radio(pDX, IDC_ISO9660_NO_EMU, m_emulation);
  //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CNewPart, CPropertyPage)
  //{{AFX_MSG_MAP(CNewPart)
  ON_EN_CHANGE(IDC_NEW_PART_NAME, OnPartChanged)
  ON_BN_CLICKED(IDC_BROWSE, OnBrowse)
  ON_EN_CHANGE(IDC_SECTORS, OnPartChanged)
  ON_MESSAGE(WM_DROPFILES, OnDropFiles)
  ON_EN_CHANGE(IDC_NEW_NAME, OnPartChanged)
  //}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL CNewPart::OnInitDialog() {
  CPropertyPage::OnInitDialog();
  
  // only show the CDROM stuff on the first page
  CPropertySheet *Sheet = (CPropertySheet *) GetParent();
  if (Sheet->GetPageIndex(this) > 0) {
    GetDlgItem(IDC_BOOTABLE)->ShowWindow(SW_HIDE);
    GetDlgItem(IDC_BOOT_FRAME)->ShowWindow(SW_HIDE);
    GetDlgItem(IDC_ISO9660_NO_EMU)->ShowWindow(SW_HIDE);
    GetDlgItem(IDC_ISO9660_120)->ShowWindow(SW_HIDE);
    GetDlgItem(IDC_ISO9660_144)->ShowWindow(SW_HIDE);
    GetDlgItem(IDC_ISO9660_288)->ShowWindow(SW_HIDE);
    GetDlgItem(IDC_ISO9660_HD)->ShowWindow(SW_HIDE);
  }
  OnSizeChanged();

  return TRUE;
}

void CNewPart::OnPartChanged() {
  if (!m_dirty) {
    CPropertySheet *Sheet = (CPropertySheet *) GetParent();
    TC_ITEM ti;
    char szText[64];
    ti.mask = TCIF_TEXT;
    ti.pszText = szText;
    ti.cchTextMax = 64;
    Sheet->GetTabControl()->GetItem(m_index, &ti);
    strcat(szText, "*");
    Sheet->GetTabControl()->SetItem(m_index, &ti);
    m_dirty = TRUE;
  }
  
  OnSizeChanged();
}

void CNewPart::OnSizeChanged() {
  CNewImage *parent = (CNewImage *) m_parent;
  CString megs;

  UpdateData(TRUE); // bring from Dialog
  if (((size_t) m_sectors * parent->m_sector_size) < (size_t) (1024 * 1024 * 1024))
    megs.Format("%.3f Meg", (float) ((double) ((size_t) m_sectors * parent->m_sector_size) / (double) (size_t) (1024 * 1024)));
  else
    megs.Format("%.3f Gig", (float) ((double) ((size_t) m_sectors * parent->m_sector_size) / (double) (size_t) (1024 * 1024 * 1024)));
  SetDlgItemText(IDC_SIZE_MEGS, megs);
}

void CNewPart::OnBrowse() {
  CString csPath;
  
  CFileDialog dlg (
    TRUE,             // Create an open file dialog
    _T(".img"),       // Default file extension
    NULL,             // Default Filename
    OFN_FILEMUSTEXIST | OFN_HIDEREADONLY | OFN_EXPLORER, // flags
    _T(".img files (.img)|*.img|")    // Filter string
    _T(".bin files (.bin)|*.bin|")    // Filter string
    _T("All Files (*.*)|*.*|")        // Filter string
    _T("|")
  );
  if (dlg.DoModal() != IDOK)
    return;
  
  POSITION pos = dlg.GetStartPosition();
  csPath = dlg.GetNextPathName(pos);
  
  UpdateData(TRUE); // bring from Dialog
  m_filename = csPath;
  
  CFile file;
  if (file.Open(csPath, CFile::modeRead | CFile::typeBinary | CFile::shareDenyWrite, NULL) != 0) {
    CUltimateDlg *dlg = (CUltimateDlg *) AfxGetApp()->m_pMainWnd;
    LARGE_INTEGER file_length = dlg->GetFileLength((HANDLE) file.m_hFile);
    CNewImage *parent = (CNewImage *) m_parent;
    DWORD sectors_needed = (DWORD) ((file_length.QuadPart + (parent->m_sector_size - 1)) / parent->m_sector_size);
    if (sectors_needed > m_sectors)
      m_sectors = sectors_needed;
    file.Close();
  }
  
  UpdateData(FALSE); // Send to Dialog
  m_dirty = TRUE;
}

LRESULT CNewPart::OnDropFiles(WPARAM wParam, LPARAM lParam) {
  /*
  CString cs;
  char szDroppedFile[MAX_PATH];
  
  DragQueryFile((HDROP) wParam, // Struture Identifier
        0,                // Index (of 0xFFFFFFFF to get count of files dropped)
        szDroppedFile,    // Droped File Name
        MAX_PATH);        // Max char 
  
  int index = m_Sheet.GetActiveIndex();
  if (m_Parts[index].m_dirty) {
    cs.Format("Update partition with new file: %s", szDroppedFile);
    if (AfxMessageBox(cs, MB_YESNO, 0) != IDYES)
      return 0;
  }
  
  cs = szDroppedFile;
  UpdateEntry(cs, index);
  */

  AfxMessageBox("Todo");
  
  return 0;
}
