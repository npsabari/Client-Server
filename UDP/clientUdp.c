/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.

* File Name : clientUdp.c

* Purpose : Networks Assignment

* Creation Date : 29-01-2013

* Last Modified : Wednesday 06 February 2013 07:46:54 PM IST

* Created By : npsabari

_._._._._._._._._._._._._._._._._._._._._.*/

#include <sys/types.h>
#include <sys/time.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include "../Def.h"

int main(int argc, char *argv[]){
    int sock, bytes_rev;
    Sock_in server_addr;
    Host_ent *host;
    char send_data[MAXN], rev_data[MAXN];
    struct timeval tv;
    tv.tv_sec = TIME_OUT;
    tv.tv_usec = 0;

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
    setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(struct timeval));

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(atoi(argv[1]));
    server_addr.sin_addr = *((In_addr *)host->h_addr);
    bzero(&(server_addr.sin_zero), 8);

    while(true){
        printf("Enter a Roll Number (q or Q to quit) : ");
        scanf("%s", send_data);
        if( strcmp(send_data, "q") == 0 || strcmp(send_data, "Q") == 0 )
            break;
        int cnt = 0;
        while(cnt < MAX_TRY){
            sendto(sock, send_data, strlen(send_data), 0, (Sock_addr *)&server_addr, sizeof(Sock_addr));
            bytes_rev = recvfrom(sock, rev_data, MAXN, 0, NULL, NULL);
            if(bytes_rev < 0){
                printf("Try #%d: Nothing received: Key not found or server timed out\n", ++cnt);
                continue;
            }
            else
                break;
        }
        if(cnt == MAX_TRY){
            printf("No response from server; Ignoring the input\n");
            continue;
        }
        rev_data[bytes_rev] = '\0';
        printf("The Name is %s\n", rev_data);
        fflush(stdout);
    }
    close(sock);
    return 0;
}


