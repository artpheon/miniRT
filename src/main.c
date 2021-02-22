#include "header.h"


// minirt part 1: https://drive.google.com/file/d/1w2Ca7xNOULY6GQWxD2l6H_1sNyGnX-S5/view
//miniRT part 2: https://drive.google.com/file/d/1DJ4OB9FcucNFlNBTUxb4C94HJDR3jNG7/edit
// part 3: https://drive.google.com/file/d/1_1G8mPuwt__6TQSW2OqBh8EGMHFsttrl/edit
//part 4 https://drive.google.com/drive/folders/17tOe9hBcn14kLIjL_6SANu1a5yAQKxL7?usp=sharing

int main(int argc, char **argv)
{
	t_config	*config;

	setbuf(stdout, NULL);
	printf("___Working on %s___\n", OS);
	if (argc > 1)
	{
		config = parser(argv[1]);
		start_show(config);
		print_config(config);
	}
	else
		exit_error("No arguments passed", 1);
	return 0;
}