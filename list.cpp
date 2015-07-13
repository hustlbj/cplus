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

void List::RemoveNode(ListNode** pHead, ElementType value)
{
	//链表为空
	if (pHead == NULL || *pHead == NULL)
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

