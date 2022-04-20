#include "circularlist.h"

CircularList* createCircularList()
{

}
int addCLElement(CircularList* pList, int position, ListNode element)
{
	//0 인덱스의 노드추가인가?
		//리스트가 비었는가?
	
	//링크드리스트의 추가
}
int removeCLElement(CircularList* pList, int position)
{
	//0 인덱스 노드 제거인가?
		// 리스트의 마지막 노드인가?
			//free
		
		// 헤드를 지울노드의 다음노드로 지정
		// 마지막노드의 다음노드를 지울노드 다음노드로 지정(헤드가 가르키는 노드)

	// 기존 링크드리스트 해제
}
ListNode* getCLElement(CircularList* pList, int position);
void clearCircularList(CircularList* pList);
void deleteCircularList(CircularList* pList);
int getCircularListLength(CircularList* pList);

int	main(void)
{
	CircularList *pList = createCircularList();
	ListNode node;

	node.data = 1;
	addCLElement(pList, 0, node);
	node.data = 2;
	addCLElement(pList, 1, node);
	node.data = 3;
	addCLElement(pList, 2, node);
	node.data = 4;
	addCLElement(pList, 0, node);
	node.data = 0;
	addCLElement(pList, 3, node);
	displayCircularList(pList);
}