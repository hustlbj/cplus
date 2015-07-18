/*
	C++ 入门练习，剑指offer例题
*/
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <cstring>
#include <stack>
#include <exception>
#include <stdexcept>

#include "list.h"
#include "tree.h"
#include "queue_2s.h"
#include "stack_2q.h"
#include "sorting.h"
#include "C++from1to2.h"
//#include <mutex>  c++11
using namespace std;

void sumFromInput()
{
	int sum = 0;
	int temp = 0;
	int ret = 0;
	char char_temp;
	string str_temp;
	//cin >> 是以空格做分割的
	//当用户键入“Enter”时，操作系统把键盘缓冲区的内容传输到cin的流内部缓冲区
	//用户不输入时，cin >> 阻塞blocking IO
	// >> 对所有内建的数据类型都进行了重载，所以可以从输入流对象提取出int float double等类型数据
	// cin >> xxx返回cin本身，如果遇到文件尾或非法值（错误类型）则返回false
	while (1)
	{
		//cin.peek()返回第一个char型的字符，只是观测，该字符并未从输入流中删除
		//cin.get()则返回第一个char型字符并从输入流中删除
		if (cin.peek() == -1 || cin.peek() == '\n')
			break;
		cout << "peek(): " << cin.peek() << ", ";

		/******111111111111111111111*********/
		//cin >> temp;
		//fail()判断cin>>temp是否失败，1为输入转换失败
		//cout << "fail(): " << cin.fail() << ", ";

		//读入一个连续字符串，空格结束，想读入一行用cin.getline()
		cin >> str_temp;
		stringstream ss(str_temp);
		//将读入的单词转化为数字，注意这里类似于cin直接读入数字，如果数字后面有字符依然可以转化部分数字
		ss >> temp; /***可以先判断ss是否全部是数字再转换***/
		cout << "ss: " << temp << endl;

		if (temp)
			sum += temp;
		temp = 0;

		/***********1111111111111111111111***********
		//成功读入一个整型数字
		if (cin.fail() != 1)
		{
			cout << "temp: " << temp << endl;
			sum += temp;
		}
		//输入类型不对则忽略
		else
		{
			//clear()更改cin的状态标识符，sync()清除缓冲区中的数据流
			cin.clear();
			//忽略换行之前的所有字符，清除当前行；cin.ignore(n)忽略n个字符
			//cin.ignore(1024, '\n');
			cin.ignore(1024, '\x20');
			//cin.get()可以直接读取一个字符，也可以指定(数组名，长度，结束符)来读取字符串
			//cin.getline(buf, n)读取一行
			//char_temp = cin.get();
			//cout << "get(): " << char_temp << endl;
		}*/
	}
	cout << sum << endl;
}
//文件I/O函数
// a.exe from_file to_file
int copyFile(int argc, char const *argv[])
{
	if (argc != 3)
	{
		cout << "Usage: ./a.exe from to" <<endl;
		return -1;
	}
	//无参构造，文件名参数构造，文件名+打开模式参数构造
	//常见的打开模式：ios::in打开一个可读取文件，ios::out打开一个可写入文件，ios::binary以二进制的形式打开
	//ios::app追加写，ios::trunk删除文件原来已存在的内容，ios::nocreate文件不存在的话open将无法进行，ios::noreplace
	//in out binary app trunk ...实际是枚举类型，分别赋值为某一位是1，比如in实际是0x01即二进制第一位是1，所以 | 可以并用多个打开模式
	ifstream in(argv[1], ios::in | ios::binary);
	ofstream out(argv[2], ios::out | ios::binary);
	//.seekg(ios::beg)使得文件指针指向文件头，ios::end则是文件尾
	if (in.bad())
		return -1;
	else
		//判断读取流是否到了文件末尾
		while (!in.eof())
		{
			char buf[256] = {0};
			in.read(buf, sizeof(char) * 256);
			if (out.bad())
			{
				return -1;
			}
			out.write(buf, sizeof(char) * 256);
		}
	in.close();
	out.close();
	return 0;
}

