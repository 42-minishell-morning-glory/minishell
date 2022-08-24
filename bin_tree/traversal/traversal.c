#include "../bintree.h"

void	preorder(t_node *parent)
{
	if (parent)
	{
		printf("%c\n", parent->data);
		preorder(parent->pLeftChild);
		preorder(parent->pRightChild);
	}
}

void	inorder(t_node *parent)
{
	if (parent)
	{
		inorder(parent->pLeftChild);
		printf("%c\n", parent->data);
		inorder(parent->pRightChild);
	}
}

void	postorder(t_node *parent)
{
	if (parent)
	{
		postorder(parent->pLeftChild);
		postorder(parent->pRightChild);
		printf("%c\n", parent->data);
	}
}