#include "../minishell.h"

void	make_token(t_info *info, int i, int last_idx, char *str)
{
	char	*temp;

	temp = malloc(sizeof(char) * (i + 1 - last_idx));
	ft_strlcpy(temp, &str[last_idx], i + 1 - last_idx);
	add_list(info, temp);
}

int	quote_handle(char *str, t_info *info)
{
	if (str[info->fo.i] == ' ')
	{
		info->fo.last_idx = info->fo.i;
		return (0);
	}
	else if (str[info->fo.i] == '\'' || str[info->fo.i] == '\"')
	{
		info->quote = str[info->fo.i++];
		info->fo.last_idx = info->fo.i;
		while (str[info->fo.i] != info->quote)
		{
			if (str[info->fo.i] == '\\' && str[info->fo.i + 1] == '\"' \
				&& info->quote == '\"')
				ft_strlcpy(&str[info->fo.i], &str[info->fo.i + 1], \
				ft_strlen(&str[info->fo.i]));
			info->fo.i++;
		}
		make_token(info, info->fo.i, info->fo.last_idx, str);
		info->fo.last_idx = ++info->fo.i;
		return (0);
	}
	return (1);
}

void	first_opertaion(char *str, t_info *info)
{
	while (str[info->fo.i])
	{
		info->quote = 0;
		if (str[info->fo.i] == ' ' && info->fo.i == info->fo.last_idx)
		{
			info->fo.last_idx = ++info->fo.i;
			continue ;
		}
		if (str[info->fo.i] == ' ' || str[info->fo.i] == '\'' || \
		str[info->fo.i] == '\"')
		{
			if (info->fo.i != 0 && str[info->fo.i - 1] == '\\' && info->fo.i++)
				continue ;
			if (info->fo.i != info->fo.last_idx)
				make_token(info, info->fo.i, info->fo.last_idx, str);
			if (!quote_handle(str, info))
				continue ;
		}
		info->fo.i++;
	}
	if (info->fo.last_idx != info->fo.i)
		make_token(info, info->fo.i, info->fo.last_idx, str);
}

int	lexer(char *str, t_info *info)
{
	t_list	*new;
	char	*lex_str;

	lex_str = ft_strdup(str);
	first_opertaion(lex_str, info);
	printList(info);
	free(lex_str);
	return (0);
}

/* yehyun
command
option
operator(논리 연산자)
redirection
pipe
single quote
double quote
string -> 달러도 여기서 받아서 예외처리
*/