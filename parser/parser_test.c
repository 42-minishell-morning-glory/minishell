#include "../minishell.h"

void	make_token(t_info *info, int i, int last_idx, char *str)
{
	char	*temp;

	temp = malloc(sizeof(char) * (i + 1 - last_idx));
	ft_strlcpy(temp, &str[last_idx], i + 1 - last_idx);
	add_list(info, temp);
}

int	handle_quote(char *str, t_info *info)
{
	ft_strlcpy(&str[info->fo.i], \
	&str[info->fo.i + 1], ft_strlen(&str[info->fo.i]));
	if (info->quote == '\'')
		while (str[info->fo.i] != info->quote)
			info->fo.i++;
	else
	{
		while (str[info->fo.i] != info->quote)
		{
			if (str[info->fo.i] == '\\')
			{
				if (str[info->fo.i + 1] == info->quote
					|| str[info->fo.i + 1] == '\\'
					|| str[info->fo.i + 1] == '$')
					ft_strlcpy(&str[info->fo.i], \
					&str[info->fo.i + 1], ft_strlen(&str[info->fo.i]));
			}
			info->fo.i++;
		}
	}
	ft_strlcpy(&str[info->fo.i], \
	&str[info->fo.i + 1], ft_strlen(&str[info->fo.i]));
	return (0);
}

void	first_opertaion(char *str, t_info *info)
{
	while (str[info->fo.i])
	{
		info->quote = 0;
		if (str[info->fo.i] == ' ' && info->fo.i == info->fo.last_idx)
			info->fo.last_idx = ++info->fo.i;
		else if (str[info->fo.i] == ' ')
		{
			if (info->fo.i != 0 && str[info->fo.i - 1] == '\\' && info->fo.i++)
				continue ;
			make_token(info, info->fo.i, info->fo.last_idx, str);
			info->fo.last_idx = ++info->fo.i;
		}
		else if (str[info->fo.i] == '\'' || str[info->fo.i] == '\"')
		{
			if (info->fo.i != 0 && str[info->fo.i - 1] == '\\' && info->fo.i++)
				continue ;
			info->quote = str[info->fo.i];
			handle_quote(str, info);
		}
		else
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

현재 알려진 이슈 : '$'와 "$"를 어떻게 구분할 것인가??
*/ 