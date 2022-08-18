#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h>
# include <readline/history.h>
# include <stdio.h>
# include <stdlib.h>
# include "libft/libft.h"

enum {
	FALSE,
	TRUE
};

typedef struct s_dlist
{
	struct s_dlist	*next;
	struct s_dlist	*prev;
char				*token;
}					t_dlist;

typedef struct s_info
{
	int						quote_flag;
	int						double_quote_flag;
	struct s_dlist			*s_dlist;
}							t_info;

/*---minishell/parser---*/

/* parser.c */
int		lexer(char *str, t_info *info);

/* mini_split.c */
char	**ft_split(const char *s, char c);

/*---minishell/parser---*/

#endif