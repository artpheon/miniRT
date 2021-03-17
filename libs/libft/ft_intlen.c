//
// Created by Howe Robbin on 3/17/21.
//

#include "libft.h"

int	ft_intlen(int i)
{
	int	count;

	count = 1;
	while (i)
	{
		i /= 10;
		if (i != 0)
			count++;
	}
	return (count);
}