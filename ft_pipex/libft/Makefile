# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jbrol-ca <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/19 22:09:17 by jbrol-ca          #+#    #+#              #
#    Updated: 2024/12/20 19:16:12 by jbrol-ca         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Standard
NAME                = libft.a

# Directories
SRC_DIR             = ./src/ft_printf
INC_DIR             = ./inc
OBJ_DIR             = ./obj

# Compiler and Flags
CC                  = cc
CFLAGS              = -g -Wall -Wextra -Werror -I$(INC_DIR)
RM                  = rm -f

# Source Files
SRC                 = $(SRC_DIR)/ft_printf.c \
                      $(SRC_DIR)/ft_printf_func.c

# Object Files
OBJ                 = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Rules
all:                $(NAME)

$(NAME):            $(OBJ)
	@ar rcs $(NAME) $(OBJ)
	@echo "Library $(NAME) created."

$(OBJ_DIR)/%.o:     $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@
	@echo "Compiled $< -> $@"

clean:
	@$(RM) -r $(OBJ_DIR)
	@echo "Object files removed."

fclean:             clean
	@$(RM) $(NAME)
	@echo "Library $(NAME) removed."

re:                 fclean all

.PHONY:             all clean fclean re
