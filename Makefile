CC = cc
CFLAGS = -Wall -Wextra -Werror -g
LINKING_FLAGS = -L/opt/homebrew/Cellar/readline/8.1.2/lib -lreadline
COMFILE_FLAGS = -I/opt/homebrew/Cellar/readline/8.1.2/include

# DFLAGS = -g3 -fsanitize=address

RM = rm -f

PARSER_DIR = parser
DOBULY_DIR = doubly_list

SRCS =	minishell.c \
		$(PARSER_DIR)/lexer.c \
		$(PARSER_DIR)/tokenize.c \
		$(PARSER_DIR)/input_check.c \
		$(DOBULY_DIR)/doubly_list.c \
		signal.c

OBJS = $(SRCS:%.c=%.o)

NAME = minishell
SHELL = bash

all : $(NAME)

$(NAME) : $(OBJS)
	@make -C ./libft
	@./make.sh
	@$(CC) -I/usr/psps/opt/readline/include $(OBJS) -o $(NAME) $(LINKING_FLAGS) ./libft/libft.a

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
	@cat ascii_art/sun
	@make re
	@./minishell

#debug :
#	@make -C ./libft
#	@./make.sh
#	@$(CC) -L/usr/local/opt/readline/lib -I/usr/local/opt/readline/include -lreadline ./libft/libft.a $(SRCS) -o $(NAME) -g3 -fsanitize=address
#	@./minishell

.PHONY : all clean fclean re