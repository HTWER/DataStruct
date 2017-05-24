#ifndef __CIRQUEUE_H__
#define __CIRQUEUE_H__

#include <iostream>
using namespace std;

//循环队列(下面所说的指针并不是c++的指针)：
//队头指针指向队头的元素的前一个位置，队尾指针指向队尾的元素
//队空条件：头指针指向尾指针
//队满条件：尾指针在头指针的前一位
//会浪费一个存储空间

template <class DataType>
class CirQueue
{
#define MaxSize 100
public:
	CirQueue();
	~CirQueue(){}

	void Push(DataType x);	//从队尾开始增加
	DataType Pop();			//从队头开始删除
	DataType Back();

	int IsEmpty();

private:
	DataType m_data[MaxSize];
	int m_front, m_rear;
};

template <class DataType>
CirQueue<DataType>::CirQueue()
{
	m_front = m_rear = MaxSize - 1;
}

template <class DataType>
void CirQueue<DataType>::Push(DataType x)
{
	//队满条件:(rear + 1) % MaxSize == front
	if ((m_rear + 1) % MaxSize == m_front)
	{
		cout << "队列已满，无法添加" << endl;
		abort();
	}

	m_rear = (m_rear + 1) % MaxSize;
	m_data[m_rear] = x;

}

template <class DataType>
DataType CirQueue<DataType>::Pop()
{
	if (IsEmpty())                //队空
	{
		cout << "队列为空，无法出队" << endl;
		abort();
	}

	m_front = (m_front + 1) % MaxSize;
	return m_data[m_front];
}

template <class DataType>
DataType CirQueue<DataType>::Back()
{
	if (IsEmpty())                //队空
	{
		cout << "队列为空，无法获取" << endl;
		abort();
	}

	int i = (m_front + 1) % MaxSize;
	return m_data[i];
}

template <class DataType>
int CirQueue<DataType>::IsEmpty()
{
	//队空的条件:front==rear;尽量不要在三目运算符中用两个return
	return m_front == m_rear ? 1 : 0;
}

#endif