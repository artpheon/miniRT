/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrobbin <hrobbin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 16:12:23 by hrobbin           #+#    #+#             */
/*   Updated: 2020/11/17 14:01:38 by hrobbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*fill_arr(char *dest, int n, int counter)
{
	dest[counter--] = '\0';
	if (n == 0)
		dest[0] = '0';
	if (n == -2147483648)
		ft_strlcpy(dest, "-2147483648", 12);
	else if (n < 0)
	{
		n *= -1;
		dest[0] = '-';
	}
	while (n > 0)
	{
		dest[counter] = (n % 10) + '0';
		n /= 10;
		counter--;
	}
	return (dest);
}

char		*ft_itoa(int n)
{
	char	*dest;
	int		nbr;
	int		count;

	nbr = n;
	count = (nbr == 0) ? 1 : 0;
	while (nbr != 0)
	{
		nbr /= 10;
		count++;
	}
	count += (n < 0) ? 1 : 0;
	if (NULL == (dest = (char *)malloc(count + 1)))
		return (NULL);
	return (fill_arr(dest, n, count));
}
