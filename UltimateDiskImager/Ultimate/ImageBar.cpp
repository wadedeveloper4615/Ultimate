// ImageBar.cpp : implementation file
//

#include "pch.h"
#include "Ultimate.h"
#include "ImageBar.h"
#include "UltimateDlg.h"

// CImageBar

IMPLEMENT_DYNAMIC(CImageBar, CWnd)

CImageBar::CImageBar()
{

}

CImageBar::~CImageBar()
{
}


BEGIN_MESSAGE_MAP(CImageBar, CWnd)
END_MESSAGE_MAP()



// CImageBar message handlers




void CImageBar::Clear()
{
    // TODO: Add your implementation code here.
}

int CImageBar::DrawBox(DWORD64 start, DWORD64 end, DWORD64 total, DWORD color, BOOL filled, TCHAR * title, CPropertyPage* page) {
    int ret;

    // fix a few things?
    if (end > total) end = total;

    // get a pointer to the main dialog
    CUltimateDlg* dlg = (CUltimateDlg*)AfxGetApp()->m_pMainWnd;

    RECT ItemRect;
    dlg->m_image_bar.GetWindowRect(&ItemRect);

    int WidthOfBox = ItemRect.right - ItemRect.left - 2;
    const double s = (double)(((double)start * 100.0) / (double)total) / 100.0;  // s = percent
    const double e = (double)(((double)end * 100.0) / (double)total) / 100.0;    // e = percent
    ItemRect.left = (long)((double)WidthOfBox * s);
    ItemRect.right = (long)((double)WidthOfBox * e);

    if (ItemRect.right <= ItemRect.left)
        ItemRect.right = ItemRect.left + 1;
    if ((ItemRect.left == 0) && (start > 0))
        ItemRect.left = 1;

    ret = dlg->m_image_bar.AddItem(ItemRect.left, ItemRect.right, color, filled, title, page);
    dlg->m_image_bar.Invalidate(FALSE);

    return ret;
}

void CImageBar::CheckForMBRRecusive(DWORD64 LBA, DWORD64 TotalBlocks) {
    CUltimateDlg* dlg = (CUltimateDlg*)AfxGetApp()->m_pMainWnd;
    int i, j;

    // check to make sure we don't loop indefinately via "ill-connected" extended partitions
    for (i = 0; i < dlg->m_MBRCount; i++) {
        if (dlg->Mbr[i].m_lba == LBA) {
            AfxMessageBox(_T("Extended MBR pointing to already found (ext) MBR..."));
            return;
        }
    }

    // "insert" a new (extended) MBR entry?
    if (dlg->m_MBRCount < MAX_SUB_VOLUMES) {
        if (dlg->Mbr[dlg->m_MBRCount].Exists(LBA)) {
            dlg->Mbr[dlg->m_MBRCount].m_draw_index = DrawBox(LBA, 1, TotalBlocks, dlg->Mbr[dlg->m_MBRCount].m_color, TRUE, _T("MBR"), &dlg->Mbr[dlg->m_MBRCount]);
            dlg->Mbr[dlg->m_MBRCount].m_index = dlg->m_MBRCount;
            dlg->Mbr[dlg->m_MBRCount].m_parent_lba = LBA;

            // set the title of the Tab
            if (dlg->m_MBRCount == 0)
                dlg->Mbr[dlg->m_MBRCount].m_Title = "MBR";
            else
                dlg->Mbr[dlg->m_MBRCount].m_Title = "ext MBR";
            dlg->Mbr[dlg->m_MBRCount].m_psp.dwFlags |= PSP_USETITLE;
            dlg->Mbr[dlg->m_MBRCount].m_psp.pszTitle = dlg->Mbr[dlg->m_MBRCount].m_Title;

            // add the page
            dlg->m_TabControl.AddPage(&dlg->Mbr[dlg->m_MBRCount]);

            // check to see if any of there are extended partitions
            j = dlg->m_MBRCount++;
            for (i = 0; i < 4; i++) {
                DWORD64 lba = convert32(dlg->Mbr[j].m_Pages[i].m_start_lba);
                BYTE type = convert8(dlg->Mbr[j].m_Pages[i].m_sys_id);
                if ((type == 0x05) || (type == 0x0F))
                    CheckForMBRRecusive(LBA + lba, TotalBlocks);
            }
        }
    }
    else
        AfxMessageBox(_T("Too many MBRs"));
}

