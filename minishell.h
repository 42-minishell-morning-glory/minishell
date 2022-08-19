#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <signal.h>
# include <termios.h>
# include "libft/libft.h"

enum {
	FALSE,
	TRUE
};

typedef struct s_fisrt_operation
{
	int			i;
	int			last_idx;
}				t_first_operation;

typedef struct s_dlist
{
	struct s_dlist	*next;
	struct s_dlist	*prev;
	char			*token;
	int				quote_flag;
	int				double_quote_flag;
}					t_dlist;

typedef struct s_info
{
	char					quote;
	int						quote_flag;
	int						double_quote_flag;
	struct s_dlist			*dlist;
	t_first_operation		fo;
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

/*---minishell/doubly_list---*/

	/* doubly_list.c */
void	printList(t_info *info);
void	delete_dlist(t_info *info);
void	add_list(t_info *info, char *str);
t_dlist	*create_list(void);

/*---minishell/doubly_list---*/

#endif