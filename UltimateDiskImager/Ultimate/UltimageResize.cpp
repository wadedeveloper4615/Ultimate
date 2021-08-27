#include "pch.h"
#include "UltimageResize.h"

CUltimageResize::CUltimageResize(CWnd* pParent /*=NULL*/)
	: CDialog(CUltimageResize::IDD, pParent) {
	//{{AFX_DATA_INIT(CUltimageResize)
	m_cur_size = _T("");
	m_new_size = _T("");
	m_title = _T("Resize Image");
	//}}AFX_DATA_INIT
}

void CUltimageResize::DoDataExchange(CDataExchange* pDX) {
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CUltimageResize)
	DDX_Text(pDX, IDC_CUR_SIZE, m_cur_size);
	DDX_Text(pDX, IDC_NEW_SIZE, m_new_size);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CUltimageResize, CDialog)
	//{{AFX_MSG_MAP(CUltimageResize)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CUltimageResize message handlers

BOOL CUltimageResize::OnInitDialog() {
	CDialog::OnInitDialog();

	SetWindowText(m_title);
	GetDlgItem(IDC_NEW_SIZE)->SetFocus();

	return FALSE;
}
