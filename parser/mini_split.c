#include "../minishell.h"

static char	*splcpy(char *s, int *point)
{
	int		i;
	int		size;
	char	*temp;

	size = 0;
	while ((s[size] != ' ' || s[size] != '\'' || s[size] != "\"") && s[size])
		size++;
	temp = (char *)malloc(sizeof(char) * (size + 1));
	if (!temp)
		return (NULL);
	i = 0;
	while (i < size)
	{
		temp[i] = s[i];
		i++;
	}
	temp[i] = '\0';
	*point += size;
	return (temp);
}

static int	count_split(const char *s)
{
	int	cnt;
	int	i;

	cnt = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] != ' ' || s[i] != '\'' || s[i] != '\"')
		{
			while ((s[i] != ' ' || s[i] != '\'' || s[i] != '\"') && s[i])
				i++;
			cnt++;
		}
		else
			i++;
	}
	return (cnt);
}

static void	free_arr(char **str, int index)
{
	int	i;

	i = 0;
	while (i < index)
	{
		free(str[i]);
		i++;
	}
}

char	**mini_split(const char *s)
{
	int		cnt;
	int		point;
	int		i;
	char	**ret_spl;

	cnt = count_split(s);
	ret_spl = malloc(sizeof(char *) * (cnt + 1));
	if (!ret_spl)
		return (NULL);
	point = 0;
	i = -1;
	while (++i < cnt)
	{
		while (s[point] == ' ' || s[point] == '\'' || s[point] == '\"')
			point++;
		ret_spl[i] = splcpy((char *)s + point, &point);
		if (ret_spl[i] == NULL && i)
		{
			free_arr(ret_spl, i);
			free(ret_spl);
		}
	}
	return (ret_spl);
}
