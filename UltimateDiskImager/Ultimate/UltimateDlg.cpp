// CUltimateDlg.cpp : implementation file
//

#include "pch.h"
#include "Ultimate.h"
#include "UltimateDlg.h"
#include "afxdialogex.h"


// CUltimateDlg dialog

IMPLEMENT_DYNAMIC(CUltimateDlg, CDialog)

CUltimateDlg::CUltimateDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_ULTIMATE_DIALOG, pParent)
{
	m_force_gpt_presence = FALSE;
	m_force_mbr_presence = FALSE;
	m_force_gpt_enum = TRUE;
	m_ignore_empty_gpt_entries = TRUE;
	m_force_readonly = TRUE;
	m_sect_size = 512;
	m_sect_size_option = 0; // default to 512-byte sectors
	m_force_no_mbr_presence = FALSE;
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_file_type = DLG_FILE_TYPE_FLAT;
	m_dflt_sect_size = 512;
	m_isISOImage = FALSE;
	m_hasVHD = FALSE;
	m_MBRCount = 0;
	m_FatCount = 0;
	m_Ext2Count = 0;
	m_ExFatCount = 0;
	m_LeanCount = 0;
	m_NTFSCount = 0;
	m_SFSCount = 0;
	m_FYSCount = 0;
	m_UCount = 0;
	m_overwrite_okay = FALSE;
	m_FSZCount = 0;
	m_bIsOpen = false;
	m_file_length.QuadPart = 0;
}

CUltimateDlg::~CUltimateDlg()
{
}

void CUltimateDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_IMAGE_BAR, m_image_bar);
	DDX_Control(pDX, IDC_TABS, m_StaticTabs);
	DDX_Check(pDX, IDC_FORCE_GPT, m_force_gpt_presence);
	DDX_Check(pDX, IDC_FORCE_MBR, m_force_mbr_presence);
	DDX_Check(pDX, IDC_FORCE_NO_MBR, m_force_no_mbr_presence);
	DDX_Check(pDX, IDC_FORCE_GPT_ENUM, m_force_gpt_enum);
	DDX_Check(pDX, IDC_IGNORE_MT_GPT_ENTRIES, m_ignore_empty_gpt_entries);
	DDX_Check(pDX, IDC_FORCE_READONLY, m_force_readonly);
	DDX_Radio(pDX, IDC_SECT_SIZE_512, m_sect_size_option);
}


BEGIN_MESSAGE_MAP(CUltimateDlg, CDialog)
	ON_BN_CLICKED(IDC_FORCE_MBR, &CUltimateDlg::OnForceMbr)
	ON_BN_CLICKED(IDC_FORCE_NO_MBR, &CUltimateDlg::OnForceNoMbr)
	ON_COMMAND(ID_FILE_OPEN, &CUltimateDlg::OnFileOpen)
	ON_BN_CLICKED(IDC_SECT_SIZE_512, OnChangeSectSize)
	ON_BN_CLICKED(IDC_SECT_SIZE_1024, OnChangeSectSize)
	ON_BN_CLICKED(IDC_SECT_SIZE_2048, OnChangeSectSize)
	ON_BN_CLICKED(IDC_SECT_SIZE_4096, OnChangeSectSize)
END_MESSAGE_MAP()


// CUltimateDlg message handlers
unsigned int g_sector_sizes[4] = { 512, 1024, 2048, 4096 };

BOOL CUltimateDlg::OnInitDialog()
{
	m_force_readonly = AfxGetApp()->GetProfileInt(_T("Settings"), _T("ForceReadOnly"), -1);
	if (m_force_readonly == -1) {
		m_force_readonly = TRUE;
	}

	// Sector Size
	m_sect_size_option = AfxGetApp()->GetProfileInt(_T("Settings"), _T("DefaultSectSize"), 0);
	m_sect_size = m_dflt_sect_size = g_sector_sizes[m_sect_size_option];
	m_TabControl.EnableStackedTabs(FALSE);
	CDialog::OnInitDialog();
	return TRUE;
}


void CUltimateDlg::OnChangeSectSize() {
	UpdateData(TRUE);  // bring from Dialog

	// update the member(s) as well
	m_sect_size = m_dflt_sect_size = g_sector_sizes[m_sect_size_option];

	// write it to the registry
	AfxGetApp()->WriteProfileInt(_T("Settings"), _T("DefaultSectSize"), m_sect_size_option);
}


void CUltimateDlg::OnForceMbr()
{
	if (IsDlgButtonChecked(IDC_FORCE_MBR))
		if (IsDlgButtonChecked(IDC_FORCE_NO_MBR))
			CheckDlgButton(IDC_FORCE_NO_MBR, BST_UNCHECKED);
}


