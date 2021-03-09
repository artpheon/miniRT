#ifndef UTILS_H
# define UTILS_H

t_vector	set_vector(float x, float y, float z);
t_ray		set_ray(t_vector origin, t_vector dir);
void		strrev(char *s);
float		macheps(void);
int			ctohex(t_vector rgb);
t_vector	hextoc(int hex);
void		exit_error(char *message, int errn);
int			typecmp(char *t, t_object *o);

#endif