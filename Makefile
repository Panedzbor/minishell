NAME = minishell

CC = cc
CFLAGS = -lreadline
#-I includes
 
SRC_DIR = srcs
OBJ_DIR = objs
#LIBFT_DIR = includes/libft
#LIBFT = $(LIBFT_DIR)/libft.a

#OBJ_DIRS = $(OBJ_DIR) $(OBJ_DIR)/$(SRC_DIR)

SRCS = main.c 
 

#OBJS = $(SRCS:%.c=$(OBJ_DIR)/%.o)

all: $(NAME)


#$(OBJ_DIRS):
#	@mkdir -p $@

$(NAME): $(SRCS)
	$(CC) $(CFLAGS) -o $(NAME) $(SRCS)

#$(OBJ_DIR)/%.o: %.c
#	@mkdir -p $(dir $@)
#	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(MAKE) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) fclean

re: fclean all

.PHONY: all clean fclean re
