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

public:
	enum {
		MESSAGETRANSBUF_SIZE = 100,
		IMAGETRANSBUF_SIZE = 1008,
		TIMESTAMP_SIZE = 7,
		DATATYPE_SIZE = 1,
		HEADER_SIZE = 8,
		IMAGEDATA_SIZE = IMAGETRANSBUF_SIZE - HEADER_SIZE,
		IMAGE_TYPE = 1,
		MESSAGE_TYPE = 2,
		IMAGESIZE_TYPE= 3
	};

	int retval;
	int addrLen;
	WSADATA wsa;
	SOCKET* udp_sock;
	SOCKADDR_IN my_sockAddr;
	SOCKADDR_IN other_sockAddr;
	SYSTEMTIME systime;
	CString cur_time;
	int temp_time;
	char messageBuf[MESSAGETRANSBUF_SIZE] = { 0, };
	char ImageBuf[IMAGETRANSBUF_SIZE] = { 0, };

	int BindUdpSock(int port);
	void RegisterOtherSock(char* ip, int port);
	void GetCurTime();
	void TransMessage(char *pBuffer);//안짰음
	void TransImage(char *source, int dataSize);
	void InsertTimeStamp(char* pBuffer);
	void PutImage(char* source, char* destination, int index);
	void PutImageSize(char* pBuffer, int size);
};
// TODO: 소켓 보내는 함수 만들어야함. 그다음은 우선순위 큐에 넣기