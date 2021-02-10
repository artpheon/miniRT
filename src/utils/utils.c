#include "header.h"

void close_app(char *message, int errn)
{
    perror(message);
    exit(errn);
}

