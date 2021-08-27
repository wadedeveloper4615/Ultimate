#pragma once

#include "MyStatic.h"
#include "ImageBar.h"
#include "Gpt.h"
#include "MBR.h"

// CUltimateDlg dialog

class CUltimateDlg : public CDialog
{
	DECLARE_DYNAMIC(CUltimateDlg)

public:
	CUltimateDlg(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CUltimateDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ULTIMATE_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
	unsigned int m_dflt_sect_size;

	CFont m_DumpFont;

	CMyStatic m_image_bar;
	CStatic m_StaticTabs;
	CPropertySheet m_TabControl;
	HICON m_hIcon;
	CImageBar m_ImageBar;
	bool    m_bIsOpen;
	CString m_cur_file;
	CFile   m_file;
	LARGE_INTEGER m_file_length;
	bool    m_overwrite_okay;

	BOOL  m_force_gpt_presence;
	BOOL  m_force_mbr_presence;
	BOOL  m_force_gpt_enum;
	BOOL  m_ignore_empty_gpt_entries;
	BOOL  m_force_readonly;
	unsigned m_sect_size;
	int   m_sect_size_option;
	BOOL	m_force_no_mbr_presence;

	CGpt  Gpt;


	CMbr  Mbr[MAX_SUB_VOLUMES];
	int  m_MBRCount;

	BOOL  m_hasVHD;
	BOOL  m_isISOImage;
	CString m_FatNames[MAX_SUB_VOLUMES];
	int  m_FatCount;
	CString m_LeanNames[MAX_SUB_VOLUMES];
	int  m_LeanCount;
	CString m_NTFSNames[MAX_SUB_VOLUMES];
	int  m_NTFSCount;
	CString m_SFSNames[MAX_SUB_VOLUMES];
	int  m_SFSCount;
	CString m_FYSNames[MAX_SUB_VOLUMES];
	int  m_FYSCount;
	CString m_Ext2Names[MAX_SUB_VOLUMES];
	int  m_Ext2Count;
	CString m_ExFatNames[MAX_SUB_VOLUMES];
	int  m_ExFatCount;
	CString m_FSZNames[MAX_SUB_VOLUMES];
	int  m_FSZCount;
	int  m_UCount;
	int   m_file_type;  // type of file we are accessing
public:
	void FileOpen(CString csPath);
	LARGE_INTEGER GetFileLength(HANDLE hFile);
	DWORD64 GetFileSectCount(void);
	long ReadFromFile(void* buffer, DWORD64 lba, long count);
	void WriteToFile(void* buffer, DWORD64 lba, long count);
	void ReadBlocks(void* buffer, DWORD64 base, DWORD64 block, DWORD block_size, long count);
	void WriteBlocks(void* buffer, DWORD64 base, DWORD64 block, DWORD block_size, long count);
	void InsertSectors(const DWORD64 lba, const long count);
	void RemoveSectors(const DWORD64 lba, const long count);

	virtual BOOL OnInitDialog();

	afx_msg void OnChangeSectSize();
	afx_msg void OnForceMbr();
	afx_msg void OnForceNoMbr();
	afx_msg void OnFileOpen();
};
