NAME    := philo
CC	    := clang
FLAGS   := -Wall -Wextra -Werror
LDFLAGS := -lpthread
SRCS 	:= src/main.c src/utils/utils.c src/utils/display_utils.c
OBJ_DIR	:=	obj
OBJS	:= $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))

.PHONY: all

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(FLAGS)  -o $@

$(OBJ_DIR)/%.o: %.c  $(OBJ_DIR)
	$(CC) $(FLAGS) -c $< -o $@

$(OBJ_DIR):
	@mkdir $@
	@mkdir $@/src
	@mkdir $@/src/utils

clean:
	@rm $(NAME)

fclean: clean
	@rm -rf $(OBJ_DIR)

re: fclean all		
