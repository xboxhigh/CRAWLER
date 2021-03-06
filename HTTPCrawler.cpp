/*
	kill : success return 0
				 fail return -1
*/
#include "pageGathering.h"
#include "globalFunc.h"
#include "sockFunc.h"
#include "urlListManage.h"

char *BUFFER_URL = (char*)malloc(sizeof(char) * MIN_BUFFER_SZIE);
int buffIndex = 0;

int main(int argc, char **argv)
{				
	//Fork 10 children
	pid_t parentID, childID[10], newChildID;
	int childNum = 10;
	
	char procID[6];
	bzero(&procID, sizeof(procID));
	
	parentID = getpid();
	//childID[0] = fork();
	
	signal(SIGUSR1, checkChildLife);
	signal(SIGCHLD, reapchild);
	
	for(int childCount = 0; childCount < childNum; childCount++)
	{
		childID[childCount] = fork();
		if(getpid() != parentID)
			break;
	}
	
	FInfo FILEVAR;
	
	//Read Files//
	char seedsFileName[128];	
	bzero(&seedsFileName, sizeof(seedsFileName));
	strcpy(seedsFileName, "/data2/xboxhigh/_gatheringFiles/pFile/URLLists.");
	
	//Write Files//	
	char headerFileName[128];
	char contentFileName[128];
	bzero(&headerFileName, sizeof(headerFileName));
	bzero(&contentFileName, sizeof(contentFileName));
	strcpy(headerFileName, "/data2/xboxhigh/_gatheringFiles/hFile/Header.");
	strcpy(contentFileName, "/data2/xboxhigh/_gatheringFiles/bFile/Content.");
	
	//Parent's job is ditributing the seed URLs//
	if(getpid() == parentID)	
	{
		cout << "ParentID : " << parentID << endl;
		//seedDistributing(seedsFileName, childID, 10);
		
		fork();
		if(getpid() != parentID)
		{			
			SockInfo SockRecv, SockSend;
			
			//SockRecv.portNum = 3580;
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
			memcpy(&SockSend.sendBuff[index], "HTTPCRAWLER", 11);
			index += 11;
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
				strcpy(SockRecv.sendBuff, "Hello, this is Service HTTPCRAWLER! Recived your request!");
				
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
				char scpPath[1024];
				int beg = 0, end = 0, pivot = 0;
				bzero(&scpPath, sizeof(scpPath));
				
				memcpy(&scpPath[pivot], "scp xboxhigh@", 13);
				pivot += 13;
				memcpy(&scpPath[pivot], &SockRecv.recvBuff[beg], strlen(&SockRecv.recvBuff[beg]));
				pivot += strlen(&SockRecv.recvBuff[beg]);
				end = strlen(SockRecv.recvBuff) + 1;
				memcpy(&scpPath[pivot], ":", 1);
				pivot += 1;
				memcpy(&scpPath[pivot], &SockRecv.recvBuff[end], strlen(&SockRecv.recvBuff[end]));
				pivot += strlen(&SockRecv.recvBuff[end]);
				memcpy(&scpPath[pivot], " ", 1);
				pivot += 1;
				memcpy(&scpPath[pivot], "/data2/xboxhigh/_gatheringFiles/pFile/", 38);
				pivot += 38;
				
				cout << scpPath << endl;
				system(scpPath);
				
				cout << "Close connection from service.\n" 
							<< "<------------------------------------------------>\n\n";
			}
		}
		
		int lifeMark = 0;
		while(1)
		{
			for(int i = 0; i < 10; i++)
			{
				lifeMark = kill(childID[i], SIGUSR1);
				
				if(lifeMark == -1)
				{
					cout << "Child " << childID[i] << " Process died !" << endl;
					childID[i] = fork();
					
					if(getpid() != parentID)
						break;
					
					cout << "New childID[" << i << "] :" << childID[i] << endl;
					
					FILEVAR.DistributedSeeds = fopen(seedsFileName, "r");
					if(FILEVAR.DistributedSeeds != NULL)
					{
						fclose(FILEVAR.DistributedSeeds);
						DitributionOfSeeds(seedsFileName, childID[i]);
					}
					
				}
				else if(lifeMark == 0)
				{
					//cout << "Child " << childID[i] << " still alives ! " << endl;
					
					char checkPath[256];
					bzero(&checkPath, sizeof(checkPath));					
					
					strcpy(checkPath, seedsFileName);
					strcat(checkPath, itoa(childID[i]).c_str());
					
					FILEVAR.checkFile = fopen(checkPath, "r");
					FILEVAR.DistributedSeeds = fopen(seedsFileName, "r");
					
					if(FILEVAR.checkFile == NULL && FILEVAR.DistributedSeeds != NULL)
					{
						FILEVAR.checkFile = fopen(checkPath, "w+");
						DitributionOfSeeds(seedsFileName, childID[i]);
						fclose(FILEVAR.checkFile);
						fclose(FILEVAR.DistributedSeeds);
					}
				}
			}
			if(getpid() != parentID)
				break;
			sleep(10);	//cout << kill(53211, SIGUSR1) << endl;
		}
	}
	
	//Children's job is gathering web pages according to the distributed seeds.
	{		
		//cout << "This is child process. PID : " << getpid() << endl;
		char seedPathForChild[256];
		char hPathForChild[256];
		char cPathForChild[256];
		char oFPathForChild[256];
		
		bzero(&seedPathForChild, sizeof(seedPathForChild));
		bzero(&hPathForChild, sizeof(hPathForChild));
		bzero(&cPathForChild, sizeof(cPathForChild));
		bzero(&oFPathForChild, sizeof(oFPathForChild));
		
		int curID = getpid();	
		
		strcat(seedPathForChild, seedsFileName);
		strcat(seedPathForChild, itoa(curID).c_str());
		strcat(hPathForChild, headerFileName);
		strcat(hPathForChild, itoa(curID).c_str());
		strcat(cPathForChild, contentFileName);
		strcat(cPathForChild, itoa(curID).c_str());
		
		strcpy(procID, itoa(curID).c_str());
		
		int key = 0;
		while(1)
		{
			FILEVAR.DistributedSeeds = fopen(seedPathForChild, "r");
			
			if(FILEVAR.DistributedSeeds == NULL)
			{
				//cout << "Child " << curID << " Seed File is Not Found, path: [" << seedPathForChild << "]" << endl;
				sleep(5);
				//cout << seedPathForChild << endl;				
			}
			else
			{
				FILEVAR.Header = fopen(hPathForChild, "w+");
				 	if (FILEVAR.Header == NULL) cout << "No Such Path [" << hPathForChild << "]" << endl;
				FILEVAR.Content = fopen(cPathForChild, "wb+");
					if (FILEVAR.Content == NULL) cout << "No Such Path [" << cPathForChild << "]" << endl;
										
				//cout << "OK !  This is Child Process and PID : " << curID << endl;
				cout << "Process " << curID << " start gathering web pages..." << endl;
				
				//Begin gathering web pages//				
				char Line[10 * 1024];
				char *find = 0;
				
				Offset OFFSET;
				OFFSET.BegOffset = 0;
				OFFSET.EndOffset = 0;
				OFFSET.BegCOffset = 0;
				OFFSET.EndCOffset = 0;
				
				char xmlTileStr[56];
				char tmpTitleTag[12];
				char tmpEndTag[8];
				char xmlEndTag[20];
				
				strcpy(xmlTileStr, "<?xml version='1.0' encoding='utf-8'?><HEADINFOFILEINFO>");
				strcpy(tmpTitleTag, "<LINK><URL>");
				strcpy(tmpEndTag, "</LINK>");
				strcpy(xmlEndTag, "</HEADINFOFILEINFO>");
				
				xmlTileStr[56] = '\0';
				tmpTitleTag[12] = '\0';
				tmpEndTag[8] = '\0';
				xmlEndTag[20] = '\0';
				
				fwrite(xmlTileStr, 1, strlen(xmlTileStr),  FILEVAR.Header);

				while(fgets(Line, 10 * 1024 - 1, FILEVAR.DistributedSeeds))
				{
					fwrite(tmpTitleTag, 1, strlen(tmpTitleTag), FILEVAR.Header);
					
					if ((find = strrchr(Line, '\n')))
					{
						*find = '\0';
						fwrite(Line, 1, strlen(Line), FILEVAR.Header);
						fwrite("</URL>", 1, 6, FILEVAR.Header);
						
						if(pageGatheringByCurl(&FILEVAR, Line, &OFFSET) != 1)
						{
  						cout << "Totally Fail !" << endl;
  					}
					}
					
					fputs("<cPath>", FILEVAR.Header);
					fputs(cPathForChild, FILEVAR.Header);
					fputs("</cPath><offset><beg>", FILEVAR.Header);
					fputs(itoa(OFFSET.BegOffset).c_str(), FILEVAR.Header);
					fputs("</beg><end>", FILEVAR.Header);
					fputs(itoa(OFFSET.EndOffset).c_str(), FILEVAR.Header);
					fputs("</end></offset>", FILEVAR.Header);
					fwrite(tmpEndTag, 1, strlen(tmpEndTag),  FILEVAR.Header);
					key++;
				}
				
				//cout << "Process " << curID << " URL COUNT : " << key << endl;
				
				//Write Result into the Original Offset File//
				fwrite(xmlEndTag, 1, strlen(xmlEndTag), FILEVAR.Header);
				
				fclose(FILEVAR.Header);
				fclose(FILEVAR.Content);
				fclose(FILEVAR.DistributedSeeds);
					
				cout << "Process " << curID << " finish gathering !" << endl;
				
				cout << "Start sending message..." << endl;
				
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
					
				memcpy(&SockMess.sendBuff[index], "req", 3);
				index += 3;
				memcpy(&SockMess.sendBuff[index], "\t", 1);
				index += 1;
				memcpy(&SockMess.sendBuff[index], "HTTPPARSER", 10);
				index += 10;
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
				
				cout << "Finish sending message..." << endl;
				
				exit(0);
			}
		}
		
	}
			
	return 0;
}
