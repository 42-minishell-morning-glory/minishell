#include "bintree.h"

void	delete_recur(t_node *parent)
{
	if (parent->pLeftChild)
		delete_recur(parent->pLeftChild);
	if (parent->pRightChild)
		delete_recur(parent->pRightChild);
	delete_node(parent);

}

void deleteBinTree(t_bintree *pTree)
{
	if (!pTree)
		return ;
	delete_recur(pTree->pRootNode);
	pTree->pRootNode = 0;
	free(pTree);
}