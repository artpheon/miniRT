NAME	= miniRT

SRC		=	src/conf_parser/parser.c \
			src/geom/geom.c \
			src/mlx/mlx_head.c \
			src/testing/test.c \
			src/utils/utils.c \
			src/main.c

OBS		= ${SRC:.c=.o}

OBSB	= ${BONUS:.c=.o}

%.o: %.c
	gcc -Wall -Wextra -Werror ${APP_INC} -g -c $< -o ${<:.c=.o}

LIN_INC		= -I./src/geom \
		  -I./src/mlx \
		  -I./src/testing \
		  -I./src/utils \
		  -I./headers \
		  -I./libs/libft \
		  -I./libs/mlxub

APP_INC		= -I./src/geom \
		  -I./src/mlx \
		  -I./src/testing \
		  -I./src/utils \
		  -I./headers \
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
			libmlx.dylib

all: unix

unix:	${OBS}
	@make -C ./libs/libft/
	gcc ${OBS} -Wall -Wextra -g ${LIN_INC} ${LIN_LIBS} -o ${NAME}

apple: ${OBS}
	@make -C ./libs/libft/
	@make -C ./libs/mms/
	@cp ./libs/mms/libmlx.dylib .
	gcc ${OBS} -Wall -Werror -Wextra ${APP_INC} ${APP_LIBS} -o ${NAME}

clean:
	${RM} ${OBS}

fclean: clean
	${RM} ${NAME}

re: fclean all

.PHONY: clean fclean bonus re all
