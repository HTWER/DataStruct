#ifndef __CIRQUEUE_H__
#define __CIRQUEUE_H__

#include <iostream>
using namespace std;

//ѭ������(������˵��ָ�벢����c++��ָ��)��
//��ͷָ��ָ���ͷ��Ԫ�ص�ǰһ��λ�ã���βָ��ָ���β��Ԫ��
//�ӿ�������ͷָ��ָ��βָ��
//����������βָ����ͷָ���ǰһλ
//���˷�һ���洢�ռ�

template <class DataType>
class CirQueue
{
#define MaxSize 100
public:
	CirQueue();
	~CirQueue(){}

	void Push(DataType x);	//�Ӷ�β��ʼ����
	DataType Pop();			//�Ӷ�ͷ��ʼɾ��
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
	//��������:(rear + 1) % MaxSize == front
	if ((m_rear + 1) % MaxSize == m_front)
	{
		cout << "�����������޷����" << endl;
		abort();
	}

	m_rear = (m_rear + 1) % MaxSize;
	m_data[m_rear] = x;

}

template <class DataType>
DataType CirQueue<DataType>::Pop()
{
	if (IsEmpty())                //�ӿ�
	{
		cout << "����Ϊ�գ��޷�����" << endl;
		abort();
	}

	m_front = (m_front + 1) % MaxSize;
	return m_data[m_front];
}

template <class DataType>
DataType CirQueue<DataType>::Back()
{
	if (IsEmpty())                //�ӿ�
	{
		cout << "����Ϊ�գ��޷���ȡ" << endl;
		abort();
	}

	int i = (m_front + 1) % MaxSize;
	return m_data[i];
}

template <class DataType>
int CirQueue<DataType>::IsEmpty()
{
	//�ӿյ�����:front==rear;������Ҫ����Ŀ�������������return
	return m_front == m_rear ? 1 : 0;
}

#endif