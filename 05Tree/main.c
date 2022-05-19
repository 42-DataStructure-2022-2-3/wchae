#include "bintree.h"

BinTree *treeCopy(BinTree *pTree)
{
	BinTree *pTree;
}

int main(void)
{
    BinTreeNode pNode;
    BinTreeNode *pFirstLeftNode;
    BinTreeNode *pFirstRightNode;
    
    BinTreeNode *pSecondLeftNode;
    BinTreeNode *pSecondRightNode;

    BinTreeNode *pSecondLeftNode2;
    BinTreeNode *pSecondRightNode2;

    pNode.data = 30;
    pNode.visited = 0;
    pNode.pLeftChild = NULL;
    pNode.pRightChild = NULL;
    BinTree *pTree = makeBinTree(pNode);

    pNode.data = 20;
    pFirstLeftNode = insertLeftChildNodeBT(pTree->pRootNode, pNode); // B
    
    pNode.data = 40;
    pFirstRightNode = insertRightChildNodeBT(pTree->pRootNode, pNode); // C

     // Level 2
    pNode.data = 10;
    pSecondLeftNode = insertLeftChildNodeBT(pFirstLeftNode, pNode);  // D
    
    pNode.data = 24;
    pSecondRightNode = insertRightChildNodeBT(pFirstLeftNode, pNode); // E

    pNode.data = 34;
    pSecondLeftNode2 = insertLeftChildNodeBT(pFirstRightNode, pNode);  // F
    
    pNode.data = 46;
    pSecondRightNode2 = insertRightChildNodeBT(pFirstRightNode, pNode); // G
    
    // Level 3
    pNode.data = 6;
    insertLeftChildNodeBT(pSecondLeftNode, pNode);  // H
    
    pNode.data = 14;
    insertRightChildNodeBT(pSecondLeftNode, pNode); // I
    
    pNode.data = 22;
    insertLeftChildNodeBT(pSecondRightNode, pNode);  // J

    deleteBinTreeNode(&pTree->pRootNode);
    deleteBinTree(pTree);
    
    system("leaks a.out");
}