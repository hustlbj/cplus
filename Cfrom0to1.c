/*
	C++入门练习过程中，相同小程序的C代码实现
*/
#include <stdio.h>
#include <limits.h>

void sumFromInput()
{
	int sum = 0;
	int temp = 0;
	int ret = 0;
	char c;
	printf("enter some integers: ");
	//从一行输入中，识别出数字，并求和，回车结束，其他字符不做处理
	while (1)
	{
		//scanf可以忽略前面的空格，当按照格式正确读入一个值时返回1
		ret = scanf("%d", &temp);
		if (ret == 1)
			sum += temp;
		//格式不正确时返回0
		else
			printf("|0");
		//读入一个格式串，其后面的空格、字符不会被忽略，可以通过getchar获取后面的字符
		c = getchar();
		printf("|%d", c);
		if (c == '\n')
			break;
	}
	printf("\nsum is %d\n", sum);
}

//文件I/O函数
// a.exe from_file to_file
int copyFile(int argc, char* argv[])
{
	FILE *in, *out;
	int ch;
	if (argc != 3)
	{
		fprintf(stderr, "输入格式：a.exe from to\n");
		return -1;
	}
	if ((in = fopen(argv[1], "rb")) == NULL)
	{
		fprintf(stderr, "打不开文件：%s\n", argv[1]);
		return -1;
	}
	if ((out = fopen(argv[2], "wb")) == NULL)
	{
		fprintf(stderr, "打不开文件：%s\n", argv[2]);
		fclose(in);
		return -1;
	}
	//EOF在stdio.h中，宏定义为-1
	//getc和putc在文件结束或遇到错误时都返回EOF
	while ((ch = getc(in)) != EOF)
	{
		if (putc(ch, out) == EOF)
			break;
	}
	//检查是否因为遇到错误返回EOF而终止
	if (ferror(in))
		printf("读取文件%s遇到错误！\n", argv[1]);
	if (ferror(out))
		printf("读取文件%s遇到错误！\n", argv[2]);
	fclose(in);
	fclose(out);
	printf("成功赋值一个文件！\n");
}

//将一个输入的字符串转换成整数
/*
  对于整数类型，在使用2的补码运算的机器(你将使用的机器几乎都属此类)上，
  一个有符号类型可以容纳的数字范围为[- 2^(位数-1) ]到[+ 2^(位数 -1)-1]，
  一个无符号类型可以容纳的数字范围为0到(+ 2^位数 )。
  例如，一个16位有符号整数可以容纳的数字范围为-2^15(即-32768)到(+2^15-1)(即+32767)。
  而16为无符号整数可容纳的最大值为(2^位数-1)或表示为汇编形式0xffff。
  INT_MAX+1溢出之后就变成INT_MIN了，INT_MIN+1溢出之后就变成INT_MAX了。
*/
/*
  范围：带符号整型，可返回正数和负数
  错误输入：返回0
*/
int strToInt(char* string)
{
	int sign = 1;
	int number = 0, temp = 0;

	//下面的max和min是为了测试int型最大和最小数，我们可以直接使用limits.h中的宏
	int len = sizeof(int); //通常是2个字节或4字节
	int max, min;
	if (len*8 == 32)
	{
		max = 0x7fffffff; // INT_MAX in limits.h
		min = -max - 1;  //INT_MIN (-INT_MAX -1) in limits.h
	}
	else if (len*8 == 16)
	{
		max = 0x7fff; 
		min = -max - 1;
	}
	else
	{
		max = 0;
		min = 0;
	}
	//INT_MAX+1溢出之后就变成INT_MIN了，INT_MIN+1溢出之后就变成INT_MAX了
	printf("sizeof(int) = %d, max = %d, min = %d\n, max+1 = %d, max+10 = %d, min-1 = %d, min-10 = %d\n", 
		len, max, min, max + 1, max + 10, min - 1, min - 10);
	//测试max和min完毕

	//进行字符串转换整型，暂未处理溢出情况。。
	if (string == NULL)
		return number;
	if (*string == '-')
	{
		sign =  -1;
		++string;
	}
	else if (*string == '+')
	{
		sign = 1;
		++string;
	}
	while (*string != '\0' && *string >= '0' && *string <= '9')
	{
		temp = number;
		number = number * 10 + (*string - '0');
		// 加上下一位后溢出，实际上不必判断temp的值，只需要检查变号即可。。这里为了表示清楚溢出的意思
		//      本来是正数，加上一位后溢出变成负数了               本来是负数，加上一位后溢出变成正数了
		if ((sign == 1 && temp <= INT_MAX && number < 0) || (sign == -1 && temp >= INT_MIN && number > 0))
		{
			printf("Bigger than INT_MAX, overflow!\n");
			return 0;
		}
		++string;
	}
	printf("strToInt: %d\n", sign * number);
	return sign * number;
}

typedef struct Node {
	int element;
	struct Node* next;
} ListNode;
//返回链表中的倒数第k个节点，距离最后一个节点k-1步，所以用2个指针构造一个k-1步的差值即可
/*
p1先走k-1，然后再走x，再走k-1步正好走到尾部
当p1在k-1时，p2在0处开始走，也是走(k-1) + x步，正好到达倒数第k个节点
p1	1 	2 	k-1     -   x   -  	k  --  3 -- n-1
0 	1 	2 	3   	5 	6 	7 	8 	9 	10 	11 
p2  -- 3 -- |       -   x   -   |
 
 异常返回为NULL
*/
ListNode* FindKthToTail(ListNode* pListHead, unsigned int k)
{
	//保证链表不为空，并且倒数数字大于0
	if (pListHead == NULL || k < 1)
		return NULL;
	ListNode* pAhead = pListHead;
	ListNode* pBehind = pListHead;
	unsigned int i = 0;
	// 0，1，……，k-2，移动k-1步
	for ( ; i < k-1; i ++)
	{
		// 在k-1步以前已经到最后一个节点，说明链表本身不够k个66666
		if (pAhead->next == NULL)
			return NULL;
		pAhead = pAhead->next;
	}
	//让pAhead走到最后一个节点
	while (pAhead->next != NULL)
	{
		pAhead = pAhead->next;
		pBehind = pBehind->next;
	}
	return pBehind;
}
void main(int argc, char* argv[])
{
	//sumFromInput();
	//copyFile(argc, argv);
	strToInt("-123aaa");
}