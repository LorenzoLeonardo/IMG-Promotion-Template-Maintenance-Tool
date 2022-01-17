
// IMG Promotion Template Maintenance ToolDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "IMG Promotion Template Maintenance Tool.h"
#include "IMG Promotion Template Maintenance ToolDlg.h"
#include "afxdialogex.h"
#include "CFileDirectory.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CIMGPromotionTemplateMaintenanceToolDlg dialog



CIMGPromotionTemplateMaintenanceToolDlg::CIMGPromotionTemplateMaintenanceToolDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_IMGPROMOTIONTEMPLATEMAINTENANCETOOL_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_hBrushPrevBackGround = CreateSolidBrush(ENZO_COLOR_DARKGRAY);
	m_hBrushDlgBackGround = CreateSolidBrush(ENZO_COLOR_NAVYBLUE);
}
CIMGPromotionTemplateMaintenanceToolDlg::~CIMGPromotionTemplateMaintenanceToolDlg()
{
	DeleteObject(m_hBrushPrevBackGround);
}
void CIMGPromotionTemplateMaintenanceToolDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_IMAGE, m_staticCtrlImage);
	DDX_Control(pDX, IDC_EDIT_COORDS, m_editCtrlCoord);
	DDX_Control(pDX, IDC_EDIT_COORDS_MOUSE, m_editCtrlMouseMove);
}

BEGIN_MESSAGE_MAP(CIMGPromotionTemplateMaintenanceToolDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_OPENFILE, &CIMGPromotionTemplateMaintenanceToolDlg::OnBnClickedButtonOpenfile)
	ON_WM_CTLCOLOR()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()


// CIMGPromotionTemplateMaintenanceToolDlg message handlers

BOOL CIMGPromotionTemplateMaintenanceToolDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	InitializeDialogPlacement();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CIMGPromotionTemplateMaintenanceToolDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CIMGPromotionTemplateMaintenanceToolDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		DisplayPreview();
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CIMGPromotionTemplateMaintenanceToolDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



BOOL CIMGPromotionTemplateMaintenanceToolDlg::InitializeDialogPlacement()
{
	// TODO: Add your implementation code here.
	RECT rect;

	GetDesktopWindow()->GetWindowRect(&rect);
	SetWindowPos(this, rect.left, rect.top, rect.right, rect.bottom, SWP_NOOWNERZORDER | SWP_NOZORDER);
	
	m_rectImage.left = rect.right / 2;
	m_rectImage.top = rect.top + 10;
	m_rectImage.right = (rect.right - (rect.right / 2)) - 30;
	m_rectImage.bottom = rect.bottom - 60;
	m_staticCtrlImage.SetWindowPos(this, m_rectImage.left, m_rectImage.top, m_rectImage.right, m_rectImage.bottom, SWP_NOOWNERZORDER | SWP_NOZORDER);

	return 0;
}

void CIMGPromotionTemplateMaintenanceToolDlg::OnBnClickedButtonOpenfile()
{
// TODO: Add your control notification handler code here
	CFileDirectory cFile;

	CString csFile = cFile.OpenFile();
	m_editCtrlCoord.SetWindowText(csFile);

	for (int i = 0; i < (int)m_vCBitmaps.size(); i++)
	{
		m_vCBitmaps[i]->DeleteObject();
		delete m_vCBitmaps[i];
	}
	m_vCBitmaps.clear();

	HBITMAP hBmp = (HBITMAP)::LoadImage((HINSTANCE)NULL, csFile,
		IMAGE_BITMAP, 0, 0,
		LR_LOADTRANSPARENT | LR_CREATEDIBSECTION| LR_LOADFROMFILE| LR_DEFAULTSIZE);//LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE | LR_VGACOLOR | LR_LOADTRANSPARENT | LR_LOADMAP3DCOLORS);
	if (hBmp == NULL)
	{
		CString csErr;
		csErr.Format(_T("%d"), GetLastError());

		MessageBox(csErr);
		return;
	}
	CBitmap* bmp = new CBitmap();
	bmp->Attach(hBmp);
	m_vCBitmaps.push_back(bmp);

	DisplayPreview();
}

BOOL CIMGPromotionTemplateMaintenanceToolDlg::DisplayPreview()
{
	if (m_vCBitmaps.empty())
		return FALSE;

	CClientDC dc(&m_staticCtrlImage);
	CDC bmDC;
	CString csPage;
	RECT rect;
	CBitmap* pOldbmp = NULL;
	BITMAP  bi;

	bmDC.CreateCompatibleDC(&dc);
	m_staticCtrlImage.GetClientRect(&rect);
	
	pOldbmp = bmDC.SelectObject(m_vCBitmaps[0]);

	m_vCBitmaps[0]->GetBitmap(&bi);
	dc.SetStretchBltMode(HALFTONE);
	GetRectRatio(&rect);
	dc.StretchBlt(rect.left, rect.top, rect.right, rect.bottom, &bmDC, 0, 0, bi.bmWidth, bi.bmHeight, SRCCOPY);
	bmDC.SelectObject(pOldbmp);

	bmDC.DeleteDC();

	return TRUE;
}


