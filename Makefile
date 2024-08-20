NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror
INC = -I ./inc
SRC = src/main.c src/arg_utils.c src/num_utils.c src/init_program.c src/cleanup.c src/init_philos.c
OBJ = $(SRC:.c=.o)
SANITIZE = -g -fsanitize=address

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

sanitize: $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(SANITIZE) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all re clean fclean
