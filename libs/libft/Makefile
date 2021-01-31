# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hrobbin <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/29 14:56:40 by hrobbin           #+#    #+#              #
#    Updated: 2020/11/26 17:04:02 by hrobbin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= libft.a

SRC		=	ft_atoi.c ft_bzero.c ft_calloc.c \
			ft_isalnum.c ft_isalpha.c ft_isascii.c \
			ft_isdigit.c ft_isprint.c ft_memccpy.c \
			ft_memchr.c ft_memcmp.c ft_memcpy.c \
			ft_memmove.c ft_memset.c ft_strchr.c \
			ft_strdup.c ft_strlcat.c ft_strlcpy.c \
			ft_strlen.c ft_strncmp.c ft_strnstr.c \
			ft_strrchr.c ft_tolower.c ft_toupper.c \
			ft_substr.c ft_strjoin.c ft_strtrim.c \
			ft_split.c ft_itoa.c ft_strmapi.c \
			ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c \
			ft_putnbr_fd.c

BONUS	=	ft_lstnew.c ft_lstadd_front.c ft_lstmap.c\
			ft_lstsize.c ft_lstlast.c ft_lstadd_back.c \
			ft_lstdelone.c ft_lstclear.c ft_lstiter.c \

OBS		= ${SRC:.c=.o}

OBSB	= ${BONUS:.c=.o}

.c.o:
	gcc -Wall -Wextra -Werror ${INC} -g -c $< -o ${<:.c=.o}

INC		= -I./

RM		= rm -f

all: ${NAME}

$(NAME):	${OBS}
	ar rc ${NAME} ${OBS}
	ranlib ${NAME}

bonus: ${OBS} ${OBSB}
	ar rc ${NAME} ${OBS} ${OBSB}
	ranlib ${NAME}

clean:
	${RM} ${OBS} ${OBSB}

fclean: clean
	${RM} ${NAME}

re: fclean all

.PHONY: clean fclean bonus re all
