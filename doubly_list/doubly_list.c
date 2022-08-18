#include "../minishell.h"

t_dlist	*create_list()
{
	t_dlist	*new;

	new = ft_calloc(1, sizeof (t_dlist));
	if (!new)
		exit(1);
	return (new);
}

void	add_list(t_info *info, char *str)
{
	t_dlist	*new;
	t_dlist	*curr;

	curr = info->dlist;
	if (curr == NULL)
	{
		curr = create_list();
		curr->token = str;
		return ;
	}
	while (curr->next)
		curr = curr->next;
	new = create_list();
	new->token = str;
	curr->next = new;
	new->next = NULL;
	new->prev = curr;
}