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
	t_ftool	tool;

	if (info->err_flag)
		return (0);
	myself->dlist = get_first(myself->dlist);
	argv = make_command(myself->dlist);
	env = make_command(info->env);
	path = get_path(argv[0], env);
	tool.status = built_in(info, myself);
	if (tool.status != -1)
		return (tool.status);
	tool.pid = fork();
	if (!tool.pid)
		if (execve(path, argv, env) == -1) // status에 exit code 0으로 저장
			exit(puterr_exit_code(argv[0], 0)); // status에 exit code 1로 저장
	waitpid(tool.pid, &tool.status, 0);
	return (WEXITSTATUS(tool.status));
}
