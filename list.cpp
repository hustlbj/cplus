//:list.cpp
#include "list.h"
#include <stdio.h>
#include <malloc.h>

//这里需要注意传值和传地址。。。ListNode* 还是只传入了指针变量的值，用ListNode** 传值指针变量的地址才行
//所以pHead是头节点指针变量的地址，初始化时(*pHead)=NULL
void List::AddToTail(ListNode** pHead, ElementType value)
{
	ListNode* pNew = new ListNode();
	//ListNode* pNew = (ListNode*)malloc(sizeof(struct ListNode));
	pNew->m_nValue = value;
	pNew->m_pNext = NULL;
	if (*pHead == NULL)
	{
		*pHead = pNew;
		printf("head: %d\t, %ld\t", pNew->m_nValue, pHead);
	}
	else
	{
		ListNode* pNode = *pHead;
		while (pNode->m_pNext != NULL)
		{
			pNode = pNode->m_pNext;
		}
		pNode->m_pNext = pNew;
		printf("insert: %d\t", pNew->m_nValue);
	}
}
//这里可以不必传入指针的地址。。如果链表为空，则ListNode* p == NULL，而 &p 肯定不为NULL，因为这是一个存在的变量
void List::RemoveNode(ListNode** pHead, ElementType value)
{
	//链表为空
	if (*pHead == NULL)
		return;
	ListNode* pToBeDeleted = NULL;
	//要删除的节点是头节点
	if ((*pHead)->m_nValue == value)
	{
		pToBeDeleted = *pHead;
		//下一个节点来作为头节点
		*pHead = (*pHead)->m_pNext;
	}
	else
	{
		ListNode* pNode = *pHead;
		//pNode是索引节点，pNode->m_pNext才是真正的受检节点
		//pNode指向当前节点，但是直接判断下一个节点，这样的好处是：
		//只用一个指针就可以删除这个节点，pNode->m_pNext = pNode->m_pNext->m_pNext;
		while (pNode->m_pNext != NULL 
			&& pNode->m_pNext->m_nValue != value)
		{
			pNode = pNode->m_pNext;
		}
		if (pNode->m_pNext != NULL && pNode->m_pNext->m_nValue == value)
		{
			pToBeDeleted = pNode->m_pNext;
			pNode->m_pNext = pNode->m_pNext->m_pNext;
		} 
		if (pToBeDeleted != NULL)
		{
			//C++用new和delete管理内存
			delete pToBeDeleted;
			pToBeDeleted = NULL;
		}
	}
}
/*
 T13. O(1)时间复杂度删除单链表中的节点
 这里可以不必传入指针的地址。。同上。。。
*/
void List::DeleteNode(ListNode** pHead, ListNode* pToBeDeleted)
{
	if (!(*pHead) || !pToBeDeleted)
		return ;
	//如果要删除的Node不是尾节点，把该节点的下一个节点的内容复制过来，直接删除下一个节点即可
	if (pToBeDeleted->m_pNext != NULL)
	{
		ListNode* pNext = pToBeDeleted->m_pNext;
		pToBeDeleted->m_nValue = pNext->m_nValue;
		pToBeDeleted->m_pNext = pNext->m_pNext;
		delete pNext;
		pNext = NULL;
	}
	//要删除的Node是头节点，直接删除
	else if (*pHead == pToBeDeleted)
	{
		delete pToBeDeleted;
		pToBeDeleted = NULL;
		*pHead = NULL;
	}
	//要删除的Node是尾节点，并且链表中还有多个节点，此时只能遍历删除
	else
	{
		ListNode* pNode = *pHead;
		//找到前一个节点
		while (pNode->m_pNext != pToBeDeleted)
		{
			pNode = pNode->m_pNext;
		}
		pNode->m_pNext = NULL;
		delete pToBeDeleted;
		pToBeDeleted = NULL;

	}
}

//这里需要传入指针的地址，以便删除头节点并让链表指向NULL
void List::Clean(ListNode** pHead)
{
	if (!(*pHead))
		return;
	//从头开始清除
	ListNode* temp = NULL;
	while (*pHead)
	{
		temp = *pHead;
		*pHead = (*pHead)->m_pNext;
		delete temp;
	}

	*pHead = NULL;
}