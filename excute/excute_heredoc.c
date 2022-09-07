#include "../minishell.h"

extern int	g_exit_code;

void	hd_sig(int signum)
{
	printf("\n");
	exit(130);
}

int	open_hdfile(t_tree *myself, t_info *info)
{
	int		fd;
	char	*file_name;
	char	*file_num;

	file_num = ft_itoa(info->hd_cnt);
	file_name = ft_strjoin(".2Pj-9C6-v9X-g47", file_num);
	free(file_num);
	fd = open(file_name, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	return (fd);
}

void	do_here_doc(t_info *info, t_tree *myself)
{
	char	*str;
	char	*limiter;
	int		fd;

	if (!myself)
		return ;
	do_here_doc(info, myself->left_child);
	do_here_doc(info, myself->right_child);
	if (myself->dlist->token[1] != '<')
		return ;
	signal(SIGINT, hd_sig);
	info->hd_cnt++;
	limiter = ft_strdup(&myself->dlist->token[2]);
	fd = open_hdfile(myself, info);
	while (1)
	{
		write(2, "> ", 2);
		str = get_next_line(0);
		if (!str)
			break ;
		if (ft_strncmp(str, limiter, ft_strlen(str)) == '\n')
		{
			free(str);
			break ;
		}
		write(fd, str, ft_strlen(str));
		free(str);
	}
	free(limiter);
	close(fd);
}

void	change2file(t_info *info, t_tree *myself)
{
	char	*file_name;
	char	*file_num;

	if (!myself)
		return ;
	change2file(info, myself->left_child);
	change2file(info, myself->right_child);
	if (myself->dlist->token[1] != '<')
		return ;
	info->hd_cnt++;
	file_num = ft_itoa(info->hd_cnt);
	file_name = ft_strjoin(".2Pj-9C6-v9X-g47", file_num);
	free(file_num);
	free(myself->dlist->token);
	myself->dlist->token = ft_strjoin("<", file_name);
	free(file_name);
}

int	here_doc(t_info *info, t_tree *myself)
{
	t_ftool	tool;

	tool.pid = fork();
	if (!tool.pid)
	{
		signal(SIGINT, hd_sig);
		do_here_doc(info, myself);
		exit(0);
	}
	waitpid(tool.pid, &tool.status, 0);
	change2file(info, myself);
	g_exit_code = WEXITSTATUS(tool.status);
	return (WEXITSTATUS(tool.status));
}