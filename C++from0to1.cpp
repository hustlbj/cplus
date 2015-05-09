#include <iostream>
using namespace std;

void sumFromInput()
{
	int sum = 0;
	int temp = 0;
	int ret = 0;
	//cin是以空格做分割的
	while (1)
	{
		if (cin.peek() == '\n')
			break;
		cout << "peek(): " << cin.peek() << ", ";
		cin >> temp;
		//fail()判断cin>>temp是否失败，1为输入转换失败
		cout << "fail(): " << cin.fail() << endl;
		//成功读入一个整型数字
		if (cin.fail() != 1)
		{
			sum += temp;
		}
		//输入类型不对则忽略
		else
		{
			cin.clear();
			cin.ignore();
		}
	}
	cout << sum << endl;
}

int main(int argc, char const *argv[])
{
	sumFromInput();
	return 0;
}