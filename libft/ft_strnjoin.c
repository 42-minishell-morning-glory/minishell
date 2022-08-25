// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   ft_strnjoin.c                                      :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2022/03/15 20:30:31 by kyhan             #+#    #+#             */
// /*   Updated: 2022/08/25 11:06:35 by marvin           ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "libft.h"
// #include <stdio.h>
// #include <stdlib.h>

// static int	check_dollar(char *token)
// {
// 	int i;

// 	i = 0;
// 	while (i < ft_strlen(token))
// 	{
// 		if (token[i] == '$')
// 		{
// 			token[i] = '\0';
// 			break ;
// 		}
// 		i++;
// 	}
// 	i++;
// 	return (i);
// }

// char	*ft_strrep(char *token, char *env)
// {
// 	int		i;
// 	char	*s1;
// 	char	*s2;
// 	char	*ret;

// 	i = check_dollar(token);
// 	s1 = ft_strdup(token);
// 	while (token[i] && token[i] != ' ' && token[i] != '\"')
// 		i++;
// 	s2 = ft_strdup(token + i);
// 	free(token);
// 	ret = ft_strjoin(s1, env);
// 	free(s1);
// 	s1 = ret;
// 	ret = ft_strjoin(s1, s2);
// 	free(s1);
// 	free(s2);
// 	return (ret);
// }
