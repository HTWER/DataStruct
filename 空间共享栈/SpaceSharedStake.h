#ifndef __SPACESHAREDSTACK_H__
#define __SPACESHAREDSTACK_H__

#include <iostream>
using namespace std;

const int StackSize = 100;			//栈的最大长度

template <class DataType>
class SpaceSharedStack
{
public:
	SpaceSharedStack();
	~SpaceSharedStack(){}

	void Push(int i, DataType x);	//压栈
	DataType Pop(int i);			//弹栈

	DataType GetTop(int i);			//获去指定栈顶元素
	int IsEmpty(int i);				//检测指定的栈是否为空

private:
	DataType m_data[StackSize];		//数据存储
	int m_top1, m_top2;				//两个栈顶的位置
};

template <class DataType>
SpaceSharedStack<DataType>::SpaceSharedStack()
{
	m_top1 = -1;
	m_top2 = StackSize;
}

template <class DataType>
void SpaceSharedStack<DataType>::Push(int i, DataType x)
{
	if (m_top1 == m_top2 - 1)
	{
		cout << "栈已满,添加失败" << endl;
		abort();
	}
	else
	{
		if (i == 1)
			m_data[++m_top1] = x;
		else if (i == 2)
			m_data[--m_top2] = x;
	}
}

template <class DataType>
DataType SpaceSharedStack<DataType>::Pop(int i)
{
	if (i == 1)
	{
		if (m_top1 == -1)
		{
			cout << "栈一为空，弹出失败" << endl;
			abort();
		}
		else
			return m_data[m_top1--];
	}
	else if (i == 2)
	{
		if (m_top2 == StackSize)
		{
			cout << "栈二为空，弹出失败";
			abort();
		}
		else
			return m_data[m_top2++];
	}
}

template <class DataType>
DataType SpaceSharedStack<DataType>::GetTop(int i)
{
	if (i == 1)
	{
		if (m_top1 == -1)
		{
			cout << "栈一越界访问" << endl;
			abort();
		}
		else
			return m_data[m_top1];
	}
	else if (i == 2)
	{
		if (m_top2 == StackSize)
		{
			cout << "栈二越界访问" << endl;
			abort();
		}
		else
			return m_data[m_top2];
	}
}

template <class DataType>
int SpaceSharedStack<DataType>::IsEmpty(int i)
{
	if (i == 1)
	{
		if (m_top1 == -1)
			return 1;
	}
	else if (i == 2)
	{
		if (m_top2 == StackSize)
			return 1;
	}
	return 0;
}

#endif