#include "../minishell.h"

char	**make_command(t_dlist *curr);

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
	t_ftool	tool; // pipefd[2], status, pid

	if (pipe(tool.p_fd) == -1)
		return (1);
	tool.pid = fork();
	if (!tool.pid)
		execute(info, myself->left_child);
	waitpid(tool.pid, &tool.status, WNOHANG);
	if (myself->dlist->token[0] == '&' && !WEXITSTATUS(tool.status))
		execute(info, myself->right_child);
	else if (myself->dlist->token[0] == '|' && WEXITSTATUS(tool.status))
		execute(info, myself->right_child);
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
		exit(WEXITSTATUS(tool.status)); // 왼쪽에서 오류났으면 파이프 오른쪽은 실행 x
	dup2(tool.p_fd[0], STDIN_FILENO);
	close(tool.p_fd[0]);
	close(tool.p_fd[1]);
	execute(info, myself->right_child);
}

int	arg_num(t_dlist *list)
{
	t_dlist *curr;
	int		i;

	curr = list;
	while (list)
	{
		i++;
		list = list->next;
	}
	return (i);
}

char	**make_command_redir(t_tree *left_c, t_tree *right_c)
{
	t_dlist	*left;
	t_dlist *right;

	left = left_c->dlist;
	right = right_c->dlist;
	left->next = right;
	return (make_command(left));
}

int	kyhan_redir_input(t_info *info, t_tree *myself)
{
	int		r_fd;
	char	**arg;

	if (myself->left_child)
	{
		if (arg_num(myself->right_child->dlist) == 1)
		{
			r_fd = open(myself->right_child->dlist->token, O_RDONLY);
			if (r_fd == -1)
				return (0);
		}
		else if (arg_num(myself->right_child->dlist) >= 2)
		{
			myself->right_child->dlist = myself->right_child->dlist->next;
			// if (!is_builtin(myself->left_child))
				arg = make_command_redir(myself->left_child, myself->right_child);
			info->redir_in_flag = 1;
		}
		if (!info->redir_in_flag) // first redir
		{
			dup2(r_fd, STDIN_FILENO);
			close(r_fd);
			info->redir_in_flag = 1;
		}
		return (execute(info, myself->left_child));
	}
	else
	{
		if (myself->right_child)
			r_fd = open(myself->right_child->dlist->token, O_RDONLY);
		if (!info->redir_in_flag) // first redir
		{
			dup2(r_fd, STDIN_FILENO);
			close(r_fd);
			info->redir_in_flag = 1;
			return (execute(info, myself->left_child)); // execute에서 REDIR가 아니면 flag off 해줘야 함
		}
		else
			return (execute(info, myself->left_child));
	}
}

int	redir_input(t_info *info, t_tree *myself)
{
	t_ftool	tool;
	char	*file_name;
	int		r_fd;

	file_name = myself->dlist->token;
	while (*file_name == '<')
		file_name++;
	r_fd = open(file_name, O_RDONLY, 0644);
	if (r_fd == -1 && myself->left_child->dlist->type == WORD)
		puterr_exit(file_name);
	if (r_fd != -1 && !info->redir_in_flag) //cat <a <b <c일떄 c만 나오도록
	{
		dup2(r_fd, STDIN_FILENO);
		close(r_fd);
		info->redir_in_flag = 1;
	}
	tool.pid = fork();
	if (!tool.pid)
		execute(info, myself->left_child);
	waitpid(tool.pid, &tool.status, 0);
	if (WEXITSTATUS(tool.status))
	{
		if (info->redir_cnt == 1)
			unlink(".minishell_tmp");
		exit(WEXITSTATUS(tool.status));
	}
	if (r_fd == -1)
		puterr_exit(file_name);
	return (0);
}

