/*
    TCP/UDP Client/Server Library.
    687410003 ±i½å©v @ DNA Workroom
    Version: 1.1    1998.11.20
    Version: 1.0    1996.6.30

    passiveTCP() Create a TCP Server Socket.
    passiveUDP() Create a UDP Server Socket.
    connectTCP() Connect to a TCP Server.
    connectUDP() Claim a connect to a UDP Server.
*/

#include "cs.h"

/*
    Create a Server Socket.
    service  : Port name , or in number.
    transport: "udp" / "tcp"
    qlen     : Listen queue length.

    return value:
            if Success, return socket, else return -1,
            and display error reason.
*/

int
passivesock(const char *service, const char *transport,int qlen)
{
        struct servent *pse;
        struct protoent *ppe;
        struct sockaddr_in sin;
        int s,type;
        int on=1;

        memset(&sin,0,sizeof(sin));
        sin.sin_family=AF_INET;
        sin.sin_addr.s_addr=INADDR_ANY;

        if( (pse=getservbyname(service,transport)) )
        {
                sin.sin_port=htons( (u_short)pse->s_port + portbase );
        }else if( (sin.sin_port = htons( (u_short)atoi(service) ))==0 )
        {
                fprintf(stderr,"Can't get \"%s\" service entry\n",service);
                return -1;
        }
        if( !(ppe=getprotobyname(transport)) )
        {
                fprintf(stderr,"Can't get \"%s\" protocol entry\n",transport);
                return -1;
        }
        
        type=(strcmp(transport,"udp")==0)?SOCK_DGRAM:SOCK_STREAM;
        if( (s=socket(PF_INET,type,ppe->p_proto))<0 )
        {
                fprintf(stderr,"Can't creat socket: %d\n",errno);
                return -1;
        }
        setsockopt(s, SOL_SOCKET, SO_REUSEPORT, (char *) &on, sizeof(on));
        if(bind(s,(struct sockaddr *)&sin,sizeof(sin))<0)
        {
/*                fprintf(stderr,"Can't bind to %s port socket: %d\n",service,
                        errno);*/
                return -1;
        }
        if(type==SOCK_STREAM && listen(s,qlen)<0)
        {
                fprintf(stderr,"Can't listen to %s port socket: %d\n",service,
                        errno);
                return -1;
        }
        return s;
}

int
passiveTCP(const char *service,int qlen)
{
        return passivesock(service,"tcp",qlen);
}

int
passiveUDP(const char *service)
{
        return passivesock(service,"udp",0);
}

/*
    Connect to a server
    host     : Host name.
    service  : Port name , or in number.
    transport: "udp" / "tcp"

    return value:
            if Success, return socket, else return -1,
            and display error reason.
*/
int
connectsock(const char *host,const char *service,const char *transport)
{
        struct hostent *phe;
        struct servent *pse;
        struct protoent *ppe;
        struct sockaddr_in sin;
        int s,type;

        memset(&sin,0,sizeof(sin));
        sin.sin_family=AF_INET;

        if( (pse=getservbyname(service,transport))!=NULL )
                sin.sin_port=pse->s_port;
        else if( (sin.sin_port=htons( (u_short)atoi(service) )) ==0)
        {
                fprintf(stderr,"Can't get \"%s\" service entry\n",service);
                return -1;
        }
        if( (phe=gethostbyname(host))!=NULL )
                memcpy(&sin.sin_addr,phe->h_addr,phe->h_length);
        else if( (sin.sin_addr.s_addr=inet_addr(host)) == INADDR_NONE)
        {
                fprintf(stderr,"Can't get \"%s\" host entry\n",host);
                return -1;
        }
        if(!(ppe=getprotobyname(transport)))
        {
                fprintf(stderr,"Can't get \"%s\" protocol entry\n",transport);
                return -1;
        }
        type=(strcmp(transport,"udp")==0)?SOCK_DGRAM:SOCK_STREAM;
        s=socket(PF_INET,type,ppe->p_proto);
        if(s<0)
        {
                fprintf(stderr,"Can't creat socket:%d\n",errno);
                return -1;
        }
        if(connect(s,(struct sockaddr *)&sin,sizeof(sin))<0)
        {
                fprintf(stderr,"Connect error:%d\n",errno);
                return -1;
        }
        return s;
}
        
int connectUDP(const char *host,const char *service)
{
        return connectsock(host,service,"udp");
}

int connectTCP(const char *host,const char *service)
{
        return connectsock(host,service,"tcp");
}

int cs_accept(int iSocket)
{
	struct sockaddr adr;
	socklen_t  alen;
        
      	alen=sizeof(adr);
	return accept(iSocket,(struct sockaddr *)&adr, &alen);
}
