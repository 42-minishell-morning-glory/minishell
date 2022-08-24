#include "../minishell.h"
// dlist -> Tree 구조로 

int	making_tree(t_info *info)
{
	t_dlist	*curr;

	curr = info->dlist;
	while (curr)
		curr = curr->next;
	while (curr)
	{
		if (curr->type != WORD || curr->type != BRACKET)
			create_tree(); // 인자로 리스트
		curr = curr->prev;
	}
}
