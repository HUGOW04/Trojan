#include <winsock2.h>
#include "Config.h"

#pragma comment(lib, "ws2_32.lib")
#pragma warning(disable: 4996)

WSAData wsaData;
WORD DLLVersion = MAKEWORD(2, 2);
SOCKADDR_IN addr;
int sizeofaddr = sizeof(addr);

SOCKADDR_IN Server() {
	if (WSAStartup(DLLVersion, &wsaData) != 0) exit(1);

	addr.sin_addr.S_un.S_addr = inet_addr(IP);
	addr.sin_port = htons(PORT);
	addr.sin_family = AF_INET;
	return addr;
}