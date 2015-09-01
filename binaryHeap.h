#ifndef _BinHeap_H
#define _BinHeap_H

#define MINPQSIZE 1
#define INT
/*
 * 二叉堆有两个最基本的性质：结构性（完全二叉树）和堆序性（根最小/大，其余父节点都比自己的子节点小/大）
*/
/*声明最大(小)堆结构，也叫优先队列，二叉堆*/
struct HeapStruct;
typedef struct HeapStruct * PriorityQueue;
typedef int ElementType;

PriorityQueue Initialize(int MaxElements);
void Destroy(PriorityQueue);
void MakeEmpty(PriorityQueue H);
/*插入一个节点到优先队列中，插入成功返回1，失败返回0。插入的最坏时间复杂度为O(log N)*/
int Insert(ElementType X, PriorityQueue H);
/*删除优先队列中最小的元素，成功则返回最小元素指针，失败返回NULL。删除的最坏时间复杂度为O(log N)*/
ElementType *DleteMin(PriorityQueue H);
ElementType FindMin(PriorityQueue H);
inline int IsEmpty(PriorityQueue H);
inline int IsFull(PriorityQueue H);

#endif