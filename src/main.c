#define _POSIX_C_SOURCE 2
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>         // close()
#include <sys/socket.h>     // socket
#include <netdb.h>          // getaddressinfo (for socket), freeaddrinfo, struct addrinfo
#include <arpa/inet.h>      // socket, connect
#include <sys/types.h>      // socket
#include <string.h>         // memset()
#include <unistd.h>         // fork() for process creation
#include <sys/types.h>      // pid_t Datatype for fork()
#include <time.h>           // sleep() for testing purposes
#include "config.h"         // struct config
#include "utils.h"          // die
#include "performConnection.h"  // performConnection

int main(int argc, char **argv) {
    
    // use readConfig() from config.c to read all commandline arguments and all further configuration from a given config file
    struct config myConfig = readConfig(argc, argv); 

    // saving pid for fork() command
    pid_t pid;
    
    if ((pid = fork()) == -1) {
        /* error with fork() */
        fprintf(stderr, "error when executing fork().\n");

    } else if (pid == 0) {
        /* connector: child process */
        
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
        
    } else {
        /* thinker: parent process */

        sleep(10000000);  // wait 1000 seconds so client/server can communicate
    }

    exit(EXIT_SUCCESS);
}
