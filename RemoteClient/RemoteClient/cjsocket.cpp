#include "stdafx.h"
#include "cjsocket.h"


cjSocket::cjSocket()
{
	WSAStartup(MAKEWORD(2, 2), &wsa);
}


cjSocket::~cjSocket()
{
}

void cjSocket::err_quit(char* msg){
	LPVOID lpMsgBuf;
	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, WSAGetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&lpMsgBuf, 0, NULL);

	MessageBox(NULL, (LPCTSTR)lpMsgBuf, (LPCWSTR)msg, MB_ICONERROR);

	LocalFree(lpMsgBuf);

	exit(-1);
}

void cjSocket::err_display(char* msg){
	LPVOID lpMsgBuf;
	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, WSAGetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&lpMsgBuf, 0, NULL);

	printf("[%s] %s", msg, (LPCTSTR)lpMsgBuf);

	LocalFree(lpMsgBuf);
}

int  cjSocket::BindUdpSock(int port) {
	udp_sock = new SOCKET;
	ZeroMemory(&my_sockAddr, sizeof(my_sockAddr));
	my_sockAddr.sin_family = AF_INET;
	my_sockAddr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	my_sockAddr.sin_port = htons(port);

	return !(bind(*udp_sock, (sockaddr*)&my_sockAddr, sizeof(my_sockAddr)));
}

void cjSocket::GetCurTime() {
	GetLocalTime(&systime);

	cur_time.Format(_T("%d%d%d"), systime.wMinute, systime.wSecond, systime.wMilliseconds);
}