#include "bintree.h"

t_node *getRootNodeBT(t_bintree *pTree)
{
	if (!pTree)
		return (0);
	if (!pTree->pRootNode)
		return (0);
	return (pTree->pRootNode);
}