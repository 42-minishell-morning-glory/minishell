#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <signal.h>
# include <termios.h>
# include "libft/libft.h"
# include <errno.h>

/* yehyun
command
option
operator(논리 연산자)
redirection
pipe
single quote
double quote
string -> 달러도 여기서 받아서 예외처리

현재 알려진 이슈 : '$'와 "$"를 어떻게 구분할 것인가??
*/ 

# define LINE 1
# define PIPE 2
# define REDIR 3
# define WORD 4
# define BRACKET 5

# define FALSE 0
# define TRUE 1

typedef struct s_operation
{
	int	i;
	int	last_idx;
}		t_operation;

typedef struct s_dlist
{
	struct s_dlist	*next;
	struct s_dlist	*prev;
	char			*token;
	int				type;
}					t_dlist;

typedef struct s_info
{
	char					quote;
	int						quote_flag;
	int						double_quote_flag;
	char					**envp;
	struct s_dlist			*dlist;
	struct s_dlist			*env;
	struct s_operation		fo;
}							t_info;
/* signal.c */
void	set_signal_handler(void);
void	signal_handler(int signal);
void	set_terminal(void);

/*---minishell/parser---*/

	/* parser.c */
int		lexer(char *str, t_info *info);
int		first_opertaion(char *str, t_info *info);

	/* mini_split.c */
char	**ft_split(const char *s, char c);

	/* input_check.c */
char	*input_check(char *str, t_info *info);
int		space_check(char *str);

/*---minishell/parser---*/
void	tokenize(t_info *info);
int		split_token(char *token, t_dlist *curr, t_dlist *next);
void	cut_node(t_dlist *curr, t_dlist *next, int i);
int		is_sep(int sep);
int		puterr_msg(char *token);
int		check_syntax(t_info *info);
int		put_syntaxerr_msg(char *token);

/*---minishell/doubly_list---*/

	/* doubly_list.c */
void	printList(t_info *info);
void	delete_dlist(t_info *info);
void	add_list(t_info *info, char *str);
void	add_list_env(t_info *info, char *str);
t_dlist	*create_list(void);
int		delete_node(t_info *info, t_dlist *node);

/*---minishell/doubly_list---*/

#endif