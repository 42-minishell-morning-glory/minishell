#include "../minishell.h"

int	put_str_err(t_dlist *list, char *str)
{
	ft_putstr_fd("morningshell: ", 2);
	ft_putstr_fd(list->token, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\n", 2);
	return (1);
}

int	puterr_exit_code(char *str, int code)
{
	ft_putstr_fd("morningshell: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": ", 2);
	if (!code)
		ft_putstr_fd(strerror(errno), 2);
	else
		ft_putstr_fd("command not found", 2);
	ft_putstr_fd("\n", 2);
	if (code)
		return(code);
	else
		return(errno);
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