/* $Id: socket.c 1.1 1995/01/01 07:11:14 cthuang Exp $
 *
 * This module has been modified by Radim Kolar for OS/2 emx
 */

/***********************************************************************
  module:       socket.c
  program:      popclient
  SCCS ID:      @(#)socket.c    1.5  4/1/94
  programmer:   Virginia Tech Computing Center
  compiler:     DEC RISC C compiler (Ultrix 4.1)
  environment:  DEC Ultrix 4.3 
  description:  UNIX sockets code.
 ***********************************************************************/
 
#include <sys/types.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/time.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

void PrintHostentInfo(struct hostent *hp) 
{
    char **pptr;
    char address[INET_ADDRSTRLEN + 1] = {0};


    printf("official hostname:%s\n", hp->h_name);

	for(pptr = hp->h_aliases; *pptr != NULL; pptr++)
		printf("alias:%s\n",*pptr);

	for(pptr = hp->h_addr_list; *pptr != NULL; pptr++)
		printf("address:%s\n",inet_ntop(hp->h_addrtype, *pptr, address, sizeof(address)));
	
    printf("first address: %s\n",inet_ntop(hp->h_addrtype, hp->h_addr, address, sizeof(address)));				
}

int Socket(const char *host, int clientPort)
{
    int ret;
    int sock;
    // unsigned long inaddr;
    struct sockaddr_in ad;
    struct hostent *hp;
    
    memset(&ad, 0, sizeof(ad));
    // AF_INET Ipv4
    ad.sin_family = AF_INET;

    // inaddr = inet_addr(host);
    // if (inaddr != INADDR_NONE)
    //     memcpy(&ad.sin_addr, &inaddr, sizeof(inaddr));
    // else

    // INADDR_NONE 可能是广播地址，注释掉原来的inet_addr换成inet_aton
    ret = inet_aton(host, &ad.sin_addr);
    if (ret != 1)
    {
        hp = gethostbyname(host);
        if (hp == NULL)
            return -1;
        // PrintHostentInfo(hp);
        memcpy(&ad.sin_addr, hp->h_addr, hp->h_length);
    }
    // 转网络字节序（大端），因为大小端问题，网络传输应该留意转换。
    ad.sin_port = htons(clientPort);
    
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0)
        return sock;
    if (connect(sock, (struct sockaddr *)&ad, sizeof(ad)) < 0)
        return -1;
    return sock;
}

