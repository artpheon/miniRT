#include "header.h"
#include "mlx_head.h"
#include "test.h"
#include "geom.h"
#ifdef __linux__
	# define OS "Linux"
#elif __APPLE__
	# define OS "Mac"
#endif

int main(int argc, char **argv)
{
	t_config	*config;
	t_object *obj_start;

	setbuf(stdout, NULL);
	printf("___Working on %s___\n", OS);
	if (argc > 1)
	{
		config = parser(argv[1]);
		obj_start = config->object->content;
		print_config(config);
		show_red_win();
		print_vector(obj_start->origin_coord);
	}
	else
	{
		perror("No arguments passed");
		exit(EXIT_FAILURE);
	}
	return 0;
}
