/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrobbin <hrobbin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 14:51:51 by hrobbin           #+#    #+#             */
/*   Updated: 2020/11/16 18:03:27 by hrobbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(char *s, int c)
{
	int		i;
	char	*ptr;

	ptr = NULL;
	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			ptr = &(s[i]);
		i++;
	}
	if (c == '\0')
		return (ptr = &(s[i]));
	return (ptr);
}
