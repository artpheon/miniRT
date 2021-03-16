/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrobbin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 00:01:17 by hrobbin           #+#    #+#             */
/*   Updated: 2021/03/16 00:01:18 by hrobbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	start_render_init(t_info *info, t_scene *scene)
{
	info->mlx = mlx_init();
	xy_size_check(scene, info->mlx);
	info->cams = ft_lstsize(scene->camera);
}

void	start_render_imgs(t_info *info, t_scene *s, t_list *cam_start)
{
	int		i;

	i = 0;
	info->img = malloc(sizeof(t_data) * info->cams);
	info->win = mlx_new_window(info->mlx, s->width, s->height, "miniRT");
	while (i < info->cams)
	{
		info->img[i].img = mlx_new_image(info->mlx, s->width, s->height);
		info->img[i].addr = mlx_get_data_addr(info->img[i].img,
							&info->img[i].bits_per_pixel,
							&info->img[i].line_length,
							&info->img[i].endian);
		put_rays(info->scene, &info->img[i], i);
		s->camera = s->camera->next;
		i++;
	}
	s->camera = cam_start;
	mlx_put_image_to_window(info->mlx, info->win, info->img[0].img, 0, 0);
	mlx_hook(info->win, 17, 0, w_close, info);
	mlx_hook(info->win, 2, 0, key_hook, info);
	mlx_loop(info->mlx);
}

void	start_render(t_info *info)
{
	t_list	*start;

	start_render_init(info, info->scene);
	start = info->scene->camera;
	if (info->sshot)
		shoot_screen(info);
	else
		start_render_imgs(info, info->scene, start);
}

void	counter_on(int height, int row)
{
	if (height < 20)
		height = 20;
	if (((row % (height / 20)) == 0))
		ft_putstr_fd(GRN"="RESET, 1);
}

void	put_rays(t_scene *scene, t_data *img, int i)
{
	int		canvas[2];
	int		vp[2];
	int		colour;
	t_ray	ray;

	canvas[1] = 0;
	vp[1] = scene->height / 2;
	printf("Rendering camera #%d: [", i + 1);
	while (vp[1] > scene->height / 2 * (-1))
	{
		vp[0] = scene->width / 2 * (-1);
		canvas[0] = 0;
		while (vp[0] < scene->width / 2)
		{
			ray = gen_ray(vp[0], vp[1], scene);
			colour = ray_trace(&ray, scene);
			my_mlx_pixel_put(img, canvas[0], canvas[1], colour);
			vp[0]++;
			canvas[0]++;
		}
		counter_on(scene->height, canvas[1]);
		vp[1]--;
		canvas[1]++;
	}
	write(1, "]\n", 2);
}