/*
 空类的sizeof是1，
 只有构造函数和析构函数的类的sizeof是1，
 类中的虚函数占一个指针大小的空间，类中只有一个虚函数的话整个类还是只占一个指针大小的空间，而不是+1
*/
class Blank //sizeof() = 4 or 8
{
	Blank() {}
	virtual ~Blank() {}
};

/*
 用另一个同类对象构造新对象，复制构造函数
*/
class A
{
private:
	int value;
public:
	A(int n) { std::cout << "exec A(int n)" << std::endl; value = n; }
	// A(A other)通过值传递传入other对象，会进行复制构造函数，又会进行复制，产生永无休止的递归调用。所以这儿编译会报错或者导致栈溢出。
	A(const A& other) { std::cout << "exec A(const A& other)" << std::endl; value = other.value; }

	void Print() { std::cout << value << std::endl; }
};

int GetSize(int data[])
{
	return sizeof(data);
}
void TestSizeof()
{
	//数组
	int data1[] = {1, 2, 3, 4, 5};
	int size1 = sizeof(data1);

	int *data2 = data1;
	int size2 = sizeof(data2);

	int size3 = GetSize(data1);

	std::cout << size1 << ", " << size2 << ", " << size3 << std::endl;
}

/*
 T1. 重载赋值运算符operator =
*/
class CMyString
{
public:
	CMyString(char* pData = NULL) { std::cout << "exec CMyString(char* pData)" << std::endl; m_pData = pData; }
	//关于delete：用new分配的单个对象用delete，用new[]分配的对象数组用delete[]保证调用每个对象析构函数；基本类型用delete和delete[]都行。
	~CMyString(void) { std::cout << "delete: " << std::endl; }
	CMyString& operator =(const CMyString& str);
	void Print() { std::cout << m_pData << std::endl; }
private:
	char* m_pData;
};
//传入参数设置为常量引用
CMyString& CMyString::operator =(const CMyString& str)
{
	std::cout << "exec operator = " << std::endl;
	//判断是不是同一个实例
	/*
	if (this == &str)
		return *this;
	//分配新内存之前先删除原来的
	delete[] m_pData;
	m_pData = NULL;
	m_pData = new char[strlen(str.m_pData) + 1];
	strcpy(m_pData, str.m_pData);
	*/
	if (this != &str)
	{
		//先创建一个临时变量
		CMyString strTemp(str.m_pData);
		char* pTemp = NULL;
		pTemp = strTemp.m_pData;
		//strTemp是临时变量，作用域结束后会自动调用析构函数把strTemp.m_pData所指向的内存释放掉
		strTemp.m_pData = m_pData;
		m_pData = pTemp;
		std::cout << "m_pData: " << m_pData << std::endl;
	}
	//返回值要设置为该类型的引用*(this)
	return *this;
}

/*
 C++中可以用struct和class来定义类型。如果没有表明成员函数或者成员变量的访问权限级别，
 在struct中默认的是public，在class中默认的是private。
 C#中struct定义的是值类型，值类型实例在栈上分配内存，class则是引用类型，引用类型的实例在堆上分配内存。
*/


/*
 T2. Singleton单例模式
  构造函数要私有，需要一个静态的实例，需要考虑多线程
*/
class Singleton1
{
private:
	Singleton1() {}
	//把复制构造函数和=操作符也设为私有，防止被复制
	Singleton1(const Singleton1&);
	Singleton1& operator =(const Singleton1&);
	//在类内不能对static成员初始化，在类定义外初始化
	//static std::recursive_mutex _lock;
	static Singleton1* _instance;
public:
	static Singleton1* Instance();
};
//new返回分配空间的首地址——指针
Singleton1* Singleton1::_instance = new Singleton1();
//多线程情况下需要加锁
Singleton1* Singleton1::Instance()
{
	if (_instance == NULL)
	{
		//std::lock_guard<std::recursive_mutex> locker(_lock);
		if (_instance == NULL)
		{
			std::cout << "Singleton1 new.." << std::endl;
			_instance = new Singleton1();
		}
	}
	return _instance;
}

