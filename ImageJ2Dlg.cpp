
// ImageJ2Dlg.cpp : ���� ����
//

#include "stdafx.h"
#include "ImageJ2.h"
#include "ImageJ2Dlg.h"
#include "afxdialogex.h"
#include "resource.h"

using namespace std;
using namespace cv;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CString pathName;
string cvstr;
Mat Inputimage;
CImage cimage;
Mat rImage;
Mat nowImage;
double m_scale;

// ���� ���α׷� ������ ���Ǵ� CAboutDlg ��ȭ �����Դϴ�.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

// �����Դϴ�.
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


// CImageJ2Dlg ��ȭ ����



CImageJ2Dlg::CImageJ2Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_IMAGEJ2_DIALOG, pParent)
	, m_DrawMode(_T(""))
	, nSx(0)
	, nSy(0)
	, nClickFlag(false)
	, nPicX(0)
	, nPicY(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CImageJ2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PICTURE, m_PicCtrl);
	DDX_Control(pDX, IDC_HISTO, m_HistoCtrl);
}

BEGIN_MESSAGE_MAP(CImageJ2Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_COMMAND(ID_FILE_OPEN32771, &CImageJ2Dlg::OnFileOpen32771)
	ON_COMMAND(ID_CONVERTCOLOR_GRAYSCALE, &CImageJ2Dlg::OnConvertcolorGrayscale)
	ON_COMMAND(ID_EDIT_BLUR, &CImageJ2Dlg::OnEditBlur)
	ON_COMMAND(ID_EDIT_ROTATE, &CImageJ2Dlg::OnEditRotate)
	ON_COMMAND(ID_FILE_SAVE32772, &CImageJ2Dlg::OnFileSave32772)
	ON_COMMAND(ID_FILE_SAVEAS, &CImageJ2Dlg::OnFileSaveas)
	ON_COMMAND(ID_FLIP_LRFILP, &CImageJ2Dlg::OnFlipLrfilp)
	ON_COMMAND(ID_FLIP_UD, &CImageJ2Dlg::OnFlipUd)
	ON_COMMAND(ID_EDIT_REVERSE, &CImageJ2Dlg::OnEditReverse)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_COMMAND(ID_LINE_DRAG, &CImageJ2Dlg::OnLineDrag)
	ON_COMMAND(ID_LINE_CLICKTWICE, &CImageJ2Dlg::OnLineClicktwice)
	ON_WM_MOUSEWHEEL()
	ON_WM_MBUTTONDOWN()
	ON_WM_MBUTTONUP()
	ON_COMMAND(ID_HISTOGRAM_SHOWHIS, &CImageJ2Dlg::OnHistogramShowhis)
	ON_BN_CLICKED(IDC_BUTT_STRECH, &CImageJ2Dlg::OnBnClickedButtStrech)
END_MESSAGE_MAP()


// CImageJ2Dlg �޽��� ó����

BOOL CImageJ2Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// �ý��� �޴��� "����..." �޴� �׸��� �߰��մϴ�.

	// IDM_ABOUTBOX�� �ý��� ��� ������ �־�� �մϴ�.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
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

	// �� ��ȭ ������ �������� �����մϴ�.  ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	m_scale = 1;

	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
}

void CImageJ2Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�.  ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CImageJ2Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ�Դϴ�.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �������� �׸��ϴ�.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.
HCURSOR CImageJ2Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CImageJ2Dlg::MatToCImage(const cv::Mat& mat, CImage& cimage)
{
	if (mat.empty()) return;

	int width = mat.cols;
	int height = mat.rows;
	int channels = mat.channels();
	int step = mat.step;

	// ��Ʈ�� ���� ����
	BITMAPINFO bmi;
	memset(&bmi, 0, sizeof(bmi));
	bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bmi.bmiHeader.biWidth = width;
	bmi.bmiHeader.biHeight = -height; // top-down DIB
	bmi.bmiHeader.biPlanes = 1;
	bmi.bmiHeader.biBitCount = channels * 8;
	bmi.bmiHeader.biCompression = BI_RGB;
	bmi.bmiHeader.biSizeImage = step * height;

	// CImage �ʱ�ȭ
	cimage.Destroy();
	cimage.Create(width, height, channels * 8);

	// CImage�� ������ ����
	BYTE* dst = (BYTE*)cimage.GetBits();
	const BYTE* src = mat.data;
	for (int y = 0; y < height; y++)
	{
		memcpy(dst + y * cimage.GetPitch(), src + y * step, width * channels);
	}
}

