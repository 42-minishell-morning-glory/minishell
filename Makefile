CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f

PARSER_DIR = parser

SRCS =	minishell.c \
		#$(PARSER_DIR)/parser.c \
		# $(PARSER_DIR)/mini_split.c\

OBJS = $(SRCS:%.c=%.o)

NAME = minishell

all : $(NAME)

$(NAME) : $(OBJS)
	make -C ./libft
	$(CC) -lreadline ./libft/libft.a $(OBJS) -o $(NAME)

%.o		:		%.c
		$(CC) -c $< -o $@

clean :
	$(RM) $(OBJS)

fclean :
	make -C ./libft fclean
	$(RM) $(OBJS) $(NAME)

re :
	make fclean
	make all

run :
	make
	cat sun
	./minishell

.PHONY : all clean fclean re