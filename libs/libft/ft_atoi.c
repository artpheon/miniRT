/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrobbin <hrobbin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 15:16:28 by hrobbin           #+#    #+#             */
/*   Updated: 2020/11/17 14:24:05 by hrobbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int sign;
	int nbr;
	int i;

	sign = 1;
	nbr = 0;
	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == 43)
		i++;
	else if (str[i] == 45)
	{
		sign *= -1;
		i++;
	}
	else if (str[i] < 48 || str[i] > 57)
		return (nbr);
	while (str[i] > 47 && str[i] < 58)
		nbr = nbr * 10 + (str[i++] - '0');
	return (nbr * sign);
}
