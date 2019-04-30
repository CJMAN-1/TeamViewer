
// RemoteClientDlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "RemoteClient.h"
#include "RemoteClientDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CRemoteClientDlg 대화 상자
//TODO : 윈도우 메시지 후킹 및 발생 해봐야함. 해서 소스 보관해둘것


CRemoteClientDlg::CRemoteClientDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_REMOTECLIENT_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CRemoteClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CRemoteClientDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDCANCEL, &CRemoteClientDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON1, &CRemoteClientDlg::OnBnClickedButton1)
END_MESSAGE_MAP()
///////////////////////////////////////

//화면의 크기를 얻어온다.
void CRemoteClientDlg::GetScreenSize() {
	screenX = GetSystemMetrics(SM_CXSCREEN);
	screenY = GetSystemMetrics(SM_CYSCREEN);
}

//바탕화면과 CImage객체의 DC를 멤버변수에 저장한다.
void CRemoteClientDlg::GetScnImageDC(CImage& image) {
	pDesktopWnd = GetDesktopWindow();
	DeskTopDC = pDesktopWnd->GetDC();

	image.Create(screenX, screenY, 32);
	hDC = image.GetDC();
}

//현재 화면을 cimage에 복사한다.
void CRemoteClientDlg::CaptureScreenTo(CImage& screen) {
	BitBlt(hDC, 0, 0, screenX, screenY, DeskTopDC->m_hDC, 0, 0, SRCCOPY);
}

//HGLOBAL 버퍼를 만들고 사용할수 있도록 void형 포인터를 반환한다.
void* CRemoteClientDlg::MakeMemoryBuffer(int size) {
	imageBuffer = ::GlobalAlloc(GMEM_MOVEABLE, size);
	return ::GlobalLock(imageBuffer);
}

//memoryStream을 buffer에 열어 screen을 저장하고 screen의 크기를 반환한다.
//수정해야함
int CRemoteClientDlg::SaveScreenOnMemory(IStream *memoryStream, HGLOBAL* buffer, CImage& screen) {
	if (imageBuffer != NULL) {
		if (::CreateStreamOnHGlobal(*buffer, FALSE, &memoryStream) == S_OK) {
			screen.Save(memoryStream, Gdiplus::ImageFormatJPEG);
			screen.Save(_T("cap.jpg"), Gdiplus::ImageFormatJPEG);

		}
		int i;
		for (i = MIN_IMAGE_SIZE; i < MAX_IMAGE_SIZE; i++) {
			if (*((char *)pJpgData + i) == END_JPG_H) {
				if (*((char *)pJpgData + i + 1) == END_JPG_L) {
					FILE * tlqk;
					tlqk = fopen("tlqk.txt", "w");
					fprintf(tlqk, "%d", i);
					fclose(tlqk);
					break;
				}
			}
		}

		return i+1;
	}
	else {
		return -1;
	}
}

//캡쳐하고  저장 한번에 하는거
int CRemoteClientDlg::CapturenSaveOnMemory(IStream *memoryStream, HGLOBAL* buffer, CImage& screen) {
	CaptureScreenTo(screen);

	return SaveScreenOnMemory(memoryStream, buffer, screen);
}
//////////////////////////////////////

// CRemoteClientDlg 메시지 처리기

BOOL CRemoteClientDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.


	GetScreenSize();
	GetScnImageDC(capScreen);
	CaptureScreenTo(capScreen);

	pJpgData = MakeMemoryBuffer(IMAGEBUFSIZE);

	jpgDataSize = CapturenSaveOnMemory(imageBufferStream, &imageBuffer, capScreen);
	
	SOCK.BindUdpSock(9000);
	SOCK.RegisterOtherSock("127.0.0.1", 9900);

	SOCK.TransImage((char*)pJpgData, jpgDataSize);

	imageBufferStream->Release();
	::GlobalFree(imageBuffer);
	capScreen.ReleaseDC();
	closesocket(*SOCK.udp_sock);
	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CRemoteClientDlg::OnPaint()
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
HCURSOR CRemoteClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CRemoteClientDlg::OnBnClickedCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CDialogEx::OnCancel();
}


void CRemoteClientDlg::OnBnClickedButton1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

}
