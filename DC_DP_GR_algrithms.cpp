#include <assert.h>
#include <time.h>
#include <iostream>
#include <cstring> //兼容的C风格头文件
//分治法：分解，解决，合并。快速排序、归并排序都采用了分治法
/* 分治法所能解决的问题一般具有以下几个特征：
1、 该问题的规模缩小到一定的成都就可以容易地解决
2、 该问题可以分解为若干规模较小的相同问题，即该问题具有最优子结构性质
3、 利用该问题分解出的子问题的解可以合并为该问题的解
4、 该问题所分解出的各个子问题是互相独立的，即子问题之间不包含公共的子问题
如果具备了第一条和第二条特征，而不具备第三条特征，则可以考虑用贪心算法或者动态规划法
*/

//动态规划
/* 问题1：
求用1*2的瓷砖覆盖2*M的地板有几种方式，即求F(M)=？
该类问题一般先图解+数学推导，找出不重叠子问题和递推公式
|*|                   M-1                     |
|*|                   M-1                     |

|*|*|                 M-2                     |
| | |                 M-2                     |
2个子问题，先竖着放一块，则剩下问题F(M-1)，先横着放一块则必然还需在下面横着放一块，则剩下问题F(M-2)
所以F(M) = F(M-1) + F(M-2)， 也就是斐波拉契数列
*/
int Fib(int M)
{
	if (M == 1)
		return 1;
	else if (M == 2)
		return 2;
	else
		return Fib(M-1) + Fib(M - 2);
}
//显然，上述过程存在大量的重复计算，可以用一个数组保存所有已计算过的项，以空间换取时间，时间复杂度为O(N)，而空间复杂度也为O(N)
//这种将先前子问题的解存起来，供后续求解问题而使用，用到了动态规划的思想，备忘录法
//事实上是动态规划的变型，通常动态规划是自底向上的求解问题的
int a[1000] = {0};
int MEM_Fib(int m)
{
	assert(m > 0);
	if (a[m] != 0) //说明先前已经缓存了结果
		return a[m];
	else
	{
		if (m == 1)
			a[1] = 1;
		else if (m == 2)
			a[2] = 2;
		else
		{
			a[m] = MEM_Fib(m-1) + MEM_Fib(m-2);
		}
		return a[m];
	}
}
int DP_Fib(int m)
{
	if (m == 1)
		return 1;
	else if (m == 2)
		return 2;
	else
	{
		a[1] = 1;
		a[2] = 2;
		for (int i = 3; i <= m; i ++)
			a[i] = a[i - 1] + a[i - 2];
		return a[m];
	}

}
//动态规划法常用于最优化问题，找到一个最优解而不是确定的最优解
//用一个表来记录所有已解的子问题的答案，是动态规划法的基本思路
/* DP算法设计步骤：
1、 描述最优解的结构
2、 递归定义最优解的值
3、 按自底向上的方式计算最优解的值
4、 由计算出的结果构造一个最优解
最优子结构：如果问题的最优解所包含的子问题的解也是最优的，则该问题具有最优子结构
*/
//动态规划解决最长公共子序列问题LCS
/* 
序列X=<X0,X1,X2,...,Xm>和序列Y=<Y1,Y2,..Yn>的一个最长公共子序列为Z=<Z0,Z1,Z2,...,Zk>
1）若Xm=Yn，则必然有Zk=Xm=Yn，且Zk-1是Xm-1和Yn-1的最长公共子序列
2）若两个序列的末尾不想等Xm!=Yn且Zk!=Xm，公共子序列的末尾不是X的末尾，则Z是Xm-1和Y的最长公共子序列
3）同理，若Xm!=Yn且Zk!=Yn，则Z是X和Yn-1的最长公共子序列
递归定义最优解的值：
当Xm=Yn时，则LCS(Xm,Yn)=LCS(Xm-1,Yn-1)+1;
当Xm!=Yn时，则LCS(Xm,Yn)=max{LCS(Xm-1,Yn), LCS(Xm,Yn-1)}
画出表格记录自底向上的值，若用C[i,j]表示m行n列表格中的元素，则
C[i,j] = 0							if i = 0 or j = 0
		 C[i-1,j-1]+1   			if i,j>0 and Xi==Yj
		 max(C[i,j-1], C[i-1,j])	if i,j>0 and Xi!=Yj
*/
int C[100][100];
int max(int a, int b)
{
	return a >= b ? a : b;
}
//自底向上求解，另外还有递归的自顶向下
int LCS_LENGTH(const char* X, const char* Y)
{
	if (X == NULL || Y == NULL)
	{
		return 0;
	}
	int m = strlen(X);
	int n = strlen(Y);
	C[0][0] = 0;
	for (int i = 1; i < m; i ++)
		C[i][0] = 0;
	for (int i = 1; i < n; i ++)
		C[0][i] = 0;
	for (int i = 1; i <= m; i ++)
		for (int j = 1; j <= n; j ++)
		{
			if (X[i] == Y[j])
				C[i][j] = C[i-1][j-1] + 1;
			else
				C[i][j] = max(C[i][j-1], C[i-1][j]);
		}
	return C[m][n];
}	

int main()
{
	int fib = 0;
	clock_t start, end;
	start = clock();
	fib = Fib(40);
	end = clock();
	std::cout << fib << ": " << end-start << std::endl;

	start = clock();
	fib = MEM_Fib(40);
	end = clock();
	std::cout << fib << ": " << end-start << std::endl;

	start = clock();
	fib = DP_Fib(40);
	end = clock();
	std::cout << fib << ": " << end-start << std::endl;

	char* X = "abcdabcdabcd";
	char* Y = "aaadbcdbcada";
	std::cout << "LCS: " << LCS_LENGTH(X, Y) << std::endl;

	return 0;
}