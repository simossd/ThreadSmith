NAME		= threadsmith

CC			= cc
CFLAGS		= -Wall -Wextra -Werror -pthread
INCLUDES	= -Iinclude

SRC_DIR		= src
OBJ_DIR		= obj

SRCS		= main.c \
			  parsing.c \
			  helpers.c \
			  init.c \
			  dongles.c \
			  pairing_dongles.c \
			  heap.c \
			  coder_routine.c \
			  monitor.c \
			  log.c

OBJS		= $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))
HEADER		= include/threadsmith.h

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADER) | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
