#include "stdafx.h"
#include "pch.h"

#include "ultimate.h"
#include "ultimateDlg.h"

#include "MyTreeCtrl.h"
#include "OurFind.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyTreeCtrl

IMPLEMENT_DYNCREATE(CMyTreeCtrl, CTreeCtrl)

CMyTreeCtrl::CMyTreeCtrl() : CTreeCtrl() {
  // allocate the Items list
  m_item_alloc = 1024;
  m_items = (S_ITEMS *) malloc(m_item_alloc * sizeof(S_ITEMS));
  m_item_count = 0;
  
  // search parameters
  m_hStart = NULL;
  m_csSearchStr.Empty();
  m_bCase = FALSE;
}

CMyTreeCtrl::~CMyTreeCtrl() {
  if (m_items)
    free(m_items);
  m_item_alloc = 0;
  m_item_count = 0;
}

BOOL CMyTreeCtrl::DeleteAllItems(void) {
  m_item_count = 0;
  return CTreeCtrl::DeleteAllItems();
}

#define MAX_ITEMS_ALLOWED       10240
#define MAX_ITEMS_ALLOWED_STR  "10240"

HTREEITEM CMyTreeCtrl::Insert(LPCTSTR lpszItem, DWORD Flags, int nImage, int nSelectedImage, HTREEITEM hParent) {
  HTREEITEM handle = NULL;
  int index = m_item_count;
  
  if (m_item_count >= m_item_alloc) {
    if ((m_item_alloc + 1024) >= MAX_ITEMS_ALLOWED) {  // don't let it get out of hand...
      AfxMessageBox("Trying to insert too many items.\r\n"
                    "To keep it under control and incase of invalid entries,\r\n"
                    "I limit the count of entries to " MAX_ITEMS_ALLOWED_STR ".");
      return NULL;
    }
    m_item_alloc += 1024;
    m_items = (S_ITEMS *) realloc(m_items, m_item_alloc * sizeof(S_ITEMS));
    if (m_items == NULL) {
      AfxMessageBox("Error with memory");
      return NULL;
    }
  }
  
  if (hParent == TVI_ROOT)
    m_items[m_item_count].IsDir = -1;
  else
    m_items[m_item_count].IsDir = ((Flags & ITEM_IS_FOLDER) > 0) ? 1 : 0;
  handle = InsertItem(TVIF_IMAGE | TVIF_PARAM | TVIF_SELECTEDIMAGE | TVIF_TEXT, 
                      lpszItem, 
                      nImage,
                      nSelectedImage,
                      0, 0, 
                      index,
                      hParent, TVI_LAST);  // TVI_SORT
  m_item_count++;
  
  return handle;
}

void *CMyTreeCtrl::GetDataStruct(HTREEITEM hItem) {
  if (hItem != NULL) {
    int index = (int) GetItemData(hItem);
    if (index > -1)
      return m_items[index].fs_item;
  }
  return NULL;
}

// IsDir returns > 0 if selected item is a directory
//              == 0 if selected item is not a dir
//               < 0 if selected item is the root directory
// csName returns text of selected item
HTREEITEM CMyTreeCtrl::GetFullPath(HTREEITEM hItem, int *IsDir, CString &csName, CString &csPath, BOOL Visible) {
  CString csTemp;
  TCHAR szText[1024];
  TVITEM item;
  HTREEITEM hName = NULL;
  int index;
  
  if (hItem == NULL)
    hItem = GetSelectedItem();
  if (hItem) {
    hName = hItem;
    if (IsDir) {
      index = (int) GetItemData(hItem);
      if (index < m_item_count)
        *IsDir = (m_items[index].IsDir != 0) ? 1 : 0;
    }
    if (Visible)
      EnsureVisible(hItem);
    csPath.Empty();
    do {
      item.hItem = hItem;
      item.mask = TVIF_TEXT | TVIF_HANDLE;
      item.pszText = szText;
      item.cchTextMax = 1024;
      GetItem(&item);
      if (csPath.IsEmpty()) {
        csPath = szText;
        csName = szText;
      } else if (!strcmp(szText, "\\"))
        csPath = szText + csPath;
      else {
        csTemp = csPath;
        csPath.Format("%s\\%s", szText, csTemp);
      }
      
      hItem = GetParentItem(hItem);
    } while (hItem);
    
    if (csName == "\\") {
      csName = "Root";
      if (IsDir) *IsDir = -1;
    }
    
//    CString cs;
//    cs.Format("%s %s %i", csPath, csName, *IsDir);
//    AfxMessageBox(cs);
    
  }
  
  return hName;
}

int CMyTreeCtrl::IsDir(HTREEITEM hItem) {
  int index = (int) GetItemData(hItem);
  if (index < m_item_count)
    return m_items[index].IsDir;
  return 0;
}

HTREEITEM CMyTreeCtrl::FindFirst(HTREEITEM hParent, LPCTSTR text) {
  if (ItemHasChildren(hParent)) {
    HTREEITEM hItem = GetChildItem(hParent);
    while (hItem != NULL) {
      if (GetItemText(hItem) == text)
        return hItem;      
      hItem = GetNextSiblingItem(hItem);
    }
  }
  return NULL;
}

// Search a tree for a specific (sub)string
// hStart = starting entry (could be Root)
//   (do not compare hStart item with search string. Use next item)
// csSearchStr = the string to search for (could have wild cards)
// bCase = TRUE = case sensitive compares
HTREEITEM CMyTreeCtrl::SearchTree(HTREEITEM hStart, CString csSearchStr, const BOOL bCase) {
  HTREEITEM hItem, ret;
  
  while (hStart != NULL) {
    if (hStart != GetSelectedItem()) {
      // check this item
      if (fnmatch(csSearchStr, GetItemText(hStart), (bCase) ? FNM_NOCASE : 0))
        return hStart;
    }
    // else, check if it has child items
    if (ItemHasChildren(hStart)) {
      hItem = GetChildItem(hStart);
      if (hItem != NULL) {
        ret = SearchTree(hItem, csSearchStr, bCase);
        if (ret != NULL)
          return ret;
      }
    }
    hStart = GetNextSiblingItem(hStart);
  }
  
  return NULL;
}

HTREEITEM CMyTreeCtrl::Search(void) {
  HTREEITEM hItem;
  COurFind findit;
  
  findit.m_match_case = m_bCase;
  findit.m_find_str = m_csSearchStr;
  if (findit.DoModal() != IDOK)
    return NULL;
  
  m_csSearchStr = findit.m_find_str;
  m_bCase = findit.m_match_case;
  if (m_csSearchStr.IsEmpty())
    return NULL;
  
  // get the starting point
  // if an item is selected, start with the next one
  // if no item selected, start with the root
  m_hStart = GetSelectedItem();
  if (m_hStart == NULL)
    m_hStart = GetChildItem(TVI_ROOT);
  
  hItem = SearchTree(m_hStart, m_csSearchStr, m_bCase);
  if (hItem != NULL)
    Select(hItem, TVGN_CARET);
  else
    AfxMessageBox("Did not find search pattern!");
  
  return hItem;
}
