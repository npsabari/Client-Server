/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.

* File Name : clientUdp.c

* Purpose : Networks Assignment

* Creation Date : 29-01-2013

* Last Modified : Wednesday 30 January 2013 02:29:40 AM IST

* Created By : npsabari

_._._._._._._._._._._._._._._._._._._._._.*/

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include "Udp.h"

typedef struct sockaddr Sock_addr;

int main(int argc, char *argv[]){
    int sock, bytes_rev;
    Sock_in server_addr;
    Host_ent *host;
    char send_data[MAXN], rev_data[MAXN];
    
    if(argc < 2){
        printf("Enter Port Number");
        exit(0);
    }

    host = (Host_ent *) gethostbyname( (char *) argv[2]);
    
    sock = socket( AF_INET, SOCK_DGRAM, 0);
    if(sock == -1){
        perror("Socket");
        exit(1);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(atoi(argv[1]));
    server_addr.sin_addr = *((In_addr *)host->h_addr);
    bzero(&(server_addr.sin_zero), 8);

    while(1){
        printf("Enter a Roll Number (q or Q to quit) : ");
        scanf("%s", send_data);
        if( strcmp(send_data, "q") == 0 || strcmp(send_data, "Q") == 0 )
            break;
    
        sendto(sock, send_data, strlen(send_data), 0, (Sock_addr *)&server_addr, sizeof(Sock_addr));

        bytes_rev = recv(sock, rev_data, MAXN, 0);
        rev_data[bytes_rev] = '\0';
        printf("The Name is %s\n", rev_data);
        fflush(stdout);
    }
    close(sock);
    return 0;
}


