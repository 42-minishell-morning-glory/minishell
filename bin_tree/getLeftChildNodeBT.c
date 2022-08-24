#include "bintree.h"

t_node *getLeftChildNodeBT(t_node *pNode)
{
	if (!pNode)
		return (0);
	if (!pNode->pLeftChild)
		return (0);
	return (pNode->pLeftChild);
}