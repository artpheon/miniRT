/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrobbin <hrobbin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 13:09:40 by hrobbin           #+#    #+#             */
/*   Updated: 2020/11/26 16:55:33 by hrobbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**clear(char **arr, int word)
{
	while (word != 0)
	{
		free(arr[word]);
		word--;
	}
	return (arr);
}

static int	words(const char *s, char d)
{
	int			count;
	const char	*tmp;

	count = 0;
	tmp = s;
	while (*tmp)
	{
		while (ft_strchr(tmp, d) != tmp && *tmp)
			tmp++;
		count++;
		while (ft_strchr(tmp, d) == tmp && *tmp)
			tmp++;
	}
	if (s == tmp)
		return (0);
	else
		return (count);
}

char		**ft_split(char const *s, char c)
{
	char		**split;
	int			i;
	int			w;

	w = 0;
	i = 0;
	if (!s || !(split = (char **)ft_calloc((words(s, c) + 1), sizeof(char *))))
		return (NULL);
	while (*s)
	{
		while (ft_strchr(s, c) == s && *s)
			s++;
		while (ft_strchr(s, c) != s && *s)
		{
			s++;
			i++;
		}
		if (*s == '\0' && i == 0)
			break ;
		if (!(split[w] = ft_substr((s - i), 0, i)))
			return (clear(split, w));
		w++;
		i = 0;
	}
	return (split);
}
