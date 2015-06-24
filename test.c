/*
	C++入门练习过程中，相同小程序的C代码实现
*/
#include <stdio.h>

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
void main(int argc, char* argv[])
{
	//sumFromInput();
	copyFile(argc, argv);
}