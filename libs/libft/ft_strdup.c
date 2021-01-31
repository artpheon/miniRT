/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrobbin <hrobbin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 18:28:41 by hrobbin           #+#    #+#             */
/*   Updated: 2020/11/16 18:00:11 by hrobbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*newstr;
	int		len;
	int		i;

	len = 0;
	i = 0;
	while (s1[len])
		len++;
	if ((newstr = (char *)malloc(len + 1)) == NULL)
		return (NULL);
	while (s1[i])
	{
		newstr[i] = s1[i];
		i++;
	}
	newstr[i] = '\0';
	return (newstr);
}
