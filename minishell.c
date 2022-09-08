#include "minishell.h"

extern char	**environ;

int		g_exit_code;

void	init_info(t_info *info)
{
	info->double_quote_flag = 0;
	info->quote_flag = 0;
	info->redir_out_fd = 0;
	info->redir_in_flag = 0;
	info->redir_cnt = 0;
	info->tmp_fd = 0;
	info->hd_cnt = 0;
	info->in_fd = 0;
	info->out_fd = 0;
	info->dlist = 0;
	info->fo.i = 0;
	info->fo.last_idx = 0;
	info->root = 0;
	info->err_flag = 0;
	info->path_flag = 0;
	info->in_fd = dup(STDIN_FILENO);
	info->out_fd = dup(STDOUT_FILENO);
}

int	before_cmd(char *str, t_info *info)
{
	if (!str)
	{
		printf("exit\n");
		delete_dlist(info->env);
		exit(0);
	}
	if (space_check(str) == TRUE)
	{
		free(str);
		return (1);
	}
	return (0);
}

int	after_cmd(char *str, t_info *info)
{
	if (!input_check(str))
	{
		free(str);
		return (1);
	}
	if (!lexer(str, info))
	{
		free(str);
		delete_dlist(info->dlist);
		return (1);
	}
	return (0);
}

int	init_main(t_info *info)
{
	int	i;

	i = 0;
	info->env = 0;
	while (environ[i])
	{
		add_list(&info->env, environ[i]);
		i++;
	}
	rl_catch_signals = 0;
	info->hd_cnt = 0;
	return (0);
}

int	close_main(t_info *info, char *str)
{
	char	*file_name;
	char	*file_num;

	// usleep(10000);
	free(str);
	free_tree(info->root);
	while (info->hd_cnt)
	{
		file_num = ft_itoa(info->hd_cnt);
		file_name = ft_strjoin(".2Pj-9C6-v9X-g47", file_num);
		unlink(file_name);
		free(file_num);
		free(file_name);
		info->hd_cnt--;
	}
	return (0);
}

int	main(void)
{
	char	*str;
	t_info	info;

	init_main(&info);
	set_terminal();
	while (1)
	{
		init_info(&info);
		set_signal_handler(0);
		str = readline("morningshell$ ");
		if (before_cmd(str, &info))
			continue ;
		add_history(str);
		if (after_cmd(str, &info))
			continue ;
		info.root = make_tree(NULL, info.dlist);
		expand(&info, info.root);
		set_signal_handler(1);
		if (here_doc(&info, info.root) && !close_main(&info, str))
			continue ;
		g_exit_code = execute(&info, info.root);
		close_main(&info, str);
	}
	return (0);
}