void CIMGPromotionTemplateMaintenanceToolDlg::GetRectRatio(LPRECT lpRect)
{
	RECT rectContainer;
	BITMAP  bi;
	ZeroMemory(lpRect, sizeof(RECT));

	if (m_vCBitmaps.empty())
		return;

	m_staticCtrlImage.GetClientRect(&rectContainer);

	m_vCBitmaps[0]->GetBitmap(&bi);

	int imageWidth = bi.bmWidth;
	int imageHeight = bi.bmHeight;

	float fimageWidth = (float)imageWidth;
	float fimageHeight = (float)imageHeight;

	// Compute the coordinates of the upper left corner of the centered bitmap.
	float fContainerWidth = (float)rectContainer.right;
	float fContainerHeight = (float)rectContainer.bottom;
	float fbitmapAspectRatio = fimageWidth / fimageHeight;

	if (fimageWidth < fimageHeight)
	{
		fbitmapAspectRatio = fimageWidth / fimageHeight;
		fimageHeight = fContainerHeight;
		fimageWidth = fimageHeight * fbitmapAspectRatio;
	}
	else
	{
		fbitmapAspectRatio = fimageHeight/fimageWidth;
		fimageWidth = fContainerWidth;
		fimageHeight = fimageWidth * fbitmapAspectRatio;
	}
	int newX = (int)((fimageWidth));
	int newY = (int)((fimageHeight));

	int nPosX = ((int)((fContainerWidth - fimageWidth))) / 2;
	int nPosY = ((int)((fContainerHeight - fimageHeight))) / 2;

	float xMargin = 20;
	float yMargin =((float)xMargin * fbitmapAspectRatio);
	lpRect->left = (float)nPosX + xMargin;
	lpRect->top = (float)nPosY  + yMargin;

	lpRect->right = newX - (xMargin * 2);
	lpRect->bottom = newY - (yMargin * 2);
}

HBRUSH CIMGPromotionTemplateMaintenanceToolDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  Change any attributes of the DC here
	switch (nCtlColor)
	{
		case CTLCOLOR_STATIC:
		{
			if ((pWnd->GetDlgCtrlID() == IDC_STATIC_IMAGE))
			{
				pDC->SetBkColor(RGB(128, 128, 128));
				return m_hBrushPrevBackGround;
			}
		}
		case CTLCOLOR_DLG:
		{
			pDC->SetTextColor(ENZO_COLOR_WHITE);
			pDC->SetBkColor(ENZO_COLOR_NAVYBLUE);
			return m_hBrushDlgBackGround;
		}
	// TODO:  Return a different brush if the default is not desired
	}
	DisplayPreview();
	return hbr;
}


void CIMGPromotionTemplateMaintenanceToolDlg::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	CString csData;
	INT nXPos = point.x - m_rectImage.left;
	INT nYPos = point.y - m_rectImage.top;

	if ((0 <= nXPos) && (nXPos <= m_rectImage.right) &&
		(0 <= nYPos) && (nYPos <= m_rectImage.bottom))
	{
		csData.Format(_T("(%d,%d)"), nXPos, nYPos);
		m_editCtrlMouseMove.SetWindowText(csData);

		RECT rect;
		GetRectRatio(&rect);
		nXPos = nXPos - rect.left;
		nYPos = nYPos - rect.top;
		if ((0 <= nXPos) && (nXPos <= rect.right) &&
			(0 <= nYPos) && (nYPos <= rect.bottom))
		{
			BITMAP  bi;

			m_vCBitmaps[0]->GetBitmap(&bi);

			int imageWidth = bi.bmWidth;
			int imageHeight = bi.bmHeight;

			float nXTranslate = ((float)imageWidth / (float)rect.right);
			float nYTranslate = ((float)imageHeight / (float)rect.bottom);

			csData.Format(_T("(%d,%d)  (%d,%d)"), nXPos, nYPos, (int)((float)nXPos* nXTranslate), (int)((float)nYPos* nYTranslate));
			m_editCtrlCoord.SetWindowText(csData);
		}
	}

	CDialogEx::OnLButtonDblClk(nFlags, point);
}


void CIMGPromotionTemplateMaintenanceToolDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
/*	CString csData;
	INT nXPos = point.x - m_rectImage.left;
	INT nYPos = point.y - m_rectImage.top;

	if ((0 <= nXPos) && (nXPos <= m_rectImage.right) &&
		(0 <= nYPos) && (nYPos <= m_rectImage.bottom))
	{
		csData.Format(_T("(%d,%d)"), nXPos, nYPos);
		m_editCtrlMouseMove.SetWindowText(csData);

		RECT rect;
		GetRectRatio(&rect);
		nXPos = nXPos - rect.left;
		nYPos = nYPos - rect.top;
		if ((0 <= nXPos) && (nXPos <= rect.right) &&
			(0 <= nYPos) && (nYPos <= rect.bottom))
		{
			BITMAP  bi;

			m_vCBitmaps[0]->GetBitmap(&bi);

			int imageWidth = bi.bmWidth;
			int imageHeight = bi.bmHeight;

			float nXTranslate = ((float)imageWidth / (float)rect.right);
			float nYTranslate = ((float)imageHeight / (float)rect.bottom);

			csData.Format(_T("(%d,%d)  (%d,%d)"), nXPos, nYPos, (int)((float)nXPos * nXTranslate), (int)((float)nYPos * nYTranslate));
			m_editCtrlCoord.SetWindowText(csData);
		}
	}
	*/
	CDialogEx::OnMouseMove(nFlags, point);
}
