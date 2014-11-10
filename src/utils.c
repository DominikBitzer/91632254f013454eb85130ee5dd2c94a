#include <stdio.h>
#include <stdlib.h>

void die(char *message) {
    perror(message);
    exit(EXIT_FAILURE);
}
