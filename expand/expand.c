#include "../minishell.h"

int	quote_removal(t_dlist *curr)
{
	char	*token;
	char	quote;
	int		i;
	int		last;

	i = 0;
	last = 0;
	quote = 0;
	token = curr->token;
	while (token[i])
	{
		if (token[i] == '\"' || token[i] == '\'')
		{
			quote = token[i];
			ft_strlcpy(&token[i], &token[i + 1], ft_strlen(&token[i]));
			while (token[i] != quote)
				i++;
			ft_strlcpy(&token[i], &token[i + 1], ft_strlen(&token[i]));
		}
		else
			i++;
	}
	return (1);
}

int	word_split(t_dlist *now, int i)
{
	t_dlist	*curr; 
	char	*token;
	char	quote;

	curr = now;
	token = curr->token;
	while (token[i])
	{
		if (token[i] == '\"' || token[i] == '\'')
		{
			quote = token[i++];
			while (token[i] != quote)
				i++;
		}
		else if (token[i] == ' ')
		{
			while (token[i] == ' ')
				ft_strlcpy(&token[i], &token[i + 1], ft_strlen(&token[i]));
			cut_node(curr, i - 1);
			curr = curr->next;
			token = curr->token;
			i = -1;
		}
		i++;
	}
}

int	expand(t_tree *myself, t_info *info)
{
	t_dlist	*curr;
	int		ret;

	curr = get_first(myself->dlist);
	ret = 0;
	while (curr)
	{
		if (curr->type != WORD)
			break ;
		shell_var_expand(curr, info);
		word_split(curr, 0);
		// filename_expand(curr);
		quote_removal(curr);
		curr = curr->next;
	}
	if (myself->left_child)
		ret = expand(myself->left_child, info);
	if (myself->right_child)
		ret = expand(myself->right_child, info);
	return (ret);
}
