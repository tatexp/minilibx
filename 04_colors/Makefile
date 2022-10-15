NAME = colors

CC = gcc
FLAGS = -Wall -Werror -Wextra

LIBPATH = ../mlx
SRC = main.c
SRC_DIR = ./
HEADERS = $(NAME).h

OBJ_DIR = ./objects/
OBJ_FILES = $(patsubst %.c,%.o,$(SRC))
OBJECTS	= $(addprefix $(OBJ_DIR), $(OBJ_FILES))

FRAMEWORKS = -framework OpenGL -framework AppKit

.PHONY: all clean fclean re

all: $(OBJ_DIR) $(NAME)

$(NAME): $(OBJECTS) $(HEADERS)
	$(CC) $(FLAGS) -I$(LIBPATH) -L$(LIBPATH) -lmlx $(FRAMEWORKS) $(OBJECTS) -o $(NAME)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	$(CC) $(FLAGS) -I$(LIBPATH) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all
