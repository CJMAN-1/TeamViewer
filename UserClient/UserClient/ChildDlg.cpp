// ChildDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "UserClient.h"
#include "ChildDlg.h"
#include "afxdialogex.h"



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
