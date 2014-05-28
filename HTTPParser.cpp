/*
  Program III :	Parse Info From Header File and Body File
  
    Parse header file and body file which 
  there are required infomation in it. 
*/

#include "urlExtracting.h"
#include "sockFunc.h"
 
int main(int argc, char **argv)
{
	FInfo FILEVAR;
	string tmpBuf[60];
	pid_t parentID, childID;
	char procID[6];
	
	bzero(&procID, sizeof(procID));
	
  parentID = getpid();		
	childID = fork();
  
  if(getpid() == parentID)
	{		
		cout << "ParentID : " << parentID << endl;
		
		SockInfo SockRecv, SockSend;
		
		SockRecv.portNum = atoi(argv[3]);
		SockRecv.sendBuff[SendBuffSize] = '\0';
		SockRecv.recvBuff[RecvBuffSize] = '\0';
		bzero(&SockRecv.sendBuff, sizeof(SockRecv.sendBuff));
		bzero(&SockRecv.recvBuff, sizeof(SockRecv.recvBuff));
		
		SockSend.portNum = atoi(argv[2]);
		SockSend.sendBuff[SendBuffSize] = '\0';
		SockSend.recvBuff[RecvBuffSize] = '\0';
		bzero(&SockSend.sendBuff, sizeof(SockSend.sendBuff));
		bzero(&SockSend.recvBuff, sizeof(SockSend.recvBuff));
		
		char addr[16];
		memcpy(addr, argv[1], strlen(argv[1]) + 1);
		
		TCPServerSocket(SockRecv);
		TCPClientSocket(SockSend, addr);			
		
		int index = 0;
		
		memcpy(&SockSend.sendBuff[index], "reg", 3);
		index += 3;
		memcpy(&SockSend.sendBuff[index], "\t", 1);
		index += 1;
		memcpy(&SockSend.sendBuff[index], "HTTPPARSER", 10);
		index += 10;
		memcpy(&SockSend.sendBuff[index], "\t", 1);
		index += 1;
		memcpy(&SockSend.sendBuff[index], argv[3], strlen(argv[3]));
		index += strlen(argv[3]);
		memcpy(&SockSend.sendBuff[index], "\0", 1);
		index += 1;	
				
		int res = Connect(SockSend);
		
		if(res == 0)
		{
				RecvMessage(SockSend, "Client");
		}
		else
		{
			cout << "Connection falure!" << endl;
			exit(1);
		}
		SendMessage(SockSend, "Client");
		
		close(SockSend.sockfd);
		
		while(true)
		{
			cout << "<------------------------------------------------>\n" << "Start listen...\n";
		
			SockRecv.clientfd = Accept(SockRecv);
			strcpy(SockRecv.sendBuff, "Hello, this is Service HTTPPARSER! Recived your request!");
			
			SendMessage(SockRecv, "Server");
			RecvMessage(SockRecv, "Server");
							
			int tmpKey = 0, stop = 0;
			cout << "Recive Message : ";
			
			while(1)
			{
				if(SockRecv.recvBuff[tmpKey] == '\0')
				{
					if(stop == 1)
					{
						cout << endl;
						break;
					}
					else
					{
						cout << "\t";
					}
					stop++;
				}
				else
					cout << SockRecv.recvBuff[tmpKey];
				tmpKey++;
			}
			close(SockRecv.clientfd);
			
			
			//SCP FILES//
			char scpHPath[1024];
			char scpCPath[1024];
			int begH = 0, begC = 0, endH = 0, endC = 0, pivotH = 0, pivotC = 0;
			
			bzero(&scpHPath, sizeof(scpHPath));	
			bzero(&scpCPath, sizeof(scpCPath));			
			
			memcpy(&scpHPath[pivotH], "scp xboxhigh@", 13);
			pivotH += 13;
			memcpy(&scpHPath[pivotH], &SockRecv.recvBuff[begH], strlen(&SockRecv.recvBuff[begH]));
			pivotH += strlen(&SockRecv.recvBuff[begH]);
			endH = strlen(SockRecv.recvBuff) + 1;
			memcpy(&scpHPath[pivotH], ":", 1);
			pivotH += 1;
			
			memcpy(&scpCPath[pivotC], "scp xboxhigh@", 13);
			pivotC += 13;
			memcpy(&scpCPath[pivotC], &SockRecv.recvBuff[begC], strlen(&SockRecv.recvBuff[begC]));
			pivotC += strlen(&SockRecv.recvBuff[begC]);
			endC = strlen(SockRecv.recvBuff) + 1;
			memcpy(&scpCPath[pivotC], ":", 1);
			pivotC += 1;
			
			memcpy(&scpHPath[pivotH], "/data2/xboxhigh/_gatheringFiles/hFile/Header.", 45);
			pivotH += 45;
			memcpy(&scpHPath[pivotH], &SockRecv.recvBuff[endH], strlen(&SockRecv.recvBuff[endH]));
			pivotH += strlen(&SockRecv.recvBuff[endH]);
			memcpy(&scpHPath[pivotH], " ", 1);
			pivotH += 1;
			memcpy(&scpHPath[pivotH], "/data2/xboxhigh/_gatheringFiles/hFile/Header.", 45);
			pivotH += 45;
			memcpy(&scpHPath[pivotH], &SockRecv.recvBuff[endH], strlen(&SockRecv.recvBuff[endH]));
			pivotH += strlen(&SockRecv.recvBuff[endH]);
			
			memcpy(procID, &SockRecv.recvBuff[endH], strlen(&SockRecv.recvBuff[endH]));
			
			memcpy(&scpCPath[pivotC], "/data2/xboxhigh/_gatheringFiles/bFile/Content.", 46);
			pivotC += 46;
			memcpy(&scpCPath[pivotC], &SockRecv.recvBuff[endC], strlen(&SockRecv.recvBuff[endC]));
			pivotC += strlen(&SockRecv.recvBuff[endC]);
			memcpy(&scpCPath[pivotC], " ", 1);
			pivotC += 1;
			memcpy(&scpCPath[pivotC], "/data2/xboxhigh/_gatheringFiles/bFile/Content.", 46);
			pivotC += 46;
			memcpy(&scpCPath[pivotC], &SockRecv.recvBuff[endC], strlen(&SockRecv.recvBuff[endC]));
			pivotC += strlen(&SockRecv.recvBuff[endC]);
			
			//cout << "beg : " << beg << ", end : " << end << endl;
			//cout << scpHPath << endl;
			//cout << scpCPath << endl;
			
			system(scpHPath);
			system(scpCPath);
			
			cout << "Close connection from service.\n" 
						<< "<------------------------------------------------>\n\n";
						
			childID = fork();
			if(getpid() != parentID)
				break;

		}
	}
	
	if(strlen(procID) != 0)
	{
		cout << "Start parse content...\n";
		
		char headerFileName[256];
		char contentFileName[256];
		char extractLinksFileName[256];		
		
		bzero(&headerFileName, sizeof(headerFileName));
		bzero(&contentFileName, sizeof(contentFileName));
		bzero(&extractLinksFileName, sizeof(extractLinksFileName));
		
		strcat(headerFileName, "/data2/xboxhigh/_gatheringFiles/hFile/Header.");
		strcat(headerFileName, procID);
		strcat(contentFileName, "/data2/xboxhigh/_gatheringFiles/bFile/Content.");
		strcat(contentFileName, procID);
		strcat(extractLinksFileName, "/data2/xboxhigh/_gatheringFiles/xFile/extractLinks.");
		strcat(extractLinksFileName, procID);
		
		FILEVAR.Header = fopen(headerFileName, "r");
		if(FILEVAR.Header == NULL)
			cout << "No Such Path [" << headerFileName << "]\n";
		else
		{
			FILEVAR.Content = fopen(contentFileName, "rb");
			if(FILEVAR.Content == NULL) 
				cout << "No Such Path [" << contentFileName << "]\n";
			else
			{
				FILEVAR.ExLinks = fopen(extractLinksFileName, "w+");
				
				extractHeaderData(&FILEVAR);
				
				fclose(FILEVAR.Content);
			  fclose(FILEVAR.Header);
			  fclose(FILEVAR.ExLinks);	
			}
		}
		cout << "Finish Parsing !\n";
		
		SockInfo SockMess;
			
		SockMess.portNum = 3579;
		SockMess.sendBuff[SendBuffSize] = '\0';
		SockMess.recvBuff[RecvBuffSize] = '\0';
		bzero(&SockMess.sendBuff, sizeof(SockMess.sendBuff));
		bzero(&SockMess.recvBuff, sizeof(SockMess.recvBuff));
		
		char addr[16];
		memcpy(addr, "120.126.17.109", 15);
		TCPClientSocket(SockMess, addr);
		
		int index = 0;
		
		cout << procID << endl;
		memcpy(&SockMess.sendBuff[index], "req", 3);
		index += 3;
		memcpy(&SockMess.sendBuff[index], "\t", 1);
		index += 1;
		memcpy(&SockMess.sendBuff[index], "URLFILTER", 9);
		index += 9;
		memcpy(&SockMess.sendBuff[index], "\t", 1);
		index += 1;
		memcpy(&SockMess.sendBuff[index], procID, strlen(procID));
		index += strlen(procID);
		memcpy(&SockMess.sendBuff[index], "\0", 1);
		index += 1;	
				
		int resl = Connect(SockMess);
		
		if(resl == 0)
		{
				RecvMessage(SockMess, "Client");
		}
		else
		{
				cout << "Connection falure!" << endl;
				exit(1);
		}
		SendMessage(SockMess, "Client");
			
		close(SockMess.sockfd);
		
		exit(0);
	}
	return 0;
}
