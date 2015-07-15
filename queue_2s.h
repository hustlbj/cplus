///:queue.h
#ifndef QUEUE_2S_H
#define QUEUE_2S_H
#include <cstddef>
#include <stack>
#include <stdexcept>

/*
 模板类的实现必须放在.h头文件中
*/
template <typename T> class CQueue
{
public:
	CQueue() {}
	~CQueue() {}

	void appendTail(const T& node)
	{
		stack1.push(node);
	}

	T deleteHead()
	{
		if (stack2.size() <= 0)
		{
			while (stack1.size() > 0)
			{
				T& data = stack1.top();
				stack1.pop();
				stack2.push(data);
			}
		}
		if (stack2.size() == 0)
		{
			std::runtime_error err("queue is empty.");
 			throw err;
		}
		
		T head = stack2.top();
		stack2.pop();
		return head;
	}

	size_t size() { return stack1.size() + stack2.size(); }
private:
	std::stack<T> stack1;
	std::stack<T> stack2;
};

#endif