
#include <sys/types.h>  //for wait3()
#include <sys/wait.h>   //for wait3()
#include <signal.h>
#include <pthread.h>

#include "Main.hpp"
#include "CS.hpp"
#include "ClientServer.hpp"

TIniFile    	*Config;
TVSocket    	*comSocket;
void        	Protocol_Handler(int newSocket);
TWriteLog   	*Log;
char        	Genbuf[1025];
pid_t			ServerPID;
THash			*Hash;
TMemoryBlock	*Memory;

static void Terminate(int sno) 
{
    comSocket->Close();
    Log->FlashOut();
    exit(1);
}

static void FlashOut(int sno)
{
    Log->FlashOut();
    signal(SIGUSR2, FlashOut);
    return;
}

static void Reaper(int sno)
{
    int status;
    while (wait3(&status, WNOHANG, (struct rusage *) 0) > 0)
        /* empty */ ;
    (void) signal(SIGCHLD, Reaper);
}

void Initial(char *ApplicationName)
{
    char bakAPName[256];

    Config=new TIniFile();
    comSocket=new TVSocket();
    Log=new TWriteLog();
    if( Log==NULL|| Config==NULL || comSocket==NULL )
        ErrorExit(errLackofMem,"Server Init.");
    strcpy(bakAPName,ApplicationName);
    sprintf(Genbuf,"%s.ini",bakAPName);
    Config->ReadIniFile(Genbuf);
    sprintf(Genbuf,"%s.log",bakAPName);
    Log->Open((char *)Config->GetCharValue("LOG_FILE",Genbuf));
    Hash=new THash(Config->GetIntValue("HASH_TABLE_SIZE",20000003));
    Memory=new TMemoryBlock;
}

void StartServer(void)
{
//Stand Alone
    if( fork() )
        exit(1);
    printf("Loding WNS Data....\n");
    if( LoadCS((char *)Config->GetCharValue("CS_FILE","CSF"))==false )
    	ErrorExit(errFileOpenError,"CS_FILE");
    printf("CS Data Loaded.\n");
    if( comSocket->passiveTCP(Config->GetCharValue("DAEMON_PORT",
                                                         DAEMON_PORT),
                                 Config->GetIntValue("DAEMON_QUEUE",
                                                        DAEMON_QUEUE))
                                 ==false )
    {
        ErrorExit(errStart,"Server Start Error.");
    }
    ServerPID=getpid();
    sprintf(Genbuf,"%s Daemon started. Port:%s PID:%d",APPLICATION_NAME,
            Config->GetCharValue("DAEMON_PORT",DAEMON_PORT),ServerPID);
    Log->Log(Genbuf,wl_NORMAL,true);
}

void main(int argc,char **argv)
{
	pthread_attr_t  attr;
	pthread_t		ptThread;

    Initial(argv[0]);
    signal(SIGCHLD, Reaper);
    signal(SIGUSR1, Terminate);
    signal(SIGUSR2, FlashOut);
    pthread_attr_init(&attr);
    pthread_attr_setscope(&attr, PTHREAD_SCOPE_SYSTEM);
    
    StartServer();
    while( 1 )
    {
        int NewSocket;
        int ForkStatus;

        NewSocket = comSocket->Accept();
        if(NewSocket == -1)
            continue;
        else
        {
			sprintf(Genbuf,"Connect From %s",comSocket->RemoteDotIP);
			Log->Log(Genbuf);
			pthread_create(&ptThread, &attr, (void * (*)(void *))Protocol_Handler, (void *)NewSocket);
        }
    }
}
