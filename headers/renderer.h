/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrobbin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 17:41:01 by hrobbin           #+#    #+#             */
/*   Updated: 2021/03/16 17:41:16 by hrobbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDERER_H
# define RENDERER_H

void	start_render_init(t_info *info, t_scene *scene);
void	start_render_imgs(t_info *info, t_scene *s, t_list *cam_start);
void	start_render(t_info *info);
void	counter_on(int height, int row);
void	put_rays(t_scene *scene, t_data *img, int i);
#endif
