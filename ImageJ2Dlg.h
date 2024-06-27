
// ImageJ2Dlg.h : ��� ����
//

#pragma once

#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "afxwin.h"

// CImageJ2Dlg ��ȭ ����
class CImageJ2Dlg : public CDialogEx
{
// �����Դϴ�.
public:
	CImageJ2Dlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_IMAGEJ2_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.


// �����Դϴ�.
protected:
	HICON m_hIcon;

	// ������ �޽��� �� �Լ�
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	void OpenPicture(cv::Mat ma);
	void MatToCImage(const cv::Mat& mat, CImage& cimage);
	afx_msg void OnFileOpen32771();
	CStatic m_PicCtrl;
	afx_msg void OnConvertcolorGrayscale();
	afx_msg void OnEditBlur();
	afx_msg void OnEditRotate();
	afx_msg void OnFileSave32772();
	afx_msg void OnFileSaveas();
	afx_msg void OnFlipLrfilp();
	afx_msg void OnFlipUd();
	afx_msg void OnEditReverse();
	afx_msg void OnDrawLine();
	CString m_DrawMode;
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	int nSx;
	int nSy;
};
