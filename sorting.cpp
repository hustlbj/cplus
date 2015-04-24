#include <iostream>

typedef int ElemType;

void swap(ElemType A[], int i, int j)
{
	ElemType temp = A[i];
	A[i] = A[j];
	A[j] = temp;
}

//传递数组给函数时，实际是传递了一个指针，函数里的sizeof只能求出指针的大小，不能求数组的大小
void PrintArray(ElemType A[], int n)
{
	std::cout << sizeof(A) << std::endl;
	for (int i = 0; i < n; ++i)
	{
		std::cout << A[i] << ", ";
	}
	std::cout << std::endl;

}

//直接插入排序，稳定，最坏时间O(n^2)，辅助空间O(1)
void InsertSort(ElemType A[], int n)
{
	int i, j;
	ElemType temp;
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
void ShellSort(ElemType A[], int n)
{
	int dk, i, j;
	ElemType temp;
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
void BubbleSort(ElemType A[], int n)
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

int LHPartition(ElemType A[], int low, int high)
{
	ElemType pivot = A[low];
	while(low < high)
	{
		while(low < high && A[high] >= pivot) --high;
		A[low] = A[high];
		while(low < high && A[low] <= pivot) ++low;
		A[high] = A[low];
	}
	A[low] = pivot;
	return low;
}
//半区保序的Partition，指针从哪边开始，哪个半区就是保序的
int LLPartition(ElemType A[], int low, int high)
{
	//选择基准元，以最右边一个为基准
	ElemType pivot = A[high];
	ElemType temp;
	//i指针为左区指针，依次存放不大于temp的元素
	int i = low - 1;
	//j指针从左向右依次扫描，发现不大于temp的元素
	for (int j = low; j < high; j ++)
	{
		if (A[j] <= pivot)
		{
			++ i;
			temp = A[i];
			//把满足条件的j放到左区i位置
			A[i] = A[j];
			A[j] = temp;
		}
	}
	//最后把枢纽元交换到中间
	temp = A[i+1];
	A[i+1] = A[high];
	A[high] = A[i+1];
	//返回枢纽元位置
	return i+1;
}
void QuickSort(ElemType A[], int low, int high)
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
int main(int argc, char const *argv[])
{
	ElemType A[] = {1, 4, 6, 2, 6, 7, 2, 3, 9, 1, 10};
	//这里还是可以求数组大小的
	std::cout << sizeof(A)/sizeof(ElemType) << std::endl;
	int n = sizeof(A)/sizeof(ElemType);
	//InsertSort(A, n);
	//ShellSort(A, n);
	//BubbleSort(A, n);
	QuickSort(A, 0, n-1);
	PrintArray(A, n);
	char a[7] = {'a', 'A', 'Z', 'd', 'B', 's', 'b'};
	CharPartition(a, 0, 6);
	int three[] = {0, 1, 2, 1, 1, 2, 0, 2, 1, 0};
	ThreePartition(three, 0, 9);
	PrintArray(three, 10);

	return 0;
}