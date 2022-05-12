#include "bintree.h"

BinTree* makeBinTree(BinTreeNode rootNode)
{
    BinTree *pTree;
    BinTreeNode *pRootNode;

    pTree = calloc(1, sizeof(BinTree));
    pRootNode = calloc(1, sizeof(BinTreeNode));
    pTree->pRootNode = pRootNode;
    *pRootNode = rootNode;

    return pTree;
}
BinTreeNode* getRootNodeBT(BinTree* pBinTree)
{
    return (pBinTree->pRootNode);
}
/* 

 parentnode 반환? 생성한 childnode 반환?
 
 만약 이미 자식노드가 있다면? 
    1. 재귀로 맨 밑에까지 가서 알아서 넣어준다
    2. 이미 자식이 있다는 에러를 준다.

*/
BinTreeNode* insertLeftChildNodeBT(BinTreeNode* pParentNode, BinTreeNode element)
{
    BinTreeNode *pChild;
    
    if (pParentNode->pLeftChild)
    {
        printf ("LeftChild Node already exist \n");
        return (NULL);
    }
    pChild = calloc(1, sizeof(BinTreeNode));
    *pChild = element;
    pParentNode->pLeftChild = pChild;
    return pChild;
}
BinTreeNode* insertRightChildNodeBT(BinTreeNode* pParentNode, BinTreeNode element)
{
    BinTreeNode *pChild;
    
    if (pParentNode->pRightChild)
    {
        printf ("RightChild Node already exist \n");
        return (NULL);
    }
    pChild = calloc(1, sizeof(BinTreeNode));
    *pChild = element;
    pParentNode->pRightChild = pChild;
    return pChild;
}
BinTreeNode* getLeftChildNodeBT(BinTreeNode* pNode)
{
    return (pNode->pLeftChild);
}
BinTreeNode* getRightChildNodeBT(BinTreeNode* pNode)
{
    return (pNode->pRightChild);
}
void deleteBinTree(BinTree* pBinTree)
{
    if (pBinTree)
    {
        deleteBinTreeNode(&pBinTree->pRootNode);
        free(pBinTree);
        memset(pBinTree, 0, sizeof(BinTree));
    }
}
// 댕글링 포인터 처리?
void deleteBinTreeNode(BinTreeNode** pNode)
{
    if (*pNode)
    {
        deleteBinTreeNode(&(*pNode)->pLeftChild);
        deleteBinTreeNode(&(*pNode)->pRightChild);
        free(*pNode);
        *pNode = NULL;
    }
}