/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrobbin <hrobbin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 16:51:52 by hrobbin           #+#    #+#             */
/*   Updated: 2020/11/16 18:22:49 by hrobbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	int i;

	i = 0;
	while (n != 0)
	{
		if (((char *)src)[i] != (char)c)
		{
			((char *)dst)[i] = ((char *)src)[i];
			i++;
			n--;
		}
		else
		{
			((char *)dst)[i] = ((char *)src)[i];
			return ((void *)(dst + i + 1));
		}
	}
	return (NULL);
}
