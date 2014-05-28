#include "sockFunc.h"

int ReadRegLog(char *_type, char *_tar)
{
	FILE *RegFile;
	char Line[64];
	char *find = 0;
	char path[16];

	strcpy(path, "Reg.log");
	
	RegFile = fopen(path, "r");
	if (RegFile == NULL) cout << "No Such Path [" << path << "]" << endl;
	
	
	char RegService[16];
	char ReqService[16];
	char IP_Port_List[32 * 1024];
	int elementCount = 0;
	int pivot = 0;
	int sePivot = 0;
	int arrow = 0;
	int seArrow = 0;
	
	srand(time(NULL));
	memcpy(&ReqService, _type, strlen(_type) + 1);
	
	while(fgets(Line, 64 - 1, RegFile))
	{
		if((find = strrchr(Line, '\n')))
		{
			*find = '\0';
			sePivot = 0;
			seArrow = 0;
			while(1)
			{
				if(Line[sePivot] == '\t')
				{
					memcpy(&RegService[seArrow], "\0", 1);
					sePivot++;
					
					if(strcmp(RegService, _type) == 0)
					{
						while(1)
						{
							if(Line[sePivot] == '\0')
							{
								memcpy(&IP_Port_List[arrow], &Line[sePivot], 1);
								arrow++;
								elementCount++;
								break;
							}
							else								
								memcpy(&IP_Port_List[arrow], &Line[sePivot], 1);
							sePivot++;
							arrow++;
						}
					}
					break;
				}
				else
				{
					memcpy(&RegService[seArrow], &Line[sePivot], 1);
				}
				seArrow++;
				sePivot++;
			}
		}		
	}
	
	int iSecret = 0;
	int cmpNum = 1;
	iSecret = rand() % elementCount + 1;
	
	sePivot = 0;
	seArrow = 0;
			
	while(sePivot < arrow)
	{
		if(IP_Port_List[sePivot] == '\0')
		{
			if(cmpNum == iSecret)
			{
				memcpy(&_tar[seArrow], &IP_Port_List[sePivot], 1);
				break;
			}
			else
			{
				sePivot++;
				seArrow = 0;
				cmpNum++;
			}
		}
		else
		{
			memcpy(&_tar[seArrow], &IP_Port_List[sePivot], 1);
		}
		seArrow++;
		sePivot++;
	}
	
	
	fclose(RegFile);
	return 1;
}

void TCPServerSocket(SockInfo &_sock)
{
	//struct sockaddr_in dest;
	
	//--Create Socket--//
	_sock.sockfd = socket(PF_INET, SOCK_STREAM, 0);
	
	//--Initailize structure Destination--//
	bzero(&_sock.dest, sizeof(_sock.dest));
	_sock.dest.sin_family = AF_INET;
	_sock.dest.sin_port = htons(_sock.portNum);
	/*
	cout << "SERVER : "<< htons(_sock.portNum) 
	<< ", Origial : " << ntohs(htons(_sock.portNum)) << endl;
	*/
	//--This line is different from client--//
	_sock.dest.sin_addr.s_addr = INADDR_ANY;
	
	//--Assign a port number to socket--//
	bind(_sock.sockfd, (struct sockaddr*)&_sock.dest, sizeof(_sock.dest));
	
	//--Make it listen to socket with max 20 connections--//
	listen(_sock.sockfd, 20);
	
}

void TCPClientSocket(SockInfo &_sock, char *_addr)
{	
	//--Create Socket--//
	_sock.sockfd = socket(PF_INET, SOCK_STREAM, 0);

	//--Initailize structure Destination--//
	bzero(&_sock.dest, sizeof(_sock.dest));
	_sock.dest.sin_family = AF_INET;
	_sock.dest.sin_port = htons(_sock.portNum);
	//--This line is different from client--//
	_sock.dest.sin_addr.s_addr = inet_addr(_addr);
	//dest.sin_addr.s_addr = inet_addr("120.126.17.110");
	//inet_aton("127.0.0.1", &dest.sin_addr);
	
}

int Accept(SockInfo &_sock)
{
	socklen_t alen;
  alen = sizeof(_sock.adr);
  
	return accept(_sock.sockfd,(struct sockaddr*)&_sock.adr, &alen);
	
}

