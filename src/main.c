#include "header.h"

int main(int argc, char **argv)
{
	t_info *info;

	info = malloc(sizeof(t_info));
	setbuf(stdout, NULL);
	if (argc > 1)
	{
		info->scene = parser(argv[1]);
		start_show(info);
	}
	else
		exit_error("Wrong arguments number", 1);
	return 0;
}