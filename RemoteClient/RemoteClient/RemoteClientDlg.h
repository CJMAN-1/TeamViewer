
// RemoteClientDlg.h : 헤더 파일
//

#pragma once
#include <iostream>
#include "cjsocket.h"
using namespace std;

// CRemoteClientDlg 대화 상자
class CRemoteClientDlg : public CDialogEx
{
// 생성입니다.
public:
	CRemoteClientDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_REMOTECLIENT_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedButton1();
protected://화면 캡쳐 관련부분
	int screenX, screenY;
	CImage capScreen;
	CWnd *pDesktopWnd;
	HDC hDC;
	CDC* DeskTopDC;
	IStream *imageBufferStream;
	HGLOBAL imageBuffer;
	int jpgDataSize;
	void* pJpgData;
	cjSocket SOCK;
	
	//TODO : DC ,buffer 해제하는 부분들 나중에 신경쓰기
	void GetScreenSize();
	void GetScnImageDC(CImage& image);
	void CaptureScreenTo(CImage& screen);
	void* MakeMemoryBuffer(int size);
	int SaveScreenOnMemory(IStream *memoryStream, HGLOBAL* buffer, CImage& screen);
	int CapturenSaveOnMemory(IStream *memoryStream, HGLOBAL* buffer, CImage& screen);

	enum {//image 관련 enum
		IMAGEBUFSIZE = 500000,
		MIN_IMAGE_SIZE = 100000,
		MAX_IMAGE_SIZE = 500000,
		END_JPG_H = (char)0xff,
		END_JPG_L = (char)0xd9
	};
};
