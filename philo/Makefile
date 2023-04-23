CC		= clang
NAME	= philo
CFLAGS	= -Werror -Wextra -Werror -g -c
TFLAGS	= -fsanitize=thread


SRC		=	src/main.c \
			src/utils/action_utils.c \
			src/utils/fork_utils.c \
			src/utils/memory_utils.c \
			src/utils/philo_utils.c \
			src/utils/print_utils.c \
			src/utils/time_utils.c \
			src/utils/string_utils.c

OBJ_DIRS	=	dist

OBJ		= $(addprefix ./$(OBJ_DIRS)/,$(SRC:.c=.o))

all: $(NAME)

$(NAME): $(OBJ_DIRS) $(OBJ)
	$(CC) -lpthread $(OBJ) -o $(NAME)

$(OBJ_DIRS):
	mkdir -p $(OBJ_DIRS)/src/utils

$(OBJ_DIRS)/%.o: %.c
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf OBJ_DIRS

fclean: clean
	rm $(NAME)

re: fclean all

