#include "../minishell.h"



int	shell_var_expand(t_dlist *dlist, t_info *info)
{
	char	*token;
	int		quote_flag;
	int		i;

	token = dlist->token;
	i = 0;
	while (token[i])
	{
		if (token[i] == '\"')
			
		i++;
	}
	return (1);
}

int	expand(t_info *info)
{
	t_dlist	*curr;

	if (info->root->dlist->type != WORD)
		return (0);
	curr = info->root->dlist;
	while (curr)
	{
		shell_var_expand(curr, info);
		wordsplit(curr);
		filename_expand(curr);
		quote_remove(curr);
		curr = curr->next;
	}
}
