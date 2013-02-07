/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.

 * File Name : serverWrapUdp.c

 * Purpose : Networks Assignment 

 * Creation Date : 29-01-2013

 * Last Modified : Thursday 07 February 2013 04:23:21 PM IST

 * Created By : npsabari

 _._._._._._._._._._._._._._._._._._._._._.*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/time.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <time.h>
#include <errno.h>
#include <netdb.h>
#include "../Def.h"
#include "BSTree/BSTree.h"

BSTree* bst;

void Construct_BSTree(){
    FILE* fp;
    fp = fopen("../files/bstinput.txt", "r");
    int size = 0;
    int i, roll;
    char name[SIZE];
    fscanf(fp, "%d", &size);
    bst = (BSTree *)malloc(sizeof(BSTree));
    bst->root = NULL;
    for(i = 0; i < size; ++i){
        fscanf(fp, "%d %s", &roll, name);
        bst->root = insert(bst->root, roll, name);
    }
    fclose(fp);
}

int main(int argc, char *argv[]){
    /* Variables Used for Receiving data from Client */
    int sock, bind_ret;                           //Socket to Receive input query from client
    int addr_len, bytes_read;           
    char rev_data[MAXN];
    char* send_data;
    Sock_in client_addr, server_addr;
    struct timeval tv;
    tv.tv_sec = TIME_OUT;
    tv.tv_usec = 0;

    float prob = atof(argv[2]);

    srand(time(NULL));

    if(argc < 2){
        printf("Port Number Missing\n");
        exit(0);
    }

    /*Socket to receive data from Client*/
    sock = socket(AF_INET, SOCK_DGRAM,  0);
    if(sock == -1){
        perror("Socket");
        exit(1);
    }

    /*Initializing Server for Socket that receives data from Client*/
    setsockopt(sock, SOL_SOCKET, SO_SNDTIMEO, &tv, sizeof(struct timeval));

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(atoi(argv[1]));
    server_addr.sin_addr.s_addr = INADDR_ANY;
    bzero(&(server_addr.sin_zero), 8);

    bind_ret = bind(sock, (Sock_addr *)&server_addr, sizeof(Sock_addr));
    if(bind_ret == -1){
        perror("Bind");
        exit(1);
    }

    addr_len = sizeof(Sock_addr);

    printf("UDP server waiting for Roll No from client on port number : %s\n", argv[1]);
    fflush(stdout);

    Construct_BSTree();

    while(true){
        bytes_read = recvfrom(sock, rev_data, MAXN, 0, (Sock_addr *)&client_addr, &addr_len);
        rev_data[bytes_read] = '\0';

        printf("\nClient from ( %s , %d ) asked for Roll No : ", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
        printf("%s", rev_data);
        fflush(stdout);

        int roll = atoi(rev_data);
        Node* ans = search(bst->root, roll);
        if(ans == NULL){
            printf("\nKey not found and data not sent \n");
            //ans = new_node(-1, "key not found");
            continue;
        }
        if(prob*1000 < rand()%1000){
            if( sendto(sock, ans->name, strlen(ans->name), 0, (Sock_addr *)&client_addr, sizeof(Sock_addr) ) < 0)
                printf("Data not sent from server\n");
        }
        else{
            printf("\nPacket dropped\n");
            continue;
        }
    }
    close(sock);
    return 0;
}
