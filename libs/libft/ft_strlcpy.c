/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrobbin <hrobbin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 18:17:56 by hrobbin           #+#    #+#             */
/*   Updated: 2020/11/18 13:30:57 by hrobbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	if (dst == NULL || src == NULL)
		return (0);
	if (src[i])
	{
		while (i != (dstsize - 1) && dstsize)
		{
			dst[i] = src[i];
			i++;
			if (src[i] == '\0')
				break ;
		}
	}
	if (dstsize)
		dst[i] = '\0';
	return (ft_strlen(src));
}
