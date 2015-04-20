#include <iostream>
#include <cstring>
#include <malloc.h>
#include <assert.h>

int main(int argc, char const *argv[])
{
	//数组初始化
	int x[4] = {0}; //{0, 0, 0, 0}
	int y[4] = {1}; //{1, 0, 0, 0}
	std::cout << x[0] << ", " << x[1] << ", " << x[2] << ", " << x[3] << std::endl;
	std::cout << y[0] << ", " << y[1] << ", " << y[2] << ", " << y[3] << std::endl;
	int* a = new int[4]; //new从堆中申请空间，{0, 0, 0, 0}
	std::cout << a[0] << ", " << a[1] << ", " << a[2] << ", " << a[3] << std::endl;
	delete []a; //释放数组空间，delete a只释放a指向的一个空间
	//二维数组
	//按每一行初始化，顺序初始化，只初始化每一行开始的元素其余为0，顺序初始化开始的一些元素其余为0
	//二维数组的第二维长度不能省略，第一维在所有元素都赋值时可以省略
	int array[][3] = {1, 2, 3, 4, 5, 6};
	std::cout << array[0][4] << std::endl; //顺序存储的思路
	//逗号分隔的表达式的值，等于最后一个表达式的值
	int a32[3][2] = {(0, 1), (2, 3), (4, 5)}; //等价于a[3][2] = {1, 3, 5}其余为0
	//二维数组指针顺序访问：int * p = &a[0][0]; *(p+i*N+j)

	//二维数组动态声明
	int** b = new int* [3];
	for (int i = 0; i < 3; i ++)
		b[i] = new int [2]; //a[3][2]
	//动态声明的二维数组释放内存
	for (int i = 0; i < 3; i ++)
		//释放里面的一维
		delete [] b[i];
	//释放外面的一维
	delete []b;

	//指针数组和数组指针
	int *pointArray[10]; //指针数组，10个元素都是int指针
	int ap1[4][10]; //二维数组的数组名ap1就是一个数组指针，类型是int (* )[10]
	int (*arrayPoint)[10];
	arrayPoint = ap1; //所以直接赋值给一个同类型数组指针
	//对于一维数组，应用数组指针
	int ap2[10];
	int (*arrayPoint1)[10] = &ap2; //一维数组的数组名是int指针即int *，所以再次取址得到数组指针&a的类型是int (* )[10]
	int *point1 = ap2;  // 直接将一维数组的数组名int *类型赋值给int *指针


	//C风格字符串
	char ca1[] = {'C', '+', '+', '+', '\0'}; //末尾添加了'\0'的字符数组
	char ca2[] = "C++++"; //字符数组存储的字符串常量，直接保存在栈中，可以修改元素，编译器自动在末尾添加null
	const char* ca3 = "C+++++"; //指针指向字符串常量，字符串保存在字符常量区，元素不能被修改，可以通过数组下标访问元素
	//sizeof可以求数组长度（数组的总字节数），sizeof(指针)则是指针所占的大小，一般是4字节
	std::cout << sizeof(ca1) << sizeof(ca2) << sizeof(ca3) << std::endl; //5,6,4
	//strlen是C风格字符串标准库中的求字符串长度的函数，必须以null结束字符串
	std::cout << strlen(ca1) << strlen(ca2) << strlen(ca3) << std::endl; //4,5,6
	//遍历C风格字符串
	const char* cp = "some value";
	while (*cp) {
		std::cout << *cp << std::endl;
		++cp;
	}

	return 0;
}

//内存拷贝，两个区域有重叠区时
void* memmove(void* str1, const void* str2, size_t n)
{
	char* pStr1 = (char*) str1;
	const char* pStr2 = (const char*) str2;
	//二者无交叉区域的话，可以随意复制
	// #########***%%%%%，*表示有交叉区域，#表示目标区域，则从低开始复制
	if (pStr1 < pStr2) {
		for (size_t i = 0; i != n; ++i)
		{
			*(pStr1++) = *(pStr2++);
		}
	}
	// %%%%%%%%***#######，目标区域在后，则从高到低复制
	else
	{
		pStr1 += n-1;
		pStr2 += n-1;
		for (size_t i = 0; i != n; ++i)
		{
			*(pStr1--) = *(pStr2--);
		}
	}
}
//数组和指针，多维数组，数组指针

//模板类的几个说法

//32位机器上gcc编译器，各种数据类型的长度，通常int为一个字长，short为半个字长，long为一个或两个字长（32位机器中为一个字长）
//float为一个字长，double为两个字长，long double为三个或四个
//空类默认会占一个字节长度，类中有虚函数时会有一个指向虚函数的指针vptr，子类的大小=父类大小+子类自身的成员大小
//还要考虑内存对齐
class A //考虑内存对齐的话是12
{
	int a; //4
	short b; // 2 
	int c; //4
	char d; //1
};
class B //考虑内存对齐的话是16
{
	double a; //8
	short b; //2
	int c; //4
	char d; //1
};

// Debug版本中有ASSERT断言保护，在Release中就会删掉ASSERT断言
//strlen求C风格字符串的长度
int cstr_strlen1(const char* str)
{
	//判断指针是否为NULL
	assert(str != NULL);
	int len = 0;
	while ((*str++) != '\0')
		len++;	
	return len;
}
//不用变量 用递归方式实现strlen
int cstr_strlen2(const char* str)
{
	assert(str != NULL);
	return *str == '\0' ? 0 : (1+strlen(++str));
}
//另一种求C风格字符串的长度
int cstr_strlen3(const char* x) 
{
	const char* y = x;
	while (*y++)
		;
	return (y-x-1);
}
//实现strcmp
int cstr_strcmp(const char* str1, const char* str2)
{
	//要求两个字符串均不为空
	assert(str1 != NULL && str2 != NULL);
	int ret = 0;
	//最开始已经判断了不为空，&& str1放在后面判断即可
	while (!(ret = *(unsigned char* )str1 - *(unsigned char * )str2) && str1)
	{
		str1 ++;
		str2 ++;
	}
	if (ret < 0) ret = -1;
	else if (ret > 0) ret = 1;
	return ret;
}
//两个C风格字符串的拼接
char* cstr_strcat(char* strDest, const char* strSrc)
{
	char* address = strDest;
	assert(strDest != NULL && strSrc != NULL);
	//是不是先用strlen判断一下目标地址的大小是否够cat
	while (*strDest ++)
		;
	while (*strDest++ = *strSrc ++)
		;
	return address;
}
//C风格字符串的复制
char* cstr_strcpy(char* strDest, const char* strSrc)
{
	assert(strDest != NULL && strSrc != NULL);
	char* strD = strDest;
	while (*strDest++ = *strSrc ++)
		;
	return strD;
}

//从C风格字符串中去除某个字符
char* cstr_remove_ch(char* str, char ch)
{
	char* it1 = str;
	char* it2 = str;
	while (*it2 != '\0')
	{
		while (*it2 == ch)
		{
			++it2;
		}
		*it1++ = *it2++;
	}
	*it1 = '\0';
	return str;
}