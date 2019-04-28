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

	/*설정한 port번호로 udp 소켓을 만들고 bind한다. bind에 실패하면 0을 반환한다.*/
	int BindUdpSock(int port);
	/*	현재 시간을 분,초,밀리세컨드 단위로 재서 멤버변수 cur_time에 문자열로 저장한다.*/
	void GetCurTime();
	void recvimage();
};
// TODO: 소켓 보내는 함수 만들어야함. 그다음은 우선순위 큐에 넣기,
