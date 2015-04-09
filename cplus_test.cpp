#include <iostream>
#include <cstring>
#include <malloc.h>

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

	//C风格字符串
	char ca1[] = {'C', '+', '+', '+', '\0'}; //末尾添加了'\0'的字符数组
	char ca2[] = "C++++"; //字符数组存储的字符串常量，编译器自动在末尾添加null
	const char* ca3 = "C+++++"; //指针指向字符串常量
	//sizeof可以求数组长度，sizeof(指针)则是指针所占的大小，一般是4字节
	std::cout << sizeof(ca1) << sizeof(ca2) << sizeof(ca3) << std::endl; //5,6,4
	//strlen是C风格字符串标准库中的求字符串长度的函数，必须以null结束字符串
	std::cout << strlen(ca1) << strlen(ca2) << strlen(ca3) << std::endl; //4,5,6

	return 0;
}