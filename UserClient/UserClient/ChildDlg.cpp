// ChildDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "UserClient.h"
#include "ChildDlg.h"
#include "afxdialogex.h"



// ChildDlg ��ȭ �����Դϴ�.

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


// ChildDlg �޽��� ó�����Դϴ�.


BOOL ChildDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	HWND hwnd;
	CWnd* cwnd;
	
	return TRUE;  // return TRUE unless you set the focus to a control
				  // ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}


void ChildDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
					   // �׸��� �޽����� ���ؼ��� CDialogEx::OnPaint()��(��) ȣ������ ���ʽÿ�.
/*	RECT rect;
	GetClientRect(&rect);
	SetStretchBltMode(dc.m_hDC, BLACKONWHITE);
	capturedSc.StretchBlt(dc.m_hDC, rect);
	::InvalidateRect(m_hWnd, NULL, TRUE);
*/
}
