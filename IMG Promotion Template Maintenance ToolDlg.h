
// IMG Promotion Template Maintenance ToolDlg.h : header file
//

#pragma once
#include <vector>


#define ENZO_COLOR_NAVYBLUE		RGB(26, 35, 126)
#define ENZO_COLOR_DIRTYWHITE	RGB(220, 220, 220)
#define ENZO_COLOR_WHITE		RGB(255,255,255)
#define ENZO_COLOR_BLACK		RGB(0,0,0)
#define ENZO_COLOR_GRAY			RGB(128,128,128)
#define ENZO_COLOR_DARKGRAY		RGB(80,80,80)
#define ENZO_COLOR_YELLOW		RGB(255, 255, 0)

using namespace std;
// CIMGPromotionTemplateMaintenanceToolDlg dialog
class CIMGPromotionTemplateMaintenanceToolDlg : public CDialogEx
{
// Construction
public:
	CIMGPromotionTemplateMaintenanceToolDlg(CWnd* pParent = nullptr);	// standard constructor
	~CIMGPromotionTemplateMaintenanceToolDlg();
// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_IMGPROMOTIONTEMPLATEMAINTENANCETOOL_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	CStatic m_staticCtrlImage;

	vector<CBitmap*> m_vCBitmaps;
	HBRUSH m_hBrushPrevBackGround;
	HBRUSH m_hBrushDlgBackGround;
	RECT m_rectImage;
	BOOL DisplayPreview();
	void GetRectRatio(LPRECT lpRect);
private:
	BOOL InitializeDialogPlacement();
private:
	CEdit m_editCtrlCoord;
public:
	afx_msg void OnBnClickedButtonOpenfile();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
private:
	CEdit m_editCtrlMouseMove;
public:
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
};
