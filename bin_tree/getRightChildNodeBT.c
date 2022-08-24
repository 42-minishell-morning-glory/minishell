#include "bintree.h"

t_node *getRightChildNodeBT(t_node *pNode)
{
	if (!pNode)
		return (0);
	if (!pNode->pRightChild)
		return (0);
	return (pNode->pRightChild);
}