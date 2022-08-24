#include "bintree.h"

void delete_node(t_node *pNode)
{
	pNode->data = 0;
	pNode->pLeftChild = 0;
	pNode->pRightChild = 0;
	pNode->visited = 0;
	free(pNode);
}