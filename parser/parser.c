#include "../minishell.h"

void	make_token(t_info *info, int i, int last_idx, char *str)
{
	char	*temp;

	temp = malloc(sizeof(char) * (i + 1 - last_idx));
	ft_strlcpy(temp, &str[last_idx], i + 1 - last_idx);
	add_list(info, temp);
}

void	first_opertaion(char *str, t_info *info)
{
	int		i;
	int		last_idx;

	i = 0;
	last_idx = 0;
	while (str[i])
	{
		info->quote = 0;
		if (str[i] == ' ' && i == last_idx)
		{
			i++;
			last_idx = i;
			continue ;
		}
		if (str[i] == ' ' || str[i] == '\'' || str[i] == '\"')
		{
			if (i != 0 && str[i - 1] == '\\')
			{
				i++;
				continue ;
			}
			if (i != last_idx)
				make_token(info, i, last_idx, str);
			if (str[i] == ' ')
			{
				last_idx = i;
				continue ;
			}
			else if (str[i] == '\'' || str[i] == '\"')
			{
				info->quote = str[i++];
				last_idx = i;
				while (str[i] != info->quote)
				{
					if (str[i] == '\\' && str[i + 1] == '\"' && info->quote == '\"')
						ft_strlcpy(&str[i], &str[i + 1], ft_strlen(&str[i]));
					i++;
				}
				make_token(info, i, last_idx, str);
				i++;
				last_idx = i;
				continue ;
			}
		}
		i++;
	}
	if (last_idx != i)
		make_token(info, i, last_idx, str);
}

int	lexer(char *str, t_info *info)
{
	t_list	*new;
	// info에 스페이스 인덱싱할 구조체 생성?
	first_opertaion(str, info);
	printList(info);
	
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