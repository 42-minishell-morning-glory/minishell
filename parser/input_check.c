#include "../minishell.h"

int	is_single_quote(t_info *info, char *str, int *i)
{
	if (*i != 0 && str[*i - 1] == '\\' && (*i)++)
		return (0);
	(*i)++;
	while (str[*i] && str[*i] != '\'')
		(*i)++;
	if (!str[*i])
		info->quote_flag = 1;
	else
		info->quote_flag = 0;
	return (1);
}

int	is_double_quote(t_info *info, char *str, int *i)
{
	if (*i != 0 && str[*i - 1] == '\\' && (*i)++)
		return (0);
	(*i)++;
	while ((str[*i] && str[*i] != '\"') || \
	(*i != 0 && str[*i] == '\"' && str[*i - 1] == '\\'))
		(*i)++;
	if (!str[*i])
		info->double_quote_flag = 1;
	else
		info->double_quote_flag = 0;
	return (1);
}

int	is_quotes(char *str, t_info *info)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' && info->double_quote_flag == 0)
		{
			if (! is_single_quote(info, str, &i))
				continue ;
		}
		else if (str[i] == '\"' && info->quote_flag == 0)
			if (! is_double_quote(info, str, &i))
				continue ;
		i++;
	}
	if (info->double_quote_flag == 0 && info->quote_flag == 0)
		return (TRUE);
	else
		return (FALSE);
}

char	*input_check(char *str, t_info *info)
{
	size_t	i;
	char	*quote_line;
	char	*tmp;
	char	*free_tmp;

	i = 0;
	while (is_quotes(str, info) == FALSE)
	{
		quote_line = readline("> ");
		tmp = ft_strjoin(str, "\n");
		free_tmp = tmp;
		tmp = ft_strjoin(tmp, quote_line);
		free(free_tmp);
		free(str);
		free(quote_line);
		str = tmp;
	}
	return (str);
}

int	space_check(char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (TRUE);
	while (str[i])
	{
		if (str[i] == 0 && i++)
			continue ;
		return (FALSE);
	}
	return (TRUE);
}
