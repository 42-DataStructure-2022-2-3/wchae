#include "bintree.h"
//전위 V L R

void    preOrder(BinTreeNode *pTreeNode)
{
    if (!pTreeNode)
        return ;
    printf("%c ", pTreeNode->data);
    pTreeNode->visited = 1;
    preOrder(pTreeNode->pLeftChild);
    preOrder(pTreeNode->pRightChild);
}

//중위 L V R

void    inOrder(BinTreeNode *pTreeNode)
{
    if (!pTreeNode)
        return ;
    pTreeNode->visited = 1;
    inOrder(pTreeNode->pLeftChild);
    printf("%c ", pTreeNode->data);
    inOrder(pTreeNode->pRightChild);
}

//후위 L R V
void    postOrder(BinTreeNode *pTreeNode)
{
    if (!pTreeNode)
        return ;
    pTreeNode->visited = 1;
    postOrder(pTreeNode->pLeftChild);
    postOrder(pTreeNode->pRightChild);
    printf("%c ", pTreeNode->data);
}