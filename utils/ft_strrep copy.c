/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrep copy.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 20:30:31 by kyhan             #+#    #+#             */
/*   Updated: 2022/08/25 14:29:51 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	check_dollar(char *token)
{
	int i;

	i = 0;
	while (i < ft_strlen(token))
	{
		if (token[i] == '$')
		{
			token[i] = '\0';
			break ;
		}
		i++;
	}
	i++;
	return (i);
}

char	*word_split(char *value)
{
	int		i;
	char	**split;
	char	*result;

	i = 0;
	result = "";
	split = ft_split(value, ' ');
	while (split[i])
	{
		if (i != 0)
			result = ft_strjoin(result, " ");
		result = ft_strjoin(result, split[i]);
		i++;
	}
	while(--i)
		free(split[i]);
	free(value);
	free(split);
	return (result);
}

char	*ft_strrep_copy(char *token, char *value, int i)
{
	int		i;
	char	*s1;
	char	*s2;
	char	*ret;

	i = check_dollar(token);
	s1 = ft_strdup(token);
	value = word_split(value);
	while (token[i] && token[i] != ' ' && token[i] != '\"'
		&& token[i] != '\'' && token[i] != '$')
		i++;
	s2 = ft_strdup(token + i);
	free(token);
	ret = ft_strjoin(s1, value);
	free(s1);
	s1 = ret;
	ret = ft_strjoin(s1, s2);
	free(s1);
	free(s2);
	return (ret);
}
// #include <stdio.h>
// int main()
// {
// 	char	*s1;
// 	char	*s2;

// 	s1 = ft_strdup("[ \"$a'$v'$asdasd\"   ]");
// 	s2 = ft_strdup("hi                bye                    hi");

// 	printf("s1 : |%s|\n", s1);
// 	printf("s2 : |%s|\n", s2);
// 	printf("result : |%s|\n", ft_strrep(s1, s2));
// 	system("leaks a.out");
// 	return (0);
// }