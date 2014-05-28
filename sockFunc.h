#ifndef SOCKET_H 
#define SOCKET_H  

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <netinet/in.h>
#include <string.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <iostream>
#include "globalFunc.h"

#define SendBuffSize 128
#define RecvBuffSize 128
#define CommonBuffSize 128

using namespace std;

struct SockInfo
{
	int sockfd;
	int clientfd;	
	int byteRecv;
	int portNum;
	
	char sendBuff[SendBuffSize];	
	char recvBuff[RecvBuffSize];
	
	struct sockaddr_in dest;
	struct sockaddr_in adr;
};

void TCPServerSocket(SockInfo &_sock);
void TCPClientSocket(SockInfo &_sock, char *_addr);
void SendMessage(SockInfo &_sock, string _service);
int Connect(SockInfo &_sock);
void RecvMessage(SockInfo &_sock, string _service);
int Accept(SockInfo &_sock);
int RequestParse(SockInfo &_sock, char *_tar);
int ReadRegLog(char *_tar, char *_type);

#endif
