#ifndef __ORDEREDBINARYTREE_H__
#define __ORDEREDBINARYTREE_H__

//˳�������(OrderedBinaryTree)

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
//���������е�ռλֻ���ṩ������Ҫ����Ϣ����һ�����е�ռλ�ڵ㶼��Ҫ�洢��������

template <class DataType>
struct TreeNode
{
	DataType m_data;	//ʵ������
	bool m_isEmpty;		//�Ƿ�Ϊռλ�ڵ�

	//��Ҫ
	TreeNode()
	{
		m_isEmpty = true;
	}
};

//˳����������+���ṹ���Զ���
template <class DataType>
class OrderedBinaryTree
{
public:
	OrderedBinaryTree(){}
	~OrderedBinaryTree(){}

	//����֮���ÿո���������ջس�
	//����ʵ�������в����԰����ո���ʵ�����ݲ�����Ϊ"#"
	//Ҫ����������֧��>>��ʼ��
	void PreConstructByCin(){ PreConstructByCin(0); }
	void LevelConstructByCin();

	//��ɾ��Ĺ���..............���ҹ���Ҫ�����ݲ��ܹ��ظ���������ܲ��ҵõ��Ľ������Ԥ�ڲ��������Ӳ��Ҫ�����ݿ����ظ�����ô������Ҫ����������������һ������

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
	vector<TreeNode<DataType>> m_space;		
};

template <class DataType>
void OrderedBinaryTree<DataType>::PreConstructByCin(int index)
{
	TreeNode<DataType> TreeNode;
	string str;
	cin >> str;
	
	if (str != "#")
	{
		TreeNode.m_isEmpty = false;
		stringstream ss(str);
		ss >> TreeNode.m_data;

		//������Ҫ����
		if (index >= m_space.size())
			m_space.resize(index + 1);
		m_space[index] = TreeNode;
		if (str != "#")
		{
			PreConstructByCin(2 * index + 1);
			PreConstructByCin(2 * index + 2);
		}
	}
}

template <class DataType>
void OrderedBinaryTree<DataType>::LevelConstructByCin()
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
		TreeNode<DataType> TreeNode;
		if (strcmp(str, "#"))
		{
			TreeNode.m_isEmpty = false;
			stringstream ss(str);
			ss >> TreeNode.m_data;
		}
		m_space.push_back(TreeNode);

		str = strtok(NULL, " ");
	}
}

template <class DataType>
void OrderedBinaryTree<DataType>::PreOrder(int number)
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
void OrderedBinaryTree<DataType>::InOrder(int number)
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
void OrderedBinaryTree<DataType>::PostOrder(int number)
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
void OrderedBinaryTree<DataType>::LevelOrder(int number)
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