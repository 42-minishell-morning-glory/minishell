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

enum {
	CMD,
	ARG,
	PIPE,
	REDIR,
	AND,
	OR,
	BRACKET
};

enum {
	FALSE,
	TRUE
};

typedef struct s_operation
{
	int			i;
	int			last_idx;
}				t_operation;

typedef struct s_dlist
{
	struct s_dlist	*next;
	struct s_dlist	*prev;
	char			*token;
	int				quote_flag;
	int				double_quote_flag;
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
void	first_opertaion(char *str, t_info *info);

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