#include "Util.hpp"
#include "Main.hpp"
#include "ClientServer.hpp"
#include "Protocol.hpp"
#include "Hash.hpp"
#include <pthread.h>
#include <signal.h>
#include <sys/types.h>
#include <md5.h>

void Protocol_Handler(int newSocket)
{
	
	TVSocket	*ClientSocket;
    char		*ClientCommand;
    int			n;

	ClientSocket=new TVSocket();
	if( ClientSocket->ReOpen(newSocket)==NULL )
	{
		delete ClientSocket;
        pthread_exit(NULL);
    }
    ClientSocket->WriteLine(DAEMON_MESSAGE,true);
    while( ClientCommand=ClientSocket->GetToken() )
    {
        char *ckCommand;
        n=0;

        while( ckCommand=ProtocolList[n].Command )
        {
            if( strcasecmp(ClientCommand,ckCommand)==0 )
                break;
            n++;        
        }
        if(ckCommand==NULL)
        {
            if( ClientSocket->ClearToLineEnd() )
                ClientSocket->WriteLine("500 What?",true);
            else
                break;
        }else
        {
            if( ProtocolList[n].Handler(ClientSocket) <=0 )
                break;
            else
            {
                if( ClientSocket->ClearToLineEnd() )
                    continue;
                else
                    break;
            }
        }
    }
    ClientSocket->Close();
    delete ClientSocket;
    pthread_exit(NULL);
}

int Query(TVSocket *ClientSocket)
{
	char			CS[100];
	unsigned char	pszSig[16];
	SHashNode		*spNode;
	char        	*cmdPtr1;
	
	ClientSocket->ClearToLineEnd();
	ClientSocket->BWriteLine("200 Result Follows.",true);
	while(1)
	{
    	cmdPtr1=ClientSocket->GetToken();
    	strcpy(CS,cmdPtr1);
    	if( !strcmp(CS,".") )
    		break;
    	asc2bin(CS, 32, (char *)pszSig);
		spNode=Hash->Query(pszSig);
		if( !spNode )
			ClientSocket->BWriteLine("0\n",false);
		else if( spNode->cFlag==0 )
		{
			ClientSocket->BWriteLine("1\n",false);
			spNode->cFlag=1;
		}else
			ClientSocket->BWriteLine("2\n",false);
    }
    ClientSocket->FlushWB();
}

int Quit(TVSocket *ClientSocket)
{
    ClientSocket->WriteLine(END_DAEMON_MESSAGE,true);
    return 0;
}
