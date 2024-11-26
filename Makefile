CC = cc
CFLAGS = -Wall -Wextra -Werror
INCLUDES = -I./includes
SRC = srcs/main.c \
	  srcs/initialising/parsing/parsing_argument.c \
	  srcs/initialising/initialising_table.c \
	  srcs/starting/starting_simulation.c \
	  srcs/starting/simulation_utils.c \
	  srcs/starting/philosopher_routine.c \
	  srcs/time/time.c \
	  srcs/error/error.c \
	  srcs/error/error_utils.c \
	  srcs/thread_mutex/set_get_bool.c \
	  srcs/thread_mutex/handle.c \
	  srcs/monitor/monitor.c 

OBJ = $(SRC:.c=.o)
NAME = philosopher

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $(NAME) 

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

