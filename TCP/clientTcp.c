/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.

 * File Name : clientTcp.c

 * Purpose : Networks Assignment 

 * Creation Date : 30-01-2013

 * Last Modified : Thursday 07 February 2013 01:58:20 PM IST

 * Created By : npsabari

 _._._._._._._._._._._._._._._._._._._._._.*/

#include <sys/types.h>
#include <sys/wait.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include "../Def.h"

int main(int argc, char** argv){
    int sock, bytes_received;
    char send_data[MAXN], rev_data[MAXN], inp[MAXN];
    Host_ent *host;
    Sock_in server_addr;

    int child_status;

    if(argc < 3){
        printf ("Enter PortNo");
        exit (0);
    }

    host = gethostbyname (argv[2]);
    while(true){
        pid_t t = fork();
        if(t == 0){
            if ((sock = socket (AF_INET, SOCK_STREAM, 0)) == -1){
                perror ("Socket");
                exit (1);
            }
            server_addr.sin_family = AF_INET;
            server_addr.sin_port = htons (atoi (argv[1]));
            server_addr.sin_addr = *((In_addr *) host->h_addr);
            bzero (&(server_addr.sin_zero), 8);

            printf("Enter name of the file to browse ( with path from server root ): ");
            scanf("%s", send_data);
            if(strcmp(send_data, "q") == 0 || strcmp(send_data, "Q") == 0)
                break;
            if(connect (sock, (Sock_addr *) &server_addr, sizeof (Sock_addr)) == -1){
                perror ("Connect");
                exit (1);
            }
            send(sock, send_data, sizeof(send_data), 0);
            int cnt = true;
            int i = 1;
            while(true){
                bytes_received = recv(sock, rev_data, MAXN, 0);
                if(bytes_received <= 0){
                    printf("End\n");
                    break;
                }
                rev_data[bytes_received] = '\0';
                if(cnt){
                    cnt = false;
                    printf("Received data : \n");
                }
                printf("Segment #%d: %s\n", i++, rev_data);
            }
            exit(EXIT_SUCCESS);
        }
        else{
            if(wait(&child_status) != -1){
                printf("Do you want to browse another file ? (y/n) : ");
                scanf("%s", inp);
                if(strcmp(inp, "n") == 0)
                    break;
            }
        }
    }
    close(sock);
    return 0;
}

