//
// Created by Howe Robbin on 1/20/21.
//

#include "header.h"

int get_next_line(char **line, int fd)
{
	char buff;
	char buffer[1000];
	int rfd;
	int k;

	k = 0;
	buff = '\0';
	*buffer = 0;
	while (buff != '\n')
	{
		rfd = read(fd, &buff, 1);
		if (rfd == -1)
			return (rfd);
		if (rfd == 0)
		{
			*line = ft_strdup(buffer);
			return (rfd);
		}
		else
		{
			if (buff != '\n')
				buffer[k] = buff;
			k++;
			buffer[k] = 0;
		}
	}
	*line = ft_strdup(buffer);
	return (1);
}

int ft_isspace(char c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}

t_scene *alloc_scene()
{
	t_scene *scene;

	if (!(scene = (t_scene *)malloc(sizeof(t_scene))))
		exit_error("Could not allocate memory for t_scene", 1);
	scene->height = 0;
	scene->width = 0;
	scene->ambl.ratio = -1;
	scene->object = NULL;
	scene->light = NULL;
	scene->camera = NULL;
	return (scene);
}

void	p_check_n(t_vector *n)
{
	if (n->x > 1 || n->x < 0)
		exit_error("Scene has wrong normalized orientation v3.", -1);
	if (n->y > 1 || n->y < 0)
		exit_error("Scene has wrong normalized orientation v3.", -1);
	if (n->z > 1 || n->z < 0)
		exit_error("Scene has wrong normalized orientation v3.", -1);
}

char *skip_num(char *str)
{
	while (ft_isspace(*str))
		str++;
	if (*str == 43 || *str == 45)
		str++;
	while (ft_isdigit(*str) || *str == '.' || *str == ',')
		str++;
	if (*str == 43 || *str == 45)
		str++;
	while (ft_isdigit(*str) || *str == '.' || *str == ',')
		str++;
	if (*str == 43 || *str == 45)
		str++;
	while (ft_isdigit(*str) || *str == '.' || *str == ',')
		str++;
	return (str);
}

void get_resolution(t_scene *scene, char *line)
{
	if (*line == 'R')
		line++;
	scene->width = ft_atoi(line);
	line = skip_num(line);
	scene->height = ft_atoi(line);
}

float ft_atof(const char *st)
{
	float	res1;
	float	res2;
	int 	sign;
	char	*tmp;

	sign = 1;
	res1 = (float)ft_atoi(st);
	res2 = 0;
	tmp = (char *)st;
	if (*tmp == '-')
	{
		sign = -1;
		tmp++;
	}
	while (*tmp && (ft_isdigit(*tmp) || ft_isspace(*tmp)))
		tmp++;
	if (*tmp == '.')
	{
		tmp++;
		res2 = (float)ft_atoi(tmp);
		while ((int)res2 != 0)
		res2 /= 10;
	}
	res2 = sign < 0 ? -res2 : res2;
	return (res1 + res2);
}

t_vector str_to_three(const char *str)
{
	t_vector new;

	new.x = (float)ft_atof(str);
	while (*str != ',')
		str++;
	if (*str == ',')
		str++;
	new.y = (float)ft_atof(str);
	while (*str != ',')
		str++;
	if (*str == ',')
		str++;
	new.z = (float)ft_atof(str);
	return (new);
}

t_ambient get_ambient(char *line)
{
	t_ambient new;

	line++;
	new.ratio = (float)ft_atof(line);
	line = skip_num(line);
	new.colour = str_to_three(line);
	return (new);
}

t_list	*get_camera(char *line)
{
	t_list		*new;
	t_camera	*new_cam;

	line++;
	
	if (!(new_cam = (t_camera *)malloc(sizeof(t_camera))))
		exit_error("Could not allocate memory for camera", 1);
	new_cam->origin_coord = str_to_three(line);
	line = skip_num(line);
	new_cam->vector_norm = str_to_three(line);
	line = skip_num(line);
	new_cam->fov = ft_atoi(line);
	if (new_cam->fov < 1)
		exit_error("Camera FOV is wrong.", -1);
	if (new_cam->fov < 35)
		perror("Camera FOV might be too low.");
	new = ft_lstnew(new_cam);
	return (new);
}

t_list *get_light(char *line)
{
	t_list *new;
	t_light *new_light;

	line++;
	if (!(new_light = (t_light *)malloc(sizeof(t_light))))
		exit_error("Could not allocate memory for light", 1);
	new_light->origin_coord = str_to_three(line);
	line = skip_num(line);
	new_light->ratio = (float)ft_atof(line);
	line = skip_num(line);
	new_light->rgb = str_to_three(line);
	new = ft_lstnew(new_light);
	return (new);
}