/*
 T3. 二维数组中查找一个数字
 二维数组每行、梅列都递增排序，如
 1 	2 	8 	9
 2 	4 	9 	12
 4 	7 	10  13
 6 	8 	11 	15
*/
 bool Find(int* matrix, int rows, int columns, int number)
 {
 	bool found = false;
 	if (matrix != NULL && rows > 0 && columns > 0)
 	{
 		//从矩阵右上角开始
 		int row = 0;
 		int column = column - 1;
 		//列从右到左，行从上到下切除
 		while (row < rows && column >= 0)
 		{
 			std::cout << "check matrix[row*columns + column] " << matrix[row * columns + column] << std::endl;
 			if (matrix[row * columns + column] == number)
 			{
 				found = true;
 				break;
 			}
 			//当前未检查区域右上角数字大于目标值，则切除这一列
 			else if (matrix[row * columns + column] > number)
 			{
 				-- column;
 			}
 			//当前未检查区域右上角数字小于目标值，说明所在行都小于目标值，切除这一行
 			else
 			{
 				++ row;
 			}
 		}
 	}
 	return found;
 }

 /*
 T4. 将一个字符串中的空格替换成%20
 O(n)方法：假定存储原串的空间足够大，在原串基础上修改。先遍历一次字符串，遇到一个空格，新字符串的长度就需要额外+2，这样计算出新串的总长度
 用两个指针或下标P1和P2，从尾部开始，P1指向新串尾部，P2指向原串尾部，P2指向的字符不是空格就复制到P1--；P2指向的字符是空格，P1--依次赋值'0' '2' '%'，然后P2--
 @param string 原字符串
 @param length 存储原字符串的空间的长度，确保可以容纳新字符串
 */
 void ReplaceBlank(char string[], int length)
 {
 	if (string == NULL || length <= 0)
 		return;
 	int i = 0;
 	int blankLength = 0, oldLength = 0, newLength = 0;
 	while (string[i ++] != '\0')
 	{
 		oldLength ++;
 		if (string[i] == ' ')
 			blankLength ++;
 	}
 	newLength = oldLength + 2 * blankLength;
 	if (newLength + 1 > length)
 		return;
 	string[newLength] = '\0';
 	int p1 = newLength - 1, p2 = oldLength - 1;
 	while (p2 >= 0)
 	{
 		if (string[p2] != ' ')
 			string[p1 --] = string[p2];
 		else
 		{
 			string[p1 --] = '0';
 			string[p1 --] = '2';
 			string[p1 --] = '%';
 		}
 		p2 --;
 	}
 }

 /*
 T5. 从尾到头打印链表中的节点值
 两种方案，一种是用递归，一种是用栈来缓存前序节点
 */
 void PrintListReversingly_Recursively(ListNode* pHead)
{
	//当前节点不为NULL
	if (pHead != NULL)
	{
		//如果当前节点有子节点的话，就递归
		if (pHead->m_pNext != NULL)
		{
			PrintListReversingly_Recursively(pHead->m_pNext);
		}
		//否则输出
		printf("%d\t", pHead->m_nValue);
	}
}
void PrintListReversingly_Iteratively(ListNode* pHead)
{
	std::stack<ListNode*> nodes;
	ListNode* pNode = pHead;
	while (pNode != NULL)
	{
		nodes.push(pNode);
		pNode = pNode->m_pNext;
	}
	while (!nodes.empty())
	{
		pNode = nodes.top();
		printf("%d\t", pNode->m_nValue);
		nodes.pop();
	}
}

