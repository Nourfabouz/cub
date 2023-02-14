# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fabou-za <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/15 17:31:50 by fabou-za          #+#    #+#              #
#    Updated: 2023/01/16 13:27:10 by fabou-za         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = Cub3d
HEADERS = cub3d.h get_next_line/get_next_line.h
SRCS =  main_2.c utils.c utils2.c ft_split.c get_next_line/get_next_line.c get_next_line/get_next_line_utils.c 

OBJS := $(SRCS:.c=.o)

RM = rm -rf
FLAGS = -Werror -Wextra -Wall

$(NAME): $(OBJS) $(HEADERS)
	gcc $(OBJS) -o $(NAME)

#$(NAME_B): $(B_OBJS) $(HEADER_B)
#	gcc $(B_OBJS) -lmlx -framework OpenGL -framework AppKit -o $(NAME_B)

%.o : %.c
	gcc $(FLAGS) -c $< -o $@


all : $(NAME) #$(NAME_B)

#bonus: $(NAME_B)

clean :
	$(RM) $(OBJS) #$(B_OBJS)

fclean: clean
	$(RM) $(NAME) #$(NAME_B)

re: fclean clean all

.PHONY: all fclean clean re #bonus
