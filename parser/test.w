#include "../minishell.h"

int	check_str(char *str)
{
	int	i;
	int	cnt;

	i = 0;
	cnt = 0;
	while (str[i])
	{
		if (str[i] == ' ')
			cnt++;
		else if (str[i] == '\'')
		{
			// 스택에 넣음
			cnt++;
			i++;
			while (str[i] != '\'' && str[i])
				i++;
		}
		else if (str[i] == '\"')
		{
			// 스택에 넣음
			cnt++;
			i++;
			while (str[i] != '\"' && str[i])
				i++;
		}
		i++;
	}
	return (cnt);
}

char	*mini_spilt(char *str)
{
	int	i;

	i = 0;
	check_str(str);
}

int	a(void)
{
  printf("\\");
}

// 공백
// 따옴표
// 