#include "../minishell.h"

int	ft_free(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
	return (1);
}

int	execute_line(t_info *info, t_tree *myself)
{
	int	ret;

	ret = execute(info, myself->left_child);
	if (myself->dlist->token[0] == '&' && ret)
		ret = execute(info, myself->right_child);
	else if (myself->dlist->token[0] == '|' && !ret)
		ret = execute(info, myself->right_child);
	return (ret);
}

int	child_proc(t_info *info, t_tree *myself, int p_fd[2])
{
	dup2(p_fd[1], STDOUT_FILENO);
	close(p_fd[1]);
	close(p_fd[0]);
	printf("child!!\n");
	execute(info, myself->left_child);
	return (0);
}

int	parent_proc(t_info *info, t_tree *myself, int p_fd[2])
{
	dup2(p_fd[0], STDIN_FILENO);
	close(p_fd[0]);
	close(p_fd[1]);
	execute(info, myself->right_child);
	return (0);
}

int	execute_pipe(t_info *info, t_tree *myself)
{	
	pid_t	id;
	int		status;

	if (pipe(info->p_fd) == -1)
		return (0);
	id = fork();
	if (id == -1)
		return (0);
	else if (id == 0)
		child_proc(info, myself, info->p_fd);
	parent_proc(info, myself, info->p_fd);
	waitpid(id, &status, 0);
	printf("parent!!\n");
	return (1);
}

int	execute_redir(t_info *info, t_tree *myself)
{
	// if (!ft_strncmp(myself->dlist->token, "<", 2))
	// {
		
	// }
	// else if (!ft_strncmp(myself->dlist->token, ">", 2))
	// {
		
	// }
	// else if (!ft_strncmp(myself->dlist->token, "<<", 3))
	// {
		
	// }
	// else if (!ft_strncmp(myself->dlist->token, ">>", 3))
	// {
		
	// }
	return (0);
}

char	**make_command(t_dlist *curr)
{
	t_dlist	*tmp;
	char	**ret;
	int		i;

	tmp = curr;
	i = 0;
	while (tmp)
	{
		tmp = tmp->next;
		i++;
	}
	ret = ft_calloc(i + 1, sizeof(char *));
	tmp = curr;
	i = 0;
	while (tmp)
	{
		ret[i] = tmp->token;
		tmp = tmp->next;
		i++;
	}
	return (ret);
}

char	*split_path(char *env, char *cmd)
{
	char	*path;
	char	**splited;
	char	*dir;
	int		i;

	i = 0;
	splited = ft_split(env, ':');
	while (splited[i])
	{
		dir = ft_strjoin(splited[i], "/");
		path = ft_strjoin(dir, cmd);
		free(dir);
		if (access(path, F_OK) > -1)
		{
			ft_free(splited);
			return (path);
		}
		free(path);
		i++;
	}
	ft_free(splited);
	return (cmd);
}

char	*get_path(char *cmd, char **env)
{
	char	*path;
	int		i;

	i = 0;
	while (env[i] && ft_strncmp(env[i], "PATH=", 5))
		i++;
	env[i] += 5;
	path = split_path(env[i], cmd);
	return (path);
}

int	execute_word(t_info *info, t_tree *myself)
{
	char	**argv;
	char	**env;
	pid_t	id;
	int		status;
	char	*path;

	myself->dlist = get_first(myself->dlist);
	argv = make_command(myself->dlist);
	env = make_command(info->env);
	if (info->p_flag);
	id = fork();
	if (id == -1)
		return (0);
	else if (!id)
	{
		path = get_path(argv[0], env);
		execve(path, argv, env);
	}
	waitpid(id, &status, 0);
	// ft_free(argv);
	// ft_free(env);
	return (1);
}

int	execute_bracket(t_info *info, t_tree *myself)
{
	return 1;
}

int	execute(t_info *info, t_tree *myself)
{
	int	ret;

	ret = 0;
	if (myself->dlist->type == LINE)
		ret = execute_line(info, myself);
	if (myself->dlist->type == PIPE)
		ret = execute_pipe(info, myself);
	if (myself->dlist->type == REDIR)
		ret = execute_redir(info, myself);
	if (myself->dlist->type == WORD)
		ret = execute_word(info, myself);
	if (myself->dlist->type == BRACKET)
		ret = execute_bracket(info, myself);
	return (ret);
}
