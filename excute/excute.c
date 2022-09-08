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
	t_ftool	parent_tool;
	t_ftool	child_tool;
	char	*tmp;

	pipe(parent_tool.p_fd);
	parent_tool.pid = fork();
	if (!parent_tool.pid)
	{
		close(parent_tool.p_fd[0]);
		pipe(child_tool.p_fd);
		child_tool.pid = fork();
		if (!child_tool.pid)
		{
			close(parent_tool.p_fd[1]);
			dup2(child_tool.p_fd[1], STDOUT_FILENO);
			close(child_tool.p_fd[0]);
			child_tool.status = execute(info, myself->left_child);
			close(child_tool.p_fd[1]);
			exit(child_tool.status);
		}
		else
		{
			tmp = ft_itoa(child_tool.pid);
			write(parent_tool.p_fd[1], tmp, ft_strlen(tmp));
			free(tmp);
			close(parent_tool.p_fd[1]);
			dup2(child_tool.p_fd[0], STDIN_FILENO);
			close(child_tool.p_fd[0]);
			close(child_tool.p_fd[1]);
			child_tool.status = execute(info, myself->right_child);
			exit(child_tool.status);
		}
	}
	tmp = ft_calloc(6, sizeof(char));
	read(parent_tool.p_fd[0], tmp, 5);
	close(parent_tool.p_fd[0]);
	waitpid(ft_atoi(tmp), 0, 0);
	free(tmp);
	waitpid(parent_tool.pid, &parent_tool.status, 0);
	return (WEXITSTATUS(parent_tool.status));
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
	char	*str;
	t_info	infoo;
	t_ftool	tool;

	str = fix_bracket(myself->dlist->token);
	init_info(&infoo);
	infoo.env = info->env;
	tool.pid = fork();
	if (!tool.pid)
	{
		if (space_check(str) == TRUE)
		{
			free(str);
			exit(0);
		}
		if (!input_check(str))
		{
			free(str);
			exit(0);
		}
		if (!lexer(str, &infoo))
		{
			free(str);
			delete_dlist(infoo.dlist);
			exit(0);
		}
		infoo.root = make_tree(NULL, infoo.dlist);
		expand(&infoo, infoo.root);
		tool.status = execute(&infoo, infoo.root);
		free(str);
		free_tree(infoo.root);
		exit(tool.status);
	}
	waitpid(tool.pid, &tool.status, 0);
	free(str);
	return (0);
}

int	execute(t_info *info, t_tree *myself)
{
	if (!myself)
		return (0);
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
	return (0);
}
