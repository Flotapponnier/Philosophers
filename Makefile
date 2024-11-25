CC = cc
CFLAGS = -Wall -Wextra -Werror
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a
INCLUDES = -I./includes
SRC = srcs/main.c \
	  srcs/initialising/parsing/parsing_argument.c \
	  srcs/initialising/initialising_table.c \
	  srcs/starting/starting_simulation.c \
	  srcs/starting/simulation_utils.c \
	  srcs/time/time.c \
	  srcs/error/error.c

OBJ = $(SRC:.c=.o)
NAME = philosopher
LIBFT_REPO = https://github.com/Flotapponnier/libft.git

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	$(CC) $(OBJ) -o $(NAME) $(LIBFT)

$(LIBFT):
	@if [ ! -d "$(LIBFT_DIR)" ]; then \
		git clone $(LIBFT_REPO) $(LIBFT_DIR); \
	fi
	make -C $(LIBFT_DIR)
	cp $(LIBFT_DIR)/libft.h includes/

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJ)
	@if [ -d "$(LIBFT_DIR)" ]; then \
		make clean -C $(LIBFT_DIR); \
	fi

fclean: clean
	rm -f $(NAME)
	@if [ -d "$(LIBFT_DIR)" ]; then \
		make fclean -C $(LIBFT_DIR); \
		rm -rf $(LIBFT_DIR); \
	fi

re: fclean all

