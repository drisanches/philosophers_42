# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dde-fati <dde-fati@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/28 11:27:02 by dde-fati          #+#    #+#              #
#    Updated: 2024/06/24 23:19:44 by dde-fati         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRC = philo.c \
      exit_error.c
	  
OBJ = $(SRC:.c=.o)

CC = cc
C_FLAGS = -Wall -Wextra -Werror -pthread
RM = rm -rf

all: $(NAME)

$(NAME): $(OBJ)
	@ echo "\n\n$(YE)Preparing Push Swap...$(EN)\n"
	$(CC) $(C_FLAGS) $(OBJ) $(LIBFT_DIR)$(LIBFT) -o $(NAME)
	@ echo -e "\n$(GR)Push Swap is ready!$(EN)\n\n"

clean:
	 $(RM) $(OBJ)
	@ echo "\n$(MG)All objects removed!$(EN)\n\n"
	
fclean: clean
	$(RM) $(NAME)
	@ echo "\n$(RE)All libraries and executables removed!$(EN)\n\n"

re: fclean all

.PHONY: all clean fclean re bonus

#Colors
GR      = \033[32;1m
RE      = \033[31;1m
YE      = \033[33;1m
CY      = \033[36;1m
MG      = \033[0;36m
EN		= \033[0m
