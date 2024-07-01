
// ImageJ2Dlg.cpp : 구현 파일
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

// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
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


// CImageJ2Dlg 대화 상자



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


// CImageJ2Dlg 메시지 처리기

BOOL CImageJ2Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
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

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	m_scale = 1;

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
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

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CImageJ2Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
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

	// 비트맵 정보 설정
	BITMAPINFO bmi;
	memset(&bmi, 0, sizeof(bmi));
	bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bmi.bmiHeader.biWidth = width;
	bmi.bmiHeader.biHeight = -height; // top-down DIB
	bmi.bmiHeader.biPlanes = 1;
	bmi.bmiHeader.biBitCount = channels * 8;
	bmi.bmiHeader.biCompression = BI_RGB;
	bmi.bmiHeader.biSizeImage = step * height;

	// CImage 초기화
	cimage.Destroy();
	cimage.Create(width, height, channels * 8);

	// CImage에 데이터 복사
	BYTE* dst = (BYTE*)cimage.GetBits();
	const BYTE* src = mat.data;
	for (int y = 0; y < height; y++)
	{
		memcpy(dst + y * cimage.GetPitch(), src + y * step, width * channels);
	}
}

void CImageJ2Dlg::OpenPicture(Mat ma){
	CRect rect;//픽쳐 컨트롤의 크기를 저장할 CRect 객체
	m_PicCtrl.GetWindowRect(rect);//GetWindowRect를 사용해서 픽쳐 컨트롤의 크기를 받는다.
	CDC* dc; //픽쳐 컨트롤의 DC를 가져올  CDC 포인터
	dc = m_PicCtrl.GetDC(); //픽쳐 컨트롤의 DC를 얻는다.

	MatToCImage(ma, cimage);

	//cimage.StretchBlt(dc->m_hDC, 0, 0, cimage.GetWidth(), cimage.GetHeight(), SRCCOPY);
	cimage.StretchBlt(dc->m_hDC, 0, 0, rect.Width(), rect.Height(), SRCCOPY);


	ReleaseDC(dc);//DC 해제
}

void CImageJ2Dlg::OnFileOpen32771()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	TCHAR szFile[] = _T("모든파일(*.*)|*.*||");

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
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	if (!Inputimage.empty()) {
		Mat grayImage;
		cvtColor(nowImage, grayImage, COLOR_RGB2GRAY);
		cvtColor(grayImage, nowImage, COLOR_GRAY2BGR);
		//imshow("gray.jpg", grayImage);
		OpenPicture(nowImage);
		//nowImage = grayImage;

		Mat binaryImage;
		double thresh = 128; // 임계값
		double maxval = 255; // 최대값
		threshold(nowImage, binaryImage, thresh, maxval, cv::THRESH_BINARY);
		//cvtColor(binaryImage, grayImage, COLOR_GRAY2BGR);
		//OpenPicture(grayImage);
		imshow("binaryImage.jpg", binaryImage);
	}
	else
		MessageBox(_T("이미지를 먼저 로드해주세요"), _T("alert"), NULL);
}


void CImageJ2Dlg::OnEditBlur()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	if (!Inputimage.empty()) {
		Mat BlurImage;
		GaussianBlur(nowImage, BlurImage, Size(7, 7), 0);
		OpenPicture(BlurImage);
		nowImage = BlurImage;
	}
	else
		MessageBox(_T("이미지를 먼저 로드해주세요"), _T("alert"), NULL);
}


void CImageJ2Dlg::OnEditRotate()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	if (!nowImage.empty()) {

		int height = nowImage.rows;
		int width = nowImage.cols;

		// 회전 중심점 및 각도 설정
		Point2f center(static_cast<float>(width / 2), static_cast<float>(height / 2));
		double angle = 90.0;  // 90도 회전

		// 회전 변환 매트릭스 계산
		Mat rotMatrix = getRotationMatrix2D(center, angle, 1.0);  // 1.0은 스케일 매개변수입니다.

		Mat rotatedImage;
		warpAffine(nowImage, rotatedImage, rotMatrix, Size(width, height));
		OpenPicture(rotatedImage);

		nowImage = rotatedImage;
	}
	else
		MessageBox(_T("이미지를 먼저 로드해주세요"), _T("alert"), NULL);
}


void CImageJ2Dlg::OnFileSave32772()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	if (!nowImage.empty()) {
		imwrite(cvstr, nowImage);
	}
	else
		MessageBox(_T("이미지를 먼저 로드해주세요"), _T("alert"), NULL);
}


void CImageJ2Dlg::OnFileSaveas()
{
	if (!nowImage.empty()) {
		CRect rect;
		GetClientRect(&rect);

		// 클라이언트 영역의 크기를 가져옵니다.
		int width = rect.Width();
		int height = rect.Height();

		// 클라이언트 DC와 메모리 DC를 생성합니다.
		CDC* pDC = GetDC();
		CDC memDC;
		memDC.CreateCompatibleDC(pDC);

		// 비트맵을 생성하고 메모리 DC에 선택합니다.
		CBitmap bmp;
		bmp.CreateCompatibleBitmap(pDC, width, height);
		CBitmap* pOldBmp = memDC.SelectObject(&bmp);

		// 클라이언트 DC의 내용을 메모리 DC로 복사합니다.
		memDC.BitBlt(0, 0, width, height, pDC, 0, 0, SRCCOPY);

		// CImage 객체를 생성하고 비트맵을 붙여넣습니다.
		CImage image;
		image.Attach((HBITMAP)bmp.Detach());

		// 다이얼로그 캡처 후 해제
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

			// CImage 객체를 파일로 저장
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
		MessageBox(_T("이미지를 먼저 로드해주세요"), _T("alert"), NULL);
}


void CImageJ2Dlg::OnFlipLrfilp()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	if (!Inputimage.empty()) {
		Mat filpImage;
		flip(nowImage, filpImage, 1);
		OpenPicture(filpImage);
		nowImage = filpImage;
	}
	else
		MessageBox(_T("이미지를 먼저 로드해주세요"), _T("alert"), NULL);
}


