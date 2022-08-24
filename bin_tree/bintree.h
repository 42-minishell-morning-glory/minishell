#ifndef _BIN_TREE_
#define _BIN_TREE_

# include <stdio.h>
# include <stdlib.h>

typedef struct s_node
{
	char			data;
	int				visited;

	struct s_node	*pLeftChild;
	struct s_node	*pRightChild;
}					t_node;

typedef struct s_bintree
{
	struct s_node	*pRootNode;
}					t_bintree;

t_bintree *makeBinTree(t_node rootNode);
t_node *getRootNodeBT(t_bintree *pTree);
t_node *insertLeftChildNodeBT(t_node *pParentNode, t_node element);
t_node *insertRightChildNodeBT(t_node *pParentNode, t_node element);
t_node *getLeftChildNodeBT(t_node *pNode);
t_node *getRightChildNodeBT(t_node *pNode);
void deleteBinTree(t_bintree *pTree);
void delete_node(t_node *pNode);

#endif

#ifndef _COMMON_TREE_DEF_
#define _COMMON_TREE_DEF_

#define TRUE		1
#define FALSE		0

#endif