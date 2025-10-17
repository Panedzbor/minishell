NAME = minishell

CC = cc
CFLAGS = -g -Wall -Wextra -Werror -I includes
TFLAGS = -g -Wall -Wextra -I includes
LRDFLAGS = -lreadline -lm

#SRC_DIR = srcs
OBJ_DIR = objs
TMP_DIR = tmp
LIBFT = includes/libft/libft.a

SRCS = main.c $(wildcard srcs/*.c)

OBJS = $(SRCS:%.c=$(OBJ_DIR)/%.o)

all: $(LIBFT) $(NAME)

$(LIBFT):
	$(MAKE) -C includes/libft

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(TMP_DIR):
	mkdir -p $(TMP_DIR)

$(NAME): $(OBJ_DIR) $(OBJS) $(TMP_DIR)
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
	rm -rf $(TMP_DIR)
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
