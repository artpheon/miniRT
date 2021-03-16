#include "libft.h"

float    ft_atof(char *str)
{
	float  atof;
	int    atoi;
	int    i;
	int    fac;

	fac = 1;
	atof = 0;
	i = 0;
	while (ft_isspace(str[i]))
		i++;
	str[i] == '-' ? fac = -1 : 0;
	atoi = ft_atoi(str);
	i += ft_intlen(atoi);
	fac == -1 ? i++ : 0;
	if (str[i] != '.')
		return (atoi);
	i++;
	while (ft_isdigit(str[i]))
	{
		fac *= 10;
		atof = atof * 10 + str[i] - 48;
		i++;
	}
	atof = atof / fac;
	return (atoi + atof);
}