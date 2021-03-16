/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_additional.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrobbin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 00:00:21 by hrobbin           #+#    #+#             */
/*   Updated: 2021/03/16 00:00:22 by hrobbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int		key_hook(int keycode, t_info *info)
{
	static int	i;

	if (keycode == ESC)
		exit_free(info, 0);
	if (keycode == TAB)
	{
		i++;
		if (i >= info->cams)
			i = 0;
		mlx_put_image_to_window(info->mlx, info->win, info->img[i].img, 0, 0);
	}
	return (0);
}

int		w_close(t_info *info)
{
	exit_free(info, 0);
	return (0);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char		*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	xy_size_check(t_scene *scene, void *mlx)
{
	int			w;
	int			h;

	mlx_get_screen_size(mlx, &w, &h);
	if (scene->width > w)
		scene->width = w;
	if (scene->height > h)
		scene->height = h;
}
