//:sorting.cpp

#include <iostream>
#include "sorting.h"

void Swap(int& a, int& b)
{
	int t = a;
	a = b;
	b = t;
}

void swap(int A[], int i, int j)
{
	int temp = A[i];
	A[i] = A[j];
	A[j] = temp;
}

//传递数组给函数时，实际是传递了一个指针，函数里的sizeof只能求出指针的大小，不能求数组的大小
void PrintArray(int A[], int n)
{
	//std::cout << sizeof(A) << std::endl;
	for (int i = 0; i < n; ++i)
	{
		std::cout << A[i] << ", ";
	}
	std::cout << std::endl;

}

//直接插入排序，稳定，最坏时间O(n^2)，辅助空间O(1)
void InsertSort(int A[], int n)
{
	int i, j;
	int temp;
	if (n >= 2)
	{
		for (i = 1; i < n; i ++)
		{
			temp = A[i];
			j = i - 1;
			while (j >= 0 && temp < A[j])
			{
				A[j+1] = A[j];
				j --;
			}
			A[j+1] = temp;
		}
	}
}
//希尔插入排序，不稳定，时间复杂度依赖于增量序列涉及数学难题约为O(n^1.3)最坏也是O(n^2)，辅助空间O(1)
void ShellSort(int A[], int n)
{
	int dk, i, j;
	int temp;
	//步长变化
	for (dk = n/2; dk >= 1; dk = dk/2)
	{
		//从dk索引开始以后的元素，分别向前面的[0...dk-1]进行插入排序
		for (i = dk; i < n; i ++)
		{
			//也是插入排序，只不过每次是和前dk比
			temp = A[i];
			j = i - dk;
			while (j >= 0 && temp < A[j])
			{
				A[j+dk] = A[j];
				j = j - dk;
			}
			A[j+dk] = temp;
		}
	}
}
//交换，冒泡排序，最坏情况和平均时间复杂度为O(n^2)，空间复杂度O(1)，稳定
void BubbleSort(int A[], int n)
{
	int i, j, flag, temp;
	//小元素上浮，第0、1、2、3。。。依次排好序
	for (i = 0; i < n-1; i ++)
	{
		flag = 0; //表示本趟冒泡是否发生交换的标志
		//从底部开始相邻比较，较小的元素交换上浮
		for (j = n-1; j > i; j --)
		{
			if (A[j] < A[j-1])
			{
				temp = A[j];
				A[j] = A[j-1];
				A[j-1] = temp;
				flag = 1;
			}
		}
		if (!flag)
			break;
	}
}
//前后两个指针向中间扫描，不稳定
int LHPartition(int A[], int low, int high)
{
	int pivot = A[low];
	while(low < high)
	{
		while(low < high && A[high] >= pivot) 
			--high;
		A[low] = A[high];
		while(low < high && A[low] <= pivot) 
			++low;
		A[high] = A[low];
	}
	A[low] = pivot;
	return low;
}
//半区保序的Partition，指针从哪边开始，哪个半区就是保序的
int LLPartition(int A[], int low, int high)
{
	//选择基准元，以最右边一个为基准
	int pivot = A[high];
	int temp;
	//i指针为左区指针，依次"存放"不大于pivot的元素
	int i = low - 1;
	//j指针从左向右依次扫描，"发现"不大于pivot的元素
	for (int j = low; j < high; j ++)
	{
		//找到不大于枢纽元的元素位置
		if (A[j] <= pivot)
		{
			++ i;
			if (i != j)
				//把满足条件的j放到左区i位置
				Swap(A[i], A[j]);
		}
		//没找到则继续向右扫描，直到到达尾部
	}
	//最后把枢纽元交换到中间
	Swap(A[i+1], A[high]);
	//返回枢纽元位置
	return i+1;
}
void QuickSort(int A[], int low, int high)
{
	if (low < high)
	{
		int pivotpos = LHPartition(A, low, high);
		QuickSort(A, low, pivotpos - 1);
		QuickSort(A, pivotpos+1, high);
	}
}

