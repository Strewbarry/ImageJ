
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
		cvtColor(nowImage, grayImage, COLOR_BGR2GRAY);
		OpenPicture(grayImage);
		nowImage = grayImage;
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


void CImageJ2Dlg::OnFileSave32772()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	imwrite(cvstr, nowImage);
}


void CImageJ2Dlg::OnFileSaveas()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	TCHAR szFile[] = _T("�������(*.*)|*.*||");
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
