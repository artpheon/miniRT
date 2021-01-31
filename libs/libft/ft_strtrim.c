/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrobbin <hrobbin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 19:37:36 by hrobbin           #+#    #+#             */
/*   Updated: 2020/11/26 16:56:14 by hrobbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*new;
	size_t	size;

	if (!s1 || !set)
		return (NULL);
	while (*s1 && ft_strchr(set, *s1))
		s1++;
	size = ft_strlen(s1);
	if (size == 0)
		return (new = ft_strdup("\0"));
	while (*s1 && ft_strchr(set, s1[size]))
		size--;
	new = ft_substr(s1, 0, size + 1);
	return (new);
}