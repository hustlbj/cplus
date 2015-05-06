#include <stdio.h>

void addFromInput()
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

void main()
{
	addFromInput();
}