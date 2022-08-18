CC = cc
CFLAGS = -Wall -Wextra -Werror
LINKING_FLAGS = -L/usr/local/Cellar/readline/8.1.2/lib -lreadline
COMFILE_FLAGS = -I/usr/local/Cellar/readline/8.1.2/include

# DFLAGS = -g3 -fsanitize=address

RM = rm -f

PARSER_DIR = parser
DOBULY_DIR = doubly_list

SRCS =	minishell.c \
		$(PARSER_DIR)/parser.c \
		$(DOBULY_DIR)/doubly_list.c \
		signal.c
		# $(PARSER_DIR)/mini_split.c\

OBJS = $(SRCS:%.c=%.o)

NAME = minishell
SHELL = bash

all : $(NAME)

$(NAME) : $(OBJS)
	@make -C ./libft
	@./make.sh
	@$(CC) -I/usr/psps/opt/readline/include ./libft/libft.a $(OBJS) -o $(NAME) $(LINKING_FLAGS)

%.o		:		%.c
		@$(CC) $(COMFILE_FLAGS) -c $< -o $@

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

#debug :
#	@make -C ./libft
#	@./make.sh
#	@$(CC) -L/usr/local/opt/readline/lib -I/usr/local/opt/readline/include -lreadline ./libft/libft.a $(SRCS) -o $(NAME) -g3 -fsanitize=address
#	@./minishell

.PHONY : all clean fclean re