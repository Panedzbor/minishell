NAME = minishell

CC = cc
CFLAGS = -g -Wall -Wextra -Werror -I includes
TFLAGS = -g -Wall -Wextra -I includes
LRDFLAGS = -lreadline -lm
#LFLAGS = -L includes/libft -lft
#-I includes

#SRC_DIR = srcs
OBJ_DIR = objs
LIBFT = includes/libft/libft.a

SRCS = main.c $(wildcard srcs/*.c)
#srcs/node_functions.c srcs/input_parsing.c

OBJS = $(SRCS:%.c=$(OBJ_DIR)/%.o)

all: $(LIBFT) $(NAME)

$(LIBFT):
	$(MAKE) -C includes/libft

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)


$(NAME): $(OBJ_DIR) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(LRDFLAGS) -o $(NAME)

test: CFLAGS = $(TFLAGS)
test: clean $(LIBFT) $(NAME)

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(MAKE) clean -C includes/libft
	rm -rf $(OBJ_DIR)
	rm -f $(wildcard *.txt)

fclean: clean
	$(MAKE) fclean -C includes/libft
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
