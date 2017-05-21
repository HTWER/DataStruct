#ifndef __ORDER_H__
#define __ORDER_H__

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <cstring>
using namespace std;

//����һ�����ķ�����
//�����죺��Ҫ��֤����������������������̬����û�нڵ�ĵط�ҲҪռһ��λ��
//ǰ���죺��Ҫ��֤�������е�ÿһ���ǿ�Ԫ�ض�Ҫ���������ӽڵ㣬��ʹ�÷ǿ�Ԫ��û�к��ӽڵ�ҲҪռһ��λ��
//			ԭ����ͨ��һ���������޷�����һ�����ģ�����Ҫ����������������һ�����������򣻵���ͨ������ķ�������ͨ��һ�����й����һ������

template <class DataType>
struct Node
{
	DataType m_data;	//ʵ������
	bool m_isEmpty;		//�Ƿ�Ϊռλ�ڵ�

	//��Ҫ
	Node()
	{
		m_isEmpty = true;
	}
};

template <class DataType>
class OrderTree
{
public:
	OrderTree(){}
	~OrderTree(){}

	//����֮���ÿո���������ջس�
	//����ʵ�������в����԰����ո���ʵ�����ݲ�����Ϊ"#"
	//Ҫ����������֧��>>��ʼ��
	void PreConstructByCin(){ PreConstructByCin(0); }
	void LevelConstructByCin();

	void PreOrder(){ PreOrder(0); }
	void InOrder(){ InOrder(0); }
	void PostOrder(){ PostOrder(0); }
	void LevelOrder(){ LevelOrder(0); }

private:
	void PreConstructByCin(int index);

	//���±�����Ҫ��������֧��<<���㣻
	//�ұ�������һ����ִ����ɣ����Ҫ������������ⲿ�ɿصģ�ǰ�к�����Ҫʹ��һ��ջ�����Ʊ����Ĺ��̣�������Ҫһ���������¼��ǰ����λ�ã�
	void PreOrder(int number);
	void InOrder(int number);
	void PostOrder(int number);
	void LevelOrder(int number);

	//ʹ����������������һ������ռλ�ڵ㣬����ʵ������֮���Ԫ�ض���ռλ��,�������󳤶������һ��ʵ�����ݵ�λ��+1
	vector<Node<DataType>> m_space;		
};

template <class DataType>
void OrderTree<DataType>::PreConstructByCin(int index)
{
	Node<DataType> node;
	string str;
	cin >> str;
	
	if (str != "#")
	{
		node.m_isEmpty = false;
		stringstream ss(str);
		ss >> node.m_data;

		//������Ҫ����
		if (index >= m_space.size())
			m_space.resize(index + 1);
		m_space[index] = node;
		if (str != "#")
		{
			PreConstructByCin(2 * index + 1);
			PreConstructByCin(2 * index + 2);
		}
	}
}

template <class DataType>
void OrderTree<DataType>::LevelConstructByCin()
{
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
		m_space.push_back(node);

		str = strtok(NULL, " ");
	}
}

template <class DataType>
void OrderTree<DataType>::PreOrder(int number)
{
	if (number >= m_space.size() || m_space[number].m_isEmpty)
	{
		
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
	if (number >= m_space.size() || m_space[number].m_isEmpty)
	{

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
	if (number >= m_space.size() || m_space[number].m_isEmpty)
	{

	}
	else
	{
		PostOrder(number * 2 + 1);
		PostOrder(number * 2 + 2);
		cout << m_space[number].m_data << " ";
	}
}

template <class DataType>
void OrderTree<DataType>::LevelOrder(int number)
{
	for (int i = 0; i < m_space.size(); i++)
	{
		if (!m_space[i].m_isEmpty)
		{
			cout << m_space[i].m_data << " ";
		}
	}
}

#endif