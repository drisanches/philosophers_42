# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dde-fati <dde-fati@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/28 11:27:02 by dde-fati          #+#    #+#              #
#    Updated: 2024/10/07 20:32:34 by dde-fati         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := philo

SRC := $(addsuffix .c, philo init threads actions forks check_death check_meals utils ft_atol)
OBJ_FOLDER := obj
OBJ := $(SRC:%.c=$(OBJ_FOLDER)/%.o)

CC := cc
FLAGS := -Wall -Wextra -Werror -fsanitize=thread
RM := rm -rf

all: $(NAME)

$(NAME): $(OBJ) 
	@$(CC) $(OBJ) -o $(NAME) -pthread -fsanitize=thread
	@echo "$(GR)Philosophers are ready!$(EN)"

$(OBJ_FOLDER)/%.o: %.c
	@mkdir -p $(OBJ_FOLDER)
	@echo "Compiling: $(notdir $<)" && $(CC) $(FLAGS) -c $< -o $@
	
clean:
	@$(RM) $(OBJ_FOLDER)
	@echo "$(MG)All objects removed!$(EN)"
	
fclean: clean
	@$(RM) $(NAME)
	@echo "$(MG)All executables removed!$(EN)"

re: fclean all

.PHONY: all clean fclean re

#Colors
GR      = \033[32;1m
CY      = \033[36;1m
MG      = \033[0;36m
EN		= \033[0m
