#include "../minishell.h"

void	make_token(t_info *info, int end, int start, char *str)
{
	char	*temp;

	temp = ft_strndup(&str[start], end + 1 - start);
	add_list(info, temp);
}

void	cut_bracket(char *str, t_info *info)
{
	if (info->fo.i != info->fo.last_idx)
		make_token(info, info->fo.i - 1, info->fo.last_idx, str);
	info->fo.last_idx = info->fo.i;
	while (str[info->fo.i] && str[info->fo.i] != ')')
		info->fo.i++;
	if (!str[info->fo.i])
		printf("괄호 안닫혀있음 에러!!\n");
	make_token(info, info->fo.i, info->fo.last_idx, str);
	info->fo.last_idx = info->fo.i + 1;
}

void	first_opertaion(char *str, t_info *info)
{
	while (str[info->fo.i])
	{
		info->quote = 0;
		if (str[info->fo.i] == ' ' && info->fo.i == info->fo.last_idx)
			info->fo.last_idx = info->fo.i + 1;
		else if (str[info->fo.i] == ' ')
		{
			make_token(info, info->fo.i - 1, info->fo.last_idx, str);
			info->fo.last_idx = info->fo.i + 1;
		}
		else if (str[info->fo.i] == '\'' || str[info->fo.i] == '\"')
		{
			info->quote = str[info->fo.i];
			info->fo.i++;
			while (str[info->fo.i] != info->quote)
				info->fo.i++;
		}
		else if (str[info->fo.i] == '(')
			cut_bracket(str, info);
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