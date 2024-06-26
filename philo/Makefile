# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dde-fati <dde-fati@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/28 11:27:02 by dde-fati          #+#    #+#              #
#    Updated: 2024/06/26 00:08:30 by dde-fati         ###   ########.fr        #
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
	$(CC) $(C_FLAGS) $(OBJ) $(LIBFT_DIR)$(LIBFT) -o $(NAME)
	@ echo -e "\n$(GR)Philosophers is ready!$(EN)\n"

clean:
	 $(RM) $(OBJ)
	@ echo "$(MG)All objects removed!$(EN)\n"
	
fclean: clean
	$(RM) $(NAME)
	@ echo "$(MG)All executables removed!$(EN)\n"

re: fclean all

.PHONY: all clean fclean re bonus

#Colors
GR      = \033[32;1m
CY      = \033[36;1m
MG      = \033[0;36m
EN		= \033[0m
