#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include "performConnection.h"
#include "config.h"
#include "utils.h"
#define MAXBUF 1024

int performConnection(int sockfd, struct config conf) {    
    char gameid[14];

    // GameID for testing: 4S693ELx2Wc

    if(conf.gameid == NULL) {
        fprintf(stderr, "You need to input a GameID!\n");
        exit(EXIT_FAILURE);
    }

    strcpy(gameid, "ID ");
    strcat(gameid, conf.gameid);
    strcat(gameid, "\n");
    
    // PROLOG
    recvFromGameserver(sockfd);
    sendToGameserver(CLIENTVERSION, sockfd);
    recvFromGameserver(sockfd);
    sendToGameserver(gameid, sockfd);
    recvFromGameserver(sockfd);
    recvFromGameserver(sockfd);
    sendToGameserver("PLAYER \n", sockfd);
    recvFromGameserver(sockfd);
    recvFromGameserver(sockfd);

    return EXIT_SUCCESS;
}

int sendToGameserver(char *msg, int sockfd) {
    int numbytes;

    if(strlen(msg) > MAXBUF-1)
        die("Message out of bounds!");

    numbytes = send(sockfd, msg, strlen(msg), 0);

    if(numbytes == -1)
        die("Something went wrong while sending data to the server!");

    printf("C: %s", msg);

    return EXIT_SUCCESS;
}

int recvFromGameserver(int sockfd) {
    char buf[MAXBUF];
    int numbytes;
    
    if((numbytes = recv(sockfd, buf, MAXBUF-1, 0)) == -1)
        die("Something went wrong while receiving the server's answer!");

    if(numbytes == 0)
        die("Server closed connection!");

    if(buf[0] == '-') {
        printf("Server answered: %s", buf);
        exit(EXIT_FAILURE);
    }

    buf[numbytes] = '\0';

    printf("S: %s", buf);

    return EXIT_SUCCESS;
}