int	redir_heredoc(t_info *info, t_tree *myself)
{
	t_ftool	tool;
	char	*limiter;
	char	*gnl;
	int		h_fd;

	limiter = &myself->dlist->token[2];
	if (!info->redir_in_flag)
	{
		h_fd = open(".here_doc_tmp", O_RDWR | O_TRUNC | O_CREAT, 0644);
		while (1)
		{
			write(2, "1hd> ", 5);
			gnl = get_next_line(0);
			if (ft_strncmp(gnl, limiter, ft_strlen(gnl)) == '\n')
			{
				free(gnl);
				break ;
			}
			write(h_fd, gnl, ft_strlen(gnl));
			free(gnl);
		}
		close(h_fd);
		h_fd = open(".here_doc_tmp", O_RDONLY, 0644);
		dup2(h_fd, STDIN_FILENO);
		close(h_fd);
		info->redir_in_flag = 1;
	}
	else
	{
		while (1)
		{
			write(2, "2hd> ", 5);
			gnl = get_next_line(0);
			if (ft_strncmp(gnl, limiter, ft_strlen(gnl)) == '\n')
			{
				free(gnl);
				break ;
			}
			free(gnl);
		}
	}
	tool.pid = fork();
	if (!tool.pid)
		execute(info, myself->left_child);
	waitpid(tool.pid, &tool.status, 0);
	if (WEXITSTATUS(tool.status))
	{
		if (info->redir_cnt == 1)
			unlink(".minishell_tmp");
		exit(WEXITSTATUS(tool.status));
	}
	return (0);
}

int	redir_output(t_info *info, t_tree *myself)
{
	t_ftool	tool;
	char	*file_name;
	int		r_fd;

	file_name = myself->dlist->token;
	while (*file_name == '>')
		file_name++;
	if (myself->dlist->token[1] == '>')
		r_fd = open(file_name, O_CREAT | O_APPEND | O_RDWR, 0644);
	else
		r_fd = open(file_name, O_CREAT | O_TRUNC | O_RDWR, 0644);
	if (!info->redir_out_fd)
	{
		info->tmp_fd = open(".minishell_tmp", O_CREAT | O_TRUNC | O_RDWR, 0644);
		dup2(info->tmp_fd, STDOUT_FILENO);
		close(info->tmp_fd);
		printf("%s\n", file_name);
		info->redir_out_fd = dup(r_fd);
	}
	close(r_fd);
	tool.pid = fork();
	if (!tool.pid)
		execute(info, myself->left_child);
	waitpid(tool.pid, &tool.status, 0);
	if (WEXITSTATUS(tool.status))
	{
		if (info->redir_cnt == 1)
			unlink(".minishell_tmp");
		unlink(file_name);
		exit(WEXITSTATUS(tool.status));
	}
	return (0);
}

int	execute_redir(t_info *info, t_tree *myself)
{
	char	*gnl;

	info->redir_cnt++;
	if (myself->dlist->token[0] == '<' && myself->dlist->token[1] != '<')
		redir_input(info, myself);
	else if (myself->dlist->token[0] == '>')
		redir_output(info, myself);
	else if (myself->dlist->token[0] == '<' && myself->dlist->token[1] == '<')
		redir_heredoc(info, myself);
	if (info->redir_cnt == 1)
	{
		info->tmp_fd = open(".minishell_tmp", O_RDONLY);
		gnl = get_next_line(info->tmp_fd);
		gnl[ft_strlen(gnl) - 1] = '\0';
		info->redir_out_fd = open(gnl, O_WRONLY, 0644);
		free(gnl);
		gnl = get_next_line(info->tmp_fd);
		while (gnl)
		{
			write(info->redir_out_fd, gnl, ft_strlen(gnl));
			free(gnl);
			gnl = get_next_line(info->tmp_fd);
		}
		close(info->redir_out_fd);
		unlink(".minishell_tmp");
		unlink(".here_doc_tmp");
		close(info->tmp_fd);
	}
	exit(0);
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
	int		status;
	char	*path;

	myself->dlist = get_first(myself->dlist);
	argv = make_command(myself->dlist);
	env = make_command(info->env);
	path = get_path(argv[0], env);
	if (execve(path, argv, env) == -1) // status에 exit code 0으로 저장
		puterr_exit("execve"); // status에 exit code 1로 저장
}

int	execute_bracket(t_info *info, t_tree *myself)
{
	return 1;
}

int	execute(t_info *info, t_tree *myself)
{
	if (myself->dlist->type == LINE)
		execute_line(info, myself);
	if (myself->dlist->type == PIPE)
		execute_pipe(info, myself);
	if (myself->dlist->type == REDIR)
		execute_redir(info, myself);
	if (myself->dlist->type == WORD)
		execute_word(info, myself);
	if (myself->dlist->type == BRACKET)
		execute_bracket(info, myself);
}