//
// Created by Howe Robbin on 1/20/21.
//

#ifndef HEADER_H
# define HEADER_H

# ifdef __linux__
	#  define OS "Linux"
	#  define ESC 65307
# elif __APPLE__
	#  define OS "Mac"
	#  define ESC 35
# endif

# include <fcntl.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <mlx.h>
# include <math.h>
# include "libft.h"
# include "parser.h"
# include "mlx.h"
# include "geom.h"
# include "mlx_head.h"
# include "test.h"
# include "utils.h"

#endif //MINIRT_HEADER_H