/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrobbin <hrobbin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 16:29:59 by hrobbin           #+#    #+#             */
/*   Updated: 2020/11/16 17:55:05 by hrobbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	int	i;

	i = 0;
	while (n != 0)
	{
		if (!dst && !src)
			return (NULL);
		((char *)dst)[i] = ((char *)src)[i];
		n--;
		i++;
	}
	return (dst);
}
