/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrobbin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 17:39:11 by hrobbin           #+#    #+#             */
/*   Updated: 2021/03/16 17:40:06 by hrobbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

# include "libft.h"
# include "main.h"
# include <fcntl.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <mlx.h>
# include <math.h>
# include "parser.h"
# include "geom.h"
# include "colours.h"
# include "renderer.h"
# include "intersections.h"
# include "ray.h"
# include "mlx_additional.h"
# include "screenshot.h"
# include "calc_light.h"
# include "utils.h"
# ifdef __linux__
#  define ESC 65307
#  define TAB 65289
#  define M_PI 3.14159265358979323846
# elif __APPLE__
#  define ESC 53
#  define TAB 48
# endif
# define RED   "\x1B[31m"
# define GRN   "\x1B[32m"
# define RESET "\x1B[0m"
# define MFAIL "Malloc failed"
# define BG_COLOUR 0x48494B
# define M_EPS 0.000001
#endif
