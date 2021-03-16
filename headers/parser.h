/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrobbin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 17:43:52 by hrobbin           #+#    #+#             */
/*   Updated: 2021/03/16 17:43:58 by hrobbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

int			get_next_line(char *line, int fd);
t_scene		*alloc_scene(void);
void		p_check_n(t_vector *n);
void		lr_check(float f);
char		*skip_1num(char *str);
char		*skip_3num(char *str);
void		get_resolution(t_scene *scene, char *line);
void		str_to_three(char *str, t_vector *new);
t_ambient	get_ambient(char *line);
t_list		*get_camera(char *line);
t_list		*get_light(char *line);
t_list		*get_sphere(char *line);
t_list		*get_plane(char *line);
t_list		*get_square(char *line);
t_list		*get_cylinder(char *line);
t_list		*get_triangle(char *line);
void		fill_scene(t_scene *scene, char *line);
void		p_first_check(int fd, char *name);
void		p_second_check(int ret, t_scene *scene);
t_scene		*parser(char *file);
#endif
