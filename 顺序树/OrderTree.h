#ifndef __ORDER_H__
#define __ORDER_H__

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <cstring>
using namespace std;

//ͨ���������ղ��򱣴�һ����
//ǰ�к����е�ǰ�к�ָ�ĸ��ı���˳��

template <class DataType>
struct Node
{
	DataType m_data;	//ʵ������
	bool m_isEmpty;		//�Ƿ�Ϊռλ�ڵ�
};

//��Ȼʹ��ģ�壬���ǽ���֧��cin>>��ʼ����cout<<������ݵ���������;
template <class DataType>
class OrderTree
{
public:
	OrderTree(){};
	~OrderTree(){}

	void ConstructByCin();
	void PreOrder(){ PreOrder(0); }
	void InOrder(){ InOrder(0); }
	void PostOrder(){ PostOrder(0); }
	void LeverOrder(){ LeverOrder(0); }

private:
	void PreOrder(int number);
	void InOrder(int number);
	void PostOrder(int number);
	void LeverOrder(int number);
	vector<Node<DataType>> m_space;
};

//���ղ����������
template <class DataType>
void OrderTree<DataType>::ConstructByCin()
{
	//һ���Ի�ȡ�������е����ݣ�
	//����֮���ÿո���������ջس�
	//����ʵ�������в����԰����ո���ʵ�����ݲ�����Ϊ"#"
	//����������1024���ַ�����
	string line;
	getline(cin, line);

	char charSource[1024];
	strcpy(charSource, line.c_str());

	//�ָ��ַ���
	char* str = strtok(charSource, " ");
	while (str != NULL)
	{
		Node<DataType> node;
		if (strcmp(str, "#"))
		{
			node.m_isEmpty = false;
			stringstream ss(str);
			ss >> node.m_data;
		}
		else
		{
			node.m_isEmpty = true;
		}

		m_space.push_back(node);

		str = strtok(NULL, " ");
	}
}

template <class DataType>
void OrderTree<DataType>::PreOrder(int number)
{
	if (number >= m_space.size())
	{

	}
	else if (m_space[number].m_isEmpty)
	{
		cout << "NULL" << " ";
	}
	else
	{
		cout << m_space[number].m_data << " ";
		PreOrder(number * 2 + 1);
		PreOrder(number * 2 + 2);
	}
}

template <class DataType>
void OrderTree<DataType>::InOrder(int number)
{
	if (number >= m_space.size())
	{

	}
	else if (m_space[number].m_isEmpty)
	{
		cout << "NULL" << " ";
	}
	else
	{
		InOrder(number * 2 + 1);
		cout << m_space[number].m_data << " ";
		InOrder(number * 2 + 2);
	}
}

template <class DataType>
void OrderTree<DataType>::PostOrder(int number)
{
	if (number >= m_space.size())
	{

	}
	else if (m_space[number].m_isEmpty)
	{
		cout << "NULL" << " ";
	}
	else
	{
		PostOrder(number * 2 + 1);
		PostOrder(number * 2 + 2);
		cout << m_space[number].m_data << " ";
	}
}

template <class DataType>
void OrderTree<DataType>::LeverOrder(int number)
{
	for (int i = 0; i < m_space.size(); i++)
	{
		if (m_space[i].m_isEmpty)
		{
			cout << "NULL" << " ";
		}
		else
		{
			cout << m_space[i].m_data << " ";
		}
	}
}

#endif