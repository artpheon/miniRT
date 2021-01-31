/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrobbin <hrobbin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 14:55:27 by hrobbin           #+#    #+#             */
/*   Updated: 2020/11/16 17:56:56 by hrobbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char *dst2;
	char *src2;

	dst2 = (char *)dst;
	src2 = (char *)src;
	if ((dst == NULL) && (src == NULL))
		return (NULL);
	if ((src2 < dst2) && (dst2 < src2 + len))
	{
		while (len--)
			dst2[len] = src2[len];
	}
	else
	{
		while (len--)
			*dst2++ = *src2++;
	}
	return (dst);
}
