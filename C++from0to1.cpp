/*
	C++ 入门练习
*/
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
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

int main(int argc, char const *argv[])
{
	//sumFromInput();
	copyFile(argc, argv);
	return 0;
}