#include <stdio.h>
class Base
{
public:
	int Bar(char x) {return (int)x; }
	virtual int Bar(int x) {return 2*x; }
};

class Derived: public Base
{
public:
	//非virtual重写，隐藏规则子类直接覆盖父类的方法
	//看指向对象的指针是父类类型还是子类类型
	int Bar(char x) {return (int)(-x); }
	//virtual重写，对象是子类，不管指针是父类类型还是子类类型
	//总是调用该子类对象的这个方法
	int Bar(int x) {return (x / 2);}
};

int main()
{
	Derived Obj;
	//子类的对象，指针是父类类型
	Base* pObj = &Obj;
	//调用非virtual方法，虽然隐含覆盖规则，但取决于指针类型是父类还是子类
	printf("%d, ", pObj->Bar((char)100));
	//virtual，重写的方法，子类对象总是调用子类方法
	printf("%d", pObj->Bar(100));
	return 0;
}