# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ccommiss <ccommiss@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/12/20 14:10:49 by ccommiss          #+#    #+#              #
#    Updated: 2019/01/25 10:50:03 by ccommiss         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_fdf

SRCS = main.c \
		parser.c \
		get_next_line.c 

OBJS = $(SRCS:.c=.o)

INCLUDES = -I ./minilibx_macos \
			-I ./libft

LIB = -L./minilibx_macos -L./libft

CFLAG = -Wall -Wextra -Werror

GCC = gcc 

MLX = -lft -lmlx -framework OpenGL -framework AppKit

$(NAME) : $(OBJS)
	make -C ./minilibx_macos
	make -C ./libft 
	$(GCC) -o $(NAME)  $(OBJS) $(LIB) $(MLX)
	@echo "$(NAME) has been correctly compiled, congrats!"

%.o : %.c
	$(GCC) $(CFLAG) $(INCLUDES) -c $< -o $@

all: $(NAME)

clean :
	make clean -C ./minilibx_macos/
	make clean -C ./libft
	rm -f $(OBJS)
	@echo "Objects deleted"

fclean: clean
	@rm -f $(NAME)
	make fclean -C ./libft
	@echo "The program $(NAME) has just been deleted"

re:  fclean all
	@echo "Remake has been done"