/*
 T6. 根据二叉树的前序遍历和中序遍历，重建该二叉树。
 参数：preorder为前序遍历数组，inorder为中序遍历数组，length为数组长度
          root |   left    |    right    |
 preorder-> 1 	2 	4 	7 	3 	5 	6 	8
 inorder -> 4 	7 	2 	1 	5 	3	8 	6
           |   left  | root|    right    |   
 preorder指向的第一个节点是root，然后再inorder序列中寻找root的位置，左边的就是left右边的就是right。
 然后递归地对left和right再进行这样的识别root
*/
 BinaryTreeNode* ConstructCore(int* startPreorder, int* endPreorder, int* startInorder, int* endInorder);
 BinaryTreeNode* Construct(int* preorder, int* inorder, int length)
 {
 	if (preorder == NULL || inorder == NULL || length <= 0)
 		return NULL;
 	printf("sub-tree root order: ");
 	return ConstructCore(preorder, preorder + length - 1, inorder, inorder + length - 1);	
 }
 BinaryTreeNode* ConstructCore(int* startPreorder, int* endPreorder, int* startInorder, int* endInorder)
 {
 	//前序遍历的第一个数字是根结点的值
 	int rootValue = startPreorder[0];
 	BinaryTreeNode* root = new BinaryTreeNode();
 	root->m_nValue = rootValue;
 	root->m_pLeft = root->m_pRight = NULL;
 	printf("%d\t", root->m_nValue);

 	if(startPreorder == endPreorder)
 	{
 		//到达叶子节点，不必再向下
 		if (startInorder == endInorder && *startPreorder == *startInorder)
 			return root;
 		else
 		{
 			std::runtime_error err("Invalid input.");
 			throw err;
 		}
 	}

 	//在中序遍历中找到根节点的位置，从而将左右子树分开
 	int* rootInorder = startInorder;
 	while (rootInorder <= endInorder && *rootInorder != rootValue)
 		++ rootInorder;
 	//前序和中序遍历冲突，输入错误
 	if (rootInorder == endInorder && *rootInorder != rootValue)
 	{
 		std::runtime_error err("Invalid input.");
 		throw err;
 	}
 	/*
 	             start                         end
		 inorder -> 4 	7 	2 	1 	5 	3	8 	6
          	       |   left  | root|    right    |
 	*/
 	int leftLength = rootInorder - startInorder;
 	int* leftPreorderEnd = startPreorder + leftLength;
 	if (leftLength > 0)
 	{
 		//构建左子树，把左子树先序遍历传入
 		root->m_pLeft = ConstructCore(startPreorder + 1, leftPreorderEnd, startInorder, rootInorder - 1);
 	}
 	if (leftLength < endPreorder - startPreorder)
 	{
 		//构建右子树，把右子树先序遍历传入
 		root->m_pRight = ConstructCore(leftPreorderEnd + 1, endPreorder, rootInorder + 1, endInorder);
 	}	
 	return root;
 }

 /*
 T7. 用两个栈实现队列，appendTail和deleteHead，分别完成在队列尾部插入节点和在对垒头部删除节点的功能
 见queue.h 和 queue.cpp
 插入数据：一直往stack1中压入数据即可
 删除数据：如果stack2为空，就从stack1中依次弹出所有的数据并压入到stack2，stack2中便是删除节点的顺序
 */
 void queueUsingStacks()
 {
 	// 模板类的实现必须要放在.h头文件中，不能单独放在cpp文件中
 	CQueue<int> queue;
 	for (int i = 0; i < 10; ++i)
 	{
 		int element = i;
 		queue.appendTail(element);
 	}
 	std::cout << "Queue: ";
 	while (queue.size() > 0)
 	{
 		std::cout << queue.deleteHead() << ", ";
 	}
 	std::cout << std::endl;
 }
 /*
 用两个队列实现栈
 */
 void stackUsingQueues()
 {
 	CStack<int> stack;
 	for (int i = 0; i < 10; i ++)
 	{
 		stack.pushToTop(i);
 	}
 	std::cout << "Stack: ";
 	while (stack.size() > 0)
 	{
 		std::cout << stack.popFromTop() << ", ";
 	}
 	std::cout << std::endl;
 }

 /*
 T8. 求旋转数组中的最小数字
 输入一个递增排序的数组的一个旋转，如一个递增数组{1,2,3,4,5}的一个旋转{3,4,5,1,2}
 根据{3,4,5,1,2}，输出最小元素1
 最差情况：顺序查找O(n)
 二分查找O(logn)
 */
 //顺序查找，这里没有做异常输入的处理，调用者注意
 int MinInOrder(int* numbers, int left, int right)
 {
 	int min = numbers[left];
 	for (int i = left + 1; i <= right ; ++i)
 	{
 		if (numbers[i] < min)
 			min = numbers[i];
 	}
 	return min;
 }
 /*
 3, 4, 5, 6, 1, 2 偶数个
 5, 6, 1, 2
 6, 1, 2
 6, 1
 left, right 返回right

 3, 4, 5, 1, 3 奇数个，left=right != mid
 5, 1, 3
 5, 1
left, right 返回right

1,1,0,1 left=right=mid
直接顺序查找
 */
 int MinInRotate(int* numbers, int length)
 {
 	if (numbers == NULL || length < 1)
 	{
 		std::runtime_error err("Min() : invalid input, NULL");
 		throw err;
 	}
 	int left = 0, right = length - 1;
 	int mid  = left;
 	// 旋转数组的左区比右区大（除特例外），并且最左比最右的还要大，左右两个指针不断向中间靠，找到最小元
 	// 特例是{1,0,1,1,1} {1,1,1,0,1}  left right mid的值相等
 	while (numbers[left] >= numbers[right])
 	{
 		if (right - left == 1)
 		{
 			mid = right;
 			break;
 		}
 		mid = (left + right) / 2;
 		//这里求解只有一个元素的数组 和 特例数组，用顺序查找
 		if (numbers[left] == numbers[right] && numbers[mid] == numbers[left])
 			return MinInOrder(numbers, left, right);

 		// 当前mid还处在左区，而真正的最小值还在右边，所以让left = min，往右移动检查
 		if (numbers[mid] >= numbers[left])
 			left = mid;
 		// 当前mid还处在右区，而真正的最小值还在左边，所以让right = min，往左移动检查
 		else if (numbers[mid] <= numbers[right])
 			right = mid;
 	}
 	return numbers[mid];
 }

