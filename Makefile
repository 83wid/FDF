# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nabouzah <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/27 05:26:56 by nabouzah          #+#    #+#              #
#    Updated: 2019/11/26 14:42:16 by nabouzah         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME= fdf
FLAGS= -Wall -Wextra -Werror 
OBJ= srcs/checker.o srcs/store.o srcs/store_utils.o srcs/init.o\
	srcs/drew.o srcs/keyboard.o srcs/projection.o srcs/main.o
INC= includes/

all : $(NAME)

%.o : %.c $(INC)
	clang -c -o $@ $<

$(NAME) : $(OBJ)
	@make -C libft/
	@clang -o $@ $^  -lmlx -framework OpenGL -framework AppKit\
		-I $(INC) libft/libft.a
	@printf "\033[0;32m"
	@printf "DONE COMPILING"

clean :
	@rm -rf $(OBJ) && make -C libft/ clean

fclean : clean
	@rm -f $(NAME) && make -C libft/ fclean
	@printf "\033[0;32m"
	@printf "DONE CLEANING\n"
	@printf "\033[0m"

re : fclean all
