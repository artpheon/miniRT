/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrobbin <hrobbin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 12:29:05 by hrobbin           #+#    #+#             */
/*   Updated: 2020/11/26 16:13:33 by hrobbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*dest;
	unsigned int	i;

	i = 0;
	if (!s)
		return (NULL);
	if (NULL == (dest = ft_strdup(s)))
		return (NULL);
	while (s[i] != '\0')
	{
		dest[i] = f(i, dest[i]);
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
