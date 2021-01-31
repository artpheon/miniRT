/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrobbin <hrobbin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 18:02:26 by hrobbin           #+#    #+#             */
/*   Updated: 2020/11/26 16:55:05 by hrobbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*dest;

	if (!s)
		return (NULL);
	if (start > ft_strlen(s) || len == 0)
		return (dest = ft_strdup("\0"));
	if ((dest = (char *)malloc(len + 1)) == NULL)
		return (NULL);
	ft_strlcpy(dest, (s + start), (len + 1));
	return (dest);
}