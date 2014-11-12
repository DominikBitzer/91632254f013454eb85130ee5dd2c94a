#ifndef CONFIG
#define CONFIG

#define GAMEKINDNAME "NMMorris"
#define PORTNUMBER "1357"
#define HOSTNAME "sysprak.priv.lab.nm.ifi.lmu.de"
#define CLIENTVERSION "VERSION 1.0\n"

// structure to save getopt() parameters and later those from a conf file in
struct config{
    char *gameid;
    char *conffile;
};

/**
 * @author  Simon Lackerbauer
 * @brief   Reads commandline parameter in form of an 11-digit game-id. Needed by performConnection() to connect to a game.
 * @input   argc, **argv
 * @output  structure config
 */
struct config readConfig(int argc, char **argv); 

/**
 * @author  Simon Lackerbauer
 * @brief   Print help.
 * @input   name of the calling program (string)
 * @output  void
 */
void printHelp(char *programName); 

#endif
