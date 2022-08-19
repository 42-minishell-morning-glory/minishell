#include "minishell.h"

void	init_info(t_info *info)
{
	info->double_quote_flag = 0;
	info->quote_flag = 0;
	info->dlist = 0;
	info->fo.i = 0;
	info->fo.last_idx = 0;
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
		printf("%s\n", str);
		lexer(str, &info);
		free(str);
		delete_dlist(&info);
	}
}