void CImageJ2Dlg::OnFlipUd()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	if (!Inputimage.empty()) {
		Mat filpImage;
		flip(nowImage, filpImage, 0);
		OpenPicture(filpImage);
		nowImage = filpImage;
	}
	else
		MessageBox(_T("이미지를 먼저 로드해주세요"), _T("alert"), NULL);
}


void CImageJ2Dlg::OnEditReverse()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	if (!Inputimage.empty()) {
		Mat notImage;
		bitwise_not(nowImage, notImage);
		OpenPicture(notImage);
		nowImage = notImage;
	}
	else
		MessageBox(_T("이미지를 먼저 로드해주세요"), _T("alert"), NULL);
}


void CImageJ2Dlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (m_DrawMode == "LineDrag") {
		nSx = point.x;
		nSy = point.y;	}
	CDialogEx::OnLButtonDown(nFlags, point);
}

void CImageJ2Dlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
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
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	if (m_DrawMode != "LineDrag")
		m_DrawMode = "LineDrag";
	else
		m_DrawMode = "";
}


void CImageJ2Dlg::OnLineClicktwice()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
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
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (zDelta > 0)
	{
		if (m_scale < 1.5)
			m_scale *= 1.05; // 휠 위로 스크롤하면 확대
		else
			MessageBox(_T("최대 확대입니다"), _T("alert"), NULL);
	}
	else
	{
		if (m_scale >= 0.5)
			m_scale /= 1.05; // 휠 아래로 스크롤하면 축소
		else
			MessageBox(_T("더이상 축소 불가"), _T("alert"), NULL);
	}

	ZoomImage(m_scale);

	return CDialogEx::OnMouseWheel(nFlags, zDelta, pt);
}

void CImageJ2Dlg::OnMButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
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
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CDialogEx::OnMButtonUp(nFlags, point);
}

void CImageJ2Dlg::OpenHisto(Mat ma) {
	CRect rect2;//픽쳐 컨트롤의 크기를 저장할 CRect 객체
	m_HistoCtrl.GetWindowRect(rect2);//GetWindowRect를 사용해서 픽쳐 컨트롤의 크기를 받는다.
	CDC* dc2; //픽쳐 컨트롤의 DC를 가져올  CDC 포인터
	dc2 = m_HistoCtrl.GetDC(); //픽쳐 컨트롤의 DC를 얻는다.

	MatToCImage(ma, cimage);

	//cimage.StretchBlt(dc->m_hDC, 0, 0, cimage.GetWidth(), cimage.GetHeight(), SRCCOPY);
	cimage.StretchBlt(dc2->m_hDC, 0, 0, rect2.Width(), rect2.Height(), SRCCOPY);


	ReleaseDC(dc2);//DC 해제
}

void CImageJ2Dlg::OnHistogramShowhis()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	int histSize = 256;
	int hist_w = 800; // 히스토그램 너비
	int hist_h = 800; // 히스토그램 높이
	int bin_w = cvRound((double)hist_w / histSize);

	Mat histImage(hist_h, hist_w, CV_8UC3, Scalar(255, 255, 255));

	// B, G, R 채널 분리
	vector<Mat> bgr_planes;
	split(nowImage, bgr_planes);

	// 히스토그램 설정
	float range[] = { 0, 256 };
	const float* histRange = { range };
	bool uniform = true, accumulate = false;

	Mat b_hist, g_hist, r_hist;

	// 각 채널의 히스토그램 계산
	calcHist(&bgr_planes[0], 1, 0, Mat(), b_hist, 1, &histSize, &histRange, uniform, accumulate);
	calcHist(&bgr_planes[1], 1, 0, Mat(), g_hist, 1, &histSize, &histRange, uniform, accumulate);
	calcHist(&bgr_planes[2], 1, 0, Mat(), r_hist, 1, &histSize, &histRange, uniform, accumulate);

	// 히스토그램 정규화
	normalize(b_hist, b_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());
	normalize(g_hist, g_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());
	normalize(r_hist, r_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());

	// 히스토그램 그리기
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

	// 히스토그램 이미지 표시
	//imshow("Histogram", histImage);
	OpenHisto(histImage);
}


void CImageJ2Dlg::OnBnClickedButtStrech()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	Mat strchImage;

	double minVal, maxVal;
	minMaxLoc(nowImage, &minVal, &maxVal);

	// 히스토그램 스트래칭
	strchImage = (nowImage - minVal) * (255.0 / (maxVal - minVal));

	OpenPicture(strchImage);
	nowImage = strchImage;
	OnHistogramShowhis();
}
