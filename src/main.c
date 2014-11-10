#define _POSIX_C_SOURCE 2
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>         // close()
#include <sys/socket.h>     // socket
#include <netdb.h>          // socket
#include <arpa/inet.h>      // socket
#include <sys/types.h>      // socket
#include <string.h>         // memset()
#include "config.h"
#include "utils.h"
#include "performConnection.h"

int main(int argc, char **argv) {
    
    // use readConfig() from config.c to read all commandline arguments and all further configuration from a given config file
    struct config myConfig = readConfig(argc, argv); 

    // get server info with getaddrinfo(), create socket and connect
    int sock, status;
    struct addrinfo hints;
    struct addrinfo *servinfo;

    memset(&hints, 0, sizeof hints); 
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    if ((status = getaddrinfo(HOSTNAME, PORTNUMBER, &hints, &servinfo)) != 0) {
        fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(status));
        exit(EXIT_FAILURE);
    }

    if((sock = socket(servinfo->ai_family, servinfo->ai_socktype, servinfo->ai_protocol)) < 0)
        die("Could not create socket");
   
    if(connect(sock, servinfo->ai_addr, servinfo->ai_addrlen) < 0)
        die("Could not connect to server");

    // free the structure because socket is already created
    freeaddrinfo(servinfo);

    // the rest of the communication is done by performConnection
    performConnection(sock, myConfig);
    
    // close socket 
    close(sock);
    
    exit(EXIT_SUCCESS);
}
