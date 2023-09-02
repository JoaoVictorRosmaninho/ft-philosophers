NAME    := philo
CC	    := clang
FLAGS   := -g
TFLAGS	:= -lpthread -fsanitize=thread
SRCS 	:= src/main.c src/utils/cmd_line_utils.c src/utils/display_utils.c src/utils/build_utils.c src/utils/time_utils.c src/philosopher/philosopher.c src/monitor/monitor.c
OBJ_DIR	:=	obj
OBJS	:= $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))

.PHONY: all

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(TFLAGS) $(OBJS) $(FLAGS)  -o $@

$(OBJ_DIR)/%.o: %.c  $(OBJ_DIR)
	$(CC) $(FLAGS) -c $< -o $@

$(OBJ_DIR):
	@mkdir $@
	@mkdir $@/src
	@mkdir $@/src/utils
	@mkdir $@/src/philosopher
	@mkdir $@/src/monitor

clean:
	@rm $(NAME)

fclean: clean
	@rm -rf $(OBJ_DIR)

re: fclean all		
