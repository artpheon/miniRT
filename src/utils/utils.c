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
    normalize(&new.dir);
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

int typecmp(char *t, t_object *o)
{
    if (ft_strncmp(o->type, t, 2) == 0)
        return (1);
    return (0);
}
/*
char	*screenshot_datetime()
{
	char		*res[35];
	time_t		t;
	struct tm	tm;

	t = time(NULL);
	tm = *localtime(&t);
	*res = ft_strdup("Screenshot YYYY-MM-DD hh:mm:ss.bmp");
	ft_memcpy(*res + 11, ft_itoa_width(tm.tm_year + 1900, 4), 4);
	ft_memcpy(*res + 16, ft_itoa_width(tm.tm_mon + 1, 2), 2);
	ft_memcpy(*res + 19, ft_itoa_width(tm.tm_mday, 2), 2);
	ft_memcpy(*res + 22, ft_itoa_width(tm.tm_hour, 2), 2);
	ft_memcpy(*res + 25, ft_itoa_width(tm.tm_min, 2), 2);
	ft_memcpy(*res + 28, ft_itoa_width(tm.tm_sec, 2), 2);
	return (*res);
}*/