void CImageJ2Dlg::OpenPicture(Mat ma){
	CRect rect;//���� ��Ʈ���� ũ�⸦ ������ CRect ��ü
	m_PicCtrl.GetWindowRect(rect);//GetWindowRect�� ����ؼ� ���� ��Ʈ���� ũ�⸦ �޴´�.
	CDC* dc; //���� ��Ʈ���� DC�� ������  CDC ������
	dc = m_PicCtrl.GetDC(); //���� ��Ʈ���� DC�� ��´�.

	MatToCImage(ma, cimage);

	//cimage.StretchBlt(dc->m_hDC, 0, 0, cimage.GetWidth(), cimage.GetHeight(), SRCCOPY);
	cimage.StretchBlt(dc->m_hDC, 0, 0, rect.Width(), rect.Height(), SRCCOPY);


	ReleaseDC(dc);//DC ����
}

void CImageJ2Dlg::OnFileOpen32771()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	TCHAR szFile[] = _T("�������(*.*)|*.*||");

	CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY, szFile);

	if (IDOK == dlg.DoModal())
	{
		pathName = dlg.GetPathName();
		cvstr = CT2A(pathName);
		Inputimage = imread(cvstr);

		//imshow(cvstr, Inputimage);
		OpenPicture(Inputimage);

	}
	rImage = Inputimage;
	nowImage = Inputimage;
}


void CImageJ2Dlg::OnConvertcolorGrayscale()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	if (!Inputimage.empty()) {
		Mat grayImage;
		cvtColor(nowImage, grayImage, COLOR_RGB2GRAY);
		cvtColor(grayImage, nowImage, COLOR_GRAY2BGR);
		//imshow("gray.jpg", grayImage);
		OpenPicture(nowImage);
		//nowImage = grayImage;

		Mat binaryImage;
		double thresh = 128; // �Ӱ谪
		double maxval = 255; // �ִ밪
		threshold(nowImage, binaryImage, thresh, maxval, cv::THRESH_BINARY);
		//cvtColor(binaryImage, grayImage, COLOR_GRAY2BGR);
		//OpenPicture(grayImage);
		imshow("binaryImage.jpg", binaryImage);
	}
	else
		MessageBox(_T("�̹����� ���� �ε����ּ���"), _T("alert"), NULL);
}


void CImageJ2Dlg::OnEditBlur()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	if (!Inputimage.empty()) {
		Mat BlurImage;
		GaussianBlur(nowImage, BlurImage, Size(7, 7), 0);
		OpenPicture(BlurImage);
		nowImage = BlurImage;
	}
	else
		MessageBox(_T("�̹����� ���� �ε����ּ���"), _T("alert"), NULL);
}


void CImageJ2Dlg::OnEditRotate()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	if (!nowImage.empty()) {

		int height = nowImage.rows;
		int width = nowImage.cols;

		// ȸ�� �߽��� �� ���� ����
		Point2f center(static_cast<float>(width / 2), static_cast<float>(height / 2));
		double angle = 90.0;  // 90�� ȸ��

		// ȸ�� ��ȯ ��Ʈ���� ���
		Mat rotMatrix = getRotationMatrix2D(center, angle, 1.0);  // 1.0�� ������ �Ű������Դϴ�.

		Mat rotatedImage;
		warpAffine(nowImage, rotatedImage, rotMatrix, Size(width, height));
		OpenPicture(rotatedImage);

		nowImage = rotatedImage;
	}
	else
		MessageBox(_T("�̹����� ���� �ε����ּ���"), _T("alert"), NULL);
}


void CImageJ2Dlg::OnFileSave32772()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	if (!nowImage.empty()) {
		imwrite(cvstr, nowImage);
	}
	else
		MessageBox(_T("�̹����� ���� �ε����ּ���"), _T("alert"), NULL);
}


