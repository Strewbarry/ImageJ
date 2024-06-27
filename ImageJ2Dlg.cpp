
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
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CImageJ2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//  DDX_Control(pDX, IDC_PICTURE, m_PicCtrl);
	DDX_Control(pDX, IDC_PICTURE, m_PicCtrl);
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
		cvtColor(nowImage, grayImage, COLOR_BGR2GRAY);
		OpenPicture(grayImage);
		nowImage = grayImage;
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


void CImageJ2Dlg::OnFileSave32772()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	imwrite(cvstr, nowImage);
}


void CImageJ2Dlg::OnFileSaveas()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	TCHAR szFile[] = _T("모든파일(*.*)|*.*||");
	CString outFileName;
	AfxExtractSubString(outFileName, pathName, 1, '.');

	CFileDialog dlg(FALSE, NULL, '.' + outFileName, OFN_OVERWRITEPROMPT, szFile);
	if (IDOK == dlg.DoModal())
	{
		CString saveFilePath = dlg.GetPathName();
		string svstr = CT2A(saveFilePath);
		imwrite(svstr, nowImage);
	}
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
