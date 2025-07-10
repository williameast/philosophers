#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: weast <weast@student.42berlin.de>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/02 12:26:33 by weast             #+#    #+#              #
#    Updated: 2025/07/10 10:41:23 by weast            ###   ########.fr        #
#                                                                              #
#******************************************************************************#
# Program file name
NAME	= philo

# Compiler and compilation flags
CC		= cc
CFLAGS	= -Werror -Wextra -Wall -pthread -I. -g
DEBUG_FLAGS = -g -DDEBUG
DEBUG_PIPE = /tmp/philo_debug_pipe

# Directories
SRC_DIR	= src/
OBJ_DIR	= obj/

# Source files
SRC		= 	main.c \
			atoxx.c \
			cleanup.c \
			forks.c \
			monitor.c \
			philosophers.c \
			setup.c \
			utils.c

# Object files
OBJ		= $(SRC:.c=.o)
SRCS	= $(addprefix $(SRC_DIR), $(SRC))
OBJS	= $(addprefix $(OBJ_DIR), $(OBJ))

# Header file
INC		= philo.h

# Main rule
all: $(NAME)

# Debug build
dev: CFLAGS += $(DEBUG_FLAGS)
dev: re
	@echo "Debug build complete - debug output will be printed to stdout"

# Create obj directory
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Objects rule
$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(INC)
	$(CC) $(CFLAGS) -c $< -o $@

# Project file rule
$(NAME): $(OBJ_DIR) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@

# Clean up build files rule
clean:
	rm -rf $(OBJ_DIR)

# Remove program executable
fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re dev