void CImageJ2Dlg::OnFileSaveas()
{
	if (!nowImage.empty()) {
		CRect rect;
		GetClientRect(&rect);

		// Ŭ���̾�Ʈ ������ ũ�⸦ �����ɴϴ�.
		int width = rect.Width();
		int height = rect.Height();

		// Ŭ���̾�Ʈ DC�� �޸� DC�� �����մϴ�.
		CDC* pDC = GetDC();
		CDC memDC;
		memDC.CreateCompatibleDC(pDC);

		// ��Ʈ���� �����ϰ� �޸� DC�� �����մϴ�.
		CBitmap bmp;
		bmp.CreateCompatibleBitmap(pDC, width, height);
		CBitmap* pOldBmp = memDC.SelectObject(&bmp);

		// Ŭ���̾�Ʈ DC�� ������ �޸� DC�� �����մϴ�.
		memDC.BitBlt(0, 0, width, height, pDC, 0, 0, SRCCOPY);

		// CImage ��ü�� �����ϰ� ��Ʈ���� �ٿ��ֽ��ϴ�.
		CImage image;
		image.Attach((HBITMAP)bmp.Detach());

		// ���̾�α� ĸó �� ����
		memDC.SelectObject(pOldBmp);
		ReleaseDC(pDC);

		CString szFile = _T("JPEG Files(*.jpg)|*.jpg|PNG Files(*.png)|*.png|All Files(*.*)|*.*||");
		CString fileName = _T("SaveAs");
		CString ext;
		AfxExtractSubString(ext, pathName, 1, '.');
		CFileDialog fileDlg(FALSE, NULL, fileName + '.' + ext, OFN_OVERWRITEPROMPT, szFile);

		if (fileDlg.DoModal() == IDOK) {
			CString saveFilePath = fileDlg.GetPathName();
			
			GUID fileType;
			if (ext == _T("jpg"))
				fileType = Gdiplus::ImageFormatJPEG;
			else if (ext == _T("png"))
				fileType = Gdiplus::ImageFormatPNG;
			else if (ext == _T("bmp"))
				fileType = Gdiplus::ImageFormatBMP;
			else if (ext == _T("gif"))
				fileType = Gdiplus::ImageFormatGIF;
			else {
				AfxMessageBox(_T("Unsupported file format!"));
				return;
			}

			// CImage ��ü�� ���Ϸ� ����
			HRESULT hr = image.Save(saveFilePath, fileType);

			if (FAILED(hr)) {
				AfxMessageBox(_T("Error: Failed to save image!"));
			}
			else {
				AfxMessageBox(_T("Image saved successfully."));
			}
		}
	}
	else
		MessageBox(_T("�̹����� ���� �ε����ּ���"), _T("alert"), NULL);
}


void CImageJ2Dlg::OnFlipLrfilp()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	if (!Inputimage.empty()) {
		Mat filpImage;
		flip(nowImage, filpImage, 1);
		OpenPicture(filpImage);
		nowImage = filpImage;
	}
	else
		MessageBox(_T("�̹����� ���� �ε����ּ���"), _T("alert"), NULL);
}


void CImageJ2Dlg::OnFlipUd()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	if (!Inputimage.empty()) {
		Mat filpImage;
		flip(nowImage, filpImage, 0);
		OpenPicture(filpImage);
		nowImage = filpImage;
	}
	else
		MessageBox(_T("�̹����� ���� �ε����ּ���"), _T("alert"), NULL);
}


void CImageJ2Dlg::OnEditReverse()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	if (!Inputimage.empty()) {
		Mat notImage;
		bitwise_not(nowImage, notImage);
		OpenPicture(notImage);
		nowImage = notImage;
	}
	else
		MessageBox(_T("�̹����� ���� �ε����ּ���"), _T("alert"), NULL);
}


void CImageJ2Dlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	if (m_DrawMode == "LineDrag") {
		nSx = point.x;
		nSy = point.y;	}
	CDialogEx::OnLButtonDown(nFlags, point);
}

void CImageJ2Dlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	CClientDC dc(this);
	CPen pEn;
	pEn.CreatePen(PS_SOLID, 3, RGB(0, 0, 0));
	dc.SelectObject(&pEn);

	if (m_DrawMode == "LineClick") {
		if (nClickFlag == 0) {
			nSx = point.x;
			nSy = point.y;
			nClickFlag = 1;
		}
		else {
			dc.MoveTo(nSx, nSy);
			dc.LineTo(point.x, point.y);
			nClickFlag = 0;
		}
	}
	else if (m_DrawMode == "LineDrag") {
		dc.MoveTo(nSx, nSy);
		dc.LineTo(point.x, point.y);
	}

	CDialogEx::OnLButtonUp(nFlags, point);
}


void CImageJ2Dlg::OnLineDrag()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	if (m_DrawMode != "LineDrag")
		m_DrawMode = "LineDrag";
	else
		m_DrawMode = "";
}


void CImageJ2Dlg::OnLineClicktwice()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	if (m_DrawMode != "LineClick")
		m_DrawMode = "LineClick";
	else
		m_DrawMode = "";
}

void CImageJ2Dlg::ZoomImage(double scale)
{
	if (nowImage.empty()) return;

	Mat resizedImage;
	resize(nowImage, resizedImage, Size(), scale, scale, INTER_LINEAR);

	// Display the resized image
	OpenPicture(resizedImage);
	nowImage = resizedImage;
}

