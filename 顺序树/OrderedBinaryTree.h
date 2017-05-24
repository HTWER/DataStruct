#ifndef __ORDEREDBINARYTREE_H__
#define __ORDEREDBINARYTREE_H__

//顺序二叉树(OrderedBinaryTree)

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <cstring>
using namespace std;

//构造一棵树的方法：
//层序构造：需要保证构造序列是满二叉树的形态，即没有节点的地方也要占一个位；
//前序构造：需要保证构造序列的每一个非空元素都要有两个孩子节点，即使该非空元素没有孩子节点也要占一个位；
//			原本仅通过一个序列是无法构造一棵树的，必须要有两个序列且其中一个序列是中序；但是通过上面的方法可以通过一个序列构造出一棵树；
//构造序列中的占位只是提供构造需要的信息，不一定所有的占位节点都需要存储到数组中

template <class DataType>
struct TreeNode
{
	DataType m_data;	//实际数据
	bool m_isEmpty;		//是否为占位节点

	//重要
	TreeNode()
	{
		m_isEmpty = true;
	}
};

//顺序树：数组+树结构可自定义
template <class DataType>
class OrderedBinaryTree
{
public:
	OrderedBinaryTree(){}
	~OrderedBinaryTree(){}

	//数据之间用空格隔开，最终回车
	//输入实际数据中不可以包含空格，且实际数据不可以为"#"
	//要求数据类型支持>>初始化
	void PreConstructByCin(){ PreConstructByCin(0); }
	void LevelConstructByCin();

	//增删查改功能..............查找功能要求数据不能够重复，否则可能查找得到的结果会与预期不符；如果硬性要求数据可以重复，那么查找需要遍历整个树来返回一个数组

	void PreOrder(){ PreOrder(0); }
	void InOrder(){ InOrder(0); }
	void PostOrder(){ PostOrder(0); }
	void LevelOrder(){ LevelOrder(0); }

private:
	void PreConstructByCin(int index);

	//以下遍历需要数据类型支持<<运算；
	//且遍历都是一次性执行完成，如果要求遍历过程是外部可控的，前中后序需要使用一个栈来控制遍历的过程，层序需要一个标记来记录当前遍历位置；
	void PreOrder(int number);
	void InOrder(int number);
	void PostOrder(int number);
	void LevelOrder(int number);

	//使用数组来保存树，一定会有占位节点，两个实际数据之间的元素都是占位的,数组的最大长度是最后一个实际数据的位置+1
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

		//可能需要扩容
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
	//输入数据在1024个字符以内
	string line;
	getline(cin, line);
	char charSource[1024];
	strcpy(charSource, line.c_str());

	//分割字符串
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