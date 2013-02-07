/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.

 * File Name : serverTcp.c

 * Purpose : SPOJ

 * Creation Date : 06-02-2013

 * Last Modified : Thursday 07 February 2013 12:56:20 PM IST

 * Created By : npsabari

 _._._._._._._._._._._._._._._._._._._._._.*/

#include <sys/types.h>
#include <sys/time.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include "../Def.h"

int main (int argc, char *argv[]){
    int sock, connected, bytes_read;
    char send_data[MAXN], rev_data[MAXN], file_name[MAXN];
    Sock_in server_addr, client_addr;
    int sin_size;
    if (argc < 2){
        printf ("Enter PortNo");
        exit (0);
    }

    if ((sock = socket (AF_INET, SOCK_STREAM, 0)) == -1){
        perror ("Socket");
        exit (1);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons (atoi (argv[1]));
    server_addr.sin_addr.s_addr = INADDR_ANY;
    bzero (&(server_addr.sin_zero), 8);

    if (bind (sock, (Sock_addr *) &server_addr, sizeof (Sock_addr)) == -1){
        perror ("Unable to bind");
        exit (1);
    }

    if (listen (sock, 5) == -1){
        perror ("Listen");
        exit (1);
    }
    printf ("\nTCPServer Waiting for client on port %s\n", argv[1]);
    fflush (stdout);

    while(true){
        connected = accept (sock, (Sock_addr *) &client_addr, &sin_size);
        sin_size = sizeof (Sock_in);
        bytes_read = recv(connected, rev_data, MAXN, 0);
        printf ("\nConnection from (%s , %d) asked for : %s\n", inet_ntoa (client_addr.sin_addr), ntohs (client_addr.sin_port), rev_data);

        sprintf(file_name, "../files/%s", rev_data);
        FILE* fp = fopen(file_name, "r");

        if(fp == NULL)
            printf("No such file found; Data not sent\n");
        else{
            while((bytes_read = fread(send_data, 1, SEG_SIZE, fp)) > 0){
                send_data[bytes_read] = '\0';
                send (connected, send_data, bytes_read, 0);
                usleep(1000);       //Sleeping while client reads the data
            }
            fclose(fp);
        }
        close(connected);
    }
    close (sock);
    return 0;
}
