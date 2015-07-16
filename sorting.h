//:sorting.h
#ifndef MY_SORT_H
#define MY_SORT_H

#define N 1024
//char short int long

void Swap(int& a, int&b);
void PrintArray(int A[], int n);
//直接插入排序，稳定，最坏时间O(n^2)，辅助空间O(1)
void InsertSort(int A[], int n);
//希尔插入排序，不稳定，时间复杂度依赖于增量序列涉及数学难题约为O(n^1.3)最坏也是O(n^2)，辅助空间O(1)
void ShellSort(int A[], int n);
//交换，冒泡排序，最坏情况和平均时间复杂度为O(n^2)，空间复杂度O(1)，稳定
void BubbleSort(int A[], int n);
//快速排序易于理解的Partition函数，前后两个指针向中间扫描，不稳定
int LHPartition(int A[], int low, int high);
//半区保序的Partition，向一个方向扫描全部，指针从哪边开始，哪个半区就是保序的
int LLPartition(int A[], int low, int high);
//快速排序，不稳定，平均时间复杂度O(n*logn)
void QuickSort(int A[], int low, int high);
//利用快速排序的一趟，将小写字母放在左边，大写字母放在右边
void CharPartition(char A[], int low, int high);
//一个集合中有三种元素，按元素聚集排序，假设为一个数组中有三种数字0、1、2，将0排在左区，1排在中区，2排在右区，需要用到2个索引指针和1个扫描指针
void ThreePartition(int A[], int low, int high);
//利用快速排序Partition函数找出数组中的topK，但不能保证topK是有序的，topK有序的话用最大堆
void getTopK(int input[], int n, int output[], int k);
//选择，简单选择排序，时间复杂度始终是O(n^2)，空间复杂度O(1)，不稳定（交换时被前面换到后面）
void SelectionSort(int A[], int n);
//选择，堆排序，最好最坏平均情况下时间复杂度为O(nlogn)，空间复杂度为O(1)，建堆的时间复杂度为O(n)
void HeapSort(int A[], int n);
//归并排序，每一趟归并的时间复杂度为O(n)，共需进行log n趟归并，所以算法的时间复杂度为O(n log n)，空间复杂度为O(n)，稳定
void MergeSort(int A[], int low, int high);
//原地归并排序，不需要O(n)的辅助空间
void InSituMergeSort(int *arr, int low, int high);

#endif