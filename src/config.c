#define _POSIX_C_SOURCE 2
#define DEFAULT_CONFIG "client.conf"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>      // tolower()
#include "config.h"
#include "utils.h"

#define LEN_BUFFER_SETTINGS 50

struct config readConfig(int argc, char **argv) {
    
    struct config thisConfig = { .gameid = NULL, .conffile = NULL};
    int opt;
    FILE *fd = NULL;

    if(argc == 1) {
        printHelp(argv[0]);
    }

    while((opt=getopt(argc, argv, "i:c:h")) != -1) {
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

    // if GameID is missing, abort
    if(thisConfig.gameid == NULL) {
        fprintf(stderr, "You need to input a GameID!\n");
        printHelp(argv[0]);
        exit(EXIT_FAILURE);
    }

    // if no config file was specified, use default config file (DEFAULT_CONFIG: client.conf)
    if(thisConfig.conffile == NULL) {
        if((fd = fopen(DEFAULT_CONFIG, "r")) == NULL) {
            fprintf(stderr, "%s: ", DEFAULT_CONFIG);
            perror(NULL);
            exit(EXIT_FAILURE);
        }
        thisConfig.conffile = DEFAULT_CONFIG;
    }

    return thisConfig;
}


// this function will parse the a configuration file that is given in the struct config element within config.conffile

struct config parseConfig(struct config thisConfig) {

    char buf[LEN_BUFFER_SETTINGS];
    
    FILE *fd = NULL;
    if((fd = fopen(optarg, "r")) == NULL) {
        fprintf(stderr, "%s: ", optarg);
        perror(NULL);
        exit(EXIT_FAILURE);
    }

// iterate over all lines of configfile and in each line save line in buf
    while (fgets(buf,LEN_BUFFER_SETTINGS,fd)) {
		
		// convert string to lowercase
		for(int i=0; buf[i]; i++) {
            buf[i] = tolower(buf[i]);
        }
		
		// check which option was specified in line that was just read out
		if (strcmp(buf, "portnumber") == 0) 
        {
            
        } 
        
        else if (strcmp(buf, "hostname") == 0)
        {
            
        }
        
        else if (strcmp(buf, "gamekindname") == 0)
        {
            
        } 
        
        else /* default: */
        {
            
        }

		
		
	}
    
    
    
    
    
    return thisConfig;
    
    
}



void printHelp(char *programName) {
    printf("Usage: \t%s [-i GAMEID] [-c CONFIGFILE]\n", programName);
    printf("\t%s -h\n", programName);
    exit(EXIT_SUCCESS);
}
