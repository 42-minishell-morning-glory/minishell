#include "bintree.h"

t_node *insertRightChildNodeBT(t_node *pParentNode, t_node element)
{
	t_node	*new;

	new = calloc(1,sizeof(t_node));
	if (!new)
		return (0);
	new = &element;
	pParentNode->pRightChild = new;
	return (new);
}