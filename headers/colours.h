/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colours.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrobbin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 17:41:58 by hrobbin           #+#    #+#             */
/*   Updated: 2021/03/16 17:43:31 by hrobbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOURS_H
# define COLOURS_H

int			ctohex(t_vector rgb);
t_vector	hextoc(int hex);
t_vector	rgb_add(t_vector rgb, t_vector add);
t_vector	rgb_add_n(t_vector rgb, float num);
t_vector	rgb_mult_n(t_vector rgb, float num);
#endif