void CImageBar::ImageParse(CFile* file) {
    CUltimateDlg* dlg = (CUltimateDlg*)AfxGetApp()->m_pMainWnd;
    CPropertyPage* page = NULL;
    CString cs;
    int i, j;

    dlg->UpdateData(TRUE); // bring from Dialog

    LARGE_INTEGER file_length = dlg->GetFileLength((HANDLE)file->m_hFile);
    DWORD64 TotalBlocks = (file_length.QuadPart + (dlg->m_sect_size - 1)) / dlg->m_sect_size;

    dlg->SetDlgItemText(IDC_START_DISP, _T("0"));
    cs.Format(_T("%lld"), TotalBlocks - 1);
    dlg->SetDlgItemText(IDC_END_DISP, cs);
    cs.Format(_T("%lld"), TotalBlocks / 2);
    dlg->SetDlgItemText(IDC_MID_DISP, cs);

    CheckForMBRRecusive(0, TotalBlocks);

    // if there was not a valid MBR, there won't be a valid GPT  
    if (dlg->Mbr[0].m_exists) {
        if (dlg->Gpt.Exists(1ULL)) {
            dlg->Gpt.m_draw_index = DrawBox(1, 2, TotalBlocks, dlg->Gpt.m_color, TRUE, _T("GPT"), &dlg->Gpt);
            dlg->m_TabControl.AddPage(&dlg->Gpt);
        }
    }

    // encompass the GPT sectors
    if (dlg->Gpt.m_exists) {
        DrawBox(1, dlg->Gpt.m_hdr.last_usable, TotalBlocks, dlg->Gpt.m_color, FALSE, _T("GPT"), &dlg->Gpt);
        DrawBox(1, dlg->Gpt.m_hdr.first_usable - 1, TotalBlocks, dlg->Gpt.m_color, TRUE, _T("GPT"), &dlg->Gpt);
        if (dlg->Gpt.m_hdr.backup_lba && (dlg->Gpt.m_hdr.backup_lba > 63))
            DrawBox(dlg->Gpt.m_hdr.backup_lba - 63, dlg->Gpt.m_hdr.backup_lba, TotalBlocks, dlg->Gpt.m_color, TRUE, _T("GPT Backup"), &dlg->Gpt);
    }

    // if no MBR, then add an "Empty" one
    // (for some reason, the system needs one before the Create() or
    //  it crashes on the first time we add a page)
    if (dlg->m_MBRCount == 0)
        dlg->m_TabControl.AddPage(&dlg->Mbr[0]);

    // if the MBR is a PMBR, change the tab's title
    CPropertyPage* p = dlg->m_TabControl.GetPage(dlg->m_TabControl.GetPageIndex(&dlg->Mbr[0]));
    if (dlg->Gpt.m_exists && dlg->Mbr[0].IsPMBR())
        p->m_psp.pszTitle = _T("PMBR");
    else
        p->m_psp.pszTitle = _T("MBR");
/*
    // If we have an ISO image as well, parse it
    if (dlg->m_isISOImage) {
        if (dlg->ISO.Start()) {
            if (dlg->ISO.m_BVD.m_is_valid)
                dlg->ISO.m_BVD.m_draw_index = DrawBox(dlg->ISO.m_BVD.m_lba, dlg->ISO.m_BVD.m_lba + dlg->ISO.m_BVD.m_size - 1, TotalBlocks, dlg->ISO.m_BVD.m_color, TRUE, "ISO", &dlg->ISO.m_BVD);
            if (dlg->ISO.m_PVD.m_is_valid)
                dlg->ISO.m_PVD.m_draw_index = DrawBox(dlg->ISO.m_PVD.m_lba, dlg->ISO.m_PVD.m_lba + dlg->ISO.m_PVD.m_size - 1, TotalBlocks, dlg->ISO.m_PVD.m_color, TRUE, "ISO", &dlg->ISO.m_PVD);
            //if (dlg->ISO.m_SVD.m_is_valid)
            //  dlg->ISO.m_SVD.m_draw_index = DrawBox(dlg->ISO.m_SVD.m_lba, dlg->ISO.m_SVD.m_lba + dlg->ISO.m_SVD.m_size - 1, TotalBlocks, dlg->ISO.m_SVD.m_color, TRUE, "ISO", &dlg->ISO.m_SVD);
            if (dlg->ISO.m_BEA.m_is_valid)
                dlg->ISO.m_BEA.m_draw_index = DrawBox(dlg->ISO.m_BEA.m_lba, dlg->ISO.m_BEA.m_lba + dlg->ISO.m_BEA.m_size - 1, TotalBlocks, dlg->ISO.m_BEA.m_color, TRUE, "ISO", &dlg->ISO.m_BEA);
            if (dlg->ISO.m_NSR.m_is_valid)
                dlg->ISO.m_NSR.m_draw_index = DrawBox(dlg->ISO.m_NSR.m_lba, dlg->ISO.m_NSR.m_lba + dlg->ISO.m_NSR.m_size - 1, TotalBlocks, dlg->ISO.m_NSR.m_color, TRUE, "ISO", &dlg->ISO.m_NSR);
        }
    }

    // move the Tabs to the correct position
    dlg->m_TabControl.Create(dlg, WS_VISIBLE | WS_CHILD | WS_DLGFRAME);
    dlg->m_TabControl.ModifyStyleEx(0, WS_EX_CONTROLPARENT);
    CRect rect;
    dlg->m_StaticTabs.GetWindowRect(&rect);
    dlg->ScreenToClient(&rect);
    dlg->m_TabControl.MoveWindow(&rect);

    // update the items
    for (i = 0; i < dlg->m_MBRCount; i++) {
        if (dlg->Mbr[i].m_exists) {
            dlg->m_TabControl.SetActivePage(&dlg->Mbr[i]);
            dlg->Mbr[i].Begin();
            if (!dlg->Gpt.m_exists || !dlg->IsDlgButtonChecked(IDC_FORCE_GPT_ENUM)) {
                page = &dlg->Mbr[i];
                for (j = 0; j < 4; j++) {
                    DWORD64 lba = dlg->Mbr[i].m_parent_lba + convert32(dlg->Mbr[i].m_Pages[j].m_start_lba);
                    DWORD64 size = convert32(dlg->Mbr[i].m_Pages[j].m_size);
                    BYTE type = convert8(dlg->Mbr[i].m_Pages[j].m_sys_id);
                    if ((type > 0) && (size > 0)) {
                        if ((type == 0x05) || (type == 0x0F))
                            ;
                        // detect if we have an Embr.  If not, try to parse the entry anyway
                        else if ((type != 0xE0) || !dlg->Embr.Exists(0ULL)) {
                            ImageParseVolume(type, lba, size, TotalBlocks);
                        }
                    }
                }
            }
        }
    }

    if (dlg->Gpt.m_exists) {
        dlg->Mbr[0].CheckDlgButton(IDC_MBR_LEGACY_GPT, BST_CHECKED);  // is GPT, so set the Legacy Button on the MBR dialog
        dlg->m_TabControl.SetActivePage(&dlg->Gpt);
        dlg->Gpt.Begin();
        if (dlg->IsDlgButtonChecked(IDC_FORCE_GPT_ENUM)) {
            page = &dlg->Gpt;
            for (i = 0; i < dlg->Gpt.m_gpt_entries; i++) {
                DWORD64 lba = convert64(dlg->Gpt.m_Pages[i].m_start_lba);
                DWORD64 size = (convert64(dlg->Gpt.m_Pages[i].m_last_lba) - lba) + 1;
                BYTE type = 0xFF;
                ImageParseVolume(type, lba, size, TotalBlocks);
            }
        }
    }
    else
        dlg->Mbr[0].GetDlgItem(IDC_MBR_LEGACY_GPT)->EnableWindow(FALSE);

    if (dlg->Embr.m_exists) {
        DrawBox(1, dlg->Embr.m_total_sectors - 1, TotalBlocks, dlg->Embr.m_color, FALSE, "eMBR", &dlg->Embr);
        DrawBox(1, 1 + convert16(dlg->Embr.m_remaining) + 1, TotalBlocks, dlg->Embr.m_color, TRUE, "eMBR", &dlg->Embr);
        dlg->m_TabControl.AddPage(&dlg->Embr);
        dlg->m_TabControl.SetActivePage(&dlg->Embr);
        dlg->Embr.Begin();
        page = &dlg->Embr;

        for (i = 0; i < dlg->Embr.m_embr_entries; i++) {
            DWORD lba = convert32(dlg->Embr.m_Pages[i].m_start_lba);
            DWORD size = convert32(dlg->Embr.m_Pages[i].m_sectors);
            BYTE type = 0xFF;
            ImageParseVolume(type, lba, size, TotalBlocks);
        }
    }

    // if there was no MBR, it could be a floppy
    //  or a volume starting at LBA 0
    if (!dlg->m_isISOImage) {
        if (!dlg->Mbr[0].m_exists) {
            ImageParseVolume(0x01, 0, TotalBlocks, TotalBlocks);
            dlg->m_TabControl.SetActivePage(0);
        }
        else
            dlg->m_TabControl.SetActivePage(page);
    }

    // if we found an ISO image as well, parse it too
    if (dlg->m_isISOImage) {
        // do the SVD first
        if (dlg->ISO.m_SVD.m_is_valid) {
            // We have to set the active page so that the framework builds the dialog
            dlg->m_TabControl.SetActivePage(&dlg->ISO.m_SVD);
            dlg->ISO.m_SVD.DoRoot();
        }
        // then the PVD second
        if (dlg->ISO.m_PVD.m_is_valid) {
            // We have to set the active page so that the framework builds the dialog
            dlg->m_TabControl.SetActivePage(&dlg->ISO.m_PVD);
            dlg->ISO.m_PVD.DoRoot();
        }
    }

    // if this is an .VHD file, load that as well.
    // (don't try if we already detected a VDI file)
    if (dlg->m_file_type != DLG_FILE_TYPE_VB_VDI) {
        if (dlg->VHD.Exists(TotalBlocks - 1)) {
            dlg->VHD.m_draw_index = DrawBox(dlg->VHD.m_lba, dlg->VHD.m_lba + 1, TotalBlocks, dlg->VHD.m_color, TRUE, "VHD", &dlg->VHD);
            dlg->m_TabControl.AddPage(&dlg->VHD);
            dlg->VHD.Begin();
            dlg->m_hasVHD = TRUE;
        }
    }
*/
    dlg->m_TabControl.Invalidate(FALSE);
}
