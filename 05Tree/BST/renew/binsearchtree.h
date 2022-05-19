#ifndef _BIN_SEARCH_TREE_
#define _BIN_SEARCH_TREE_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct BinSearchTreeNodeType
{
	int data;
	int key;

	struct BinSearchTreeNodeType* pLeftChild;
	struct BinSearchTreeNodeType* pRightChild;
} BinSearchTreeNode;

typedef struct BinTreeType
{
	struct BinSearchTreeNodeType* pRootNode;
} BinSearchTree;
BinSearchTree* createBinSearchTree(BinSearchTreeNode rootNode);
BinSearchTreeNode* insertBSTNode(BinSearchTree *pBinSearchTree, BinSearchTreeNode element);
BinSearchTreeNode* deleteBSTNode(BinSearchTree *pBinSearchTree, int key);

BinSearchTreeNode* getRootNodeBT(BinSearchTree* pBinSearchTree);
/*BST */
BinSearchTreeNode* searchBSTRecursivee(BinSearchTreeNode *pTreeNode, int key);
BinSearchTreeNode* searchBST(BinSearchTree *pBinSearchTree, int key);
/*BST END*/
// BinSearchTreeNode* insertLeftChildNodeBT(BinSearchTreeNode* pParentNode, BinSearchTreeNode element);
// BinSearchTreeNode* insertRightChildNodeBT(BinSearchTreeNode* pParentNode, BinSearchTreeNode element);
// BinSearchTreeNode* getLeftChildNodeBT(BinSearchTreeNode* pNode);
// BinSearchTreeNode* getRightChildNodeBT(BinSearchTreeNode* pNode);
void deleteBinSearchTree(BinSearchTree* pBinSearchTree);
void deleteBinSearchTreeNode(BinSearchTreeNode* pTreeNode);

void deleteBinTree(BinSearchTree* pBinTree);
void deleteBinTreeNode(BinSearchTreeNode** pNode);

#endif

#ifndef _COMMON_TREE_DEF_
#define _COMMON_TREE_DEF_

#define TRUE		1
#define FALSE		0

#endif