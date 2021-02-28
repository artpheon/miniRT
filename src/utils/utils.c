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
    normalize(&new);
    return (new);
}

t_ray set_ray(t_vector origin, t_vector dir)
{
    t_ray new;

    new.orig = origin;
    new.dir = dir;
    normalize(&(new.dir));
    return (new);
}

void strrev(char *s)
{
    char b;
    char e;
    int last;
    int i;

    i = 0;
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


float macheps(void)
{
	float e = 1.0f;

	while (1.0f + e / 2.0f > 1.0f)
		e /= 2.0f;
	return (e);
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

t_vector hextoc(int hex)
{
	t_vector new;

	new.x = (hex >> 16) & 0xff;
	new.y = (hex >> 8) & 0xff;
	new.z = hex & 0xff;
	return(new);
}

void exit_error(char *message, int errn)
{
    perror(message);
    exit(errn);
}

