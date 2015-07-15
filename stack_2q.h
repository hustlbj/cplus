///:stack_2q.h
#ifndef STACK_2Q_H
#define STACK_2Q_H
#include <queue>
#include <cstddef>
#include <stdexcept>

template <typename T> 
class CStack
{
public:
	CStack() {}
	~CStack() {}
	void pushToTop(const T& element) 
	{
		queue1.push(element);
	}
	T popFromTop() 
	{
		// 元素都在queue1中，这时候需要把queue1中的元素按照队列次序插入到queue2中（除最后一个元素），最后一个元素就是要弹出的元素
		if (queue2.empty() && queue1.size() > 0)
		{
			while (queue1.size() > 1)
			{
				T& front = queue1.front();
				queue1.pop();
				queue2.push(front);
			}
			T& top = queue1.front();
			//现在queue1为空了
			queue1.pop();
			return top;
		}
		if (queue1.empty() && queue2.size() > 0)
		{
			while (queue2.size() > 1)
			{
				T& front = queue2.front();
				queue2.pop();
				queue1.push(front);
			}
			T& top = queue2.front();
			queue2.pop();
			return top;
		}
		if (queue1.empty() && queue2.empty())
		{
			std::runtime_error err("stack is empty");
			throw err;
		}
	}
	size_t size() { return queue1.size() + queue2.size(); }
private:
	//queue.push  queue.pop  queue.front  queue.back  queue.empty  queue.size
	std::queue<T> queue1;
	std::queue<T> queue2;
};

#endif

