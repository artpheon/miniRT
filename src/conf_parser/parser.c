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

t_config *alloc_conf()
{
	t_config *conf;

	if (!(conf = (t_config *)malloc(sizeof(t_config))))
		close_app("Could not allocate memory for t_config", 1);
	conf->object = NULL;
	conf->light = NULL;
	conf->camera = NULL;
	return(conf);
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

t_resolution get_resolution(char *line)
{
	t_resolution new;

	line++;
	new.width = ft_atoi(line);
	line = skip_num(line);
	new.height = ft_atoi(line);
	return (new);
}

float ft_atof(const char *st)
{
	float	res1;
	float	res2;

	while (ft_isspace(*st))
		st++;
	res1 = (float)ft_atoi(st);
	while (*st && *st != '.')
		st++;
	if (*st == '.')
		st++;
	res2 = (float)ft_atoi(st);
	while ((int)res2 != 0)
		res2 /= 10;
	return (res1 + ((res1 > 0) ? res2 : -res2));
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
	t_list *new;
	t_camera *new_cam;

	line++;
	if (!(new_cam = (t_camera *)malloc(sizeof(t_camera))))
		close_app("Could not allocate memory for camera", 1);
	new_cam->origin_coord = str_to_three(line);
	line = skip_num(line);
	new_cam->vector_norm = str_to_three(line);
	line = skip_num(line);
	new_cam->fov = (char)ft_atoi(line);
	new = ft_lstnew(new_cam);
	return (new);
}

t_list *get_light(char *line)
{
	t_list *new;
	t_light *new_light;

	line++;
	if (!(new_light = (t_light *)malloc(sizeof(t_light))))
		close_app("Could not allocate memory for light", 1);
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
		close_app("Could not allocate memory for an object", 1);
	ft_strlcpy(new_obj->type, "sp", 3);
	new_obj->origin_coord = str_to_three(line);
	line = skip_num(line);
	new_obj->sphere_diam = (float)ft_atof(line);
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
		close_app("Could not allocate memory for an object", 1);
	ft_strlcpy(new_obj->type, "pl", 3);
	new_obj->origin_coord = str_to_three(line);
	line = skip_num(line);
	new_obj->vector_norm = str_to_three(line);
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
		close_app("Could not allocate memory for an object", 1);
	ft_strlcpy(new_obj->type, "sq", 3);
	new_obj->origin_coord = str_to_three(line);
	line = skip_num(line);
	new_obj->vector_norm = str_to_three(line);
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
		close_app("Could not allocate memory for an object", 1);
	ft_strlcpy(new_obj->type, "cy", 3);
	new_obj->origin_coord = str_to_three(line);
	line = skip_num(line);
	new_obj->vector_norm = str_to_three(line);
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
		close_app("Could not allocate memory for an object", 1);
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

void fill_conf(t_config **config, char *line)
{
	t_config *conf;

	conf = *config;
	while (ft_isspace(*line))
		line++;
	if (*line == 'R')
		conf->res = get_resolution(line);
	else if (*line == 'A')
		conf->ambl = get_ambient(line);
	else if (*line == 'c' && line[1] != 'y')
		ft_lstadd_back(&(conf->camera), get_camera(line));
	else if (*line == 'l')
		ft_lstadd_back(&(conf->light), get_light(line));
	else if (*line == 's' && line[1] == 'p')
		ft_lstadd_back(&(conf->object), get_sphere(line));
	else if (*line == 'p' && line[1] == 'l')
		ft_lstadd_back(&(conf->object), get_plane(line));
	else if (*line == 's' && line[1] == 'q')
		ft_lstadd_back(&(conf->object), get_square(line));
	else if (*line == 'c' && line[1] == 'y')
		ft_lstadd_back(&(conf->object), get_cylinder(line));
	else if (*line == 't' && line[1] == 'r')
		ft_lstadd_back(&(conf->object), get_triangle(line));
}

t_config *parser(char *file)
{
	int			fd;
	int			read_return;
	char		*line;
	t_config	*new;

	printf("___file: \"%s\"___\n", file);
	line = NULL;
	if (-1 == (fd = open(file, O_RDONLY)))
	{
		perror("Cannot open file passed as argument");
		exit(EXIT_FAILURE);
	}
	new = alloc_conf();
	while (-1 < (read_return = get_next_line(&line, fd)))
	{
		//printf("%s\n", line);
		fill_conf(&new, line);
		free(line);
		if (read_return == 0)
			break ;
	}
	if (read_return == -1)
	{
		perror("Cannot read file");
		exit(EXIT_FAILURE);
	}
	close(fd);
	return(new);
}