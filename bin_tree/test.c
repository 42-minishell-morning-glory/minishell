#include "bintree.h"
#include "traversal.h"

int main()
{
	t_bintree *tree;
    t_node node;

    node.pLeftChild = NULL;
    node.pRightChild = NULL;
    node.data = '1';
    tree = makeBinTree(node);
    node.data = '2';
    t_node *left = insertLeftChildNodeBT(tree->pRootNode, node);
    node.data = '3';
    insertLeftChildNodeBT(left, node);
    node.data = '4';
    insertRightChildNodeBT(left, node);
    node.data = '5';
    insertRightChildNodeBT(tree->pRootNode, node);

    printf("------ preorder -------\n");
    preorder(tree->pRootNode);
    printf("------ inorder -------\n");
    inorder(tree->pRootNode);
    printf("------ postorder -------\n");
    postorder(tree->pRootNode);
}