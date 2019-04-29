
// UserClientDlg.h : ��� ����
//

#pragma once
#include "ChildDlg.h"
#include <atlimage.h>
#include <iostream>
#include "cjsocket.h"
using namespace std;

// CUserClientDlg ��ȭ ����
class CUserClientDlg : public CDialogEx
{
// �����Դϴ�.
public:
	CUserClientDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_USERCLIENT_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.


// �����Դϴ�.
protected:
	HICON m_hIcon;

	// ������ �޽��� �� �Լ�
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnBnClickedCancel();
protected://ȭ�� ĸ�� ���úκ�
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

	void GetScreenSize();
	void GetScnImageDC(CImage& image);
	void CaptureScreenTo(CImage& screen);
	void* MakeMemoryBuffer(int size);
	int SaveScreenOnMemory(IStream *memoryStream, HGLOBAL* buffer, CImage& screen);
	int CapturenSaveOnMemory(IStream *memoryStream, HGLOBAL* buffer, CImage& screen);

	enum {//image ���� enum
		IMAGEBUFSIZE = 500000,
		MIN_IMAGE_SIZE = 100000,
		MAX_IMAGE_SIZE = 500000,
		END_JPG_H = (char)0xff,
		END_JPG_L = (char)0xd9
	};
};
