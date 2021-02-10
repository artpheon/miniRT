#include "header.h"

t_vector set_vector(float x, float y, float z)
{
    t_vector new;

    new.x = x;
    new.y = y;
    new.z = z;
    return (new);
}

void close_app(char *message, int errn)
{
    perror(message);
    exit(errn);
}

