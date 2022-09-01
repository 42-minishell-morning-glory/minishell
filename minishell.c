#include "minishell.h"

extern char **environ;

void	init_info(t_info *info)
{
	int	i;

	i = 0;
	info->double_quote_flag = 0;
	info->quote_flag = 0;
	info->redir_out_fd = 0;
	info->redir_in_flag = 0;
	info->redir_cnt = 0;
	info->tmp_fd = 0;
	info->dlist = 0;
	info->env = 0;
	info->fo.i = 0;
	info->fo.last_idx = 0;
	info->root = 0;
	while (environ[i])
	{
		add_list_env(info, environ[i]);
		i++;
	}
}

int	main(void)
{
	char	*str;
	pid_t	pid;
	t_info	info;

	set_terminal();
	set_signal_handler();
	while (1)
	{
		init_info(&info);
		str = readline("morningshell$ ");
		if (!str)
		{
			printf("exit\n");
			exit(0);
		}
		if (space_check(str) == TRUE)
			continue ;
		add_history(str);
		if (!input_check(str))
			continue ;
		if (!lexer(str, &info))
		{
			free(str);
			delete_dlist(&info);
			continue;
		}
		printList(&info);
		info.root = make_tree(NULL, info.dlist);
		expand(info.root, &info);
		printTree(info.root, 0);
		pid = fork();
		if (!pid)
		{
			execute(&info, info.root);
			exit(0);
		}
		waitpid(pid, 0, 0);
		free(str);
		delete_dlist(&info);
	}
}
