NAME	= miniRT

SRC		=	$(addprefix src/,conf_parser/parser.c \
			geom/geom.c \
			mlx/mlx_head.c \
			testing/test.c \
			utils/utils.c \
			lighting/calc_light.c \
			screenshot/screenshot.c \
			main.c)

%.o: %.c
	gcc -Wall -Wextra ${LIN_INC} -g -c $< -o ${<:.c=.o}

OBS		= ${SRC:.c=.o}

LIN_INC		= -I./headers \
		  -I./libs/libft \
		  -I./libs/mlxub

APP_INC		= -I./headers \
		  -I./libs/libft \
		  -I./libs/mms

RM		= rm -f

LIN_LIBS	= -L./libs/libft -lft \
		  -L./libs/mlxub -lmlx_Linux \
		  -lXext \
		  -lX11 \
		  -lbsd \
		  -lm

APP_LIBS	= -L./libs/libft -lft \
			-framework OpenGL \
			-framework AppKit \
			libmlx.dylib

all: apple

linux:	${OBS}
	@make -C ./libs/libft/
	gcc ${OBS} -Wall -Wextra -g -fsanitize=address ${LIN_INC} ${LIN_LIBS} -o ${NAME}

apple: ${OBS}
	@make -C ./libs/libft/
	@make -C ./libs/mms/
	@mv ./libs/mms/libmlx.dylib .
	gcc ${OBS} -Wall -Wextra -g ${APP_INC} ${APP_LIBS} -o ${NAME}

clean:
	${RM} ${OBS}
	@make clean -C ./libs/libft/
	@make clean -C ./libs/mms/

fclean: clean
	${RM} ${NAME}
	@make fclean -C ./libs/libft/
	@make clean -C ./libs/mms/

re: fclean all

.PHONY: clean fclean bonus re all
