#include "pch.h"
#include "Attribute.h"

CAttribute::CAttribute(CWnd* pParent /*=NULL*/) : CDialog(CAttribute::IDD, pParent) {
    m_title = "Please Choose:";
    m_single = FALSE;
    m_attrib = 0;
}

void CAttribute::DoDataExchange(CDataExchange* pDX) {
    CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_LIST, m_list);
}

BEGIN_MESSAGE_MAP(CAttribute, CDialog)
    ON_LBN_SELCHANGE(IDC_LIST, OnSelchangeList)
END_MESSAGE_MAP()

BOOL CAttribute::OnInitDialog() {
    CDialog::OnInitDialog();
    int i = 0;

    SetWindowText(m_title);
    m_list.ResetContent();
    while (m_attributes[i].index > -1) {
        m_list.AddString((LPCTSTR)m_attributes[i].str);
        if ((m_attrib & m_attributes[i].mask) == m_attributes[i].attrb)
            m_list.SetSel(i, TRUE);
        i++;
    }

    return TRUE;
}

void CAttribute::OnOK() {
    int i = 0;

    m_attrib = 0;
    while (m_attributes[i].index > -1) {
        if (m_list.GetSel(i))
            m_attrib |= m_attributes[i].attrb;
        i++;
    }

    CDialog::OnOK();
}

void CAttribute::OnSelchangeList() {
    int i, j = 0;

    i = m_list.GetCaretIndex();
    if (m_list.GetSel(i)) {
        if (m_single) {
            for (j = 0; j < m_list.GetCount(); j++)
                if (j != i)
                    m_list.SetSel(j, FALSE);
        }
        else {
            while (m_attributes[i].groups[j] > -1) {
                m_list.SetSel(m_attributes[i].groups[j], FALSE);
                j++;
            }
        }
    }
}
