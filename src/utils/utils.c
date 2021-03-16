/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrobbin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 00:01:34 by hrobbin           #+#    #+#             */
/*   Updated: 2021/03/16 17:38:21 by hrobbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

t_vector	set_vector(float x, float y, float z)
{
	t_vector	new;

	new.x = x;
	new.y = y;
	new.z = z;
	return (new);
}

t_ray		set_ray(t_vector origin, t_vector dir)
{
	t_ray		new;

	new.orig = origin;
	new.dir = dir;
	normalize(&new.dir);
	return (new);
}

void		exit_error(char *message, int errn)
{
	write(2, "Error\n", 6);
	write(2, message, ft_strlen(message));
	exit(errn);
}

void		exit_free(t_info *info, int sshot)
{
	int			i;

	i = 0;
	ft_lstclear(&(info->scene->camera), (void *)free);
	ft_lstclear(&(info->scene->light), (void *)free);
	ft_lstclear(&(info->scene->object), (void *)free);
	free(info->scene);
	while (i < info->cams)
	{
		mlx_destroy_image(info->mlx, info->img[i].img);
		i++;
	}
	free(info->img);
	if (!sshot)
		mlx_destroy_window(info->mlx, info->win);
	else
	{
		ft_putstr_fd("Saved screenshot: ", 1);
		ft_putstr_fd(GRN"save_image.bmp\n"RESET, 1);
	}
	free(info);
	exit(EXIT_SUCCESS);
}

int			typecmp(char *t, t_object *o)
{
	if (ft_strncmp(o->type, t, 2) == 0)
		return (1);
	return (0);
}
