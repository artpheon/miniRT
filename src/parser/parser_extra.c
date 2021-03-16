/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_extra.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrobbin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 00:00:43 by hrobbin           #+#    #+#             */
/*   Updated: 2021/03/16 00:27:56 by hrobbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int		get_next_line(char *line, int fd)
{
	char	buff;
	int		rfd;
	int		k;

	k = 0;
	buff = '\0';
	while (buff != '\n')
	{
		rfd = read(fd, &buff, 1);
		if (rfd == -1)
			return (rfd);
		if (rfd == 0)
			return (rfd);
		else
		{
			if (buff != '\n')
				line[k] = buff;
			k++;
			line[k] = 0;
		}
	}
	return (1);
}

char	*skip_1num(char *str)
{
	while (ft_isspace(*str))
		str++;
	if (*str == '-' || *str == '+')
		str++;
	while (ft_isdigit(*str))
		str++;
	if (*str == '.')
	{
		str++;
		while (ft_isdigit(*str))
			str++;
	}
	while (ft_isspace(*str))
		str++;
	return (str);
}

char	*skip_3num(char *str)
{
	str = skip_1num(str);
	str++;
	str = skip_1num(str);
	str++;
	str = skip_1num(str);
	return (str);
}

void	str_to_three(char *str, t_vector *new)
{
	new->x = ft_atof(str);
	str = skip_1num(str);
	if (*str == ',')
		str++;
	else
		exit_error("wrong symbol among triples of numbers", -1);
	new->y = ft_atof(str);
	str = skip_1num(str);
	if (*str == ',')
		str++;
	else
		exit_error("wrong symbol among triples of numbers", -1);
	new->z = ft_atof(str);
}
