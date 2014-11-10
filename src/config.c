#define _POSIX_C_SOURCE 2
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "config.h"
#include "utils.h"

struct config readConfig(int argc, char **argv) {
    
    struct config thisConfig = { .gameid = NULL, .conffile = NULL};
    int opt;
    FILE *fd = NULL;

    while ((opt=getopt(argc, argv, "i:c:h")) != -1) {
        switch (opt) {
            case 'i': // -i switch for gameid
                if(strlen(optarg) != 11) {
                    fprintf(stderr, "GameID must be 11 digits long! \"%s\" is only %zu digits long.\n", optarg, strlen(optarg));
                    exit(EXIT_FAILURE);
                }
                thisConfig.gameid = optarg;
                break;
            case 'c': // -c switch for config file
                if((fd = fopen(optarg, "r")) == NULL) {
                    fprintf(stderr, "%s: ", optarg);
                    perror(NULL);
                    exit(EXIT_FAILURE);
                }
                thisConfig.conffile = optarg;
                break;
            case 'h': // -h switch for help
                printHelp(argv[0]);
                break;
            default:
                printHelp(argv[0]);
        }
    }

    return thisConfig;
}

void printHelp(char *programName) {
    printf("Usage: \t%s [-i GAMEID] [-c CONFIGFILE]\n", programName);
    printf("\t%s -h\n", programName);
    exit(EXIT_SUCCESS);
}
