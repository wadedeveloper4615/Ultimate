// MyStatic.cpp : implementation file
//

#include "pch.h"
#include "Ultimate.h"
#include "MyStatic.h"


// CMyStatic

IMPLEMENT_DYNCREATE(CMyStatic, CStatic)

CMyStatic::CMyStatic() : CStatic() {
    m_item_count = 0;
    m_TabControl = NULL;
}

CMyStatic::~CMyStatic() {
}

BEGIN_MESSAGE_MAP(CMyStatic, CStatic)
    //{{AFX_MSG_MAP(CMyStatic)
    ON_WM_PAINT()
    ON_WM_LBUTTONUP()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

int CMyStatic::AddItem(int left, int right, DWORD color, BOOL filled, TCHAR* title, CPropertyPage* page) {
    int ret = -1;

    if (m_item_count < IMAGE_BAR_MAX) {
        m_items[m_item_count].page = page;
        m_items[m_item_count].left = left;
        m_items[m_item_count].right = right;
        m_items[m_item_count].color = color;
        m_items[m_item_count].filled = filled;
        _tcscpy_s(m_items[m_item_count].title, 32, title);
        ret = m_item_count++;
    }

    return ret;
}

void CMyStatic::UpdateTitle(int index, TCHAR* title) {
    if ((index > -1) && (index < IMAGE_BAR_MAX))
        _tcscpy_s(m_items[index].title, 32, title);
    Invalidate(TRUE);
}

void CMyStatic::Clear() {
    m_item_count = 0;
    Invalidate(TRUE);
}

void CMyStatic::OnPaint() {
    int i;
    CPaintDC dc(this); // device context for painting

    CRect rect;
    GetClientRect(&rect);

    CBrush Brush;

    // back color first
    Brush.CreateSolidBrush(COLOR_MBR_EMPTY);
    dc.FillRect(&rect, &Brush);

    // So that a regular rectangle (non-filled) will
    // "encompass" other filled rectangles, we need to
    // draw them last.
    for (i = 0; i < m_item_count; i++) {
        if (m_items[i].filled) {
            Brush.CreateSolidBrush(m_items[i].color);
            rect.left = m_items[i].left;
            rect.right = m_items[i].right;
            dc.FillRect(&rect, &Brush);

            // draw a title
            dc.SetTextColor(RGB(255, 255, 255));
            dc.SetBkColor(m_items[i].color);
            dc.DrawText(m_items[i].title, -1, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
        }
    }

    // now the (non-filled) rectangles
    // no text involved
    for (i = 0; i < m_item_count; i++) {
        if (!m_items[i].filled) {
            Brush.CreateSolidBrush(m_items[i].color);
            rect.left = m_items[i].left;
            rect.right = m_items[i].right;
            dc.FrameRect(&rect, &Brush);
        }
    }
}

void CMyStatic::OnLButtonUp(UINT nFlags, CPoint point) {
    int i;

    for (i = 0; i < m_item_count; i++) {
        if ((point.x >= m_items[i].left) && (point.x <= m_items[i].right)) {
            if (m_TabControl && m_items[i].page) {
                m_TabControl->SetActivePage(m_items[i].page);
                //break; // ??? If we break, it doesn't work right ?????
            }
        }
    }

    CStatic::OnLButtonUp(nFlags, point);
}
