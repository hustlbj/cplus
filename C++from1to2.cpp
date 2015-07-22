//:C++from1to2.cpp
#include <iostream>
#include <string.h>
#include <stdio.h>
#include "C++from1to2.h"
#include "list.h"
/*
 T11. 求数值的整数次方
 输入：数值是double型有符号，指数是有符号int型
 注意：0值，指数为负时的处理
 方案：除了异常输入外，不论指数是正还是负，都先计算正指数次方，为负的话就再求一次倒数
 优化：降2次递归的方式，减少乘法次数
*/
bool g_InvalidInput = false;
double Power(double base, int exponent)
{
	if (equal(base, 0.0))
	{
		if (exponent <= 0)
		{
			g_InvalidInput = true;
			return 0.0;
		}
		else
		{
			return 1.0;
		}
	}
	//先把指数转换成绝对值 >=0 来计算
	unsigned int absExponent = (exponent >= 0 ? (unsigned int )(exponent) : (unsigned int )(-exponent) );
	std::cout << "absExponent: " << absExponent << std::endl;
	double result = PowerWithUnsignedExponent(base, absExponent);
	//如果原指数是小于0的，则还需要求倒数
	if (exponent < 0)
		result = 1.0 / result;
	return result;
}
bool equal(double num1, double num2)
{
	if ((num1 - num2 < 0.0000001) && (num1 - num2 > -0.0000001))
		return true;
	return false;
}
double PowerWithUnsignedExponent(double base, unsigned int exponent)
{
	if (exponent == 0)
		return 1;
	// 正常情况下，递归执行降级到exponent=1就停止递归了，然后向上返回结果
	if (exponent == 1)
		return base;
	//拆分：11 5 2 1 
	//求解过程：base*base -> base^2 * base^2 + 1 -> base^5 * base^5 + 1
	double result = PowerWithUnsignedExponent(base, exponent >> 1);
	result *= result;
	if (exponent & 0x01 == 1)
		result *= base;
	return result;
}


/*
 T12. 打印1到最大的n位数
 输入：位数n如3，则打印出1,2,3....999
 方法：没有限制n，则考虑大数问题，用字符串解决大数问题，数字为n位时只需要n+1长的字符串即可
 需要在“字符串表达的数字上模拟加法”并把“字符串表达的数字打印出来”。
*/
// 注意字符串中高位是数字中的低位，所以做加法时从字符串的高位开始判断
bool Increment(char* number)
{
	bool isOverflow = false;
	// 进位标志
	int nTakeOver = 0;
	int nLength = strlen(number);
	for (int i = nLength - 1; i >= 0; --i)
	{
		// 每一位的运算都要加上进位标志
		int nSum = number[i] - '0' + nTakeOver;
		// 字符串最高位也就是数字中的最低位，让它开始做加法
		if (i == nLength - 1)
			nSum += 1;
		// 需要进位时
		if (nSum >= 10)
		{
			// 字符串最低位也就是数字中的最高位，发生溢出
			if(i == 0)
			{
				isOverflow = true;
			}
			else
			{
				nSum -= 10;
				nTakeOver = 1;
				number[i] = '0' + nSum;
			}
		}
		//不需要进位时比较简单
		else
		{
			number[i] = '0' + nSum;
			//自增运算，每次只执行一次
			break;
		}
	}
	return isOverflow;
}
//返回存放结果的指针，注意用完后用delete释放内存
char* AddTowBigDigits(char* number1, char* number2)
{
	if (number1 == NULL || number2 == NULL)
		return NULL;
	int length1 = strlen(number1);
	int length2 = strlen(number2);
	//防止溢出，多1位
	int length = (length1 >= length2 ? length1 : length2) + 1;
	//还得多一位'\0'
	char* result = new char[length + 1];
	memset(result, '0', length);
	result[length] = '\0';
	//进位标志
	int nTakeOver = 0;
	for (--length1, --length2, --length; length1 >= 0 && length2 >= 0;  )
	{	
		std::cout << "length1: " << length1 << std::endl;
		int bitSum = number1[length1--] - '0' + number2[length2--] - '0' + nTakeOver;
		std::cout << "bit:" << bitSum << " ";
		if (bitSum >= 10)
		{
			nTakeOver = 1;
			bitSum = bitSum - 10;
		}
		result[length--] = '0' + bitSum;
	}
	int remainIndex = (length1 < 0 ? length2 : length1);
	char* remainNumber = (length1 < 0 ? number2 : number1);
	while(remainIndex >= 0)
	{
		std::cout << "remainIndex: " << remainIndex << " ";
		int bitSum = remainNumber[remainIndex--] - '0' + nTakeOver;
		std::cout << "bit:" << bitSum << " " << std::endl;
		if (bitSum >= 10)
		{
			nTakeOver = 1;
			bitSum = bitSum - 10;
		}
		result[length--] = '0' + bitSum;
	}
	if (nTakeOver)
		result[0] = '1';
	else
	{
		char* new_result = new char[strlen(result) - 1];
		strcpy(new_result, result + 1);
		delete[] result;
		result = new_result;
		new_result = NULL;
	}
	return result;
}
void PrintNumber(char* number)
{
	bool isBeginning0 = true;
	int nLength = strlen(number);
	for (int i = 0; i < nLength; ++i)
	{
		if(number[i] != '0' && isBeginning0)
			isBeginning0 = false;
		if(!isBeginning0)
			printf("%c", number[i]);
	}
}
void Print1ToMaxOfNDigits(int n)
{
	if (n <= 0)
	{
		return;
	}
	char* number = new char[n + 1];
	memset(number, '0', n);
	number[n] = '\0';
	//自增没有溢出，就一直打印
	while(!Increment(number))
	{
		PrintNumber(number);
		printf("\t");
	}
	delete[] number;
}

