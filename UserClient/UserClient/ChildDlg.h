#pragma once


// ChildDlg ��ȭ �����Դϴ�.

class ChildDlg : public CDialogEx
{
	DECLARE_DYNAMIC(ChildDlg)

public:
	ChildDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~ChildDlg();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CHILDDLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.
	enum {
		cx_space = 7,
		cy_space = 35
	};
	
	int cx;
	int cy;
	CImage capturedSc;
	CString path_capturedSc;

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
};
