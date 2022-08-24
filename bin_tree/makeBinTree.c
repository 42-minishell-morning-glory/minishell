#include "bintree.h"

t_bintree *makeBinTree(t_node rootNode)
{
	t_bintree	*tree;

	tree = calloc(1, sizeof(t_bintree));
	tree->pRootNode = &rootNode;
	tree->pRootNode->visited = FALSE;
	tree->pRootNode->pLeftChild = 0;
	tree->pRootNode->pRightChild = 0;
	return (tree);
}

