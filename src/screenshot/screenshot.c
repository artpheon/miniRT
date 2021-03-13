//
// Created by Howe Robbin on 3/13/21.
//

#include "header.h"

void	make_header(int fd, int w, int h)
{
	char			head[54];
	int				i;
	i = 0;
	while (i < 54)
	{
		head[i] = 0x00;
		i++;
	}
	head[0] = 0x42;
	head[1] = 0x4D;
	head[10] = 0x36;
	head[14] = 0x28;
	head[18] = (char)((w & 0x000000FF) >> 0);
	head[19] = (char)((w & 0x0000FF00) >> 8);
	head[20] = (char)((w & 0x00FF0000) >> 16);
	head[21] = (char)((h & 0xFF000000) >> 24);
	head[22] = (char)((h & 0x000000FF) >> 0);
	head[23] = (char)((h & 0x0000FF00) >> 8);
	head[24] = (char)((h & 0x00FF0000) >> 16);
	head[25] = (char)((h & 0xFF000000) >> 24);
	head[26] = 0x01;
	head[28] = 0x20;
	write(fd, head, 54);
}

unsigned int	my_mlx_pixel_get(t_data *data, int x, int y)
{
	unsigned int colour;

	colour = *(unsigned int*)(data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8)));
	return (colour);
}

void	writedata(int w, int h, t_data *img_data, int fd)
{
	char	clr[4];
	unsigned colour;
	int width;
	int height;

	height = h;
	while (--height >= 0)
	{
		width = -1;
		while (++width < w)
		{
			colour = *(unsigned int*)(img_data->addr + (height * img_data->line_length + width * (img_data->bits_per_pixel / 8)));
			clr[0] = colour >> 0;
			clr[1] = colour >> 8;
			clr[2] = colour >> 16;
			clr[3] = 0;
			write(fd, clr, 4);
		}
	}
}

int		writebmp(int w, int h, t_data *img_data)
{
	int				fd;

	fd = open("save_image.bmp", O_WRONLY | O_CREAT | O_TRUNC, \
		S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
	make_header(fd, w, h);
	writedata(w, h, img_data, fd);
	close(fd);
	return (0);
}

void	shoot_screen(t_info *info)
{
	t_scene *scene;

	scene = info->scene;
	info->cams = 1;
	info->img = malloc(sizeof(t_data));
	info->img->img = mlx_new_image(info->mlx, scene->width, scene->height); // создаем имидж
	info->img->addr = mlx_get_data_addr(info->img->img,
									  &info->img->bits_per_pixel,
									  &info->img->line_length,
									  &info->img->endian);
	put_rays(info->scene, info->img);
	writebmp(scene->width, scene->height, info->img);
	exit_free(info);
}