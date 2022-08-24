#include "../minishell.h"

t_dlist	*check_priority(t_dlist *curr)
{
	t_dlist	*priority;

	while (curr->next)
		curr = curr->next;
	priority = curr;
	while (curr)
	{
		if (curr->type < priority->type)
			priority = curr;
		curr = curr->prev;
	}
	return (priority);
}

t_dlist	*get_first(t_dlist *curr)
{
	while (curr && curr->prev)
		curr = curr->prev;
	return (curr);
}

void	printTree(t_tree *parent, int cnt)
{
	t_dlist	*temp;

	if (parent)
	{
		temp = get_first(parent->dlist);
		printf("depth : %d, tree: ", cnt);
		while (temp)
		{
			printf("%s", temp->token);
			temp = temp->next;
			if (temp)
				printf(", ");
		}
		printf("\n");
		printTree(parent->left_child, cnt + 1);
		printTree(parent->right_child, cnt + 1);
	}
}

t_tree *make_tree(t_tree *myself, t_dlist *dlist)
{
	t_dlist 	*left;
	t_dlist 	*right;
	t_dlist		*node;
	
	node = check_priority(dlist);
	if (!myself)
		myself = ft_calloc(1, sizeof(t_tree));
	myself->dlist = node;
	if (node->type >= 4)
		return (myself);
	left = node->prev;
	right = node->next;
	if (left)
		left->next = 0;
	if (right)
		right->prev = 0;
	left = get_first(node->prev);
	node->next = 0;
	node->prev = 0;
	if (left)
		myself->left_child = make_tree(myself->left_child, left);
	if (right)
		myself->right_child = make_tree(myself->right_child, right);
	return (myself);
}
