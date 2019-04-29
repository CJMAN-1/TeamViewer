
// UserClientDlg.cpp : ���� ����
//

#include "stdafx.h"
#include "UserClient.h"
#include "UserClientDlg.h"
#include "afxdialogex.h"
#include <WinUser.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CUserClientDlg ��ȭ ����



CUserClientDlg::CUserClientDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_USERCLIENT_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CUserClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CUserClientDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CUserClientDlg::OnBnClickedButton1)
	ON_EN_CHANGE(IDC_EDIT1, &CUserClientDlg::OnEnChangeEdit1)
	ON_BN_CLICKED(IDCANCEL, &CUserClientDlg::OnBnClickedCancel)
END_MESSAGE_MAP()

//ȭ���� ũ�⸦ ���´�.
void CUserClientDlg::GetScreenSize() {
	screenX = GetSystemMetrics(SM_CXSCREEN);
	screenY = GetSystemMetrics(SM_CYSCREEN);
}

//����ȭ��� CImage��ü�� DC�� ��������� �����Ѵ�.
void CUserClientDlg::GetScnImageDC(CImage& image) {
	pDesktopWnd = GetDesktopWindow();
	DeskTopDC = pDesktopWnd->GetDC();

	image.Create(screenX, screenY, 32);
	hDC = image.GetDC();
}

//���� ȭ���� cimage�� �����Ѵ�.
void CUserClientDlg::CaptureScreenTo(CImage& screen) {
	BitBlt(hDC, 0, 0, screenX, screenY, DeskTopDC->m_hDC, 0, 0, SRCCOPY);
}

//HGLOBAL ���۸� ����� ����Ҽ� �ֵ��� void�� �����͸� ��ȯ�Ѵ�.
void* CUserClientDlg::MakeMemoryBuffer(int size) {
	imageBuffer = ::GlobalAlloc(GMEM_MOVEABLE, size);
	return ::GlobalLock(imageBuffer);
}

//memoryStream�� buffer�� ���� screen�� �����ϰ� screen�� ũ�⸦ ��ȯ�Ѵ�.
//�����ؾ���
int CUserClientDlg::SaveScreenOnMemory(IStream *memoryStream, HGLOBAL* buffer, CImage& screen) {
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

		return i + 1;
	}
	else {
		return -1;
	}
}

//ĸ���ϰ�  ���� �ѹ��� �ϴ°�
int CUserClientDlg::CapturenSaveOnMemory(IStream *memoryStream, HGLOBAL* buffer, CImage& screen) {
	CaptureScreenTo(screen);

	return SaveScreenOnMemory(memoryStream, buffer, screen);
}
//////////////////////////////////////

// CUserClientDlg �޽��� ó����

BOOL CUserClientDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// �� ��ȭ ������ �������� �����մϴ�.  ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.
	
	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	SOCK.BindUdpSock(9900);
	SOCK.RegisterOtherSock("127.0.0.1", 9000);
	int addrlen = sizeof(SOCK.other_sockAddr);
//	recvfrom(*SOCK.udp_sock, buf + i * 1000, 1000, 0, (sockaddr *)&SOCK.other_sockAddr,&addrlen);

	return FALSE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
}

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�.  ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CUserClientDlg::OnPaint()
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
HCURSOR CUserClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CUserClientDlg::OnBnClickedButton1()
{
	
	ChildDlg child;

	child.DoModal();

	child.DestroyWindow();
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}


void CUserClientDlg::OnEnChangeEdit1()
{
	// TODO:  RICHEDIT ��Ʈ���� ���, �� ��Ʈ����
	// CDialogEx::OnInitDialog() �Լ��� ������ 
	//�ϰ� ����ũ�� OR �����Ͽ� ������ ENM_CHANGE �÷��׸� �����Ͽ� CRichEditCtrl().SetEventMask()�� ȣ������ ������
	// �� �˸� �޽����� ������ �ʽ��ϴ�.

	// TODO:  ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}


void CUserClientDlg::OnBnClickedCancel()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CDialogEx::OnCancel();
}
