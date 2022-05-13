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
static BinTreeNode *searchRecursive(BinTreeNode *pNode, BinTreeNode key)
{
    if (!pNode)
        return (NULL);
    if (key.data == pNode->data)
        return (pNode);
    else if ( key.data < pNode->data)
        searchRecursive(pNode->pLeftChild, key);
    else if (pNode->data < key.data)
        searchRecursive(pNode->pRightChild, key);
}

BinTreeNode* searchBST(BinTree *pBinTree, BinTreeNode key)
{
    if (!pBinTree)
        return NULL;
    return (searchRecursive(pBinTree->pRootNode, key));
}

static BinTreeNode *insertBSTNodeRecur(BinTreeNode *pNode, BinTreeNode key)
{
    if (key.data == pNode->data)
    {
        printf("이미 존재하는 값입니다.\n");
        return (NULL);
    }
    else if ( key.data < pNode->data)
    {
        if (pNode->pLeftChild)
            insertBSTNodeRecur(pNode->pLeftChild, key);
        else
            return (pNode);    
    }
    else if (pNode->data < key.data)
    {
        if (pNode->pRightChild)
            insertBSTNodeRecur(pNode->pRightChild, key);
        else
            return (pNode);       
    }
}

BinTreeNode *insertBSTNode(BinTree *pBinTree, BinTreeNode key)
{
    BinTreeNode *parentNode;

    parentNode = insertBSTNodeRecur(pBinTree->pRootNode, key);
    if (!parentNode)
        return (NULL);
    if (parentNode->data < key.data)
        return (insertLeftChildNodeBT(parentNode, key));
    else
        return (insertRightChildNodeBT(parentNode, key));
}

static BinTreeNode *deleteBSTNodeRecur(BinTreeNode *parentNode, BinTreeNode key)
{
    if (!parentNode)
        return (NULL);
    if (key.data == parentNode->pLeftChild->data || key.data == parentNode->pRightChild->data )
        return (parentNode);
    else if ( key.data < parentNode->data)
        deleteBSTNodeRecur(parentNode->pLeftChild, key);  
    else if (parentNode->data < key.data)
        deleteBSTNodeRecur(parentNode->pRightChild, key);  
}

//만약 14 를 삭제하는경우 tree 41page
static BinTreeNode* deleteLeafNode(BinTree *pBinTree, BinTreeNode key)
{
    BinTreeNode *pDeleteNode;
    BinTreeNode *parentNode;

    if (pBinTree->pRootNode->data == key.data)
    {
        pDeleteNode = pBinTree->pRootNode;
        pBinTree->pRootNode = NULL;
        return pDeleteNode;
    }
    parentNode = deleteBSTNodeRecur(pBinTree->pRootNode, key);
    if (parentNode->pLeftChild->data == key.data)
    {
        pDeleteNode = parentNode->pLeftChild;
        parentNode->pLeftChild = NULL;
    }
    else
    {
        pDeleteNode = parentNode->pRightChild;
        parentNode->pRightChild = NULL;
    }
    return pDeleteNode;
}
static BinTreeNode *deleteOnlyChildNode(BinTree *pBinTree, BinTreeNode key)
{
    BinTreeNode *pDeleteNode;
    BinTreeNode *parentNode;

    parentNode = deleteBSTNodeRecur(pBinTree->pRootNode, key);
        if (pDeleteNode->pLeftChild)
        {
            if (parentNode->pLeftChild->data == pDeleteNode->data)
                parentNode->pLeftChild = pDeleteNode->pLeftChild;
            else 
                parentNode->pRightChild = pDeleteNode->pLeftChild;
        }
        else
        {
            if (parentNode->pLeftChild->data == pDeleteNode->data)
                parentNode->pLeftChild = pDeleteNode->pRightChild;
            else 
                parentNode->pRightChild = pDeleteNode->pRightChild;
        }
        return pDeleteNode;
}


BinTreeNode* deleteBSTNode(BinTree *pBinTree, BinTreeNode key)
{
    BinTreeNode *pDeleteNode;
    BinTreeNode *parentNode;
    
    pDeleteNode = searchBST(pBinTree, key);
    if (!pDeleteNode)
        return (NULL);
    else if (!pDeleteNode->pLeftChild && !pDeleteNode->pRightChild) // 단말 노드인 경우
        pDeleteNode = deleteLeafNode(pBinTree, key);
     // 자식이 2개인 경우
    else if (pDeleteNode->pLeftChild && pDeleteNode->pRightChild)
    {
        BinTreeNode *pCandidate = pDeleteNode->pLeftChild;
        BinTreeNode *pParentCandidate = pDeleteNode;
        while (pCandidate->pRightChild)
        {
            pParentCandidate = pCandidate;
            pCandidate = pCandidate->pRightChild;
        }
        if (pDeleteNode->data != pBinTree->pRootNode->data)//지울노드가 루트노드가 아닌경우
        {
            parentNode = deleteBSTNodeRecur(pBinTree, key);
            if (parentNode->pLeftChild->data == pDeleteNode->data) // 지울노드가 왼쪽에있다
                parentNode->pLeftChild = pCandidate;
            else// 지울 노드가 오른쪽에있다
                parentNode->pRightChild = pCandidate;
        }
        pParentCandidate->pRightChild = pCandidate->pLeftChild;
        pCandidate->pLeftChild = pDeleteNode->pLeftChild;
        pCandidate->pRightChild = pDeleteNode->pRightChild;            
    }
    else// 자식이 1개인 경우
        pDeleteNode = deleteOnlyChildNode(pBinTree, key);
    return pDeleteNode;
}