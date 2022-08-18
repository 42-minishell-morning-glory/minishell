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
	if (info->dlist == NULL)
	{
		info->dlist = create_list();
		info->dlist->token = str;
		//printf("curr->token : |%s| and str : |%s|\n", info->dlist->token, str);
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

void	delete_dlist(t_info *info)
{
	t_dlist *curr;
	t_dlist	*tmp;

	curr = info->dlist;
	while (!curr)
	{
		tmp = curr;
		curr = curr->next;
		free(tmp->token);
		free(tmp);
	}
}

void printList(t_info *info)
{
	t_dlist *tmp;
	int		i;

	i = 0;
	tmp = info->dlist;
	printf("====print start====\n");
	while(tmp)
	{	
		printf("token : |%s|\n", tmp->token);
		tmp = tmp->next;
	}
	printf("=====print end=====\n\n");
}