NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror
INC = -I ./inc
SRC = src/arg_utils.c \
	  src/init_program.c \
	  src/init_threads.c \
	  src/main.c \
	  src/monitoring.c \
	  src/print_utils.c \
	  src/num_utils.c \
	  src/philo_actions.c \
	  src/time_utils.c

OBJ = $(SRC:src/%.c=bin/%.o)
SANITIZE = -g -fsanitize=address

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

sanitize: $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(SANITIZE) -o $(NAME)

bin/%.o: src/%.c
	@mkdir -p bin
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

clean:
	rm -f $(OBJ)
	@rmdir bin 2>/dev/null || true  # Remove bin/ if it's empty

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all re clean fclean
