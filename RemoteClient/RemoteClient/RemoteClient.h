
// RemoteClient.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CRemoteClientApp:
// �� Ŭ������ ������ ���ؼ��� RemoteClient.cpp�� �����Ͻʽÿ�.
//

class CRemoteClientApp : public CWinApp
{
public:
	CRemoteClientApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CRemoteClientApp theApp;