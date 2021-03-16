/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_basic.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrobbin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 00:00:30 by hrobbin           #+#    #+#             */
/*   Updated: 2021/03/16 00:00:32 by hrobbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

t_scene		*alloc_scene(void)
{
	t_scene *scene;

	if (!(scene = (t_scene *)malloc(sizeof(t_scene))))
		exit_error(MFAIL, -1);
	scene->height = 0;
	scene->width = 0;
	scene->ambl.ratio = -1;
	scene->object = NULL;
	scene->light = NULL;
	scene->camera = NULL;
	return (scene);
}

void		fill_scene(t_scene *scene, char *line)
{
	while (ft_isspace(*line))
		line++;
	if (*line == 'R')
		get_resolution(scene, line);
	else if (*line == 'A')
		scene->ambl = get_ambient(line);
	else if (*line == 'c' && line[1] != 'y')
		ft_lstadd_back(&(scene->camera), get_camera(line));
	else if (*line == 'l')
		ft_lstadd_back(&(scene->light), get_light(line));
	else if (*line == 's' && line[1] == 'p')
		ft_lstadd_back(&(scene->object), get_sphere(line));
	else if (*line == 'p' && line[1] == 'l')
		ft_lstadd_back(&(scene->object), get_plane(line));
	else if (*line == 's' && line[1] == 'q')
		ft_lstadd_back(&(scene->object), get_square(line));
	else if (*line == 'c' && line[1] == 'y')
		ft_lstadd_back(&(scene->object), get_cylinder(line));
	else if (*line == 't' && line[1] == 'r')
		ft_lstadd_back(&(scene->object), get_triangle(line));
	else if (*line == '#' || *line == '\0')
		return ;
	else
		exit_error("Parser reading error. Undefined symbol in the line.", -1);
}

t_scene		*parser(char *file)
{
	int			fd;
	int			read_return;
	char		*line;
	t_scene		*new;

	if (NULL == (line = malloc(1000)))
		exit_error(MFAIL, -1);
	fd = open(file, O_RDONLY);
	p_first_check(fd, file);
	new = alloc_scene();
	while (0 < (read_return = get_next_line(&line, fd)))
		fill_scene(new, line);
	if (read_return == -1)
		exit_error("Error while reading from FD", -1);
	p_second_check(read_return, new);
	free(line);
	close(fd);
	return (new);
}
