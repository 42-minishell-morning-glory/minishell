#include "minishell.h"

extern char **environ;

void	init_info(t_info *info)
{
	int	i;

	i = 0;
	info->double_quote_flag = 0;
	info->quote_flag = 0;
	info->dlist = 0;
	info->fo.i = 0;
	info->fo.last_idx = 0;
	while (environ[i])
	{
		add_list_env(info, environ[i]);
		i++;
	}
}

int	main(void)
{
	char	*str;
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
		str = input_check(str, &info);
		add_history(str);
		lexer(str, &info);
		tokenize(&info);
		printList(&info);
		free(str);
		delete_dlist(&info);
	}
}
