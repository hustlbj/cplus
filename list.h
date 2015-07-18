//:List
#ifndef MY_LIST_H
#define MY_LIST_H
#include <stdlib.h>
#include <stdio.h>

typedef int ElementType;
struct ListNode
{
	ElementType m_nValue;
	ListNode* m_pNext;
};


class List
{
public:
	List() { m_pList = NULL; }
	~List() { }
	//这里需要注意传值和传地址。。。ListNode* 还是只传入了指针变量的值，用ListNode** 传值指针变量的地址才行
	//所以pHead是头节点指针变量的地址
	void AddToTail(ListNode** pHead, ElementType value);
	void RemoveNode(ListNode** pHead, ElementType value);
	//要删除的节点是ListNode，里面保存了完整的value和next，所以删除该节点是有可能在O(1)时间完成的，如果只是传入value，那还得比较
	void DeleteNode(ListNode** pHead, ListNode* pToBeDeleted);
	ListNode* m_pList; 
private:
	
};
#endif  