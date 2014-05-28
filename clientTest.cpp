/*
	Service Type Name :
		1.HTTPCRAWL
		2.HTTPPARSER
		3.URLFILTER
		4.URLPOOLLIST
		5.DNSLOOKUP
		6.STORAGE

*/
#include <curl.h>
#include <queue>
#include <dirent.h>		
#include <string>	
#include <pthread.h>

#include "globalFunc.h"
#include "sockFunc.h"

int main(int argc, char **argv)
{	
	SockInfo Sock;
	int index = 0;
	char command[4];
	command[3] = '\0';
	
	if(argc < 4 || argc > 5)
	{
		printf("%s <Command Type> <Target Address> <Target Port> <Self Port>\n", argv[0]);
    exit(1);
	}
	char addr[16];
	
	strcpy(command, argv[1]);	
	memcpy(addr, argv[2], strlen(argv[2]) + 1);
	//strcpy(Sock.addr, argv[2]);
	Sock.portNum = atoi(argv[3]);
	
	Sock.sendBuff[SendBuffSize - 1] = '\0';
	Sock.recvBuff[RecvBuffSize - 1] = '\0';
	
	bzero(&Sock.sendBuff, sizeof(Sock.sendBuff));		
	bzero(&Sock.recvBuff, sizeof(Sock.recvBuff));
	//cout << command << "\t[" << addr << "]\t" << Sock.portNum << endl;
	
	
	TCPClientSocket(Sock, addr);
	
	memcpy(&Sock.sendBuff[index], command, strlen(command));
	index += strlen(command);
	memcpy(&Sock.sendBuff[index], "\t", 1);
	index += 1;
	memcpy(&Sock.sendBuff[index], "URLPOOLMANAGER", 14);
	index += 14;
	memcpy(&Sock.sendBuff[index], "\t", 1);
	index += 1;
	/*
	memcpy(&Sock.sendBuff[index], argv[4], 4);
	index += strlen(argv[4]);
	memcpy(&Sock.sendBuff[index], "\0", 1);
	index += 1;	
	
	memcpy(&Sock.sendBuff[index], "/data2/xboxhigh/_gatheringFiles/sFile/UniqueLinks", 49);
	index += 49;
	memcpy(&Sock.sendBuff[index], "\0", 1);
	index += 1;	
	*/
	
	memcpy(&Sock.sendBuff[index], "75665", 5);
	index += 5;
	memcpy(&Sock.sendBuff[index], "\0", 1);
	index += 1;	
	
	int res = Connect(Sock);
	
	if(res == 0)
		RecvMessage(Sock, "Client");
	else
	{
		cout << "Connection falure!" << endl;
		exit(1);
	}
	cout << Sock.recvBuff << endl;
	
	SendMessage(Sock, "Client");
	
	close(Sock.sockfd);
	
}
