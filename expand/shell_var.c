#include "../minishell.h"

extern int	g_exit_code;

char	*token2env(char *env)
{
	int		i;
	int		j;
	int		env_size;
	char	*new;

	i = 0;
	j = 0;
	env_size = ft_strlen(env);
	while (env[j] != '=')
		j++;
	j++;
	new = ft_strdup(&env[j]);
	return (new);
}

int	empty_env_in_quote(char *token, int i)
{
	int	a;
	
	a = 0;
	while (token[i + a] == ' ' || token[i + a] == '\'' || token[i + a] == '\"' || token[i + a] == '$' || token[i + a])
		a++;
	ft_strlcpy(&token[i], &token[i + a], ft_strlen(&token[i]));
	return(1);
}

char	*switch2env(char *token, t_info *info, int i)
{
	t_dlist	*env;
	int		j;

	env = info->env;
	while (env)
	{
		j = 0;
		while (env->token[j] != '=')
		{
			if (token[i + j + 1] != env->token[j])
				break ;
			j++;
		}
		if (env->token[j] == '='
			&& ((token[i + j + 1] == ' ' || token[i + j + 1] == '\''
				|| token[i + j + 1] == '\"' || token[i + j + 1] == '$'
					|| token[i + j + 1] == '\0')))
			return (token2env(env->token));
		env = env->next;
	}
	empty_env_in_quote(token, i);
	return (NULL);
}

int	normal_expand(t_dlist *curr, t_info *info, int i)
{
	char	*expand;
	char	*tmp;
	char	*exit_code;

	tmp = curr->token;
	while (tmp[i] && (tmp[i] != '\'' || tmp[i] != '\"' || tmp[i] != ' '))
	{
		if (tmp[i] == '$' && tmp[i + 1] == '?')
		{
			exit_code = ft_itoa(g_exit_code);
			curr->token = exit_code;
			free(tmp);
			return (1);
		}
		else if (tmp[i] == '$')
		{
			expand = switch2env(tmp, info, i);
			if (expand)
			{
				curr->token = ft_strrep(tmp, expand, i);
				free(expand);
			}
			return (1);
		}
		i++;
	}
	return (1);
}

int	shell_var_expand(t_dlist *curr, t_info *info)
{
	char	*token;
	char	quote;
	int		i;

	token = curr->token;
	quote = 0;
	i = 0;
	while (token[i])
	{
		if (token[i] == '\'' && !quote)
			quote = '\'';
		else if (token[i] == '\'' && quote == '\'')
			quote = 0;
		else if (token[i] == '\"' && !quote)
			quote = '\"';
		else if (token[i] == '\"' && quote == '\"')
			quote = 0;
		else if (token[i] == '$' && quote != '\'')
		{
			normal_expand(curr, info, i);
			quote = 0;
			i = -1;
			token = curr->token;
		}
		i++;
	}
	return (1);
}
