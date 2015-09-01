/*
 * PriorityQueue/ BinaryHeap/ MinHeap
 * implementation
 * binaryHeap.c
*/

#include "binaryHeap.h"
#include <stdio.h>
#include <malloc.h>

struct HeapStruct
{
	int Capacity;
 	int Size;
 	ElementType * Elements;
};

PriorityQueue
Initialize(int MaxElements)
{
 	PriorityQueue H;
 	if (MaxElements < MINPQSIZE)
 	{
 		printf("Priority queue size is too small\n");
 		return NULL;
 	}
 	H = malloc(sizeof(struct HeapStruct));
 	if (H == NULL)
 	{
 		printf("Out of space!!!\n");
 		return NULL;
 	}
 	//头节点从索引1开始比较好处理，这里还是尝试从0开始，这样根据子节点求父节点位置就是(i-1)/2
 	H->Elements = malloc(MaxElements * sizeof(ElementType));
 	if (H->Elements == NULL)
 	{
 		printf("Out of space!!!\n");
 		free(H);
 		return NULL;
 	}
 	H->Capacity = MaxElements;
 	H->Size = 0;

 	return H;

}

inline int 
IsFull(PriorityQueue H)
{
	return ((H->Capacity == H->Size) ? 1 : 0);
}

inline int
IsEmpty(PriorityQueue H)
{
	return ((H->Size == 0) ? 1 : 0);
}

inline ElementType
FindMin(PriorityQueue H)
{
	return ((H->Size == 0) ? (ElementType)NULL : H->Elements[0]);
}

inline void
MakeEmpty(PriorityQueue H)
{
	H->Size = 0;
}

void 
Destroy(PriorityQueue H)
{
	int i = H->Capacity - 1;
	for ( ; i >= 0; i --)
	{
		free(H->Elements + i);
	}
	free(H);
}

int
Insert(ElementType X, PriorityQueue H)
{
	int i;
	if (IsFull(H))
	{
		printf("Priority queue is full!!\n");
		return 0;
	}
	if (IsEmpty(H))
	{
		H->Elements[H->Size++] = X;
	}
	//插入的节点先放在尾部，然后逐层和父节点比较，上滤
	for (i = H->Size++; H->Elements[(i - 1) / 2] > X; i /=2)
		H->Elements[i] = H->Elements[i / 2];
	H->Elements[i] = X;
	return 1;
}

ElementType *
DeleteMin(PriorityQueue H)
{
	int i, Child;
	ElementType *MinElement, LastElement;
	if (IsEmpty(H))
	{
		printf("Priority queue is empty!!\n");
		return NULL;
	}
	MinElement = H->Elements + 0;
	/*交换头节点和尾节点，要删除的MinElement就放在了尾部，然后对新的头节点做下滤操作来调整最小堆*/
	H->Elements[0] = H->Elements[H->Size - 1];
	LastElement = H->Elements[H->Size - 1];
	/*父节点为i，子节点为2i+1和2i+2*/
	/*有儿子才做调整*/
	for (i = 0; 2*i+1 < H->Size; i = Child)
	{
		/*在左儿子和右儿子中寻找比父节点小的，取代父节点*/
		/*左儿子*/
		Child = 2*i+1;
		/*右儿子*/
		if ((Child + 1 < H->Size) && (H->Elements[Child + 1] < H->Elements[Child]))
			Child ++;
		/*需要调整*/
		if (H->Elements[Child] < H->Elements[i])
			H->Elements[i] = H->Elements[Child];
		/*不需要调整则跳出*/
		else
			break;
	}
	return MinElement;
}