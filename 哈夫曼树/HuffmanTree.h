#ifndef _HUFFMANTREE_H__
#define _HUFFMANTREE_H__

#include <iostream>
#include <vector>
#include <string>
using namespace std;

//�����������OT��Ҳ����LT������������LT������
//��Ϊ�ڵ㲻����ָ�����ӣ�������һ�����������ӣ���������Žڵ��������е�λ��
struct TreeNode
{
	//��������
	int weight;
	int lchild, rchild;
	int parent;
	//��Ҷ��ӵ�е�����
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
	vector<TreeNode> hufftree;					//�������нڵ㣬ǰNumberOfLeaves���ڵ���Ҷ��
	int NumberOfLeaves;							//Ҷ�ӽ�����

	void SelectTwoMin(int& min1, int& min2);		//ѡ��Ȩ����С�������޸��׽ڵ�
	void Encoded();
	void Encoded(int num, string str);			//�����
};

HuffmanTree::HuffmanTree()
{
	cout << "������Ҷ�ӵĸ�����";
	cin >> NumberOfLeaves;

	TreeNode temp;

	temp.isLeaves = true;
	cout << "�����ʽ��Ҷ������ Ҷ��Ƶ�ʣ���" << endl;
	//��������Ҷ�ӽڵ�
	for (int i = 0; i < NumberOfLeaves; ++i)
	{
		cin >> temp.oriStr >> temp.weight;
		hufftree.push_back(temp);
	}

	//������������
	//�������з�Ҷ�ӽڵ�
	//��Ҫѭ��n-1��
	int min1;
	int min2;
	temp.isLeaves = false;
	for (int i = NumberOfLeaves; i < 2 * NumberOfLeaves - 1; ++i)
	{
		SelectTwoMin(min1, min2);

		temp.weight = hufftree[min1].weight + hufftree[min2].weight;
		temp.lchild = min1;			//��ѭ��С�Ҵ�
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
	cout << "Ƶ��  " << "���ڵ�  " << "����  " << "�Һ���  " << endl;
	for (int i = 0; i < huff.hufftree.size(); i++)
	{
		cout << huff.hufftree[i].weight << " "
			<< huff.hufftree[i].parent << " "
			<< huff.hufftree[i].lchild << " "
			<< huff.hufftree[i].rchild << " " << endl;
	}
	cout << endl;

	for (int i = 0; i < huff.NumberOfLeaves; i++)
		cout << huff.hufftree[i].oriStr << "�ı���Ϊ:" << huff.hufftree[i].code << endl;

	return out;
}


#endif