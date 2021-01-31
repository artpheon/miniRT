//
// Created by Howe Robbin on 1/28/21.
//

#include "mlx_head.h"

void 	my_mlx_pixel_put(t_data *data, int x, int y, int colour)
{
	char *dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = colour;
}

void show_red_win()
{
	void *mlx;
	void *mlx_win;
	t_data img;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 500, 600, "NEW WINDOW");
	img.img = mlx_new_image(mlx, 500, 600);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img
			.line_length, &img.endian);
	for (int x = 0; x < 500; x++)
	{
		for (int y = 0; y < 600; y++)
		{
			my_mlx_pixel_put(&img, x, y, 0x00FF0000);
		}
	}
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);
}