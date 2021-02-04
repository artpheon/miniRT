NAME	= miniRT

SRC		=	src/conf_parser/parser.c \
			src/geom/geom.c \
			src/mlx/mlx_head.c \
			src/testing/test.c \
			src/main.c

OBS		= ${SRC:.c=.o}

OBSB	= ${BONUS:.c=.o}

%.o: %.c
	gcc -Wall -Wextra -Werror ${INC} -g -c $< -o ${<:.c=.o}

INC		= -I./src/geom \
		  -I./src/mlx \
		  -I./src/testing \
		  -I./headers \
		  -I./libs/libft \
		  -I./libs/mlxub

RM		= rm -f

LIBS	= -L./libs/libft -lft \
		  -L./libs/mlxub -lmlx_Linux \
		  -lXext \
		  -lX11 \
		  -lbsd \
		  -lm

all: ${NAME}

$(NAME):	${OBS}
	gcc ${OBS} -Wall -Wextra -g ${INC} ${LIBS} -o ${NAME}

clean:
	${RM} ${OBS}

fclean: clean
	${RM} ${NAME}

re: fclean all

.PHONY: clean fclean bonus re all
