/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_param2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrobbin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 00:00:59 by hrobbin           #+#    #+#             */
/*   Updated: 2021/03/16 17:38:39 by hrobbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static t_vector	get_tr_normal(t_object *tr)
{
	t_vector	u;
	t_vector	v;
	t_vector	norm;

	u = v3_sub(tr->angle2, tr->orig);
	v = v3_sub(tr->angle3, tr->orig);
	norm = v3_cross(u, v);
	normalize(&norm);
	return (norm);
}

t_list			*get_plane(char *line)
{
	t_list		*new;
	t_object	*new_obj;

	line += 2;
	if (!(new_obj = (t_object *)malloc(sizeof(t_object))))
		exit_error(MFAIL, -1);
	ft_strlcpy(new_obj->type, "pl", 3);
	str_to_three(line, &new_obj->orig);
	line = skip_3num(line);
	str_to_three(line, &new_obj->normal);
	p_check_n(&new_obj->normal);
	normalize(&new_obj->normal);
	line = skip_3num(line);
	str_to_three(line, &new_obj->rgb);
	new = ft_lstnew(new_obj);
	return (new);
}

t_list			*get_square(char *line)
{
	t_list		*new;
	t_object	*new_obj;

	line += 2;
	if (!(new_obj = (t_object *)malloc(sizeof(t_object))))
		exit_error(MFAIL, -1);
	ft_strlcpy(new_obj->type, "sq", 3);
	str_to_three(line, &new_obj->orig);
	line = skip_3num(line);
	str_to_three(line, &new_obj->normal);
	p_check_n(&new_obj->normal);
	normalize(&new_obj->normal);
	line = skip_3num(line);
	new_obj->side_size = (float)ft_atof(line);
	line = skip_1num(line);
	str_to_three(line, &new_obj->rgb);
	new = ft_lstnew(new_obj);
	return (new);
}

t_list			*get_cylinder(char *line)
{
	t_list		*new;
	t_object	*new_obj;

	line += 2;
	if (!(new_obj = (t_object *)malloc(sizeof(t_object))))
		exit_error(MFAIL, -1);
	ft_strlcpy(new_obj->type, "cy", 3);
	str_to_three(line, &new_obj->orig);
	line = skip_3num(line);
	str_to_three(line, &new_obj->normal);
	p_check_n(&new_obj->normal);
	normalize(&new_obj->normal);
	line = skip_3num(line);
	new_obj->cyl_d = (float)ft_atof(line);
	line = skip_1num(line);
	new_obj->cyl_h = (float)ft_atof(line);
	line = skip_1num(line);
	str_to_three(line, &new_obj->rgb);
	new = ft_lstnew(new_obj);
	return (new);
}

t_list			*get_triangle(char *line)
{
	t_list		*new;
	t_object	*new_obj;

	line += 2;
	if (!(new_obj = (t_object *)malloc(sizeof(t_object))))
		exit_error(MFAIL, -1);
	ft_strlcpy(new_obj->type, "tr", 3);
	str_to_three(line, &new_obj->orig);
	line = skip_3num(line);
	str_to_three(line, &new_obj->angle2);
	line = skip_3num(line);
	str_to_three(line, &new_obj->angle3);
	if (v3cmp(new_obj->orig, new_obj->angle2) ||
		v3cmp(new_obj->angle2, new_obj->angle3) ||
		v3cmp(new_obj->angle3, new_obj->orig))
		exit_error("Triangle has impossible coordinates", -1);
	line = skip_3num(line);
	str_to_three(line, &new_obj->rgb);
	new_obj->normal = get_tr_normal(new_obj);
	new = ft_lstnew(new_obj);
	return (new);
}
