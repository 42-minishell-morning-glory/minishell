CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f

PARSER_DIR = parser

SRCS =	minishell.c \
		#$(PARSER_DIR)/parser.c \
		# $(PARSER_DIR)/mini_split.c\

OBJS = $(SRCS:%.c=%.o)

NAME = minishell
SHELL = bash

all : $(NAME)

$(NAME) : $(OBJS)
	@make -C ./libft
	@./make.sh
	@$(CC) -L/usr/local/opt/readline/lib -I/usr/local/opt/readline/include -lreadline ./libft/libft.a $(OBJS) -o $(NAME)

%.o		:		%.c
		@$(CC) -c $< -o $@

clean :
	$(RM) $(OBJS)

fclean :
	@make -C ./libft fclean
	@$(RM) $(OBJS) $(NAME)

re :
	@make fclean
	@make all

run :
	@cat sun
	@make re
	@./minishell

.PHONY : all clean fclean re