# **************************************************************************** #
#                                                           LE - /             #
#                                                               /              #
#    Makefile                                         .::    .:/ .      .::    #
#                                                  +:+:+   +:    +:  +:+:+     #
#    By: befuhro <marvin@le-101.fr>                 +:+   +:    +:    +:+      #
#                                                  #+#   #+    #+    #+#       #
#    Created: 2017/11/30 13:54:18 by befuhro      #+#   ##    ##    #+#        #
#    Updated: 2017/12/05 21:34:03 by befuhro     ###    #+. /#+    ###.fr      #
#                                                          /                   #
#                                                         /                    #
# **************************************************************************** #

SRC_PATH = 		srcs/
SRC_NAME =		tab.c
SRC =			$(addprefix $(SRC_PATH),$(SRC_NAME))

OBJ_PATH =		objs/
OBJ_NAME = 		$(SRC_NAME:.c=.o)
OBJ =			$(addprefix $(OBJ_PATH),$(OBJ_NAME))



INC = 			-Iinclude -I libft

LDLIBS = 		-lft
LDFLAGS = 		-Llibft
LIBFT_PATH = 	libft/
LIBFT = 		$(LIBFT_PATH)libft.a

CC = 			clang
CFLAGS = 		-Wall -Wextra -Werror
NAME = 			fdf

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	$(CC) $(INC) $(LDFLAGS) $(LDLIBS) -L mlx -lmlx -framework OpenGL -framework AppKit $^ -o $@

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	mkdir -p objs
	$(CC) $(CFLAGS) $(INC) $(CPPFLAGS) -o $@ -c $<

$(LIBFT):
	@make -C $(LIBFT_PATH)

clean:
	rm -fv $(OBJ)
	@make -C $(LIBFT_PATH) clean

fclean: clean
	rm -fv $(NAME)
	@make -C $(LIBFT_PATH) fclean

re: fclean all
