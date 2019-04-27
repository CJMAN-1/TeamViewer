// ChildDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "UserClient.h"
#include "ChildDlg.h"
#include "afxdialogex.h"

#define BUFSIZE 168643

// ChildDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(ChildDlg, CDialogEx)

ChildDlg::ChildDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_CHILDDLG, pParent)
{

}

ChildDlg::~ChildDlg()
{
}

void ChildDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(ChildDlg, CDialogEx)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// ChildDlg 메시지 처리기입니다.


BOOL ChildDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	HWND hwnd;
	CWnd* cwnd;
	int retval;
	WSADATA wsa;

	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		return -1;

	SOCKET sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	SOCKADDR_IN server;
	SOCKADDR_IN client;

	ZeroMemory(&server, sizeof(server));
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = inet_addr("127.0.0.1");
	server.sin_port = htons(9000);

	ZeroMemory(&client, sizeof(client));
	client.sin_family = AF_INET;
	client.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	client.sin_port = htons(9001);

	bind(sock, (sockaddr *)&client, sizeof(client));
	//	char buf[BUFSIZE+1];
	int len;

	//	buf[BUFSIZE - 1] = '\0';
	//	len = BUFSIZE;
	ifstream fi;    // 읽기용 파일 
	ofstream fo; // 쓰기용 파일

	FILE * file = fopen("image.jpg", "rb");
	fseek(file, 0, SEEK_END);
	len = ftell(file);
	fseek(file, 0, SEEK_SET);
	char *buf = (char*)malloc(len);
	fread(buf, len, 1, file);


	fclose(file);

	for (int i = 0; i < 168; i++) {
		retval = sendto(sock, buf + i * 1000, 1000, 0, (sockaddr *)&server, sizeof(server));
	}
	
	// TODO:  여기에 추가 초기화 작업을 추가합니다.
/*	cx = GetSystemMetrics(SM_CXFULLSCREEN);
	cy = GetSystemMetrics(SM_CYFULLSCREEN);
	hwnd = GetSafeHwnd();
	cwnd = FromHandle(hwnd);
	SetWindowPos(&wndTop, -cx_space, 0, cx+2*cx_space, cy+cy_space, NULL);
	
	path_capturedSc = _T("hwang.jpg");
	HRESULT hResult = capturedSc.Load(path_capturedSc);
*/	

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void ChildDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 여기에 메시지 처리기 코드를 추가합니다.
					   // 그리기 메시지에 대해서는 CDialogEx::OnPaint()을(를) 호출하지 마십시오.
/*	RECT rect;
	GetClientRect(&rect);
	SetStretchBltMode(dc.m_hDC, BLACKONWHITE);
	capturedSc.StretchBlt(dc.m_hDC, rect);
	::InvalidateRect(m_hWnd, NULL, TRUE);
*/
}
