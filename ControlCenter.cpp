/*
	Service Type Name :
		1.HTTPCRAWLER
		2.HTTPPARSER
		3.URLFILTER
		4.URLPOOLMANAGER
		5.DNSLOOKUP
		6.STORAGE
	
	Socket Message Form :
		Register message : <Message Type(1.request 2.register 3.response)> <Srevice> <IP>
		Request message : <Message Type(1.request 2.register 3.response)> <Request Service> <FilePath>
		Response message : <File Path>
*/
#include <curl.h>
#include <queue>
#include <dirent.h>		
#include <string>	
#include <pthread.h>

#include "globalFunc.h"
#include "sockFunc.h"

void Initial(SockInfo &Sock)
{
	Sock.portNum = 3579;
	Sock.sendBuff[SendBuffSize] = '\0';
	Sock.recvBuff[RecvBuffSize] = '\0';	
}

int main(int argc, char **argv)
{	
	SockInfo Sock;
	
	Initial(Sock);
	TCPServerSocket(Sock);
	
	while(true)
	{
		cout << "<------------------------------------------------>\n" << "Start listen...\n";
		
		Sock.clientfd = 0;
		char reqMessage[CommonBuffSize];
		
		bzero(&Sock.sendBuff, sizeof(Sock.sendBuff));
		bzero(&Sock.recvBuff, sizeof(Sock.recvBuff));
		bzero(&reqMessage, sizeof(reqMessage));
		
		/*Indinity loop ( Accepting connettion from client forever, Wait and Accept connection
			it will be blocked until there are connections from client*/		
		Sock.clientfd = Accept(Sock);
		
		//Sock.sendBuff = "HELLO Client ! ";
		strcpy(Sock.sendBuff, "Hello Client, recived your request!");
		
		SendMessage(Sock, "Server");
		RecvMessage(Sock, "Server");
		
		cout << "Recive Message : " << Sock.recvBuff << endl;
		
		/* For Server2 Test
		int tmpKey = 0, stop = 0;
		cout << "Recive Message : ";
		while(1)
		{
			if(Sock.recvBuff[tmpKey] == '\0')
			{
				if(stop == 1)
				{
					cout << endl;
					break;
				}
				else
					cout << "\t";
				stop++;
			}
			else
				cout << Sock.recvBuff[tmpKey];
			tmpKey++;
		}
		*/
		
		if(Sock.recvBuff != " ")
		{
			RequestParse(Sock, reqMessage);
			
			cout << "Parse Message : " << reqMessage << endl;
		}
		else
		{
			bzero(&reqMessage, sizeof(reqMessage));
		}
		close(Sock.clientfd);
		
		cout << "Close connection from service.\n" 
					<< "<------------------------------------------------>\n\n";
			
		if(Sock.recvBuff[2] != 'g')
		{
			int count = 0, e = 0;
			char ReqSevIP[16];			
			char ReqScpPath[CommonBuffSize];
			char RegFileIP[16];
			char RegFilePort[10];
			
			char *pch;
			
		  pch = strtok (reqMessage,"\t\0");
		  while (pch != NULL)
		  {
		    //printf ("%s\n", pch);
		    if(e == 0)
		    {
		    	strcpy(ReqSevIP, pch);
		    	memcpy(&ReqSevIP[strlen(ReqSevIP) + 1], "\0", 1);
		    }
		    else if(e == 1)
		    {
		    	strcpy(ReqScpPath, pch);
		    	memcpy(&ReqScpPath[strlen(ReqScpPath) + 1], "\0", 1);
		    }
		    else if(e == 2)
		    {
		    	strcpy(RegFileIP, pch);
		    	memcpy(&RegFileIP[strlen(RegFileIP) + 1], "\0", 1);
		    }
		    else
		    {
		    	strcpy(RegFilePort, pch);
		    	memcpy(&RegFilePort[strlen(RegFilePort) + 1], "\0", 1);
		    }
		    
		    pch = strtok (NULL, "\t\0");
		    e++;
  		}
			
			//cout << "ReqSevIP [" << strlen(ReqSevIP) << "]: " << ReqSevIP << endl;
			//cout << "ReqScpPath [" << strlen(ReqScpPath) << "]: " << ReqScpPath << endl;
			//cout << "RegFileIP [" << strlen(RegFileIP) << "]: " << RegFileIP << endl;
			//cout << "RegFilePort [" << strlen(RegFilePort) << "]: " << RegFilePort << endl;

			SockInfo Sock_2;
			char addr[16];
			
			memcpy(addr, &RegFileIP, strlen(RegFileIP) + 1);
			Sock_2.portNum = atoi(RegFilePort);						
			Sock_2.sendBuff[SendBuffSize] = '\0';
			Sock_2.recvBuff[RecvBuffSize] = '\0';
			
			bzero(&Sock_2.sendBuff, sizeof(Sock_2.sendBuff));
			bzero(&Sock_2.recvBuff, sizeof(Sock_2.recvBuff));
		
			TCPClientSocket(Sock_2, addr);
			
			int index = 0;
			
			memcpy(&Sock_2.sendBuff[index], ReqSevIP, strlen(ReqSevIP) + 1);
			index += strlen(ReqSevIP) + 1;
			memcpy(&Sock_2.sendBuff[index], ReqScpPath, strlen(ReqScpPath) + 1);
			index	+= strlen(ReqScpPath) + 1;
			
			cout << "Length of send message : "<< index << endl;
			
			if(Connect(Sock_2) == 0)
			{
				RecvMessage(Sock_2, "Client");
				SendMessage(Sock_2, "Client");
			}
			else
			{
				cout << "Fail to establish connection." << endl;				
			}
			
			close(Sock_2.sockfd);
		}
		
	}
	
	
}
