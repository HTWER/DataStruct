#ifndef __SPACESHAREDSTACK_H__
#define __SPACESHAREDSTACK_H__

#include <iostream>
using namespace std;

const int StackSize = 100;			//ջ����󳤶�

template <class DataType>
class SpaceSharedStack
{
public:
	SpaceSharedStack();
	~SpaceSharedStack(){}

	void Push(int i, DataType x);	//ѹջ
	DataType Pop(int i);			//��ջ

	DataType GetTop(int i);			//��ȥָ��ջ��Ԫ��
	int IsEmpty(int i);				//���ָ����ջ�Ƿ�Ϊ��

private:
	DataType m_data[StackSize];		//���ݴ洢
	int m_top1, m_top2;				//����ջ����λ��
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
		cout << "ջ����,���ʧ��" << endl;
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
			cout << "ջһΪ�գ�����ʧ��" << endl;
			abort();
		}
		else
			return m_data[m_top1--];
	}
	else if (i == 2)
	{
		if (m_top2 == StackSize)
		{
			cout << "ջ��Ϊ�գ�����ʧ��";
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
			cout << "ջһԽ�����" << endl;
			abort();
		}
		else
			return m_data[m_top1];
	}
	else if (i == 2)
	{
		if (m_top2 == StackSize)
		{
			cout << "ջ��Խ�����" << endl;
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