bool isUpper(char a)
{
	if (a >= 'A' && a <= 'Z')
	{
		return true;
	}
	return false;
}
bool isLower(char a)
{
	if (a >= 'a' && a <= 'z')
	{
		return true;
	}
	return false;
}
//利用快速排序的一趟，将小写字母放在左边，大写字母放在右边
void CharPartition(char A[], int low, int high)
{
	while (low < high)
	{
		while(low < high && isUpper(A[high])) --high;
		while(low < high && isLower(A[low])) ++low;
		char temp = A[high];
		A[high] = A[low];
		A[low] = A[high];
	}
}
//一个集合中有三种元素，按元素聚集排序，假设为一个数组中有三种数字0、1、2，将0排在左区，1排在中区，2排在右区
void ThreePartition(int A[], int low, int high)
{
	int current, begin, end;
	current = low;
	begin = low;
	end = high;
	while (current <= end)
	{
		if (A[current] == 0)
		{
			//把0交换到左区begin指针位置
			swap(A, current, begin);
			current ++;
			//begin指针往右走，保证它的左边都是0
			begin ++;
		}
		else if (A[current] == 1)
		{
			current ++;
		}
		else
		{
			//把2交换到右区end指针
			swap(A, current, end);
			//end指针往左走，保证它的右边都是2
			end --;
		}
	}
}

//利用快速排序Partition函数找出数组中的topK，但不能保证topK是有序的
void getTopK(int input[], int n, int output[], int k)
{
	if (input == NULL || output == NULL || k > n || n <= 0 || k <= 0)
	{
		return;
	}
	int start = 0;
	int end = n-1;
	//一次划分函数
	//LHPartition为快速排序默认划分函数，以首元作为枢纽元，low和high两个指针从两边向中间扫描
	int index = LHPartition(input, start, end);
	//index = k-1说明[0...k-1]这k个数字是topK，但不能保证它们是有序的。
	while (index != k-1)
	{
		if (index >= k-1)
		{
			end = index - 1;
			index = LHPartition(input, start, end);
		}
		else
		{
			start = index + 1;
			index = LHPartition(input, start, end);
		}
	}
	for (int i = 0; i < k; i ++)
	{
		output[i] = input[i];
	}
}
//选择，简单选择排序，时间复杂度始终是O(n^2)，空间复杂度O(1)，不稳定（交换时被前面换到后面）
void SelectionSort(int A[], int n)
{
	int min;
	for (int i = 0; i < n; i ++)
	{
		min = i;
		for (int j = i+1; j < n; j ++)
		{
			//元素移动很少次，每轮循环只记录下标，每轮swap移动3次，总共最多移动3(n-1)次
			//比较次数始终是n(n-1)/2
			if (A[j] < A[min])
				min = j;
		}
		if (min != i)
			swap(A, i, min);
	}
}

void AdjustDown(int A[], int k, int len)
{
	//A[0]位置缓存当前子树的根节点
	A[0] = A[k];
	//对其子节点以下进行调整
	for (int i = 2*k; i <= len; i *= 2)
	{
		//i<len 如果有两个子节点，则从中选择较大的一个
		if (i < len && A[i] < A[i+1])
			i ++;
		//子树根节点本身就满足，不需要调整
		if (A[0] >= A[i])
			break;
		//否则进行调整，子树根节点换成较大的子节点，然后k=i对子节点进行调整
		else
		{
			A[k] = A[i];
			k = i;
		}
	} //for
	A[k] = A[0];
}
//选择，堆排序，最好最坏平均情况下时间复杂度为O(nlogn)，空间复杂度为O(1)，建堆的时间复杂度为O(n)
void buildMaxHeap(int A[], int len)
{
	for (int i = len/2; i > 0; i --)
		AdjustDown(A, i, len);
}
void HeapSort(int A[], int n)
{
	buildMaxHeap(A, n);
	// >1表示最后剩一个根节点未排序时，它正好就是在哪个位置，无需交换
	for (int i = n; i > 1; --i)
	{
		//把大顶堆的根节点交换到最后，后面都是排好序的
		swap(A, i, 1);
		//由于交换，根节点破坏了大顶堆条件，则从根节点开始向下调整
		AdjustDown(A, 1, i-1);
	}
}

int B[N]; 
//A是原始数组，全局变量B是辅助缓存数组，对low~mid, mid+1~high进行合并
void Merge(int A[], int low, int mid, int high)
{
	int i, j, k;
	//先把A中原来的数值缓存在B中，排好序的再放到A中
	for (k = low; k <= high; k ++)
		B[k] = A[k];
	//i j分别是low~mid和mid+1~high的半区指针，k是A中存放排好序的指针
	for (i = low, j = mid + 1, k = i; i <= mid && j <= high; k ++)
	{
		//左半区的元素小的话就先复制到A中
		if (B[i] < B[j])
			A[k] = B[i++];
		else
			A[k] = B[j++];
	}
	//最后如果有个半区剩下了元素，则把剩下的复制到A中
	while (i <= mid) A[k++] = B[j++];
	while (j <= high) A[k++] = B[j++];
}
//归并排序，每一趟归并的时间复杂度为O(n)，共需进行log n趟归并，所以算法的时间复杂度为O(n log n)，空间复杂度为O(n)，稳定
void MergeSort(int A[], int low, int high)
{
	//至少2个元素，如果递归到只有1个元素则不会执行下一层MergeSort，返回到上一层执行Merge
	if (low < high)
	{
		int mid = (low + high) / 2;
		MergeSort(A, low, mid);
		MergeSort(A, mid+1, high);
		Merge(A, low, mid, high);
	}
}

