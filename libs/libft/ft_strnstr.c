/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrobbin <hrobbin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 14:51:51 by hrobbin           #+#    #+#             */
/*   Updated: 2020/11/16 18:56:22 by hrobbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	k;

	k = 0;
	if (ft_strlen(needle) == 0 || needle == NULL)
		return ((char*)haystack);
	while (k < len)
	{
		if ((ft_strncmp((char *)&haystack[k], needle,
						ft_strlen(needle))) == 0)
		{
			if (ft_strlen(needle) + k > len)
				return (NULL);
			return ((char *)&haystack[k]);
		}
		k++;
	}
	return (NULL);
}
