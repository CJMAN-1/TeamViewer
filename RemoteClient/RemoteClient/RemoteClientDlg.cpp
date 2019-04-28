
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


// CRemoteClientDlg �޽��� ó����

BOOL CRemoteClientDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// �� ��ȭ ������ �������� �����մϴ�.  ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.

	int nx = 0, ny = 0;
	CImage capimage;
	CWnd *pDesktopWnd = GetDesktopWindow();
	HDC hDC = NULL;
	CWindowDC DeskTopDC(pDesktopWnd);
	nx = GetSystemMetrics(SM_CXSCREEN);
	ny = GetSystemMetrics(SM_CYSCREEN);
	////////////
	capimage.Create(nx, ny, 32);
	hDC = capimage.GetDC();
	BitBlt(hDC, 0, 0, nx, ny, DeskTopDC.m_hDC, 0, 0, SRCCOPY);
	////////////////
	IStream *p_stream = NULL;
	HGLOBAL h_buffer = ::GlobalAlloc(GMEM_MOVEABLE, 1024 * 1024);

	if (h_buffer != NULL) {
		int jpg_data_size = 0;

	
		if (::CreateStreamOnHGlobal(h_buffer, FALSE, &p_stream) == S_OK) {
			capimage.Save(p_stream, Gdiplus::ImageFormatJPEG);
			capimage.Save(_T("cap.jpg"), Gdiplus::ImageFormatJPEG);
			capimage.ReleaseDC();
		}
		void *p_jpg_data = ::GlobalLock(h_buffer);

		for (int i = 100000; i < 500000; i++) {
			if (*((char *)p_jpg_data + i) == (char)0xff) {
				if (*((char *)p_jpg_data + i +1) == (char)0xd9) {
					printf("sd");
					FILE * tlqk ;
					tlqk = fopen("tlqk.txt", "w");
					fprintf(tlqk, "%d", i);
					fclose(tlqk);
					break;
				}
			}
		}
		::GlobalFree(h_buffer);
	}

	

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