t_list *get_sphere(char *line)
{
	t_list *new;
	t_object *new_obj;

	line += 2;
	if (!(new_obj = (t_object *)malloc(sizeof(t_object))))
		exit_error("Could not allocate memory for an object", 1);
	ft_strlcpy(new_obj->type, "sp", 3);
	new_obj->origin_coord = str_to_three(line);
	line = skip_num(line);
	new_obj->sp_radius = (float)ft_atof(line) / 2;
	if (new_obj->sp_radius <= 0)
		exit_error("Sphere radius is too small.", -1);
	line = skip_num(line);
	new_obj->rgb = str_to_three(line);
	new = ft_lstnew(new_obj);
	return (new);
}

t_list *get_plane(char *line)
{
	t_list *new;
	t_object *new_obj;

	line += 2;
	if (!(new_obj = (t_object *)malloc(sizeof(t_object))))
		exit_error("Could not allocate memory for an object", 1);
	ft_strlcpy(new_obj->type, "pl", 3);
	new_obj->origin_coord = str_to_three(line);
	line = skip_num(line);
	new_obj->vector_norm = str_to_three(line);
	p_check_n(&new_obj->vector_norm);
	line = skip_num(line);
	new_obj->rgb = str_to_three(line);
	new = ft_lstnew(new_obj);
	return (new);
}

t_list *get_square(char *line)
{
	t_list *new;
	t_object *new_obj;

	line += 2;
	if (!(new_obj = (t_object *)malloc(sizeof(t_object))))
		exit_error("Could not allocate memory for an object", 1);
	ft_strlcpy(new_obj->type, "sq", 3);
	new_obj->origin_coord = str_to_three(line);
	line = skip_num(line);
	new_obj->vector_norm = str_to_three(line);
	p_check_n(&new_obj->vector_norm);
	line = skip_num(line);
	new_obj->side_size = (float)ft_atof(line);
	line = skip_num(line);
	new_obj->rgb = str_to_three(line);
	new = ft_lstnew(new_obj);
	return (new);
}

t_list *get_cylinder(char *line)
{
	t_list *new;
	t_object *new_obj;

	line += 2;
	if (!(new_obj = (t_object *)malloc(sizeof(t_object))))
		exit_error("Could not allocate memory for an object", 1);
	ft_strlcpy(new_obj->type, "cy", 3);
	new_obj->origin_coord = str_to_three(line);
	line = skip_num(line);
	new_obj->vector_norm = str_to_three(line);
	p_check_n(&new_obj->vector_norm);
	line = skip_num(line);
	new_obj->cyl_d = (float)ft_atof(line);
	line = skip_num(line);
	new_obj->cyl_h = (float)ft_atof(line);
	line = skip_num(line);
	new_obj->rgb = str_to_three(line);
	new = ft_lstnew(new_obj);
	return (new);
}

t_list *get_triangle(char *line)
{
	t_list *new;
	t_object *new_obj;

	line += 2;
	if (!(new_obj = (t_object *)malloc(sizeof(t_object))))
		exit_error("Could not allocate memory for an object", 1);
	ft_strlcpy(new_obj->type, "tr", 3);
	new_obj->origin_coord = str_to_three(line);
	line = skip_num(line);
	new_obj->trian2 = str_to_three(line);
	line = skip_num(line);
	new_obj->trian3 = str_to_three(line);
	line = skip_num(line);
	new_obj->rgb = str_to_three(line);
	new = ft_lstnew(new_obj);
	return (new);
}

void fill_scene(t_scene *scene, char *line)
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

void 	p_first_check(int fd, char *name)
{
	if (fd < 0)
		exit_error("Cannot open file passed as argument.", -1);
	if (ft_strlen(name) < 4)
		exit_error("Filename too short.", -1);
	while (*name)
		name++;
	name -= 3;
	if (ft_strncmp(name, ".rt", 3))
		exit_error("Wrong file extension.", -1);
}

void 	p_second_check(int ret, t_scene *scene)
{
	if (ret == -1)
		exit_error("Cannot read file", -1);
	if (scene->width < 1 || scene->height < 1)
		exit_error("Window width or height values are too small", -1);
	if (scene->camera == NULL || scene->camera->content == NULL)
		exit_error("No cameras on the scene.", -1);
	if (scene->ambl.ratio < 0)
		exit_error("Wrong ambient(ratio below zero).", -1);
}

t_scene *parser(char *file)
{
	int			fd;
	int			read_return;
	char		*line;
	t_scene		*new;

	printf("___file: \"%s\"___\n", file);
	line = NULL;
	fd = open(file, O_RDONLY);
	p_first_check(fd, file);
	new = alloc_scene();
	while (-1 < (read_return = get_next_line(&line, fd)))
	{
		fill_scene(new, line);
		free(line);
		if (read_return == 0)
			break ;
	}
	p_second_check(read_return, new);
	close(fd);
	return (new);
}