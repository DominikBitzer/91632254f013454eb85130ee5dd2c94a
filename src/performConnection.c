#define _POSIX_C_SOURCE 2 
#include <unistd.h>         // close()
#include <sys/socket.h>     // socket
#include <netdb.h>          // getaddressinfo (for socket), freeaddrinfo, struct addrinfo
#include <arpa/inet.h>      // socket, connect
#include <sys/types.h>      // socket
#include <string.h>         // memset()
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "performConnection.h"
#include "config.h"
#include "utils.h"
#define MAXBUF 1024

void connector(int argc, char **argv) {
    
    // use readConfig() from config.c to read all commandline arguments and all further configuration from a given config file
    struct config myConfig = readConfig(argc, argv);
    
    // get server info with getaddrinfo(), create socket and connect
    int sock, status;
    struct addrinfo hints;
    struct addrinfo *servinfo;

    memset(&hints, 0, sizeof hints); 
    hints.ai_family = AF_UNSPEC;        // Specifies if IPv4 or IPv6 but AF_UNSPEC states arbitrarity of it
    hints.ai_socktype = SOCK_STREAM;

    if ((status = getaddrinfo(HOSTNAME, PORTNUMBER, &hints, &servinfo)) != 0) {
        fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(status));
        exit(EXIT_FAILURE);
    }

    if((sock = socket(servinfo->ai_family, servinfo->ai_socktype, servinfo->ai_protocol)) < 0)
        die("Could not create socket");     // die: Error message and exiting program with failure
   
    if(connect(sock, servinfo->ai_addr, servinfo->ai_addrlen) < 0) 
        die("Could not connect to server");

    // free the structure because socket is already created
    freeaddrinfo(servinfo);

    // the rest of the communication is done by performConnection
    performConnection(sock, myConfig);
    
    // close socket 
    close(sock);
}

int performConnection(int sockfd, struct config myConfig) {    
    char gameid[15];                 //Because message to server: "ID xxxxxxxxxxx\n"
    char playerInput[MAXBUF];

    // GameID for testing: 4S693ELx2Wc

    strcpy(gameid, "ID ");
    strcat(gameid, myConfig.gameid);
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

    while(1) {
        scanf("%s", playerInput);
        strcat(playerInput, "\n");
        sendToGameserver(playerInput, sockfd);
        recvFromGameserver(sockfd);
    }

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
