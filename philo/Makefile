CC		= clang
NAME	= philo
CFLAGS	= -Werror -Wextra -Werror -g -c
TFLAGS	= -lpthread -fsanitize=thread


SRC		=	src/main.c \
			src/utils/action_utils.c \
			src/utils/fork_utils.c \
			src/utils/memory_utils.c \
			src/utils/philo_utils.c \
			src/utils/print_utils.c \
			src/utils/time_utils.c \
			src/utils/string_utils.c \
			src/utils/min_max_utils.c

OBJ_DIRS	=	dist

OBJ		= $(addprefix ./$(OBJ_DIRS)/,$(SRC:.c=.o))

all: $(NAME)

valgrind:
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes  -s --tool=helgrind ./$(NAME)

$(NAME): $(OBJ_DIRS) $(OBJ)
	$(CC) $(TFLAGS) $(OBJ) -o $(NAME)

$(OBJ_DIRS):
	mkdir -p $(OBJ_DIRS)/src/utils

$(OBJ_DIRS)/%.o: %.c
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf $(OBJ)

fclean: clean
	rm $(NAME)
	rm -rf ./$(OBJ_DIRS)

re: fclean all