void CUltimateDlg::OnForceNoMbr()
{
	if (IsDlgButtonChecked(IDC_FORCE_NO_MBR))
		if (IsDlgButtonChecked(IDC_FORCE_MBR))
			CheckDlgButton(IDC_FORCE_MBR, BST_UNCHECKED);
}


void CUltimateDlg::OnFileOpen()
{
	CFileDialog dlg(
		TRUE,             // Create an open file dialog
		_T(".img"),       // Default file extension
		NULL,             // Default Filename
		OFN_FILEMUSTEXIST | OFN_HIDEREADONLY | OFN_EXPLORER, // flags
		_T(".img files (.img)|*.img|")    // Filter string
		_T("All Files (*.*)|*.*|")        // Filter string
		_T("|")
	);
	if (dlg.DoModal() != IDOK)
		return;

	POSITION pos = dlg.GetStartPosition();
	FileOpen(dlg.GetNextPathName(pos));
}

LARGE_INTEGER CUltimateDlg::GetFileLength(HANDLE hFile) {
	LARGE_INTEGER large;

	large.QuadPart = 0;
	switch (m_file_type) {
	case DLG_FILE_TYPE_FLAT:
		::GetFileSizeEx(hFile, &large);
		break;
	default:
		AfxMessageBox(_T("Error: Unknown DLF_FILE_TYPE..."));
	}

	return large;
}

void CUltimateDlg::FileOpen(CString csPath) {
	BYTE buffer[MAX_SECT_SIZE];
	CString cs;

	// see if we already have a file open
	if (m_bIsOpen) {

		// do the save/close of existing

		m_file.Close();
		m_ImageBar.Clear();
		m_bIsOpen = FALSE;
	}

	m_sect_size = m_dflt_sect_size;
	m_isISOImage = FALSE;
	m_hasVHD = FALSE;
	m_MBRCount = 0;
	m_FatCount = 0;
	m_LeanCount = 0;
	m_NTFSCount = 0;
	m_SFSCount = 0;
	m_FYSCount = 0;
	m_Ext2Count = 0;
	m_ExFatCount = 0;
	m_UCount = 0;

	if (m_file.Open(csPath, CFile::modeReadWrite | CFile::typeBinary | CFile::shareDenyWrite, NULL) == 0) {
		return;
	}

	m_file_type = DLG_FILE_TYPE_FLAT;
	m_file_length = GetFileLength((HANDLE)m_file.m_hFile);
	m_sect_size = m_dflt_sect_size;

	// now don't allow the user to change the sector size and a few other things
	GetDlgItem(IDC_FORCE_MBR)->EnableWindow(FALSE);
	GetDlgItem(IDC_FORCE_NO_MBR)->EnableWindow(FALSE);
	GetDlgItem(IDC_FORCE_GPT)->EnableWindow(FALSE);
	GetDlgItem(IDC_FORCE_GPT_ENUM)->EnableWindow(FALSE);
	GetDlgItem(IDC_SECT_SIZE_512)->EnableWindow(FALSE);
	GetDlgItem(IDC_SECT_SIZE_1024)->EnableWindow(FALSE);
	GetDlgItem(IDC_SECT_SIZE_2048)->EnableWindow(FALSE);
	GetDlgItem(IDC_SECT_SIZE_4096)->EnableWindow(FALSE);

	m_image_bar.m_item_count = 0;
	m_image_bar.m_TabControl = &m_TabControl;
	m_ImageBar.ImageParse(&m_file);

	m_bIsOpen = TRUE;
	m_cur_file = csPath;
}

DWORD64 CUltimateDlg::GetFileSectCount(void) {
	return (DWORD64)(GetFileLength((HANDLE)m_file.m_hFile).QuadPart / m_sect_size);
}


long CUltimateDlg::ReadFromFile(void* buffer, DWORD64 lba, long count) {
	return 0;
}

void CUltimateDlg::WriteToFile(void* buffer, DWORD64 lba, long count) {
}

void CUltimateDlg::ReadBlocks(void* buffer, DWORD64 base, DWORD64 block, DWORD block_size, long count) {
}

void CUltimateDlg::WriteBlocks(void* buffer, DWORD64 base, DWORD64 block, DWORD block_size, long count) {
}

void CUltimateDlg::InsertSectors(const DWORD64 lba, const long count) {
}

void CUltimateDlg::RemoveSectors(const DWORD64 lba, const long count) {
}
