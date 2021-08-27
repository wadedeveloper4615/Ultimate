#pragma once


// CImageBar

class CImageBar : public CWnd
{
	DECLARE_DYNAMIC(CImageBar)

public:
	CImageBar();
	virtual ~CImageBar();

protected:
	DECLARE_MESSAGE_MAP()
public:
	void Clear();
	void ImageParse(CFile* file);
	void CheckForMBRRecusive(DWORD64 LBA, DWORD64 TotalBlocks);
	int  DrawBox(DWORD64 start, DWORD64 end, DWORD64 total, DWORD color, BOOL filled, TCHAR * title, CPropertyPage* page);
};


