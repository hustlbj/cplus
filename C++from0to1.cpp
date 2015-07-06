/*
	C++ 入门练习
*/
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <cstring>
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

	char* str = "hehe";
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
	std::cout << "Singleton1: " << (s1 == s2) << std::endl;

	return 0;
}