#include "../minishell.h"

void	first_opertaion(char *str, t_info *info)
{
	int		i;
	int		last_idx;
	int		qoute;
	char	*temp;

	i = 0;
	last_idx = 0;
	while (str[i])
	{
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
			// 버퍼에 옮기는 작업
			temp = malloc(sizeof(char) * (i + 1 - last_idx));
			ft_strlcpy(temp, &str[last_idx], i + 1 - last_idx);
			add_list(info, temp);
			if (str[i] == ' ')
				continue ;
			else if (str[i] == '\'' || str[i] == '\"')
			{
				qoute = str[i++];
				last_idx = i;
				while (str[i] != qoute && str[i - 1] != '\\')
					i++;
				temp = malloc(sizeof(char) * (i + 1 - last_idx));
				ft_strlcpy(temp, &str[last_idx], i + 1 - last_idx);
				add_list(info, temp);
				i++;
				last_idx = i;
				continue ;
			}
		}
		i++;
	}
	if (last_idx != i)
	{
		temp = malloc(sizeof(char) * (i + 1 - last_idx));
		ft_strlcpy(temp, &str[last_idx], i + 1 - last_idx);
		add_list(info, temp);
	}
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
double qoute
string -> 달러도 여기서 받아서 예외처리
*/