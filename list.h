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
	ListNode* m_pList; 
};
#endif  