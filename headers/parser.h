

int get_next_line(char **line, int fd);
t_scene *parser(char *file);
float ft_atof(char *st);
t_ambient get_ambient(char *line);
void str_to_three(char *str, t_vector *new);
char *skip_3num(char *str);
char *skip_1num(char *str);