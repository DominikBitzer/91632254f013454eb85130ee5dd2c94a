#ifndef PERFORMCONNECTION
#define PERFORMCONNECTION
#include "config.h"

/**
 * @author  Simon Lackerbauer
 * @brief   Handles all communication over the net
 * @input   file descriptor of socket
 * @output  EXIT_SUCCESS or EXIT_FAILURE
 */
int performConnection(int sockfd, struct config conf);

/**
 * @author  Simon Lackerbauer
 * @brief   Handles the sending part
 * @input   message to send ending with \n, file descriptor of socket
 * @output  EXIT_SUCCESS or EXIT_FAILURE
 */
int sendToGameserver(char *msg, int sockfd);

/**
 * @author  Simon Lackerbauer
 * @brief   Handles the receiving part
 * @input   file descriptor of socket
 * @output  EXIT_SUCCESS or EXIT_FAILURE
 */
int recvFromGameserver(int sockfd);

/**
 * @author  Simon Lackerbauer
 * @brief   Makes gameserver response human readable
 * @input   unformatted gameserver response (string)
 * @output  formatted gameserver response (string)
 */
char *formatResponse(char *response);

#endif
