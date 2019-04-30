
// RemoteClientDlg.cpp : ���� ����
//

#include "stdafx.h"
#include "RemoteClient.h"
#include "RemoteClientDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CRemoteClientDlg ��ȭ ����
//TODO : ������ �޽��� ��ŷ �� �߻� �غ�����. �ؼ� �ҽ� �����صѰ�


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

//ȭ���� ũ�⸦ ���´�.
void CRemoteClientDlg::GetScreenSize() {
	screenX = GetSystemMetrics(SM_CXSCREEN);
	screenY = GetSystemMetrics(SM_CYSCREEN);
}

//����ȭ��� CImage��ü�� DC�� ��������� �����Ѵ�.
void CRemoteClientDlg::GetScnImageDC(CImage& image) {
	pDesktopWnd = GetDesktopWindow();
	DeskTopDC = pDesktopWnd->GetDC();

	image.Create(screenX, screenY, 32);
	hDC = image.GetDC();
}

//���� ȭ���� cimage�� �����Ѵ�.
void CRemoteClientDlg::CaptureScreenTo(CImage& screen) {
	BitBlt(hDC, 0, 0, screenX, screenY, DeskTopDC->m_hDC, 0, 0, SRCCOPY);
}

//HGLOBAL ���۸� ����� ����Ҽ� �ֵ��� void�� �����͸� ��ȯ�Ѵ�.
void* CRemoteClientDlg::MakeMemoryBuffer(int size) {
	imageBuffer = ::GlobalAlloc(GMEM_MOVEABLE, size);
	return ::GlobalLock(imageBuffer);
}

//memoryStream�� buffer�� ���� screen�� �����ϰ� screen�� ũ�⸦ ��ȯ�Ѵ�.
//�����ؾ���
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

//ĸ���ϰ�  ���� �ѹ��� �ϴ°�
int CRemoteClientDlg::CapturenSaveOnMemory(IStream *memoryStream, HGLOBAL* buffer, CImage& screen) {
	CaptureScreenTo(screen);

	return SaveScreenOnMemory(memoryStream, buffer, screen);
}
//////////////////////////////////////

// CRemoteClientDlg �޽��� ó����

BOOL CRemoteClientDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// �� ��ȭ ������ �������� �����մϴ�.  ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.


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
	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
}

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�.  ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CRemoteClientDlg::OnPaint()
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
HCURSOR CRemoteClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CRemoteClientDlg::OnBnClickedCancel()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CDialogEx::OnCancel();
}


void CRemoteClientDlg::OnBnClickedButton1()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

}