/*
 T14. 调整数组顺序使奇数位于偶数前面
 用到了类似快速排序的Partition
*/
 void ReprderOddEven(int* pData, unsigned int length)
 {
 	if (pData == NULL || length == 0)
 		return;
 	//头指针
 	int* pBegin = pData;
 	//尾指针
 	int* pEnd = pData + length - 1;

 	while (pBegin < pEnd)
 	{
 		//寻找偶数
 		while (pBegin < pEnd && (*pBegin & 0x1) != 0)
 			pBegin ++;
 		while (pBegin < pEnd && (*pEnd & 0x1) == 0)
 			pEnd --;
 		if (pBegin < pEnd)
 		{
 			int temp = *pBegin;
 			*pBegin = *pEnd;
 			*pEnd = temp;
 		}
 	}
 }

 /*
 T15. 链表中的倒数第k个节点
 思路：单向从头到尾遍历的链表，假设有n个节点，倒数第k个节点就是从头开始的第n-k+1也就是第n-(k-1)个节点
 大概的图形如下：翔知道前面的n-(k-1)，需要知道n和(k-1)，具体+1还是-1可举例论证。
 |---n-(k-1)---|------(k-1)------|
 |----------------n--------------|
 所以，用两个指针，第一个先向前走k-1，然后从第k步开始，第二个指针也开始从链表头部向前走，两指针的距离保持在k-1。
 相关题目：求链表的中间节点，用两个指针从头开始，一个指针每次走两步，一个指针每次走一步，走的快的到达末尾时，走的慢的正好在链表中间。
 判断一个单向链表是否形成了环形结构，也是两个指针一个走两步一个走一步，如果走得快的追上了走的慢的指针，那么就是环形链表。
 */
// 注意输入：NULL，k=0，链表总长度不够k个这些边界和异常
ListNode* FindKthToTail(ListNode* pHead, unsigned int k)
{
	if (pHead == NULL || k == 0)
	{
		return NULL;
	}
	ListNode* pA = pHead;
	ListNode* pB = NULL;
	for (unsigned int i = 0; i < k - 1; ++i)
	{
		if (pA->m_pNext != NULL)
		{
			pA = pA->m_pNext;
		}
		//不够k个，返回NULL
		else
		{
			return NULL;
		}
	}
	pB = pHead;
	while (pA ->m_pNext != NULL)
	{
		pA = pA->m_pNext;
		pB = pB->m_pNext;
	}
	return pB;
}

/*
 T16. 反转链表
 输入：链表的头节点
 输出：反转后链表的头节点
 用到3个指针，当调整节点i的m_pNext指向前一个节点h时，还需要保存i的后一个节点j
 最后的m_pNext==NULL的节点就是反转后的头节点
*/
ListNode* ReverseList(ListNode* pHead)
{
	//pNode是当前调整的节点
	ListNode* pNode = pHead;
	ListNode* pPrev = NULL;
	ListNode* pNext = NULL;
	//已经排除了链表为空的情况
	while (pNode != NULL)
	{
		//先保存next节点，再修改当前节点
		pNext = pNode->m_pNext; 
		pNode->m_pNext = pPrev; 
		//下一轮
		pPrev = pNode;
		pNode = pNext;
	}
	//链表不为空的时候，pNode最终会走到NULL，所以返回pPrev
	if (pNode == NULL && pHead != NULL)
		return pPrev;
	else
		return NULL;
}
