/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_additional.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrobbin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 17:39:43 by hrobbin           #+#    #+#             */
/*   Updated: 2021/03/16 17:39:57 by hrobbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MLX_ADDITIONAL_H
# define MLX_ADDITIONAL_H

int		key_hook(int keycode, t_info *info);
int		w_close(t_info *info);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
void	xy_size_check(t_scene *scene, void *mlx);
#endif
