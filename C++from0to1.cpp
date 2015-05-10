#include <iostream>
#include <string>
#include <sstream>
using namespace std;

void sumFromInput()
{
	int sum = 0;
	int temp = 0;
	int ret = 0;
	char char_temp;
	string str_temp;
	//cin >> 是以空格做分割的
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
			//忽略换行之前的所有字符，清除当前行
			//cin.ignore(1024, '\n');
			cin.ignore(1024, '\x20');
			//cin.get()可以直接读取一个字符，也可以指定(数组名，长度，结束符)来读取字符串
			//char_temp = cin.get();
			//cout << "get(): " << char_temp << endl;
		}*/
	}
	cout << sum << endl;
}

int main(int argc, char const *argv[])
{
	sumFromInput();
	return 0;
}