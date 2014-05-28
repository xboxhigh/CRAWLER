#include "globalFunc.h"
#include "sockFunc.h"
#include "urlListManage.h"

int main(int argc, char **argv)
{
	FInfo FILEVAR;
	pid_t parentID, childID;
	char procID[6];
	
	parentID = getpid();
		
	childID = fork();
	
	if(getpid() == parentID)
	{
		cout << "ParentID : " << parentID << endl;
		
		SockInfo SockRecv, SockSend;
		
		SockRecv.portNum = atoi(argv[3]);		
		SockSend.portNum = atoi(argv[2]);
		
		char addr[16];
		memcpy(addr, argv[1], strlen(argv[1]) + 1);
		
		TCPServerSocket(SockRecv);
		TCPClientSocket(SockSend, addr);			
		
		int index = 0;
		
		memcpy(&SockSend.sendBuff[index], "reg", 3);
		index += 3;
		memcpy(&SockSend.sendBuff[index], "\t", 1);
		index += 1;
		memcpy(&SockSend.sendBuff[index], "URLPOOLMANAGER", 14);
		index += 14;
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
			
			SockSend.sendBuff[SendBuffSize] = '\0';
			SockSend.recvBuff[RecvBuffSize] = '\0';
			bzero(&SockSend.sendBuff, sizeof(SockSend.sendBuff));
			bzero(&SockSend.recvBuff, sizeof(SockSend.recvBuff));
			SockRecv.sendBuff[SendBuffSize] = '\0';
			SockRecv.recvBuff[RecvBuffSize] = '\0';
			bzero(&SockRecv.sendBuff, sizeof(SockRecv.sendBuff));
			bzero(&SockRecv.recvBuff, sizeof(SockRecv.recvBuff));
		
			strcpy(SockRecv.sendBuff, "Hello, this is Service URLPOOLMANAGER! Recived your request!");
			
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
			int begH = 0, endH = 0, pivotH = 0;
			
	
			bzero(&procID, sizeof(procID));
			bzero(&scpHPath, sizeof(scpHPath));	
			
			memcpy(&scpHPath[pivotH], "scp xboxhigh@", 13);
			pivotH += 13;
			memcpy(&scpHPath[pivotH], &SockRecv.recvBuff[begH], strlen(&SockRecv.recvBuff[begH]));
			pivotH += strlen(&SockRecv.recvBuff[begH]);
			endH = strlen(SockRecv.recvBuff) + 1;
			memcpy(&scpHPath[pivotH], ":", 1);
			pivotH += 1;
			
			memcpy(&scpHPath[pivotH], "/data2/xboxhigh/_gatheringFiles/xFile/UniqueLinks.", 50);
			pivotH += 50;
			memcpy(&scpHPath[pivotH], &SockRecv.recvBuff[endH], strlen(&SockRecv.recvBuff[endH]));
			pivotH += strlen(&SockRecv.recvBuff[endH]);
			memcpy(&scpHPath[pivotH], " ", 1);
			pivotH += 1;
			memcpy(&scpHPath[pivotH], "/data2/xboxhigh/_gatheringFiles/sFile/UniqueLinks.", 50);
			pivotH += 50;
			memcpy(&scpHPath[pivotH], &SockRecv.recvBuff[endH], strlen(&SockRecv.recvBuff[endH]));
			pivotH += strlen(&SockRecv.recvBuff[endH]);
			
			memcpy(procID, &SockRecv.recvBuff[endH], strlen(&SockRecv.recvBuff[endH]));
					
			//cout << "beg : " << beg << ", end : " << end << endl;
			//cout << scpHPath << endl;
			//cout << scpCPath << endl;
			
			system(scpHPath);
			
	
			cout << "Close connection from service.\n" 
						<< "<------------------------------------------------>\n\n";
						
			childID = fork();
			if(getpid() != parentID)
				break;						
		}
	}
	
	{
		cout << "Child ID : " << getpid() << endl;
		srand(time(NULL));
		
		char uniqueURLFileName[128];
		char distSeedFileName[128];
		
		bzero(&uniqueURLFileName, sizeof(uniqueURLFileName));
		bzero(&distSeedFileName, sizeof(distSeedFileName));
		
		strcpy(uniqueURLFileName, "/data2/xboxhigh/_gatheringFiles/sFile/UniqueLinks.");
		strcat(uniqueURLFileName, procID);
		memcpy(&uniqueURLFileName[strlen(uniqueURLFileName) + 1], "\0", 1);
		strcpy(distSeedFileName, "/data2/xboxhigh/_gatheringFiles/sFile/URLLists.");
		memcpy(&distSeedFileName[strlen(distSeedFileName) + 1], "\0", 1);
		
		FILEVAR.UniLinks = fopen(uniqueURLFileName, "r");
		
		if(FILEVAR.UniLinks == NULL)
		{
			cout << "No Such Path" << uniqueURLFileName << "]\n";
			exit(0);
		}
		else
		{
			FILEVAR.DistributedSeeds = fopen(distSeedFileName, "w+");
			if (FILEVAR.DistributedSeeds == NULL) cout << "No Such Path" << distSeedFileName << "]\n";
			
			//distributeSeed(FILEVAR);
			
			fclose(FILEVAR.UniLinks);
			fclose(FILEVAR.DistributedSeeds);
			
			char cmd1[256];
			char cmd2[128];
			bzero(&cmd1, sizeof(cmd1));
			bzero(&cmd2, sizeof(cmd2));
			
			strcpy(cmd1, "cp ");
			strcat(cmd1, uniqueURLFileName);
			strcat(cmd1, " ");
			strcat(cmd1, distSeedFileName);
			
			strcpy(cmd2, "rm ");
			strcat(cmd2, uniqueURLFileName);
			
			//cout << "cmd1 : " << cmd1 << endl;
			//cout << "cmd2 : " << cmd2 << endl;
			
			system(cmd1);
			system(cmd2);
			
			int iSecret = 0, index = 0;
			int baseDir = 100;
			char mvPath[128];
			char finalPath[256];
			
			bzero(&mvPath, sizeof(mvPath));
			
			iSecret = 9 + (rand() % (13 - 9 + 1));
					
			strcpy(mvPath, "/data2/xboxhigh/_gatheringFiles/sFile/");
			strcat(mvPath, itoa(baseDir + 9).c_str());
			memcpy(&mvPath[strlen(mvPath) + 1], "\0", 1);
			
			memcpy(&finalPath[index], "mv ", 3);
			index += 3;
			memcpy(&finalPath[index], distSeedFileName, strlen(distSeedFileName));
			index += strlen(distSeedFileName);
			memcpy(&finalPath[index], " ", 1);
			index += 1;
			memcpy(&finalPath[index], mvPath, strlen(mvPath));
			
			//cout << "Final Path : " << finalPath << endl;
			
			system(finalPath);
			
			//Finish distributing URLs, Start send message//		
			SockInfo Sock;
			int sockIndex = 0;
			char addr[16];		
			char command[4];
			command[3] = '\0';
			
			strcpy(command, "req");
			strcpy(addr, "120.126.17.109");
			
			Sock.portNum = 3579;
			
			Sock.sendBuff[SendBuffSize - 1] = '\0';
			Sock.recvBuff[RecvBuffSize - 1] = '\0';
			
			bzero(&Sock.sendBuff, sizeof(Sock.sendBuff));		
			bzero(&Sock.recvBuff, sizeof(Sock.recvBuff));
				
			TCPClientSocket(Sock, addr);
		
			memcpy(&Sock.sendBuff[sockIndex], command, strlen(command));
			sockIndex += strlen(command);
			memcpy(&Sock.sendBuff[sockIndex], "\t", 1);
			sockIndex += 1;
			memcpy(&Sock.sendBuff[sockIndex], "HTTPCRAWLER", 11);
			sockIndex += 11;
			memcpy(&Sock.sendBuff[sockIndex], "\t", 1);
			sockIndex += 1;
			
			memcpy(&Sock.sendBuff[sockIndex], mvPath, strlen(mvPath));
			sockIndex += strlen(mvPath);
			memcpy(&Sock.sendBuff[sockIndex], "/URLLists.", 10);
			sockIndex += 10;
			memcpy(&Sock.sendBuff[sockIndex], "\0", 1);
			sockIndex += 1;	
			
			cout << "Send message : " << Sock.sendBuff << endl;
			int res = Connect(Sock);
			
			if(res == 0)
				RecvMessage(Sock, "Client");
			else
			{
				cout << "Connection falure!" << endl;
				exit(1);
			}
			//cout << Sock.recvBuff << endl;
			
			SendMessage(Sock, "Client");
			
			close(Sock.sockfd);			
		}
		exit(0);
	}
	
	return 0;
}
