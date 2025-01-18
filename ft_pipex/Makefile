# **************************************************************************** #
#                                  MAKEFILE                                    #
# **************************************************************************** #

NAME = pipex
CC = cc
CFLAGS = -Wall -Wextra -Werror -I./libft/inc
SRCS = pipex_main.c child_processes.c file_utils.c command_utils.c split.c string_utils.c
OBJS = $(SRCS:.c=.o)
RM = rm -f
LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a

# All target
all: $(NAME)

# Pipex target
$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT)

# Rule to compile object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean target
clean:
	$(RM) $(OBJS)
	$(MAKE) -C $(LIBFT_DIR) clean

# Full clean target
fclean: clean
	$(RM) $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

# Rebuild target
re: fclean all

# Include the libft library
$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

.PHONY: all clean fclean re
