/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screenshot.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrobbin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 17:41:23 by hrobbin           #+#    #+#             */
/*   Updated: 2021/03/16 17:41:28 by hrobbin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCREENSHOT_H
# define SCREENSHOT_H

void	make_header(int fd, int w, int h);
void	writedata(int w, int h, t_data *img_data, int fd);
int		writebmp(int w, int h, t_data *img_data);
void	shoot_screen(t_info *info);
#endif
