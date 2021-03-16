/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_param1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrobbin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 00:00:54 by hrobbin           #+#    #+#             */
/*   Updated: 2021/03/16 00:00:55 by hrobbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void		get_resolution(t_scene *scene, char *line)
{
	if (*line == 'R')
		line++;
	scene->width = ft_atoi(line);
	line = skip_1num(line);
	scene->height = ft_atoi(line);
}

t_ambient	get_ambient(char *line)
{
	t_ambient	new;

	line++;
	new.ratio = ft_atof(line);
	lr_check(new.ratio);
	line = skip_1num(line);
	str_to_three(line, &new.colour);
	return (new);
}

t_list		*get_camera(char *line)
{
	t_list		*new;
	t_camera	*new_cam;

	line++;
	if (!(new_cam = (t_camera *)malloc(sizeof(t_camera))))
		exit_error(MFAIL, -1);
	str_to_three(line, &new_cam->orig);
	line = skip_3num(line);
	str_to_three(line, &new_cam->normal);
	normalize(&new_cam->normal);
	line = skip_3num(line);
	new_cam->fov = ft_atoi(line);
	if (new_cam->fov < 1 || new_cam->fov > 180)
		exit_error("Camera FOV is wrong.", -1);
	if (new_cam->fov < 35)
		perror("Camera FOV might be too low.");
	new = ft_lstnew(new_cam);
	return (new);
}

t_list		*get_light(char *line)
{
	t_list		*new;
	t_light		*new_light;

	line++;
	if (!(new_light = (t_light *)malloc(sizeof(t_light))))
		exit_error(MFAIL, -1);
	str_to_three(line, &new_light->orig);
	line = skip_3num(line);
	new_light->ratio = ft_atof(line);
	lr_check(new_light->ratio);
	line = skip_1num(line);
	str_to_three(line, &new_light->rgb);
	new = ft_lstnew(new_light);
	return (new);
}

t_list		*get_sphere(char *line)
{
	t_list		*new;
	t_object	*new_obj;

	line += 2;
	if (!(new_obj = (t_object *)malloc(sizeof(t_object))))
		exit_error(MFAIL, -1);
	ft_strlcpy(new_obj->type, "sp", 3);
	str_to_three(line, &new_obj->orig);
	line = skip_3num(line);
	new_obj->sp_radius = ft_atof(line) / 2;
	if (new_obj->sp_radius <= 0)
		exit_error("Sphere radius is too small.", -1);
	line = skip_1num(line);
	str_to_three(line, &new_obj->rgb);
	new = ft_lstnew(new_obj);
	return (new);
}
