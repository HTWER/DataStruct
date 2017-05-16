#include <iostream>
using namespace std;

//双向循环链表

//用户使用时，下标从1开始

//链表节点
template <class DataType>
struct Node
{
	DataType data;
	Node<DataType> * left;
	Node<DataType> * right;
};

template <class DataType>
class LinkList
{
public:
	LinkList();
	LinkList(DataType a[], int n);
	~LinkList();

	void Insert(int i, DataType x);	//在指定位置插入数据
	DataType Erase(int i);			//将删除位置的数据返回
	int Find(DataType x);			//确定数据位置
	DataType At(int i);				//按位置获取数据

	void PrintList();				//正向遍历输出
	void PrintList2();				//反向遍历输出

	int Length();					//获取链表长度

private:
	Node<DataType> * rear;			//一个没有数据的节点，一直正确处于循环链中，统一空链表和非空链表的操作
	int length;						//记录了链表长度
};

template <class DataType>
LinkList<DataType>::LinkList()
{
	rear = new Node<DataType>();
	rear->right = rear;				//由于是循环链表，所以这个辅助节点要自己指向自己
	rear->left = rear;

	length = 0;
}

template <class DataType>
LinkList<DataType>::LinkList(DataType a[], int n)
{
	this->LinkList<DataType>::LinkList();		//为什么这里要这样写？

	for (int i = 0; i < n; ++i)
		Insert(length + 1, a[i]);
}

template <class DataType>
LinkList<DataType>::~LinkList()
{
	for (int i = 0; i < length; ++i)
		Erase(1);

	delete rear;
}

template <class DataType>
void LinkList<DataType>::Insert(int index, DataType x)
{
	if (index > length + 1)						//可以在长度的后一位插入
	{
		cout << "数据插入失败" << endl;
		abort();
	}

	Node<DataType>* p = rear;
	for (int i = 0; i < index - 1; ++i)			//定位到插入位置的前一位
		p = p->right;
	Node<DataType>* s = new Node < DataType > ;
	s->data = x;
	s->left = p;
	s->right = p->right;
	p->right = s;
	s->right->left = s;

	++length;
}

template <class DataType>
DataType LinkList<DataType>::Erase(int index)
{
	if (length == 0)
	{
		cout << "链表为空，无法删除" << endl;
		abort();
	}

	if (index<1 || index>length)
	{
		cout << "越界删除" << endl;
		abort();
	}

	Node<DataType>* p = rear;
	for (int i = 0; i < index - 1; ++i)		//定位到删除位置的前一位
		p = p->right;
	Node<DataType>* q = p->right;
	p->right = q->right;
	q->right->left = q->left;
	DataType x = q->data;
	delete q;

	--length;

	return x;
}

template <class DataType>
int LinkList<DataType>::Find(DataType x)
{
	if (rear->right == rear)
	{
		cout << "链表为空，无法定位数据" << endl;
		abort();
	}

	Node<DataType>* p = rear;
	for (int i = 1; i <= length; ++i)
	{
		p = p->right;
		if (p->data == x)
			return i;
	}

	return 0;
}

template <class DataType>
DataType LinkList<DataType>::At(int index)
{
	if (index > length)
	{
		cout << "越界访问" << endl;
		abort();
	}

	Node<DataType>* p = rear;
	for (int i = 0; i < index; ++i)
		p = p->right;

	return p->data;
}

template <class DataType>
void LinkList<DataType>::PrintList()
{
	Node<DataType>* p = rear;
	for (int i = 0; i < length; ++i)
	{
		p = p->right;
		cout << p->data << " ";
	}
	cout << endl;
}

template <class DataType>
void LinkList<DataType>::PrintList2()
{
	Node<DataType>* p = rear;
	for (int i = 0; i < length; ++i)
	{
		p = p->left;
		cout << p->data << " ";
	}
	cout << endl;
}

template <class DataType>
int LinkList<DataType>::Length()
{
	return length;
}
