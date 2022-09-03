#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <signal.h>
# include <termios.h>
# include <fcntl.h>
# include "libft/libft.h"
# include <errno.h>
# include <dirent.h>
# include <sys/wait.h>
# include "get_next_line/get_next_line.h"

# define LINE 1
# define PIPE 2
# define REDIR 3
# define WORD 4
# define BRACKET 5

# define FALSE 0
# define TRUE 1

# define VERTICAL 1
# define HORIZONTAL 0

# define REPLACE_ONE 140

typedef struct s_operation
{
	int	i;
	int	last_idx;
}		t_operation;

typedef struct s_ftool
{
	int		p_fd[2];
	int		status;
	pid_t	pid;
}			t_ftool;

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
	int						redir_cnt;
	int						redir_out_fd;
	int						tmp_fd;
	int						in_fd;
	int						out_fd;
	int						quote_flag;
	int						double_quote_flag;
	int						redir_in_flag;
	int						err_flag;
	int						path_flag;
	unsigned char			exit_code;
	struct s_operation		fo;
	struct s_dlist			*env;
	struct s_dlist			*dlist;
	t_tree					*root;
}							t_info;

void	init_info(t_info *info);

/* signal.c */
void	set_signal_handler(int flag);
void	signal_handler(int signal);
void	set_terminal(void);
void	signal_handler2(int signal);
/*---parser---*/
	/* lexer.c */
int		lexer(char *str, t_info *info);

	/* input_check.c */
int		input_check(char *str);
int		space_check(char *str);

	/* tokenize.c */	
void	tokenize(t_info *info);
void	cut_node(t_dlist *curr, int i);

	/* syntax.c, syntax_table.c */
int		put_syntaxerr_msg(char *token);
int		check_syntax(t_info *info);
int		check_redir(t_dlist *curr);
int		check_pipe(t_dlist *curr);
int		check_word(t_dlist *curr);
int		check_line(t_dlist *curr);
int		check_bracket(t_dlist *curr);
/*---parser---*/

/*---minishell/utils---*/
	/* doubly_list.c */
t_dlist	*create_list(void);
void	add_list(t_dlist **list, char *str);
int		delete_node(t_dlist **list, t_dlist *node);
void	delete_dlist(t_dlist *list);
void	printList(t_dlist *list);
t_dlist	*get_first(t_dlist *curr);

	/* tree.c */
t_tree	*make_tree(t_tree *myself, t_dlist *dlist);
void	printTree(t_tree *parent, int cnt);
void	free_tree(t_tree *myself);

	/* utils.c */
int		puterr_exit_code(char *str, char *arg, int code);
int		put_str_err(t_dlist *list, char *str);
int		ft_free(char **split);
int		ft_isdigit_str(char *str);

	/* other */
char	*ft_strjoin_free(char *s1, char *s2);
char	*ft_strrep(char *token, char *value, int i);
/*---minishell/utils---*/

/*---minishell/expand---*/
	/* expand.c */
int		expand(t_info *info, t_tree *myself);
int		shell_var_expand(t_dlist *curr, t_info *info);

	/* wildcard.c */
int		wildcard(t_dlist **now);
int		set_list(t_dlist *curr, t_dlist *new_list);
char	*ft_str_rep_wildcard(char *d_name, char *next_path);
char	*ft_strjoin_free(char *s1, char *s2);
int		filter_wildcard(char *wc, char *str, int i, int j);
/*---minishell/expand---*/

/* minishell/execute */
	/* excute.c */
int		execute(t_info *info, t_tree *myself);
int		execute_word(t_info *info, t_tree *myself);
int		execute_redir(t_info *info, t_tree *myself);
char	**make_command(t_dlist *curr);

	/* built_in.c */
int		is_echo_option(char *arg);
char	*list2p(t_dlist *list);
int		echo(t_dlist *list);
int		export(t_info *info, t_dlist *list);
int		unset(t_info *info, t_dlist *list);
int		env(t_info *info, int flag);
int		cd(t_info *info, t_dlist *list);
int		pwd(void);
int		mini_exit(t_dlist *list);
int		built_in(t_info *info, t_tree *myself);

#endif
