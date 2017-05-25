#ifndef _HUFFMANTREE_H__
#define _HUFFMANTREE_H__

#include <iostream>
#include <vector>
#include <string>
using namespace std;

//这里的树不是OT，也不是LT，而是类似于LT的树；
//因为节点不是用指针连接，而是用一个号码来连接，号码代表着节点在数组中的位置
struct TreeNode
{
	//公有属性
	int weight;
	int lchild, rchild;
	int parent;
	//仅叶子拥有的属性
	bool isLeaves;
	string oriStr;
	string code;

	TreeNode()
	{
		weight = 0;
		lchild = -1;
		rchild = -1;
		parent = -1;
		isLeaves = false;
		oriStr = "";
		code = "";
	}
};

class HuffmanTree
{
public:
	HuffmanTree();
	~HuffmanTree(){};
	friend ostream & operator<<(ostream & out, const HuffmanTree & huff);

private:
	vector<TreeNode> hufftree;					//树的所有节点，前NumberOfLeaves个节点是叶子
	int NumberOfLeaves;							//叶子结点个数

	void SelectTwoMin(int& min1, int& min2);		//选择权重最小的两个无父亲节点
	void Encoded();
	void Encoded(int num, string str);			//求编码
};

HuffmanTree::HuffmanTree()
{
	cout << "请输入叶子的个数：";
	cin >> NumberOfLeaves;

	TreeNode temp;

	temp.isLeaves = true;
	cout << "输入格式（叶子名称 叶子频率）：" << endl;
	//创建所有叶子节点
	for (int i = 0; i < NumberOfLeaves; ++i)
	{
		cin >> temp.oriStr >> temp.weight;
		hufftree.push_back(temp);
	}

	//构建哈夫曼树
	//创建所有非叶子节点
	//需要循环n-1次
	int min1;
	int min2;
	temp.isLeaves = false;
	for (int i = NumberOfLeaves; i < 2 * NumberOfLeaves - 1; ++i)
	{
		SelectTwoMin(min1, min2);

		temp.weight = hufftree[min1].weight + hufftree[min2].weight;
		temp.lchild = min1;			//遵循左小右大
		temp.rchild = min2;
		temp.parent = -1;
		hufftree.push_back(temp);

		hufftree[min1].parent = i;
		hufftree[min2].parent = i;
	}

	Encoded();
}

void HuffmanTree::SelectTwoMin(int& min1, int& min2)
{
	int minW = INT_MAX;
	for (int i = 0; i < hufftree.size(); ++i)
	{
		if (hufftree[i].parent == -1 && hufftree[i].weight < minW)
		{
			min1 = i;
			minW = hufftree[i].weight;
		}
	}

	minW = INT_MAX;
	for (int i = 0; i < hufftree.size(); ++i)
	{
		if (hufftree[i].parent == -1 && hufftree[i].weight < minW&&i != min1)
		{
			min2 = i;
			minW = hufftree[i].weight;
		}
	}
}

void HuffmanTree::Encoded()
{
	Encoded(hufftree.size() - 1, "");
}

void HuffmanTree::Encoded(int num, string str)
{
	if (hufftree[num].isLeaves)
		hufftree[num].code = str;
	else
	{
		Encoded(hufftree[num].lchild, str + "0");
		Encoded(hufftree[num].rchild, str + "1");
	}
}

ostream & operator<<(ostream & out, const HuffmanTree & huff)
{
	cout << "频率  " << "父节点  " << "左孩子  " << "右孩子  " << endl;
	for (int i = 0; i < huff.hufftree.size(); i++)
	{
		cout << huff.hufftree[i].weight << " "
			<< huff.hufftree[i].parent << " "
			<< huff.hufftree[i].lchild << " "
			<< huff.hufftree[i].rchild << " " << endl;
	}
	cout << endl;

	for (int i = 0; i < huff.NumberOfLeaves; i++)
		cout << huff.hufftree[i].oriStr << "的编码为:" << huff.hufftree[i].code << endl;

	return out;
}


#endif