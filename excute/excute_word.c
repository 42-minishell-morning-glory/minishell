#include "../minishell.h"

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

int	ft_access(char *path)
{
	int	tmp_fd;

	tmp_fd = open(path, O_RDONLY);
	if (tmp_fd == -1)
		return (-1);
	close(tmp_fd);
	return (0);
}

char	*split_path(t_info *info, char *env, char *cmd)
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
		if (ft_access(path) > -1)
		{
			info->path_flag = 1;
			ft_free(splited);
			return (path);
		}
		free(path);
		i++;
	}
	ft_free(splited);
	return (cmd);
}

char	*get_path(t_info *info, char *cmd, char **env)
{
	char	*path;
	int		i;

	i = 0;
	while (env[i] && ft_strncmp(env[i], "PATH=", 5))
		i++;
	env[i] += 5;
	path = split_path(info, env[i], cmd);
	return (path);
}

int	execute_word(t_info *info, t_tree *myself)
{
	char	**argv;
	char	**env;
	char	*path;
	t_ftool	tool;

	if (info->err_flag)
		return (0);
	myself->dlist = get_first(myself->dlist);
	tool.status = built_in(info, myself);
	if (tool.status != -1)
		return (tool.status);
	argv = make_command(myself->dlist);
	env = make_command(info->env);
	path = get_path(info, argv[0], env);
	tool.pid = fork();
	if (!tool.pid)
		if (execve(path, argv, env) == -1)
			exit(puterr_exit_code(argv[0], 127));
	waitpid(tool.pid, &tool.status, 0);
	// 여기서 올바르지 않은 명령어일때 그 명령어 free 해줘야댐
	if (info->path_flag)
		free(path);
	free(argv);
	free(env);
	return (WEXITSTATUS(tool.status));
}
