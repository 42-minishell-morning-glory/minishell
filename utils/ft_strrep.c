/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrep.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 20:30:31 by kyhan             #+#    #+#             */
/*   Updated: 2022/08/25 16:23:24 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strrep(char *token, char *value, int i)
{
	char	*s1;
	char	*s2;
	char	*ret;

	token[i] = '\0';
	s1 = ft_strdup(token);
	// value = word_split(value); why? 워드 스플릿은 따옴표 없을때만 일어나야함.
	i++;
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
