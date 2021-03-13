//
// Created by Howe Robbin on 3/13/21.
//

#ifndef SCREENSHOT_H
# define SCREENSHOT_H

void	make_header(int fd, int w, int h);
void	writedata(int w, int h, t_data *img_data, int fd);
int		writebmp(int w, int h, t_data *img_data);
void	shoot_screen(t_info *info);

#endif //MINIRT_SCREENSHOT_H
