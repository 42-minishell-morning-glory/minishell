#include "../minishell.h"

int	is_sep_token(int sep)
{
	if (sep == '<' || sep == '>' || sep == '&' || sep == '|')
		return (1);
	return (0);
}

void	cut_node(t_dlist *curr, int i)
{
	t_dlist	*new;
	char	*tmp1;
	char	*tmp2;
	char	*remove;

	remove = curr->token;
	new = create_list();
	tmp1 = ft_strndup(remove, i + 1);
	tmp2 = ft_strdup(&remove[i + 1]);
	free(remove);
	curr->token = tmp1;
	new->token = tmp2;
	new->next = curr->next;
	curr->next = new;
	new->prev = curr;
}

int	pass_quote(char *token, int i)
{
	char	quote;

	quote = 0;
	while (token[i])
	{
		if (token[i] == '\'' && !quote)
			quote = '\'';
		else if (token[i] == '\'' && quote == '\'')
		{
			quote = 0;
			return (i);
		}
		else if (token[i] == '\"' && !quote)
			quote = '\"';
		else if (token[i] == '\"' && quote == '\"')
		{
			quote = 0;
			return (i);
		}
		i++;
	}
	return (i);
}

int	split_token(char *token, t_dlist *curr)
{
	int	i;
	int	quote;

	i = 0;
	quote = 0;
	while (token[i])
	{
		if (token[i] == '\'' || token[i] == '\"')
			i = pass_quote(token, i);
		else if (!is_sep_token(token[i]))
		{
			while (token[i] && !is_sep_token(token[i]))
				i++;
			if (is_sep_token(token[i]))
				cut_node(curr, i - 1);
			return (1);
		}
		else if (is_sep_token(token[i]))
		{
			if (token[i + 1] == token[i])
				cut_node(curr, i + 1);
			else
				cut_node(curr, i);
			return (1);
		}
		i++;
	}
	return (0);
}

int	is_complete_sep(char *token)
{
	if (!ft_strncmp(token, "<<", 3) || !ft_strncmp(token, "||", 3) \
	|| !ft_strncmp(token, ">>", 3) || !ft_strncmp(token, "&&", 3) \
	|| !ft_strncmp(token, "<", 2) || !ft_strncmp(token, ">", 2) \
	|| !ft_strncmp(token, "|", 2))
		return (1);
	return (0);
}

void	tokenize(t_info *info)
{
	t_dlist	*curr;

	curr = info->dlist;
	while (curr)
	{
		if (curr->token[0] == '(' || is_complete_sep(curr->token))
		{
			curr = curr->next;
			continue ;
		}
		split_token(curr->token, curr);
		curr = curr->next;
	}
	printList(info);
}
