#include "../minishell.h"

void	puterr_exit(char *str)
{
	ft_putstr_fd("minishell: ", 2);
	perror(str);
	exit(1);
}

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
	t_ftool	tool;
	int		ret;

	if (pipe(tool.p_fd) == -1)
		return (1);
	tool.pid = fork();
	if (!tool.pid)
		ret = execute(info, myself->left_child);
	waitpid(tool.pid, &tool.status, 0);
	if (myself->dlist->token[0] == '&' && ret)
		return (execute(info, myself->right_child));
	else if (myself->dlist->token[0] == '|' && !ret)
		return (execute(info, myself->right_child));
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
	if (WEXITSTATUS(tool.status) == 1)
		return (1); // 왼쪽에서 오류났으면 파이프 오른쪽은 실행 x
	dup2(tool.p_fd[0], STDIN_FILENO);
	close(tool.p_fd[0]);
	close(tool.p_fd[1]);
	return (execute(info, myself->right_child));
}

int	redir_right_one(t_info *info, t_tree *myself)
{
	int		fd;
	t_ftool	tool;

	fd = open(myself->right_child->dlist->token, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	myself->right_child->dlist = myself->right_child->dlist->next;
	if (myself->left_child)
	{	
		dup2(fd, STDOUT_FILENO);
		close(fd);
		execute(info, myself->left_child);
	}
}

int	execute_redir(t_info *info, t_tree *myself)
{
	if (!ft_strncmp(myself->dlist->token, ">", 2))
		redir_right_one(info, myself);
	//if (!ft_strncmp(myself->dlist->token, "<", 2))
	//{
			//}
	//else if (!ft_strncmp(myself->dlist->token, ">", 2))
	//{
	
	//}
	//else if (!ft_strncmp(myself->dlist->token, "<<", 3))
	//{
	
	//}
	//else if (!ft_strncmp(myself->dlist->token, ">>", 3))
	//{
	
	//}
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
	char	*path;

	myself->dlist = get_first(myself->dlist);
	argv = make_command(myself->dlist);
	env = make_command(info->env);
	path = get_path(argv[0], env);
	if (execve(path, argv, env) == -1)
		puterr_exit("execve");
}

int	execute_bracket(t_info *info, t_tree *myself)
{
	return 1;
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
