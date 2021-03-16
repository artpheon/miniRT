NAME	= miniRT

SRC		=	$(addprefix src/,\
			parser/parser_check.c \
			parser/parser_basic.c \
			parser/parser_param1.c \
			parser/parser_param2.c \
			parser/parser_extra.c \
			geom/geom.c \
			geom/geom_extra.c \
			renderer/renderer.c \
			mlx/mlx_additional.c \
			utils/utils.c \
			colours/colours.c \
			intersections/sp_inter.c \
			intersections/pl_inter.c \
			intersections/tr_inter.c \
			intersections/sq_inter.c \
			intersections/cy_inter.c \
			intersections/closest.c \
			rays/ray.c \
			lighting/calc_light.c \
			screenshot/screenshot.c \
			main.c)

%.o: %.c
	gcc -Wall -Wextra -Werror ${APP_INC} -g -c $< -o ${<:.c=.o}

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

${NAME}: all

linux:	${OBS}
	@make -C ./libs/libft/
	gcc ${OBS} -Wall -Wextra -Werror -g ${LIN_INC} ${LIN_LIBS} -o ${NAME}

apple: ${OBS}
	@make -C ./libs/libft/
	@make -C ./libs/mms/
	@mv ./libs/mms/libmlx.dylib .
	gcc ${OBS} -Wall -Wextra -Werror -g ${APP_INC} ${APP_LIBS} -o ${NAME}

clean:
	${RM} ${OBS}
	@make clean -C ./libs/libft/
	@make clean -C ./libs/mms/

fclean: clean
	${RM} ${NAME}
	@make fclean -C ./libs/libft/
	@make clean -C ./libs/mms/
	${RM} libmlx.dylib

re: fclean all

.PHONY: clean fclean bonus re all
