#include "header.h"

t_vector set_vector(float x, float y, float z)
{
    t_vector new;

    new.x = x;
    new.y = y;
    new.z = z;
    return (new);
}

t_vector set_nvector(float x, float y, float z)
{
    t_vector new;

    new.x = x;
    new.y = y;
    new.z = z;
    return (norm_vector(new));
}

t_ray set_ray(t_vector origin, t_vector dir)
{
    t_ray new;

    new.origin = origin;
    new.direction = dir;
    return (new);
}

void strrev(char *s)
{
    char b;
    char e;
    int last;
    int i;

    last = ft_strlen(s) - 1;
    while (last > i)
    {
        b = s[i];
        e = s[last];
        s[last] = b;
        s[i] = e;
        last--;
        i++;
    }
}


int ctohex(t_vector rgb)
{
    int r;
    int g;
    int b;

    r = rgb.x;
    g = rgb.y;
    b = rgb.z;
    return ((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff);
}

void close_app(char *message, int errn)
{
    perror(message);
    exit(errn);
}

