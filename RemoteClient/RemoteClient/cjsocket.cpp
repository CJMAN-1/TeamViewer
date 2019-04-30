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

/*������ port��ȣ�� udp ������ ����� bind�Ѵ�. bind�� �����ϸ� 0�� ��ȯ�Ѵ�.*/
int  cjSocket::BindUdpSock(int port) {
	udp_sock = new SOCKET;
	*udp_sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	ZeroMemory(&my_sockAddr, sizeof(my_sockAddr));
	my_sockAddr.sin_family = AF_INET;
	my_sockAddr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	my_sockAddr.sin_port = htons(port);

	return !(bind(*udp_sock, (sockaddr*)&my_sockAddr, sizeof(my_sockAddr)));
}

/*other_sockAddr�� �ٲ㼭 ��� ��븦 �ٲ۴�.*/
void cjSocket::RegisterOtherSock(char* ip, int port) {
	ZeroMemory(&other_sockAddr, sizeof(other_sockAddr));
	other_sockAddr.sin_family = AF_INET;
	other_sockAddr.sin_addr.S_un.S_addr = inet_addr(ip);
	other_sockAddr.sin_port = htons(port);
}

/*	���� �ð��� ��,��,�и������� ������ �缭 ������� cur_time�� ���ڿ��� �����Ѵ�.*/
void cjSocket::GetCurTime() {
	GetLocalTime(&systime);

	cur_time.Format(_T("%d%d%d"), systime.wMinute, systime.wSecond, systime.wMilliseconds);
}

void cjSocket::TransMessage(char *pBuffer) {
	//TODO : Ÿ�ӽ����� �� ��Ŷ ������, ��� ���α׷� ��� �����ϳ�???
	
}

//�̹��� ������ �����Ѵ�.
void cjSocket::TransImage(char *source, int dataSize) {
	PutImageSize(ImageBuf, dataSize);
	sendto(*udp_sock, ImageBuf, IMAGETRANSBUF_SIZE, 0, (sockaddr*)&other_sockAddr, sizeof(other_sockAddr));



	for (int i = 0; i < (dataSize / IMAGEDATA_SIZE) + 1; i++) {
		PutImage(source, ImageBuf, i);
		sendto(*udp_sock, ImageBuf, IMAGETRANSBUF_SIZE, 0, (sockaddr*)&other_sockAddr, sizeof(other_sockAddr));
	}
}

//���� ���ۿ� Ÿ�� �������� ��´�.
void cjSocket::InsertTimeStamp(char* pBuffer) {
	GetCurTime();
	for (int i = 0; i < TIMESTAMP_SIZE; i++) {
		pBuffer[i] = cur_time[i];
	}
}

void cjSocket::PutImage(char* source, char* destination, int index) {
	InsertTimeStamp(destination);
	destination[TIMESTAMP_SIZE] = IMAGE_TYPE;
	if (index >= 0) {
		for (int i = 0; i < IMAGEDATA_SIZE; i++) {
			destination[HEADER_SIZE + i] = source[index*IMAGEDATA_SIZE + i];
		}
	}
}

void cjSocket::PutImageSize(char* pBuffer, int size) {
	InsertTimeStamp(pBuffer);
	pBuffer[TIMESTAMP_SIZE] = IMAGESIZE_TYPE;
	sprintf(pBuffer + HEADER_SIZE, "%d", size);
}