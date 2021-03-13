#include "header.h"

int main(int argc, char **argv)
{
	t_info *info;

	setbuf(stdout, NULL);
	info = malloc(sizeof(t_info));
	if (info)
	{
		if (argc == 2 || argc == 3)
		{
			info->sshot = 0;
			info->scene = parser(argv[1]);
			if (argc == 3)
			{
				if (ft_strncmp("--save", argv[2], 7) == 0)
					info->sshot = 1;
				else
					exit_error("Wrong second argument", 1);
			}
			start_render(info);
		}
		else
			exit_error("Wrong arguments number", 1);
	}
	else
		exit_error("Memory for info list was not allocated", 1);
	return (0);
}