/*
 T9. 循环实现斐波拉契数列。可以解决：
 青蛙跳台阶问题
 铺地板问题
*/
 //输入限制为unsigned int型。。
long long Fibonaci(unsigned n)
{
	int result[2] = {0, 1};
	if (n < 2)
		return result[n];

	long long fibN_1 = 1;
	long long fibN_2 = 0;
	long long fibN = 0;
	for (unsigned int i = 2; i <= n; i ++)
	{
		fibN = fibN_1 + fibN_2;
		fibN_2 = fibN_1;
		fibN_1 = fibN;
	}
	return fibN;
}

/*
 T10. 二进制中1的个数
 注意正数和负数，位运算实现
 相关题目：判断一个整数是不是2的整数次方，如果是，它的二进制表示中只有一位是1，(n-1)&n就等于0
 两个整数m和n，计算m的二进制表示中需要改变多少位才能变成n的二进制表示，先对二者做异或再统计结果中1的位数。
*/
//方法1：n & flag, flag = flag<<1，直接用&检测每一位
//输入：有符号int
//输出：该数字二进制表示的1的个数
int NumberOf1(int n)
{
	unsigned int flag = 1;
	int count = 0;
	while (flag)
	{
		if (n & flag)
			count ++;
		flag = flag << 1;
	}
	return count;
}
//用减1的方法计算，一个数减去1以后，最右边的1变成0，并且该位以后的0都变成1
//再“与”原数，就消去了最右边的那个1，即(n-1) & n 消去了最右边的1
int NumberOf1New(int n)
{
	int count = 0;
	while (n)
	{
		++ count;
		n = (n - 1) & n;
	}
	return count;
}

