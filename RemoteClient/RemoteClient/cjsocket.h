#pragma once
#include "stdafx.h"
class cjSocket
{
private:
	void err_quit(char* msg);
	void err_display(char* msg);

public:
	cjSocket();
	~cjSocket();

protected:
	enum {
		BUFSIZE = 100
	};
	int retval;
	WSADATA wsa;
	SOCKET* udp_sock;
	SOCKADDR_IN my_sockAddr;
	SOCKADDR_IN* other_sockAddr;
	SYSTEMTIME systime;
	CString cur_time;

	char buf[BUFSIZE] = { 0, };

	/*������ port��ȣ�� udp ������ ����� bind�Ѵ�. bind�� �����ϸ� 0�� ��ȯ�Ѵ�.*/
	int BindUdpSock(int port);
	/*	���� �ð��� ��,��,�и������� ������ �缭 ������� cur_time�� ���ڿ��� �����Ѵ�.*/
	void GetCurTime();
	void recvimage();
};
// TODO: ���� ������ �Լ� ��������. �״����� �켱���� ť�� �ֱ�,
