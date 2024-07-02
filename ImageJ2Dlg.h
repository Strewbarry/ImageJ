
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
	int GetEncoderClsid(const WCHAR * format, CLSID * pClsid);
	afx_msg void OnFileSaveas();
	afx_msg void OnFlipLrfilp();
	afx_msg void OnFlipUd();
	afx_msg void OnEditReverse();
	CString m_DrawMode;
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	int nSx;
	int nSy;
	bool nClickFlag;
	afx_msg void OnLineDrag();
	afx_msg void OnLineClicktwice();
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	void ZoomImage(double scale);
	afx_msg void OnMButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMButtonUp(UINT nFlags, CPoint point);
	void OpenHisto(cv::Mat ma);
	int nPicX;
	int nPicY;
	afx_msg void OnHistogramShowhis();
	int his_arr_r[256];
	int his_arr_g[256];
	int his_arr_b[256];
	afx_msg void OnBnClickedButtStrech();
	CStatic m_HistoCtrl;
	CString m_Shold;
	afx_msg void OnBnClickedButtShold();
};
