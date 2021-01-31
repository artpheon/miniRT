/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrobbin <hrobbin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 19:17:14 by hrobbin           #+#    #+#             */
/*   Updated: 2020/11/23 12:14:23 by hrobbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	res;
	int		j;

	i = ft_strlen(dst);
	res = 0;
	while (src[res])
		++res;
	if (dstsize <= i)
		return (res += dstsize);
	else
		res += i;
	j = 0;
	while (src[j] && dstsize > i + 1)
	{
		dst[i] = src[j];
		i++;
		j++;
	}
	dst[i] = '\0';
	return (res);
}
