#include "minishell.h"

extern char **environ;

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

int	main(void)
{
	int		i;
	char	*str;
	t_info	info;

	set_terminal();
	set_signal_handler();
	info.env = 0;
	i = 0;
	while (environ[i])
	{
		add_list(&info.env, environ[i]);
		i++;
	}
	while (1)
	{
		init_info(&info);
		str = readline("morningshell$ ");
		if (!str)
		{
			printf("exit\n");
			delete_dlist(info.env);
			exit(0);
		}
		if (space_check(str) == TRUE)
		{
			free(str);
			continue ;
		}
		add_history(str);
		if (!input_check(str))
		{
			free(str);
			continue ;
		}
		if (!lexer(str, &info))
		{
			free(str);
			delete_dlist(info.dlist);
			continue ;
		}
		info.root = make_tree(NULL, info.dlist);
		expand(&info, info.root);
		execute(&info, info.root);
		free(str);
		free_tree(info.root);
	}
}
