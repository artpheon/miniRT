/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colours.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrobbin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 23:57:15 by hrobbin           #+#    #+#             */
/*   Updated: 2021/03/15 23:57:27 by hrobbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int			ctohex(t_vector rgb)
{
	int r;
	int g;
	int b;

	r = rgb.x;
	g = rgb.y;
	b = rgb.z;
	return ((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff);
}

t_vector	hextoc(int hex)
{
	t_vector new;

	new.x = (hex >> 16) & 0xff;
	new.y = (hex >> 8) & 0xff;
	new.z = hex & 0xff;
	return (new);
}

t_vector	rgb_add(t_vector rgb, t_vector add)
{
	rgb.x += add.x;
	if (rgb.x > 255)
		rgb.x = 255;
	rgb.y += add.y;
	if (rgb.y > 255)
		rgb.y = 255;
	rgb.z += add.z;
	if (rgb.z > 255)
		rgb.z = 255;
	return (rgb);
}

t_vector	rgb_add_n(t_vector rgb, float num)
{
	rgb.x += num;
	rgb.y += num;
	rgb.z += num;
	if (rgb.x > 255)
		rgb.x = 255;
	if (rgb.y > 255)
		rgb.y = 255;
	if (rgb.z > 255)
		rgb.z = 255;
	return (rgb);
}

t_vector	rgb_mult_n(t_vector rgb, float num)
{
	rgb.x *= num;
	rgb.y *= num;
	rgb.z *= num;
	if (rgb.x > 255)
		rgb.x = 255;
	if (rgb.y > 255)
		rgb.y = 255;
	if (rgb.z > 255)
		rgb.z = 255;
	return (rgb);
}
