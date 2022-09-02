#include "../minishell.h"

int	execute_line(t_info *info, t_tree *myself)
{
	int	left;
	int	right;

	left = execute(info, myself->left_child);
	if (myself->dlist->token[0] == '&' && !left)
		right = execute(info, myself->right_child);
	else if (myself->dlist->token[0] == '|' && left)
		right = execute(info, myself->right_child);
	else
		return (left);
	return (right);
}

int	execute_pipe(t_info *info, t_tree *myself)
{
	t_ftool	tool;

	if (pipe(tool.p_fd) == -1)
		return (1);
	tool.pid = fork();
	if (!tool.pid)
	{
		dup2(tool.p_fd[1], STDOUT_FILENO);
		close(tool.p_fd[1]);
		close(tool.p_fd[0]);
		return (execute(info, myself->left_child));
	}
	waitpid(tool.pid, &tool.status, 0);
	if (!WIFEXITED(tool.status))
		exit(WEXITSTATUS(tool.status));
	dup2(tool.p_fd[0], STDIN_FILENO);
	close(tool.p_fd[0]);
	close(tool.p_fd[1]);
	execute(info, myself->right_child);
}

char	*fix_bracket(char *token)
{
	char	*fixed;
	char	tmp;
	int		len;

	fixed = ft_strdup(token);
	len = ft_strlen(fixed);
	ft_strlcpy(&fixed[0], &fixed[1], len);
	len -= 2;
	tmp = fixed[len - 1];
	ft_strlcpy(&fixed[len - 1], &fixed[len], 2);
	len--;
	fixed[len] = tmp;
	return (fixed);
}

int	execute_bracket(t_info *info, t_tree *myself)
{
	char	*fixed;
	pid_t	pid;

	fixed = fix_bracket(myself->dlist->token);
	printf("%s\n", fixed);
	pid = fork();
	if (!pid)
		
	exit(0);
}

int	execute(t_info *info, t_tree *myself)
{
	if (myself->dlist->type == LINE)
		return (execute_line(info, myself));
	if (myself->dlist->type == PIPE)
		return (execute_pipe(info, myself));
	if (myself->dlist->type == REDIR)
		return (execute_redir(info, myself));
	if (myself->dlist->type == WORD)
		return (execute_word(info, myself));
	if (myself->dlist->type == BRACKET)
		return (execute_bracket(info, myself));
}