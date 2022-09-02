#include "../minishell.h"

t_dlist	*create_list(void)
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

void	add_list_env(t_info *info, char *str)
{
	t_dlist	*new;
	t_dlist	*curr;

	curr = info->env;
	if (info->env == NULL)
	{
		info->env = create_list();
		info->env->token = ft_strdup(str);
		return ;
	}
	while (curr->next)
		curr = curr->next;
	new = create_list();
	new->token = ft_strdup(str);
	curr->next = new;
	new->next = NULL;
	new->prev = curr;
}

void	delete_dlist(t_info *info)
{
	t_dlist	*curr;
	t_dlist	*tmp;

	curr = info->dlist;
	while (curr)
	{
		tmp = curr;
		curr = curr->next;
		free(tmp->token);
		free(tmp);
	}
}

void	printList(t_info *info)
{
	t_dlist	*tmp;

	tmp = info->dlist;
	printf("====print start====\n");
	while (tmp)
	{	
		printf("token : %s, type : %d\n", tmp->token, tmp->type);
		tmp = tmp->next;
	}
	printf("=====print end=====\n\n");
}

int	delete_node(t_dlist **list, t_dlist *node)
{
	t_dlist	*tmp;

	tmp = *list;
	while (tmp && tmp != node)
		tmp = tmp->next;
	if (tmp == 0)
		return (0);
	if (tmp->next)
		tmp->next->prev = tmp->prev;
	if (tmp->prev)
		tmp->prev->next = tmp->next;
	else
		*list = (*list)->next;
	tmp->next = 0;
	tmp->prev = 0;
	free(tmp->token);
	tmp->token = 0;
	free(tmp);
	return (1);
}
