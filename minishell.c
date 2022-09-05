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
	info->in_fd = 0;
	info->out_fd = 0;
	info->dlist = 0;
	info->fo.i = 0;
	info->fo.last_idx = 0;
	info->root = 0;
	info->err_flag = 0;
	info->path_flag = 0;
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
		set_signal_handler(1);
		if (before_cmd(str, &info))
			continue ;
		add_history(str);
		if (after_cmd(str, &info))
			continue ;
		info.root = make_tree(NULL, info.dlist);
		expand(&info, info.root);
		g_exit_code = execute(&info, info.root);
		free(str);
		free_tree(info.root);
		unlink(".heredoc");
		unlink(".minishell_tmp");
	}
	return (0);
}
