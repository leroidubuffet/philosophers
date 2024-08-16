# Makefile

NAME = philo
CC = gcc
CFLAGS = -Wall -Wextra -Werror
INC = -I ./inc
SRC = src/main.c src/philosopher.c src/forks.c
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
