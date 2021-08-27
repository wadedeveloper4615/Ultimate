// Modeless.cpp : implementation file
//

#include "pch.h"
#include "Ultimate.h"
#include "Modeless.h"
#include "afxdialogex.h"


// CModeless dialog

CModeless::CModeless(CWnd* pParent /*=NULL*/)
    : CDialog(CModeless::IDD, pParent) {
    //{{AFX_DATA_INIT(CModeless)
    m_edit = _T("");
    //}}AFX_DATA_INIT
    m_modeless = FALSE;
    m_Title = _T("");
}

void CModeless::DoDataExchange(CDataExchange* pDX) {
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CModeless)
    DDX_Text(pDX, IDC_EDIT, m_edit);
    //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CModeless, CDialog)
    //{{AFX_MSG_MAP(CModeless)
    ON_BN_CLICKED(IDC_DONE, OnDone)
    ON_BN_CLICKED(IDC_COPY, OnCopy)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CModeless message handlers
BOOL CModeless::OnInitDialog() {
    CDialog::OnInitDialog();

    SetWindowText(m_Title);

    // only allow the DONE and COPY buttons to be active if
    //  we are done and now not a modeless window
    GetDlgItem(IDC_DONE)->EnableWindow(!m_modeless);
    GetDlgItem(IDC_COPY)->EnableWindow(!m_modeless);

    // scroll down to the last line
    if (!m_modeless) {
        CEdit* pEdit = (CEdit*)GetDlgItem(IDC_EDIT);
        pEdit->LineScroll(pEdit->GetLineCount());
    }

    // setting the focus to the button and 
    //  returning FALSE doesn't select the text
    //  in the Edit Control
    GetDlgItem(IDC_DONE)->SetFocus();
    return FALSE;
}

void CModeless::OnDone() {
    if (m_modeless)
        EndModalLoop(IDOK);
    else
        EndDialog(IDOK);
}

// copy the current contents of the string to the Windows clipboard
void CModeless::OnCopy() {

    if (!OpenClipboard())
        return;

    if (!EmptyClipboard())
        return;

    size_t size = m_edit.GetLength();
    HGLOBAL hGlob = GlobalAlloc(GMEM_FIXED, size);
    memcpy(hGlob, m_edit, size);
    ::SetClipboardData(CF_TEXT, hGlob);

    CloseClipboard();
}

// CModeless message handlers
