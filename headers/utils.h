/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrobbin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 17:43:39 by hrobbin           #+#    #+#             */
/*   Updated: 2021/03/16 17:43:44 by hrobbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

t_vector	set_vector(float x, float y, float z);
t_ray		set_ray(t_vector origin, t_vector dir);
void		exit_error(char *message, int errn);
void		exit_free(t_info *info, int sshot);
int			typecmp(char *t, t_object *o);
#endif
