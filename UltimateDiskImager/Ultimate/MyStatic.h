#pragma once


// CMyStatic

#define IMAGE_BAR_MAX  64
typedef struct _S_IMAGE_BAR {
	CPropertyPage* page;
	int  left;
	int  right;
	DWORD color;
	BOOL filled;
	TCHAR title[32];
}S_IMAGE_BAR;

class CMyStatic : public CStatic {
	DECLARE_DYNCREATE(CMyStatic)

	// Construction
public:
	CMyStatic();
	~CMyStatic();

	int AddItem(int left, int right, DWORD color, BOOL filled, TCHAR * title, CPropertyPage* page);
	void UpdateTitle(int index, TCHAR* title);
	void Clear();

	S_IMAGE_BAR m_items[IMAGE_BAR_MAX];
	int m_item_count;
	CPropertySheet* m_TabControl;

	// Overrides
	  // ClassWizard generate virtual function overrides
	  //{{AFX_VIRTUAL(CMyStatic)
protected:
	//}}AFX_VIRTUAL

  // Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMyStatic)
	afx_msg void OnPaint();
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