struct ListNode {
	int value;
	ListNode* pNext;
};
//利用二路归并排序中的merge思想，递归合并两个已经排好序的子链表
ListNode* mergeList(ListNode* list1, ListNode* list2)
{
	if (list1 == NULL)
		return list2;
	else if (list2 ==  NULL)
		return list1;
	ListNode* pHead = NULL;
	if (list1->value < list2->value)
	{
		pHead = list1;
		pHead->pNext = mergeList(list1->pNext, list2);
	}
	else
	{
		pHead = list2;
		pHead->pNext = mergeList(list1, list2->pNext);
	}
	return pHead;
}

//a、b两个有序数组，a足够大，将b合并到a中。思想，从后端开始合并放入a的后端
void mergeTwoArray(int a[], int b[], int n, int m)
{
	int k = n + m - 1; //a全序索引
	int i = n - 1; //原来a中元素的索引
	int j = m - 1; //b中元素的索引
	while (i >= 0 && j >= 0)
	{
		if (a[i] > b[j])
		{
			a[k--] = a[i--];
		}
		else
		{
			a[k--] = b[j--];
		}
	}
	while (j >= 0)
	{
		a[k--] = b[j--];
	}
}

//原地归并相关函数
//将长度为n的数组逆序
void reverse(int *arr, int n)
{
	int i = 0, j = n - 1;
	while (i < j)
	{
		swap(arr, i, j);
		i ++; 
		j --;
	}
}
//将含有n个元素的数组向左循环移动i个位置
//相当于把arr指向区域的前i个元素和后n-i个元素整体位置交换
// |  i   |      n-i     |
// |      n-i     |  i   |
void exchange(int *arr, int n, int i)
{
	reverse(arr, i);
	reverse(arr+i, n-i);
	reverse(arr, n);
}
// | <arr[j] , , , | >arr[j], , , , | <arr[i], , , | >arr[i], , , |
// | begin   , , , | i      , , , , | mid    , , , | j      , , , |
// |原左区中较小的 | 原左区中较大的 |原右区中较小的|原右区中较大的|
// | 位置保持      | 和右区较小交换 |和左区较大交换| 位置暂时保持 |
void inSituMerge(int *arr, int begin, int mid, int end)
{
	int i = begin, j = mid, k = end;
	//循环条件是半区指针不越界
	while (i < j && j <= k)
	{
		int step = 0;
		//在左区寻找arr[i] > arr[j]的一个元素
		while (i < j && arr[i] <= arr[j])
			++i;
		//在右区寻找arr[j] > arr[i]的一个元素
		while (j <= k && arr[j] <= arr[i])
		{
			++j;
			++step;
		}
		//把这个区域中的元素做exchange，原地merge的核心
		exchange(arr+i, j-i, j-i-step);
		//再把后面没合并好的继续这个操作
		i = i + step;
	}
}
void InSituMergeSort(int *arr, int low, int high)
{
	if (low < high)
	{
		//n=11, 0~10, mid=5, |0, 1, 2, 3, 4, 5,| 6, 7, 8, 9, 10|
		int mid = (low + high) / 2;
		InSituMergeSort(arr, low, mid);
		InSituMergeSort(arr, mid+1, high);
		inSituMerge(arr, low, mid+1, high);
	}
}
/*
int main(int argc, char const *argv[])
{
	int A[] = {1, 4, 6, 2, 6, 7, 2, 3, 9, 1, 10};
	//这里还是可以求数组大小的
	std::cout << sizeof(A)/sizeof(int) << std::endl;
	int n = sizeof(A)/sizeof(int);
	//InsertSort(A, n);
	//ShellSort(A, n);
	//BubbleSort(A, n);
	//QuickSort(A, 0, n-1);
	//SelectionSort(A, n);
	//HeapSort(A, n);
	//MergeSort(A, 0, n-1);
	InSituMergeSort(A, 0, n-1);
	PrintArray(A, n);
	char a[7] = {'a', 'A', 'Z', 'd', 'B', 's', 'b'};
	CharPartition(a, 0, 6);
	int three[] = {0, 1, 2, 1, 1, 2, 0, 2, 1, 0};
	ThreePartition(three, 0, 9);
	PrintArray(three, 10);

	return 0;
}*/