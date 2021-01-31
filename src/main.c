#include "header.h"
#include "mlx_head.h"
#include "test.h"
#include "geom.h"



int main()
{
	t_config	*config;
	t_object *obj_start;

	config = parser("conf.txt");
	obj_start = config->object->content;
//	print_config(config);
//	show_red_win();
	print_vector(obj_start->origin_coord);
	return 0;
}