BOOL CImageJ2Dlg::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	if (zDelta > 0)
	{
		if (m_scale < 1.5)
			m_scale *= 1.05; // �� ���� ��ũ���ϸ� Ȯ��
		else
			MessageBox(_T("�ִ� Ȯ���Դϴ�"), _T("alert"), NULL);
	}
	else
	{
		if (m_scale >= 0.5)
			m_scale /= 1.05; // �� �Ʒ��� ��ũ���ϸ� ���
		else
			MessageBox(_T("���̻� ��� �Ұ�"), _T("alert"), NULL);
	}

	ZoomImage(m_scale);

	return CDialogEx::OnMouseWheel(nFlags, zDelta, pt);
}

void CImageJ2Dlg::OnMButtonDown(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	nPicX = point.x;
	nPicY = point.y;

	Mat M = (Mat_<double>(2, 3) << 1, 0, nPicX, 0, 1, nPicY);
	Mat moveImage;
	warpAffine(nowImage, moveImage, M, nowImage.size());
	OpenPicture(moveImage);


	CDialogEx::OnMButtonDown(nFlags, point);
}


void CImageJ2Dlg::OnMButtonUp(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	CDialogEx::OnMButtonUp(nFlags, point);
}

void CImageJ2Dlg::OpenHisto(Mat ma) {
	CRect rect2;//���� ��Ʈ���� ũ�⸦ ������ CRect ��ü
	m_HistoCtrl.GetWindowRect(rect2);//GetWindowRect�� ����ؼ� ���� ��Ʈ���� ũ�⸦ �޴´�.
	CDC* dc2; //���� ��Ʈ���� DC�� ������  CDC ������
	dc2 = m_HistoCtrl.GetDC(); //���� ��Ʈ���� DC�� ��´�.

	MatToCImage(ma, cimage);

	//cimage.StretchBlt(dc->m_hDC, 0, 0, cimage.GetWidth(), cimage.GetHeight(), SRCCOPY);
	cimage.StretchBlt(dc2->m_hDC, 0, 0, rect2.Width(), rect2.Height(), SRCCOPY);


	ReleaseDC(dc2);//DC ����
}

void CImageJ2Dlg::OnHistogramShowhis()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	int histSize = 256;
	int hist_w = 800; // ������׷� �ʺ�
	int hist_h = 800; // ������׷� ����
	int bin_w = cvRound((double)hist_w / histSize);

	Mat histImage(hist_h, hist_w, CV_8UC3, Scalar(255, 255, 255));

	// B, G, R ä�� �и�
	vector<Mat> bgr_planes;
	split(nowImage, bgr_planes);

	// ������׷� ����
	float range[] = { 0, 256 };
	const float* histRange = { range };
	bool uniform = true, accumulate = false;

	Mat b_hist, g_hist, r_hist;

	// �� ä���� ������׷� ���
	calcHist(&bgr_planes[0], 1, 0, Mat(), b_hist, 1, &histSize, &histRange, uniform, accumulate);
	calcHist(&bgr_planes[1], 1, 0, Mat(), g_hist, 1, &histSize, &histRange, uniform, accumulate);
	calcHist(&bgr_planes[2], 1, 0, Mat(), r_hist, 1, &histSize, &histRange, uniform, accumulate);

	// ������׷� ����ȭ
	normalize(b_hist, b_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());
	normalize(g_hist, g_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());
	normalize(r_hist, r_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());

	// ������׷� �׸���
	for (int i = 1; i < histSize; i++)
	{
		line(histImage, Point(bin_w * (i - 1), hist_h - cvRound(b_hist.at<float>(i - 1))),
			Point(bin_w * (i), hist_h - cvRound(b_hist.at<float>(i))),
			Scalar(255, 0, 0), 2, 8, 0);
		line(histImage, Point(bin_w * (i - 1), hist_h - cvRound(g_hist.at<float>(i - 1))),
			Point(bin_w * (i), hist_h - cvRound(g_hist.at<float>(i))),
			Scalar(0, 255, 0), 2, 8, 0);
		line(histImage, Point(bin_w * (i - 1), hist_h - cvRound(r_hist.at<float>(i - 1))),
			Point(bin_w * (i), hist_h - cvRound(r_hist.at<float>(i))),
			Scalar(0, 0, 255), 2, 8, 0);
	}

	// ������׷� �̹��� ǥ��
	//imshow("Histogram", histImage);
	OpenHisto(histImage);
}


void CImageJ2Dlg::OnBnClickedButtStrech()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	Mat strchImage;

	double minVal, maxVal;
	minMaxLoc(nowImage, &minVal, &maxVal);

	// ������׷� ��Ʈ��Ī
	strchImage = (nowImage - minVal) * (255.0 / (maxVal - minVal));

	OpenPicture(strchImage);
	nowImage = strchImage;
	OnHistogramShowhis();
}
