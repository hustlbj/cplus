#include <iostream>

typedef int ElemType;


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
int main(int argc, char const *argv[])
{
	ElemType A[] = {1, 4, 6, 2, 6, 7, 2, 3, 9, 1, 10};
	//这里还是可以求数组大小的
	std::cout << sizeof(A)/sizeof(ElemType) << std::endl;
	int n = sizeof(A)/sizeof(ElemType);
	//InsertSort(A, n);
	ShellSort(A, n);
	PrintArray(A, n);
	return 0;
}