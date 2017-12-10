##
## EPITECH PROJECT, 2017
## Makefile
## File description:
##
##

SRC	=	source/my_hunter.c	\
		source/window.c	\
		source/sprites.c	\
		source/bird.c	\
		source/event.c	\
		source/game_over.c	\
		source/fill_struct.c	\
		source/main.c

OBJ	=	$(SRC:.c=.o)

NAME	=	my_hunter

CFLAGS	=	-W -Wall -Wextra -I include

LDFLAGS	=	-l c_graph_prog

$(NAME):	$(OBJ)
	gcc -o $(NAME) $(OBJ) $(LDFLAGS)

all:	$(NAME)

clean:
	rm -f $(OBJ)

fclean:	clean
	rm -f $(NAME)

re:	fclean all

PHONY: fclean clean all re
