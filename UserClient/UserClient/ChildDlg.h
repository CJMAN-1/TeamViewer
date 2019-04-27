#pragma once


// ChildDlg 대화 상자입니다.

class ChildDlg : public CDialogEx
{
	DECLARE_DYNAMIC(ChildDlg)

public:
	ChildDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~ChildDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CHILDDLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
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
