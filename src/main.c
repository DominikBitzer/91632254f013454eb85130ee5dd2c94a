#define _POSIX_C_SOURCE 2
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>         // fork() for process creation
#include <sys/types.h>      // pid_t Datatype for fork()
#include <time.h>           // sleep() for testing purposes
#include "config.h"         // struct config
#include "utils.h"          // die
#include "performConnection.h"  // performConnection

int main(int argc, char **argv) {
    
    // saving pid for fork() command
    pid_t pid;
    if ((pid = fork()) == -1) {
        /* error with fork() */
        fprintf(stderr, "error when executing fork().\n");
    } else if (pid == 0) {
        /* connector: child process */
        connector(argc,argv);
    } else {
        /* thinker: parent process */
        sleep(10000000);  // wait 1000 seconds so client/server can communicate
    }

    exit(EXIT_SUCCESS);
}
