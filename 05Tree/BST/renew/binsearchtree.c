#include "binsearchtree.h"

BinSearchTree* createBinSearchTree(BinSearchTreeNode rootNode)
{
	BinSearchTree	*pTree;
	pTree = calloc(1, sizeof(BinSearchTree));
	if (!pTree)
		return FALSE;
	return (pTree);
}

BinSearchTreeNode* insertBSTNode(BinSearchTree *pBinSearchTree, BinSearchTreeNode element)
{
	BinSearchTreeNode *pParentNode;
	BinSearchTreeNode *pNewNode;

	if (pBinSearchTree == NULL)
		return (FALSE);
	pParentNode = pBinSearchTree->pRootNode;
	//새 노드를 넣을 부모노드 찾기
	while (pParentNode)
	{
		if (element.key == pParentNode->key)
		{
			printf("중복된 키값 \n");
			return (FALSE);
		}
		else if (element.key < pParentNode->key)
		{
			if(!pParentNode->pLeftChild)
				break;
			else
				pParentNode = pParentNode->pLeftChild;
		}
		else
			pParentNode = pParentNode->pRightChild;
	}
	pNewNode = calloc(1, sizeof(BinSearchTreeNode));
	if (!pNewNode)
		return (FALSE);
	*pNewNode = element;
	// 부모노드가 없다면 루트노드인것(처음 추가할 경우)
	if(!pParentNode)
		pBinSearchTree->pRootNode = pNewNode;
	// 부모노드가 있다면 왼쪽 / 오른쪽 찾아서 넣기
	else
	{
		if (pParentNode->key < pNewNode->key)
			pParentNode->pRightChild = pNewNode;
		else
			pParentNode->pLeftChild = pNewNode;
	}
	return (TRUE);
}
int deleteBSTNode(BinSearchTree *pBinSearchTree, int key)
{
	BinSearchTreeNode *pDelNode;
	BinSearchTreeNode *pParentNode;
	BinSearchTreeNode *pPreCandidate;
	BinSearchTreeNode *pCandidate;
	BinSearchTreeNode *pChildNode;

	if (!pBinSearchTree)
		return (FALSE);
	pDelNode = pBinSearchTree->pRootNode;
	//삭제할 노드의 key값으로 노드를 찾음
	while (pDelNode)
	{
		if (key == pDelNode->key)
			break;
		pParentNode = pDelNode;
		if (key < pDelNode->key)
			pDelNode = pDelNode->pLeftChild;
		else
			pDelNode = pDelNode->pRightChild;
	}
	if (!pDelNode)
	{
		printf("존재하지 않는 키\n");
		return (FALSE);
	}
	//자식이 없는 노드를 삭제
	if (!pDelNode->pLeftChild && !pDelNode->pRightChild)
	{
		if (!pParentNode)
			pBinSearchTree->pRootNode = NULL;
		else
		{
			if (pParentNode->pLeftChild == pDelNode)
				pParentNode->pLeftChild = NULL;
			else
				pParentNode->pRightChild = NULL;
		}
	}
	//자식이 둘 다 있을경우 (왼쪽 서브트리에서 가장 큰값을 찾아서 올림)
	else if (pDelNode->pLeftChild && pDelNode->pRightChild)
	{
		pPreCandidate = pDelNode;
		pCandidate = pDelNode->pLeftChild;
		while (pCandidate->pRightChild)
		{
			pPreCandidate = pCandidate;
			pCandidate = pCandidate->pRightChild;
		}
		pPreCandidate->pRightChild = pCandidate->pLeftChild;
		pCandidate->pLeftChild = pDelNode->pLeftChild;
		pCandidate->pRightChild = pDelNode->pRightChild;
		//지우려는 노드가 루트노드가 아닐때
		if (!pParentNode)
		{
			if(pParentNode->pLeftChild == pDelNode)
				pParentNode->pLeftChild = pCandidate;
			else
				pParentNode->pRightChild = pCandidate;
		}
		//지우려는 노드가 루트노드일때
		else
			pBinSearchTree->pRootNode = pCandidate;
	}
	//자식이 하나만 있는경우
	else
	{
		//지울 노드의 왼쪽 자식이있는경우
		if (!pDelNode->pLeftChild)
			pChildNode = pDelNode->pLeftChild;
		else
			pChildNode = pDelNode->pRightChild;
		//지우려는 노드가 루트노드가 아닌경우 연결
		if (pParentNode)
		{
			if (pParentNode->pLeftChild == pDelNode)
				pParentNode->pLeftChild = pChildNode;
			else
				pParentNode->pRightChild = pChildNode;
		}
		//지우려는 노드가 루트노드일때
		else
			pBinSearchTree->pRootNode = pChildNode;
	}
	free(pDelNode);
	return (TRUE);
}
BinSearchTreeNode* getRootNodeBT(BinSearchTree* pBinSearchTree);



void deleteBinTree(BinSearchTree* pBinSearchTree)
{
    if (pBinSearchTree)
    {
        deleteBinTreeNode(&pBinSearchTree->pRootNode);
        free(pBinSearchTree);
        memset(pBinSearchTree, 0, sizeof(BinSearchTree));
    }
}

// 댕글링 포인터 처리?
void deleteBinTreeNode(BinSearchTreeNode** pNode)
{
    if (*pNode)
    {
        deleteBinTreeNode(&(*pNode)->pLeftChild);
        deleteBinTreeNode(&(*pNode)->pRightChild);
        free(*pNode);
        *pNode = NULL;
    }
}