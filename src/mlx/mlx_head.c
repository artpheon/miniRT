//
// Created by Howe Robbin on 1/28/21.
//

#include "header.h"

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

t_vplane	*get_new_plane(float width, float height, float fov)
{
	t_vplane *plane;
	float	asp_ratio;

	if (NULL == (plane = malloc(sizeof(t_vplane))))
		close_app("Could not allocate mem for view plane", -1);
	asp_ratio = width / height;
	plane->width = 1;
	plane->height = plane->width / asp_ratio;
	plane->x_pixel = plane->width / width;
	plane->y_pixel = plane->height / height;
	fov = 1; //fix
	return (plane);
}

int sphere_inter()
{
// 4 part, 1st
}

void trace_ray(void *mlx, void *window, t_config *config)
{
    int mlx_x, mlx_y;
    float angle_x, angle_y;
	float x_ray, y_ray;
    int color;
	t_vector ray;
	t_vplane *new_plane;
	
	mlx_y = 0;
	new_plane = get_new_plane(config->res.width, 
							  config->res.height, 
							  ((t_camera *)(config->camera->content))->fov);
	angle_y = (config->res.height) / 2;
	while (angle_y >= (config->res.height / 2) * (-1))
	{
		y_ray = angle_y * new_plane->y_pixel;
		angle_x = (config->res.width / 2) * (-1);
		mlx_x = 0;
		while (angle_x <= (config->res.width / 2))
		{
			x_ray = angle_x * new_plane->x_pixel;
			ray.x = x_ray;
			ray.y = y_ray;
			ray.z = -1;
			ray = norm_vector(ray);
			if (sphere_inter(config->camera->content, ray, config->object->next->content))
				color = 16777215;
			else
				color = 0;
			mlx_pixel_put(mlx, window, mlx_x, mlx_y, color);
			angle_x++;
			mlx++;
		}
		angle_y--;
		mlx_y++;
	}
    
}