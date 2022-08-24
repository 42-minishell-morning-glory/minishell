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

typedef struct s_tree
{
	t_dlist				*dlist;
	struct s_tree		*right_child;
	struct s_tree		*left_child;
}						t_tree;

typedef struct s_info
{
	char					quote;
	int						quote_flag;
	int						double_quote_flag;
	char					**envp;
	struct s_dlist			*dlist;
	t_tree					*root;
	struct s_dlist			*env;
	struct s_operation		fo;
}							t_info;
/* signal.c */
void	set_signal_handler(void);
void	signal_handler(int signal);
void	set_terminal(void);

/*---minishell/parser---*/

	/* lexer.c */
int		lexer(char *str, t_info *info);

	/* input_check.c */
char	*input_check(char *str, t_info *info);
int		space_check(char *str);

	/* tokenize.c */	
void	tokenize(t_info *info);

	/* syntax.c, syntax_table.c */
int		put_syntaxerr_msg(char *token);
int		check_syntax(t_info *info);
int		check_redir(t_dlist *curr);
int		check_pipe(t_dlist *curr);
int		check_word(t_dlist *curr);
int		check_line(t_dlist *curr);
int		check_bracket(t_dlist *curr);

/*---minishell/utils---*/

	/* doubly_list.c */
t_dlist	*create_list(void);
void	add_list(t_info *info, char *str);
void	add_list_env(t_info *info, char *str);
int		delete_node(t_info *info, t_dlist *node);
void	delete_dlist(t_info *info);
void	printList(t_info *info);

	/* tree.c */
t_tree *make_tree(t_tree *myself, t_dlist *dlist);
void	printTree(t_tree *parent, int cnt);
/*---minishell/utils---*/

#endif