int main(int argc, char const *argv[])
{
	//sumFromInput();
	//copyFile(argc, argv);
	std::cout << sizeof(Blank) << std::endl;
	//C++还可以这样创建对象。。。。直接赋值，调用了A(int n)
	A a = 10;
	a.Print();
	//这里则是调用了A(const A& other)
	A b = a;
	b.Print();

	//C风格字符串，将字符串常量最好赋给字符数组而不是字符指针。
	char str[] = "hehe";
	CMyString c(str);
	c.Print();
	//默认执行构造函数
	CMyString d;
	//执行operator =
	d = c;
	d.Print();

	//单例
	Singleton1* s1 = Singleton1::Instance();
	Singleton1* s2 = Singleton1::Instance();
	std::cout << "Singleton1: s1==s2? " << (s1 == s2) << std::endl;

	//sizeof(数组名)结果是数组大小=元素个数*每个元素所占字节数
	//sizeof(指针)结果是指针变量所占字节数，数组名传入到函数中自动转换成指针类型
	TestSizeof();

	int matrix[] = {1, 2, 8, 9, 2, 4, 9, 12, 4, 7, 10, 13, 6, 8, 11, 15};
	if (Find(matrix, 4, 4, 7))
		std::cout << "Found 7" << std::endl;
	else
		std::cout << "Not found 7" << std::endl;

	//替换掉原串中的空格为%20
	char string[100] = "I am not a hacker!";
	std::cout << "Original string: " << string << std::endl;
	ReplaceBlank(string, 100);
	std::cout << "ReplaceBlank: " << string << std::endl;

	//链表测试
	List myList;
	/*
	ListNode* aNode = new ListNode();
	aNode->m_nValue = 0;
	aNode->m_pNext = NULL;
	myList.m_pList = aNode;*/
	for (int i = 0; i < 10; i ++)
	{
		myList.AddToTail(&myList.m_pList, i);
	}
	PrintListReversingly_Recursively(myList.m_pList);

	//二叉树测试
	int preorder[] = {1, 2, 4, 7, 3, 5, 6, 8};
	int inorder[] = {4, 7, 2, 1, 5, 3, 8, 6};
	BinaryTreeNode* binaryTree = NULL;
	binaryTree = Construct(preorder, inorder, 8);

	//队列测试
	std::cout << std::endl;
	queueUsingStacks();
	//栈测试
	stackUsingQueues();

	//排序测试
	int sA = 10;
	int sB = 20;
	Swap(sA, sB);
	std::cout << "Swap: " << sA << ", " << sB << std::endl;
	int sortA[] = {1, 4, 6, 2, 6, 7, 2, 3, 9, 1, 10};
	//这里还是可以求数组大小的
	std::cout << "sortArray size: " << sizeof(sortA) / sizeof(int) << std::endl;
	int n = sizeof(sortA)/sizeof(int);
	//InsertSort(sortA, n);
	//ShellSort(sortA, n);
	//BubbleSort(sortA, n);
	std::cout << "Before sort: ";
	PrintArray(sortA, n);
	std::cout << "Quick sort: ";
	QuickSort(sortA, 0, n-1);
	//SelectionSort(sortA, n);
	//HeapSort(sortA, n);
	//MergeSort(sortA, 0, n-1);
	//InSituMergeSort(sortA, 0, n-1);
	PrintArray(sortA, n);
	char partitionString[7] = {'a', 'A', 'Z', 'd', 'B', 's', 'b'};
	CharPartition(partitionString, 0, 6);
	int threeCollection[] = {0, 1, 2, 1, 1, 2, 0, 2, 1, 0};
	ThreePartition(threeCollection, 0, 9);
	PrintArray(threeCollection, 10);

	//旋转数组的最小数字
	int rotateArray[] = {3,4,5,6,1,2,3};
	std::cout << "Min value in rotateArray: " << MinInRotate(rotateArray, 7) << std::endl;

	//斐波拉契数
	std::cout << "Fibonaci(100): " << Fibonaci(100) << std::endl;

	//位运算
	std::cout << "NumberOf1(127): " << NumberOf1(127) << ", " << NumberOf1New(127) << std::endl;

	//T11. 数值的整数次方运算
	std::cout << "PowerWithUnsignedExponent(0.2, 3): " << PowerWithUnsignedExponent(0.2, 3) << std::endl;
	std::cout << "Power(0.2, -3): " << Power(0.2, -3) << std::endl;
	std::cout << "g_InvalidInput: " << g_InvalidInput << std::endl;

	//T12. 打印从1到最大的n位数
	Print1ToMaxOfNDigits(2);
	std::cout << std::endl;
	
	// 两个用字符串表示的大数相加，只考虑两个正数
	char number1[] = "123";
	char number2[] = "11111";
	char* result = NULL;
	result = AddTowBigDigits(number1, number2);
	std::cout << "AddTwoBigDigits(): " << result << std::endl;
	delete[] result;


	return 0;
}