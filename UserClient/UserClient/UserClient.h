
// UserClient.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.
#include <iostream>
#include <fstream>
using namespace std;

// CUserClientApp:
// �� Ŭ������ ������ ���ؼ��� UserClient.cpp�� �����Ͻʽÿ�.
//

class CUserClientApp : public CWinApp
{
public:
	CUserClientApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CUserClientApp theApp;