void SendMessage(SockInfo &_sock, string _service)
{
	struct sockaddr_in client_addr;
	
	if(_service == "Server")
		send(_sock.clientfd, _sock.sendBuff, sizeof(_sock.sendBuff), 0);
	else if(_service == "Client")
		send(_sock.sockfd, _sock.sendBuff, sizeof(_sock.sendBuff), 0);
		
}

void RecvMessage(SockInfo &_sock, string _service)
{
	struct sockaddr_in client_addr;
	
	if(_service == "Server")
		_sock.byteRecv = recv(_sock.clientfd, _sock.recvBuff, sizeof(_sock.recvBuff), 0);
	else if(_service == "Client")
		_sock.byteRecv = recv(_sock.sockfd, _sock.recvBuff, sizeof(_sock.recvBuff), 0);
	
}

int Connect(SockInfo &_sock)
{	
	//--Connecting to server--//
	return connect(_sock.sockfd, (struct sockaddr*)&_sock.dest, sizeof(_sock.dest));
	
}

int RequestParse(SockInfo &_sock, char *_tar)
{	
	char recvCache[CommonBuffSize];
	bzero(&recvCache, sizeof(recvCache));
	char type[4];
	int pivot = 0, arrow = 0, sig = 0;
	
	while(1)
	{
		if(_sock.recvBuff[pivot] == '\t')	
		{
			memcpy(&type[arrow], "\0", 1);
			arrow = 0;
			pivot++;
			break;
		}
		else	
		{
			type[arrow] = _sock.recvBuff[pivot];
			arrow++;
		}
		pivot++;
	}
	
	if(strcmp(type, "reg") == 0)			//Register status
	{
		FILE *RegFile;
		char path[CommonBuffSize];
		char regInfo[CommonBuffSize];
		int offset = 0;
		
		bzero(&path, sizeof(path));
		bzero(&regInfo, sizeof(regInfo));
		
		strcpy(path, "Reg.log");
		RegFile = fopen(path, "a");
		if (RegFile == NULL) cout << "No such file or path.[" << path << "]" << endl;
		
		fseek(RegFile, 0, SEEK_END);
		offset = ftell(RegFile);
		fseek(RegFile, offset, SEEK_SET);		
		
		while(1)			//Parse Message : <Service>\t<Prot>\0
		{
			if(_sock.recvBuff[pivot] == '\t')	
			{				
				memcpy(&recvCache[arrow], "\0", 1);
			}
			else if(_sock.recvBuff[pivot] == '\0')
			{							
				memcpy(&recvCache[arrow], "\0", 1);
				arrow = 0;
				pivot = 0;
				cout << recvCache << endl;
				break;
			}
			else	
			{
				recvCache[arrow] = _sock.recvBuff[pivot];
			}
			arrow++;
			pivot++;
		}
		
		//Register Information Form "<Service>\t<Port>\t<IP>\n"//
		memcpy(&regInfo[pivot], &recvCache[arrow], strlen(recvCache));
		pivot += strlen(recvCache);
		arrow += strlen(recvCache) + 1;
		memcpy(&regInfo[pivot], "\t", 1);
		pivot += 1;
		
		memcpy(&regInfo[pivot], inet_ntoa(_sock.adr.sin_addr), strlen(inet_ntoa(_sock.adr.sin_addr)));
		pivot += strlen(inet_ntoa(_sock.adr.sin_addr));
		memcpy(&regInfo[pivot], "\t", 1);
		pivot += 1;
		
		memcpy(&regInfo[pivot], &recvCache[arrow], strlen(&recvCache[arrow]));
		pivot += strlen(&recvCache[arrow]);		
		memcpy(&regInfo[pivot], "\n", 1);
		pivot += 1;
		
		fwrite(regInfo, 1, strlen(regInfo), RegFile);
		
		fclose(RegFile);
		
	}
	else if(strcmp(type, "req") == 0)			//Requeset Service		return [ReqMessIP\tPath\tRegFileIP\tPort\0]
	{		
		while(1)
		{
			if(_sock.recvBuff[pivot] == '\t')	
			{
				memcpy(&recvCache[arrow], "\0", 1);
				arrow = 0;
				pivot++;
				break;
			}
			else	
			{
				recvCache[arrow] = _sock.recvBuff[pivot];
				arrow++;
			}
			pivot++;
		}
		//cout << recvCache << endl;
		
		char IP_Port_List[32];			//<ServiceIP> <Port>		
		ReadRegLog(recvCache, IP_Port_List);
		
		cout << "Register Infomation : " << IP_Port_List << endl;
		
		if(strcmp(recvCache, "HTTPCRAWLER") == 0)
		{
			memcpy(&_tar[arrow], inet_ntoa(_sock.adr.sin_addr), strlen(inet_ntoa(_sock.adr.sin_addr)));
			arrow += strlen(inet_ntoa(_sock.adr.sin_addr));
			memcpy(&_tar[arrow], "\t", 1);
			arrow += 1;
			
			while(1)
			{
				if(_sock.recvBuff[pivot] == '\0')
				{
					memcpy(&_tar[arrow], "\t", 1);
					arrow++;
					break;
				}
				else
				{
					_tar[arrow] = _sock.recvBuff[pivot];
				}
				arrow++;
				pivot++;					
			}
			memcpy(&_tar[arrow], IP_Port_List, strlen(IP_Port_List) + 1);
			
			//cout << "Path : [" << arrow << "] "<< _tar << endl;
		}
		else if(strcmp(recvCache, "HTTPPARSER") == 0)
		{
			memcpy(&_tar[arrow], inet_ntoa(_sock.adr.sin_addr), strlen(inet_ntoa(_sock.adr.sin_addr)));
			arrow += strlen(inet_ntoa(_sock.adr.sin_addr));
			memcpy(&_tar[arrow], "\t", 1);
			arrow += 1;
			
			while(1)
			{
				if(_sock.recvBuff[pivot] == '\0')
				{
					memcpy(&_tar[arrow], "\t", 1);
					arrow++;
					break;
				}
				else
				{
					_tar[arrow] = _sock.recvBuff[pivot];
				}
				arrow++;
				pivot++;					
			}
			memcpy(&_tar[arrow], IP_Port_List, strlen(IP_Port_List) + 1);
		}
		else if(strcmp(recvCache, "URLFILTER") == 0)
		{
			memcpy(&_tar[arrow], inet_ntoa(_sock.adr.sin_addr), strlen(inet_ntoa(_sock.adr.sin_addr)));
			arrow += strlen(inet_ntoa(_sock.adr.sin_addr));
			memcpy(&_tar[arrow], "\t", 1);
			arrow += 1;
			
			while(1)
			{
				if(_sock.recvBuff[pivot] == '\0')
				{
					memcpy(&_tar[arrow], "\t", 1);
					arrow++;
					break;
				}
				else
				{
					_tar[arrow] = _sock.recvBuff[pivot];
				}
				arrow++;
				pivot++;					
			}
			memcpy(&_tar[arrow], IP_Port_List, strlen(IP_Port_List) + 1);
		}
		else if(strcmp(recvCache, "URLPOOLMANAGER") == 0)
		{
			memcpy(&_tar[arrow], inet_ntoa(_sock.adr.sin_addr), strlen(inet_ntoa(_sock.adr.sin_addr)));
			arrow += strlen(inet_ntoa(_sock.adr.sin_addr));
			memcpy(&_tar[arrow], "\t", 1);
			arrow += 1;
			
			while(1)
			{
				if(_sock.recvBuff[pivot] == '\0')
				{
					memcpy(&_tar[arrow], "\t", 1);
					arrow++;
					break;
				}
				else
				{
					_tar[arrow] = _sock.recvBuff[pivot];
				}
				arrow++;
				pivot++;					
			}
			memcpy(&_tar[arrow], IP_Port_List, strlen(IP_Port_List) + 1);
		}
		else if(strcmp(recvCache, "DNSLOOKUP") == 0)
		{
		}	
		else if(strcmp(recvCache, "STORAGE") == 0)
		{
		}
	}
	else if(strcmp(type, "res") == 0)			//Response request
	{		
		
	}
	
	return 1;
}
