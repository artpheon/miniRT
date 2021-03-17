/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrobbin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 00:00:37 by hrobbin           #+#    #+#             */
/*   Updated: 2021/03/16 00:00:38 by hrobbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void		p_check_n(t_vector *n)
{
	if (n->x > 1 || n->x < -1)
		exit_error("Scene has wrong normalized orientation v3.", -1);
	if (n->y > 1 || n->y < -1)
		exit_error("Scene has wrong normalized orientation v3.", -1);
	if (n->z > 1 || n->z < -1)
		exit_error("Scene has wrong normalized orientation v3.", -1);
}

void		lr_check(float f)
{
	if (f < 0)
		exit_error("Ratio value is too low", -1);
	if (f > 1)
		exit_error("Ratio value is too big", -1);
}

void		p_first_check(int fd, char *name)
{
	if (fd < 0)
		exit_error("No such file, or cannot open it", -1);
	if (ft_strlen(name) < 4)
		exit_error("Filename too short.", -1);
	while (*name)
		name++;
	while (*name != '.')
		name--;
	if (ft_strncmp(name, ".rt\0", 4))
		exit_error("Wrong file extension.", -1);
}

void		p_second_check(int ret, t_scene *scene)
{
	if (ret == -1)
		exit_error("Cannot read file", -1);
	if (scene->width < 1 || scene->height < 1)
		exit_error("Wrong values for window width or height", -1);
	if (scene->camera == NULL || scene->camera->content == NULL)
		exit_error("No cameras on the scene.", -1);
	if (scene->ambl.ratio < 0)
		exit_error("Wrong ambient(ratio below zero).", -1);
}
